

float average (int * array, int len)  // assuming array is int.
{
  long sum = 0L ;  // sum will be larger than an item, long for safety.
  for (int i = 0 ; i < len ; i++)
    sum += array [i] ;
  return  round(((float) sum) / len) ;  // average will be fractional, so float may be appropriate.
}

void loopSensorTest(){
  float arr[200] = {};
  float middle;
 int i;
  for(i=0; i<200; i++){
    arr[i] = analogRead(irR1);
  }
  middle = median(arr, 200);
  Serial.print("1: ");
  Serial.println(middle);

  for(i=0; i<200; i++){
    arr[i] = analogRead(irR2);
  }
  middle = median(arr, 200);
  Serial.print("2: ");
  Serial.println(middle);

  for(i=0; i<200; i++){
    arr[i] = analogRead(irR3);
  }
  middle = median(arr, 200);
  Serial.print("3: ");
  Serial.println(middle);


//  for(i=0; i<200; i++){
//    arr[i] = analogRead(irR4);
//  }
//  middle = median(arr, 200);
//  Serial.print("4: ");
//  Serial.println(middle);
//
//  for(i=0; i<200; i++){
//    arr[i] = analogRead(irR5);
//  }
//  middle = median(arr, 200);
//  Serial.print("5: ");
//  Serial.println(middle);
  

//  for(i=0; i<200; i++){
//    arr[i] = analogRead(irR6);
//  }
//  middle = median(arr, 200);
//  Serial.print("6: ");
//  Serial.println(middle);


  Serial.println();
  

  delay(1000);
  
  }
