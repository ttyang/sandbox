//Purpose:
//  Demo reducing along 1 axis of an array_dyn.
//
#include <boost/iostreams/utility/indent_scoped_ostreambuf.hpp>
#include <vector>
#include "reducer_variance.hpp"
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
  < typename Reducer=reducer_variance
  >
void reduce_test()
{
    std::cout<<"*************************\n";
    for( unsigned i_dir=dir_fwd; i_dir<dir_rev+1; ++i_dir)
    {
        dirs const dir_op=dirs(i_dir);
        std::cout<<"dir_op="<<dir_op<<"\n";
        indent_scope is;
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
        std::cout<<":Reducer for each axis:\n";
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
                        < Reducer const&
                        >
                        ( Reducer()
                        , sample_data
                        , oper_axis
                        )
                      );
                    std::cout<<":arr_reduce=\n";
                    std::cout<<arr_reduce<<".\n";
                }
            }//exit for(mean_axis...)
        }
    }//end for(i_dir...)
}

struct reduce_add_double
{
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
          double sum=0.0;
          std::cout<<sum;
          for(; beg!=end; ++beg)
          {
              double val=*beg;
              std::cout<<"+"<<val;
              sum+=val;
          }
          std::cout<<"="<<sum<<"\n";
          return sum;
      };
      
};

int main(void)
{
    ::boost::iostreams::indent_scoped_ostreambuf<> indent_cout(std::cout);
    reduce_test<reduce_add_double>();
    return 0;
}    
