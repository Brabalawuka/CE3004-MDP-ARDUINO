void caliNew() // Do this in an unknown scenario
{ 
  float ir1reading, ir2reading, ir3reading;
  
  move(convertLeftAngleToTicks(90), DIRECTION_LEFT); // rotate left
  caliFront();
  move(convertRightAngleToTicks(90), DIRECTION_RIGHT);//rotate right

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
   moveTillLeftEnd(DIRECTION_FORWARD, 200);
   moveWithSpeed(convertDistanceToTicks(7.4),   DIRECTION_BACKWARD, 200); // moving backward by 9cm when IR3 senses dist > 10cm  
   caliLeft(); //check left allignment   
 
}


void caliForwardtoWall() // move until got wall in front 
{
  float dist = 9.9;
  float error = 0.4;

  float ir1reading, ir3reading;
  ir1reading = readIR1();
  ir3reading = readIR3();

  if(ir1reading > dist && ir3reading > dist) // checking if there is a need for me to move first
  {
    moveTillEnd( DIRECTION_FORWARD); //move
  }
  caliFront();    
}


void caliLeftBack() // Do this when there is wall on the left and back
{
  move(convertLeftAngleToTicks(180), DIRECTION_LEFT); // rotate left
  caliFront();
  move(convertRightAngleToTicks(90), DIRECTION_RIGHT);//rotate right
  caliFront();
  move(convertRightAngleToTicks(90), DIRECTION_RIGHT);
  caliLeftAlignmnet();

}


void caliLeft(){

  float ir4Reading, ir5Reading;
  ir4Reading = readIR4Cali();
  ir5Reading = readIR5Cali();

  if(ir5Reading <= 4.5 || ir5Reading >= 5.5 || ir4Reading >= 5.5 || ir4Reading <= 4.5)
  {
    move(convertLeftAngleToTicks(90), DIRECTION_LEFT);
    caliFront();
    move(convertRightAngleToTicks(90), DIRECTION_RIGHT);//rotate right
  }
  caliLeftAlignmnet();

}

void caliFront() //check if it is parallel to my front wall using sensors (IR2 & IR6)
{
  
  caliFrontAlignment();
  float ir1reading, ir2reading, ir3reading;
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
//  caliDistance();
//  caliAlignment();

}







//Calibrite the distance to the front wall as 5cm using front sensors
//void caliDistance()
//{
//  bool tried_front = false;
//  bool tried_back = false;
//  float dist = 4.9;
//  float error = 0.4;
//
//  float ir1reading, ir3reading;
//  ir1reading = readIR1Cali();
//  ir3reading = readIR3Cali();
//
//
//    while( ( (abs(ir1reading - dist)> error)  || (abs(ir3reading- dist)> error) ) //first checking if there is a difference and there is a need to calibrate
//           && not(tried_front && tried_back)){ //will stop when when IR reading is within error && both (tried_front & tried_back are true).
//
//    if (ir1reading < dist || ir3reading < dist) // so if the distance from the front is < than 5cm, we move backward
//    {
//      moveWithSpeed(convertDistanceToTicks(0.2),   DIRECTION_BACKWARD, 200);
//      ir1reading = readIR1Cali();
//    
//      ir3reading = readIR3Cali();
//      tried_front = true;
//    }
//    else if (ir1reading > dist && ir3reading > dist) // so if the distannce front is > than 5 cm, we move forward
//    {
//      moveWithSpeed(convertDistanceToTicks(0.2),DIRECTION_FORWARD, 200);
//      ir1reading = readIR1Cali();
//    
//      ir3reading = readIR3Cali();
//      tried_back = true;
//    }
//  }
//}

//Calibrite the alignment to front walls using front sensors
void caliFrontAlignment(){


  bool tried_left = false;
  bool tried_right = false;
  
  float ir_diff = readIR1Cali() - readIR3Cali();
  

  //using Front left and Front right sensors
  while ((abs(ir_diff) > 0.2) && not(tried_left && tried_right))//gg to enter loop as long as there is a difference btw the 2 front sensors 
  {
    
    if (ir_diff < 0.3) //if my ir1 is closer to the wall, then we move on the left
    {
      //left adjustment
      moveWithSpeed(convertLeftAngleToTicks(0.2), DIRECTION_LEFT, 200); //move left
      tried_left = true;
    }
    else if (ir_diff > 0.2) // if my ir3 is closer to the wall, then we move on the right
    {
      //right adjustment
      moveWithSpeed(convertRightAngleToTicks(0.2), DIRECTION_RIGHT, 200); //move right
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
  while (abs(ir_diff) > 0.2 && not(tried_left && tried_right))
  {

    //delay(10);

    if (ir_diff < 0.3) //if my ir4 is closer to the wall, then we move on the left
    {
      //left
      moveWithSpeed(convertLeftAngleToTicks(0.2), DIRECTION_LEFT, 200);
      tried_left = true;
    }
    else if (ir_diff > 0.2) //if my ir5 is closer to the wall, then we move on the right
    {
      //right
      moveWithSpeed(convertRightAngleToTicks(0.2), DIRECTION_RIGHT, 200);
      tried_right = true;
    }
    

    ir_diff = readIR5Cali() - readIR4Cali();
  }


}
//void caliDistance1() //Using IR3
//{
//  bool tried_front = false;
//  bool tried_back = false;
//  float dist = 4.9;
//  float error = 0.4;
//
//  float ir3reading;
//  ir3reading = readIR3Cali();
//
//
//    while( (abs(ir3reading- dist)> error) && not(tried_front && tried_back)){ //will stop when when IR reading is within error && both (tried_front & tried_back are true).
//
//    if (ir3reading < dist) // so if the distance from the front is < than 5cm, we move backward
//    {
//      moveWithSpeed(convertDistanceToTicks(0.2),   DIRECTION_BACKWARD, 200);
//   
//      ir3reading = readIR3Cali();
//      tried_front = true;
//    }
//    else if (ir3reading > dist) // so if the distannce front is > than 5 cm, we move forward
//    {
//      moveWithSpeed(convertDistanceToTicks(0.2),DIRECTION_FORWARD, 200);
//    
//      ir3reading = readIR3Cali();
//      tried_back = true;
//    }
//  }
//}


void caliDistanceUsingSensor(int number) //Using IR1 IR2 IR3
{
  bool tried_front = false;
  bool tried_back = false;
  float distNear = 4.9;
  float distFar = 5.1;
  float error = 0.3;

  float irreading;
  switch (number){
     case 1: {irreading = readIR1Cali();break;}
     case 2: {irreading = readIR2Cali();break;}
     case 3: {irreading = readIR3Cali();break;}
   }
   
   resetGlobalConstants();
   while( (abs(irreading - 5)> error) && not(tried_front && tried_back)){
      //will stop when when IR reading is within error && both (tried_front & tried_back are true).
      while (irreading < distNear) // so if the distance from the front is < than 5cm, we move backward
      {      
         double pid = 0;
         md.setSpeeds((200 + pid) * DIRECTION_BACKWARD[0]  , (200 - pid) * DIRECTION_BACKWARD[1]);
         computeDelta();
         pid = computePID();
         switch (number){
           case 1: {irreading = readIR1Cali();break;}
           case 2: {irreading = readIR2Cali();break;}
           case 3:{irreading = readIR3Cali();break;}
         }
         
      }
      md.setBrakes(400, 400);
      resetGlobalConstants();
      tried_front = true;
      while (irreading > distFar) // so if the distannce front is > than 5 cm, we move forward
      {
         double pid = 0;
         md.setSpeeds((200 + pid) * DIRECTION_FORWARD[0]  , (200 - pid) * DIRECTION_FORWARD[1]);
         computeDelta();
         pid = computePID();
         switch (number){
           case 1: {irreading = readIR1Cali();break;}
           case 2: {irreading = readIR2Cali();break;}
           case 3:{irreading = readIR3Cali();break;}
         }
      }
      md.setBrakes(400, 400);
      tried_back = true;
  }
}
