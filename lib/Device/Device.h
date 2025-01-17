#ifndef FLYBLYND_DEVICE_H
#define FLYBLYND_DEVICE_H

#include "Console.h"
#include "GPS.h"

namespace FlyBlynd
{
    namespace Device
    {
        class Device
        {
        public:
            /*
             * System that is used to manage the device
             */
            explicit Device();
            ~Device();

            /*
             * Get GPS module instance
             */
            const GPS::GPS &getGPS() const;

            /*
             * Get console instance
             */
            Console::Console *getConsole() const;

        private:
            GPS::GPS gps;              // GPS module instance
            Console::Console *console; // console instance
        };
    } // namespace Device
} // namespace FlyBlynd

#endif // FLYBLYND_DEVICE_H
