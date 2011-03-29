#ifndef BOOST_UNICODE_COMBINING_HPP
#define BOOST_UNICODE_COMBINING_HPP

#include <boost/unicode/ucd/properties.hpp>
#include <boost/unicode/utf_codecs.hpp>

#include <boost/unicode/detail/boundary_segment_def.hpp>
#include <boost/iterator/segment_iterator.hpp>
#include <boost/iterator/convert_iterator.hpp>

#include <boost/detail/unspecified.hpp>
#include <algorithm>
#include <boost/range/adaptor/reversed.hpp>

#include <boost/throw_exception.hpp>
#include <stdexcept>
#ifndef BOOST_NO_STD_LOCALE
#include <sstream>
#include <ios>
#endif

namespace boost
{
namespace unicode
{

/** Maximum size of a combining character sequence in a stream-safe Unicode string */
typedef mpl::int_<31> combining_max;

namespace detail
{
    struct combining_pred
    {
        bool operator()(char32 lft, char32 rgt) const
        {
            return ucd::get_combining_class(lft) < ucd::get_combining_class(rgt);
        }
    };
    
    template<typename Size, typename Iterator, typename Comp>
    void stable_sort_bounded(Iterator begin, Iterator end, Comp comp = std::less<typename std::iterator_traits<Iterator>::value_type>())
    {
#if defined(__GLIBCPP__) || defined(__GLIBCXX__) || defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION) 
        typename std::iterator_traits<Iterator>::value_type buf[Size::value];
        return std::__stable_sort_adaptive(begin, end, buf, Size::value, comp);
#else
        return std::stable_sort(begin, end, comp);
#endif
    }
    
    template<typename Iterator>
    void not_stream_safe(Iterator begin, Iterator end)
    {
        typedef typename std::iterator_traits<Iterator>::value_type ValueType;
        typedef typename boost::make_unsigned<ValueType>::type UnsignedType;
        
#ifndef BOOST_NO_STD_LOCALE
        std::stringstream ss;
        ss << "Invalid Unicode stream-safe combining character sequence " << std::showbase << std::hex;
        for(Iterator it = begin; it != end; ++it)
            ss << (boost::uint_least32_t)(UnsignedType)*it << " ";
        ss << "encountered while trying to decompose UTF-32 sequence";
        std::out_of_range e(ss.str());
#else
        std::out_of_range e("Invalid Unicode stream-safe combining character sequence encountered while trying to decompose UTF-32 sequence");
#endif
        boost::throw_exception(e);
    }
    
    template<typename Iterator, typename OutputIterator>
    OutputIterator copy_bounded(Iterator begin, Iterator end, OutputIterator first, OutputIterator last)
    {
        for(Iterator it = begin; it != end; ++it)
        {
            if(first == last)
                not_stream_safe(begin, end);
            
            *first++ = *it;
        }
        return first;
    }

} // namespace detail

struct combine_boundary
{
    typedef char32 input_type;
    
    template<typename Iterator>
    bool operator()(Iterator begin, Iterator end, Iterator pos)
    {
        return ucd::get_combining_class(*pos) == 0;
    }
};

/** Model of \c \xmlonly<conceptname>Segmenter</conceptname>\endxmlonly
 * that segments combining character sequences. */
typedef boost::detail::unspecified<
    boost::boundary_segmenter<combine_boundary>
>::type combine_segmenter;
BOOST_SEGMENTER_DEF(boost::unicode::combine_segmenter, combine_segment)

BOOST_UNICODE_BOUNDARY_SEGMENT_DEF(u8, combine)
BOOST_UNICODE_BOUNDARY_SEGMENT_DEF(u16, combine)
BOOST_UNICODE_BOUNDARY_SEGMENT_DEF(utf, combine)

/** Model of \c \xmlonly<conceptname>Converter</conceptname>\endxmlonly
 * that canonically sorts a combining character sequence. */
struct combine_sorter
{
    typedef char32 input_type;
    typedef char32 output_type;
    typedef combining_max max_output;
    
    template<typename In, typename Out>
    Out ltr(In& begin, In end, Out out)
    {
        boost::iterator_range<
            In
        > sequence = *boost::make_segment_iterator(begin, end, begin, combine_segmenter());
        
        out = combine_sort_impl(sequence, out);
        begin = boost::end(sequence);
        return out;
    }
    
    template<typename In, typename Out>
    Out rtl(In begin, In& end, Out out)
    {
        boost::reverse_range<
            const boost::iterator_range<In>
        > sequence = boost::adaptors::reverse(
            *boost::prior(
                boost::make_segment_iterator(begin, end, end, combine_segmenter())
            )
        );
        
        out = combine_sort_impl(sequence, out);
        end = boost::end(sequence).base();
        return out;
    }
    
private:
    template<typename Range, typename Out>
    Out combine_sort_impl(const Range& range, Out out)
    {
        return combine_sort_impl(boost::begin(range), boost::end(range), out, (typename std::iterator_traits<Out>::iterator_category*)0);
    }

    template<typename In, typename Out>
    Out combine_sort_impl(In begin, In end, Out out, std::random_access_iterator_tag*)
    {
        Out out_pos = detail::copy_bounded(begin, end, out, out + max_output::value);
        detail::stable_sort_bounded<max_output>(out, out_pos, detail::combining_pred());
        return out_pos;
    }
    
    template<typename In, typename Out>
    Out combine_sort_impl(In begin, In end, Out out, std::output_iterator_tag*)
    {
        char32 buffer[max_output::value];
        char32* out_pos = detail::copy_bounded(begin, end, buffer, buffer + max_output::value);
        detail::stable_sort_bounded<max_output>(buffer, out_pos, detail::combining_pred());
        return std::copy(buffer, out_pos, out);
    }
};
BOOST_CONVERTER_DEF(boost::unicode::combine_sorter, combine_sort)
    
} // namespace unicode
} // namespace boost

#endif