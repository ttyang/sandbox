#ifndef BOOST_ITERATOR_PIPE_ITERATOR_FWD_HPP
#define BOOST_ITERATOR_PIPE_ITERATOR_FWD_HPP

#include <boost/utility/enable_if.hpp>
#include <boost/mpl/has_xxx.hpp>

#include <boost/iterator/iterator_facade.hpp>
#include <vector>

#include <boost/iterator/converter_concept.hpp>

namespace boost
{

namespace detail
{
    BOOST_MPL_HAS_XXX_TRAIT_DEF(max_output)

    template<typename P, typename Enable = void>
    struct convert_output_storage;

    template<typename P>
    struct convert_output_storage<P, typename ::boost::disable_if< has_max_output<P> >::type>
    {
        BOOST_CONCEPT_ASSERT((ConverterConcept<P>));
private:
        typedef std::vector<typename P::output_type> Values;
public:
        typedef std::back_insert_iterator<Values> output_iterator;
        
        const typename P::output_type& operator[](size_t i) const
        {
            return values[i];
        }
        
        size_t last_index() const
        {
            return values.size() - 1;
        }
        
        output_iterator out()
        {
            values.clear();
            return std::back_inserter(values);
        }
        
        void update(output_iterator)
        {
        }
        
    private:
        Values values;
    };
    
    template<typename P>
    struct convert_output_storage<P, typename boost::enable_if< has_max_output<P> >::type>
    {
        BOOST_CONCEPT_ASSERT((ConverterConcept<P>));
private:
        typedef typename P::output_type Value;
public:
        typedef Value* output_iterator;
        
        const Value& operator[](size_t i) const
        {
            return values[i];
        }
        
        size_t last_index() const
        {
            return last;
        }
        
        output_iterator out()
        {
            return values;
        }
        
        void update(output_iterator u)
        {
            last = u - values - 1;
        }
        
    private:
        Value values[P::max_output::value];
        size_t last;
    };
}

/** Iterator adapter that wraps a range to make it appear like a converted
 * one, by converting it step-by-step as it is advanced. */ 
template<typename It, typename Converter>
struct convert_iterator
	: iterator_facade<
		convert_iterator<It, Converter>,
		typename Converter::output_type,
		std::bidirectional_iterator_tag,
		const typename Converter::output_type
	>
{
    BOOST_CONCEPT_ASSERT((InputIterator<It>));
    BOOST_CONCEPT_ASSERT((ConverterConcept<Converter>));
    
    BOOST_CONCEPT_ASSERT((Convertible<typename InputIterator<It>::value_type, typename Converter::input_type>));
    
    convert_iterator() {} // singular
    
	convert_iterator(It begin_, It end_, It pos_, Converter p_) : pos(pos_), begin(begin_), end(end_), index(0), p(p_)
	{
		if(pos != end)
        {
            std::pair<It, typename detail::convert_output_storage<Converter>::output_iterator> pair =
                p.ltr(pos, end, values.out());
            next_pos = pair.first;
            values.update(pair.second);
        }
	}
	
	It base() const
	{
        BOOST_CONCEPT_ASSERT((ForwardIterator<It>));
        
		return pos;
	}

private:
	typedef typename Converter::output_type T;
	friend class boost::iterator_core_access;

	T dereference() const
	{
		return values[index];
	}
	
	void increment()
	{
		if(index != values.last_index())
		{
			index++;
		}
		else
		{			
			pos = next_pos;	
			if(pos != end)
            {
                std::pair<It, typename detail::convert_output_storage<Converter>::output_iterator> pair =
				    p.ltr(pos, end, values.out());
                next_pos = pair.first;
                values.update(pair.second);
            }
			index = 0;
		}
	}
	
	void decrement()
	{
        BOOST_CONCEPT_ASSERT((BidirectionalIterator<It>));
        
		if(index != 0)
		{
			index--;
		}
		else
		{
			next_pos = pos;	
            
            std::pair<It, typename detail::convert_output_storage<Converter>::output_iterator> pair =
                p.rtl(begin, pos, values.out());
            pos = pair.first;
            values.update(pair.second);
            
			index = values.last_index();
		}
	}
	
	bool equal(const convert_iterator& other) const
	{
		return pos == other.pos && index == other.index;
	}
	
	It pos;
	It next_pos;
	
	It begin;
	It end;
	size_t index;
	
	Converter p;
	
	detail::convert_output_storage<Converter> values;
};

/** Output Iterator adapter that wraps an output iterator to make one
 * that will convert its output before pushing it to the wrapped iterator. */
template<typename OutputIterator, typename OneManyConverter>
struct convert_output_iterator
{
    BOOST_CONCEPT_ASSERT((OutputIteratorConcept<OutputIterator, typename OneManyConverter::output_type>));
    BOOST_CONCEPT_ASSERT((OneManyConverterConcept<OneManyConverter>));
    
    typedef void                                                difference_type;
    typedef void                                                value_type;
    typedef convert_output_iterator<OutputIterator, OneManyConverter>*  pointer;
    typedef convert_output_iterator<OutputIterator, OneManyConverter>&  reference;
    typedef std::output_iterator_tag                            iterator_category;

    convert_output_iterator() {} // singular
    
	convert_output_iterator(OutputIterator pos_, OneManyConverter p_) : pos(pos_), p(p_)
	{
	}
	
	OutputIterator base() const
	{
		return pos;
	}
	
	const convert_output_iterator& operator*() const
	{
		return *this;
	}
	
	convert_output_iterator& operator++()
	{
		return *this;
	}
	
	convert_output_iterator& operator++(int)
	{
		return *this;
	}
	
    template<typename T>
	void operator=(T val) const
	{
		pos = p(val, pos);
	}
    
    bool operator==(const convert_output_iterator& other) const
    {
        return pos == other.pos;
    }
    
    bool operator!=(const convert_output_iterator& other) const
    {
        return pos != other.pos;
    }
	
private:	
	mutable OutputIterator pos;
	mutable OneManyConverter p;
};

} // namespace boost

#endif
