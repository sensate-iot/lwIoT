/*
 * I2C algorithm base class.
 * 
 * @author Michel Megens
 * @email  dev@bietje.net
 */

#pragma once

#include <lwiot/lwiot.h>
#include <lwiot/bytebuffer.h>
#include <lwiot/log.h>
#include <lwiot/error.h>
#include <lwiot/types.h>

#include <lwiot/stl/vector.h>
#include <lwiot/io/i2cmessage.h>

#define MAX_RETRIES 3

namespace lwiot
{
	class I2CAlgorithm {
	public:
		explicit I2CAlgorithm(int delay, uint32_t frequency);
		explicit I2CAlgorithm();
		explicit I2CAlgorithm(I2CAlgorithm&& other) = default;
		explicit I2CAlgorithm(const I2CAlgorithm& other) = default;
		virtual ~I2CAlgorithm() = default;

		I2CAlgorithm& operator=(const I2CAlgorithm& rhs) = default;
		I2CAlgorithm& operator=(I2CAlgorithm&& rhs) = default;

		const uint32_t& frequency() const;
		int delay() const;

		virtual void setFrequency(const uint32_t& freq);

		virtual ssize_t transfer(I2CMessage& msg) = 0;
		virtual ssize_t transfer(stl::Vector<I2CMessage>& msgs) = 0;

	protected:
		uint32_t _frequency;
		static constexpr int DefaultRetryDelay = 200;
		virtual void copy(const I2CAlgorithm& other);

	private:
		int _delay;

		static constexpr uint32_t DefaultFrequency = 100000UL;
	};
}
