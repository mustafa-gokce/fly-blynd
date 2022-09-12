#ifndef RE_GPS_H
#define RE_GPS_H

#include "Arduino.h"
#include "TinyGPS++.h"
#include "SoftwareSerial.h"


// Location class contains latitude, longitude and altitude.
class RE_Location {
    friend class RE_GPS;

public:
    RE_Location() {};

    ~RE_Location() {};

    // Latitude in degrees.
    double latitude() { return _latitude; };

    // Longitude in degrees.
    double longitude() { return _longitude; };

    // Altitude above mean sea level in meters.
    double altitude() { return _altitude; };

private:
    double _latitude;
    double _longitude;
    double _altitude;
};

// Date class contains this year, month and day.
class RE_Date {
    friend class RE_GPS;

public:
    RE_Date() {};

    ~RE_Date() {};

    // This year.
    uint16_t year() { return _year; };

    // This month.
    uint8_t month() { return _month; };

    // This day.
    uint8_t day() { return _day; };

private:
    uint16_t _year;
    uint8_t _month;
    uint8_t _day;
};

// Time class contains current hour, minute and second.
class RE_Time {
    friend class RE_GPS;

public:
    RE_Time() {};

    ~RE_Time() {};

    // Current hour.
    uint8_t hour() { return _hour; };

    // Current minute.
    uint8_t minute() { return _minute; };

    // Current second.
    uint8_t second() { return _second; };

private:
    uint8_t _hour;
    uint8_t _minute;
    uint8_t _second;
};

// GPS class contains data from attached GPS module.
class RE_GPS {
public:
    RE_GPS() {};

    ~RE_GPS() {};

    RE_Date date;
    RE_Time time;
    RE_Location location;

    // Current speed in meters per second.
    double speed() {return _speed;};

    // Current movement course in degrees.
    double course() {return _course;};

    // Current visible satellites count.
    uint32_t satellites() {return _satellites;};
    
    // Current HDOP of attached GPS module.
    double hdop() {return _hdop;};

    void begin();

private:
    double _speed;
    double _course;
    uint32_t _satellites;
    double _hdop;

    // GPS module parser.
    TinyGPSPlus parserGPS;

    // Task name for GPS module serial reading task
    const char *NAME_TASK_GPS = "taskGPS";

    // Stack size for GPS module serial reading task
    const uint32_t STACK_SIZE_TASK_GPS = 10000;

    // Priority for GPS module serial reading task
    const UBaseType_t PRIORITY_TASK_GPS = 1;

    // GPS module task handler.
    TaskHandle_t taskHandlerGPS = NULL;

    // Use 0th core for sensing.
    const BaseType_t CORE_SENSE = 0;

    // GPS module receiver pin.
    const uint8_t PIN_GPS_RX = 17;

    // GPS module transmitter pin.
    const uint8_t PIN_GPS_TX = 16;

    // GPS module baud rate.
    const uint32_t BAUD_GPS = 9600;

    void startTask();
    
    static void startTaskImpl(void* _this);

    void run();

    // Update GPS class with parser.
    void update(TinyGPSPlus *parserGPS);


};

#endif