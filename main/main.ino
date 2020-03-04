/*
|**********************************************************************;
* Project           : MDP Arduino Subsystem
*
* Program name      : fuckMDP.ino
*
* Author            : Zizheng
*
* Date created      : 0101/2020
*
* Purpose           : This script tests some basic movements. 
*                       per revolution of the wheel is math.pi * 6 * 2 cm, which is around 37 cm
*                       theoretical number of ticks for that is 2249.
*                       so, let's say if you want 30cm. Your number of ticks should be 2249 / 37 * 30
*
* Updated           : 1302/2020
|**********************************************************************;
*/


#include <DualVNH5019MotorShield.h>
#include <EnableInterrupt.h>
#include "string.h"
#include "SharpIR.h"

DualVNH5019MotorShield md;

// this is the new set of pins
const int M1A = 11;  //Right
const int M1B = 13;  //Right
const int M2A = 3;  //Left
const int M2B = 5;  //Left


volatile uint16_t m1Ticks = 0;
volatile uint16_t m2Ticks = 0;
// global variables for finding PID (those indirectly based on interrupts have 'volatile' as well, may not be necessary)
volatile uint16_t deltaM1Ticks = 0;
volatile uint16_t deltaM2Ticks = 0;
volatile uint16_t lastM1Ticks = 0;
volatile uint16_t lastM2Ticks = 0;
int16_t lastError = 0;
int16_t cumError = 0;


const double SPEED = 350; //cannot be greater than 350 to leave spce for pid control 

//IR sensor pin
#define irR1 A0 
#define irR2 A1 
#define irR3 A2 
#define irR4 A3 // Long Range Sensor
#define irR5 A4 
#define irR6 A5 


const int DIRECTION_FORWARD[2] = {1, 1};
const int DIRECTION_BACKWARD[2] = {-1, -1};
const int DIRECTION_LEFT[2] = {1, -1};
const int DIRECTION_RIGHT[2] = {-1, 1};

//for checklist only
bool detect_obs = false; 
float irLB = 0;


void setup() {
  Serial.begin(115200);
  
  enableInterrupt(M1B, m1Edge, RISING);
  enableInterrupt(M2B, m2Edge, RISING);
  md.init();
  // put your setup code here, to run once:


  /*CheckList*/
   //navObs(convertDistanceToTicks(100),DIRECTION_FORWARD); //uncomment this and comment 'loopreading' to check for navigate obstacle checklist */
}

void loop() {
  
  loopReading();
  // put your main code here, to run repeatedly:

  //loopSensorTest();
}


void resetGlobalConstants()
{
    m1Ticks = 0;
    m2Ticks = 0;

    deltaM1Ticks = 0;
    deltaM2Ticks = 0;
    
    lastError = 0;
    
}

void computeDelta()
{
    deltaM1Ticks = m1Ticks - lastM1Ticks;
    deltaM2Ticks = m2Ticks - lastM2Ticks;

    lastM1Ticks = m1Ticks;
    lastM2Ticks = m2Ticks;
    
}
