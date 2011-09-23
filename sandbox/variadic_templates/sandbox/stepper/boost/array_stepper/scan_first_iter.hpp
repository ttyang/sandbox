#ifndef BOOST_ARRAY_STEPPER_SCAN_FIRST_ITER_HPP_INCLUDED
#define BOOST_ARRAY_STEPPER_SCAN_FIRST_ITER_HPP_INCLUDED
namespace boost
{
namespace array_stepper
{

  template
  < typename InputIter
  , typename OutputIter
  , typename Operations
  >
  OutputIter
scan_first_iter
  ( Operations& ops
  , InputIter first
  , InputIter last
  , OutputIter result
  )
{
    if(first!=last)
    {
        typedef typename OutputIter::value_type value_t;
        *result=ops(*first);
        for
          ( ++first
          ; first!=last
          ; ++first
          )
        {
            value_t next=ops(*result,*first);
            ++result;
            *result=next;
        }
    }
    return result;
}        
        
}//exit array_stepper namespace
}//exit boost namespace
#endif
