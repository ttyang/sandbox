#ifndef BOOST_GENERIC_DETAIL_DEDUCTION_RESULT_HPP
#define BOOST_GENERIC_DETAIL_DEDUCTION_RESULT_HPP

#include <boost/generic/detail/dummy_type.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace generic { namespace detail {

// Error tags
class no_deduction {};
class ambiguous_deduction {};

template< class T >
struct is_not_deduction_error : boost::mpl::true_ {};

template<>
struct is_not_deduction_error< no_deduction > : mpl::false_ {};

template<>
struct is_not_deduction_error< ambiguous_deduction > : mpl::false_ {};

template<>
struct is_dummy_type< no_deduction > : mpl::true_ {};

template< class FirstDeduction >
struct is_different_deduction_
{
  template< class OtherDeduction >
  struct apply
    : mpl::not_
      < mpl::or_
        < is_dummy_type< OtherDeduction >
        , is_same< FirstDeduction, OtherDeduction >
        >
      > {};
};

template< class T > struct is_dummy_meta : is_dummy_type< typename T::type > {};

template< class L, class R >
struct is_same_second_meta : is_same< L, typename R::type > {};

template< class FirstDeduction, class OtherDeductionMeta >
struct deduction_result
  : mpl::if_c
    < is_dummy_type< FirstDeduction >::value
    , mpl::eval_if
      < is_dummy_meta< OtherDeductionMeta >
      , mpl::identity< FirstDeduction >
      , OtherDeductionMeta
      >
    , mpl::eval_if
      < is_dummy_meta< OtherDeductionMeta >
      , mpl::identity< FirstDeduction >
      , mpl::if_< is_same_second_meta< FirstDeduction, OtherDeductionMeta >
                , FirstDeduction
                , ambiguous_deduction
                >
      >
    >::type {};

// Takes a sequence and an iterator into that sequence and yields
//   ambiguous_deduction // if there is another deduction to a different type
template< class Sequence, class FirstDeductionIt >
struct deduction_result_verifier
{
private:
  typedef typename mpl::deref< FirstDeductionIt >::type first_deduction;
  typedef typename mpl::next< FirstDeductionIt >::type  range_begin;
  typedef typename mpl::end< Sequence >::type           range_end;

  typedef typename mpl::find_if
          < mpl::iterator_range< range_begin, range_end >
          , is_different_deduction_< first_deduction >
          >::type mismatched_deduced_type_it;
public:
  typedef typename mpl::if_
          < is_same< mismatched_deduced_type_it, range_end >
          , first_deduction
          , ambiguous_deduction
          >
          ::type type;
};



template< class Sequence >
struct deduction_result_
{
private:
  typedef typename mpl::find_if
          < Sequence, mpl::quote1< is_not_dummy_type > >::type
          first_deduced_type_it;
public:
  typedef typename mpl::eval_if
          < is_same< first_deduced_type_it
                   , typename mpl::end< Sequence >::type
                   >
          , mpl::identity< no_deduction >
          , deduction_result_verifier< Sequence, first_deduced_type_it >
          >::type type;
};

} } }

#endif // BOOST_GENERIC_DETAIL_DEDUCTION_RESULT_HPP
