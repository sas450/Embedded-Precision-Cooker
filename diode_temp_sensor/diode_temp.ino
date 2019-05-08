float ambient = 27.00;


const float DC_Analog_Conversion = 5000.0/ 1023;
float ambientVd = 0;  //voltage drop at ambient temperature
int diodeAnodePin = 14;

void setup() {
  // put your setup code here, to run once:
  pinMode(diodeAnodePin,INPUT_PULLUP);
  Serial.begin(9600);
  ambientVd = analogRead(diodeAnodePin) * DC_Analog_Conversion;  //gets forward voltage at current temperature from pin 30
  
}

float getAvgTemp(){
  float avgTemp = 0; 
  for(int i = 0; i < 1000; i++){
    float currentVd = analogRead(diodeAnodePin) * DC_Analog_Conversion;  //current voltage drop at temperature
    float difference = currentVd - ambientVd;                            //difference between voltage drops
    float temp = ambient - (difference * .454545);            //.4545 Celcius / 1 mV
    temp = (1.8 * temp) + 32;
    avgTemp += temp;
  }
  return avgTemp/1000.0;
}

void loop() {

  Serial.println(getAvgTemp());
 
}
