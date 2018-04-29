/*
 * lwIoT string wrapper.
 *
 * @author Michel Megens, Arduino
 * @email  dev@bietje.net
 */

#ifndef LWIOT_STRING_H
#define LWIOT_STRING_H

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

namespace lwiot {
	class StringSumHelper;

	// The string class
	class String {
		// use a function pointer to allow for "if (s)" without the
		// complications of an operator bool(). for more information, see:
		// http://www.artima.com/cppsource/safebool.html
		typedef void (String::*StringIfHelperType)() const;

		void StringIfHelper() const {}

	public:
		// constructors
		// creates a copy of the initial value.
		// if the initial value is null or invalid, or if memory allocation
		// fails, the string will be marked as invalid (i.e. "if (s)" will
		// be false).
		String(const char *cstr = "");

		String(const String &str);

#if __cplusplus >= 201103L || defined(__GXX_EXPERIMENTAL_CXX0X__)

		String(String &&rval);

		String(StringSumHelper &&rval);

#endif

		explicit String(char c);

		explicit String(unsigned char, unsigned char base = 10);

		explicit String(int, unsigned char base = 10);

		explicit String(unsigned int, unsigned char base = 10);

		explicit String(long, unsigned char base = 10);

		explicit String(unsigned long, unsigned char base = 10);

		explicit String(float, unsigned char decimalPlaces = 2);

		explicit String(double, unsigned char decimalPlaces = 2);

		~String(void);

		// memory management
		// return true on success, false on failure (in which case, the string
		// is left unchanged).  reserve(0), if successful, will validate an
		// invalid string (i.e., "if (s)" will be true afterwards)
		unsigned char reserve(unsigned int size);

		inline unsigned int length(void) const { return len; }

		// creates a copy of the assigned value.  if the value is null or
		// invalid, or if the memory allocation fails, the string will be
		// marked as invalid ("if (s)" will be false).
		String &operator=(const String &rhs);

		String &operator=(const char *cstr);

#if __cplusplus >= 201103L || defined(__GXX_EXPERIMENTAL_CXX0X__)

		String &operator=(String &&rval);

		String &operator=(StringSumHelper &&rval);

#endif

		// concatenate (works w/ built-in types)

		// returns true on success, false on failure (in which case, the string
		// is left unchanged).  if the argument is null or invalid, the
		// concatenation is considered unsucessful.
		unsigned char concat(const String &str);

		unsigned char concat(const char *cstr);

		unsigned char concat(char c);

		unsigned char concat(unsigned char c);

		unsigned char concat(int num);

		unsigned char concat(unsigned int num);

		unsigned char concat(long num);

		unsigned char concat(unsigned long num);

		unsigned char concat(float num);

		unsigned char concat(double num);

		// if there's not enough memory for the concatenated value, the string
		// will be left unchanged (but this isn't signalled in any way)
		String &operator+=(const String &rhs) {
			concat(rhs);
			return (*this);
		}

		String &operator+=(const char *cstr) {
			concat(cstr);
			return (*this);
		}

		String &operator+=(char c) {
			concat(c);
			return (*this);
		}

		String &operator+=(unsigned char num) {
			concat(num);
			return (*this);
		}

		String &operator+=(int num) {
			concat(num);
			return (*this);
		}

		String &operator+=(unsigned int num) {
			concat(num);
			return (*this);
		}

		String &operator+=(long num) {
			concat(num);
			return (*this);
		}

		String &operator+=(unsigned long num) {
			concat(num);
			return (*this);
		}

		String &operator+=(float num) {
			concat(num);
			return (*this);
		}

		String &operator+=(double num) {
			concat(num);
			return (*this);
		}

		friend StringSumHelper &operator+(const StringSumHelper &lhs, const String &rhs);

		friend StringSumHelper &operator+(const StringSumHelper &lhs, const char *cstr);

		friend StringSumHelper &operator+(const StringSumHelper &lhs, char c);

		friend StringSumHelper &operator+(const StringSumHelper &lhs, unsigned char num);

		friend StringSumHelper &operator+(const StringSumHelper &lhs, int num);

		friend StringSumHelper &operator+(const StringSumHelper &lhs, unsigned int num);

		friend StringSumHelper &operator+(const StringSumHelper &lhs, long num);

		friend StringSumHelper &operator+(const StringSumHelper &lhs, unsigned long num);

		friend StringSumHelper &operator+(const StringSumHelper &lhs, float num);

		friend StringSumHelper &operator+(const StringSumHelper &lhs, double num);

		// comparison (only works w/ Strings and "strings")
		operator StringIfHelperType() const { return buffer ? &String::StringIfHelper : 0; }

		int compareTo(const String &s) const;

		unsigned char equals(const String &s) const;

		unsigned char equals(const char *cstr) const;

		unsigned char operator==(const String &rhs) const { return equals(rhs); }

		unsigned char operator==(const char *cstr) const { return equals(cstr); }

		unsigned char operator!=(const String &rhs) const { return !equals(rhs); }

		unsigned char operator!=(const char *cstr) const { return !equals(cstr); }

		unsigned char operator<(const String &rhs) const;

		unsigned char operator>(const String &rhs) const;

		unsigned char operator<=(const String &rhs) const;

		unsigned char operator>=(const String &rhs) const;

		unsigned char equalsIgnoreCase(const String &s) const;

		unsigned char startsWith(const String &prefix) const;

		unsigned char startsWith(const String &prefix, unsigned int offset) const;

		unsigned char endsWith(const String &suffix) const;

		// character acccess
		char charAt(unsigned int index) const;

		void setCharAt(unsigned int index, char c);

		char operator[](unsigned int index) const;

		char &operator[](unsigned int index);

		void getBytes(unsigned char *buf, unsigned int bufsize, unsigned int index = 0) const;

		void toCharArray(char *buf, unsigned int bufsize, unsigned int index = 0) const {
			getBytes((unsigned char *) buf, bufsize, index);
		}

		const char *c_str() const { return buffer; }

		char *begin() { return buffer; }

		char *end() { return buffer + length(); }

		const char *begin() const { return c_str(); }

		const char *end() const { return c_str() + length(); }

		// search
		int indexOf(char ch) const;

		int indexOf(char ch, unsigned int fromIndex) const;

		int indexOf(const String &str) const;

		int indexOf(const String &str, unsigned int fromIndex) const;

		int lastIndexOf(char ch) const;

		int lastIndexOf(char ch, unsigned int fromIndex) const;

		int lastIndexOf(const String &str) const;

		int lastIndexOf(const String &str, unsigned int fromIndex) const;

		String substring(unsigned int beginIndex) const { return substring(beginIndex, len); };

		String substring(unsigned int beginIndex, unsigned int endIndex) const;

		// modification
		void replace(char find, char replace);

		void replace(const String &find, const String &replace);

		void remove(unsigned int index);

		void remove(unsigned int index, unsigned int count);

		void toLowerCase(void);

		void toUpperCase(void);

		void trim(void);

		// parsing/conversion
		long toInt(void) const;

		float toFloat(void) const;

		double toDouble(void) const;

	protected:
		char *buffer;            // the actual char array
		unsigned int capacity;  // the array length minus one (for the '\0')
		unsigned int len;       // the String length (not counting the '\0')
	protected:
		void init(void);

		void invalidate(void);

		unsigned char changeBuffer(unsigned int maxStrLen);

		unsigned char concat(const char *cstr, unsigned int length);

		// copy and move
		String &copy(const char *cstr, unsigned int length);

#if __cplusplus >= 201103L || defined(__GXX_EXPERIMENTAL_CXX0X__)

		void move(String &rhs);

#endif
	};

	class StringSumHelper : public String {
	public:
		StringSumHelper(const String &s) : String(s) {}

		StringSumHelper(const char *p) : String(p) {}

		StringSumHelper(char c) : String(c) {}

		StringSumHelper(unsigned char num) : String(num) {}

		StringSumHelper(int num) : String(num) {}

		StringSumHelper(unsigned int num) : String(num) {}

		StringSumHelper(long num) : String(num) {}

		StringSumHelper(unsigned long num) : String(num) {}

		StringSumHelper(float num) : String(num) {}

		StringSumHelper(double num) : String(num) {}
	};
}

#endif //LWIOT_STRING_H
