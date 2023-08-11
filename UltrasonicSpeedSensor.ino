// 超声波测速仪
const int trig = 2;
const int echo = 3; 
const int red = 9; 
const int yellow = 10; 
const int green = 11; 
const float vSound = 33000.0 / 1000000.0; // speed of sound in cm/us
float prevDistanceCM = 200;
float currDistanceCM, speed;

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
}

void loop() {
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(red, LOW);

  currDistanceCM = measureDistance();
  speed = abs((prevDistanceCM - currDistanceCM) / 0.05);
  Serial.print(currDistanceCM);
  Serial.print(" , "); 
  Serial.println(speed);

  if (speed < 150){
    digitalWrite(green, HIGH);
  }else if (speed < 250){
    digitalWrite(yellow, HIGH);
  }else{
    digitalWrite(red, HIGH);
  }
  prevDistanceCM = currDistanceCM;
  delay(50); 
}

float measureDistance(){
  // Hold trigger for 10 microseconds, which sends ultrasound signal
  digitalWrite(trig, HIGH);
  delayMicroseconds(10); // delay 10 microseconds
  digitalWrite(trig, LOW);

  // Measure the length of echo signal, which is equal to the time needed for sound to go there and back.
  // pulseIn(pin, measure pulse time for HIGH or LOW signal, microseconds for waiting signal bouncing back)
  unsigned long durationMicroSec = pulseIn(echo, HIGH, 25000);

  float distanceCM = durationMicroSec * vSound / 2.0f;
  return distanceCM < 2 || distanceCM > 400 ? -1 : distanceCM;
}