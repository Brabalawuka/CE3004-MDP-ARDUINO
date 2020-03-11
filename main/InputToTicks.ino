// TODO: need to recalibrate this before every run
double convertDistanceToTicks(int distance) //10cm
{
  // calculation was made with the knowledge that one revolution of the wheel is 510 ticks, and the diameter of the wheel is 6cm.
  // https://www.robotc.net/wikiarchive/Tutorials/Arduino_Projects/Mobile_Robotics/VEX/Using_encoders_to_drive_some_distance
  double ticks = distance * (28.9 + distance/60 * 1);      //6.21v 28.8
  // double ticks = distance * 29 + distance*0.05*29;      //6.21v 28.8
  return ticks;
}

double convertDiagDistanceToTicks(int distance) //10cm
{
  // calculation was made with the knowledge that one revolution of the wheel is 510 ticks, and the diameter of the wheel is 6cm.
  // https://www.robotc.net/wikiarchive/Tutorials/Arduino_Projects/Mobile_Robotics/VEX/Using_encoders_to_drive_some_distance
  double ticks = distance * 1.41421 * (29 + distance* 1.41421/100 * 1);   
  return ticks;
}




double convertLeftAngleToTicks(int angle)
{
  double tick = angle * (4.38 + angle/360 * 0.1); // 6.21v 4.38
  return tick;
}

double convertRightAngleToTicks(int angle)
{
  double tick = angle * (4.37 + angle/360 * 0.1); // 6.21v 4.37
  return tick;
}
