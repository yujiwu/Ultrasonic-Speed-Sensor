const int trig = 2;
const int echo = 3; 
const float vSound = 33000.0 / 1000000.0; // speed of sound in cm/us
float distanceCM;

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  distanceCM = measureDistance();
  // print out the distance via serial
  Serial.println(distanceCM);
  delay(30); 

}

float measureDistance(){
  // Hold trigger for 10 microseconds, which sends ultrasound signal
  digitalWrite(trig, HIGH);
  delayMicroseconds(10); // delay 10 microseconds
  digitalWrite(trig, LOW);

  // Measure the length of echo signal, which is equal to the time needed for sound to go there and back.
  // pulseIn(pin, measure pulse time for HIGH or LOW signal, microseconds for waiting signal bouncing back)
  unsigned long durationMicroSec = pulseIn(echo, HIGH, 25000);

  distanceCM = durationMicroSec * vSound / 2.0f;
  return distanceCM < 2 || distanceCM > 400 ? -1 : distanceCM;
}