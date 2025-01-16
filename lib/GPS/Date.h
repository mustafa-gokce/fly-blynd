#ifndef FLY_BLYND_DATE_H
#define FLY_BLYND_DATE_H

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
    namespace Date
    {
        class Date
        {

        public:
            /*
             * Date class contains this year, month and day
             */
            explicit Date(uint16_t year = 0, uint8_t month = 0, uint8_t day = 0);
            ~Date();
            friend class GPS::GPS;

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
    } // namespace Date
} // namespace FlyBlynd

#endif // FLY_BLYND_DATE_H
