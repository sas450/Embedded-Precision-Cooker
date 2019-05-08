//PIN ASSIGNMENTS

//HOOK UP DIODE ANODE TO PIN 14
//HOOK UP RF DATA to PIN 13
int RF_Data_pin = 13;
int diodeAnodePin = 14;

//Byte Sequence to turn On/Off the remote switch
int seqOn[] = {0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,1,1,0,1,1,1,0,0,0};
int seqOff[] = {0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,1,1,0,1,0,1,0,0,0};

//milliseconds

//shortHigh followed by a longLow = 0
unsigned long shortHigh = 100;
unsigned long longLow = 500;

//longHigh followed by a medium low = a 1;
unsigned long longHigh = 400;
unsigned long medLow = 200;

//Ambient temp
float ambient = 27.00;

//constants
const float DC_Analog_Conversion = 5000.0/ 1023;
float ambientVd = 0;  //voltage drop at ambient temperature

void setup() {
  // assigning pins to output/input
  pinMode(RF_Data_pin,OUTPUT);
  pinMode(diodeAnodePin,INPUT_PULLUP);

  Serial.begin(9600);

  //gets intial Voltage drop at ambient temperature
  ambientVd = analogRead(diodeAnodePin) * DC_Analog_Conversion;
}

//pulse function for RF remote
void pulse(unsigned long delay1, unsigned long delay2){
  digitalWrite(RF_Data_pin,HIGH);
  delayMicroseconds(delay1);
  digitalWrite(RF_Data_pin,LOW);
  delayMicroseconds(delay2);
}

//step through each bit in the sequence if its a 0 or 1 send the corresponding pulse
//outer most loop controls how many signals are sent, redunancy increases chance it will be success
void sendSignal(int sequence[], int numSignals){
  for(int i = 0; i < numSignals; i++){
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
}

//gets average temperature over 100 cycles
float getAvgTemp(){
  float avgTemp = 0; 
  for(int i = 0; i < 100; i++){
    float currentVd = analogRead(diodeAnodePin) * DC_Analog_Conversion;  //current voltage drop at temperature
    float difference = currentVd - ambientVd;                            //difference between voltage drops
    float temp = ambient - (difference * .454545);            //.4545 Celcius / 1 mV
    temp = (1.8 * temp) + 32;
    avgTemp += temp;
  }
  return avgTemp/100.0;
}


void loop() {
  Serial.println(getAvgTemp());
  
  //main control structure 
  if(getAvgTemp() > 90.0) {
    sendSignal(seqOff,5);
  } 
  else if(getAvgTemp() < 90.0 && getAvgTemp() > 83.0){
    sendSignal(seqOn,5);
  } 

}
