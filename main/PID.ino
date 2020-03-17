const double KP = 4;
const double KI = 2;
const double KD = 0.1;




double computePID() {   //Proportional, Integral,Derivative. 
// source: https://www.teachmemicro.com/arduino-pid-control-tutorial/
  double p, i, d, pid, error, integral;   //kp->proportional, ki->integral, kd->deriavative

  error = deltaM1Ticks - deltaM2Ticks; // originally was m1ticks - m2ticks, which is actually cumulative error (without taking into account time) because m1ticks and m2ticks are cumulative.
  cumError = m1Ticks - m2Ticks;
  Serial.println(error);

  p = KP * error;
  i = KI * cumError;
  d = KD * (error - lastError);


//  Serial.println("-----------");
//  Serial.println(p);
//  Serial.println(i);
//  Serial.println(d);
//  Serial.println("-----------");
  
  pid = i;
  
  lastError = error;


  //Return PID that is within 50<-->-50range
  if (pid >= 50){
    return 50;
    }
  else if (pid <= -50){
    return -50;
    }
  else{
    return pid;
    }

 
  
}
