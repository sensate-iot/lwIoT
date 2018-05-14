/*
 * GPIO strategy for the ESP8266.
 *
 * @author Michel Megens
 * @email  dev@bietje.net
 */

#include <lwiot.h>

#include <esp/rtc_regs.h>

#include <lwiot/types.h>
#include <lwiot/gpiochip.h>
#include <lwiot/esp8266gpiochip.h>
#include <lwiot/log.h>

#define PIN16 16

namespace lwiot
{
	Esp8266GpioChip::Esp8266GpioChip() : GpioChip(PINS)
	{ }

	void Esp8266GpioChip::mode(int pin, const PinMode& mode)
	{
		if(pin == PIN16) {
			this->mode16(mode);
			return;
		}

		uint8_t _pin = pin;

		switch(mode) {
		case INPUT_PULLUP:
			GPIO.ENABLE_OUT_CLEAR = BIT(_pin);
			iomux_set_gpio_function(_pin, false);
			this->setPullup(_pin, true);
			break;

		case INPUT_NOPULLUP:
			GPIO.ENABLE_OUT_CLEAR = BIT(_pin);
			iomux_set_gpio_function(_pin, false);
			this->setPullup(_pin, false);
			break;

		case INPUT:
			GPIO.ENABLE_OUT_CLEAR = BIT(_pin);
			iomux_set_gpio_function(_pin, false);
			break;
		case OUTPUT:
			GPIO.CONF[_pin] &= ~GPIO_CONF_OPEN_DRAIN;
			GPIO.ENABLE_OUT_SET = BIT(_pin);
			iomux_set_gpio_function(_pin, true);
			break;

		case OUTPUT_OPEN_DRAIN:
			GPIO.CONF[_pin] |= GPIO_CONF_OPEN_DRAIN;
			GPIO.ENABLE_OUT_SET = BIT(_pin);
			iomux_set_gpio_function(_pin, true);
			break;

		default:
			print_dbg("Attempting to set invalid GPIO mode!\n");
			break;
		}
	}

	void Esp8266GpioChip::write(int pin, bool value)
	{
		uint8_t _pin = pin;

		if(_pin == 16) {
			RTC.GPIO_OUT = (RTC.GPIO_OUT & 0xfffffffe) | (value ? 1 : 0);
		} else if(value) {
			GPIO.OUT_SET = BIT(_pin) & GPIO_OUT_PIN_MASK;
		} else {
			GPIO.OUT_CLEAR = BIT(_pin) & GPIO_OUT_PIN_MASK;
		}
	}

	bool Esp8266GpioChip::read(int pin)
	{
		return false;
	}

	void Esp8266GpioChip::setOpenDrain(int _pin)
	{
	}

	void Esp8266GpioChip::odWrite(int pin, bool value)
	{
		this->write(pin, value);
	}

	void Esp8266GpioChip::setPullup(int pin, bool enable)
	{
		uint32_t flags = 0;

		if(enable)
			flags |= IOMUX_PIN_PULLUP;

		flags |= IOMUX_PIN_PULLUP_SLEEP;
		iomux_set_pullup_flags(gpio_to_iomux(pin), flags);
	}

	void Esp8266GpioChip::mode16(const PinMode& mode)
	{
		RTC.GPIO_CFG[3] = (RTC.GPIO_CFG[3] & 0xffffffbc) | 1;
		RTC.GPIO_CONF = (RTC.GPIO_CONF & 0xfffffffe) | 0;

		switch(mode) {
		case INPUT_NOPULLUP:
			RTC.GPIO_ENABLE = (RTC.GPIO_OUT & 0xfffffffe);
			this->setPullup(16, false);
			break;

		case INPUT_PULLUP:
			RTC.GPIO_ENABLE = (RTC.GPIO_OUT & 0xfffffffe);
			this->setPullup(16, true);
			break;

		case INPUT:
			RTC.GPIO_ENABLE = (RTC.GPIO_OUT & 0xfffffffe);
			break;

		case OUTPUT:
		case OUTPUT_OPEN_DRAIN:
			RTC.GPIO_ENABLE = (RTC.GPIO_OUT & 0xfffffffe) | 1;
			break;

		default:
			print_dbg("Attempting to set invalid GPIO mode!\n");
			break;
		}
	}
}