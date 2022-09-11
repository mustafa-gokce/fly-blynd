#define True true
#define TRUE true
#define False false
#define FALSE false

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "TinyGPS++.h"

const uint8_t rxPinGPS = 17;
const uint8_t txPinGPS = 16;
const uint32_t baudGPS = 9600;

static volatile uint16_t year;
static volatile uint8_t month;
static volatile uint8_t day;
static volatile uint8_t hour;
static volatile uint8_t minute;
static volatile uint8_t second;
static volatile double latitude;
static volatile double longitude;
static volatile double altitude;
static volatile double speed;
static volatile double course;
static volatile uint32_t satellites;
static volatile double hdop;

TinyGPSPlus parserGPS;
SoftwareSerial serialGPS(rxPinGPS, txPinGPS);
TaskHandle_t taskHandlerGPS;
TaskHandle_t taskHandlerDumpGPS;
void taskGPS(void *pvParameters);
void taskDumpGPS(void *pvParameters);
