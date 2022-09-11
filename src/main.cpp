#include "main.h"

// Setup application.
void setup() {
    // Start GPS module serial reading task.
    xTaskCreatePinnedToCore(taskGPS,
                            NAME_TASK_GPS,
                            STACK_SIZE_TASK_GPS,
                            NULL,
                            PRIORITY_TASK_GPS,
                            &taskHandlerGPS,
                            CORE_SENSE);

    // Start GPS data dumping task.
    xTaskCreatePinnedToCore(taskGPSDump,
                            NAME_TASK_GPS_DUMP,
                            STACK_SIZE_TASK_GPS_DUMP,
                            NULL,
                            PRIORITY_TASK_GPS_DUMP,
                            &taskHandlerGPSDump,
                            CORE_SENSE);
}

// Empty loop.
void loop() {
    // Always leave this empty.
}

void taskGPS(void *pvParameters) {
    serialGPS.begin(BAUD_GPS);
    for (;;) {
        if (serialGPS.available() > 0) {
            while (serialGPS.available() > 0) {
                if (parserGPS.encode(serialGPS.read())) {
                    gps.update(&parserGPS);
                }
            }
        } else {
            vTaskDelay(DELAY_TASK_GPS / portTICK_PERIOD_MS);
        }
    }
    vTaskDelete(taskHandlerGPS);
}

void taskGPSDump(void *pvParameters) {
    Serial.begin(BAUD_SERIAL);
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
        vTaskDelay(DELAY_TASK_GPS_DUMP / portTICK_PERIOD_MS);
    }
    vTaskDelete(taskHandlerGPSDump);
}