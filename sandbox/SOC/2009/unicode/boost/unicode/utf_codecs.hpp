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
	boost::throw_exception(e);
}

} // namespace detail

/** Model of \c OneManyPipe that converts a code point to a sequence
 * of UTF-16 code units. */
struct u16_encoder
{
	typedef char16 output_type;
    static const int max_output = 2;
	
    /** Throws std::out_of_range if \c v is not a valid code point. */
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

/** Model of \c Pipe that converts a sequence of UTF-16 code units into
 * a single code point. */
struct u16_decoder
{
	typedef char32 output_type;
    static const int max_output = 1;
	
    /** Throws std::out_of_range if [<tt>begin</tt>, <tt>end</tt>[ is not a valid UTF-16 range. */
	template<typename In, typename Out>
	std::pair<In, Out>
	ltr(In begin, In end, Out out)
	{
		BOOST_ASSERT(begin != end);
		
		In it = begin;
		char32 value = *it;
		
		if(unicode::is_high_surrogate(value))
		{
            // precondition; next value must have be a low-surrogate:
			if(++it == end)
				detail::invalid_utf_sequence(begin, end);
			
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
	
    /** Throws std::out_of_range if [<tt>begin</tt>, <tt>end</tt>[ is not a valid UTF-16 range. */
	template<typename In, typename Out>
	std::pair<In, Out>
	rtl(In begin, In end, Out out)
	{
		BOOST_ASSERT(begin != end);
        BOOST_ASSERT(!is_surrogate(*begin) || is_high_surrogate(*begin));
		
		In it = --end;
		char32 value = *it;
		
		if(unicode::is_low_surrogate(value))
		{
            // precondition; next value must have be a high-surrogate:
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

/** Model of \c BoundaryChecker that tells whether a position lies on a code
 * point boundary within a range of UTF-16 code units. */
struct u16_boundary
{
    template<typename In>
    bool operator()(In begin, In end, In pos)
    {
        BOOST_ASSERT(begin != end);
        BOOST_ASSERT(pos != begin);
        BOOST_ASSERT(pos != end);
        
        return !is_surrogate(*pos) || is_high_surrogate(*pos);
    }
};

/** Model of \c OneManyPipe that converts a code point to a sequence
 * of UTF-8 code units. */
struct u8_encoder
{
	typedef char output_type;
    static const int max_output = 4;
	
    /** Throws std::out_of_range if \c c is not a valid code point. */
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

/** Model of \c Pipe that converts a sequence of UTF-8 code units into
 * a single code point. */
struct u8_decoder
{
	typedef char32 output_type;
    static const int max_output = 1;

private:
    template<typename In>
    void check(bool test, In begin, In end)
    {
        if(!test)
            detail::invalid_utf_sequence(begin, end);
    }

public:	
    /** Throws std::out_of_range if [<tt>begin</tt>, <tt>end</tt>[ is not a valid UTF-8 range. */
	template<typename In, typename Out>
	std::pair<In, Out>
	ltr(In begin, In end, Out out)
	{
		BOOST_ASSERT(begin != end);
		In p = begin;
        
        unsigned char b0 = *(p++);
        if((b0 & 0x80) == 0)
        {
            char32 r = b0;
            *out++ = r;
            return std::make_pair(p, out);
        }
        
        check(p != end, begin, end);
        unsigned char b1 = *(p++);
        check((b1 & 0xc0) == 0x80, begin, end);
        if((b0 & 0xe0) == 0xc0)
        {
            char32 r = (b1 & 0x3f) | ((b0 & 0x1f) << 6);
            check(r >= 0x80, begin, end);
            *out++ = r;
            return std::make_pair(p, out);
        }
        
        check(p != end, begin, end);
        unsigned char b2 = *(p++);
        check((b2 & 0xc0) == 0x80, begin, end);
        if((b0 & 0xf0) == 0xe0)
        {
            char32 r = (b2 & 0x3f) | ((b1 & 0x3f) << 6) | ((b0 & 0x0f) << 12);
            check(r >= 0x800, begin, end);
            *out++ = r;
            return std::make_pair(p, out);
        }
        
        check(p != end, begin, end);
        unsigned char b3 = *(p++);
        check((b3 & 0xc0) == 0x80, begin, end);
        if((b0 & 0xf8) == 0xf0)
        {
            char32 r = (b3 & 0x3f) | ((b2 & 0x3f) << 6) | ((b1 & 0x3f) << 12) | ((b0 & 0x07) << 18);
            check(r >= 0x10000, begin, end);
            *out++ = r;
            return std::make_pair(p, out);
        }
        
        detail::invalid_utf_sequence(begin, end);
        return std::make_pair(p, out);
	}

    /** Throws std::out_of_range if [<tt>begin</tt>, <tt>end</tt>[ is not a valid UTF-8 range. */	
	template<typename In, typename Out>
	std::pair<In, Out>
	rtl(In begin, In end, Out out)
	{
		BOOST_ASSERT(begin != end);
		In p = end;
        
		unsigned char b0 = *(--p);
        if((b0 & 0x80) == 0)
        {
            char32 r = b0;
            *out++ = r;
            return std::make_pair(p, out);
        }
        
        check((b0 & 0xc0) == 0x80, begin, end);
        check(p != begin, begin, end);
        unsigned char b1 = *(--p);
        if((b1 & 0xe0) == 0xc0)
        {
            char32 r = (b0 & 0x3f) | ((b1 & 0x1f) << 6);
            check(r >= 0x80, begin, end);
            *out++ = r;
            return std::make_pair(p, out);
        }
        
        check((b1 & 0xc0) == 0x80, begin, end);
        check(p != begin, begin, end);
        unsigned char b2 = *(--p);
        if((b2 & 0xf0) == 0xe0)
        {
            char32 r = (b0 & 0x3f) | ((b1 & 0x3f) << 6) | ((b2 & 0x0f) << 12);
            check(r >= 0x800, begin, end);
            *out++ = r;
            return std::make_pair(p, out);
        }
        
        check((b2 & 0xc0) == 0x80, begin, end);
        check(p != begin, begin, end);
        unsigned char b3 = *(--p);
        if((b3 & 0xf8) == 0xf0)
        {
            char32 r = (b0 & 0x3f) | ((b1 & 0x3f) << 6) | ((b2 & 0x3f) << 12) | ((b3 & 0x07) << 18);
            check(r >= 0x10000, begin, end);
            *out++ = r;
            return std::make_pair(p, out);
        }
        
        detail::invalid_utf_sequence(begin, end);
        return std::make_pair(p, out);
	}
};


/** Model of \c BoundaryChecker that tells whether a position lies on a code
 * point boundary within a range of UTF-8 code units. */
struct u8_boundary
{
    template<typename In>
    bool operator()(In begin, In end, In pos)
    {
        BOOST_ASSERT(begin != end);
        BOOST_ASSERT(pos != begin);
        BOOST_ASSERT(pos != end);
        
        unsigned char c = *pos;
        return (c & 0x80) == 0 || (c & 0xc0) == 0xc0;
    }
};

} // namespace unicode

} // namespace boost

#endif
