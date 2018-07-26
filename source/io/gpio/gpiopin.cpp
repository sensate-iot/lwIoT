/*
 * GPIO pin wrapper.
 *
 * @author Michel Megens
 * @email  dev@bietje.net
 */

#include <lwiot/gpiopin.h>
#include <lwiot/gpiochip.h>

namespace lwiot
{
	GpioPin::GpioPin(int pin) : GpioPin(pin, gpio)
	{
	}

	GpioPin::GpioPin() : GpioPin(-1)
	{
	}

	GpioPin::GpioPin(int pin, GpioChip& chip) : _pin(pin), _chip(chip)
	{
		this->_open_drain = false;
	}

	GpioPin::~GpioPin() = default;

	GpioPin& GpioPin::operator =(int num)
	{
		this->_pin = num;
		return *this;
	}

	GpioPin& GpioPin::operator =(const GpioPin& pin)
	{
		this->_pin = pin.pin();
		this->_chip = pin._chip;

		return *this;
	}

	GpioPin::operator int() const
	{
		return this->_pin;
	}

	void GpioPin::input()
	{
		this->mode(INPUT);
	}

	void GpioPin::output()
	{
		this->mode(OUTPUT);
	}

	void GpioPin::setOpenDrain()
	{
		this->mode(OUTPUT_OPEN_DRAIN);
		this->write(true);
	}

	uint8_t GpioPin::shiftIn(const GpioPin& clk, bool lsb, uint8_t count, int delay)
	{
		return this->_chip.shiftIn(this->_pin, clk.pin(), lsb, count, delay);
	}

	int GpioPin::shiftOut(const GpioPin& clk, bool lsb, uint8_t value, uint8_t count, int delay)
	{
		return this->_chip.shiftOut(this->_pin, clk.pin(), lsb, value, count, delay);
	}

	void GpioPin::mode(const PinMode& mode)
	{
		if(mode == OUTPUT_OPEN_DRAIN)
			this->_open_drain = true;
		else
			this->_open_drain = false;

		this->_chip.mode(this->_pin, mode);
	}

	void GpioPin::write(bool value)
	{
		if(this->_open_drain)
			this->_chip.odWrite(this->_pin, value);
		else
			this->_chip.write(this->_pin, value);
	}

	void GpioPin::operator()(bool value)
	{
		this->write(value);
	}

	GpioPin& GpioPin::operator<<(bool value)
	{
		this->write(value);
		return *this;
	}

	bool GpioPin::read() const
	{
		return this->_chip.read(this->_pin);
	}

	GpioPin& GpioPin::operator>>(bool& value)
	{
		value = this->read();
		return *this;
	}

	bool GpioPin::operator()(void) const
	{
		return this->read();
	}

	GpioPin::operator bool() const
	{
		return this->read();
	}

	int GpioPin::pin() const
	{
		return this->_pin;
	}

	bool GpioPin::operator ==(const GpioPin& pin)
	{
		return this->_pin == pin.pin();
	}

	bool GpioPin::operator <(const GpioPin& pin)
	{
		return this->_pin < pin.pin();
	}

	bool GpioPin::operator >(const GpioPin& pin)
	{
		return this->_pin > pin.pin();
	}

	bool GpioPin::operator <=(const GpioPin& pin)
	{
		return this->_pin <= pin.pin();
	}

	bool GpioPin::operator >=(const GpioPin& pin)
	{
		return this->_pin >= pin.pin();
	}
}
