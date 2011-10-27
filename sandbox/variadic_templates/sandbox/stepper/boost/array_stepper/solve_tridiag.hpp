#ifndef BOOST_ARRAY_STEPPER_SOLVE_TRIDIAG_HPP_INCLUDED
#define BOOST_ARRAY_STEPPER_SOLVE_TRIDIAG_HPP_INCLUDED
#include <boost/array_stepper/index_stack_length_stride_crtp.hpp>
#include <boost/array_stepper/array_dyn.hpp>
#include <boost/array_stepper/vector_print.hpp>
#include <boost/iostreams/utility/indent_scoped_ostreambuf.hpp>
#include <iomanip>
#include <limits>
#define SOLVE_TRIDIAG_VERIFY
#ifdef  SOLVE_TRIDIAG_VERIFY
#include <boost/assert.hpp>
#endif

namespace boost
{
namespace array_stepper
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
        ( istk_t& a_istk
        , tridiag_t& a_trid//the matrix
        , arr_data_iter_t a_r//rhs
        , arr_data_iter_t a_x//unknown
        )
        : my_istk(a_istk)
        , my_trid(a_trid) 
        , my_r(a_r)
        , my_x(a_x)
      #ifdef SOLVE_TRIDIAG_VERIFY
        , o_r(my_istk.space())
        , o_trid(my_trid)
      #endif
        {
          #ifdef SOLVE_TRIDIAG_VERIFY
            unsigned const n_node=o_r.size();
            for
              ( unsigned i_node=0
              ; i_node<n_node
              ; ++my_istk, ++i_node
              )
            {
                int offset_istk=my_istk.offset_space_val();
                o_r[i_node]=my_r[offset_istk];
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
              <<"\n";
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
                ::boost::trace_scope ts("outer");
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
                    my_r[offset_istk+stride_last]-=my_trid.l(i_last+1)*my_r[offset_istk]
                    ;
                  #ifdef TRACE_UPPER_TRIANGULATE_RHS
                    ::boost::trace_scope ts("inner");
                    std::cout
                      <<":i_node="<<i_node
                      <<":i_last="<<i_last
                      <<":offset_istk="<<offset_istk
                      <<":r="<<my_r[offset_istk+stride_last]
                      <<"\n";
                  #endif
                }
            }
          #ifdef SOLVE_TRIDIAG_VERIFY
            BOOST_ASSERT_MSG(i_node==n_node,"i_node!=n_node");
          #endif
          #undef TRACE_UPPER_TRIANGULATE_RHS
        }
    #ifdef SOLVE_TRIDIAG_VERIFY
          static
        bool
      almost_equal_relative
        ( value_t value_a
        , value_t value_b
        )
       /**@brief
        *  Are value_a and value_b almost equal?
        */
        //Reference:
        //  http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
        //
        {
            value_t max_error=2.0*std::numeric_limits<value_t>::epsilon();
            value_t abs_diff=std::abs(value_a - value_b);
            if (abs_diff < max_error)
                return true;
            value_t abs_a=std::abs(value_a);
            value_t abs_b=std::abs(value_b);
            value_t abs_max=std::max(abs_a,abs_b);
            value_t relative_error=abs_diff / abs_max;
            if (relative_error < max_error)
                return true;
            return false;
        }
    #endif
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
            --my_istk
              //put all indices at max values.
              ;
              int 
            offset_istk=my_istk.offset_space_val();
          #define TRACE_BACK_SUBSTITUTE
          #ifdef TRACE_BACK_SUBSTITUTE
            ::boost::trace_scope ts("back_substitute");
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
              ( i_node=n_node
              ; 0<i_node
              ;
              )
             /*MAINTENANCE_NOTE:2011-10-22:Larry Evans:
              *  I *think* there's no data dependence between
              *  iterations of this i_node loop; hence, this loop
              *  could be made parallel, somewhat like the MATLAB
              *  parfor loop:
              *    http: *www.mathworks.com/help/toolbox/distcomp/brb2x2l-1.html
              */
            {
                int i_last=n_last-1;
                my_x[offset_istk]=my_r[offset_istk]/my_trid.d(i_last);
              #ifdef TRACE_BACK_SUBSTITUTE
                using ::operator<<;
                if(i_node<n_node)std::cout<<", ";
                std::cout<<indent_buf_in;
                std::cout<<"{ ";
                std::cout
                  <<":x"<<my_istk.indices()<<"="<<my_x[offset_istk]
                  <<"\n"
                  ;
              #endif
                for
                  ( --i_last
                    , --my_istk
                    , --i_node
                    , offset_istk=my_istk.offset_space_val()
                  ; -1<i_last
                  ; --i_last
                    , --my_istk
                    , --i_node
                    , offset_istk=my_istk.offset_space_val()
                  )
                {
                    my_x[offset_istk]=
                      ( my_r[offset_istk]
                      - my_trid.u(i_last)*my_x[offset_istk+stride_last]
                      )
                      / my_trid.d(i_last)
                      ;
                  #ifdef TRACE_BACK_SUBSTITUTE
                    std::cout<<", ";
                    std::cout
                      <<":x"<<my_istk.indices()<<"="<<my_x[offset_istk]
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
            BOOST_ASSERT_MSG(0==i_node,"0!=i_node");
            i_node=n_node;
            for
              ( i_node=n_node
              ; 0<i_node
              ;
              )
            {
                int i_last=n_last-1;
                  value_t
                rhs=o_r[i_node-1]
                  ;
                  value_t
                lhs
                  = my_x[offset_istk-stride_last]*o_trid.l(i_last)
                  + my_x[offset_istk            ]*o_trid.d(i_last)
                  ;
              #ifdef TRACE_TRIDIAG_VERIFY
                std::cout
                  <<":i_last="<<i_last
                  <<":my_x["<<offset_istk-stride_last<<"]="<<my_x[offset_istk-stride_last]
                  <<":l="<<o_trid.l(i_last)
                  <<":my_x["<<offset_istk<<"]="<<my_x[offset_istk]
                  <<":d="<<o_trid.d(i_last)
                  <<":r["<<i_node-1<<"]="<<o_r[i_node-1]
                  <<"\n:lhs="<<lhs
                  <<"\n:rhs="<<rhs
                  ;
                std::cout<<"\n:my_istk=";
                ::operator<<(std::cout,my_istk);
                std::cout<<"\n";
              #endif
                BOOST_ASSERT_MSG(almost_equal_relative(lhs,rhs),"equation not solved");
                for
                  ( --i_last
                    , --my_istk
                    , --i_node
                    , offset_istk=my_istk.offset_space_val()
                  ; -1<i_last
                  ; --i_last
                    , --my_istk
                    , --i_node
                    , offset_istk=my_istk.offset_space_val()
                  )
                {
                    rhs=o_r[i_node-1];
                    lhs
                      = 0.0
                      + my_x[offset_istk            ]*o_trid.d(i_last)
                      + my_x[offset_istk+stride_last]*o_trid.u(i_last)
                      ;
                    if(0<i_last)
                    {
                        lhs
                         +=my_x[offset_istk-stride_last]*o_trid.l(i_last)
                          ;
                    }
                  #ifdef TRACE_TRIDIAG_VERIFY
                    std::cout
                      <<":i_last="<<i_last;
                    if(0<i_last) std::cout
                      <<":my_x["<<offset_istk-stride_last<<"]="<<my_x[offset_istk-stride_last]
                      <<":l="<<o_trid.l(i_last);
                    std::cout
                      <<":my_x["<<offset_istk<<"]="<<my_x[offset_istk]
                      <<":d="<<o_trid.d(i_last)
                      <<":my_x["<<offset_istk+stride_last<<"]="<<my_x[offset_istk+stride_last]
                      <<":u="<<o_trid.u(i_last)
                      <<":r["<<i_node-1<<"]="<<o_r[i_node-1]
                      <<"\n:lhs="<<lhs
                      <<"\n:rhs="<<rhs
                      ;
                    std::cout<<"\n:my_istk=";
                    ::operator<<(std::cout,my_istk);
                    std::cout<<"\n";
                  #endif
                    BOOST_ASSERT_MSG(almost_equal_relative(lhs,rhs),"equation not solved");
                }
            }
        #endif
            ++my_istk
              //restore all indices to min values.
              ;
          #ifdef TRACE_BACK_SUBSTITUTE
            std::cout
              <<":my_istk.offset_space_val()="<<my_istk.offset_space_val()
              <<"\n";
          #endif
          #undef TRACE_BACK_SUBSTITUTE
        }
   private:
      istk_t& my_istk;
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
  
}//exit array_stepper namespace
}//exit boost namespace
#endif
