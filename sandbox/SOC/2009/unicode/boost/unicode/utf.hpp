#ifndef BOOST_UNICODE_UTF_HPP
#define BOOST_UNICODE_UTF_HPP

#include <boost/unicode/utf_codecs.hpp>
#include <boost/iterator/pipe_iterator.hpp>
#include <boost/iterator/consumer_iterator.hpp>

#include <boost/unicode/pipe_def.hpp>
#include <boost/detail/unspecified.hpp>

namespace boost
{
namespace unicode
{

/** INTERNAL ONLY */
#define BOOST_UNICODE_ENCODER_DEF(Name)                                \
BOOST_UNICODE_ONE_MANY_PIPE_DEF(Name##_encode, 0)

/* */

#ifdef BOOST_UNICODE_DOXYGEN_INVOKED
/** INTERNAL ONLY */
#define BOOST_UNICODE_DECODER_DEF(Name)                                \
BOOST_UNICODE_PIPE_DEF(Name##_decode, 0)                               \
/** Adapts the range of Name units \c range into a range of ranges of
Name units, each subrange being a decoded unit. */                     \
template<typename Range>                                               \
detail::unspecified<void> Name##_bounded(Range&& range);
#else
#define BOOST_UNICODE_DECODER_DEF(Name)                                \
BOOST_UNICODE_PIPE_DEF(Name##_decode, 0)                               \
                                                                       \
template<typename Range>                                               \
iterator_range<typename boost::detail::unspecified<                    \
    consumer_iterator<                                                 \
        typename range_iterator<const Range>::type,                    \
        pipe_consumer<unicode::Name##_decoder>                         \
    >                                                                  \
>::type> Name##_bounded(const Range& range)                            \
{                                                                      \
    return consumed(                                                   \
        range,                                                         \
        make_pipe_consumer(unicode::Name##_decoder())                  \
    );                                                                 \
}                                                                      \
                                                                       \
template<typename Range>                                               \
iterator_range<typename boost::detail::unspecified<                    \
    consumer_iterator<                                                 \
        typename range_iterator<Range>::type,                          \
        pipe_consumer<unicode::Name##_decoder>                         \
    >                                                                  \
>::type> Name##_bounded(Range& range)                                  \
{                                                                      \
    return consumed(                                                   \
        range,                                                         \
        make_pipe_consumer(unicode::Name##_decoder())                  \
    );                                                                 \
}                                                                      
#endif

BOOST_UNICODE_ENCODER_DEF(u16)
BOOST_UNICODE_DECODER_DEF(u16)

BOOST_UNICODE_ENCODER_DEF(u8)
BOOST_UNICODE_DECODER_DEF(u8)

BOOST_UNICODE_DECODER_DEF(utf)

template<typename ValueType, typename Range, typename OutputIterator>
OutputIterator utf_encode(const Range& range, OutputIterator out)
{
    return pipe(range, utf_encoder<ValueType>(), out);
}

#ifdef BOOST_UNICODE_DOXYGEN_INVOKED
template<typename ValueType, typename Range>
detail::unspecified<void> utf_encoded(Range&& range);
#else
template<typename ValueType, typename Range>
iterator_range<
    pipe_iterator<
        typename range_iterator<const Range>::type,
        utf_encoder<ValueType>
    >
> utf_encoded(const Range& range)
{
    return piped(range, utf_encoder<ValueType>());
}

template<typename ValueType, typename Range>
iterator_range<
    pipe_iterator<
        typename range_iterator<Range>::type,
        utf_encoder<ValueType>
    >
> utf_encoded(Range& range)
{
    return piped(range, utf_encoder<ValueType>());
}
#endif

template<typename ValueType, typename OutputIterator>
typename boost::detail::unspecified<
    pipe_output_iterator<
        OutputIterator,
        utf_encoder<ValueType>
    >
>::type utf_encoded_out(OutputIterator out)
{
    return piped_output(out, utf_encoder<ValueType>());
}

BOOST_UNICODE_ENCODER_DEF(latin1);

} // namespace unicode
} // namespace boost

#endif
