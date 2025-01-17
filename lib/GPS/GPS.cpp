
#include "GPS.h"

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
    } // namespace

    namespace GPS
    {
        GPS::GPS()
        {
            // initialize GPS module
            this->begin();
        }

        GPS::~GPS() = default;

        const Date::Date &GPS::getDate() const
        {
            return this->date;
        }

        const Time::Time &GPS::getTime() const
        {
            return this->time;
        }

        const Location::Location &GPS::getLocation() const
        {
            return this->location;
        }

        double GPS::getSpeed() const
        {
            return this->speed;
        }

        double GPS::getCourse() const
        {
            return this->course;
        }

        uint8_t GPS::getSatellites() const
        {
            return this->satellites;
        }

        double GPS::getHDOP() const
        {
            return this->hdop;
        }

        bool GPS::isAvailable() const
        {
            // HDOP is invalid
            if (this->hdop >= 100.0f || this->hdop <= 0.1f)
            {
                return false;
            }

            // date is invalid
            if (this->date.year < 2000 || this->date.year > 2099)
            {
                return false;
            }
            
            // GPS module is available
            return true;
        }

        void GPS::begin()
        {
            // start GPS module serial reading task
            this->startTask();
        }

        void GPS::startTask()
        {
            // start GPS module serial reading task
            xTaskCreatePinnedToCore(this->startTaskImpl,
                                    GPS_TASK_NAME,
                                    GPS_TASK_STACK_SIZE,
                                    this,
                                    GPS_TASK_PRIORITY,
                                    &this->gpsTaskHandle,
                                    GPS_TASK_CORE);
        }

        void GPS::startTaskImpl(void *instance)
        {
            // run GPS module serial reading task
            static_cast<GPS *>(instance)->run();
        }

        void GPS::run()
        {
            // GPS module serial connection
            SoftwareSerial serialGPS(GPS_MODULE_RX_PIN, GPS_MODULE_TX_PIN);
            serialGPS.begin(GPS_MODULE_BAUD_RATE);

            // run infinite loop
            for (;;)
            {
                // read GPS module serial data
                while (serialGPS.available() > 0)
                {
                    // parse GPS module serial data
                    if (this->gpsParser.encode(serialGPS.read()))
                    {
                        // update GPS module with parser
                        this->update(&this->gpsParser);
                    }
                }

                // delay for GPS module serial reading task
                vTaskDelay(1 / portTICK_PERIOD_MS);
            }

            // delete GPS module task
            vTaskDelete(this->gpsTaskHandle);
        }

        void GPS::update(TinyGPSPlus *parser)
        {
            // update date
            if (parser->date.isValid() && parser->date.isUpdated())
            {
                this->date.year = parser->date.year();
                this->date.month = parser->date.month();
                this->date.day = parser->date.day();
            }

            // update time
            if (parser->time.isValid() && parser->time.isUpdated())
            {
                this->time.hour = parser->time.hour();
                this->time.minute = parser->time.minute();
                this->time.second = parser->time.second();
            }

            // update location
            if (parser->location.isValid() && parser->location.isUpdated())
            {
                this->location.latitude = parser->location.lat();
                this->location.longitude = parser->location.lng();
            }

            // update altitude
            if (parser->altitude.isValid() && parser->altitude.isUpdated())
            {
                this->location.altitude = parser->altitude.meters();
            }

            // update speed
            if (parser->speed.isValid() && parser->speed.isUpdated())
            {
                this->speed = parser->speed.mps();
            }

            // update course
            if (parser->course.isValid() && parser->course.isUpdated())
            {
                this->course = parser->course.deg();
            }

            // update satellites
            if (parser->satellites.isValid() && parser->satellites.isUpdated())
            {
                this->satellites = parser->satellites.value();
            }

            // update HDOP
            if (parser->hdop.isValid() && parser->hdop.isUpdated())
            {
                this->hdop = parser->hdop.hdop();
            }
        }
    } // namespace GPS
} // namespace FlyBlynd
