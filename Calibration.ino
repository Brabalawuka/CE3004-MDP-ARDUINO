void caliLeft()
{
  bool tried_left = false;
  bool tried_right = false;


  
  float ir_diff = readIR1() - readIR3();

  // using Right front and right back sensors
  while (abs(ir_diff) > 0.2 && not(tried_left && tried_right))
  {

    //delay(10);

    if (ir_diff < 0.3)
    {
      //left
      move(convertRightAngleToTicks(0.2), DIRECTION_RIGHT);
      tried_left = true;
    }
    else if (ir_diff > 0.2)
    {
      //right
      move(convertLeftAngleToTicks(0.2), DIRECTION_LEFT);
      tried_right = true;
    }
    

    ir_diff = readIR1() - readIR3();
  }
}

void caliDistance()
{
  bool tried_front = false;
  bool tried_back = false;
  float dist = 4.9;
  float error = 0.4;

  float ir2reading, ir5reading, ir6reading;
  ir2reading = readIR2();
  ir5reading = readIR5();
  ir6reading = readIR6();


    while( ( (abs(ir2reading - dist)> error) || (abs(ir5reading- dist)> error) || (abs(ir6reading- dist)> error) ) 
           && not(tried_front && tried_back)){

    if (ir2reading < dist || ir5reading < dist || ir6reading < dist)
    {
      move(convertDistanceToTicks(0.2),   DIRECTION_BACKWARD);
      ir2reading = readIR2();
      ir5reading = readIR5();
      ir6reading = readIR6();
      tried_front = true;
    }
    else if (ir2reading > dist && ir5reading > dist && ir6reading > dist)
    {
      move(convertDistanceToTicks(0.2),DIRECTION_FORWARD);
      ir2reading = readIR2();
      ir5reading = readIR5();
      ir6reading = readIR6();
      tried_back = true;
    }
  }
}

void caliCorner()
{
  caliDistance();
  caliLeft();
  Serial.println("cali:test");
  move(convertRightAngleToTicks(90), DIRECTION_RIGHT); //rotate left
  Serial.println("cali:test2");
  caliFront();
  move(convertLeftAngleToTicks(90), DIRECTION_LEFT); //rotate right
  caliDistance();
  caliLeft();
 
  Serial.println("cali:done");
}

void initCali()
{
  move(convertRightAngleToTicks(90), DIRECTION_RIGHT); //left
  caliCorner();
  caliLeft();
  move(convertLeftAngleToTicks(90), DIRECTION_LEFT);
  caliLeft();

  
}

void caliFront()
{
  
  
  bool tried_left = false;
  bool tried_right = false;
  
  float ir_diff = readIR2() - readIR6();
  

  //using Front left and Front right sensors
  while ((abs(ir_diff) > 0.2) && not(tried_left && tried_right))
  {
    
    if (ir_diff < 0.3)
    {
      //left adjustment
      move(convertRightAngleToTicks(0.2), DIRECTION_RIGHT);
      tried_left = true;
    }
    else if (ir_diff > 0.2)
    {
      //right adjustment
      move(convertLeftAngleToTicks(0.2), DIRECTION_LEFT);
      tried_right = true;
    }
    ir_diff = readIR2() - readIR6();
  }


   caliDistance();
}
