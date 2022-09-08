#include "../include/main.h"

SoftwareSerial mySerial(17, 16);

void setup()
{
  Serial.begin(115200);
  mySerial.begin(9600);
}

void loop()
{
  if (mySerial.available())
    Serial.write(mySerial.read());
  if (Serial.available())
    mySerial.write(Serial.read());
}