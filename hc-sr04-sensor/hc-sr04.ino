const int trigger = 6;
const int ecopin = 7;

void setup() {
  Serial.begin(115200);

  pinMode(trigger, OUTPUT);
  pinMode(ecopin, INPUT);


  Serial.write("programme working :)");
}

float getDistance() {
  float time;
  float distance;
  digitalWrite(trigger, LOW);
  delay(20);
  digitalWrite(trigger, HIGH);
  delay(20);
  digitalWrite(trigger, LOW);

  time = pulseIn(ecopin, HIGH);
  distance = (0.034 * time) / 2;

  return distance;
}


void loop() {
  float distances = getDistance();

  Serial.print("Distance: ");
  Serial.print(distances);
  Serial.println(" cm");

  delay(200);
}
