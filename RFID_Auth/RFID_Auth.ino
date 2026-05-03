#include <SPI.h>
#include <MFRC522.h>

const int GREEN = 4;
const int RED = 2;

const int BUZZER = 15;

#define SS_PIN 5
#define RST_PIN 22

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  playWarning();

  digitalWrite(GREEN, HIGH);
  delay(500);
  digitalWrite(GREEN, LOW);

  Serial.println("--- RFID Scanner Check ---");

  rfid.PCD_DumpVersionToSerial();
  Serial.println("Waiting for card scan...");
}

void loop() {

  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }


  Serial.print("\nCard Detected! UID:");
  String content = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    content.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(rfid.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println(content);


  if (content.substring(1) == "63 EB 7D 2F") {
    Serial.print("Access Granted!");
    playSuccess();

    delay(2000);
  } else {
    Serial.print("Access Denied!");
    playWarning();
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}


void playSuccess() {
  digitalWrite(GREEN, HIGH);
  digitalWrite(BUZZER, HIGH);
  delay(500);
  digitalWrite(BUZZER, LOW);
  delay(100);
  digitalWrite(GREEN, LOW);
}


void playWarning() {
  digitalWrite(RED, HIGH);
  for (int i = 0; i < 3; i++) {
    digitalWrite(RED, HIGH);
    digitalWrite(BUZZER, HIGH);
    delay(50);
    digitalWrite(RED, LOW);
    digitalWrite(BUZZER, LOW);
    delay(50);
  }
  digitalWrite(RED, LOW);
}

void blinkBoth() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, HIGH);
    delay(20);
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, LOW);
    delay(20);
  }
}

void customBlink(int ledPin, int times, int duration) {
  for (int i = 0; i < times; i++) {
    digitalWrite(ledPin, HIGH);
    delay(duration);
    digitalWrite(ledPin, LOW);
    delay(duration);
  }
}