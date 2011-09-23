//Purpose:
//  Use array_dyn and its support functions to emulate the code here:
/*
  [DuffyAde2011]
    http://www.datasimfinancial.com/forum/download.php?id=351
 */
//  The limits on del_t are from page 3 of:
/*
  [Hor05]
    http://www.cosy.sbg.ac.at/events/parnum05/book/horak1.pdf
 */
#include <boost/utility/trace_scope.hpp>
#include <boost/array_stepper/array_dyn.hpp>
#include <boost/array_stepper/array_store_print.hpp>
#include <boost/array_stepper/vector_print.hpp>
#include <boost/array_stepper/index_stack_length_stride_crtp.hpp>
#include <boost/array.hpp>
#include <boost/mpl/package_range_c.hpp>
#include <iomanip>

typedef double value_t;
struct val_err
{
    value_t val;
    value_t err;
    val_err()
    : val(0.0)
    , err(0.0)
    {}
    
    operator value_t()const
    {
        return val;
    }
};

  std::ostream&
operator<<
  ( std::ostream& sout
  , val_err const& ve
  )
  {
        value_t 
      err=100.0*ve.err/ve.val
        //percent error in value.
        ;
      unsigned const ew=9;
      unsigned const ep=3;
    #if 0
      unsigned const vw=9;
      unsigned const vp=5;
      sout
        <<"( v:" <<std::setw(vw)<<std::setprecision(vp)<<ve.val
        <<", %e:"<<std::setw(ew)<<std::setprecision(ep)<<err
        <<")"
    #else
      sout
        <<std::setw(ew)<<std::setprecision(ep)<<err
    #endif
        ;
      return sout;
  }  
    
using namespace boost::array_stepper;

typedef array_dyn<val_err> array_t;

unsigned const N_s=10
 /**@brief
  *  length of array space axes
  */
  ;
unsigned const R_s=2
  /**@brief
   *  Rank (in apl terms) 
   *  or number of dimensions (a more familiar description?)
   *  of the space mesh.
   */
  ;
value_t const s_max=1.0
  /**@brief
   *  maximum space values
   *  (minimum space values=0.0).
   */
  ;
    typedef
  index_stack_length_stride_crtp_indices<> 
istk_indices_t
  ;
    typedef
  array_t::data_t::iterator
arr_data_iter_t
  ;  
    typedef
  array_t::length_dir_t
length_dir_t
  ;
    typedef
  std::vector
  < length_dir_t
  >
length_dirs_t
  ;    
  length_dirs_t
lengths_s
  ( R_s
  , N_s
  );
  
  std::vector<value_t>
index_bounds_val[index_bounds_value_size]
{ std::vector<value_t>(N_s,value_t(0.0))
, std::vector<value_t>(N_s,s_max)
};

  boost::array< value_t, N_s>
mk_del_s()
{
    boost::array< value_t, N_s> del_s;
    for(unsigned i_s=0; i_s<N_s; ++i_s)
    {
        value_t upper_lower_diff
          =index_bounds_val[index_bound_upper][i_s]
          -index_bounds_val[index_bound_lower][i_s];
        del_s[i_s]=upper_lower_diff/(N_s-1);
    }
    return del_s;
}
  boost::array< value_t, N_s> const
del_s(mk_del_s());

  value_t const
diffusivity=1.0
  //Thermal diffusivity (the constant 'c' in [Hor05]).
  //In [DuffyAde2011], in equation(1), it's assumed to be 1.0;
  //hence, that value is used here.
  ;
  value_t const
t_offset=0.1
  //instead of using time starting at 0, start at
  //some offset from 0 to avoid dividing by 0
  //in some expressions below.
  ;
  value_t const
t_max=1.0
  ;
  unsigned
N_t=0
  /**@brief
   *  Number of time increments.
   *  Actual value calculated by mk_del_t.
   */
  ;
  value_t const 
mk_del_t()
  {
      value_t del_s_min=0.0;
      int const n=del_s.size();
      value_t del_t=0.0;
      if(0<n) 
      {
          del_s_min=del_s[n-1];
          for(int i=0; i<n-1; ++i)
          {
              value_t del_s_i=del_s[i];
              if(del_s_i<del_s_min) del_s_min=del_s_i;
          }
          del_t=(del_s_min*del_s_min)/(4.0*diffusivity)
            //time increment, from page 6 of [Hor05].
            //*except* min del_s is chosen instead
            //of del_s aince del_s is vector.
            ;
          del_t/=10.0
            //extra insurance.
            ;
      }
      N_t=(t_max-t_offset)/del_t;
      return del_t;
  }
  
  value_t const 
del_t=mk_del_t()
  //time increment
  ;
  value_t
fundamental_indices( unsigned it, istk_indices_t const& s_iter)
//The fundamental solution to heat equation:
//References:
//  [Churchill72]
//    problem 8, page 150 of:
//    _Operational Mathematics_
//    Ruel V. Churchill
//    McGraw-Hill, 1972.
//  [Wiki2011]
//    http://en.wikipedia.org/wiki/Heat_equation#Fundamental_solutions
//However:
//  [Wiki2011] differs from [Churchill72] slightly:
//    [Wiki2011] has pow( 4*Pi*k*t, n/2) whereas
//    [Churchill72] has sqrt(t).
//  Since, in [Churchill72], the dimensionality, n=1,
//  that's almost the same, the only difference being
//  a constant factor, pow(4*Pi*k, n/2), both solution functions
//  satisfy the homogeneous equation if either does.
//
{
      value_t
    sumsq=0.0;
    for(unsigned axis=0; axis<R_s; ++axis) 
    {
          value_t const 
        s_val
          = index_bounds_val[index_bound_lower][axis]
          + s_iter[axis].get<index_value>()
          * del_s[axis]
          ;
        sumsq+=s_val*s_val;
    }
      value_t 
    t_val=t_offset+it*del_t;
        static
      value_t const
    R_s_div_2=double(R_s)/2.0
      //This is the n/2 in equation following sentence:
      //  The n-variable fundamental solution is the product of the fundamental solutions in each variable; i.e.,
      //in [Wiki2011].
      ;  
      value_t
    u_val=exp(-sumsq/(4.0*diffusivity*t_val))/pow(t_val,R_s_div_2);
    return u_val;
}

  value_t 
ic_indices( istk_indices_t const& s_iter)
{//initial conditions at indices, i_iter.
    return fundamental_indices( unsigned(0), s_iter);
}

void initial_conditions( arr_data_iter_t& u_iter, istk_indices_t& s_iter)
{//initial conditions, from [DuffyAde2011], page 5 (function IC).
    unsigned const n_space=s_iter.space();
    for(unsigned i_space=0; i_space<n_space; ++i_space, ++s_iter) 
    {
        value_t u_val=ic_indices(s_iter);
        val_err&ve_val=u_iter[s_iter.offset_space_val()];
        ve_val.val=u_val;
        ve_val.err=0.0;
    }
}

  template
  < unsigned AxisBound
  , index_bounds_value_enum IBV
  >
  typename ::boost::enable_if_c
  < IBV!=index_value
  , value_t
  >::type
bc_indices( unsigned it, istk_indices_t const& s_iter)
{//boundary conditions at it-th time at indices i_iter
    return fundamental_indices( it, s_iter);
}

    typedef
  value_t
(*bc_fun_t)( unsigned it, istk_indices_t const& s_iter)
  //Boundary condition function
  ;
  
    typedef
  boost::array
  < bc_fun_t
  , index_bounds_value_size
  >
bc_funs_axis_t  
  ;
   template
  < unsigned Axis
  >
  bc_funs_axis_t
mk_bc_lower_upper()
{
    bc_funs_axis_t const arr
    ={{ bc_indices<Axis,index_bound_lower>
      , bc_indices<Axis,index_bound_upper>
      }
     };
   return arr;
}  
   typedef
  boost::array
  < bc_funs_axis_t
  , N_s
  >
bc_funs_space_t  
  ;
  template
  < typename Axes
  >
  struct
arr_bc_funs
;
  template
  < unsigned... Axes
  >
  struct
arr_bc_funs
  < boost::mpl::package_c<unsigned,Axes...>
  >
{
        static
      bc_funs_space_t const&
    _()
    {
            static
          bc_funs_space_t const
        bc_funs_v=
        {{  mk_bc_lower_upper<Axes>()...
        }};
        return bc_funs_v;
    }
};

  bc_funs_space_t const&
mk_bc_funs()
{  
    typedef typename boost::mpl::package_range_c<unsigned,0,N_s>::type axes_t;
    return arr_bc_funs<axes_t>::_();
}    

void boundary_conditions(unsigned it, arr_data_iter_t& u_iter, istk_indices_t& s_iter)
{
  //#define TRACE_BOUNDARY_CONDITIONS
  #ifdef TRACE_BOUNDARY_CONDITIONS
      ::boost::trace_scope
    ts("boundary_conditions");
  #endif
        typedef
      typename istk_indices_t::axis_t
    axis_t
      ;
        typedef
      typename istk_indices_t::index_t
    index_t
      ;
      unsigned 
    rank=s_iter.rank();
  #ifdef TRACE_BOUNDARY_CONDITIONS
    std::cout<<"rank="<<rank<<"\n"<<"indices_v=\n"<<s_iter<<"\n";
  #endif
    {//remove any offset bounds and 
     //reset indices to beginning of index range.
        for
          ( axis_t axis_v=0
          ; axis_v<rank
          ; ++axis_v
          )
        {
            s_iter.axis_offset_put(axis_v,0,0);
        }
    }
    for
      ( axis_t axis_v=0
      ; axis_v<rank
      ; ++axis_v
      )
    {
      #ifdef TRACE_BOUNDARY_CONDITIONS
          ::boost::trace_scope
        ts("for(axis_v=)");
        std::cout
          <<":axis_v="<<axis_v
          <<":for(axis_v.offset_space=)"<<s_iter.offset_space_val()
          <<"\n";
      #endif
          bc_funs_axis_t 
        bc_funs_axis_v=mk_bc_funs()[axis_v];
        index_t offset_lower=0;
        index_t offset_upper=s_iter[axis_v].length_val()-1;
        auto ibs=s_iter[axis_v];
        for
          ( unsigned index_bound_side=index_bound_lower
          ; index_bound_side<index_value
          ; ++index_bound_side
            , std::swap(offset_lower,offset_upper)
          )
        {
            s_iter.axis_offset_put(axis_v,offset_lower,offset_upper);
          #ifdef TRACE_BOUNDARY_CONDITIONS
              ::boost::trace_scope
            ts("for(index_bound_side=)");
            std::cout
              <<":index_bound_side="<<index_bound_side
              <<":before index_bound.offset_space_axis="<<s_iter.offset_space_val()
              <<"\n";
          #endif
            unsigned const n_space=s_iter.space();
            for
              ( unsigned i_space=0
              ; i_space<n_space
              ; ++i_space
                , ++s_iter
              ) 
            {
                auto const offset_space=s_iter.offset_space_val();
              #ifdef TRACE_BOUNDARY_CONDITIONS
                  ::boost::trace_scope
                ts("for(i_space=)");
                std::cout
                  <<":i_space="<<i_space
                  <<":offset_space="<<offset_space
                  <<"\n";
              #endif
                value_t u_val=bc_funs_axis_v[index_bound_side]( it, s_iter);
                val_err&ve_val=u_iter[s_iter.offset_space_val()];
                ve_val.val=u_val;
                ve_val.err=0.0;
              #ifdef TRACE_BOUNDARY_CONDITIONS
                std::cout<<"u_val["<<it<<","<<s_iter<<"]="<<u_val<<"\n";
              #endif
            }//exit for(i_space=)
        }//exit for(index_bound_side=)
        s_iter.axis_offset_put(axis_v,1,1);
    }//exit for(axis_v=)
}
      
int main()
  {
    boost::iostreams::indent_scoped_ostreambuf<char> indent_outbuf(std::cout,2);
    std::cout<<"N_t="<<N_t<<"\n";
    std::cout<<"N_s="<<N_s<<"\n";
    std::cout<<"(t_offset+N_t*del_t)-t_max="<<(t_offset+N_t*del_t)-t_max<<"\n";
  #if 1
    {
        ::boost::trace_scope ts("stacked_space_loops");
        std::cout<<"lengths_s="<<lengths_s<<"\n";
          length_dirs_t
        lengths_u
          ( 1+R_s
          );
        lengths_u[0]=N_t;
        std::copy_n
          ( lengths_s.begin()
          , R_s
          , lengths_u.begin()+1
          );
        std::cout<<"lengths_u="<<lengths_u<<"\n";
          array_t 
        u(lengths_u)
         /**@brief
          * u(it,ix1,ix2,...ixn)=temperature 
          *   at position (ix1*del_s,ix2*del_s,...,ixn*del_s)
          *   (where n=N_s)
          *   at time(it*del_t).
          */
          ;
          arr_data_iter_t
        u_iter=u.data().begin()+u.offset()
          ;
          istk_indices_t
        space_istk_is
          ( u.length_strides().begin()+1
          , u.length_strides().end()
          );
        initial_conditions( u_iter, space_istk_is);
          istk_indices_t
        time_istk_is
          ( u.length_strides().begin()
          , u.length_strides().begin()+1
          );
        {//solve the differential equation:
          //#define TRACE_SOLN_DIFF_EQ
              value_t
            t_div_s2[N_s]
              //These are the lambda's in equation(11) of [DuffyAde2011] 
              ;
              value_t
            sum_tds=0.0
              //This is the sigma of equation(11) of [DuffyAde2011] 
              ;
            for( unsigned s_axis=0; s_axis<R_s; ++s_axis)
            {
                value_t del_s_axis=del_s[s_axis];
                t_div_s2[s_axis]=del_t/(del_s_axis*del_s_axis);
                sum_tds+=t_div_s2[s_axis];
            }
              value_t const
            one_plus_sum_tds=1.0+sum_tds
              ;
              value_t const
            one_minus_sum_tds=1.0-sum_tds
              ;
              value_t const
            one_minus_div_one_plus_sum_tds=one_minus_sum_tds/one_plus_sum_tds
              ;
          #if 0
            std::cout<<"sum_tds="<<sum_tds<<"\n";
            std::cout<<"one_plus_sum_tds="<<one_plus_sum_tds<<"\n";
            std::cout<<"one_minus_sum_tds="<<one_minus_sum_tds<<"\n";
            std::cout<<"one_minus_div_one_plus_sum_tds="<<one_minus_div_one_plus_sum_tds<<"\n";
          #endif
              value_t
            t_div_s2_div_one_plus_sum_tds[N_s]
              ;
            for( unsigned s_axis=0; s_axis<N_s; ++s_axis)
            {
                t_div_s2_div_one_plus_sum_tds[s_axis]
                  =t_div_s2[s_axis]/one_plus_sum_tds;
            }
            for
              ( unsigned it=0
              ; it<N_t-1
              #if 0
                && it<1 //just for debugging.
              #endif
              ; ++it
              )
            {
              #ifdef TRACE_SOLN_DIFF_EQ
                std::cout<<"it.{="<<it<<"\n";
                std::cout<<"u["<<it<<"]=\n"<<u<<".\n";
                std::cout<<indent_buf_in;
              #endif
                  arr_data_iter_t
                ut_now_iter=u_iter+time_istk_is.offset_space_val()
                  //u at it-th time.
                  ;
                ++time_istk_is
                  //increment time to (it+1)-th time.
                  ;
                  arr_data_iter_t
                ut_nxt_iter=u_iter+time_istk_is.offset_space_val()
                  //u at (it+1)-th time.
                  ;
                //std::cout<<"ut_nxt_iter-ut_now_iter="<<(ut_nxt_iter-ut_now_iter)<<"\n";
                boundary_conditions( it+1, ut_nxt_iter, space_istk_is)
                  //update boundary nodes in mesh
                  ;
                  auto const 
                s_space=space_istk_is.space()
                  //The number of nodes in inner mesh.
                  ;
              #if 0
                std::cout<<"after boundary_conditions:\n";
                std::cout<<"space_istk_is.space()="<<s_space<<"\n";
                std::cout<<"u["<<it+1<<"]=\n"<<u<<".\n";
              #endif
                //return 0;
                { //update inner nodes in mesh
                  //#define TRACE_UPDATE_INNER_MESH
                  #ifdef TRACE_UPDATE_INNER_MESH
                    ::boost::trace_scope ts("update inner_nodes");
                  #endif
                    enum sweep_enum
                    { sweep_up
                    , sweep_down
                    , sweeps_size
                    };
                        typedef
                      array_dyn<value_t>
                    arrswp_t;
                        typedef
                      arrswp_t::data_t::iterator
                    arrswp_data_iter_t;
                      arrswp_t 
                    sweeps[sweeps_size]=
                      { arrswp_t(lengths_s)//The U in equation( 9) of [DuffyAde2011]
                      , arrswp_t(lengths_s)//The V in equation(10) of [DuffyAde2011]
                      };
                    ;
                        typedef
                      int(istk_indices_t::*
                    incdec_t
                      )()
                      ;
                      incdec_t
                    incdecs[sweeps_size]=
                      { &istk_indices_t::operator++
                      , &istk_indices_t::operator--
                      };
                    for
                      ( unsigned i_sweep=sweep_up
                      ; i_sweep<sweeps_size
                      ; ++i_sweep
                        , (space_istk_is.*(incdecs[i_sweep%sweeps_size]))()
                          //to undo last ++ or -- space_istk_is 
                          //in  nested for(s_index loop)
                      )
                    {
                      #ifdef TRACE_UPDATE_INNER_MESH
                        ::boost::trace_scope ts("i_sweep");
                        std::cout<<"i_sweep="<<i_sweep<<"\n";
                      #endif
                          incdec_t const
                        incdec_v=incdecs[i_sweep];
                          arrswp_t&
                        sweep_i_arr=sweeps[i_sweep];
                        std::copy_n
                          ( ut_now_iter-u.offset()
                          , sweep_i_arr.data().size()
                          , sweep_i_arr.data().begin()
                          );
                          arrswp_data_iter_t
                        sweep_i_iter=sweep_i_arr.data().begin()+sweep_i_arr.offset();
                        enum{ u_stride_index, s_stride_index};
                          unsigned const
                        stride_indices[sweeps_size]=
                          { i_sweep
                          , (i_sweep+1)%sweeps_size
                          }
                          // =={0,1} during i_sweep==0
                          // =={1,0} during i_sweep==1
                          ;
                        for//each node in inner mesh, calculate sweeps values.
                          ( istk_indices_t::stride_t s_index=0
                          ; s_index<s_space
                          ; ++s_index
                            , (space_istk_is.*incdec_v)()
                          )
                        {
                          #ifdef TRACE_UPDATE_INNER_MESH
                            ::boost::trace_scope ts("s_index");
                            std::cout<<"s_index="<<s_index<<"\n";
                            std::cout<<"space_istk_is="<<space_istk_is<<"\n";
                          #endif
                              auto const 
                            space_offset=space_istk_is.offset_space_val();
                              arr_data_iter_t
                            uts_node_iter=ut_now_iter+space_offset;
                              arrswp_data_iter_t
                            sweep_node_iter=sweep_i_iter+space_offset;
                              value_t&
                            sweep_node0=sweep_node_iter[0]
                              //The lhs of equation(9 or 10) of [DuffyAde2011]
                              //divided by (1+lower case sigma).
                            ;
                            sweep_node0=uts_node_iter[0].val*one_minus_div_one_plus_sum_tds
                              //The rhs of this assignment is
                              //1st term on rhs of equation(9 or 10)of [DuffyAde2011]
                              //divided by (1+lower case sigma)[in [DuffyAde2011]]
                              //[or one_plus_sum_tds here].
                            ;
                            { //add to sweep_node0, the rhs of equation( 9 or 10)
                              //except for 1st term.
                                for
                                  ( unsigned s_axis=0
                                  ; s_axis<R_s
                                  ; ++s_axis
                                  )
                                {
                                  #ifdef TRACE_UPDATE_INNER_MESH
                                    ::boost::trace_scope ts("s_axis");
                                    std::cout<<"s_axis="<<s_axis<<"\n";
                                  #endif
                                        typedef
                                      istk_indices_t::stride_t
                                    stride_t
                                    ;
                                      stride_t 
                                    stride_v=space_istk_is[s_axis].stride_val();
                                      stride_t const
                                    stride_plus_minus[sweeps_size]=
                                      { +stride_v
                                      , -stride_v
                                      };
                                      stride_t const
                                    stride_u=stride_plus_minus[stride_indices[u_stride_index]]
                                      ;
                                      value_t
                                    uts_node_stride=
                                      uts_node_iter
                                      [ stride_u
                                        // ==+stride_v if i_sweep==0
                                        // ==-stride_v if i_sweep==1
                                      ].val
                                      //this expresssion corresponds to
                                      //the U(if i_sweep==0) or V(if i_sweep==1)
                                      //with n superscript of rhs of equation(9 or 10)
                                      //in [DuffyAde2011].
                                      ;
                                      stride_t const
                                    stride_s=stride_plus_minus[stride_indices[s_stride_index]]
                                      ;
                                      value_t
                                    sweep_node_stride=
                                      sweep_node_iter
                                      [ stride_s
                                        // ==-stride_v if i_sweep==0
                                        // ==+stride_v if i_sweep==1
                                      ]
                                      //this expresssion corresponds to
                                      //the U(if i_sweep==0) or V(if i_sweep==1)
                                      //with n+1 superscript of rhs of equation(9 or 10)
                                      //in [DuffyAde2011].
                                      ;
                                  #ifdef TRACE_UPDATE_INNER_MESH
                                    std::cout
                                      <<":stride_index_s="<<stride_indices[s_stride_index]
                                      <<":stride_s="<<stride_s
                                      <<":indices_s="
                                      <<sweep_i_arr.indexs_at_offset
                                        ( space_offset
                                        + stride_s
                                        )
                                      <<"\n";
                                  #endif
                                      value_t
                                    sum_uts_sweep_node=uts_node_stride+sweep_node_stride;
                                    sweep_node0+=
                                        t_div_s2_div_one_plus_sum_tds[s_axis]
                                      * sum_uts_sweep_node
                                      //This is one of the terms on rhs of equation(9)
                                      //of [DuffyAde2011] which are multiplied
                                      //by one of the lambda's(s_axis corresponds to
                                      //the lambda subscript in equation(9)) 
                                      //then divided by (1+lower case sigma)
                                      ;
                                }//for stride_iter_v
                            } //add to sweep_node0
                        }//for(s_index, for sweeps
                    }//for(i_sweep
                    for//each node in inner mesh, calculate next u value.
                       //as average of the just calculated sweeps data.
                       //This loop implements equation(6) of [DuffyAde2011].
                      ( istk_indices_t::stride_t s_index=0
                      ; s_index<s_space
                      ; ++s_index
                        , ++space_istk_is
                      )
                    {
                      #if 0
                        ::boost::trace_scope ts("average sweeps");
                        std::cout<<"space_istk_is="<<space_istk_is<<"\n";
                      #endif
                          auto const 
                        space_offset=space_istk_is.offset_space_val();
                          val_err&
                        uts_nxt_node=*(ut_nxt_iter+space_offset);
                        uts_nxt_node.val=0.0;
                        for
                          ( unsigned i_sweep=sweep_up
                          ; i_sweep<sweeps_size
                          ; ++i_sweep
                          )
                        {
                              arrswp_t&
                            sweep_i_arr=sweeps[i_sweep];
                              arrswp_data_iter_t
                            sweep_iter=sweep_i_arr.data().begin()
                              +sweep_i_arr.offset()
                              +space_offset
                              ;
                            uts_nxt_node.val+=*sweep_iter;//sum sweeps
                        }//for(i_sweep
                        uts_nxt_node.val/=value_t(sweeps_size);//average sweeps
                        value_t exact=fundamental_indices( it+1, space_istk_is);
                        uts_nxt_node.err=uts_nxt_node.val-exact;
                    }//for(s_index
                } //update inner nodes in mesh
            }//for(it=...)
        }//solve the differential equation:
        std::cout<<"u["<<N_t<<"]=\n"<<u<<".\n";
    }
  #endif
    return 0;
  }
