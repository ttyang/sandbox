#ifndef BOOST_ARRAY_STEPPER_NUMERIC_SOLVE_TRIDIAG_HPP_INCLUDED
#define BOOST_ARRAY_STEPPER_NUMERIC_SOLVE_TRIDIAG_HPP_INCLUDED
#include <boost/array_stepper/index_stack_length_stride_crtp.hpp>
#include <boost/array_stepper/array_dyn.hpp>
#include <boost/array_stepper/vector_print.hpp>
#include <boost/iostreams/utility/indent_scoped_ostreambuf.hpp>
#include <iomanip>
#include <limits>
#define SOLVE_TRIDIAG_VERIFY
#ifdef  SOLVE_TRIDIAG_VERIFY
#include <boost/assert.hpp>
#include <boost/array_stepper/numeric/almost_equal_relative.hpp>
#include <boost/array_stepper/array_store_print.hpp>
#endif

namespace boost
{
namespace array_stepper
{
namespace numeric
{

  struct
tridiag_seq_seq_tag
  /**@brief
   *  Just used to select tridiag CTOR.
   */
{};
  template
  < typename Value
  >
  struct
tridiag
  /**@brief
   *  Tridiagonal matrix of Size rows and Size columns
   *  of elements with type, Value.
   */
{
        typedef
      std::vector<Value>
    seq_t
      ;
      template
      < typename SeqSeq
      >
    tridiag
      ( tridiag_seq_seq_tag const&
      , SeqSeq const&ss
      )
      : my_size(ss[1].size())
      , my_seq(my_size*3-2)
      {
          unsigned m=0;
          for(unsigned i=0; i<my_size-1; ++i,++m)
          {
              my_seq[m]=ss[0][i];
              //std::cout<<"my_seq["<<m<<"]="<<my_seq[m]<<"\n";
          }
          for(unsigned i=0; i<my_size  ; ++i,++m) 
          {
              my_seq[m]=ss[1][i];
              //std::cout<<"my_seq["<<m<<"]="<<my_seq[m]<<"\n";
          }
          for(unsigned i=0; i<my_size-1; ++i,++m) 
          {
              my_seq[m]=ss[2][i];
              //std::cout<<"my_seq["<<m<<"]="<<my_seq[m]<<"\n";
          }
      }
    tridiag
      ( std::size_t a_size
      )
      : my_size(a_size)
      , my_seq(my_size*3-2)
      {}
 private:      
      std::size_t
    u_o //upper diagonal offset in my_seq
      (
      )const
      {
          return 0;
      }
      std::size_t
    d_o //middle diagonal offset in my_seq
      (
      )const
      {
          return u_o()+my_size-1;
      }
      std::size_t
    l_o //lower diagonal offset in my_seq
      (
      )const
      {
          return d_o()+my_size;
      }
      std::size_t
    u_i //translate upper diagonal row to index in my_seq.
      ( std::size_t row
      )const
      {
          return u_o()+row;
      }
      std::size_t
    d_i //translate middle diagonal row to index in my_seq.
      ( std::size_t row
      )const
      {
          return d_o()+row;
      }
      std::size_t
    l_i //translate lower diagonal row to index in my_seq.
      ( std::size_t row
      )const
      {
          return l_o()+row-1;
      }
 public:      
      Value&
    u ( std::size_t i
      )
      {
        return my_seq[u_i(i)];
      }
      Value const&
    u ( std::size_t i
      )const
      {
        return my_seq[u_i(i)];
      }
      Value&
    d ( std::size_t i
      )
      {
        return my_seq[d_i(i)];
      }
      Value const&
    d ( std::size_t i
      )const
      {
        return my_seq[d_i(i)];
      }
      Value&
    l ( std::size_t i
      )
      {
        return my_seq[l_i(i)];
      }
      Value const&
    l ( std::size_t i
      )const
      {
        return my_seq[l_i(i)];
      }
      std::size_t
    size()const
      {
        return my_size;
      }
 private:
      std::size_t
    my_size
      ;
      seq_t
    my_seq
      ;
    tridiag
      (
      )
      : my_size(0)
      {
      }
};

  template
  < typename Value
  >
  std::ostream&
operator<<
  ( std::ostream& sout
  , tridiag<Value>const& a
  )
  {
      std::size_t const size=a.size();
      sout<<"{ ";
      for(unsigned i=0; i<size; ++i)
      {
          if(0<i) sout<<", ";
          sout<<indent_buf_in;
          sout<<"{ ";
          for(unsigned j=0; j<size; ++j)
          {
              if(0<j) sout<<", ";
              unsigned const w=5;
              if     (i  ==j+1)  sout<<std::setw(w)<<a.l(i);
              else if(i  ==j  )  sout<<std::setw(w)<<a.d(i);
              else if(i+1==j  )  sout<<std::setw(w)<<a.u(i);
              else               sout<<std::setw(w)<<"_";
          }
          sout<<"}\n";
          sout<<indent_buf_out;
      }
      sout<<"}\n";
      return sout;
  }          

  template
  < typename Value
  >
  struct
solve_tridiag
  /**@brief
   *  Solver for tridiagonal system.
   **@reference:
   *  [MarLop1991A3.2E]
   *    ALGORITHM 3.2E on page 137 of:
   *      Maron, Melvin J.
   *      Lopez, Robert J.
   *      _Numerical Analysis: A Practical Approach_
   *      Wadsworth(1991)
   */
  {
          typedef
        Value
      value_t
        ;
          typedef
        tridiag<value_t>
      tridiag_t
        ;
          typedef
        array_dyn<Value>
      array_t
        ;
          typedef
        typename array_t::length_strides_t
      length_strides_t
        ;
          typedef
        typename array_t::data_t::iterator
      arr_data_iter_t
        ;
          typedef
        typename length_strides_t::value_type::stride_t
      stride_t
        ;
          typedef
        index_stack_length_stride_crtp_indices<stride_t> 
      istk_t
        ;
      solve_tridiag
        ( istk_t const& a_istk
        , tridiag_t& a_trid//the matrix
        , arr_data_iter_t a_r//rhs
        , arr_data_iter_t a_x//unknown
        )
        : my_istk(a_istk)
        , my_trid(a_trid) 
        , my_r(a_r)
        , my_x(a_x)
      #ifdef SOLVE_TRIDIAG_VERIFY
        , o_r( my_istk.space_outer())
        , o_trid(my_trid)
      #endif
        {
          #ifdef SOLVE_TRIDIAG_VERIFY
          //Save the original rhs in o_r to verify solution later.
            unsigned const n_node=my_istk.space();
            for
              ( unsigned i_node=0
              ; i_node<n_node
              ; ++my_istk, ++i_node
              )
            {
                int offset_istk=my_istk.offset_space_val();
                o_r[offset_istk]=my_r[offset_istk];
            }
          #endif
        }
        
        bool
      upper_triangulate_trid
        ( value_t zero_tol=2.0*std::numeric_limits<value_t>::epsilon()
        )
        /**@brief
         *  Convert this->my_trid to upper triangular form.
         *  (Actually, the lower digonal not zeroed, but it's
         *  not used in back_substitute, so, that doesn't matter).
         */
        {
        /*MAINTENANCE_NOTE:2011-10-22:Larry Evans:
         *  [MarLop1991A3.2E] combined this code with that of
         *  upper_triangulate_rhs.  That's not done here because
         *  the rhs in this case may have more than just 1
         *  dimension.  IOW, instead of a vector, it may be
         *  an n-dimensional array. OTOH, this->my_trid always
         *  remains an nxn tridiagonal matrix.
         */
            std::size_t const size=my_trid.size();
          //#define TRACE_UPPER_TRIANGULATE_TRID
          #ifdef TRACE_UPPER_TRIANGULATE_TRID
            ::boost::trace_scope ts("upper_triangulate_trid");
            std::cout<<"size="<<size<<"\n";
          #endif
            unsigned m=0;
            for( ; m<size-1; ++m)
            {
              #ifdef TRACE_UPPER_TRIANGULATE_TRID
                //std::cout<<":m="<<m<<":d="<<my_trid.d(m)<<"\n";
              #endif
                if(std::abs(my_trid.d(m))<zero_tol)
                {
                    std::cerr<<"Zero on diagonal "<<m<<". upper_triangulate_trid failed.\n";
                    return false;
                }
                my_trid.l(m+1)=my_trid.l(m+1)/my_trid.d(m);
                my_trid.d(m+1)=my_trid.d(m+1)-my_trid.l(m+1)*my_trid.u(m);
            }
            if(std::abs(my_trid.d(m))<zero_tol)
            {
                std::cerr<<"Zero on diagonal "<<m<<". upper_triangulate_trid failed.\n";
                return false;
            }
          #ifdef TRACE_UPPER_TRIANGULATE_TRID
            std::cout
              <<"upper_triangulate_trid=\n"<<my_trid
              ;
          #endif
            return true;
        }  
        void
      upper_triangulate_rhs
        (
        )
        /**@brief
         *  Make change to my_r corresponding to change made by
         *  upper_triangulate_trid to my_trid.
         **@requires
         *  this->upper_trigulate_trid(a_tol) has been called.
         */
        {
              auto const
            ibs=my_istk[my_istk.rank()-1]
              ;
              auto const
            stride_last=ibs.stride_val()
              //stride of last axis
              ;
              auto const
            n_last=ibs.length_val()
              //length of last axis
              ;
              unsigned const 
            n_node=my_istk.space()
              //number of nodes in mesh.
              ;
          //#define TRACE_UPPER_TRIANGULATE_RHS
          #ifdef TRACE_UPPER_TRIANGULATE_RHS
            ::boost::trace_scope ts("upper_triangulate_rhs");
            std::cout
              <<":n_node="<<n_node
              <<":n_last="<<n_last
              <<":stride_last="<<stride_last
              <<":rotation="<<my_istk.rotation()
              <<"\n"
              <<"{ "
              ;
          #endif
            unsigned i_node;
            for
              ( i_node=0
              ; i_node<n_node
              ; ++my_istk
                , ++i_node
              )
             /*MAINTENANCE_NOTE:2011-10-22:Larry Evans:
              *  I *think* the similar MAINTENANCE_NOTE in
              *  back_substitute applies here.  IOW, this
              *  i_node loop can be parallelized.
              */
            {
              #ifdef TRACE_UPPER_TRIANGULATE_RHS
                using ::operator<<;
                if(0<i_node)std::cout<<", ";
                std::cout<<indent_buf_in;
                std::cout<<"{ ";
                std::cout
                  <<":r"<<my_istk.indices()
                  <<"="<<my_r[my_istk.offset_space_val()]
                  <<"\n"
                  ;
              #endif
                for
                  ( int i_last=0
                  ; i_last<n_last-1
                  ; ++i_last
                    , ++my_istk
                    , ++i_node
                  )
                {
                    int offset_istk=my_istk.offset_space_val();
                  #ifdef TRACE_UPPER_TRIANGULATE_RHS
                    value_t my_old_r=my_r[offset_istk+stride_last];
                  #endif
                    my_r[offset_istk+stride_last]-=my_trid.l(i_last+1)*my_r[offset_istk]
                    ;
                  #ifdef TRACE_UPPER_TRIANGULATE_RHS
                    std::cout<<", ";
                    std::cout
                      <<":r"<<my_istk.indices_at_offset(offset_istk+stride_last)
                      <<"="
                      <<my_old_r
                      <<":->"
                      <<my_r[offset_istk+stride_last]
                      <<"\n";
                  #endif
                }
              #ifdef TRACE_UPPER_TRIANGULATE_RHS
                std::cout<<"}\n";
                std::cout<<indent_buf_out;
              #endif
            }
          #ifdef TRACE_UPPER_TRIANGULATE_RHS
            std::cout<<"}\n";
          #endif
          #ifdef SOLVE_TRIDIAG_VERIFY
            BOOST_ASSERT_MSG(i_node==n_node,"i_node!=n_node");
          #endif
          #undef TRACE_UPPER_TRIANGULATE_RHS
        }
        void
      back_substitute
        (
        )
        /**@brief
         *  Solves system of equations, a*x=r, for x. 
         *  where:
         *    a is this->my_trid
         *    x is this->my_x
         *    r is this->my_r
         **@requires
         *  this->upper_trigulate_trid(a_tol) has been called.
         *  this->upper_trigulate_rhs() has been called.
         */
        {
              auto const
            axis_last=my_istk.rank()-1
              ;
              auto const
            ibs=my_istk[axis_last]
              ;
              auto const
            stride_last=ibs.stride_val()
              //stride of last axis
              ;
              auto const
            n_last=ibs.length_val()
              //length of last axis
              ;
            --my_istk
              //Assuming all indices are at min values,
              //put all indices at max values.
              ;
            my_istk.axis_offsets_put
              ( axis_last
              , n_last-1
              , 0
              )
              //Fix last index at it's max.
              ;
          //#define TRACE_BACK_SUBSTITUTE
          #ifdef TRACE_BACK_SUBSTITUTE
            ::boost::trace_scope ts("back_substitute");
            using ::operator<<;
            std::cout
              <<":n_last="<<n_last
              <<":stride_last="<<stride_last
              <<"\n:my_istk="<<my_istk
              <<"\n"
              <<"{ "
              ;
          #endif
              unsigned const 
            n_outer=my_istk.space();
            for
              ( unsigned i_outer=0
              ; i_outer<n_outer
              ; ++i_outer
                , --my_istk
              )
             /*MAINTENANCE_NOTE:2011-10-22:Larry Evans:
              *  I *think* there's no data dependence between
              *  iterations of this i_outer loop; hence, this loop
              *  could be made parallel, somewhat like the MATLAB
              *  parfor loop:
              *    http: *www.mathworks.com/help/toolbox/distcomp/brb2x2l-1.html
              */
            {
                int i_last=n_last-1;
                auto offset_inner=my_istk.offset_space_val();
                my_x[offset_inner]=my_r[offset_inner]/my_trid.d(i_last);
              #ifdef TRACE_BACK_SUBSTITUTE
                using ::operator<<;
                if(0<i_outer)std::cout<<", ";
                std::cout<<indent_buf_in;
                std::cout<<"{ ";
                std::cout
                  <<":x"<<my_istk.indices_at_offset(offset_inner)
                  <<"="<<my_x[offset_inner]
                  <<"\n"
                  ;
              #endif
                for
                  ( --i_last
                    , offset_inner-=stride_last
                  ; -1<i_last
                  ; --i_last
                    , offset_inner-=stride_last
                  )
                {
                    my_x[offset_inner]=
                      ( my_r[offset_inner]
                      - my_trid.u(i_last)*my_x[offset_inner+stride_last]
                      )
                      / my_trid.d(i_last)
                      ;
                  #ifdef TRACE_BACK_SUBSTITUTE
                    std::cout<<", ";
                    std::cout
                      <<":x"<<my_istk.indices_at_offset(offset_inner)<<"="<<my_x[offset_inner]
                      <<"\n"
                      ;
                  #endif
                }
              #ifdef TRACE_BACK_SUBSTITUTE
                std::cout<<"}\n";
                std::cout<<indent_buf_out;
              #endif
            }
          #ifdef TRACE_BACK_SUBSTITUTE
            std::cout<<"}\n";
          #endif
          #ifdef SOLVE_TRIDIAG_VERIFY
            for
              ( unsigned i_outer=0
              ; i_outer<n_outer
              ; ++i_outer
                , --my_istk
              )
            {
                  int 
                i_last=n_last-1;
                auto offset_inner=my_istk.offset_space_val();
                auto indices=my_istk.indices_at_offset(offset_inner);
                  value_t
                rhs=o_r[offset_inner]
                  ;
                  value_t
                lhs
                  = my_x[offset_inner-stride_last]*o_trid.l(i_last)
                  + my_x[offset_inner            ]*o_trid.d(i_last)
                  ;
              #if 0
                {
                    istk_t istk_border(my_istk);
                    istk_border.axes_offsets_put(0,0);
                    array_iter_wrap<value_t> o_rw(o_r.begin(),istk_border);
                    std::cout
                      <<"**SOLVE_TRIDIAG_VERIFY(outer)**\n"
                      <<":my_istk="<<my_istk<<"\n"
                      <<":istk_border="<<istk_border<<"\n"
                      <<":offset_inner="<<offset_inner
                      <<":indices="<<indices
                      <<"\n";
                    std::cout<<":o_rw=\n"
                      <<o_rw<<".\n";
                }
              #endif
                  bool
                solved=almost_equal_relative(lhs,rhs)
                  ;
              #define TRACE_TRIDIAG_VERIFY 0
              #define TRACE_LONG_TRIDIAG_VERIFY 1
              #if TRACE_TRIDIAG_VERIFY
                  auto
                trace_verify=
                  [ &i_last
                  , &solved
                #if TRACE_LONG_TRIDIAG_VERIFY
                  , &my_x
                  , &o_trid
                  , &offset_inner
                  , &stride_last
                  , &o_r
                  , &lhs
                  , &rhs
                  , &my_istk
                #endif
                  ]()
                  {
                      if
                        ( !solved
                        || TRACE_TRIDIAG_VERIFY
                        )
                      {
                          std::cout
                            <<":i_last="<<i_last;
                        #if TRACE_LONG_TRIDIAG_VERIFY
                          std::cout
                            <<":my_x["<<offset_inner-stride_last<<"]="<<my_x[offset_inner-stride_last]
                            <<":l="<<o_trid.l(i_last)
                            <<":my_x["<<offset_inner<<"]="<<my_x[offset_inner]
                            <<":d="<<o_trid.d(i_last)
                            <<":r["<<offset_inner<<"]="<<o_r[offset_inner]
                            <<"\n:lhs="<<lhs
                            <<"\n:rhs="<<rhs
                            ;
                        #endif
                          std::cout<<"\n"<<std::flush;
                      }
                  };
                ::boost::indent_scope<> is();
                trace_verify();
              #endif
                BOOST_ASSERT_MSG(solved,"equation not solved");
                for
                  ( --i_last
                    , offset_inner-=stride_last
                  ; -1<i_last
                  ; --i_last
                    , offset_inner-=stride_last
                  )
                {
                    rhs=o_r[offset_inner];
                    indices=my_istk.indices_at_offset(offset_inner);
                   #if 0
                    {
                        std::cout
                          <<"**SOLVE_TRIDIAG_VERIFY(inner)**\n"
                          <<":offset_inner="<<offset_inner
                          <<":indices="<<indices
                          <<"\n";
                    }
                  #endif
                    lhs
                      = 0.0
                      + my_x[offset_inner            ]*o_trid.d(i_last)
                      + my_x[offset_inner+stride_last]*o_trid.u(i_last)
                      ;
                    if(0<i_last)
                    {
                        lhs
                         +=my_x[offset_inner-stride_last]*o_trid.l(i_last)
                          ;
                    }
                    solved=almost_equal_relative(lhs,rhs);
                  #if TRACE_TRIDIAG_VERIFY
                    ::boost::indent_scope<> is;
                    trace_verify();
                  #endif
                    BOOST_ASSERT_MSG(solved,"equation not solved");
                }
            }
        #endif
          #ifdef TRACE_BACK_SUBSTITUTE
            std::cout
              <<":my_istk="<<my_istk
              <<"\n";
          #endif
          #undef TRACE_BACK_SUBSTITUTE
        }
   private:
      istk_t my_istk;
      tridiag_t& my_trid;
      arr_data_iter_t my_r;
      arr_data_iter_t my_x;
    #ifdef SOLVE_TRIDIAG_VERIFY
        std::vector<value_t>
      o_r
        /**@brief
         *  The original my_r
         */
        ;
        tridiag_t
      o_trid
        /**@brief
         *  The orginal my_trid.
         */
        ;
    #endif
  };//solve_tridiag
  
}//exit numeric namespace
}//exit array_stepper namespace
}//exit boost namespace
#endif
