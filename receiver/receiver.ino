#include <SPI.h>
#include <RF24.h>

RF24 radio(9,10);   // CE, CSN

byte address[6] = "00001";
struct Data {
  int x1;
  int y1;
  int b1;
  int x2;
  int y2;
  int b2;
};

Data data;

void setup() {
  Serial.begin(9600);

  if (!radio.begin()) {
    Serial.println("NRF24L01 not detected!");
    while (1);
  }

  radio.setChannel(76);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
    radio.setRetries(5,15);

  radio.openReadingPipe(0, address);
  radio.startListening();

  Serial.println("Receiver ready");
}

void loop() {

if (radio.available()) {
  radio.read(&data, sizeof(data));

  Serial.print("x1:");
  Serial.print(data.x1);
  Serial.print(" y1:");
  Serial.print(data.y1);
  Serial.print(" b1:");
  Serial.print(data.b1);

  Serial.print(" || x2:");
  Serial.print(data.x2);
  Serial.print(" y2:");
  Serial.print(data.y2);
  Serial.print(" b2:");
  Serial.println(data.b2);
}


}
