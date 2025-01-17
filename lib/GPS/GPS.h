#ifndef FLY_BLYND_GPS_H
#define FLY_BLYND_GPS_H

#include <Arduino.h>
#include <SoftwareSerial.h>

#include <TinyGPS++.h>

#include "Location.h"
#include "Date.h"
#include "Time.h"

namespace FlyBlynd
{
    namespace GPS
    {
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
            const Date::Date &getDate() const;

            /*
             * Get current time
             */
            const Time::Time &getTime() const;

            /*
             * Get current location
             */
            const Location::Location &getLocation() const;

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

            /*
             * Check if GPS module is available
             */
            bool isAvailable() const;

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
            Date::Date date;             // current date
            Time::Time time;             // current time
            Location::Location location; // current location
            double speed;                // current speed in meters per second
            double course;               // current course in degrees
            uint8_t satellites;          // current number of satellites
            double hdop;                 // current HDOP
            TinyGPSPlus gpsParser;       // GPS parser
            TaskHandle_t gpsTaskHandle;  // GPS module task handler
        };
    } // namespace GPS
} // namespace FlyBlynd

#endif // FLY_BLYND_GPS_H
