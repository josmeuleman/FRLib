// Testscript for reading PPM signals on the Flight Recorder Board
// Testscript is developed for a Turnigy TGY IA6B controller
// Connections:
// - TGY channel PPM, pin 1 - FR Board, PPL2 GND
// - TGY channel PPM, pin 2 - FR Board, PPL2, D4
// - TGY channel PPM, pin 3 - FR Board, SD card reader, 5V (or connected to other 5V source)
//
// 2023-03-02, Jos Meuleman, Inholland Aeronautical & Precision Engineering, The Netherlands

#include <FRPPMReceiver.h>

const int PINPPM = 4;  // PPL2 input pint
const int NUMBEROFCHANNELS = 6;
const int PRINTLOOP = 10;  //We print to the screen after X measurements

// filter values are used to smooth or slow down signals. 1 = no filter
// experiment with values to see the differences
float filterValues[NUMBEROFCHANNELS] = { 0.1, 0.1, 1, 1, 0.1, 1.0 };

PPMReceiver MyReceiver(PINPPM, NUMBEROFCHANNELS);  // Create a PPM receiver object with given pin and number of channels

float channelValues[NUMBEROFCHANNELS];
int counter = 0;  //Measurement counter

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  MyReceiver.SetLowPassFilter(filterValues);  //apply the filter settings
}

void loop() {
  MyReceiver.Update();
  if (counter > PRINTLOOP) {                      // only print when the counter exceeds the printloop value
    for (int i = 0; i < NUMBEROFCHANNELS; i++) {  // Cycle through the channels to read and print the value
      channelValues[i] = MyReceiver.ReadChannel(i);
      Serial.print(channelValues[i]);
      Serial.print("; ");
    }
    Serial.println("");  // End of line
    counter = 0;         // Reset the counter
  }

  // Do
  if (channelValues[4] > 0) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }


  counter++;
}