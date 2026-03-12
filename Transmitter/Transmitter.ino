#include <SPI.h>
#include <RF24.h>

RF24 radio(9,10);   // CE, CSN

byte address[6] = "00001";
int data = 123;

void setup() {
  Serial.begin(9600);

  if (!radio.begin()) {
    Serial.println("NRF24L01 not detected!");
    while (1);
  }

  radio.setChannel(76);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.setRetries(5,15);

  radio.openWritingPipe(address);
  radio.stopListening();

  Serial.println("Transmitter readyy");
}

void loop() {

  bool ok = radio.write(&data, sizeof(data));

  if (ok) {
    Serial.println("Send OK");
  } else {
    Serial.println("Send FAIL");
  }

  delay(5000);
}
