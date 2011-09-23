#ifndef BOOST_ARRAY_STEPPER_MK_IOTA_HPP_INCLUDED
#define BOOST_ARRAY_STEPPER_MK_IOTA_HPP_INCLUDED
#include <cstdlib>
#include <vector>
#ifdef __GXX_EXPERIMENTAL_CXX0X__
#include <numeric>
#else
#include <boost/iterator/counting_iterator.hpp>
#endif
namespace boost
{
namespace array_stepper
{
  template
  < typename Value
  >
  std::vector<Value>
mk_iota
  ( Value first
  , Value last
  )
  {
      int size=last-first;
      std::vector<Value> result(abs(size));
      if(size>0)
      {
        #ifdef __GXX_EXPERIMENTAL_CXX0X__
          std::iota( result.begin(), result.end(), first);
        #else
          unsigned const n=size;
          for(unsigned i=0; i<n; ++i) result[i]=first+i;
        #endif
      }
      else
      {
        #ifdef __GXX_EXPERIMENTAL_CXX0X__
          std::iota( result.rbegin(), result.rend(), last);
        #else
          unsigned const n=-size;
          for(unsigned i=0; i<n; ++i) result[n-1-i]=last+i;
        #endif
      }
      return result;
  }
}//exit array_stepper namespace
}//exit boost namespace
#endif
