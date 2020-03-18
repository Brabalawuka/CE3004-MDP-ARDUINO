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
  return 7639.679695/middle-8.13793942;
}
float readIR2Cali() {
  float arr[20] = {};
  int i;
  for(i=0; i<20; i++){
    arr[i] = analogRead(irR2);
  }
  float middle = median(arr, 20);
  return 7245.370852/middle-7.459382 ;
}
float readIR3Cali() {
  float arr[20] = {};
  int i;
  for(i=0; i<20; i++){
    arr[i] = analogRead(irR3);
  }
  float middle = median(arr, 20);
  return  6396.729152/middle-6.4674028 ;
}
float readIR4Cali() {
  float arr[20] = {};
  int i;
  for(i=0; i<20; i++){
    arr[i] = analogRead(irR4);
  }
  float middle = median(arr, 20);
  return  5408.017484/middle-7.055727513;
}
float readIR5Cali() {
  float arr[20] = {};
  int i;
  for(i=0; i<20; i++){
    arr[i] = analogRead(irR5);
  }
  float middle = median(arr, 20);
  return 5163.974847/middle-7.272009122;
}
  
float readIR6Cali() {
  float arr[20] = {};
  int i;
  for(i=0; i<20; i++){
    arr[i] = analogRead(irR6);
  }
  float middle = median(arr, 20);
  return 6506.84523/middle-6.2879815;
}





float readIR1() {
  float arr[30] = {};
  int i;
  for(i=0; i<30; i++){
    arr[i] = analogRead(irR1);
  }
  float middle = median(arr, 30);
  return 6506.84523/middle-6.2879815 ;
}


float readIR2() {
  float arr[30] = {};
  int i;
  for(i=0; i<30; i++){
    arr[i] = analogRead(irR2);
  }
  float middle = median(arr, 30);
  return  4503.673/middle-1.7623;
}

 
float readIR3() {
  float arr[30] = {};
  int i;
  for(i=0; i<30; i++){
    arr[i] = analogRead(irR3);
  }
  float middle = median(arr, 30);
  return 7086.289029/middle-8.76717515 ;
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
  return 5736.875018/middle-8.173388232 ;
}

float readIR5() {
  float arr[30] = {};
  int i;
  for(i=0; i<30; i++){
    arr[i] = analogRead(irR5);
  }
  float middle = median(arr, 30);
  return 6222.375402/middle-10.97077133
;
}

float readIR6() {
  float arr[30] = {};
  int i;
  for(i=0; i<30; i++){
    arr[i] = analogRead(irR6);
  }
  float middle = median(arr, 30);
  if(middle < 470)
    return 13208.4563/middle-13.22363189;
  else
    return 23580.59709/middle-34.96770086;

;
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
