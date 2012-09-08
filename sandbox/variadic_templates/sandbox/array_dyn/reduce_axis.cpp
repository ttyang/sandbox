//Purpose:
//  Demo reducing along 1 axis of an array_dyn.
//
#include <boost/iostreams/utility/indent_scoped_ostreambuf.hpp>
#include <vector>
#include <algorithm>//for_each
#include "reduce_axis.hpp"

  template<typename Elem>
  std::ostream&
operator<<
  ( std::ostream&sout
  , std::vector<Elem>const&vec
  )
  {  
      sout<<"{ ";
      for(unsigned i=0; i< vec.size(); ++i)
      {
          if(0<i)sout<<", ";
          sout<<vec[i];
      }
      sout<<"}";
      return sout;
  }
  
struct indent_scope
{
    indent_scope()
    {
        std::cout<<indent_buf_in;
    }
    ~indent_scope()
    {
        std::cout<<indent_buf_out;
    }
};

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
        
int main(void)
{
    ::boost::iostreams::indent_scoped_ostreambuf<> indent_cout(std::cout);
    std::cout<<"*************************\n";
    dirs const dir_op=dir_rev;
    std::cout<<"dir_op="<<dir_op<<"\n";
    typedef double val_t;
    typedef array_dyn<val_t> array_t;
    typedef array_t::index_t index_t;
    std::vector<index_t> sample_shape({2,3,4});
    std::cout<<"sample_shape="<<sample_shape<<"\n";
    array_t sample_data(dir_op,sample_shape);
    unsigned const sample_size=sample_data.my_data.size();
    std::cout<<"my_data.size()="<<sample_size<<"\n";
    unsigned const value0=1000;
    for( unsigned i=0; i<sample_size; ++i)
    {
        sample_data.my_data[i]=value0+i;
    }
    unsigned const rank=sample_data.rank();
    std::cout<<"rank="<<rank<<"\n";
    std::cout<<"size()="<<sample_data.size()<<"\n";
    for(unsigned i=0;i<rank;++i)
    {
        std::cout<<"stride("<<i<<")="<<sample_data.stride(i)<<"\n";
        std::cout<<"  size("<<i<<")="<<sample_data.size(i)<<"\n";
    }
  #if 1
    std::cout<<"sample_data=\n";
    std::cout<<sample_data<<".\n";
  #endif
    std::cout<<":reducer_variance for each axis:\n";
    {
        indent_scope is;
        for(unsigned oper_axis=0; oper_axis<rank; ++oper_axis)
        {
            std::cout<<":oper_axis="<<oper_axis<<"\n";
            {
                indent_scope is;
                  array_t 
                arr_reduce
                  ( reduce_axis
                    < reducer_variance const&
                    >
                    ( reducer_variance()
                    , sample_data
                    , oper_axis
                    )
                  );
                std::cout<<"arr_reduce=\n";
                std::cout<<arr_reduce<<".\n";
            }
        }//exit for(mean_axis...)
    }
    return 0;
}    
