#include "block_identification.h"



// Function to control LED lighting
void lightled(int ledPin) {
  digitalWrite(ledPin, HIGH);  // Turn on LED
  delay(6000);
  digitalWrite(ledPin, LOW);   // Turn off LED
  delay(2000);
}

// Function to detect the type of block based on distance
void identifyblock() {
  float usVal = analogRead(usSensorPin);
  float usDistance = usVal * maxRange  / adcSolution;

  blockNumber += 1;   // update block number

  if (usDistance <= solidUpperBound) {
    // SOLID block

    lightled(redLED);

    blockType = 1;        // update block type

  } else if (usDistance > solidUpperBound && usDistance <= foamUpperBound) {
    // FOAM block

    lightled(greenLED);

    blockType = 0;        // update block type

  } else {
    // This code can be used as failsafe in the future, in case we try to handle the case where dist > foamUpperBound.

    lightled(greenLED);

    blockType = 0;        // update block type

  }

  if (!pickup) {  
    liftblock();        // lift block after identification
  }
}

void liftblock() {

  // Rotate the servo from servoStartAngle to servoEndAngle
  for (int pos = servoStartAngle; pos <= servoEndAngle; pos += 1) {
    pincerServo.write(pos);
    delay(15);
  }

  pickup = 1; // Set the boolean to true indicating that the block is picked up
}

void releaseblock() {

  // Rotate the servo from servoEndAngle to servoStartAngle
  for (int pos = servoEndAngle; pos >= servoStartAngle; pos -= 1) {
    pincerServo.write(pos);
    delay(15);
  }

  pickup = 0; // Set the boolean to false indicating that the block is released
}
