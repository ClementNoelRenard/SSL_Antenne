#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>

const uint8_t address_1[6] = "00001"; // 5 bytes + 1 for the null terminator
RF24 radioNRF(7, 8); // CE, CSN pins

void serial_setupConnection(int baudrate) {
  Serial.begin(baudrate);
  while (!Serial) {
    // Commenting this out as it waits for Serial to be ready
    // Serial.println("En attente de l'ouverture du port série...");
    delay(1000);
  }
  Serial.println("Port série activé. Baudrate: " + String(baudrate));
  delay(50);
}

void nrf24_init(uint8_t channel) {
  printf_begin(); // Initializes the printf library for RF24 debug prints
  radioNRF.begin();
  radioNRF.setChannel(channel); // Set communication channel (0-125)
  radioNRF.setDataRate(RF24_250KBPS); // Set communication speed
  radioNRF.enableDynamicPayloads();
  radioNRF.setPALevel(RF24_PA_HIGH); // Set amplification level
  radioNRF.printDetails(); // Print all radio configurations
}

bool nrf24_sendData(String dataToSend) {
  delay(50); // Short delay for stability
  Serial.println("Envoi de: " + dataToSend);
  radioNRF.stopListening(); // Stop listening to send data
  char inputChar[dataToSend.length() + 1];
  dataToSend.toCharArray(inputChar, dataToSend.length() + 1);
  bool result = radioNRF.write(&inputChar, strlen(inputChar) + 1);
  return result;
}

void setup() {
  serial_setupConnection(9600);
  nrf24_init(115); // Initialize nRF24L01 on channel 115
  radioNRF.openWritingPipe(address_1); // Open writing pipe with address
}

void loop() {
  bool sent = nrf24_sendData("B");
  if (sent) {
    Serial.println("Data sent successfully.");
  } else {
    Serial.println("Failed to send data.");
  }
  delay(5000); // Wait 5 seconds before sending the next data
}
