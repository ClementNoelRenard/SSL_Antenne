#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define PIN_CE 9
#define PIN_CSN 10

RF24 radio(PIN_CE, PIN_CSN);
int receivedData;

void setup() {
  radio.begin();
  radio.openReadingPipe(1, 0xF0F0F0F0E1LL); // ID unique pour l'émetteur
  radio.startListening();
  Serial.begin(9600);
}

void loop() {
  if (radio.available()) {
    radio.read(&receivedData, sizeof(receivedData));
    Serial.print("Données reçues: ");
    Serial.println(receivedData);
  }
}