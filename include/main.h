#include "Arduino.h"
#include "SoftwareSerial.h"
#include "TinyGPS++.h"
#include "RE_GPS.h"

/*
 * General purpose definitions.
 */

// True is true.
const bool True = true;

// TRUE is true.
const bool TRUE = true;

// False is false.
const bool False = false;

// FALSE is false.
const bool FALSE = false;

/*
 * RTOS related task declarations.
 */

// GPS module serial reading task function.
void taskGPS(void *pvParameters);

// GPS data dumping task function.
void taskGPSDump(void *pvParameters);

// Task name for GPS module serial reading task
const char *NAME_TASK_GPS = "taskGPS";

// Task name for GPS data dumping task
const char *NAME_TASK_GPS_DUMP = "taskGPSDump";

// Stack size for GPS module serial reading task
const uint32_t STACK_SIZE_TASK_GPS = 10000;

// Stack size for GPS data dumping task
const uint32_t STACK_SIZE_TASK_GPS_DUMP = 10000;

// Priority for GPS module serial reading task
const UBaseType_t PRIORITY_TASK_GPS = 1;

// Priority for GPS data dumping task
const UBaseType_t PRIORITY_TASK_GPS_DUMP = 2;

// GPS module task handler.
TaskHandle_t taskHandlerGPS;

// GPS module dump task handler.
TaskHandle_t taskHandlerGPSDump;

// Use 0th core for sensing.
const BaseType_t CORE_SENSE = 0;

// Use 1st core for user interaction.
const BaseType_t CORE_INTERACT = 1;

// Delay for GPS module serial reading task
const uint32_t DELAY_TASK_GPS = 1;

// Delay for GPS data dumping task
const uint32_t DELAY_TASK_GPS_DUMP = 1000;

/*
 * Device hardware, input and output definitions.
 */

// GPS module receiver pin.
const uint8_t PIN_GPS_RX = 17;

// GPS module transmitter pin.
const uint8_t PIN_GPS_TX = 16;

// GPS module baud rate.
const uint32_t BAUD_GPS = 9600;

// Serial console baud rate.
const uint32_t BAUD_SERIAL = 115200;

/*
 * Global object instance declarations.
 */

// GPS module parser.
TinyGPSPlus parserGPS;

// GPS module serial connection.
SoftwareSerial serialGPS(PIN_GPS_RX, PIN_GPS_TX);

// GPS data class instance.
RE_GPS gps;