#include "main.h"

// GPS data class instance.
RE_GPS gps;

// Setup application.
void setup() {
    Serial.begin(BAUD_SERIAL);
    gps.begin();
    // Start data dumping task.
    xTaskCreatePinnedToCore(taskDump,
                            NAME_TASK_DUMP,
                            STACK_SIZE_TASK_DUMP,
                            NULL,
                            PRIORITY_TASK_DUMP,
                            &taskHandlerDump,
                            CORE_INTERACT);
}

// Empty loop.
void loop() {
    // Always leave this empty.
}


void taskDump(void *pvParameters) {
    for (;;) {
        Serial.print("DATE ");
        Serial.print(gps.date.year());
        Serial.print("/");
        Serial.print(gps.date.month());
        Serial.print("/");
        Serial.print(gps.date.day());
        Serial.print(" TIME ");
        Serial.print(gps.time.hour());
        Serial.print(":");
        Serial.print(gps.time.minute());
        Serial.print(":");
        Serial.print(gps.time.second());
        Serial.print(" LOCATION ");
        Serial.print(gps.location.latitude(), 6);
        Serial.print(" ");
        Serial.print(gps.location.longitude(), 6);
        Serial.print(" ");
        Serial.print(gps.location.altitude(), 1);
        Serial.print(" SPEED ");
        Serial.print(gps.speed(), 1);
        Serial.print(" COURSE ");
        Serial.print(gps.course(), 1);
        Serial.print(" SATELLITES ");
        Serial.print(gps.satellites());
        Serial.print(" HDOP ");
        Serial.print(gps.hdop(), 1);
        Serial.println();
        vTaskDelay(DELAY_TASK_DUMP / portTICK_PERIOD_MS);
    }
    vTaskDelete(taskHandlerDump);
}