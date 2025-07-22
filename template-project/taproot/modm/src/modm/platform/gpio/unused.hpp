/*
 * Copyright (c) 2017-2018, Niklas Hauser
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#ifndef MODM_STM32_GPIO_PIN_UNUSED_HPP
#define MODM_STM32_GPIO_PIN_UNUSED_HPP

#include "base.hpp"
#include <modm/architecture/interface/gpio.hpp>

namespace modm
{

namespace platform
{

/**
 * Dummy implementation of an I/O pin.
 *
 * This class can be used when a pin is not required. All functions
 * are dummy functions which do nothing. `read()` will always
 * return `false`.
 *
 * For example when creating a software SPI with the modm::SoftwareSimpleSpi
 * class and the return channel (MISO - Master In Slave Out) is not needed,
 * a good way is to use this class as a parameter when defining the
 * SPI class.
 *
 * Example:
 * @code
 * #include <modm/architecture/platform.hpp>
 *
 * namespace pin
 * {
 *     typedef GpioOutputD7 Clk;
 *     typedef GpioOutputD5 Mosi;
 * }
 *
 * modm::SoftwareSpiMaster< pin::Clk, pin::Mosi, GpioUnused > Spi;
 *
 * ...
 * Spi::write(0xaa);
 * @endcode
 *
 * @author	Fabian Greif
 * @author	Niklas Hauser
 * @ingroup	modm_platform_gpio
 */
class GpioUnused : public Gpio, public ::modm::GpioIO
{
public:
	using Output = GpioUnused;
	using Input = GpioUnused;
	using IO = GpioUnused;
	using Type = GpioUnused;
	static constexpr bool isInverted = false;
	static constexpr Port port = Port(-1);
	static constexpr uint8_t pin = uint8_t(-1);
	static constexpr uint16_t mask = 0;

protected:
	/// @cond
	static void setAlternateFunction(uint8_t) {}
	static void setAnalogInput() {}
	/// @endcond

public:
	// GpioOutput
	// start documentation inherited
	static void setOutput() {}
	static void setOutput(bool) {}
	static void set() {}
	static void set(bool) {}
	static void reset() {}
	static void toggle() {}
	static bool isSet() { return false; }
	// stop documentation inherited
	static void configure(OutputType, OutputSpeed = OutputSpeed::MHz50) {}
	static void setOutput(OutputType, OutputSpeed = OutputSpeed::MHz50) {}

	// GpioInput
	// start documentation inherited
	static void setInput() {}
	static bool read() { return false; }
	// end documentation inherited
	static void configure(InputType) {}
	static void setInput(InputType) {}
	// External Interrupts
	static void enableExternalInterrupt() {}
	static void disableExternalInterrupt() {}
	static void enableExternalInterruptVector(const uint32_t) {}
	static void disableExternalInterruptVector() {}
	static void setInputTrigger(const InputTrigger) {}
	static bool getExternalInterruptFlag() { return false; }
	/// Reset the interrupt flag in the interrupt routine.
	static void acknowledgeExternalInterruptFlag() {}

	// GpioIO
	// start documentation inherited
	static Direction getDirection() { return Direction::Special; }
	// end documentation inherited
	static void lock() {}
	static void disconnect() {}

public:
	/// @cond
	template< Peripheral _ >
	struct Af1
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Af1;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Af2
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Af2;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Bk1io0
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Bk1io0;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Bk1io1
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Bk1io1;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Bk1io3
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Bk1io3;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Bk1ncs
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Bk1ncs;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Bk2ncs
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Bk2ncs;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Bkin
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Bkin;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Cec
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Cec;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Ch1
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Ch1;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Ch1n
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Ch1n;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Ch2
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Ch2;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Ch2n
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Ch2n;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Ch3
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Ch3;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Ch3n
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Ch3n;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Ch4
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Ch4;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Ck
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Ck;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Ckin
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Ckin;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Clk
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Clk;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Cmd
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Cmd;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Cts
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Cts;
		static void connect() {}
	};
	template< Peripheral _ >
	struct D0
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::D0;
		static void connect() {}
	};
	template< Peripheral _ >
	struct D1
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::D1;
		static void connect() {}
	};
	template< Peripheral _ >
	struct D10
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::D10;
		static void connect() {}
	};
	template< Peripheral _ >
	struct D11
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::D11;
		static void connect() {}
	};
	template< Peripheral _ >
	struct D2
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::D2;
		static void connect() {}
	};
	template< Peripheral _ >
	struct D3
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::D3;
		static void connect() {}
	};
	template< Peripheral _ >
	struct D4
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::D4;
		static void connect() {}
	};
	template< Peripheral _ >
	struct D5
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::D5;
		static void connect() {}
	};
	template< Peripheral _ >
	struct D6
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::D6;
		static void connect() {}
	};
	template< Peripheral _ >
	struct D7
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::D7;
		static void connect() {}
	};
	template< Peripheral _ >
	struct D8
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::D8;
		static void connect() {}
	};
	template< Peripheral _ >
	struct D9
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::D9;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Dm
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Dm;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Dp
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Dp;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Etr
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Etr;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Fsa
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Fsa;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Fsb
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Fsb;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Hsync
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Hsync;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Id
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Id;
		static void connect() {}
	};
	template< Peripheral _ >
	struct In0
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::In0;
		static void connect() {}
	};
	template< Peripheral _ >
	struct In1
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::In1;
		static void connect() {}
	};
	template< Peripheral _ >
	struct In10
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::In10;
		static void connect() {}
	};
	template< Peripheral _ >
	struct In11
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::In11;
		static void connect() {}
	};
	template< Peripheral _ >
	struct In12
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::In12;
		static void connect() {}
	};
	template< Peripheral _ >
	struct In13
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::In13;
		static void connect() {}
	};
	template< Peripheral _ >
	struct In14
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::In14;
		static void connect() {}
	};
	template< Peripheral _ >
	struct In15
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::In15;
		static void connect() {}
	};
	template< Peripheral _ >
	struct In2
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::In2;
		static void connect() {}
	};
	template< Peripheral _ >
	struct In3
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::In3;
		static void connect() {}
	};
	template< Peripheral _ >
	struct In4
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::In4;
		static void connect() {}
	};
	template< Peripheral _ >
	struct In5
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::In5;
		static void connect() {}
	};
	template< Peripheral _ >
	struct In6
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::In6;
		static void connect() {}
	};
	template< Peripheral _ >
	struct In7
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::In7;
		static void connect() {}
	};
	template< Peripheral _ >
	struct In8
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::In8;
		static void connect() {}
	};
	template< Peripheral _ >
	struct In9
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::In9;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Jtck
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Jtck;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Jtdi
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Jtdi;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Jtdo
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Jtdo;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Jtms
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Jtms;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Jtrst
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Jtrst;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Mck
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Mck;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Mclkb
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Mclkb;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Mco1
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Mco1;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Mco2
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Mco2;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Miso
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Miso;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Mosi
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Mosi;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Nss
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Nss;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Osc32in
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Osc32in;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Osc32out
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Osc32out;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Oscin
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Oscin;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Oscout
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Oscout;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Out1
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Out1;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Out2
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Out2;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Pixclk
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Pixclk;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Refin
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Refin;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Rts
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Rts;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Rx
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Rx;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Sck
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Sck;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Scka
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Scka;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Sckb
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Sckb;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Scl
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Scl;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Sd
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Sd;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Sda
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Sda;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Sdb
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Sdb;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Smba
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Smba;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Sof
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Sof;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Swclk
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Swclk;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Swdio
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Swdio;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Swo
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Swo;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Traced0
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Traced0;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Tx
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Tx;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Ulpick
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Ulpick;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Ulpid0
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Ulpid0;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Ulpid1
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Ulpid1;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Ulpid2
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Ulpid2;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Ulpid3
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Ulpid3;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Ulpid4
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Ulpid4;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Ulpid5
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Ulpid5;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Ulpid6
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Ulpid6;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Ulpid7
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Ulpid7;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Ulpidir
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Ulpidir;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Ulpinxt
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Ulpinxt;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Ulpistp
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Ulpistp;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Vbus
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Vbus;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Vsync
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Vsync;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Wkup0
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Wkup0;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Wkup1
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Wkup1;
		static void connect() {}
	};
	template< Peripheral _ >
	struct Ws
	{
		using Gpio = GpioUnused;
		static constexpr Gpio::Signal Signal = Gpio::Signal::Ws;
		static void connect() {}
	};
	/// @endcond
};

} // namespace platform

} // namespace modm

#endif // MODM_STM32_GPIO_PIN_UNUSED_HPP