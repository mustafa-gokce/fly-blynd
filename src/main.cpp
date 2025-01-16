#include "main.h"

#include "Arduino.h"

#include "GPS.h"

namespace
{
    static const char *DEBUG_TASK_NAME = "debugTask";     // task name for debugging
    constexpr uint32_t DEBUG_TASK_STACK_SIZE = 10000;     // stack size for debugging task
    constexpr UBaseType_t DEBUG_TASK_PRIORITY = 2;        // priority for debugging task
    constexpr BaseType_t DEBUG_TASK_CORE = 1;             // core for debugging task
    constexpr uint32_t DEBUG_TASK_DELAY = 1000;           // delay for debugging task
    constexpr uint32_t SERIAL_CONSOLE_BAUD_RATE = 115200; // baud rate for serial console
    TaskHandle_t debugTaskHandle;                         // task handle for debugging task
} // namespace

FlyBlynd::GPS::GPS gps; // GPS module instance

void setup()
{
    // start serial console
    Serial.begin(SERIAL_CONSOLE_BAUD_RATE);

    // start data dumping task
    xTaskCreatePinnedToCore(debugTask,
                            DEBUG_TASK_NAME,
                            DEBUG_TASK_STACK_SIZE,
                            nullptr,
                            DEBUG_TASK_PRIORITY,
                            &debugTaskHandle,
                            DEBUG_TASK_CORE);
}

void loop()
{
    // always leave this empty
}

void debugTask(void *pvParameters)
{
    // loop forever
    for (;;)
    {
        // check serial console is available
        if (!Serial)
        {
            // delay for a while
            vTaskDelay(DEBUG_TASK_DELAY / portTICK_PERIOD_MS);

            // continue to next iteration
            continue;
        }

        // print system information to serial console
        Serial.print("DATE ");
        Serial.print(gps.getDate().getYear());
        Serial.print("/");
        Serial.print(gps.getDate().getMonth());
        Serial.print("/");
        Serial.print(gps.getDate().getDay());
        Serial.print(" TIME ");
        Serial.print(gps.getTime().getHour());
        Serial.print(":");
        Serial.print(gps.getTime().getMinute());
        Serial.print(":");
        Serial.print(gps.getTime().getSecond());
        Serial.print(" LOCATION ");
        Serial.print(gps.getLocation().getLatitude(), 6);
        Serial.print(" ");
        Serial.print(gps.getLocation().getLongitude(), 6);
        Serial.print(" ");
        Serial.print(gps.getLocation().getAltitude(), 1);
        Serial.print(" SPEED ");
        Serial.print(gps.getSpeed(), 1);
        Serial.print(" COURSE ");
        Serial.print(gps.getCourse(), 1);
        Serial.print(" SATELLITES ");
        Serial.print(gps.getSatellites());
        Serial.print(" HDOP ");
        Serial.print(gps.getHDOP(), 1);
        Serial.println();

        // delay for a while
        vTaskDelay(DEBUG_TASK_DELAY / portTICK_PERIOD_MS);
    }

    // delete task if it ever breaks out of loop
    vTaskDelete(debugTaskHandle);
}
