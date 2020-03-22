// TODO: need to recalibrate this before every run
double convertDistanceToTicks(int distance) //10cm
{
  // calculation was made with the knowledge that one revolution of the wheel is 510 ticks, and the diameter of the wheel is 6cm.
  // https://www.robotc.net/wikiarchive/Tutorials/Arduino_Projects/Mobile_Robotics/VEX/Using_encoders_to_drive_some_distance
  double ticks = distance * (29.2 + distance/90);
  //double ticks = distance * (30.3 + distance/150);      //6.21v 28.8f
  // double ticks = distance * (28.7 + distance/100); 
  return ticks;
}

double convertDiagDistanceToTicks(int distance) //10cm
{
  // calculation was made with the knowledge that one revolution of the wheel is 510 ticks, and the diameter of the wheel is 6cm.
  // https://www.robotc.net/wikiarchive/Tutorials/Arduino_Projects/Mobile_Robotics/VEX/Using_encoders_to_drive_some_distance
  double ticks = distance * 1.41421 * (29.2 + distance* 1.41421/90 * 1);   
  return ticks;
}




double convertRightAngleToTicks(int angle) //convertLeftAngleToTicks(int angle) orginal statement
{
  if(angle == 45){
    return angle*4.40;
  }
   
  double tick = angle * (4.45 + angle/240 * 0.1); // 6.21v 4.38 
  return tick;
}

double convertLeftAngleToTicks(int angle) //convertRightAngleToTicks(int angle) original statement
{
  if(angle == 45){
    return angle*4.40;
  }
  double tick = angle * (4.470 + angle/240 * 0.1); // 6.21v 4.37
  return tick;
}
