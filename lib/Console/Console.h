#ifndef FLY_BLYND_CONSOLE_H
#define FLY_BLYND_CONSOLE_H

#include "GPS.h"

namespace FlyBlynd
{
    namespace Console
    {
        class Console
        {
        public:
            /*
             * Console that interfaces with serial console
             */
            explicit Console(const GPS::GPS &gps);
            ~Console();

            /*
             * Get GPS module instance
             */
            const GPS::GPS &getGPS() const;

            /*
             * Print a message to the serial console followed by a new line
             */
            void printLine(const std::string &message);

        private:
            /*
             * Begin serial console
             */
            void begin();

            /*
             * Start serial console task
             */
            void startTask();

            /*
             * Start serial console task implementation
             */
            static void startTaskImpl(void *instance);

            /*
             * Serial console task
             */
            void run();

        private:
            const GPS::GPS &gps;            // GPS module instance
            TaskHandle_t consoleTaskHandle; // serial console task handler
        };
    } // namespace Console
} // namespace FlyBlynd

#endif // FLY_BLYND_CONSOLE_H
