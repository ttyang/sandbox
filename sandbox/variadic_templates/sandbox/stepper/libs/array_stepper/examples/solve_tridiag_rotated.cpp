#include <boost/utility/trace_scope.hpp>
#include <boost/array_stepper/numeric/solve_tridiag.hpp>
#include <boost/array_stepper/array_dyn.hpp>
#include <boost/array_stepper/array_store_print.hpp>
#include <boost/assert.hpp>

using namespace boost::array_stepper;
void test_tridiag()
 /**@brief
  *  Test solve_tridiag with rotated rhs. 
  *  The test problem is that
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
      a0( numeric::tridiag_seq_seq_tag()
       , std::vector< vv_t>
         ( { { -3.0, -2.0, 1.0} //upper
           , {  5.0,  4.0, 3.0, 5.0} //diagonal
           , {  1.0, -1.0, 2.0} //lower
           }
         )
       );
      //std::cout<<"a0.size()="<<a0.size()<<"\na=\n"<<a0<<"\n";
    #if 1 
       value_t const
      r0[n]
      = {   7.0
        ,   6.0
        , - 4.0
        , -15.0
        }
        //The rhs (from [MarLop1991])
        ;
        std::size_t const 
      m=2
        //lengths for axes besides the solution axis.
        ;
        std::size_t const 
      rank=3
        //number of axes(including solution axis).
        ;
      auto rot_solve=[ =](std::size_t rot_soln)->void
      {
          std::vector<unsigned> 
        lengths_soln(rank,m)
          //shape of rhs and solution(the x's)
          ;
          std::size_t const 
        axis_soln=(rank+rot_soln)%rank
          //axis where solutions stored.
          ;
        lengths_soln[axis_soln]=n;
        std::cout<<"lengths_soln="<<lengths_soln<<"\n";
          std::size_t const 
        rot_lengths=(axis_soln+1)%rank
          //This is the rotation which rotates:
          //  lengths_soln[axis_soln]
          //to:
          //  lengths_soln[rank-1]
          ;
          typedef ::boost::array_stepper::array_dyn<value_t> 
        array_t;
          array_t 
        r(lengths_soln);
            typedef
          typename array_t::length_strides_t
        length_strides_t;
            typedef
          typename length_strides_t::value_type::stride_t
        stride_t;
            typedef
          index_stack_length_stride_crtp_indices<stride_t> 
        istk_t;
          length_strides_t const&
        length_strides_v=r.length_strides();
          istk_t
        istk_unrot
          ( length_strides_v.begin()
          , length_strides_v.end()
          );
          istk_t
        istk_rot(istk_unrot);
        istk_rot.rotate
          ( rot_lengths
          );
          auto const
        axis_inner=(axis_soln+rank-rot_lengths)%rank;
      #define TRACE_SOLVE_ROTATED_TRIDIAG 0
      #if TRACE_SOLVE_ROTATED_TRIDIAG||1
        std::cout
          <<":axis_soln="<<axis_soln
          <<":rank="<<rank
          <<":rot_lengths="<<rot_lengths
          <<":axis_inner="<<axis_inner
          <<"\n:istk_unrot="<<istk_unrot
          <<"\n:istk_rot="<<istk_rot
          <<"\n";
      #endif
        BOOST_ASSERT_MSG(axis_inner==rank-1,"axis_inner!=rank-1");
          auto const
        ibs=istk_rot[axis_inner]
          ;
          auto const
        stride_inner=ibs.stride_val()
          //stride of axis_inner axis
          ;
          auto const
        n_inner=ibs.length_val()
          //length of axis_inner axis
          ;
        istk_rot.axis_offsets_put
          ( axis_inner
          , 0        //lower border
          , n_inner-1//upper border
          )
          //Fix axis_inner index at it's min.
          ;
          auto const 
        n_outer=istk_rot.space();
      #if TRACE_SOLVE_ROTATED_TRIDIAG
        std::cout
          <<":n_outer="<<n_outer
          <<":n_inner="<<n_inner
          <<"\n";
      #endif
          auto
        r_iter=r.data().begin();
        {
              value_t
            factor=1.0;
            for
              ( int i_outer=0
              ; i_outer<n_outer
              ; ++i_outer
                , ++istk_rot
                , factor+=1.0
              )
              {
                  auto offset_inner=istk_rot.offset_space_val();
                #if TRACE_SOLVE_ROTATED_TRIDIAG
                  ::boost::trace_scope ts("init_outer");
                  std::cout
                    <<":i_outer="<<i_outer
                    <<":offset_inner="<<offset_inner
                    <<":istk_rot(axis_inner@min)="<<istk_rot
                    <<"\n";
                #endif
                  for
                    ( int i_inner=0
                    ; i_inner<n_inner
                    ; ++i_inner
                      , offset_inner+=stride_inner
                    )
                  {
                        value_t
                      val=factor*r0[i_inner];
                    #if TRACE_SOLVE_ROTATED_TRIDIAG
                      ::boost::trace_scope ts("init_inner");
                      std::cout
                        <<":i_inner="<<i_inner
                        <<":val="<<val
                        <<":offset_inner="<<offset_inner
                        <<":istk_rot(axis_inner@min)="<<istk_rot
                        <<"\n";
                    #endif
                      r_iter[offset_inner]=val;
                  }
              }
            #if 1
              std::cout<<"r=\n"<<r<<".\n";
            #endif
            #if 1
                array_iter_wrap<value_t> 
              r_w(r_iter,istk_rot);
              std::cout
                <<":istk_rot(axis_inner@min)="<<istk_rot<<"\n"
                <<":r_w=\n"
                <<r_w<<".\n";
            #endif
            #if 1
              istk_rot.axes_offsets_put(0,0);
                array_iter_wrap<value_t> 
              rb_w(r_iter,istk_rot);
              std::cout
                <<":istk_borders_rot="<<istk_rot<<"\n"
                <<":rb_w=\n"
                <<rb_w<<".\n";
            #endif
        }
        {
            trid_t
          a(a0);
          #if 1
          //#define INPLACE
          //ifdef INPLACE, then solution is done in-place.
          //i.e. r contains the solution; otherwise,
          //x (declared below) contains the solution.
          //
          #ifndef INPLACE
              array_t 
            x(lengths_soln);
          #endif
              numeric::solve_tridiag<value_t> 
            tds
              ( istk_rot
              , a
              , r_iter
            #ifdef INPLACE
              , r_iter
            #else
              , x.data().begin()
            #endif
              );
              value_t const 
            zero_tol=
            #if 0
              0.001
            #else
              std::numeric_limits<value_t>::epsilon()
            #endif
              ;
            if( tds.upper_triangulate_trid(zero_tol))
            {
                tds.upper_triangulate_rhs();
                tds.back_substitute();
                std::cout<<"***solution***\n";
              #ifdef INPLACE
                std::cout<<"r=\n"<<r<<".\n";
                array_iter_wrap<value_t> r_w(r_iter,istk_rot);
                std::cout<<"r_w=\n"
                  <<r_w<<".\n";
              #else
                std::cout<<"x=\n"<<x<<".\n";
                array_iter_wrap<value_t> x_w(x.data().begin(),istk_rot);
                std::cout<<"x_w=\n"
                  <<x_w<<".\n";
              #endif
            }
          #endif
        }
      #endif
    };
    for( std::size_t axis_rot=0; axis_rot<rank; ++axis_rot)
    {
        ::boost::trace_scope ts("rot_solve");
        std::cout<<":axis_rot="<<axis_rot<<"\n";
        rot_solve(axis_rot);
    }
  }   
  
int main()
{
    boost::iostreams::indent_scoped_ostreambuf<char> indent_outbuf(std::cout,2);
    test_tridiag();
    return 0;
}    
