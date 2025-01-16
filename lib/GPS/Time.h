#ifndef FLY_BLYND_TIME_H
#define FLY_BLYND_TIME_H

#include <cstdint>

namespace FlyBlynd
{
    namespace GPS
    {
        class GPS;
    } // namespace GPS
} // namespace FlyBlynd

namespace FlyBlynd
{
    namespace Time
    {
        class Time
        {
        public:
            /*
             * Time class contains current hour, minute and second
             */
            explicit Time(uint8_t hour = 0, uint8_t minute = 0, uint8_t second = 0);
            ~Time();
            friend class GPS::GPS;

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

    } // namespace Time
} // namespace FlyBlynd

#endif // FLY_BLYND_TIME_H
