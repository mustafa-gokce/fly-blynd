#include "main.h"

FlyBlynd::GPS::GPS gps; // GPS module instance

// Setup application.
void setup() {
    Serial.begin(BAUD_SERIAL);
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
        vTaskDelay(DELAY_TASK_DUMP / portTICK_PERIOD_MS);
    }
    vTaskDelete(taskHandlerDump);
}
