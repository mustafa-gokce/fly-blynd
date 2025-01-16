#ifndef FLY_BLYND_GPS_H
#define FLY_BLYND_GPS_H

#include "Arduino.h"
#include "SoftwareSerial.h"

#include "TinyGPS++.h"

namespace FlyBlynd
{

    namespace
    {

        static const char *GPS_TASK_NAME = "taskGPS";   // task name for GPS module serial reading task
        constexpr uint32_t GPS_TASK_STACK_SIZE = 10000; // stack size for GPS module serial reading task
        constexpr UBaseType_t GPS_TASK_PRIORITY = 1;    // priority for GPS module serial reading task
        constexpr BaseType_t GPS_TASK_CORE = 0;         // use 0th core for GPS module serial reading task
        constexpr uint8_t GPS_MODULE_RX_PIN = 17;       // GPS module receiver pin
        constexpr uint8_t GPS_MODULE_TX_PIN = 16;       // GPS module transmitter pin
        constexpr uint32_t GPS_MODULE_BAUD_RATE = 9600; // GPS module baud rate

    }

    class Location
    {

    public:
        /*
         * Location class contains latitude, longitude and altitude
         */
        explicit Location(double latitude = 0.0,
                          double longitude = 0.0,
                          double altitude = 0.0);
        ~Location();
        friend class GPS;

        /*
         * Get latitude in degrees
         */
        double getLatitude() const;

        /*
         * Get longitude in degrees
         */
        double getLongitude() const;

        /*
         * Get altitude in meters above mean sea level
         */
        double getAltitude() const;

    protected:
        double latitude;  // latitude in degrees
        double longitude; // longitude in degrees
        double altitude;  // altitude above mean sea level in meters
    };

    class Date
    {

    public:
        /*
         * Date class contains this year, month and day
         */
        explicit Date(uint16_t year = 0, uint8_t month = 0, uint8_t day = 0);
        ~Date();
        friend class GPS;

        /*
         * Get this year
         */
        uint16_t getYear() const;

        /*
         * Get this month
         */
        uint8_t getMonth() const;

        /*
         * Get this day
         */
        uint8_t getDay() const;

    protected:
        uint16_t year; // this year
        uint8_t month; // this month
        uint8_t day;   // this day
    };

    class Time
    {

    public:
        /*
         * Time class contains current hour, minute and second
         */
        explicit Time(uint8_t hour = 0, uint8_t minute = 0, uint8_t second = 0);
        ~Time();
        friend class GPS;

        /*
         * Get current hour
         */
        uint8_t getHour() const;

        /*
         * Get current minute
         */
        uint8_t getMinute() const;

        /*
         * Get current second
         */
        uint8_t getSecond() const;

    protected:
        uint8_t hour;   // current hour
        uint8_t minute; // current minute
        uint8_t second; // current second
    };

    class GPS
    {

    public:
        /*
         * GPS class that interfaces with GPS module
         */
        explicit GPS();
        ~GPS();

        /*
         * Get current date
         */
        const Date &getDate() const;

        /*
         * Get current time
         */
        const Time &getTime() const;

        /*
         * Get current location
         */
        const Location &getLocation() const;

        /*
         * Get current speed in meters per second
         */
        double getSpeed() const;

        /*
         * Get current course in degrees
         */
        double getCourse() const;

        /*
         * Get current number of satellites
         */
        uint8_t getSatellites() const;

        /*
         * Get current HDOP.
         */
        double getHDOP() const;

    private:
        /*
         * Begin GPS module
         */
        void begin();

        /*
         * Start GPS module task
         */
        void startTask();

        /*
         * Start GPS module task implementation
         */
        static void startTaskImpl(void *instance);

        /*
         * Run GPS module task
         */
        void run();

        /*
         * Update GPS class with parser
         */
        void update(TinyGPSPlus *parser);

    private:
        Date date;                            // current date
        Time time;                            // current time
        Location location;                    // current location
        double speed;                         // current speed in meters per second
        double course;                        // current course in degrees
        uint8_t satellites;                   // current number of satellites
        double hdop;                          // current HDOP
        TinyGPSPlus gpsParser;                // GPS parser
        TaskHandle_t gpsTaskHandle = nullptr; // GPS module task handler
    };

} // namespace FlyBlynd

#endif // FLY_BLYND_GPS_H
