#include <WiFi.h>
#include <SPI.h>
#include <MFRC522.h>

#define PIEZO_PIN 21         // Digital pin for piezoelectric sensor
#define THRESHOLD 100         // Threshold value for detecting an intrusion
#define RST_PIN 2             // Digital pin for MFRC522 RST
#define SDA_PIN 4             // Digital pin for MFRC522 SDA
#define SCK_PIN 5             // Digital pin for MFRC522 SCK
#define MOSI_PIN 18           // Digital pin for MFRC522 MOSI
#define MISO_PIN 19           // Digital pin for MFRC522 MISO
#define TRIGGER_WEBCAM "trigger_webcam"  // Trigger message for Python script

const char* ssid = "Appu";
const char* password = "password";

MFRC522 mfrc522(RST_PIN);   // Create MFRC522 instance.

void setup() {
  Serial.begin(9600);
  pinMode(PIEZO_PIN, INPUT);
  pinMode(RST_PIN, OUTPUT);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, SDA_PIN); // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
  Serial.println("RFID Reader Initialized");
  Serial.println("Place your tag near the reader...");
}

void loop() {
  // Check for intruder
  int piezoReading = digitalRead(PIEZO_PIN);
  if (piezoReading > THRESHOLD) {
    Serial.println("Intruder Detected!");

    // Send signal to trigger Python script
    Serial.println(TRIGGER_WEBCAM);

    // Wait for a while to avoid multiple triggers
    delay(5000);
  }

  // Look for new cards
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Show UID on serial monitor
    Serial.print("Tag UID: ");
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println();

    // Compare with authorized tag UID (replace with your authorized tag UID)
    byte authorizedUID[4] = {0xA3, 0xEF, 0x09, 0x0E}; // Replace with your actual tag UID
    bool accessGranted = true;
    for (int i = 0; i < 4; i++) {
      if (mfrc522.uid.uidByte[i] != authorizedUID[i]) {
        accessGranted = false;
        break;
      }
    }

    if (accessGranted) {
      Serial.println("Access Granted!");
    } else {
      Serial.println("Access Denied!");
    }

    delay(1000); // Wait a bit before reading the next card
  }
}
