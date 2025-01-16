#include "Date.h"

namespace FlyBlynd
{
    namespace Date
    {
        Date::Date(uint16_t year, uint8_t month, uint8_t day)
            : year(year), month(month), day(day)
        {
        }

        Date::~Date() = default;

        uint16_t Date::getYear() const
        {
            return this->year;
        }

        uint8_t Date::getMonth() const
        {
            return this->month;
        }

        uint8_t Date::getDay() const
        {
            return this->day;
        }
    } // namespace Date
} // namespace FlyBlynd