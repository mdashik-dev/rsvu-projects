const int trigger = 6;
const int ecopin = 7;

const int LED1 = 8;
const int LED2 = 9;
const int LED3 = 10;
const int LED4 = 11;
const int LED5 = 12;


void setup() {
  Serial.begin(115200);

  pinMode(trigger, OUTPUT);
  pinMode(ecopin, INPUT);


  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);



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


void LED_ON() {

  digitalWrite(LED1, HIGH);
  delay(40);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  delay(40);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, HIGH);
  delay(40);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, HIGH);
  delay(40);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, HIGH);
  delay(40);
}


void loop() {
  float distances = getDistance();

  Serial.print("Distance: ");
  Serial.print(distances);
  Serial.println(" cm");

  if (distances < 30) {
    Serial.print("testing...");
    LED_ON();
  }
}