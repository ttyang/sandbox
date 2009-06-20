#ifndef BOOST_UTF_CODECS_HPP
#define BOOST_UTF_CODECS_HPP

#include <boost/assert.hpp>
#include <boost/throw_exception.hpp>
#include <stdexcept>
#ifndef BOOST_NO_STD_LOCALE
#include <sstream>
#include <ios>
#endif

#include <boost/unicode/surrogates.hpp>


namespace boost
{

namespace unicode
{

namespace detail
{
    
static const char16 high_surrogate_base = 0xD7C0u;
static const char16 low_surrogate_base = 0xDC00u;
static const char32 ten_bit_mask = 0x3FFu;

inline unsigned utf8_byte_count(uint8_t c)
{
   // if the most significant bit with a zero in it is in position
   // 8-N then there are N bytes in this UTF-8 sequence:
   uint8_t mask = 0x80u;
   unsigned result = 0;
   while(c & mask)
   {
      ++result;
      mask >>= 1;
   }
   return (result == 0) ? 1 : ((result > 4) ? 4 : result);
}

inline unsigned utf8_trailing_byte_count(uint8_t c)
{
   return utf8_byte_count(c) - 1;
}

inline void invalid_code_point(char32 val)
{
#ifndef BOOST_NO_STD_LOCALE
	std::stringstream ss;
	ss << "Invalid UTF-32 code point U+" << std::showbase << std::hex << (uint_least32_t)val << " encountered";
	std::out_of_range e(ss.str());
#else
	std::out_of_range e("Invalid UTF-32 code point encountered while trying to encode UTF-16 sequence");
#endif
	throw_exception(e);
}

template<typename Iterator>
inline void invalid_utf_sequence(Iterator begin, Iterator end)
{
#ifndef BOOST_NO_STD_LOCALE
	std::stringstream ss;
	ss << "Invalid UTF sequence " << std::showbase << std::hex;
	for(Iterator it = begin; it != end; ++it)
		ss << *it << " ";
	ss << "encountered while trying to decode UTF-32 sequence";
	std::out_of_range e(ss.str());
#else
	std::out_of_range e("Invalid UTF sequence encountered while trying to decode UTF-32 sequence");
#endif
	throw_exception(e);
}

} // namespace detail

struct u16_encoder
{
	typedef char16 output_type;
    static const int max_output = 2;
	
	template<typename OutputIterator>
	OutputIterator operator()(char32 v, OutputIterator out)
	{
		if(v >= 0x10000u)
		{
			if(v > 0x10FFFFu)
				detail::invalid_code_point(v);
				
			// split into two surrogates:
			output_type hi = static_cast<output_type>(v >> 10) + detail::high_surrogate_base;
			output_type lo = static_cast<output_type>(v & detail::ten_bit_mask) + detail::low_surrogate_base;
			
			BOOST_ASSERT(unicode::is_high_surrogate(hi));
			BOOST_ASSERT(unicode::is_low_surrogate(lo));
			
			*out++ = hi;
			*out++ = lo;
		}
		else
		{
			// 16-bit code point:
			output_type cp = static_cast<output_type>(v);

			// value must not be a surrogate:
			if(unicode::is_surrogate(cp))
				detail::invalid_code_point(v);
				
			*out++ = cp;
		}
		
		return out;
	}
};

struct u16_decoder
{
	typedef char32 output_type;
    static const int max_output = 1;
	
	template<typename In, typename Out>
	std::pair<In, Out>
	ltr(In begin, In end, Out out)
	{
		BOOST_ASSERT(begin != end);
		
		In it = begin;
		char32 value = *it;
		
		if(unicode::is_high_surrogate(value))
		{
			if(++it == end)
				detail::invalid_utf_sequence(begin, end);
			
			// precondition; next value must have be a low-surrogate:
         	char16 lo = *it;
         	if(!unicode::is_low_surrogate(lo))
            	detail::invalid_code_point(lo);
				
         	value = code_point(value, lo);
      	}
      	// postcondition; result must not be a surrogate:
      	if(unicode::is_surrogate(value))
			detail::invalid_code_point(static_cast<char16>(value));
		
		*out++ = value;
				
		return std::make_pair(++it, out);
	}
	
	template<typename In, typename Out>
	std::pair<In, Out>
	rtl(In begin, In end, Out out)
	{
		BOOST_ASSERT(begin != end);
		
		In it = --end;
		char32 value = *it;
		
		if(unicode::is_low_surrogate(value))
		{
			if(it == begin)
				detail::invalid_utf_sequence(begin, end);
			--it;
			
			char16 hi = *it;
         	if(!unicode::is_high_surrogate(hi))
            	detail::invalid_code_point(hi);
			
			value = code_point(hi, value);
      	}
      	// postcondition; result must not be a surrogate:
      	if(unicode::is_surrogate(value))
			detail::invalid_code_point(static_cast<char16>(value));
			
		*out++ = value;
		
		return std::make_pair(it, out);
	}
	
private:
	char32 code_point(char16 hi, char16 lo)
	{
		return   ((hi - detail::high_surrogate_base) << 10)
		       | (static_cast<char32>(static_cast<char16>(lo)) & detail::ten_bit_mask);
	}
};

struct u8_encoder
{
	typedef char output_type;
    static const int max_output = 4;
	
	template<typename OutputIterator>
	OutputIterator operator()(char32 c, OutputIterator out)
	{
		if(c > 0x10FFFFu)
			detail::invalid_code_point(c);

		if(c < 0x80u)
		{
			*out++ = static_cast<unsigned char>(c);
		}
		else if(c < 0x800u)
		{
			*out++ = static_cast<unsigned char>(0xC0u + (c >> 6));
			*out++ = static_cast<unsigned char>(0x80u + (c & 0x3Fu));
		}
		else if(c < 0x10000u)
		{
			*out++ = static_cast<unsigned char>(0xE0u + (c >> 12));
			*out++ = static_cast<unsigned char>(0x80u + ((c >> 6) & 0x3Fu));
			*out++ = static_cast<unsigned char>(0x80u + (c & 0x3Fu));
		}
		else
		{
			*out++ = static_cast<unsigned char>(0xF0u + (c >> 18));
			*out++ = static_cast<unsigned char>(0x80u + ((c >> 12) & 0x3Fu));
			*out++ = static_cast<unsigned char>(0x80u + ((c >> 6) & 0x3Fu));
			*out++ = static_cast<unsigned char>(0x80u + (c & 0x3Fu));
		}
		
		return out;
	}
};

struct u8_decoder
{
	typedef char32 output_type;
    static const int max_output = 1;
	
	template<typename In, typename Out>
	std::pair<In, Out>
	ltr(In begin, In end, Out out)
	{
		BOOST_ASSERT(begin != end);
		
		In it = begin;
		char32 value = *it;
		
		if((value & 0xC0u) == 0x80u)
			detail::invalid_utf_sequence(begin, end);
			
		// see how many extra byts we have:
		unsigned extra = detail::utf8_trailing_byte_count(value);
		// extract the extra bits, 6 from each extra byte:
		for(unsigned c = 0; c < extra; ++c)
		{
			if(++it == end)
				detail::invalid_utf_sequence(begin, end);
			
			value <<= 6;
			value += static_cast<unsigned char>(*it) & 0x3Fu;
		}
		
		// we now need to remove a few of the leftmost bits, but how many depends
		// upon how many extra bytes we've extracted:
		static const char32 masks[4] = 
		{
			0x7Fu,
			0x7FFu,
			0xFFFFu,
			0x1FFFFFu,
		};
		value &= masks[extra];
		
		// check the result:
		if(value > static_cast<char32>(0x10FFFFu))
			detail::invalid_utf_sequence(begin, end);
		
		*out++ = value;
				
		return std::make_pair(++it, out);
	}
	
	template<typename In, typename Out>
	std::pair<In, Out>
	rtl(In begin, In end, Out out)
	{
		BOOST_ASSERT(begin != end);
		
		In it = --end;
		char32 value = *it;
		
		// Keep backtracking until we don't have a trailing character:
		unsigned count = 0;
		while((*it & 0xC0u) == 0x80u)
		{					
			if(count >= 4 || it == begin)
				detail::invalid_utf_sequence(begin, end);
				
			--it;
			++count;
		}

		// now check that the sequence was valid:
		if(count != detail::utf8_trailing_byte_count(value))
			detail::invalid_utf_sequence(begin, end);
		
		out = ltr(it, end, out).second;
		return std::make_pair(it, out);
	}
};

} // namespace unicode

} // namespace boost

#endif
