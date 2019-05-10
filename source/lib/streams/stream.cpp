/*
 * Virtual data stream definition.
 *
 * @author Michel Megens
 * @email  dev@bietje.net
 */

#include <stdlib.h>
#include <lwiot.h>
#include <stdint.h>

#include <lwiot/types.h>
#include <lwiot/log.h>
#include <lwiot/stream.h>

namespace lwiot {
	Stream::Stream() : Stream(1000)
	{
	}

	Stream::Stream(const time_t& timeout)
	{
		this->_timeout = timeout;
	}

	ssize_t Stream::read(String& output)
	{
		char x;
		ssize_t bytes;
		time_t tmo = lwiot_tick_ms() + this->_timeout;

		bytes = 0;
		while((x = this->read()) != '\n') {
			if(this->_timeout > 0 && lwiot_tick_ms() > tmo) {
				return 0;
			}

			bytes++;
			output += x;
		}

		return bytes;
	}

	ssize_t Stream::write(const String& data)
	{
		return this->write((const uint8_t*)data.c_str(), (ssize_t)data.length());
	}

	void Stream::setTimeout(time_t tmo)
	{
		this->_timeout = tmo;
	}

	String Stream::readString()
	{
		String retval;

		this->read(retval);
		return retval;
	}

	String Stream::readStringUntil(char terminator)
	{
		String retval;
		int c;
		time_t tmo = lwiot_tick_ms() + this->_timeout;

		c = this->read();

		while(c >= 0 && c != terminator) {
			if(this->_timeout > 0 && lwiot_tick_ms() > tmo) {
				return String("");
			}

			retval += (char)c;
			c = this->read();
		}


		return retval;
	}
}
