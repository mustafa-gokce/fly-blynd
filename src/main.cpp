#include "main.h"

void setup() {
    Serial.begin(115200);
    xTaskCreatePinnedToCore(taskGPS, "taskGPS", 10000, NULL, 1, &taskHandlerGPS, 0);
}

void loop() {
    Serial.println(latitude, 6);
    sleep(1);
}

void taskGPS(void *parameter) {
    SoftwareSerial serialGPS(rxPinGPS, txPinGPS);
    serialGPS.begin(baudGPS);
    while (true) {
        if (serialGPS.available() > 0) {
            while (serialGPS.available() > 0) {
                if (parserGPS.encode(serialGPS.read())) {
                    if (parserGPS.location.isValid() && parserGPS.location.isUpdated()) {
                        latitude = parserGPS.location.lat();
                    }
                }
            }
        } else {
            vTaskDelay(1 / portTICK_PERIOD_MS);
        }
    }
}