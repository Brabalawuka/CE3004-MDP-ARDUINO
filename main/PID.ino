const double KP = 3;
const double KI = 3;
const double KD = 0.1;

double last_error_to_wall = 0;

double computeI() {   //Proportional only 
  double i, error;   
  error = m1Ticks - m2Ticks;
//  Serial.print("Error is ");
//  Serial.println(error);

  i = KI * error;

  //Return P that is within 50<-->-50range
  i = max(i, -50);
  i = min(i, 50);
  
  return i;
}

double computeir4P() {   //Proportional only, use ir4 as error
  double p,d,  error, ir4_KP, ir4_KD, pd; 
  ir4_KP = 15;  
  ir4_KD = 5;
  
  error = 5.0 - readIR4Cali();
  last_error_to_wall = error - last_error_to_wall; 

  p = ir4_KP * error;
  d = last_error_to_wall * ir4_KD;

  last_error_to_wall = error;

  pd = p + d;


  //Return P that is within 50<-->-50range
  pd = max(pd, -50);
  pd = min(pd, 50);
  
  return p;
}

double computeir5P() {   //Proportional only, use ir5 as error
  double p,d,  error, ir5_KP, ir5_KD, pd; 
  ir5_KP = 15;  
  ir5_KD = 10;
  error = 5.0 - readIR5Cali();
  last_error_to_wall = error - last_error_to_wall; 

  p = ir5_KP * error;
  d = last_error_to_wall * ir5_KD;

  last_error_to_wall = error;

  pd = p + d;
  
  //Return P that is within 50<-->-50range
  pd = max(pd, -50);
  pd = min(pd, 50);
  
  return pd;
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
  pid = max(pid, -50);
  pid = min(pid, 50);
  
  return p;

}
