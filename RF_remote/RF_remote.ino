int seqOn[] = {0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,1,1,0,1,1,1,0,0,0};
int seqOff[] = {0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,1,1,0,1,0,1,0,0,0};

//milliseconds

//pair = 0
unsigned long shortHigh = 100;
unsigned long longLow = 500;

//this pair = 1
unsigned long longHigh = 400;
unsigned long medLow = 200;

void setup() {
  // put your setup code here, to run once:
  pinMode(4,OUTPUT);
  Serial.begin(9600);
}

void pulse(unsigned long delay1, unsigned long delay2){
  digitalWrite(4,HIGH);
  delayMicroseconds(delay1);
  digitalWrite(4,LOW);
  delayMicroseconds(delay2);
}

void sendSignal(int sequence[]){
  for(int i = 0; i < 25; i++){
    if(sequence[i] == 0){
      pulse(shortHigh, longLow);
    } 
    else if(sequence[i] == 1){
      pulse(longHigh, medLow);
    }
  }
  //long delay in between signals
  delay(4.5);
}

void loop() {
  //sends signal 10 times
  for(int i = 0; i < 5; i++){
      sendSignal(seqOn);
  }

  delay(2000);
    for(int i = 0; i < 5; i++){
      sendSignal(seqOff);
  }
  delay(2000);
}
