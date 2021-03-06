/*
 * UART interface class.
 *
 * @author Michel Megens
 * @email  dev@bietje.net
 */

#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <lwiot.h>

#ifdef __cplusplus

#include <lwiot/io/gpiopin.h>
#include <lwiot/stream.h>
#include <lwiot/stl/string.h>
#include <lwiot/io/gpiochip.h>

#endif

#define SERIAL_5N1 0x8000010
#define SERIAL_6N1 0x8000014
#define SERIAL_7N1 0x8000018
#define SERIAL_8N1 0x800001c
#define SERIAL_5N2 0x8000030
#define SERIAL_6N2 0x8000034
#define SERIAL_7N2 0x8000038
#define SERIAL_8N2 0x800003c
#define SERIAL_5E1 0x8000012
#define SERIAL_6E1 0x8000016
#define SERIAL_7E1 0x800001a
#define SERIAL_8E1 0x800001e
#define SERIAL_5E2 0x8000032
#define SERIAL_6E2 0x8000036
#define SERIAL_7E2 0x800003a
#define SERIAL_8E2 0x800003e
#define SERIAL_5O1 0x8000013
#define SERIAL_6O1 0x8000017
#define SERIAL_7O1 0x800001b
#define SERIAL_8O1 0x800001f
#define SERIAL_5O2 0x8000033
#define SERIAL_6O2 0x8000037
#define SERIAL_7O2 0x800003b
#define SERIAL_8O2 0x800003f

#ifdef __cplusplus
namespace lwiot
{
	class Uart : public Stream {
	public:
		explicit Uart(int tx, int rx, long baud = 9600, uint32_t config = SERIAL_8N1);
		explicit Uart(const GpioPin& tx, const GpioPin& rx, long baud = 9600, uint32_t config = SERIAL_8N1);

		using Stream::write;
		using Stream::read;
		using Stream::available;

		virtual Stream& operator << (char x) override;
		virtual Stream& operator << (short x) override;
		virtual Stream& operator << (int  x) override;
		virtual Stream& operator << (const long&  x) override;
		virtual Stream& operator << (const long long&  x) override;
		virtual Stream& operator << (unsigned char x) override;
		virtual Stream& operator << (unsigned short x) override;
		virtual Stream& operator << (unsigned int  x) override;
		virtual Stream& operator << (const unsigned long&  x) override;
		virtual Stream& operator << (const unsigned long long&  x) override;
		virtual Stream& operator << (const double& flt) override;
		virtual Stream& operator << (const float& flt) override;
		virtual Stream& operator << (const String& str) override;
		virtual Stream& operator << (const char *cstr) override;

	protected:
		GpioPin _tx, _rx;
		long _baud;

	private:
		uint32_t _config;
	};
}
#endif
