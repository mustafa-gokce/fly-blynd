#include "Console.h"

namespace FlyBlynd
{
    namespace
    {
        static const char *CONSOLE_TASK_NAME = "consoleTask"; // task name for debugging
        constexpr uint32_t CONSOLE_TASK_STACK_SIZE = 10000;   // stack size for debugging task
        constexpr UBaseType_t CONSOLE_TASK_PRIORITY = 2;      // priority for debugging task
        constexpr BaseType_t CONSOLE_TASK_CORE = 1;           // core for debugging task
        constexpr uint32_t CONSOLE_TASK_DELAY = 1000;         // delay for debugging task
        constexpr uint32_t SERIAL_CONSOLE_BAUD_RATE = 115200; // baud rate for serial console

    } // namespace

    namespace Console
    {
        Console::Console(const GPS::GPS &gps) : gps(gps)
        {
            // initialize serial console
            Serial.begin(SERIAL_CONSOLE_BAUD_RATE);

            // initialize serial console
            this->begin();
        }

        Console::~Console() = default;

        const GPS::GPS &Console::getGPS() const
        {
            // return GPS module instance
            return this->gps;
        }

        void Console::printLine(const std::string &message)
        {
            // message header
            static const std::string MESSAGE_HEADER = "[FLY_BLYND]: ";

            // build message
            const std::string messageWithHeader = MESSAGE_HEADER + message;

            // print message to serial console followed by a new line
            Serial.println(messageWithHeader.c_str());
        }

        void Console::begin()
        {
            // start serial console task
            this->startTask();
        }

        void Console::startTask()
        {
            // start serial console task
            xTaskCreatePinnedToCore(this->startTaskImpl,
                                    CONSOLE_TASK_NAME,
                                    CONSOLE_TASK_STACK_SIZE,
                                    this,
                                    CONSOLE_TASK_PRIORITY,
                                    &this->consoleTaskHandle,
                                    CONSOLE_TASK_CORE);
        }

        void Console::startTaskImpl(void *instance)
        {
            // run serial console task
            static_cast<Console *>(instance)->run();
        }

        void Console::run()
        {
            // loop forever
            for (;;)
            {
                // check serial console and GPS are available
                if (!Serial || !this->gps.isAvailable())
                {
                    // delay for a while
                    vTaskDelay(1 / portTICK_PERIOD_MS);

                    // continue to next iteration
                    continue;
                }

                // construct GPS message
                std::string message = "DATE ";
                message += std::to_string(this->gps.getDate().getYear());
                message += "/";
                message += std::to_string(this->gps.getDate().getMonth());
                message += "/";
                message += std::to_string(this->gps.getDate().getDay());
                message += " TIME ";
                message += std::to_string(this->gps.getTime().getHour());
                message += ":";
                message += std::to_string(this->gps.getTime().getMinute());
                message += ":";
                message += std::to_string(this->gps.getTime().getSecond());
                message += " LOCATION ";
                message += std::to_string(this->gps.getLocation().getLatitude());
                message += " ";
                message += std::to_string(this->gps.getLocation().getLongitude());
                message += " ";
                message += std::to_string(this->gps.getLocation().getAltitude());
                message += " SPEED ";
                message += std::to_string(this->gps.getSpeed());
                message += " COURSE ";
                message += std::to_string(this->gps.getCourse());
                message += " SATELLITES ";
                message += std::to_string(this->gps.getSatellites());
                message += " HDOP ";
                message += std::to_string(this->gps.getHDOP());

                // print message to serial console
                this->printLine(message);

                // delay for a while
                vTaskDelay(CONSOLE_TASK_DELAY / portTICK_PERIOD_MS);
            }

            // delete serial console task
            vTaskDelete(this->consoleTaskHandle);
        }
    } // namespace Console
} // namespace FlyBlynd
