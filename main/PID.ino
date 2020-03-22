const double KP = 5;
const double KI = 3;
const double KD = 0.1;

double computeP() {   //Proportional only 
  double p, error;   
  error = m1Ticks - m2Ticks;

  p = KP * error;

  //Return P that is within 50<-->-50range
  p = max(p, -50);
  p = min(p, 50);
  
  return p;
}

double computeir4P() {   //Proportional only, use ir4 as error
  double p, error, ir4_KP; 
  ir4_KP = 20;  
  error = 5.0 - readIR4Cali();

  p = ir4_KP * error;

  //Return P that is within 50<-->-50range
  p = max(p, -50);
  p = min(p, 50);
  
  return p;
}

double computeir5P() {   //Proportional only, use ir5 as error
  double p, error, ir5_KP; 
  ir5_KP = 20;  
  error = 5.0 - readIR5Cali();

  p = ir5_KP * error;

  //Return P that is within 50<-->-50range
  p = max(p, -50);
  p = min(p, 50);
  
  return p;
}




double computePID() {   //Proportional, Integral,Derivative. 
// source: https://www.teachmemicro.com/arduino-pid-control-tutorial/
  double p, i, d, pid, error, integral;   //kp->proportional, ki->integral, kd->deriavative

  error = deltaM1Ticks - deltaM2Ticks; // originally was m1ticks - m2ticks, which is actually cumulative error (without taking into account time) because m1ticks and m2ticks are cumulative.
  cumError = m1Ticks - m2Ticks;
  //Serial.println(error);

  p = KP * error;
  i = KI * cumError;
  d = KD * (error - lastError);


//  Serial.println("-----------");
//  Serial.println(p);
//  Serial.println(i);
//  Serial.println(d);
//  Serial.println("-----------");
  
  pid = p + i;
  
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
