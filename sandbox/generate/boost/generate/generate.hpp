// Copyright Fabian Bösch 2013
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/**
 *  @file 
 *  @brief This file contains the generate function and helper classes for making your generator a Range Generator.
 */

#ifndef BOOST_GENERATE_HPP
#define BOOST_GENERATE_HPP

#include <boost/mpl/if.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_class.hpp>
#include "is_stride_iterator.hpp"
#include <iterator>
#include <algorithm>
//#include <iostream>

namespace boost {

namespace range_generate {

#ifndef DOXYGEN_SHOULD_SKIP_THIS

namespace detail {

namespace type_introspection {

template <typename type>
struct has_member
{
    private:

    class yes { char m;};

    class no { yes m[2];};

    struct mixin
    {
        void operator()(){}
    };

    struct derived : public type, public mixin {};

    template <typename T, T t>  class helper{};

    template <typename U>
    static no deduce(U*, helper<void (mixin::*)(), &U::operator()>* = 0);

    static yes deduce(...);

    public:

    static const bool result = sizeof(yes) == sizeof(deduce((derived*)(0)));
};

template <typename type>
class void_exp_result{};

template <typename type, typename U>
U const& operator,(U const&, void_exp_result<type>);

template <typename type, typename U>
U& operator,(U&, void_exp_result<type>);

template <typename src_type, typename dest_type>
struct clone_constness
{
    typedef dest_type type;
};

template <typename src_type, typename dest_type>
struct clone_constness<const src_type, dest_type>
{
    typedef const dest_type type;
};


template <typename type, typename signature>
struct is_call_possible
{
    private:

    class yes {};

    class no { yes m[2]; };

    struct derived : public type
    {
        using type::operator();
        no operator()(...) const;
    };

    typedef typename clone_constness<type, derived>::type derived_type;

    template <typename T, typename due_type>
    struct return_value_check
    {
        static yes deduce(due_type);
        static no deduce(...);
        //static no deduce(no);
        //static no deduce(void_exp_result<type>);
    };

    template <typename T>
    struct return_value_check<T, void>
    {
        static yes deduce(...);
        static no deduce(no);
    };

    template <bool has, typename F>
    struct impl
    {
        static const bool value = false;
    };

    #define BOOST_TYPE_INTROSPECTION_IMPL_ARGS(z, n, text) *(text##n*)0

    #define BOOST_TYPE_INTROSPECTION_IMPL_SPEZIALIZATION(n)                                                                         \
    template <typename r, BOOST_PP_ENUM_PARAMS(n, typename arg)>                                                                    \
    struct impl<true, r(BOOST_PP_ENUM_PARAMS(n, arg))>                                                                              \
    {                                                                                                                               \
        static const bool value = sizeof(                                                                                           \
            return_value_check<type, r>::deduce(                                                                                    \
                (((derived_type*)0)->operator()(BOOST_PP_ENUM(n, BOOST_TYPE_INTROSPECTION_IMPL_ARGS, arg)),void_exp_result<type>()) \
            )                                                                                                                       \
        ) == sizeof(yes);                                                                                                           \
    };

    #define BOOST_TYPE_INTROSPECTION_IMPL(z, n, text) BOOST_TYPE_INTROSPECTION_IMPL_SPEZIALIZATION(n)

    BOOST_PP_REPEAT_FROM_TO(1, 10, BOOST_TYPE_INTROSPECTION_IMPL, empty)

    public:

    static const bool value = impl<has_member<type>::result,signature>::value;
};

} // type_introspection

template <typename T>
struct has_typedef_is_range_generator {
    typedef char yes[1];
    typedef char no[2];

    template <typename C>
    static yes& test(typename C::is_range_generator*);

    template <typename>
    static no& test(...);

    static const bool value = sizeof(test<T>(0)) == sizeof(yes);
};

template <class Generator, class Iterator, class Enable=void>
struct is_range_generator_impl : public boost::mpl::false_ {};

#ifndef BOOST_GENERATE_NO_EXPERIMENTAL_TYPE_INFERENCE

template <class Generator, class Iterator>
struct is_range_generator_impl< Generator, Iterator, typename boost::enable_if_c< boost::is_class<Generator>::value && !has_typedef_is_range_generator<Generator>::value >::type > 
: public 
	boost::mpl::eval_if<
        typename boost::is_unit_stride_iterator<Iterator>::type, // is Iterator a Unit Stride Iterator?
        typename boost::mpl::eval_if_c<
            type_introspection::is_call_possible<Generator,void(Iterator,Iterator)>::value, // Does void Generator::operator()(Iterator,iterator) exist?
            boost::mpl::true_,
            boost::mpl::false_
        >::type,
        boost::mpl::false_
    >::type
{};

#endif // BOOST_GENERATE_NO_EXPERIMENTAL_TYPE_INFERENCE

template <class Generator, class Iterator>
struct is_range_generator_impl<Generator, Iterator, typename boost::enable_if_c< has_typedef_is_range_generator<Generator>::value >::type > 
: public Generator::is_range_generator::template apply<Iterator>::type {};


} // detail

#endif // DOXYGEN_SHOULD_SKIP_THIS

/**
 *  @brief Template metafunction class for a Range Generator.
 *  
 *  This class can be used to make a generator match the requirements of
 *  the Range Generator Concept. In your generator declare: 
 *  @code typedef boost::range_generate::unit_stride_range_generator is_range_generator; @endcode
 * 
 *  The generator will then be a range generator for Iterators that satisfy
 *  the Unit Stride Iterator Concept.
 *
 */
struct unit_stride_range_generator
{
	/** 
	 *  @brief Metafunction
	 *
     *  Inherits from bool true constant type (e.g. boost::mpl::true_) if Iterator is a Unit Stride Iterator. 
	 *  Otherwise inherits from bool false constant type (e.g. boost::mpl::false_).
	 *
	 *  @tparam Iterator An Iterator type
	 */
    template <class Iterator>
    struct apply : public boost::is_unit_stride_iterator<Iterator>::type {};
};

/**
 *  @brief Template metafunction class for a Range Generator.
 *  
 *  This class can be used to make a generator match the requirements of
 *  the Range Generator Concept. In your generator declare: 
 *  @code typedef boost::range_generate::unit_stride_range_generator_type_checked<YourResultType> is_range_generator; @endcode
 * 
 *  The generator will then be a range generator for Iterators that satisfy
 *  the Unit Stride Iterator Concept and additionally have value type YourResultType.
 *
 *  @tparam ResultType Generator's result type.
 */
template <class ResultType>
struct unit_stride_range_generator_type_checked
{
	/** 
	 *  @brief Metafunction
	 *
     *  Inherits from bool true constant type (e.g. boost::mpl::true_) if Iterator is a Unit Stride Iterator and ResultType
	 *  is equal to Iterators value_type. Otherwise inherits from bool false constant type (e.g. boost::mpl::false_).
	 *
	 *  @tparam Iterator An Iterator type
	 */
    template <class Iterator>
    struct apply : public
        boost::mpl::eval_if<
            typename boost::is_unit_stride_iterator<Iterator>::type,
			typename boost::is_same<typename std::iterator_traits<Iterator>::value_type, ResultType>::type,
            boost::mpl::false_
        >::type
    {};
};

/**
 *  @brief Template metafunction class for a Range Generator.
 *  
 *  This class can be used to make a generator match the requirements of
 *  the Range Generator Concept. In your generator declare: 
 *  @code typedef boost::range_generate::constant_stride_range_generator is_range_generator; @endcode
 * 
 *  The generator will then be a range generator for Iterators that satisfy
 *  the Constant Stride Iterator Concept.
 *
 */
struct constant_stride_range_generator
{
	/** 
	 *  @brief Metafunction
	 *
     *  Inherits from bool true constant type (e.g. boost::mpl::true_) if Iterator is a Constant Stride Iterator. 
	 *  Otherwise inherits from bool false constant type (e.g. boost::mpl::false_).
	 *
	 *  @tparam Iterator An Iterator type
	 */
    template <class Iterator>
    struct apply : public boost::is_constant_stride_iterator<Iterator>::type {};
};

/**
 *  @brief Template metafunction class for a Range Generator.
 *  
 *  This class can be used to make a generator match the requirements of
 *  the Range Generator Concept. In your generator declare: 
 *  @code typedef boost::range_generate::constant_stride_range_generator_type_checked<YourResultType> is_range_generator; @endcode
 * 
 *  The generator will then be a range generator for Iterators that satisfy
 *  the Constant Stride Iterator Concept and additionally have value type YourResultType.
 *
 *  @tparam ResultType Generator's result type.
 */
template <class ResultType>
struct constant_stride_range_generator_type_checked
{
	/** 
	 *  @brief Metafunction
	 *
     *  Inherits from bool true constant type (e.g. boost::mpl::true_) if Iterator is a Constant Stride Iterator and ResultType
	 *  is equal to Iterators value_type. Otherwise inherits from bool false constant type (e.g. boost::mpl::false_).
	 *
	 *  @tparam Iterator An Iterator type
	 */
    template <class Iterator>
    struct apply : public
        boost::mpl::eval_if<
            typename boost::is_constant_stride_iterator<Iterator>::type,
			//typename boost::is_same<typename iterator_value_type<Iterator>::type, ResultType>::type,
			typename boost::is_same<typename std::iterator_traits<Iterator>::value_type, ResultType>::type,
            boost::mpl::false_
        >::type
    {};
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS

template<class Iterator, class Generator, class T>
void generate(Iterator first, Iterator last, Generator generator, boost::mpl::false_, T)
{
    // std::cout << "standard generate" << std::endl;
    std::generate(first,last,generator);
}

template<class Iterator, class Generator, class T>
void generate(Iterator first, Iterator last, Generator generator, boost::mpl::true_, T)
{
    // std::cout << "range generate" << std::endl;
    generator(first,last);
}

template <class UnitStrideIterator, class Generator>
void generate(UnitStrideIterator first, UnitStrideIterator last, Generator generator, boost::mpl::false_, boost::mpl::true_)
{
	// std::cout << "for generate" << std::endl;
	typedef typename std::iterator_traits<UnitStrideIterator>::difference_type difference_type;
	typedef typename std::iterator_traits<UnitStrideIterator>::pointer pointer;

	const difference_type n(last-first);
	pointer data(&*first);
	for ( difference_type i=0; i<n; ++i) data[i] = generator();
}

#endif // DOXYGEN_SHOULD_SKIP_THIS

} // range_genererate

/** @brief Traits class for checking whether a Generator is a Range Generator.
 *
 *  The default behaviour for this traits class is to check whether the Generator class
 *  exposes a publicly accessible type named is_range_generator.
 *  If such a nested type exists, it is assumed to model a metafunction class and it's 
 *  apply metafunction will be invoked with the Iterator type: @code Generator::is_range_generator::apply<Iterator> @endcode
 *  and the return type will be forwarded to the traits class.
 *  Otherwise the Generator type will be inspected (experimental feature). If it has defined a range function call and the Iterator type models
 *  the concept of a Unit Stride Iterator, it is assumed that the Generator is indeed a Range Generator.
 *  If none of the above are true, the Generator is not a Range Generator.
 *
 *  @tparam Generator A Generator type (function object)
 *  @tparam Iterator  An Iterator type
 */
template <class Generator, class Iterator>
struct is_range_generator : public
	boost::range_generate::detail::is_range_generator_impl<Generator,Iterator>::type
{};

/**
 *  @brief Generates values for a range.
 *
 *  This function dispatches to a range generate version iff the @c Generator
 *  used is a Range Generator for the @c Iterator employed. Otherwise the
 *  std::generate version is used.
 *
 *	@tparam Iterator An Iterator type
 *  @tparam Generator A Generator type (function object)
 *  @param first Beginning of the range to be generated
 *  @param last End of the range to be generated
 *  @param generator An instance of a @c Generator type
 */
template<class Iterator, class Generator>
void generate(Iterator first, Iterator last, Generator generator)
{
	typedef typename boost::is_range_generator<Generator,Iterator>::type dispatch_type1;
	typedef typename boost::is_unit_stride_iterator<Iterator>::type dispatch_type2;
	range_generate::generate(first,last,generator,boost::mpl::bool_<dispatch_type1::value>(), boost::mpl::bool_<dispatch_type2::value>());
}

} // boost

#endif // BOOST_GENERATE_HPP

