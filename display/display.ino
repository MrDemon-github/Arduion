#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // put your setup code here, to run once:
display.begin(SSD1306_SWITCHCAPVCC,0x3C);
display.clearDisplay();


display.setTextSize(2);
display.setTextColor(SSD1306_WHITE);
display.setCursor(10,20);
for(int i=0;i<10;++i){
display.clearDisplay();
display.setCursor(0,0);
display.print(i);
display.display();
delay(1000);

}



}

void loop() {
  // put your main code here, to run repeatedly:

}
