int move(double ticks, const int direction[2]) 
{
    resetGlobalConstants();
    double pid = 0;
    double brakingOffset = 0;
    double startingOffset = 0;


    //md.setSpeeds((SPEED + pid) * direction[0]  , (SPEED - pid) * direction[1]);
    while (m1Ticks <= ticks)
    {   

        computeDelta();
        pid = computePID();

        double difference = ticks - m1Ticks;

        if (m1Ticks < 50){
          md.setSpeeds((SPEED - 150 + 3 * m1Ticks) * direction[0], (SPEED- 150 + 3 * m1Ticks) * direction[1]);
        } else if ( difference < 100) {
          brakingOffset = difference / 100;
          md.setSpeeds((SPEED + pid)* brakingOffset * direction[0], (SPEED - pid)* brakingOffset * direction[1]);
        } else {
          md.setSpeeds((SPEED + pid) * direction[0], (SPEED - pid) * direction[1]);
        }
           
//             Serial.println("printing number of ticks");       
//             Serial.println(m1Ticks);
//             Serial.println(m2Ticks);
    
    }
    md.setBrakes(400, 400);
 //    the number of ticks output here should be the same for each motor
//    Serial.print("#final m1ticks: ");
//    Serial.print(m1Ticks);
//    Serial.print(" #final m2ticks: ");
//    Serial.println(m2Ticks);

   // Serial.print("# final m2ticks after delay: ");
   // Serial.println(m2ticks);

//    Serial.print("#sum of deltaM1Ticks: ");
//    Serial.print(sumOfDeltaM1);
//    Serial.print("# sum of deltaM2Ticks: ");
//    Serial.println(sumOfDeltaM2);

    delay(10);

    return 1;
}


int moveWithSpeed(double ticks, const int direction[2], int speed) 
{
    resetGlobalConstants();
    double pid = 0;


    md.setSpeeds((speed + pid) * direction[0]  , (speed - pid) * direction[1]);
    while (m1Ticks <= ticks && Forward)
    {   

        computeDelta();
        pid = computePID();

        //Serial.println();       
    }
    md.setBrakes(400, 400);

    delay(10);

    return 1;
}



int moveTillEnd(const int direction[2]) 
{
    resetGlobalConstants();
    double pid = 0;
    double brakingOffset = 0;
    double startingOffset = 0;
    double dist = 8;
    float ir1reading, ir3reading;


    //md.setSpeeds((SPEED + pid) * direction[0]  , (SPEED - pid) * direction[1]);
    while (Forward)
    {   

        computeDelta();
        pid = computePID();
       

        if (m1Ticks < 30){
          md.setSpeeds((SPEED - 150 + 5 * m1Ticks) * direction[0], (SPEED- 150 + 5 * m1Ticks) * direction[1]);
        }  else {
          md.setSpeeds((SPEED + pid) * direction[0], (SPEED - pid) * direction[1]);
        }

         ir1reading = readIR1(); //taking reading
         ir3reading = readIR3(); //taking reading

         if(ir1reading < dist && ir3reading < dist){
          break;
         }

    }
    md.setBrakes(400, 400);
    delay(20);
    return 1;
}

int moveTillLeftEnd(const int direction[2], int speed) 
{
    resetGlobalConstants();
    double pid = 0;
    double brakingOffset = 0;
    double startingOffset = 0;
    double dist = 9;
    float ir4reading;


    //md.setSpeeds((speed + pid) * direction[0]  , (speed - pid) * direction[1]);
    while (true)
    {   
        computeDelta();
        pid = computePID();
       
        md.setSpeeds((speed + pid) * direction[0], (speed - pid) * direction[1]);
        ir4reading = readIR4(); //taking reading
        if(ir4reading > dist){
          break;
        }
    }
    md.setBrakes(400, 400);
    delay(20);
    return 1;
}




//int glideforward(double ticks, const int direction[2]) 
//{
//  
//    resetGlobalConstants();
//    double pid = 0;
//    double brakingOffset = 0;
//    double startingOffset = 0;
//    double dist = 9;
//    float ir1reading, ir3reading;
//
//     
//    ir1reading = readIR1Cali();
//    ir3reading = readIR3Cali();
//
//
//    //md.setSpeeds((SPEED + pid) * direction[0]  , (SPEED - pid) * direction[1]);
//    while (m1Ticks <= ticks)
//    {   
//
//        computeDelta();
//        pid = computePID();
//        double difference = ticks - m1Ticks;
//
//
//        if (m1Ticks < 50){
//          md.setSpeeds((SPEED - 150 + 3 * m1Ticks) * direction[0], (SPEED- 150 + 3 * m1Ticks) * direction[1]);
//        } else if ( difference < 100) {
//          brakingOffset = difference / 100;
//          md.setSpeeds((SPEED + pid)* brakingOffset * direction[0], (SPEED - pid)* brakingOffset * direction[1]);
//          //md.setBrakes(200, 200);
//        } else {
//          if (m1Ticks > 300 && abs(ir1reading-ir3reading) >= 0.4) 
//          {
//              if(ir3reading <5 || ir1reading<5) //need to move to the right, give more power to left motor
//                {
//                  md.setSpeeds((SPEED + pid + 10) * direction[0], (SPEED - pid - 10) * direction[1]);
//                
//                }
//                else if(  ir3reading>5 || ir1reading>5)//need to move to the left,
//                {
//                  md.setSpeeds((SPEED + pid - 10) * direction[0], (SPEED - pid + 10) * direction[1]);
//                }else { md.setSpeeds((SPEED + pid) * direction[0], (SPEED - pid) * direction[1]);}
//                
//          } else //when ticks are smaller than 300
//          {
//            md.setSpeeds((SPEED + pid) * direction[0], (SPEED - pid) * direction[1]);
//          }
//        }
//
//         ir1reading = readIR1Cali(); //taking reading
//         ir3reading = readIR3Cali(); //taking reading
//          
//         }
//   
//    md.setBrakes(400, 400);
//
//    delay(20);
//
//    return 1;
//}
//
//
//
//
//
//
//
//int diagnalAvoid(const int direction[2]){
//
//    resetGlobalConstants();
//    double pid = 0;
//    double brakingOffset = 0;
//    double startingOffset = 0;
//    double dist =17;
//    float ir5reading;
//  
//
//    //md.setSpeeds((SPEED + pid) * direction[0]  , (SPEED - pid) * direction[1]);
//    while (true)
//    {   
//
//        computeDelta();
//        pid = computePID();
//       
//
//        if (m1Ticks < 30){
//          md.setSpeeds((SPEED - 150 + 5 * m1Ticks) * direction[0], (SPEED- 150 + 3 * m1Ticks) * direction[1]);
//        }  else {
//          md.setSpeeds((SPEED + pid) * direction[0], (SPEED - pid) * direction[1]);
//        }
//
//         ir5reading = readIR5(); //taking reading
//        
//         if(ir5reading < dist){
//          break;
//         }
//      
//    
//    }
//    md.setBrakes(400, 400);
//
//    delay(20);
//
//    move(convertRightAngleToTicks(45), DIRECTION_RIGHT);
//    move(convertDiagDistanceToTicks(30),  DIRECTION_FORWARD);
//    move(convertLeftAngleToTicks(90), DIRECTION_LEFT);
//    move(convertDiagDistanceToTicks(30),  DIRECTION_FORWARD);
//    move(convertRightAngleToTicks(45), DIRECTION_RIGHT);
//    moveTillEnd(DIRECTION_FORWARD);
//
////    move(convertLeftAngleToTicks(45), DIRECTION_LEFT);
////    move(convertDiagDistanceToTicks(30),  DIRECTION_FORWARD);
////    move(convertRightAngleToTicks(90), DIRECTION_RIGHT);
////    move(convertDiagDistanceToTicks(30),  DIRECTION_FORWARD);
////    move(convertLeftAngleToTicks(45), DIRECTION_LEFT);
////    moveTillEnd(DIRECTION_FORWARD);
////    
//
//  
//  
//  }
