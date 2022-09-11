#include "Arduino.h"
#include "SoftwareSerial.h"
#include "TinyGPS++.h"

TaskHandle_t taskHandlerGPS;
TinyGPSPlus parserGPS;

const uint8_t rxPinGPS = 17;
const uint8_t txPinGPS = 16;
const uint32_t baudGPS = 9600;

static volatile float latitude;

void taskGPS(void *parameter);
