void caliNew() // Do this in an unknown scenario
{ 
  float ir1reading, ir2reading, ir3reading;

  caliLeft();

  ir1reading = readIR1Cali();
  ir2reading = readIR2Cali();
  ir3reading = readIR3Cali();
  
  if(ir1reading < ir3reading && ir1reading < ir2reading)
  {
    caliDistanceUsingSensor(1);
  }else if(ir2reading < ir1reading && ir2reading < ir3reading)
  {
    caliDistanceUsingSensor(2);
  }else if(ir3reading < ir1reading && ir3reading < ir2reading)
  {
    caliDistanceUsingSensor(3);
  }
  caliLeftAlignmnet();
}



void caliEdge() //when there is a wall on the the left and you want the robot to be in the middle
{
   caliLeft();
   moveTillLeftEnd();
   move(convertDistanceToTicks(7.4), DIRECTION_BACKWARD, true); // moving backward by 7.4cm when IR4 senses dist > 10cm  
   caliLeft(); //check left allignment   
 
}


void caliLeftBack() // Do this when there is wall on the left and back
{
  move(convertLeftAngleToTicks(180), DIRECTION_LEFT, false); // rotate left
  caliFront();
  move(convertRightAngleToTicks(90), DIRECTION_RIGHT, false);//rotate right
  caliFront();
  move(convertRightAngleToTicks(90), DIRECTION_RIGHT, false);
  caliLeftAlignmnet();

}


void caliLeft(){

  float ir4Reading, ir5Reading;
  ir4Reading = readIR4Cali();
  ir5Reading = readIR5Cali();

  caliLeftAlignmnet();
  
  ir4Reading = readIR4Cali();
  ir5Reading = readIR5Cali();

  if(ir5Reading <= 4.5 || ir5Reading >= 5.5 || ir4Reading >= 5.5 || ir4Reading <= 4.5)
  {
    move(convertLeftAngleToTicks(90), DIRECTION_LEFT, true);
    caliFront();
    move(convertRightAngleToTicks(90), DIRECTION_RIGHT, true);//rotate right
    delay(100);
    caliLeftAlignmnet();
  }
  
  
}

void caliFront() //check if it is parallel to my front wall using sensors (IR2 & IR6)
{
  caliDistance();
 
  caliFrontAlignment();

  caliDistance();
  caliFrontAlignment();
}







//Calibrite the distance to the front wall as 5cm using front sensors
void caliDistance()
{
  bool tried_front = false;
  bool tried_back = false;
  float dist = 4.8;
  float error = 0.3;

  float ir1reading, ir3reading;
  ir1reading = readIR1Cali();
  ir3reading = readIR3Cali();


    while( ( (abs(ir1reading - dist)> error)  || (abs(ir3reading- dist)> error) ) //first checking if there is a difference and there is a need to calibrate
           && not(tried_front && tried_back)){ //will stop when when IR reading is within error && both (tried_front & tried_back are true).

    if (ir1reading < (dist-0.2) || ir3reading < (dist-0.2)) // so if the distance from the front is < than 5cm, we move backward
    {
      move(convertDistanceToTicks(0.2), DIRECTION_BACKWARD, true);
      tried_front = true;
    }
    else if (ir1reading > (dist+0.2) || ir3reading > (dist+0.2)) // so if the distannce front is > than 5 cm, we move forward
    {
      move(convertDistanceToTicks(0.2),DIRECTION_FORWARD, true);
      tried_back = true;
    }
    ir1reading = readIR1Cali();
    ir3reading = readIR3Cali();
  }
}


void caliFrontAlignment(){


  bool tried_left = false;
  bool tried_right = false;
  
  float ir_diff = readIR1Cali() - readIR3Cali();
  

  //using Front left and Front right sensors
  while ((abs(ir_diff) > 0.2) && not(tried_left && tried_right))//gg to enter loop as long as there is a difference btw the 2 front   sensors 
  {
    
    if (ir_diff < -0.2) //if my ir1 is closer to the wall, then we move on the left
    {
      //left adjustment
      move(convertLeftAngleToTicks(0.2), DIRECTION_LEFT, true); //move left
      tried_left = true;
    }
    else if (ir_diff > 0.2) // if my ir3 is closer to the wall, then we move on the right
    {
      //right adjustment
      move(convertRightAngleToTicks(0.2), DIRECTION_RIGHT, true); //move right
      tried_right = true;
    }
    ir_diff = readIR1Cali() - readIR3Cali();
  }

}

 //check if it is parallel to my left wall using my side sensors (IR4 & IR5)
void caliLeftAlignmnet(){

  bool tried_left = false;
  bool tried_right = false;

  
  float ir_diff = readIR5Cali() - readIR4Cali();

  // using Right front and right back sensors
  while (abs(ir_diff) > 0.3 && not(tried_left && tried_right))
  {

    //delay(10);

    if (ir_diff < -0.3) //if my ir4=5 is closer to the wall, then we move on the left
    {
      //left
      move(convertLeftAngleToTicks(0.2), DIRECTION_LEFT, true);
      tried_left = true;
    }
    else if (ir_diff > 0.3) //if my ir4 is closer to the wall, then we move on the right
    {
      //right
      move(convertRightAngleToTicks(0.2), DIRECTION_RIGHT, true);
      tried_right = true;
    }
    ir_diff = readIR5Cali() - readIR4Cali();
  }


}


void caliDistanceUsingSensor(int number) //Using IR1 IR2 IR3
{
  bool tried_front = false;
  bool tried_back = false;
  float distNear = 4.4;
  float distFar = 4.8;
  float error = 0.3;


  float irreading;
  switch (number){
     case 1: {irreading = readIR1Cali();break;}
     case 2: {irreading = readIR2Cali();break;}
     case 3: {irreading = readIR3Cali();break;}
   }


  while( (abs(irreading - 4.6)> error) && not(tried_front && tried_back)){ //will stop when when IR reading is within error && both (tried_front & tried_back are true).

    if (irreading < distNear) // so if the distance from the front is < than 5cm, we move backward
    {
      move(convertDistanceToTicks(0.2), DIRECTION_BACKWARD, true);
      tried_front = true;
    }
    else if (irreading > distFar) // so if the distannce front is > than 5 cm, we move forward
    {
      move(convertDistanceToTicks(0.2), DIRECTION_FORWARD, true);
      tried_back = true;
    }
    switch (number){
        case 1: {irreading = readIR1Cali();break;}
        case 2: {irreading = readIR2Cali();break;}
        case 3: {irreading = readIR3Cali();break;}
      }
  }

}
