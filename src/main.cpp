#include "main.h"

void setup() {
    xTaskCreatePinnedToCore(taskGPS, "taskGPS", 10000, NULL, 1, &taskHandlerGPS, 0);
    xTaskCreatePinnedToCore(taskDumpGPS, "taskDumpGPS", 10000, NULL, 1, &taskHandlerDumpGPS, 0);
}

void loop() {

}

void taskGPS(void *pvParameters) {
    serialGPS.begin(baudGPS);
    for (;;) {
        if (serialGPS.available() > 0) {
            while (serialGPS.available() > 0) {
                if (parserGPS.encode(serialGPS.read())) {
                    if (parserGPS.date.isValid() && parserGPS.date.isUpdated()) {
                        year = parserGPS.date.year();
                        month = parserGPS.date.month();
                        day = parserGPS.date.day();
                    }
                    if (parserGPS.time.isValid() && parserGPS.time.isUpdated()) {
                        hour = parserGPS.time.hour();
                        minute = parserGPS.time.minute();
                        second = parserGPS.time.second();
                    }
                    if (parserGPS.location.isValid() && parserGPS.location.isUpdated()) {
                        latitude = parserGPS.location.lat();
                        longitude = parserGPS.location.lng();
                    }
                    if (parserGPS.altitude.isValid() && parserGPS.altitude.isUpdated()) {
                        altitude = parserGPS.altitude.meters();
                    }
                    if (parserGPS.speed.isValid() && parserGPS.speed.isUpdated()) {
                        speed = parserGPS.speed.mps();
                    }
                    if (parserGPS.course.isValid() && parserGPS.course.isUpdated()) {
                        course = parserGPS.course.deg();
                    }
                    if (parserGPS.satellites.isValid() && parserGPS.satellites.isUpdated()) {
                        satellites = parserGPS.satellites.value();
                    }
                    if (parserGPS.hdop.isValid() && parserGPS.hdop.isUpdated()) {
                        hdop = parserGPS.hdop.hdop();
                    }
                }
            }
        } else {
            vTaskDelay(1 / portTICK_PERIOD_MS);
        }
    }
    vTaskDelete(taskHandlerGPS);
}

void taskDumpGPS(void *pvParameters) {
    Serial.begin(115200);
    for (;;) {
        Serial.print("DATE ");
        Serial.print(year);
        Serial.print("/");
        Serial.print(month);
        Serial.print("/");
        Serial.print(day);
        Serial.print(" TIME ");
        Serial.print(hour);
        Serial.print(":");
        Serial.print(minute);
        Serial.print(":");
        Serial.print(second);
        Serial.print(" LOCATION ");
        Serial.print(latitude, 6);
        Serial.print(" ");
        Serial.print(longitude, 6);
        Serial.print(" ");
        Serial.print(altitude, 1);
        Serial.print(" SPEED ");
        Serial.print(speed, 1);
        Serial.print(" COURSE ");
        Serial.print(course, 1);
        Serial.print(" SATELLITES ");
        Serial.print(satellites);
        Serial.print(" HDOP ");
        Serial.print(hdop, 1);
        Serial.println();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(taskHandlerDumpGPS);
}