#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define PIN_CE 9
#define PIN_CSN 10

RF24 radio(PIN_CE, PIN_CSN);
int dataToSend = 658; // Initialiser avec 658

void setup() {
  Serial.begin(9600); // Initialiser la communication série pour le débogage
  radio.begin(); 
  radio.setPALevel(RF24_PA_LOW); // Régler la puissance d'émission à faible
  radio.setDataRate(RF24_250KBPS); // Régler le débit de données à 250 kbps
  radio.openWritingPipe(0xF0F0F0F0E1LL); // ID unique pour l'émetteur
}

void loop() {
  bool success = radio.write(&dataToSend, sizeof(dataToSend)); // Envoyer la donnée

  if (success) {
    Serial.print("Transmission réussie : ");
    Serial.println(dataToSend); // Afficher la donnée envoyée
  } else {
    Serial.println("Transmission échouée.");
  }
  
  dataToSend++; // Incrémenter la donnée pour la prochaine transmission
  delay(1000); // Attendre 1 seconde avant la prochaine transmission
}
