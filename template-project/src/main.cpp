// // /*
// //  * Copyright (c) 2020-2021 Advanced Robotics at the University of Washington <robomstr@uw.edu>
// //  *
// //  * This file is part of taproot-template-project.
// //  *
// //  * taproot-template-project is free software: you can redistribute it and/or modify
// //  * it under the terms of the GNU General Public License as published by
// //  * the Free Software Foundation, either version 3 of the License, or
// //  * (at your option) any later version.
// //  *
// //  * taproot-template-project is distributed in the hope that it will be useful,
// //  * but WITHOUT ANY WARRANTY; without even the implied warranty of
// //  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// //  * GNU General Public License for more details.
// //  *
// //  * You should have received a copy of the GNU General Public License
// //  * along with taproot-template-project.  If not, see <https://www.gnu.org/licenses/>.
// //  */

// // #ifdef PLATFORM_HOSTED
// // /* hosted environment (simulator) includes --------------------------------- */
// // #include <iostream>

// // #include "tap/communication/tcp-server/tcp_server.hpp"
// // #include "tap/motor/motorsim/dji_motor_sim_handler.hpp"
// // #endif

// // #include "tap/board/board.hpp"

// // #include "modm/architecture/interface/delay.hpp"

// // /* arch includes ------------------------------------------------------------*/
// // #include "tap/architecture/periodic_timer.hpp"
// // #include "tap/architecture/profiler.hpp"

// // /* communication includes ---------------------------------------------------*/
// // #include "drivers.hpp"
// // #include "drivers_singleton.hpp"

// // /* error handling includes --------------------------------------------------*/
// // #include "tap/errors/create_errors.hpp"

// // /* control includes ---------------------------------------------------------*/
// // #include "tap/architecture/clock.hpp"

// // /* define timers here -------------------------------------------------------*/
// // static constexpr float MAIN_LOOP_FREQUENCY = 500.0f;
// // tap::arch::PeriodicMilliTimer sendMotorTimeout(1000.0f / MAIN_LOOP_FREQUENCY);

// // // Place any sort of input/output initialization here. For example, place
// // // serial init stuff here.
// // static void initializeIo(src::Drivers *drivers);

// // // Anything that you would like to be called place here. It will be called
// // // very frequently. Use PeriodicMilliTimers if you don't want something to be
// // // called as frequently.
// // static void updateIo(src::Drivers *drivers);

// // int main()
// // {
// // #ifdef PLATFORM_HOSTED
// //     std::cout << "Simulation starting..." << std::endl;
// // #endif

// //     /*
// //      * NOTE: We are using DoNotUse_getDrivers here because in the main
// //      *      robot loop we must access the singleton drivers to update
// //      *      IO states and run the scheduler.
// //      */
// //     src::Drivers *drivers = src::DoNotUse_getDrivers();

// //     Board::initialize();
// //     initializeIo(drivers);
// //     drivers->leds.init();    // initalize the led

// // #ifdef PLATFORM_HOSTED
// //     tap::motor::motorsim::DjiMotorSimHandler::getInstance()->resetMotorSims();
// //     // Blocking call, waits until Windows Simulator connects.
// //     tap::communication::TCPServer::MainServer()->getConnection();
// // #endif

// //     while (1)
// //     {
// //         // do this as fast as you can
// //         PROFILE(drivers->profiler, updateIo, (drivers));
        
// //         if (sendMotorTimeout.execute())
// //         {
// //             // PROFILE(drivers->profiler, drivers->mpu6500.periodicIMUUpdate, ());
// //             PROFILE(drivers->profiler, drivers->commandScheduler.run, ());
// //             PROFILE(drivers->profiler, drivers->djiMotorTxHandler.encodeAndSendCanData, ());
// //             PROFILE(drivers->profiler, drivers->terminalSerial.update, ());
// //                     drivers->leds.set(tap::gpio::Leds::Green, true);     // Turn On LED
// //             modm::delay_ms(100);
// //             drivers->leds.set(tap::gpio::Leds::Green, false);     // Turn On LED
// //             modm::delay_ms(100);
                
// //         }
// //         modm::delay_us(10);
// //     }
// //     return 0;
// // }

// // static void initializeIo(src::Drivers *drivers)
// // {
// //     drivers->analog.init();
// //     drivers->pwm.init();
// //     drivers->digital.init();
// //     drivers->leds.init();
// //     drivers->can.initialize();
// //     drivers->errorController.init();
// //     drivers->remote.initialize();
// //     // drivers->mpu6500.init(MAIN_LOOP_FREQUENCY, 0.1, 0);
// //     drivers->refSerial.initialize();
// //     drivers->terminalSerial.initialize();
// //     drivers->schedulerTerminalHandler.init();
// //     drivers->djiMotorTerminalSerialHandler.init();
// // }

// // static void updateIo(src::Drivers *drivers)
// // {
// // #ifdef PLATFORM_HOSTED
// //     tap::motor::motorsim::DjiMotorSimHandler::getInstance()->updateSims();
// // #endif

// //     drivers->canRxHandler.pollCanData();
    // drivers->refSerial.updateSerial();
// //     drivers->remote.read();
// //     // drivers->mpu6500.read();
// // }





// #include "tap/algorithms/smooth_pid.hpp"
// #include "tap/board/board.hpp"

// #include "drivers_singleton.hpp"

// static constexpr tap::motor::MotorId MOTOR_ID = tap::motor::MOTOR2;
// static constexpr tap::can::CanBus CAN_BUS = tap::can::CanBus::CAN_BUS1;
// static constexpr int DESIRED_RPM = 600;

// uint8_t led = 0;
// uint16_t ledTimer = 0;

// // timer object
// tap::arch::PeriodicMilliTimer sendMotorTimeout(2);

// // PID algorithm
// // PID explained: <https://www.youtube.com/watch?v=wkfEZmsQqiA>
// static tap::algorithms::SmoothPidConfig pid_config_dt = {20, 0, 0, 0, 8000, 1, 0, 1, 0};
// tap::algorithms::SmoothPid pidController(pid_config_dt);

// int main()
// {
//     tap::Drivers *drivers = src::DoNotUse_getDrivers();

//     // motor object
//     tap::motor::DjiMotor motor(drivers, MOTOR_ID, CAN_BUS, false, "cool motor");

//     Board::initialize();

//     drivers->can.initialize();          // init CanBus to talk to motor
//     motor.initialize();                 // init motor
//     drivers->leds.init();    // initalize the led

//     while (1)
//     {
//         if (sendMotorTimeout.execute())
//         {
//             // do the pid algorithm
//             pidController.runControllerDerivateError(DESIRED_RPM - motor.getShaftRPM(), 1);
//             // set up msg so its ready to be sent
//             motor.setDesiredOutput(static_cast<int32_t>(pidController.getOutput()));
//             // send all msg to the motors
//             drivers->djiMotorTxHandler.encodeAndSendCanData();
            
//             ledTimer++;
//             if (ledTimer > 200) {
//                 ledTimer = 0;
//                 if (led) {
//                     drivers->leds.set(tap::gpio::Leds::Green, false);     // Turn On LED
//                     led = 0;
//                 } else {
//                     drivers->leds.set(tap::gpio::Leds::Green, true);     // Turn On LED
//                     led = 1;
//                 }
//             }
//         }

//         drivers->canRxHandler.pollCanData();   // checks to see if a msg is waiting
//         modm::delay_us(10);
//     }

// }

































#include "tap/algorithms/smooth_pid.hpp"
#include "tap/board/board.hpp"
#include "tap/motor/dji_motor.hpp"

#include "drivers_singleton.hpp"

using namespace src;

static constexpr tap::motor::MotorId MOTOR_ID = tap::motor::MOTOR2;
static constexpr tap::can::CanBus CAN_BUS = tap::can::CanBus::CAN_BUS1;
static constexpr int DESIRED_RPM = 3000;

uint8_t led = 0;
uint16_t ledTimer = 0;

// timer object
tap::arch::PeriodicMilliTimer sendMotorTimeout(2);

// PID algorithm
// PID explained: <https://www.youtube.com/watch?v=wkfEZmsQqiA>
static tap::algorithms::SmoothPidConfig pid_config_dt = {20, 0, 0, 0, 8000, 1, 0, 1, 0};
tap::algorithms::SmoothPid pidController(pid_config_dt);

int main()
{
    //tap::Drivers *drivers = src::DoNotUse_getDrivers();

    driversFunc drivers = DoNotUse_getDrivers; 

    // motor object
    tap::motor::DjiMotor motor(drivers(), MOTOR_ID, CAN_BUS, false, "cool motor", false);

    Board::initialize();

    drivers()->can.initialize();          // init CanBus to talk to motor
    motor.initialize();                 // init motor
    drivers()->leds.init();    // initalize the led

    tap::communication::serial::Remote remote(drivers());
    remote.initialize();
    drivers()->refSerial.initialize();

    while (1)
    {
        remote.read();
        drivers()->refSerial.updateSerial();
        if (sendMotorTimeout.execute())
        {

            float reading = remote.getChannel(tap::communication::serial::Remote::Channel::RIGHT_HORIZONTAL) * 1000;
            // do the pid algorithm
            pidController.runControllerDerivateError(reading - motor.getShaftRPM(), 1);
            // set up msg so its ready to be sent
            motor.setDesiredOutput(static_cast<int32_t>(pidController.getOutput()));
            // send all msg to the motors
            drivers()->djiMotorTxHandler.encodeAndSendCanData();
            tap::communication::serial::RefSerialData::Rx::RobotData data = drivers()->refSerial.getRobotData();
            uint16_t powerBuff = data.maxHp;
            
            ledTimer++;
            if (ledTimer > powerBuff) {
                ledTimer = 0;
                if (led) {
                    drivers()->leds.set(tap::gpio::Leds::A, true);     // Turn On LED
                    led = 0;
                } else {
                    drivers()->leds.set(tap::gpio::Leds::A, false);     // Turn Off LED
                    led = 1;
                }

                if (remote.isConnected()) {
                    drivers()->leds.set(tap::gpio::Leds::B, true);     // Turn On LED
                } else {
                    drivers()->leds.set(tap::gpio::Leds::B, false);     // Turn Off LED
                }

                if (drivers()->refSerial.getRefSerialReceivingData()) {
                    drivers()->leds.set(tap::gpio::Leds::C, true);     // Turn On LED
                } else {
                    drivers()->leds.set(tap::gpio::Leds::C, false);     // Turn Off LED
                }
            }
        }

        drivers()->canRxHandler.pollCanData();   // checks to see if a msg is waiting
        modm::delay_us(10);
    }

}