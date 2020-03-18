/*
 * 
34 5 6
2[][][]
 [][][]
1[][][]

Short Sensor - 1,2,3,5,6
Long Sensor - 4

*/ 
float leftwall_ir45(){
    return abs(readIR4Cali()-readIR5Cali());
  }

float readIR1Cali() {
  float arr[20] = {};
  int i;
  for(i=0; i<20; i++){
    arr[i] = analogRead(irR1);
  }
  float middle = median(arr, 20);
  return (1/0.0000021192)/(middle +(0.008287/0.0000021192))-100 ;
}
float readIR2Cali() {
  float arr[20] = {};
  int i;
  for(i=0; i<20; i++){
    arr[i] = analogRead(irR2);
  }
  float middle = median(arr, 20);
  return (1/0.00000176336)/(middle +(0.008487/0.00000176336))-100 ;
}
float readIR3Cali() {
  float arr[20] = {};
  int i;
  for(i=0; i<20; i++){
    arr[i] = analogRead(irR3);
  }
  float middle = median(arr, 20);
  return (1/0.000087535)/(middle +(0.01759/0.000087535))-10 ;
}
float readIR4Cali() {
  float arr[20] = {};
  int i;
  for(i=0; i<20; i++){
    arr[i] = analogRead(irR4);
  }
  float middle = median(arr, 20);
  return (1/0.00027499)/(middle +(-0.02272112/0.00027499))-5;
}
float readIR5Cali() {
  float arr[20] = {};
  int i;
  for(i=0; i<20; i++){
    arr[i] = analogRead(irR5);
  }
  float middle = median(arr, 20);
  return (1/0.00002389)/(middle +(0.01843/0.00002389))-30;
}
  
float readIR6Cali() {
  float arr[20] = {};
  int i;
  for(i=0; i<20; i++){
    arr[i] = analogRead(irR6);
  }
  float middle = median(arr, 20);
  return (1/0.0002415)/(middle +(0.01831/0.00002415))-30;
}





float readIR1() {
  float arr[30] = {};
  int i;
  for(i=0; i<30; i++){
    arr[i] = analogRead(irR1);
  }
  float middle = median(arr, 30);
  return (1/0.00017375)/(middle +(-0.0026447/0.00017375))-5 ;
}


float readIR2() {
  float arr[30] = {};
  int i;
  for(i=0; i<30; i++){
    arr[i] = analogRead(irR2);
  }
  float middle = median(arr, 30);
  return (1/0.000172)/(middle +(0.004298/0.000172))- 4.5 ;
}

 
float readIR3() {
  float arr[30] = {};
  int i;
  for(i=0; i<30; i++){
    arr[i] = analogRead(irR3);
  }
  float middle = median(arr, 30);
  return (1/0.000233)/(middle +(-0.01309/0.000233))- 3.5 ;
}


float readIR4() {
  float arr[20] = {};
  int i;
  for(i=0; i<20; i++){
    arr[i] = analogRead(irR4);
  }
  float middle = median(arr, 20);
  if (middle >= 490){
    return (600 - middle)/10;
    }
  return (1/0.000213)/(middle +(-0.00443/0.000213))-6 ;
}

float readIR5() {
  float arr[30] = {};
  int i;
  for(i=0; i<30; i++){
    arr[i] = analogRead(irR5);
  }
  float middle = median(arr, 30);
  return (1/0.000265)/(middle +(-0.01166/0.000265))-5;
}

float readIR6() {
  float arr[30] = {};
  int i;
  for(i=0; i<30; i++){
    arr[i] = analogRead(irR6);
  }
  float middle = median(arr, 30);
  return (1/0.00004292)/(middle +(0.003483/0.00004292))-30 ;
}


void checkRawValuesCali (){

    Serial.println("X"+String(readIR1Cali())+";"
                      +String(readIR2Cali())+";"
                      +String(readIR3Cali())+";"
                      +String(readIR4Cali())+";"
                      +String(readIR5Cali())
                 );
  }


void checkRawValues (){

    Serial.println("X"+String(readIR1())+";"
                      +String(readIR2())+";"
                      +String(readIR3())+";"
                      +String(readIR4())+";"
                      +String(readIR5())+";"
                      +String(readIR6())
                 );

  }

//CheckList

//collects samples for ir Array
//void irSamples(int maxnum) {
//  for (int i = 0; i < maxnum; i++) {
//    irArr1[i] = analogRead(irR1);
//    irArr2[i] = readIR2();
//    irArr3[i] = readIR3();
//    irArr4[i] = readIR4();
//    irArr5[i] = readIR5();
//    irArr6[i] = readIR6();
//    delay(5);
//  }
//}
///////////////////////////////////////////////////////////////
/*Sorting*/

float median(float nums[], int n) {
  int k = n % 2 == 0 ? n / 2 : n / 2 + 1;
  return qselect(nums, 0, n - 1, k - 1);
}

float qselect(float A[], int start, int end, int k) {
  if (start == end) {
    return A[start];
  }

  int left = start, right = end;
  int index = (left + right) / 2;
  float pivot = A[index];

  while (left <= right) {
    while (left <= right && A[left] > pivot) {
      left++;
    }

    while (left <= right && A[right] < pivot) {
      right--;
    }

    if (left <= right) {
      float tmp = A[left];
      A[left] = A[right];
      A[right] = tmp;

      left++;
      right--;
    }
  }

  if (k >= start && k <= right) {
    return qselect(A, start, right, k);
  }
  if (k >= left && k <= end) {
    return qselect(A, left, end, k);
  }
  return A[right + 1];
}
