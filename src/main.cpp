#include <Arduino.h>
#include <Servo.h>
/**
 * Create and program a device that detects light in much the same way radar detects radio waves 
 * or lidar detects laser light. 
 * Your light wave radar will use a servo to point the phototransistor around the room, 
 * measuring light intensity.
 * Your light wave radar system will be a manual scanner that moves by accepting commands from you through the serial monitor.
**/


// name Arduino board pins used by the circuit
const int sensorPin = A0;
const int servoPin = 3;
const int LEDPin = 10;

int servoAngle = 0;
int inputCommand = 0;
int lightAmount = 0;

Servo myServo; // create servo Onject

void setup() {
  // put your setup code here, to run once:
  pinMode(LEDPin, OUTPUT);
  Serial.begin(9600);
  myServo.attach(servoPin);   // attaches the servo on pin 3 to the servo object
  myServo.write(servoAngle);  // move the servo to the starting position
  delay(1000); 
}

void loop() {
  // check if there is any data in the serial buffer
  if (Serial.available() > 0) {
    // read the first byte and delete it from the buffer
    inputCommand = Serial.read();
    
    switch (inputCommand) {
      case 'i':
      // Increase angle by 10 degrees
      servoAngle = servoAngle + 10;
      // make sure the angle is within the servo's limits
        if (servoAngle >= 180) {
          servoAngle = 180;
          digitalWrite(LEDPin, HIGH);
          delay(500);
          digitalWrite(LEDPin, LOW);
        }
      break;
      case 'd':
      // Decrease angle by 10 degrees
      servoAngle = servoAngle - 10;
      // make sure the angle is within the servo's limits
        if (servoAngle <= 0) {
          servoAngle = 0;
          digitalWrite(LEDPin, HIGH);
          delay(500);
          digitalWrite(LEDPin, LOW);
        }
      break;    
    }

      // move servo to the correct angle
    myServo.write(servoAngle);
    delay(500);
    // read the light sensor and store the measurement in a variable
    lightAmount = analogRead(sensorPin);

    Serial.print("Angle: ");
    Serial.print(servoAngle);
    Serial.print("     Light Intensity: ");
    Serial.println(lightAmount);
  }
}