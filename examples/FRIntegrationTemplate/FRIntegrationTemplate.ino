// Template script for the integrated Flight Recorder. In this script the basic logger and servo handler is implemented
// Required hardware:
// - 1x Flight Recorder Board with ESP32
// - 1x MPU6050
// - 1x SD Card reader
// - 1x Turnigy TGY IA6B Receiver programmed in PPL mode
// - 1x Tunigy TGY-i6S Controller programmed in PPL mode
// - 3x breadboard cables female-male
// Connections:
// - GPS mounted on board
// - SD card reader mounted on board
// - TGY channel PPM, pin 1 - FR Board, PPL2 GND
// - TGY channel PPM, pin 2 - FR Board, PPL2, D4
// - TGY channel PPM, pin 3 - FR Board, J11 5V (or connected to other 5V source)
// Required libraries:
// - FRLib (download from https://github.com/josmeuleman/FRLib, unzipped in ../Documents/Arduino/libraries/ )
// - Adafruit_MPU6050.h
//
// 2023-04-20, Jos Meuleman, Inholland Aeronautical & Precision Engineering, The Netherlands


#include <FRTimer.h>
#include <FRLogger.h>
#include <FRLED.h>
#include <FRButton.h>
#include <FRMPU6050Manager.h>  //Use a custom library that internally initializes and logs the MPU6050 so you don't need #include <Adafruit_MPU6050.h>
#include <FRPPMReceiverManager.h>

// Some switches have three states. We make constants defining LOSTATE (-1), MIDSTATE (0) and HISTATE(1)
typedef enum triStateSwitch {
  LOSTATE = -1,
  MIDSTATE,
  HISTATE
};

typedef enum triStateMotion {
  MOVEDOWN = -1,
  NOMOVE,
  MOVEUP
};



const int I2C_SDA = 33;             // The data pin for I2C communication
const int I2C_SCL = 32;             // The clock pin for I2C communcation
const int PINSWITCH = 22;           // The pin number for he button to start and stop logging
const int PINLED = 21;              // The pin number for the LED
const int PINAD = 34;               // Analog input pin number
const int LOOPTIMELOGGERMS = 100;   // Loop time for reading the AD channel in milliseconds
const int LOOPTIMESERVOMS = 10;     // Loop time for reading the AD channel in milliseconds
const int PINPPM2 = 4;              // PM2 input pint
const int NUMBEROFCHANNELS2 = 8;    // Number of Channels of Receiver2

// Create all objects
Timer loggerTimer(LOOPTIMELOGGERMS);  // Timer object for the clock
Timer servoTimer(LOOPTIMESERVOMS);    // Timer object for the clock

Logger myLogger;                   // Logger object for logging sensors to the SD
Button myButton(PINSWITCH, true);  // Create a button object with the given pin. True for an inverted button, false for a normal button
LED myLed(PINLED);                 // Create a led object with the given pin.
MPU6050Manager myMPU;              // Make an object for the sensor manager for the MPU6050 (accelerometer and gyro)

PPMReceiverManager receiver2(PINPPM2, NUMBEROFCHANNELS2);  // Create a PPM receiver object with given pin and number of channels
int channelValues[NUMBEROFCHANNELS2];
// Suggestion for signal mapping
// channel0 - tick up --> handle cargo drop servo
// channel1 - NA
// channel2 - NA
// channel3 - NA
// channel4 - SWA UP/DOWN -> stop/start logging
// channel5 - SWB UP/MID/DOWN -> gears down & hatch open / gears up & hatch open / gears up & hatch closed
// channel6 - NA
// channel7 - SWD UP/DOWN -> cargo bay closed/open
const byte LOGGERSWITCHCHANNEL = 4;
const byte LANDINGGEARCHANNEL = 5;

// Threshold for discrete PPM signals
const int PPMTHRESHLOW = 850;
const int PPMTHRESHMID = 1100;
const int PPMTHRESHHIGH = 1350;

// States for starting and stopping the logger
bool loggerSwitchState = false;
bool loggerSwitchStatePrev = false;
bool startLogger = false;
bool stopLogger = false;

// States for landing gear
triStateSwitch landingGearSwitchState;
triStateSwitch landingGearSwitchStatePrev;
bool isHatchOpen = true;
bool isLandingGearOut = true;
triStateMotion landingGearAction = NOMOVE;
triStateMotion landingGearHatchAction = NOMOVE;

const byte NUMBEROFSERVOS = 4;
const int MAXSERVOSPEEDDEGS[NUMBEROFSERVOS] = {2, 10, 100, 1}; // Maximum speed of the servos in degrees per sec
const int MAXSERVOACCDEGSS[NUMBEROFSERVOS] = {10, 10, 10, 10}; // Maximum acceleration of the servos in degrees per sec2
int servoTargetPos[NUMBEROFSERVOS] = {0, 0, 0, 0}; //The initial state of the servos
float servoActualPos[NUMBEROFSERVOS];

//---------------------------------------------------------------------------------------------------------
// SETUP
// This block of code is only run once at the beginning
//---------------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);  // Start the serial communciation
  Wire.begin(I2C_SDA, I2C_SCL);
  Wire.setClock(400000);

  // The Wire connection must be made before initializing the MPU
  if (!myMPU.Init(Wire, MPU6050_RANGE_4_G, MPU6050_RANGE_500_DEG)) {
    Error("MPU not found!");
  }
  receiver2.Init();

  if (!myLogger.CheckSD()) {
    Error("No SD card found!");
  }

  myLogger.AddSensor(&myMPU);

  loggerTimer.Start();
  servoTimer.Start();

  for (int i = 0; i < NUMBEROFSERVOS; i++) {
    servoActualPos[i] = servoTargetPos[i];
  }

}

//---------------------------------------------------------------------------------------------------------
// LOOP
// This block of code is looped infinitely
//---------------------------------------------------------------------------------------------------------
void loop() {
  //-------------------------------------------------------------------------------------------------------
  // Read the receiver2 and store the values
  //-------------------------------------------------------------------------------------------------------
  for (int i = 0; i < NUMBEROFCHANNELS2; i++) {
    channelValues[i] = servoTargetPos[i];
  }

  //-------------------------------------------------------------------------------------------------------
  // Process the controller channels
  //-------------------------------------------------------------------------------------------------------

  // Read switch SWA (high/low) for logging
  loggerSwitchState = IsPPMHigh(channelValues[LOGGERSWITCHCHANNEL]);
  // Compare the state with the previous state:
  startLogger = (loggerSwitchState < loggerSwitchStatePrev);  //if new state is LOW (0) and old state is HIGH (1)
  stopLogger = (loggerSwitchState > loggerSwitchStatePrev);   //if new state is HIGH (1) and old state is LOW (1)
  loggerSwitchStatePrev = loggerSwitchState; //update the previous state for the next loop

  // Read switch SWB (high/mid/low) for landing gear. 
  HandleLandingGearSwitch(); //Update of landingGearAction and landingGearHatchAction

  //-------------------------------------------------------------------------------------------------------
  // Handle the motors
  //-------------------------------------------------------------------------------------------------------
  servoTargetPos[0] = map(channelValues[0], 600, 2100, 0, 180);
  // UpdateServos();
  // Serial.print(servoTargetPos[0]);
  // Serial.print("; ");
  // Serial.print(servoActualPos[0]);
  

  //-------------------------------------------------------------------------------------------------------
  // Start or stop logger
  //-------------------------------------------------------------------------------------------------------
  if (startLogger) {
    if (!myLogger.IsLogging()) {  // Start logging
      Serial.println("Start logging");
      if (!myLogger.StartLogger()) {
        Error("Something went wrong with the start of the log");
      } else {
        myLed.SetOn();
        Serial.print("File opened with the name: ");
        Serial.println(myLogger.GetLoggerFileName());
      }
    }
  }
  if (stopLogger) {  // Stop logging
    Serial.println("Stop logging");
    if (!myLogger.StopLogger()) {
      Error("Something went wrong with the stopping of the log");
    } else {
      myLed.SetOff();
    }
  }


  //-------------------------------------------------------------------------------------------------------
  // Write to the log file if needed
  //-------------------------------------------------------------------------------------------------------
  
  // Check if it is time to log the data
  if (loggerTimer.LoopTimePassed()) {
    String myString = myLogger.UpdateSensors();  // Updates all connected sensors and generates a string of all sensor values;
    //Serial.print(myString);                      // Writing to the Serial Monitor will sometimes take more than 100 ms. So print to screen only when you have a slow update rate.
    myLogger.WriteLogger();                      // Only writes to logger if myLogger. IsLogging is true;
  }

  //-------------------------------------------------------------------------------------------------------
  // End of the loop
  //-------------------------------------------------------------------------------------------------------
  // Kill the time until
  if (servoTimer.WaitUntilEnd()) {
    Serial.println("Overrun!");
  }
}

//---------------------------------------------------------------------------------------------------------
// FUNCTIONS
// Here the custom functions are defined
//---------------------------------------------------------------------------------------------------------
void Error(String errorMessage) {
  Serial.println(errorMessage);
  myLed.SetBlink(100);
}


triStateSwitch GetPPMZone(int value) {
  if (value < PPMTHRESHLOW) {
    return HISTATE;
  } else if (value < PPMTHRESHHIGH) {
    return MIDSTATE;
  } else {
    return LOSTATE;
  }
}

bool IsPPMHigh(int value) {
  return (value < PPMTHRESHMID);
}

void HandleLandingGearSwitch(){
  landingGearSwitchState = GetPPMZone(channelValues[LANDINGGEARCHANNEL]);
  if (landingGearSwitchState < landingGearSwitchStatePrev) {
    // towards rectracted state
    if (landingGearSwitchState == MIDSTATE) {
      // So it was HISTATE, now pull in the gear
      landingGearAction = MOVEUP;
      landingGearHatchAction = NOMOVE;
      Serial.println("Retract gear");
    } else {
      landingGearAction = NOMOVE;
      landingGearHatchAction = MOVEUP;
      Serial.println("Close hatch");
    }
  }
  if (landingGearSwitchState > landingGearSwitchStatePrev) {
    // towards extended state
    if (landingGearSwitchState == MIDSTATE) {
      // So it was LOSTATE, now extent in the gear
      landingGearAction = NOMOVE;
      landingGearHatchAction = MOVEDOWN;
      Serial.println("Open hatch");
    } else {
      landingGearAction = MOVEDOWN;
      landingGearHatchAction = NOMOVE;
      Serial.println("Extend gear");
    }
  }
  landingGearSwitchStatePrev = landingGearSwitchState; //update the previous state for the next loop

}

void UpdateServos(){
  for (int i = 0; i < NUMBEROFSERVOS; i++) {
    float posError = servoTargetPos[i] - servoActualPos[i];
    float maxStep = MAXSERVOSPEEDDEGS[i]*LOOPTIMESERVOMS/1000.0; //maximumStep a servo can make in a loopcycle
    if (posError > maxStep) {
      posError = maxStep;
    }
    if (posError < -maxStep) {
      posError = -maxStep;
    }
    servoActualPos[i] = servoActualPos[i]+posError;

  }

}