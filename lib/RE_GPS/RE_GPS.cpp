
#include "RE_GPS.h"


void RE_GPS::begin(){

    startTask() ;
}

void RE_GPS::run() {

    // GPS module serial connection
    SoftwareSerial serialGPS(PIN_GPS_RX, PIN_GPS_TX);
    serialGPS.begin(BAUD_GPS);

    for (;;) {
        if (serialGPS.available() > 0) {
            while (serialGPS.available() > 0) {
               if (parserGPS.encode(serialGPS.read())) {
                    update(&parserGPS);
                }           
            }
        } else {
            vTaskDelay(1 / portTICK_PERIOD_MS);
        }
    }
     vTaskDelete(taskHandlerGPS);
}

void RE_GPS::startTaskImpl(void* _this)
{
    static_cast<RE_GPS*>(_this)->run();

}

// Setup application.
void RE_GPS::startTask() {
    
    // Start GPS module serial reading task.
    xTaskCreatePinnedToCore(this->startTaskImpl,
                            NAME_TASK_GPS,
                            10000,
                            this,
                            PRIORITY_TASK_GPS,
                            &taskHandlerGPS,
                            CORE_SENSE);

}

void RE_GPS::update(TinyGPSPlus *parserGPS) {
    if (parserGPS->date.isValid() && parserGPS->date.isUpdated()) {
        date._year = parserGPS->date.year();
        date._month = parserGPS->date.month();
        date._day = parserGPS->date.day();
    }
    if (parserGPS->time.isValid() && parserGPS->time.isUpdated()) {
        time._hour = parserGPS->time.hour();
        time._minute = parserGPS->time.minute();
        time._second = parserGPS->time.second();
    }
    if (parserGPS->location.isValid() && parserGPS->location.isUpdated()) {
        location._latitude = parserGPS->location.lat();
        location._longitude = parserGPS->location.lng();
    }
    if (parserGPS->altitude.isValid() && parserGPS->altitude.isUpdated()) {
        location._altitude = parserGPS->altitude.meters();
    }
    if (parserGPS->speed.isValid() && parserGPS->speed.isUpdated()) {
        _speed = parserGPS->speed.mps();
    }
    if (parserGPS->course.isValid() && parserGPS->course.isUpdated()) {
        _course = parserGPS->course.deg();
    }
    if (parserGPS->satellites.isValid() && parserGPS->satellites.isUpdated()) {
        _satellites = parserGPS->satellites.value();
    }
    if (parserGPS->hdop.isValid() && parserGPS->hdop.isUpdated()) {
        _hdop = parserGPS->hdop.hdop();
    }
}