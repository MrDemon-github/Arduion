#include <Servo.h>

Servo myServo;

void setup() {
  myServo.attach(9                                                                                                                                                                                                                                                                                       );   // signal pin connected to D9
}

void loop() {

  for (int i=0; i<180; i++)
  {
  myServo.write(i);    // move to 0 degrees
  delay(40);
  }

for (int i=180; i>=0; --i)
  {
  myServo.write(i);    // move to 0 degrees
  delay(40);
  }

}
