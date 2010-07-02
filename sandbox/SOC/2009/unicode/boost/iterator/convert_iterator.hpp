#ifndef BOOST_ITERATOR_PIPE_ITERATOR_HPP
#define BOOST_ITERATOR_PIPE_ITERATOR_HPP

#include <boost/assert.hpp>
#include <utility>

#include <boost/range.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/times.hpp>
#include <boost/tuple/tuple.hpp>

#include <boost/concept/requires.hpp>
#include <boost/range/concepts.hpp>

#include <boost/iterator/convert_iterator_fwd.hpp>

#include <boost/type_traits.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/utility/enable_if.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost
{

/** CRTP Utility to define a \c \xmlonly<conceptname>OneManyConverter</conceptname>\endxmlonly. */
template<typename OneManyConverter>
struct one_many_converter
{
	template<typename In, typename Out>
	std::pair<In, Out>
	ltr(In begin, In end, Out out)
	{
		BOOST_ASSERT(begin != end);
		
		out = static_cast<OneManyConverter&>(*this)(*begin, out);
		return std::make_pair(++begin, out);
	}
	
	template<typename In, typename Out>
	std::pair<In, Out>
	rtl(In begin, In end, Out out)
	{
		BOOST_ASSERT(begin != end);
		
		out = static_cast<OneManyConverter&>(*this)(*--end, out);
		return std::make_pair(end, out);
	}
};

/* TODO: Make it work for types that don't expose max_output */
/** Model of \c \xmlonly<conceptname>Converter</conceptname>\endxmlonly
 * constructed from two models of \c \xmlonly<conceptname>Converter</conceptname>\endxmlonly
 * and that applies one after the other.
 * 
 * The second convert must require less input than the output of the first per
 * step for it to work. */
template<typename P1, typename P2>
struct multi_converter
{
    BOOST_CONCEPT_ASSERT((ConverterConcept<P1>));
    BOOST_CONCEPT_ASSERT((ConverterConcept<P2>));
    
    BOOST_CONCEPT_ASSERT((Convertible<typename P1::output_type, typename P2::input_type>));
    
    typedef typename P1::input_type input_type;
    typedef typename P2::output_type output_type;
    
    typedef typename mpl::times<
        typename P1::max_output,
        typename P2::max_output
    >::type max_output;
    
    multi_converter() {}
    multi_converter(P1 p1_, P2 p2_ = P2()) : p1(p1_), p2(p2_) {}
    
    template<typename In, typename Out>
    typename enable_if<
        mpl::and_<
            is_base_of<
                std::forward_iterator_tag,
                typename std::iterator_traits<Out>::iterator_category
            >,
            is_same<
                typename P1::output_type,
                typename P2::output_type
            >
        >,
        std::pair<In, Out>
    >::type
    ltr(In begin, In end, Out out)
    {
        Out b = out;
        
        std::pair<In, Out> pair = p1.ltr(begin, end, out);
        Out e = pair.second;
        
        do
        {
            tie(b, out) = p2.ltr(b, e, out);
        }
        while(b != e);
        
        return std::make_pair(pair.first, out);
    }
    
    template<typename In, typename Out>
    typename disable_if<
        mpl::and_<
            is_base_of<
                std::forward_iterator_tag,
                typename std::iterator_traits<Out>::iterator_category
            >,
            is_same<
                typename P1::output_type,
                typename P2::output_type
            >
        >,
        std::pair<In, Out>
    >::type
    ltr(In begin, In end, Out out)
    {
        typename P1::output_type buf[max_output::value];
        typename P1::output_type* b = buf;
        
        std::pair<In, typename P1::output_type*> pair = p1.ltr(begin, end, buf);
        typename P1::output_type* e = pair.second;
        
        do
        {
            tie(b, out) = p2.ltr(b, e, out);
        }
        while(b != e);
        
        return std::make_pair(pair.first, out);
    }
    
    template<typename In, typename Out>
    typename enable_if<
        mpl::and_<
            is_base_of<
                std::forward_iterator_tag,
                typename std::iterator_traits<Out>::iterator_category
            >,
            is_same<
                typename P1::output_type,
                typename P2::output_type
            >
        >,
        std::pair<In, Out>
    >::type rtl(In begin, In end, Out out)
    {
        Out b = out;
        
        std::pair<In, Out> pair = p1.rtl(begin, end, out);
        Out e = pair.second;
        
        do
        {
            tie(b, out) = p2.ltr(b, e, out);
        }
        while(b != e);
        
        return std::make_pair(pair.first, out);
    }
    
    template<typename In, typename Out>
    typename disable_if<
        mpl::and_<
            is_base_of<
                std::forward_iterator_tag,
                typename std::iterator_traits<Out>::iterator_category
            >,
            is_same<
                typename P1::output_type,
                typename P2::output_type
            >
        >,
        std::pair<In, Out>
    >::type rtl(In begin, In end, Out out)
    {
        typename P1::output_type buf[max_output::value];
        typename P1::output_type* b = buf;
        
        std::pair<In, typename P1::output_type*> pair = p1.rtl(begin, end, buf);
        typename P1::output_type* e = pair.second;
        
        do
        {
            tie(b, out) = p2.ltr(b, e, out);
        }
        while(b != e);
        
        return std::make_pair(pair.first, out);
    }
    
private:
    P1 p1;
    P2 p2;
};

template<typename P1, typename P2>
BOOST_CONCEPT_REQUIRES(
    ((ConverterConcept<P1>))
    ((ConverterConcept<P2>))
    ((Convertible<typename P1::output_type, typename P2::input_type>)),
    (multi_converter<P1, P2>)
) make_multi_converter(P1 p1, P2 p2)
{
    return multi_converter<P1, P2>(p1, p2);
}

/** Model of \c \xmlonly<conceptname>Converter</conceptname>\endxmlonly
 * that adapts the elements another \c \xmlonly<conceptname>Converter</conceptname>\endxmlonly
 * sees with a model of \c \xmlonly<conceptname>Converter</conceptname>\endxmlonly, assuming its \c max_output is \c 1. */
template<typename P1, typename P2>
struct converted_converter : P2
{
    BOOST_CONCEPT_ASSERT((ConverterConcept<P1>));
    BOOST_CONCEPT_ASSERT((ConverterConcept<P2>));
    
    BOOST_CONCEPT_ASSERT((Convertible<typename P1::output_type, typename P2::input_type>));
    
    BOOST_MPL_ASSERT(( mpl::equal_to< typename P1::max_output, mpl::int_<1> > ));
    
    typedef typename P1::input_type input_type;
    typedef typename P2::output_type output_type;
    
    converted_converter() {}
    converted_converter(P1 p1_, P2 p2_ = P2()) : P2(p2_), p1(p1_) {}
    
    template<typename In, typename Out>
    std::pair<In, Out> ltr(In begin, In end, Out out)
    {
        std::pair<
            convert_iterator<In, P1>,
            Out
        > pair = P2::ltr(
            make_convert_iterator(begin, end, begin, p1),
            make_convert_iterator(begin, end, end, p1),
            out
        );
        
        return std::make_pair(pair.first.base(), pair.second);
    }
    
    template<typename In, typename Out>
    std::pair<In, Out> rtl(In begin, In end, Out out)
    {
        std::pair<
            convert_iterator<In, P1>,
            Out
        > pair = P2::rtl(
            make_convert_iterator(begin, end, begin, p1),
            make_convert_iterator(begin, end, end, p1),
            out
        );
        return std::make_pair(pair.first.base(), pair.second);
    }
    
private:
    P1 p1;
};

template<typename P1, typename P2>
BOOST_CONCEPT_REQUIRES(
    ((ConverterConcept<P1>))
    ((ConverterConcept<P2>))
    ((Convertible<typename P1::output_type, typename P2::input_type>)),
    (converted_converter<P1, P2>)
) make_converted_converter(P1 p1, P2 p2)
{
    return converted_converter<P1, P2>(p1, p2);
}



/** Model of \c \xmlonly<conceptname>OneManyConverter</conceptname>\endxmlonly
 * that casts its input to its template parameter and writes it to its output. */
template<typename T>
struct cast_converter : one_many_converter< cast_converter<T> >
{
    typedef T input_type;
    typedef T output_type;
    typedef mpl::int_<1> max_output;
    
    template<typename U, typename Out>
    Out operator()(U in, Out out)
    {
        *out++ = static_cast<output_type>(in);
        return out;
    }
};

template<typename It, typename Converter>
BOOST_CONCEPT_REQUIRES(
    ((InputIterator<It>))
    ((ConverterConcept<Converter>))
    ((Convertible<typename InputIterator<It>::value_type, typename Converter::input_type>)),
    (convert_iterator<It, Converter>)
) make_convert_iterator(It begin, It end, It pos, Converter p)
{
	return convert_iterator<It, Converter>(begin, end, pos, p);
}

template<typename Range, typename Converter>
BOOST_CONCEPT_REQUIRES(
    ((SinglePassRangeConcept<Range>))
    ((ConverterConcept<Converter>))
    ((Convertible<typename range_value<Range>::type, typename Converter::input_type>)),
    (iterator_range<
	    convert_iterator<typename range_iterator<const Range>::type, Converter>
    >)
) converted(const Range& range, Converter p)
{
	return boost::make_iterator_range(
		make_convert_iterator(boost::begin(range), boost::end(range), boost::begin(range), p),
		make_convert_iterator(boost::begin(range), boost::end(range), boost::end(range), p)
	);
}

template<typename Range, typename Converter>
BOOST_CONCEPT_REQUIRES(
    ((SinglePassRangeConcept<Range>))
    ((ConverterConcept<Converter>))
    ((Convertible<typename range_value<Range>::type, typename Converter::input_type>)),
    (iterator_range<
	    convert_iterator<typename range_iterator<Range>::type, Converter>
    >)
) converted(Range& range, Converter p)
{
	return boost::make_iterator_range(
		make_convert_iterator(boost::begin(range), boost::end(range), boost::begin(range), p),
		make_convert_iterator(boost::begin(range), boost::end(range), boost::end(range), p)
	);
}

template<typename Range, typename Converter, typename OutputIterator>
BOOST_CONCEPT_REQUIRES(
    ((SinglePassRangeConcept<Range>))
    ((ConverterConcept<Converter>))
    ((Convertible<typename range_value<Range>::type, typename Converter::input_type>))
    ((OutputIteratorConcept<OutputIterator, typename Converter::output_type>)),
    (OutputIterator)
) convert(const Range& range, Converter convert, OutputIterator out)
{
    typedef typename boost::range_iterator<const Range>::type Iterator;
    
    Iterator begin = boost::begin(range);
    Iterator end = boost::end(range);
    
    while(begin != end)
    {
        std::pair<Iterator, OutputIterator> p = convert.ltr(begin, end, out);
        begin = p.first;
        out = p.second;
    }
    
    return out;
}

template<typename OutputIterator, typename OneManyConverter>
BOOST_CONCEPT_REQUIRES(
    ((OneManyConverterConcept<OneManyConverter>))
    ((OutputIteratorConcept<OutputIterator, typename OneManyConverter::output_type>)),
    (convert_output_iterator<OutputIterator, OneManyConverter>)
) converted_output(OutputIterator out, OneManyConverter p)
{
	return convert_output_iterator<OutputIterator, OneManyConverter>(out, p);
}

} // namespace boost

#endif
