/*
Library for navigation
Created by Emily Lau, Isaac Lam, February 2024
IDP
*/
#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <Adafruit_MotorShield.h>
#include "Arduino.h"
#include "Wire.h"
#include "DFRobot_VL53L0X.h"
#include "../globalflags/globalflags.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Set motor ports M2 (left) , M1 (right)
Adafruit_DCMotor *motor_right = AFMS.getMotor(1);
Adafruit_DCMotor *motor_left = AFMS.getMotor(2);

// Set LED pins and blinking time variables
int blueLED = 12;
bool blueLEDStatus = 0;
unsigned long currentLEDMillis;
unsigned long startLEDMillis;

// Global flags for motor status
int RightMotorSpeed = 0;
int* RightMotorSpeedPter = &RightMotorSpeed;
int LeftMotorSpeed = 0;
int* LeftMotorSpeedPter = &LeftMotorSpeed;

// Delay time in ms for rotateright90degrees
const int rotate90Offset = 120;

// forwardawhile Time between line and back wall in open area
const int lineToBackWall3 = 1500;        // block 3
const int lineToBackWall4 = 1800;        // block 4

// TOF Distances in open area
const int sideWallDistance = 300;
const int backWallDistance3 = 500;                   // value between back wall and front face of block
const int backWallDistance4 = 515;                   // value between back wall and front face of block
const int leaveWallDistance = 2300;
const int sensorWheelDistance = 2000;                

// Set line sensors to input pins
int lineleftPin = 2;
int linerightPin = 3;
int lineSideRightPin = 13;
int lineSideLeftPin = 8;
int valLeft = digitalRead(lineleftPin); // read left input value
int valRight = digitalRead(linerightPin); // read right input value
int valSideRight = digitalRead(lineSideRightPin); // read side right input value
int valSideLeft = digitalRead(lineSideLeftPin); // read side left input value

// Set ToF sensor to input pins
DFRobot_VL53L0X sensor; 




// array of routes; does not include backing out in free space; does not include U-turns after picking block up in line area
const char routes[16][6] = {  

  // REMEMBER TO CHANGE SIZEOFROUTES ARRAY AFTER CHANGING ROUTES

          "RL",               // 0: block 1 to green 
          "LSR",              // 1: block 1 to red
          "SRSR",             // 2: green to block 2
          "SLL",              // 3: red to block 2
          "LSLS",             // 4: block 2 to green
          "RRS",              // 5: block 2 to red
          "SSS",              // 6: green to block 3
          "SLSRR",            // 7: red to block 3
          "RSSLS",            // 8: block 3 to green
          "SS",               // 9: block 3 to red
          "SSR",              // 10: green to block 4
          "SSL",              // 11: red to block 4
          "RLS",              // 12: block 4 to green
          "LSRS",             // 13: block 4 to red
          "RSRS",              // 14: green to finish
          "LLS"};              // 15: red to finish


  // REMEMBER TO CHANGE SIZEOFROUTES ARRAY AFTER CHANGING ROUTES

// number of junctions of each route, used when passing as second argument to routefollow()
const int sizeOfRoutes[16] = {2,3,4,3,4,3,3,5,5,2,3,3,3,4,4,3};
int routePtr;

// Set speed constants
const int HighSpeed = 250;            // adjustment on straight line
const int NormalSpeed = 200;          // straight line
const int LowSpeed = 0;               // adjustment on straight line
const int RotationSpeed = 180;        // rotation
const int OpenAreaSpeed = 100;        // slow speed in open area

// Junction to outpost (green red area) time in milliseconds
int junctionOutpostTimeStraight = 950; 
int junctionOutpostTimeTurn = 1200; 

// Junction to finish box time in milliseconds
int junctionFinishTime = 900;

// Leave junction time (make sure junction is not detected twice)
int leaveJunctionTime = 350;

// functions
void updaterightmotorspeed(int NewRightMotorSpeed);
void updateleftmotorspeed(int NewLeftMotorSpeed);
void updatelinesensors();
void junctionrotation(char Direction[2]);
void stopmoving();
void rotateright90degrees();
void gostraight();
void forwardawhile(int time);
void backwardawhile(int time);
void findandapproachblock();
void returntoline();
void routefollow(const char route[], int numberOfJunctions);

#endif
