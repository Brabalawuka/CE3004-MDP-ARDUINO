int move(double ticks, const int direction[2], const bool slow) 
{
    resetGlobalConstants();
    double p = 0;
    double brakingOffset = 0;
    int startingOffset = 0;
    double base_speedL, base_speedR;
    if (slow == true)
    {
      base_speedL = SPEED_L_SLOW;
      base_speedR = SPEED_R_SLOW;
    }
    else
    {
      base_speedL = SPEED_L;
      base_speedR = SPEED_R;
    }

    while (m1Ticks <= ticks && m2Ticks <= ticks)
    {   
        p = computeP();

        double difference = ticks - m1Ticks;
        double speedL, speedR;
        
        if (startingOffset < min(base_speedL, base_speedR))
        {
          md.setSpeeds(startingOffset * direction[0], startingOffset * direction[1]);
          startingOffset += 10;
        }
        else if ( difference < 100) 
        {
          brakingOffset = difference / 100;
          speedL = (base_speedL + p)* brakingOffset * direction[0];
          speedR = (base_speedR - p)* brakingOffset * direction[1];
        } else {
          speedL = (base_speedL + p) * direction[0];
          speedR = (base_speedR - p) * direction[1];
        }
        md.setSpeeds(speedL , speedR);
    }
    md.setSpeeds(0,0);
    md.setBrakes(400, 400);
    delay(50);
    return 1;
}

int movewithfeedback(double ticks, const int direction[2]) 
{
    resetGlobalConstants();
    double p = 0;
    double brakingOffset = 0;
    int tick_increment = (int)round(convertDistanceToTicks(10));
    int tick_threshold = tick_increment;

    while (m1Ticks <= ticks)
    {   
        if (m1Ticks >= tick_threshold)
        {
          Serial.println("X"
                 + String(readIR4()) + ";"
                 + String(readIR6())
                );
          tick_threshold = tick_threshold + tick_increment;
        }
        
        p = computeP();

        double difference = tick_threshold - m1Ticks;
        double speedL, speedR;
        
        if ( difference < 80) {
          brakingOffset = (difference / 100) + 0.2;
          speedL = (SPEED_L + p)* brakingOffset * direction[0];
          speedR = (SPEED_R - p)* brakingOffset * direction[1];
        } else {
          speedL = (SPEED_L + p) * direction[0];
          speedR = (SPEED_R - p) * direction[1];
        }
        md.setSpeeds(speedL , speedR );
    }

    if ((m1Ticks % tick_increment) > (tick_increment/2.0))
    {
      // Have not sent sensor data for the last 10cm
      Serial.println("X"
             + String(readIR4()) + ";"
             + String(readIR6())
            );
    }
    
    md.setBrakes(400, 400);
    delay(50);
    return 1;
}


int movetillwall() 
{
    // Only used for fastest path 
    resetGlobalConstants();
    double p = 0;
    double threshold = 8;
    float ir1reading, ir3reading;

    while (true)
    {   
        p = computeP();
       
        md.setSpeeds((SPEED_L + p) * DIRECTION_FORWARD[0], (SPEED_R - p) * DIRECTION_FORWARD[1]);
        ir1reading = readIR1(); //taking reading
        ir3reading = readIR3(); //taking reading
        if(ir1reading < threshold){
          break;
        }
        else if(ir3reading < threshold){
          break;
        }
    }
    
    md.setBrakes(400, 400);
    delay(20);
    return 1;
}

int moveTillLeftEnd() 
{
    // Only used for exploration
    resetGlobalConstants();
    double p = 0;
    double threshold = 10;
    float ir4reading;
    
    while (true)
    {   
        p = computeP();
       
        md.setSpeeds((SPEED_L_SLOW + p) * DIRECTION_FORWARD[0], (SPEED_R_SLOW - p) * DIRECTION_FORWARD[1]);
        ir4reading = readIR4Cali(); //taking reading
        if(ir4reading > threshold){
          break;
        }
    }
    md.setBrakes(400, 400);
    delay(20);
    return 1;
}

int glideforwardtillwall_exp() 
{
    // Only used for exploration 
    resetGlobalConstants();
    double p = 0;
    double threshold = 8;
    double brakingOffset = 0;
    int tick_increment = (int)round(convertDistanceToTicks(10));
    int tick_threshold = tick_increment;
    float ir1reading, ir2reading, ir3reading;

    while (true)
    {   
        if (m1Ticks >= tick_threshold)
        {
          Serial.println("X"
                 + String(readIR4()) + ";"
                 + String(readIR6())
                );
          tick_threshold = tick_threshold + tick_increment;
        }
        
        p = computeir4P();

        double difference = tick_threshold - m1Ticks;
        double speedL, speedR;
        
        if ( difference < 80) {
          brakingOffset = (difference / 100) + 0.2;
          speedL = (SPEED_L + p)* brakingOffset * DIRECTION_FORWARD[0];
          speedR = (SPEED_R - p)* brakingOffset * DIRECTION_FORWARD[1];
        } else {
          speedL = (SPEED_L + p) * DIRECTION_FORWARD[0];
          speedR = (SPEED_R - p) * DIRECTION_FORWARD[1];
        }
        md.setSpeeds(speedL , speedR );
        
        ir1reading = readIR1(); //taking reading
        ir2reading = readIR2(); //taking reading
        ir3reading = readIR3(); //taking reading
        if(ir1reading < threshold){
          break;
        }
        else if(ir2reading < threshold){
          break;
        }
        else if(ir3reading < threshold){
          break;
        }
    }

    if ((m1Ticks % tick_increment) > (tick_increment/2.0))
    {
      // Have not sent sensor data for the last 10cm
      Serial.println("X"
             + String(readIR4()) + ";"
             + String(readIR6())
            );
    }
    
    md.setBrakes(400, 400);
    delay(20);
    return 1;
}

int glideforwardtillwall_fp() 
{
    // Only used for fastest path 
    resetGlobalConstants();
    double p = 0;
    double threshold = 8;
    float ir1reading, ir3reading;

    while (true)
    {   
        p = computeir4P();
       
        md.setSpeeds((SPEED_L + p) * DIRECTION_FORWARD[0], (SPEED_R - p) * DIRECTION_FORWARD[1]);
        ir1reading = readIR1(); //taking reading
        ir3reading = readIR3(); //taking reading
        if(ir1reading < threshold){
          break;
        }
        else if(ir3reading < threshold){
          break;
        }
    }
    
    md.setBrakes(400, 400);
    delay(20);
    return 1;
}

int glideforwarddistance(double ticks)
{
    // Only used for fastest path
    resetGlobalConstants();
    double p = 0;
    double brakingOffset = 0;

    while (m1Ticks <= ticks && m2Ticks <= ticks)
    {   
        p = computeir4P();

        double difference = ticks - m1Ticks;
        double speedL, speedR;
        if ( difference < 100) {
          brakingOffset = difference / 100;
          speedL = (SPEED_L + p)* brakingOffset * DIRECTION_FORWARD[0];
          speedR = (SPEED_R - p)* brakingOffset * DIRECTION_FORWARD[1];
        } else {
          speedL = (SPEED_L + p) * DIRECTION_FORWARD[0];
          speedR = (SPEED_R - p) * DIRECTION_FORWARD[1];
        }
        md.setSpeeds(speedL , speedR );
    }
    md.setBrakes(400, 400);
    delay(50);
    return 1;
}

int glidebackwarddistance(double ticks)
{
    // Only used for fastest path
    resetGlobalConstants();
    double p = 0;
    double brakingOffset = 0;

    while (m1Ticks <= ticks && m2Ticks <= ticks)
    {   
        p = computeir5P();

        double difference = ticks - m1Ticks;
        double speedLeft, speedRight, speedL, speedR;
        if ( difference < 100) {
          brakingOffset = difference / 100;
          speedL = (SPEED_L + p)* brakingOffset * DIRECTION_BACKWARD[0];
          speedR = (SPEED_R - p)* brakingOffset * DIRECTION_BACKWARD[1];
        } else {
          speedL = (SPEED_L + p) * DIRECTION_BACKWARD[0];
          speedR = (SPEED_R - p) * DIRECTION_BACKWARD[1];
        }
        md.setSpeeds(speedL , speedR );
    }
    md.setBrakes(400, 400);
    delay(50);
    return 1;
}
