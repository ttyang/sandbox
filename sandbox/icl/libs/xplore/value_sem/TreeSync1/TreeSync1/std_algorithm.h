#pragma once

#include <algorithm>

namespace std
{

template <class InputIterator1, class InputIterator2, class OutputIterator, class Compare, class Merger>
  OutputIterator general_union(InputIterator1 first1, InputIterator1 last1,
                               InputIterator2 first2, InputIterator2 last2,
                               OutputIterator result, Compare less, Merger merger)
{
  while (true)
  {
    if (first1==last1) return std::copy(first2,last2,result);
    if (first2==last2) return std::copy(first1,last1,result);

    if (less(*first1, *first2)) { *result = *first1; ++first1; }
    else if (less(*first2, *first1)) { *result = *first2; ++first2; }
    else {
      // *first1 == *first2
      *result = merger(*first1, *first2);
      ++first1; ++first2; 
    }
    ++result;
  }
}


template<class Less>
struct Minimum : std::binary_function<typename Less::first_argument_type, typename Less::first_argument_type, typename Less::first_argument_type>
{
  typedef typename Less::first_argument_type Comparable;
  typedef typename Less::first_argument_type first_argument_type;

  Comparable operator()(Comparable const& lhs, Comparable const& rhs)
  { return Less()(rhs,lhs) ? rhs : lhs; }
};

template<class Less>
struct Maximum : std::binary_function<typename Less::first_argument_type, typename Less::first_argument_type, typename Less::first_argument_type>
{
  typedef typename Less::first_argument_type Comparable;
  typedef typename Less::first_argument_type first_argument_type;

  Comparable operator()(Comparable const& lhs, Comparable const& rhs)
  { return Less()(lhs,rhs) ? rhs : lhs; }
};


} //std