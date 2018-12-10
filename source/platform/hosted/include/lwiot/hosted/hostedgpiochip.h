/*
 * Hosted (Windows / Unix) GPIO chip.
 *
 * @author Michel Megens
 * @email  dev@bietje.net
 */

#pragma once

#include <vector>
#include <map>

#include <stdlib.h>
#include <assert.h>
#include <lwiot.h>

#include <lwiot/gpiochip.h>
#include <lwiot/error.h>
#include <lwiot/pair.h>
#include <lwiot/string.h>

namespace lwiot
{
	class HostedGpioChip : public GpioChip {
	public:
		explicit HostedGpioChip(int pins) noexcept;
		virtual ~HostedGpioChip() = default;

		void mode(int pin, const PinMode& mode) override;
		void write(int pin, bool value) override;
		bool read(int pin) const override;

		void setOpenDrain(int pin) override;
		void odWrite(int pin, bool value) override;
		void attachIrqHandler(int pin, irq_handler_t handler, IrqEdge edge) override;
	};
}