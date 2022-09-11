#include "Arduino.h"
#include "RE_GPS.h"

RE_GPS::RE_GPS() {

}

RE_GPS::~RE_GPS() {

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