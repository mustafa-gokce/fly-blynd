#include "Location.h"

namespace FlyBlynd
{
    namespace Location
    {
        Location::Location(double latitude, double longitude, double altitude)
            : latitude(latitude), longitude(longitude), altitude(altitude)
        {
        }

        Location::~Location() = default;

        double Location::getLatitude() const
        {
            return this->latitude;
        }

        double Location::getLongitude() const
        {
            return this->longitude;
        }

        double Location::getAltitude() const
        {
            return this->altitude;
        }
    } // namespace Location
} // namespace FlyBlynd