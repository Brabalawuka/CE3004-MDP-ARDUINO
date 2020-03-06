/*
Control command send to serial port:

prefix: 'f' -> move forward
        'b' -> move backward
        'l' -> trun left
        'r' -> turn right

siffix: distance in cm or degreee in °


eg,
      f100 -> move forward 100cm
      b40  -> move back 40cm
      l70  -> turn left 70°
      r60  -> turn right 60°

*/




char cmd ='#';
String inString = "";  // string to hold input
int distance = 0;


//Direction Information
//const int DIRECTION_FORWARD[2] = {1, -1};
//const int DIRECTION_BACKWARD[2] = {-1, 1};
//const int DIRECTION_LEFT[2] = {1, 1};
//const int DIRECTION_RIGHT[2] = {-1, -1};


void loopReading(){

  
  
  while (Serial.available() > 0) {
    if (cmd != '#'){
      int inChar = Serial.read();
      if (isDigit(inChar)) {
        // convert the incoming byte to a char and add it to the string:
        inString += (char)inChar;
      }
      // if you get a newline, print the string, then the string's value:
      if (inChar == '\n') {

        Serial.print("Value:");
        Serial.println(inString.toInt());
        distance = inString.toInt();
        switch(cmd){
          case 'f':{
            move(convertDistanceToTicks(distance),  DIRECTION_FORWARD);
            //moveWithSpeed(convertDistanceToTicks(distance),  DIRECTION_FORWARD, 150);

            Serial.println("Xdone");
            break;
          }
          case 'b':{
            move(convertDistanceToTicks(distance),   DIRECTION_BACKWARD);
            Serial.println("Xdone");
            
            break;
          }
          case 'l':{
            move(convertLeftAngleToTicks(distance), DIRECTION_LEFT);
            Serial.println("Xdone");
            
            break;
          }
          case 'r':{
            move(convertRightAngleToTicks(distance), DIRECTION_RIGHT);
            Serial.println("Xdone");
            
            break;
          }

          case 's':{
            checkRawValues ();
           

            break;
          }
          
          case 'm':{
            checkRawValuesCali ();
          
            break;
          }


          case 'k':{
            navObs(convertDistanceToTicks(100),DIRECTION_FORWARD);
             Serial.println("Xdone");
            
            break;
          }

          case 'i':{
             caliFrontLeft();
             Serial.println("Xdone");
            
            break;
          }

          case 'o':{
            caliFront();
            Serial.println("Xdone");
            
            break;
          }

          case 'p':{
            caliLeft();
             Serial.println("Xdone");
            
            break;
          }

          case 'u':{
            caliLeftBack();
             Serial.println("Xdone");
            
            break;
          }
          case 'n':{
            caliNew();
             Serial.println("Xdone");
            
            break;
          }
          case 'e':{
            caliEdge();
             Serial.println("Xdone");
            
            break;
          }
          case 'x':{
            caliForwardtoWall();
             Serial.println("Xdone");
            
            break;
          }
          case 'g':{
            fx_glide(convertDistanceToTicks(100),300);

            break;
          }
        }
       
        // clear the string for new input:
        cmd ='#';
        inString = "";  // string to hold input
        distance = 0;
        
      }
    }
    else {
      cmd = (char)Serial.read();
      
     
    }
    
  }
  Serial.flush();
  
  
}
