void caliNew() // Do this in an unknown scenario
{ 
  float ir2reading, ir6reading, ir5reading;
  ir2reading = readIR2();
  ir6reading = readIR6();
  ir5reading = readIR5();
  
  move(convertRightAngleToTicks(90), DIRECTION_RIGHT); // rotate left
  caliFront();
  move(convertLeftAngleToTicks(180), DIRECTION_LEFT);//rotate right
  if(ir6reading < 10)
  {
    caliDistance1();
  }
  else if(ir5reading < 10)
  {
    caliDistance2();
  }
  else if(ir2reading < 10)
  {
    caliDistance3();
  }
  caliLeftAlignmnet();

}
void caliFrontLeft() //when there is a wall on the front and left 
{
  //Calibrate distance and alignment to the front wall
  caliFront();
  move(convertRightAngleToTicks(90), DIRECTION_RIGHT); //rotate left
  caliFront();
  move(convertLeftAngleToTicks(90), DIRECTION_LEFT); //rotate right
  caliLeftAlignmnet();
 
}

void caliLeftBack() // Do this when there is wall on the left and back
{
  move(convertRightAngleToTicks(90), DIRECTION_RIGHT); // rotate left
  caliFront();
  move(convertRightAngleToTicks(90), DIRECTION_RIGHT);// rotate left
  caliFront();
  move(convertLeftAngleToTicks(180), DIRECTION_LEFT);//rotate right
  caliLeftAlignmnet();

}


void caliLeft(){

  float ir1Reading, ir3Reading;
  ir1Reading = readIR1();
  ir3Reading = readIR3();

  if(ir1Reading <= 4.2 || ir1Reading >= 5.8 || ir3Reading >= 5.8 || ir3Reading <= 4.2)
  {
    move(convertRightAngleToTicks(90), DIRECTION_RIGHT);
    caliFront();
    move(convertLeftAngleToTicks(90), DIRECTION_LEFT);//rotate right
  }

  caliLeftAlignmnet();
}

void caliFront() //check if it is parallel to my front wall using sensors (IR2 & IR6)
{
  
  caliAlignment();
  caliDistance();

}







//Calibrite the distance to the front wall as 5cm using front sensors
void caliDistance()
{
  bool tried_front = false;
  bool tried_back = false;
  float dist = 4.9;
  float error = 0.4;

  float ir2reading, ir6reading;
  ir2reading = readIR2();
  ir6reading = readIR6();


    while( ( (abs(ir2reading - dist)> error)  || (abs(ir6reading- dist)> error) ) //first checking if there is a difference and there is a need to calibrate
           && not(tried_front && tried_back)){ //will stop when when IR reading is within error && both (tried_front & tried_back are true).

    if (ir2reading < dist || ir6reading < dist) // so if the distance from the front is < than 5cm, we move backward
    {
      moveWithSpeed(convertDistanceToTicks(0.2),   DIRECTION_BACKWARD, 200);
      ir2reading = readIR2();
    
      ir6reading = readIR6();
      tried_front = true;
    }
    else if (ir2reading > dist && ir6reading > dist) // so if the distannce front is > than 5 cm, we move forward
    {
      moveWithSpeed(convertDistanceToTicks(0.2),DIRECTION_FORWARD, 200);
      ir2reading = readIR2();
    
      ir6reading = readIR6();
      tried_back = true;
    }
  }
}

//Calibrite the alignment to front walls using front sensors
void caliAlignment(){


  bool tried_left = false;
  bool tried_right = false;
  
  float ir_diff = readIR2() - readIR6();
  

  //using Front left and Front right sensors
  while ((abs(ir_diff) > 0.2) && not(tried_left && tried_right))//gg to enter loop as long as there is a difference btw the 2 front sensors 
  {
    
    if (ir_diff < 0.3) //if my ir2 is closer to the wall, then we move on the left
    {
      //left adjustment
      moveWithSpeed(convertRightAngleToTicks(0.2), DIRECTION_RIGHT, 200);
      tried_left = true;
    }
    else if (ir_diff > 0.2) // if my ir6 is closer to the wall, then we move on the right
    {
      //right adjustment
      moveWithSpeed(convertLeftAngleToTicks(0.2), DIRECTION_LEFT, 200);
      tried_right = true;
    }
    ir_diff = readIR2() - readIR6();
  }


}

 //check if it is parallel to my left wall using my side sensors (IR1 & IR3)
void caliLeftAlignmnet(){

    bool tried_left = false;
  bool tried_right = false;

  
  float ir_diff = readIR1() - readIR3();

  // using Right front and right back sensors
  while (abs(ir_diff) > 0.2 && not(tried_left && tried_right))
  {

    //delay(10);

    if (ir_diff < 0.3) //if my ir1 is closer to the wall, then we move on the left
    {
      //left
      moveWithSpeed(convertRightAngleToTicks(0.2), DIRECTION_RIGHT, 200);
      tried_left = true;
    }
    else if (ir_diff > 0.2) //if my ir3 is closer to the wall, then we move on the right
    {
      //right
      moveWithSpeed(convertLeftAngleToTicks(0.2), DIRECTION_LEFT, 200);
      tried_right = true;
    }
    

    ir_diff = readIR1() - readIR3();
  }


}
void caliDistance1() //Using IR6
{
  bool tried_front = false;
  bool tried_back = false;
  float dist = 4.9;
  float error = 0.4;

  float ir6reading;
  ir6reading = readIR6();


    while( (abs(ir6reading- dist)> error) && not(tried_front && tried_back)){ //will stop when when IR reading is within error && both (tried_front & tried_back are true).

    if (ir6reading < dist) // so if the distance from the front is < than 5cm, we move backward
    {
      moveWithSpeed(convertDistanceToTicks(0.2),   DIRECTION_BACKWARD, 200);
   
      ir6reading = readIR6();
      tried_front = true;
    }
    else if (ir6reading > dist) // so if the distannce front is > than 5 cm, we move forward
    {
      moveWithSpeed(convertDistanceToTicks(0.2),DIRECTION_FORWARD, 200);
    
      ir6reading = readIR6();
      tried_back = true;
    }
  }
}

void caliDistance2() //Using IR5
{
  bool tried_front = false;
  bool tried_back = false;
  float dist = 4.9;
  float error = 0.4;

  float ir5reading;
  ir5reading = readIR5();

    while( ( (abs(ir5reading - dist)> error) ) //first checking if there is a difference and there is a need to calibrate
           && not(tried_front && tried_back)){ //will stop when when IR reading is within error && both (tried_front & tried_back are true).

    if (ir5reading < dist) // so if the distance from the front is < than 5cm, we move backward
    {
      moveWithSpeed(convertDistanceToTicks(0.2),   DIRECTION_BACKWARD, 200);
    
      ir5reading = readIR6();
      tried_front = true;
    }
    else if (ir5reading > dist) // so if the distannce front is > than 5 cm, we move forward
    {
      moveWithSpeed(convertDistanceToTicks(0.2),DIRECTION_FORWARD, 200);
    
      ir5reading = readIR6();
      tried_back = true;
    }
  }
}
void caliDistance3() //Using IR2
{
  bool tried_front = false;
  bool tried_back = false;
  float dist = 4.9;
  float error = 0.4;

  float ir2reading;
  ir2reading = readIR2();
  
    while( ( (abs(ir2reading - dist)> error)) //first checking if there is a difference and there is a need to calibrate
           && not(tried_front && tried_back)){ //will stop when when IR reading is within error && both (tried_front & tried_back are true).

    if (ir2reading < dist) // so if the distance from the front is < than 5cm, we move backward
    {
      moveWithSpeed(convertDistanceToTicks(0.2),   DIRECTION_BACKWARD, 200);
    
      ir2reading = readIR2();
      tried_front = true;
    }
    else if (ir2reading > dist) // so if the distannce front is > than 5 cm, we move forward
    {
      moveWithSpeed(convertDistanceToTicks(0.2),DIRECTION_FORWARD, 200);
    
      ir2reading = readIR6();
      tried_back = true;
    }
  }
}
