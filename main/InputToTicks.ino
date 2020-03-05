// TODO: need to recalibrate this before every run
double convertDistanceToTicks(int distance) //10cm
{
  // calculation was made with the knowledge that one revolution of the wheel is 510 ticks, and the diameter of the wheel is 6cm.
  // https://www.robotc.net/wikiarchive/Tutorials/Arduino_Projects/Mobile_Robotics/VEX/Using_encoders_to_drive_some_distance
  double ticks = distance* 29.1;   //277 wk9:270      6.3vB2: 242
  return ticks;
}



double convertLeftAngleToTicks(int angle)
{
  double tick = angle *4.40 ; // 332-6.17VB2   6.3vB2: 332
  return tick;
}

double convertRightAngleToTicks(int angle)
{
  double tick = angle * 4.40; // 339 -6.17VB2     6.3vB2: 340
  return tick;
}
