/*
 * ESP32 digital to analog converter class.
 * 
 * @author Michel Megens
 * @email  dev@bietje.net
 */

#include <stdlib.h>
#include <stdint.h>
#include <lwiot.h>

#include <lwiot/dacchip.h>
#include <lwiot/esp32dacchip.h>

#include <driver/dac.h>

namespace lwiot
{
	Esp32DacChip::Esp32DacChip() : DacChip(2, 8, 3300)
	{ }

	void Esp32DacChip::begin()
	{
		DacChip::begin(false);
	}

	void Esp32DacChip::enable(int pin)
	{
		if(!this->_zero_pin)
			pin += 1;

		dac_output_enable(static_cast<dac_channel_t>(pin));
	}

	void Esp32DacChip::disable(int pin)
	{
		if(!this->_zero_pin)
			pin += 1;

		dac_output_disable(static_cast<dac_channel_t>(pin));
	}

	void Esp32DacChip::write(int pin, const size_t& voltage)
	{
		auto mapped = this->map(voltage);

		if(!this->_zero_pin)
			pin += 1;

		dac_output_voltage(static_cast<dac_channel_t>(pin), mapped);
	}
}

static lwiot::Esp32DacChip esp_dac;
lwiot::DacChip &dac = esp_dac;