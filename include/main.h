#include "Arduino.h"
#include "GPS.h"

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

// Data dumping task function.
void taskDump(void *pvParameters);

// Task name for data dumping task
const char *NAME_TASK_DUMP = "taskDump";

// Stack size for data dumping task
const uint32_t STACK_SIZE_TASK_DUMP = 10000;

// Priority for GPS data dumping task
const UBaseType_t PRIORITY_TASK_DUMP = 2;

// Dump task handler.
TaskHandle_t taskHandlerDump;

// Use 1st core for user interaction.
const BaseType_t CORE_INTERACT = 1;

// Delay for data dumping task
const uint32_t DELAY_TASK_DUMP = 1000;

/*
 * Device hardware, input and output definitions.
 */

// Serial console baud rate.
const uint32_t BAUD_SERIAL = 115200;