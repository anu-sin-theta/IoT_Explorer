#include <Wire.h>
#include "FirebaseESP8266.h" // Anufied -- Arduino lib manager se download karna not works every time better to use my_zip file 
#include <ESP8266WiFi.h>

const byte ledPin = D3; // Pin number of the LED
const byte fanPin = D6;               

char FIREBASE_AUTH[] = "AIzaSyBfOFUAGrtd0s9KHIAx0h02GsrfBb1bBmU"; // Your Firebase Web API Key
char FIREBASE_HOST[] = "https://inventory-students-default-rtdb.asia-southeast1.firebasedatabase.app"; // Your Firebase URL
char WIFI_SSID[] = "Test";     // Your WIFI SSID
char WIFI_PASSWORD[] = "cisi4000"; // Your WIFI Password

FirebaseData firebaseData;

int lightStatus;
int fanStatus;

void setup() {
  Serial.begin(115200);
  
  pinMode(ledPin, OUTPUT);
  pinMode(fanPin, OUTPUT);  // Initialize pins

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.getInt(firebaseData, "/lightStatus")) {
    if (firebaseData.dataType() == "int") {
      lightStatus = firebaseData.intData();
      digitalWrite(ledPin, lightStatus ? HIGH : LOW);
      Serial.print("Light Status: ");
      Serial.println(lightStatus);
    } else {
      Serial.println("Error: lightStatus is not an int");
    }
  } else {
    Serial.println("Failed to get lightStatus");
    Serial.println(firebaseData.errorReason());
  }

  if (Firebase.getInt(firebaseData, "/FanStatus")) {
    if (firebaseData.dataType() == "int") {
      fanStatus = firebaseData.intData();
      digitalWrite(fanPin, fanStatus ? HIGH : LOW);
      Serial.print("Fan Status: ");
      Serial.println(fanStatus);
    } else {
      Serial.println("Error: FanStatus is not an int");
    }
  } else {
    Serial.println("Failed to get FanStatus");
    Serial.println(firebaseData.errorReason());
  }

  yield();
}
