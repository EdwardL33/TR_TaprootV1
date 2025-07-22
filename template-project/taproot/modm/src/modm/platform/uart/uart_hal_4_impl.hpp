/*
 * Copyright (c) 2013-2014, 2016, Kevin Läufer
 * Copyright (c) 2013-2017, Niklas Hauser
 * Copyright (c) 2017, Fabian Greif
 * Copyright (c) 2017, Sascha Schade
 * Copyright (c) 2018, Christopher Durand
 * Copyright (c) 2018, Lucas Mösch
 * Copyright (c) 2021, Raphael Lehmann
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#ifndef MODM_STM32_UARTHAL_4_HPP
#	error 	"Don't include this file directly, use uart_hal_4.hpp instead!"
#endif
#include <modm/platform/clock/rcc.hpp>
#include <modm/math/algorithm/prescaler.hpp>

namespace modm::platform
{

// ----------------------------------------------------------------------------
void
UartHal4::enable()
{
	Rcc::enable<Peripheral::Uart4>();
}

void
UartHal4::disable()
{
	// TX, RX, Uart, etc. Disable
	UART4->CR1 = 0;
	Rcc::disable<Peripheral::Uart4>();
}

void
UartHal4::enableOperation()
{
	UART4->CR1 |= USART_CR1_UE;
}

void
UartHal4::disableOperation()
{
	UART4->CR1 &= ~USART_CR1_UE;
}

template< class SystemClock, modm::baudrate_t baudrate, modm::percent_t tolerance >
void
UartHal4::initialize(Parity parity, WordLength length)
{
	enable();
	disableOperation();

	constexpr uint32_t scalar = (baudrate * 16 > SystemClock::Uart4) ? 8 : 16;
	constexpr uint32_t max = ((scalar == 16) ? (1ul << 16) : (1ul << 15)) - 1ul;
	constexpr auto result = Prescaler::from_range(SystemClock::Uart4, baudrate, 1, max);
	modm::PeripheralDriver::assertBaudrateInTolerance< result.frequency, baudrate, tolerance >();

	uint32_t cr1 = UART4->CR1;
	// set baudrate and oversampling
	if constexpr (scalar == 16) {
		// When OVER8 = 0:, BRR[3:0] = USARTDIV[3:0].
		UART4->BRR = result.prescaler;
		cr1 &= ~USART_CR1_OVER8;
	} else {
		// When OVER8 = 1: BRR[15:4] = USARTDIV[15:4]
		// BRR[2:0] = USARTDIV[3:0] shifted 1 bit to the right. BRR[3] must be kept cleared.
		UART4->BRR = (result.prescaler & ~0b1111) | ((result.prescaler & 0b1111) >> 1);
		cr1 |= USART_CR1_OVER8;
	}
	// Set parity
	cr1 &= ~(USART_CR1_PCE | USART_CR1_PS);
	cr1 |= static_cast<uint32_t>(parity);

	// Set word length
#ifdef USART_CR1_M1
	cr1	&= ~(USART_CR1_M0 | USART_CR1_M1);
#else
	cr1	&= ~USART_CR1_M;
#endif
	cr1 |= static_cast<uint32_t>(length);

	UART4->CR1 = cr1;
}

void
UartHal4::write(uint16_t data)
{
	UART4->DR = data;
}

void
UartHal4::read(uint8_t &data)
{
	data = UART4->DR;
}

void
UartHal4::read(uint16_t &data)
{
	data = UART4->DR;
}

void
UartHal4::setTransmitterEnable(bool enable)
{
	if (enable) {
		UART4->CR1 |=  USART_CR1_TE;
	} else {
		UART4->CR1 &= ~USART_CR1_TE;
	}
}

void
UartHal4::setReceiverEnable(bool enable)
{
	if (enable) {
		UART4->CR1 |=  USART_CR1_RE;
	} else {
		UART4->CR1 &= ~USART_CR1_RE;
	}
}

bool
UartHal4::isReceiveRegisterNotEmpty()
{
	return UART4->SR & USART_SR_RXNE;
}

bool
UartHal4::isTransmitRegisterEmpty()
{
	return UART4->SR & USART_SR_TXE;
}

void
UartHal4::enableInterruptVector(bool enable, uint32_t priority)
{
	if (enable) {
		// Set priority for the interrupt vector
		NVIC_SetPriority(UART4_IRQn, priority);

		// register IRQ at the NVIC
		NVIC_EnableIRQ(UART4_IRQn);
	}
	else {
		NVIC_DisableIRQ(UART4_IRQn);
	}
}

void
UartHal4::setInterruptPriority(uint32_t priority)
{
	NVIC_SetPriority(UART4_IRQn, priority);
}

void
UartHal4::enableInterrupt(Interrupt_t interrupt)
{
	UART4->CR1 |= interrupt.value;
}

void
UartHal4::disableInterrupt(Interrupt_t interrupt)
{
	UART4->CR1 &= ~interrupt.value;
}

UartHal4::InterruptFlag_t
UartHal4::getInterruptFlags()
{
	return InterruptFlag_t( UART4->SR );
}

void
UartHal4::acknowledgeInterruptFlags(InterruptFlag_t flags)
{
	/* Interrupts must be cleared manually by accessing SR and DR.
	 * Overrun Interrupt, Noise flag detected, Framing Error, Parity Error
	 * p779: "It is cleared by a software sequence (an read to the
	 * USART_SR register followed by a read to the USART_DR register"
	 */
	if (flags.value & 0xful) {
		uint32_t tmp;
		tmp = UART4->SR;
		tmp = UART4->DR;
		(void) tmp;
	}
	(void) flags;	// avoid compiler warning
}

} // namespace modm::platform