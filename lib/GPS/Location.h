#ifndef FLY_BLYND_LOCATION_H
#define FLY_BLYND_LOCATION_H

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
    namespace Location
    {
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
            friend class GPS::GPS;

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
    } // namespace Location
} // namespace FlyBlynd

#endif // FLY_BLYND_LOCATION_H
