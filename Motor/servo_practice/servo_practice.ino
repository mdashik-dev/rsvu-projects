#include <Servo.h>

const int trigger = 6;
const int ecopin = 7;


const int motorA1 = 11;
const int motorA2 = 12;


const int ServoPin = 9;

Servo myServo;



void setup() {

  myServo.attach(ServoPin);

  Serial.begin(115200);

  pinMode(trigger, OUTPUT);
  pinMode(ecopin, INPUT);

  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);


  myServo.write(65);
  delay(200);
  myServo.write(120);


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


// void LED_ON() {

//   digitalWrite(LED1, HIGH);
//   delay(40);
//   digitalWrite(LED1, LOW);
//   digitalWrite(LED2, HIGH);
//   delay(40);
//   digitalWrite(LED2, LOW);
//   digitalWrite(LED3, HIGH);
//   delay(40);
//   digitalWrite(LED3, LOW);
//   digitalWrite(LED4, HIGH);
//   delay(40);
//   digitalWrite(LED4, LOW);
//   digitalWrite(LED5, HIGH);
//   delay(40);
// }


void loop() {
  float distances = getDistance();

  Serial.print("Distance: ");
  Serial.print(distances);
  Serial.println(" cm");


  myServo.write(0);
  delay(200);
  myServo.write(120);



  if (distances > 20) {

    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);

  } else if (distances < 20 && distances > 5) {
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, HIGH);
  } else {
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, LOW);
  }


  // if (distances < 30) {
  //   Serial.print("testing...");
  //   LED_ON();
  // }
}