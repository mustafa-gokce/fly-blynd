#include "Time.h"

namespace FlyBlynd
{
    namespace Time
    {
        Time::Time(uint8_t hour, uint8_t minute, uint8_t second)
            : hour(hour), minute(minute), second(second)
        {
        }

        Time::~Time() = default;

        uint8_t Time::getHour() const
        {
            return this->hour;
        }

        uint8_t Time::getMinute() const
        {
            return this->minute;
        }

        uint8_t Time::getSecond() const
        {
            return this->second;
        }
    } // namespace Time
} // namespace FlyBlynd
