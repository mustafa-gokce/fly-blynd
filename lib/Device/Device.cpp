#include "Device.h"

namespace FlyBlynd
{
    namespace Device
    {
        Device::Device()
        {
            // create console instance
            this->console = new Console::Console(this->gps);
        }

        Device::~Device()
        {
            // free console instance
            delete this->console;
        }

        const GPS::GPS &Device::getGPS() const
        {
            // return GPS module instance
            return this->gps;
        }

        Console::Console *Device::getConsole() const
        {
            // return console instance
            return this->console;
        }
    } // namespace System
} // namespace FlyBlynd
