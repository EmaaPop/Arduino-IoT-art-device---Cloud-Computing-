#include <Arduino_MKRENV.h>
#include "thingProperties.h"
#include <WiFiNINA.h>

// Define the ports of sensors and actuators
int redPin = 25;
// int greenPin = 25;
int bluePin = 27;
int pirPin = 3;
int ledPin = 1;

void setup() {
  Serial.begin(9600);
  
  if (!ENV.begin()) {
    Serial.println("Failed to initialise MKR ENV shield");
    while(1);
  }
  delay(1500);
  
  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
  */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  // WiFiDrv::pinMode(25, OUTPUT);
  // WiFiDrv::pinMode(26, OUTPUT);
  // WiFiDrv::pinMode(27, OUTPUT);

  // pinMode(redPin, OUTPUT);
  // pinMode(greenPin, OUTPUT);
  // // pinMode(bluePin, OUTPUT);
  // pinMode(pirPin, INPUT);
  // pinMode(ledPin, OUTPUT);
}

void loop() {
  // Read the temperature from the built-in sensor
  float temperature = ENV.readTemperature();
  Serial.print("Original Temperature=");
  Serial.print(temperature);
  
  CloudColor colour;

  // Map the temperature reading to an RGB value between red and blue
  u_int8_t r, g, b;
  r = map(temperature, 20, 30, 0, 255);
  b = map(temperature, 20, 30, 255, 0);
  g = 0; // We don't need green
  Serial.print(" Value of mapped r,g,b =");
  Serial.print(r);
  Serial.print(",");
  Serial.print(g);
  Serial.print(",");
  Serial.println(b);
  // Serial.println();

// Set the RGB LED to the mapped color
WiFiDrv::analogWrite(redPin, r);
  // WiFiDrv::analogWrite(greenPin, g);
WiFiDrv::analogWrite(bluePin, b);

  // Read the PIR motion sensor
int pirValue = digitalRead(pirPin);
Serial.print(pirValue);

// Control the LED Socket based on PIR motion sensor
if (pirValue == 1) {
  digitalWrite(ledPin, HIGH);
  Serial.println("high");
  } else {
  digitalWrite(ledPin, LOW);
  Serial.println("low");
  }
  
  colour.getValue().getRGB(r, g, b);
  delay(1000);
}


/*  
    Arduino with PIR motion sensor
    For complete project details, visit: http://RandomNerdTutorials.com/pirsensor
    Modified by Rui Santos based on PIR sensor by Limor Fried
*/
 
// int led = 1;                // the pin that the LED is atteched to
// int sensor = 3;              // the pin that the sensor is atteched to
// int state = LOW;             // by default, no motion detected
// int val = 0;                 // variable to store the sensor status (value)

// void setup() {
//   pinMode(led, OUTPUT);      // initalize LED as an output
//   pinMode(sensor, INPUT);    // initialize sensor as an input
//   Serial.begin(9600);        // initialize serial
// }

// void loop(){
//   val = digitalRead(sensor);   // read sensor value
//   if (val == HIGH) {           // check if the sensor is HIGH
//     digitalWrite(led, HIGH);   // turn LED ON
//     delay(100);                // delay 100 milliseconds 
    
//     if (state == LOW) {
//       Serial.println("Motion detected!"); 
//       state = HIGH;       // update variable state to HIGH
//     }
//   } 
//   else {
//       digitalWrite(led, LOW); // turn LED OFF
//       delay(200);             // delay 200 milliseconds 
      
//       if (state == HIGH){
//         Serial.println("Motion stopped!");
//         state = LOW;       // update variable state to LOW
//     }
//   }
// }
/*
  Since Colour is READ_WRITE variable, onColourChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onColourChange()  {
  // Add your code here to act upon Colour change
}
/*
  Since Temperature is READ_WRITE variable, onTemperatureChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onTemperatureChange()  {
  // Add your code here to act upon Temperature change
}