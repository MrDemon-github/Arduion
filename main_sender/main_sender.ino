#include <SPI.h>
#include <RF24.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


RF24 radio(9,10);   // CE, CSN
byte address[6] = "00001";
int data = 123;


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// joystick pins
int joy1X = A0;
int joy1Y = A1;
int joy2X = A2;
int joy2Y = A3;

int b1 = 3;
int b2 = 2;

int b1state=0;
int b2state=0;


struct Data {
  int x1;
  int y1;
  int b1;
  int x2;
  int y2;
  int b2;
};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
    while(true);
  }


  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,20);


  if (!radio.begin()) {
    Serial.println("NRF24L01 not detected!");
    display.print("NRF24L01 not detected");
    display.display();
    while (1);
  }


  radio.setChannel(76);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.setRetries(5,15);
  radio.openWritingPipe(address);
  radio.stopListening();
  Serial.println("Transmitter readyy");

  display.print("Transmitter ready");
  display.display();


  pinMode(b1, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:

  int x1 = analogRead(joy1X);
  int y1 = analogRead(joy1Y);
  int x2 = analogRead(joy2X);
  int y2 = analogRead(joy2Y);
  b1state = digitalRead(b1);
  b2state = digitalRead(b2);

String line1 = "x1:" + String(x1) + " y1:" + String(y1) + " b1:" + String(b1state);
String line2 = "x2:" + String(x2) + " y2:" + String(y2) + " b2:" + String(b2state);

display.clearDisplay();
display.setCursor(0,0);
display.print(line1);

display.setCursor(0,20);
display.print(line2);

display.display();

Serial.println(line1);
Serial.println(line2);




Data data;
data.x1 = x1;
data.y1 = y1;
data.b1 = b1state;
data.x2 = x2;
data.y2 = y2;
data.b2 = b2state;


radio.write(&data, sizeof(data));

delay(1000);

}
