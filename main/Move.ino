int move(double ticks, const int direction[2], const bool slow) 
{
    resetGlobalConstants();
    double i = 0;
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
        i = computeI();

        double difference = ticks - m1Ticks;
        double speedL, speedR;
        
        if (startingOffset < min(base_speedL, base_speedR) && !slow)
        {
          md.setSpeeds(startingOffset * direction[0], startingOffset * direction[1]);
          startingOffset += 10;
        }
        else if ( difference < 100 && !slow) 
        {
          brakingOffset = difference / 125 + 0.2;
          speedL = (base_speedL * brakingOffset + i + 7) * direction[0];
          speedR = (base_speedR * brakingOffset - i) * direction[1];
          md.setSpeeds(speedL , speedR);
        } else {
          speedL = (base_speedL + i + 7) * direction[0];
          speedR = (base_speedR - i) * direction[1];
          md.setSpeeds(speedL , speedR);
        }
        
//        Serial.print("M1Ticks:");
//        Serial.print(m1Ticks);
//        Serial.print(" M2Ticks:");
//        Serial.println(m2Ticks);
        
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
    int tick_increment = 303;
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
        
        if ( difference < 100) {
          brakingOffset = difference / 125 + 0.2;
          speedL = (SPEED_L * brakingOffset + p + 7) * direction[0];
          speedR = (SPEED_R * brakingOffset - p) * direction[1];
        } else {
          speedL = (SPEED_L + p + 7) * direction[0];
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

int moveWithSpeed(double ticks, const int direction[2], int setSpeed) 
{
    resetGlobalConstants();
    double p = 0;
    double brakingOffset = 0;
    int startingOffset = 0;
    double speedL, speedR;

    while (m1Ticks <= ticks && m2Ticks <= ticks)
    {   
        p = computeP();

        double difference = ticks - m1Ticks;
        
        if (startingOffset < min(setSpeed, setSpeed))
        {
          md.setSpeeds(startingOffset * direction[0], startingOffset * direction[1]);
          startingOffset += 10;
        }
        else if ( difference < 100) 
        {
          brakingOffset = difference / 125 + 0.2;
          speedL = (setSpeed * brakingOffset + p + 7) * direction[0];
          speedR = (setSpeed * brakingOffset - p) * direction[1];
          md.setSpeeds(speedL , speedR);
        } else {
          speedL = (setSpeed + p + 7) * direction[0];
          speedR = (setSpeed - p) * direction[1];
          md.setSpeeds(speedL , speedR);
        }
        
    }
    md.setSpeeds(0,0);
    md.setBrakes(400, 400);
    delay(50);
    return 1;
}



int movetillwall(bool faster) 
{
    double moveSpeed;
    if (faster)
      moveSpeed = 360;
    else moveSpeed = SPEED_L;
    // Only used for fastest path 
    resetGlobalConstants();
    double p = 0;
    double threshold = 8;
    float ir1reading, ir3reading;

    while (true)
    {   
        p = computeP();
       
        md.setSpeeds((moveSpeed + p + 7) * DIRECTION_FORWARD[0], (moveSpeed - p) * DIRECTION_FORWARD[1]);
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
       
        md.setSpeeds((SPEED_L_SLOW + p + 7) * DIRECTION_FORWARD[0], (SPEED_R_SLOW - p) * DIRECTION_FORWARD[1]);
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
    double threshold = 7;
    double brakingOffset = 0;
    int tick_increment = 301;
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
        
        if ( difference < 120) {
          brakingOffset = (difference / 120);
          speedL = (SPEED_L * brakingOffset + p + 7) * DIRECTION_FORWARD[0];
          speedR = (SPEED_R * brakingOffset - p) * DIRECTION_FORWARD[1];
        } else {
          speedL = (SPEED_L + p + 7) * DIRECTION_FORWARD[0];
          speedR = (SPEED_R - p) * DIRECTION_FORWARD[1];
        }
        md.setSpeeds(speedL , speedR );
        
        ir1reading = readIR1(); //taking reading
        ir2reading = readIR2(); //taking reading
        ir3reading = readIR3(); //taking reading
        if(ir1reading < threshold || ir2reading < threshold ||(ir3reading < threshold && ir3reading > 0)){
          if (m1Ticks >= tick_threshold)
          {
            Serial.println("X"
                   + String(readIR4()) + ";"
                   + String(readIR6())
                  );
          }
          break;
        }

    }
    Serial.println(m1Ticks);
    md.setBrakes(400, 400);
    if ((m1Ticks % tick_increment) > (tick_increment * 0.7))
    {
      // Have not sent sensor data for the last 10cm
     
      Serial.println("X"
             + String(readIR4()) + ";"
             + String(readIR6())
            );
    }
     
    
    delay(20);
    return 1;
}

int glideforwardtillwall_exp_faster(int speed) 
{
    // Only used for exploration 
    resetGlobalConstants();
    double p = 0;
    double threshold = 7;
    double brakingOffset = 0;
    int tick_increment = 300;
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
        
        if ( difference < 120) {
          brakingOffset = (difference / 120);
          speedL = (speed * brakingOffset + p + 7) * DIRECTION_FORWARD[0];
          speedR = (speed * brakingOffset - p) * DIRECTION_FORWARD[1];
        } else {
          speedL = (speed + p + 7) * DIRECTION_FORWARD[0];
          speedR = (speed - p) * DIRECTION_FORWARD[1];
        }
        md.setSpeeds(speedL , speedR );
        
        ir1reading = readIR1(); //taking reading
        ir2reading = readIR2(); //taking reading
        ir3reading = readIR3(); //taking reading
        if(ir1reading < threshold || ir2reading < threshold ||(ir3reading < threshold && ir3reading > 0)){
          if (m1Ticks >= tick_threshold)
          {
            Serial.println("X"
                   + String(readIR4()) + ";"
                   + String(readIR6())
                  );
          }
          break;
        }

    }
    Serial.println(m1Ticks);
    md.setBrakes(400, 400);
    if ((m1Ticks % tick_increment) > (tick_increment * 0.7))
    {
      // Have not sent sensor data for the last 10cm
     
      Serial.println("X"
             + String(readIR4()) + ";"
             + String(readIR6())
            );
    }
     
    
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
       
        md.setSpeeds((SPEED_L + p + 7) * DIRECTION_FORWARD[0], (SPEED_R - p) * DIRECTION_FORWARD[1]);
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

int glideforwardtillwall_fp_faster(int speed) 
{
    // Only used for fastest path 
    resetGlobalConstants();
    double p = 0;
    double threshold = 8;
    float ir1reading, ir3reading;

    while (true)
    {   
        p = computeir4P();
       
        md.setSpeeds((speed + p + 7) * DIRECTION_FORWARD[0], (speed - p) * DIRECTION_FORWARD[1]);
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
          brakingOffset = difference / 125 + 0.2;
          speedL = (SPEED_L * brakingOffset + p + 7) * DIRECTION_FORWARD[0];
          speedR = (SPEED_R * brakingOffset - p) * DIRECTION_FORWARD[1];
        } else {
          speedL = (SPEED_L + p + 7) * DIRECTION_FORWARD[0];
          speedR = (SPEED_R - p) * DIRECTION_FORWARD[1];
        }
        md.setSpeeds(speedL , speedR );
    }
    md.setBrakes(400, 400);
    delay(50);
    return 1;
}

int glideforwarddistance_faster(double ticks, int speed)
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
          brakingOffset = difference / 125 + 0.2;
          speedL = (speed * brakingOffset + p + 7) * DIRECTION_FORWARD[0];
          speedR = (speed * brakingOffset - p) * DIRECTION_FORWARD[1];
        } else {
          speedL = (speed + p + 7) * DIRECTION_FORWARD[0];
          speedR = (speed - p) * DIRECTION_FORWARD[1];
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
          brakingOffset = difference / 125 + 0.2;
          speedL = (SPEED_L * brakingOffset + p + 7) * DIRECTION_BACKWARD[0];
          speedR = (SPEED_R * brakingOffset - p) * DIRECTION_BACKWARD[1];
        } else {
          speedL = (SPEED_L + p + 7) * DIRECTION_BACKWARD[0];
          speedR = (SPEED_R - p) * DIRECTION_BACKWARD[1];
        }
        md.setSpeeds(speedL , speedR );
    }
    md.setBrakes(400, 400);
    delay(50);
    return 1;
}


int glidebackwarddistance_faster(double ticks, int speed)
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
          brakingOffset = difference / 125 + 0.2;
          speedL = (speed * brakingOffset + p + 7) * DIRECTION_BACKWARD[0];
          speedR = (speed * brakingOffset - p) * DIRECTION_BACKWARD[1];
        } else {
          speedL = (speed + p + 7) * DIRECTION_BACKWARD[0];
          speedR = (speed - p) * DIRECTION_BACKWARD[1];
        }
        md.setSpeeds(speedL , speedR );
    }
    md.setBrakes(400, 400);
    delay(50);
    return 1;
}
