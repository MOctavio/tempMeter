const int sensorPin = A0;

int sensorValue = 0;         // the sensor value
int sensorMax = 0;           // maximum sensor value
float baseLine = 0.0;        // temperature baseline

void setup() {  
  Serial.begin(9600);
  Serial.print("Establishing baseline temperature value.\n");
  
  for (int pin = 2; pin<=4; pin++){
    pinMode(pin,OUTPUT);
    digitalWrite(pin, LOW);
  }
  
  /* record the maximum sensor value
     during the first five seconds */
  while (millis() < 5000) {
    sensorValue = analogRead(sensorPin);
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }
  }
  
  // sets baseline temperature
  float voltage = (sensorValue/1024.0)*5.0;
  baseLine = (voltage - .5)*100;
  Serial.print("Baseline temperature set to ");
  Serial.print(baseLine);
  Serial.print("C\n\n");
}

void loop() {
  sensorValue = analogRead(sensorPin);
  Serial.print("Sensor value: ");
  Serial.print(sensorValue);

  float voltage = (sensorValue/1024.0)*5.0;
  Serial.print(", Volts: ");
  Serial.print(voltage);

  float temperature = (voltage - .5)*100;
  Serial.print(", Temprature : ");
  Serial.print(temperature);
  Serial.print("C\n");
  
  if (temperature <= baseLine){
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  }else if (temperature < baseLine+3){
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  }else if (temperature < baseLine+6){
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  }else {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
  }
  delay(1);
  
}

