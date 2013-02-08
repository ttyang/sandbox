//reducer_variance::operator(iter b,iter e) calculates variance of *b...*(e-1)
#ifndef REDUCER_VARIANCE_HPP_INCLUDED
#define REDUCER_VARIANCE_HPP_INCLUDED
#include <algorithm>//for_each

  template
  < typename Value
  >
struct reduce_add_one
/**@brief
 *  add values.
 */
{
      Value& 
    my_value
      ;
    reduce_add_one
    ( Value&a_value
    )
    : my_value
      ( a_value
      )
    {}
      Value 
    operator()(Value operand)
    {
        my_value+=operand;
        return my_value;
    }
};
  template
  < typename Value
  >
struct reduce_var_one
/**@brief
 *  sum square of deviation from a mean.
 */
{
      Value&
    my_value
      //result value
      ;
      Value const
    my_mean
      //the mean
      ;
    reduce_var_one
    ( Value&a_value//sum of square of devitation from mean
    , Value a_mean=0
    )
    : my_value
      ( a_value
      )
    , my_mean
      ( a_mean
      )
    {}
      Value 
    operator()(Value operand)
    {
          Value 
        deviation=operand-my_mean;
        my_value+=deviation*deviation;
        return my_value;
    }
};
struct reducer_variance
{
      unsigned const
    my_bessel_correction
      /**@brief
       *  == 0 or 1, indicating whether to use
       *  Bessel's correction:
       *    http://en.wikipedia.org/wiki/Bessel%27s_correction
       *  if == 0, don't correct.
       *  if == 1, then do correct.
       */
      ;
    reducer_variance
      ( bool a_bessel_correction=false
      )
      : my_bessel_correction(a_bessel_correction?1:0)
      {}
      template
      < typename Iter
      >
      typename Iter::value_type
    operator()
      ( Iter beg
      , Iter end
      )const
      /**@brief
       *  return value == variance of data in sample, *beg ... *(end-1).
       */
      {
            auto
          sample_size=beg.distance(end);
          assert(sample_size > my_bessel_correction);
              typedef
            typename Iter::value_type
          val_t
            ;
            val_t
          mean_v=0
            ;
            reduce_add_one<val_t>
          reduce_add_v(mean_v)
            ;
          std::for_each
            ( beg
            , end
            , reduce_add_v
            );
          mean_v=mean_v/sample_size
            //mean_v = mean of data in *beg ... *(end-1)
            ;
            val_t
          var_v;
            reduce_var_one<val_t>
          reduce_var_v(var_v,mean_v)
            ;
          std::for_each
            ( beg
            , end
            , reduce_var_v
            );
          var_v=var_v/(sample_size-my_bessel_correction)
            //var_v = variance of data in *beg ... *(end-1)
            ;
          return var_v;
      }
};
        
#endif
