#include "main.h"

SoftwareSerial mySerial(17, 16);
const char nmea_start = 0x24;
const char carriage_return = 0x0D;
const char line_feed = 0x0A;
char sentence[79];
int8_t i = 0;

void setup() {
    Serial.begin(115200);
    mySerial.begin(9600);
}

void loop() {
    if (mySerial.available()) {
        char c = mySerial.read();
        if (c == nmea_start) {
            i = 0;
        } else if (c == carriage_return) {
            i = 0;
        } else if (c == line_feed) {
            i = 0;
            Serial.println(sentence);
        } else {
            sentence[i] = c;
            i++;
        }
    }
}