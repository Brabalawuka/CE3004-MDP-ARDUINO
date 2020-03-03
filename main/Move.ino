int move(double ticks, const int direction[2]) 
{
    resetGlobalConstants();
    double pid = 0;
    double brakingOffset = 0;


    md.setSpeeds((SPEED + pid) * direction[0]  , (SPEED - pid) * direction[1]);
    while (m1Ticks <= ticks)
    {   

        computeDelta();
        pid = computePID();

       
        double difference = ticks - m1Ticks;
        if ( difference < 200) {
          brakingOffset = 2.5 * (120 - difference);
          md.setSpeeds((SPEED + pid - brakingOffset) * direction[0], (SPEED - pid - brakingOffset) * direction[1]);
        } else {
          md.setSpeeds((SPEED + pid) * direction[0], (SPEED - pid) * direction[1]);
        }

        

        
        md.setSpeeds((SPEED + pid) * direction[0], (SPEED - pid) * direction[1]);
            
//             Serial.println("printing number of ticks");
//             Serial.println(deltaM1Ticks);
//             Serial.println(m1Ticks);
//             Serial.println(m2Ticks);
        // delay(70);

        //delay(1);

        //Serial.println();       
    }
    md.setBrakes(400, 400);
 //    the number of ticks output here should be the same for each motor
//    Serial.print("#final m1ticks: ");
//    Serial.print(m1Ticks);
//    Serial.print(" #final m2ticks: ");
//    Serial.println(m2Ticks);

    //delay(200);
  
   // Serial.print("# final m2ticks after delay: ");
   // Serial.println(m2ticks);

//    Serial.print("#sum of deltaM1Ticks: ");
//    Serial.print(sumOfDeltaM1);
//    Serial.print("# sum of deltaM2Ticks: ");
//    Serial.println(sumOfDeltaM2);

    delay(50);

    return 1;
}


int moveWithSpeed(double ticks, const int direction[2], int speed) 
{
    resetGlobalConstants();
    double pid = 0;


    md.setSpeeds((speed + pid) * direction[0]  , (speed - pid) * direction[1]);
    while (m1Ticks <= ticks)
    {   

        computeDelta();
        pid = computePID();




        
            
//             Serial.println("printing number of ticks");
//             Serial.println(deltaM1Ticks);
//             Serial.println(m1Ticks);
//             Serial.println(m2Ticks);
        // delay(70);

        //delay(1);

        //Serial.println();       
    }
    md.setBrakes(400, 400);
 //    the number of ticks output here should be the same for each motor
//    Serial.print("#final m1ticks: ");
//    Serial.print(m1Ticks);
//    Serial.print(" #final m2ticks: ");
//    Serial.println(m2Ticks);

    //delay(200);
  
   // Serial.print("# final m2ticks after delay: ");
   // Serial.println(m2ticks);

//    Serial.print("#sum of deltaM1Ticks: ");
//    Serial.print(sumOfDeltaM1);
//    Serial.print("# sum of deltaM2Ticks: ");
//    Serial.println(sumOfDeltaM2);

    delay(50);

    return 1;
}
