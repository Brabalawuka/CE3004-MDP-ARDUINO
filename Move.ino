int move(double ticks, const int direction[2]) 
{
    resetGlobalConstants();
    double pid = 0;


    md.setSpeeds((SPEED + pid) * direction[0]  , (SPEED - pid) * direction[1]);
    while (m1Ticks <= ticks)
    {   

        computeDelta();
        pid = computePID();

        
        md.setSpeeds((SPEED + pid) * direction[0], (SPEED - pid) * direction[1]);
            
//             Serial.println("printing number of ticks");
//             Serial.println(deltaM1Ticks);
//             Serial.println(m1Ticks);
//             Serial.println(m2Ticks);
        // delay(70);

        //delay(2);

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
