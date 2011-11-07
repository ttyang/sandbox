#include <boost/utility/trace_scope.hpp>
#include <boost/array_stepper/numeric/solve_tridiag.hpp>
#include <boost/array_stepper/array_dyn.hpp>
#include <boost/array_stepper/array_store_print.hpp>
using namespace boost::array_stepper;
void test_tridiag()
 /**@brief
  *  Test tridigonal solution.  The test problem is that
  *  from Example 3.2E on page 136 of [MarLop1991].
  **@references
  *  [MarLop1991]
  *    Maron, Melvin J.
  *    Lopez, Robert J.
  *    _Numerical Analysis: A Practical Approach_
  *    Wadsworth(1991)
  */
  {
      std::size_t const n=4;
      typedef double value_t;
      typedef numeric::tridiag<value_t> trid_t;
      typedef std::vector<value_t> vv_t;
        trid_t 
      a( numeric::tridiag_seq_seq_tag()
       , std::vector< vv_t>
         ( { { -3.0, -2.0, 1.0} //upper
           , {  5.0,  4.0, 3.0, 5.0} //diagonal
           , {  1.0, -1.0, 2.0} //lower
           }
         )
       );
      std::cout<<"a.size()="<<a.size()<<"\na=\n"<<a<<"\n";
    #if 1 
       value_t const
      r0[n]
      = {   7.0
        ,   6.0
        , - 4.0
        , -15.0
        };
      std::size_t const m=2;
      std::size_t const rank=3;
      boost::array<unsigned,rank> lengths_soln={{m,m,n}};
      typedef ::boost::array_stepper::array_dyn<value_t> array_t;
      array_t r(lengths_soln);
      value_t const zero_tol=
      #if 0
        0.001
      #else
        std::numeric_limits<value_t>::epsilon()
      #endif
        ;
      {
              typedef
            typename array_t::length_strides_t
          length_strides_t
            ;
              typedef
            typename length_strides_t::value_type::stride_t
          stride_t
            ;
              typedef
            index_stack_length_stride_crtp_indices<stride_t> 
          istk_t
            ;
            length_strides_t const&
          length_strides_v=r.length_strides()
            ;
            istk_t
          istk_outer
            ( length_strides_v.begin()
            , length_strides_v.end()-1
            )
            ;
          auto const n_outer=istk_outer.space();
            istk_t
          istk_inner
            ( length_strides_v.end()-1
            , length_strides_v.end()
            )
            ;
            value_t
          ten_power=1.0
            ;
          auto const n_inner=istk_inner.space();
          std::cout<<":n_outer="<<n_outer<<":n_inner="<<n_inner<<"\n";
          for(int i_outer=0; i_outer<n_outer; ++i_outer, ++istk_outer, ten_power*=10.0)
          {
              std::cout<<"ten_power="<<ten_power<<"\n";
              for(int i_inner=0; i_inner<n_inner; ++i_inner, ++istk_inner)
              {
                    auto const 
                  o = r.offset()
                    + istk_outer.offset_space_val()
                    + istk_inner.offset_space_val()
                    ;
                  r.data()[o]=ten_power*r0[i_inner];
              }
          }
          std::cout<<"r=\n"<<r<<".\n";
      }
      {
              typedef
            typename array_t::length_strides_t
          length_strides_t
            ;
              typedef
            typename length_strides_t::value_type::stride_t
          stride_t
            ;
              typedef
            index_stack_length_stride_crtp_indices<stride_t> 
          istk_t
            ;
            length_strides_t const&
          length_strides_v=r.length_strides()
            ;
            istk_t 
          istk_v
            ( length_strides_v.begin()
            , length_strides_v.end()
            );
          trid_t la(a);
          array_t lr(r);
          array_t x(lengths_soln);
          numeric::solve_tridiag<value_t> tds( istk_v, la, lr.data().begin(), x.data().begin());
          if( tds.upper_triangulate_trid(zero_tol))
          {
              tds.upper_triangulate_rhs();
              tds.back_substitute();
              std::cout<<"x=\n"<<x<<".\n";
          }
      }
    #endif      
  }   
  
int main()
{
    boost::iostreams::indent_scoped_ostreambuf<char> indent_outbuf(std::cout,2);
    test_tridiag();
    return 0;
}    
