// TODO: need to recalibrate this before every run
double convertDistanceToTicks(int distance) //10cm
{
  // calculation was made with the knowledge that one revolution of the wheel is 510 ticks, and the diameter of the wheel is 6cm.
  // https://www.robotc.net/wikiarchive/Tutorials/Arduino_Projects/Mobile_Robotics/VEX/Using_encoders_to_drive_some_distance
  double ticks = distance * (29.4 + distance/150);
  //double ticks = distance * (30.3 + distance/150);      //6.21v 28.8f
  // double ticks = distance * (28.7 + distance/100); 
  return ticks;
}

double convertDiagDistanceToTicks(int distance) //10cm
{
  // calculation was made with the knowledge that one revolution of the wheel is 510 ticks, and the diameter of the wheel is 6cm.
  // https://www.robotc.net/wikiarchive/Tutorials/Arduino_Projects/Mobile_Robotics/VEX/Using_encoders_to_drive_some_distance
  double ticks = distance * 1.41421 * (29.5 + distance* 1.41421/150 * 1);   
  return ticks;
}




double convertRightAngleToTicks(int angle) //convertLeftAngleToTicks(int angle) orginal statement
{
  double tick = angle * (4.46 + angle/360 * 0.1); // 6.21v 4.38 
  return tick;
}

double convertLeftAngleToTicks(int angle) //convertRightAngleToTicks(int angle) original statement
{
  double tick = angle * (4.46 + angle/360 * 0.1); // 6.21v 4.37
  return tick;
}
