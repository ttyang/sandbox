//Purpose:
//  Use array_dyn and its support functions to implement
//  numerical solution of diffusion differential equation.
//References:
//==============================
//  The "Alternating Directions Explicit(ADE)" method is
//  described here:
/*
  [DuffyAde2011]
    http://www.datasimfinancial.com/forum/download.php?id=351
 */
//==============================
/*
  [DuffyFdm2006]
    Duffy, Daniel J.
    _Finite Difference Methods in Financial Engineering
     A Partial Differential Equation Approach_
    John Wiley & Sons, Ltd(2006)
 */
//==============================
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
#include <iomanip>
#include <initializer_list>
#include <deque>
#include <boost/array_stepper/solve_tridiag.hpp>

    typedef 
  double 
value_t;
struct estim_exact
{
      value_t 
    estim
      /**@brief
       *  Estimated or calculated value.
       */
      ;
      value_t 
    exact
      /**@brief
       *  Exact value.
       */
      ;
    estim_exact
    ( value_t a_estim=0.0
    , value_t a_exact=0.0
    )
    : estim(a_estim)
    , exact(a_exact)
    {}
      value_t
    err()const
      /**@brief
       *  percent error between estimated and exact values.
       */
    {
          value_t const 
        ratio=estim/exact;
          value_t const
        diff1=ratio-value_t(1.0);
          value_t const
        percent=
          ( std::abs(diff1)
          < 1.1*std::numeric_limits<value_t>::epsilon()
          )
          ? value_t(0.0)
          : 100.0*diff1
          ;
        return percent;
    }
};

  std::ostream&
operator<<
  ( std::ostream& sout
  , estim_exact const& ee
  )
  {
      unsigned const ew=9;
      unsigned const ep=3;
    #if 0
      unsigned const vw=9;
      unsigned const vp=5;
      sout
        <<"( x:" <<std::setw(vw)<<std::setprecision(vp)<<ee.exact
        <<", %e:"<<std::setw(ew)<<std::setprecision(ep)<<ee.err()
        <<")"
    #else
      sout
        <<std::setw(ew)<<std::showpos<<std::left<<std::setprecision(ep)<<ee.err()
    #endif
        ;
      return sout;
  }  
  
using namespace boost::array_stepper;

struct hot_spot
{
      value_t
    my_err
      /**@brief
       *  percent error
       */
      ;
        typedef
      index_stack_length_stride_crtp_indices
      <
      > 
    istk_indices_t
      ;
        typedef
      typename istk_indices_t::indices_t
    indices_t
      ;
      indices_t
    my_indices
      ;
    hot_spot
      ( value_t a_err
      , indices_t const& a_indices
      )
      : my_err(a_err)
      , my_indices(a_indices)
      {}
      
};

struct hot_spots
: std::deque<hot_spot>
{
        typedef
      std::deque<hot_spot>
    super_t
    ;
    hot_spots( unsigned a_size_max)
    : my_size_max(a_size_max)
    {}
      struct
    find_spot
    {
          bool
        operator()
          ( hot_spot const& a_spot
          )
        {
            return my_abs_err>std::abs(a_spot.my_err);
        }
        find_spot( value_t a_err)
        : my_abs_err(std::abs(a_err))
        {}
          value_t
        my_abs_err
        ;
    };
      void
    push_spot_if( value_t a_err, hot_spot::istk_indices_t const& a_istk)
    {
        find_spot pred(a_err);
        super_t::iterator found=std::find_if(begin(),end(),pred);
        hot_spot a_spot( a_err, a_istk.indices());
        insert(found,a_spot);
        if(size()>my_size_max)pop_back();
    }
 private:
      unsigned
    my_size_max
    ;
};
        
  template
  < typename Value
  >
struct grid_axis_size_bounds
{
        typedef
      Value
    value_t
    ;
      unsigned
    size
      /**@brief
       *  Number of points on the axis
       */
    ;
      value_t
    lower
      /**@brief
       *  Minumum value on axis.
       */
    ;
      value_t
    upper
      /**@brief
       *  Maximum value on axis.
       */
    ;
    grid_axis_size_bounds
    ( unsigned a_size=2
    , value_t  a_lower=0.1
    , value_t  a_upper=1.0
    )
    : size(a_size)
    , lower(a_lower)
    , upper(a_upper)
    {}
};

  template
  < typename Value
  >
  std::ostream&
operator<<
  ( std::ostream& sout
  , grid_axis_size_bounds<Value>const& a
  )
  {
      sout
        <<"( size="<<a.size
        <<", lower="<<a.lower
        <<", upper="<<a.upper
        <<"}";
      return sout;
  }
  

  template
  < typename Value
  >
struct grid_axis_points
{
        typedef
      Value
    value_t
    ;
    grid_axis_points
      (
      )
      : my_size(2)
      , my_lower(0.0)
      , my_del(0.0)
      {}
    grid_axis_points
      ( grid_axis_size_bounds<value_t>const&a_size_bounds
      )
      : my_size(a_size_bounds.size)
      , my_lower(a_size_bounds.lower)
      , my_del(mk_del(a_size_bounds.upper))
      {}
    grid_axis_points
      ( grid_axis_points const&a_self
      )
      : my_size(a_self.my_size)
      , my_lower(a_self.my_lower)
      , my_del(a_self.my_del)
      {}
      unsigned
    size()const
      {
          return my_size;
      }
      value_t
    lower()const
      {
          return my_lower;
      }
      value_t
    del()const
      {
          return my_del;
      }
      void
    size_put(value_t a_size)
      {
          my_size=a_size;
      }
      void
    lower_put(value_t a_lower)
      {
          my_lower=a_lower;
      }
      void
    del_put(value_t a_del)
      {
          my_del=a_del;
      }
      grid_axis_points const&
    operator=
      ( grid_axis_size_bounds<value_t>const&a_size_bounds
      )
      {
          my_size=a_size_bounds.size;
          my_lower=a_size_bounds.lower;
          my_del=mk_del(a_size_bounds.upper);
          return *this;
      }
      value_t
    operator[]( unsigned i)const
      {
          return my_lower+i*my_del;
      }
 private:    
      unsigned
    my_size
      /**@brief
       *  Number of points on the axis
       */
      ;
      value_t
    my_lower
      /**@brief
       *  Minumum value on axis.
       */
      ;
      value_t
    my_del
      /**@brief
       *  the differenced between points on the axis.
       */
      ;
      value_t
    mk_del(value_t a_upper)
      {
            value_t
          result=(a_upper-my_lower)/value_t(my_size-1);
          return result;
      }
};
  
  template
  < typename Value
  >
  std::ostream&
operator<<
  ( std::ostream& sout
  , grid_axis_points<Value>const& a
  )
  {
      sout
        <<"( size="<<a.size()
        <<", lower="<<a.lower()
        <<", del="<<a.del()
        <<"}";
      return sout;
  }
  
  template
  < typename Value
  >
struct grid_axes_diff
{
 private:
      template
      < typename Iter
      >
      void
    init_axes
      ( Iter a_iter
      )
      {
            unsigned const 
          rank=my_axes.size();
            value_t 
          del_s_min=std::numeric_limits<value_t>::max()
           /**@brief
            *  Minimum value of space delta's..
            */
            ;
          for
            ( unsigned i=1//init just space axes.
            ; i<rank
            ; ++i
            )
          {
              my_axes[i]=a_iter[i];
              if(my_axes[i].del()<del_s_min) 
                  del_s_min=my_axes[i].del();
          } 
            value_t 
          del_t=(del_s_min*del_s_min)/(4.0*diffusivity)
            //time increment, from page 6 of [Hor05].
            //*except* min del_s is chosen instead
            //of a single space delta since there's a 
            //n-1 space deltas.
            ;
          del_t/=10.0
            //reduce for extra insurance.
            ;
          if(a_iter[0].size==0) 
          {
              value_t const diff_t=a_iter[0].upper-a_iter[0].lower;
              my_axes[0].size_put(diff_t/del_t);
          }
          else
          {
              my_axes[0].size_put(a_iter[0].size);
          }
          my_axes[0].lower_put(a_iter[0].lower);
          my_axes[0].del_put(del_t);
      }
 public:
        typedef
      Value
    value_t
      ;
        typedef
      std::vector<grid_axis_size_bounds<value_t> >
    grid_axes_size_bounds_t
      ;
        typedef
      std::vector<grid_axis_points<value_t> >
    grid_axes_points_t
      ;
    grid_axes_diff
      ( grid_axes_size_bounds_t const& a_grid_axes
      , value_t a_diffusivity=1.0
      )
      : diffusivity(a_diffusivity)
      , my_axes
        ( a_grid_axes.size()
        )
      {
          init_axes(a_grid_axes.begin());
      }
    grid_axes_diff
      ( std::initializer_list<grid_axis_size_bounds<value_t> >const& a_grid_axes
      , value_t a_diffusivity=1.0
      )
      : diffusivity(a_diffusivity)
      , my_axes
        ( a_grid_axes.size()
        )
      {
          init_axes(a_grid_axes.begin());
      }
      value_t const
    diffusivity
      ;
      grid_axes_points_t const&
    axes()const
      {
          return my_axes;
      }
 private:            
      grid_axes_points_t
    my_axes
      ;
};

  template
  < typename Value
  >
  std::ostream&
operator<<
  ( std::ostream& sout
  , grid_axes_diff<Value>const& a
  )
  {
      sout<<"grid_axes_diff=\n";
      sout<<"{ ";
      auto const&axes=a.axes();
      for(unsigned i=0; i<axes.size(); ++i)
      {
          if(0<i)sout<<", ";
          auto const&axis=axes[i];
          sout<<"{ ";
          for(unsigned j=0; j<axis.size(); ++j)
          {
              if(0<j)sout<<", ";
              sout<<axis[j];
          }
          sout<<"}\n";
      }
      sout<<"}\n";
      return sout;
  }  

  template
  < typename FunctionsDerived
  >
struct funcs_grid_iters
;
  template
  < template< typename V>class FunctionsDerived
  , typename Value
  >
struct funcs_grid_iters
  < FunctionsDerived
    < Value
    >
  >
: grid_axes_diff<Value>
{
        typedef
      FunctionsDerived<Value>
    funcs_t
      ;
        typedef
      Value
    value_t
    ;
        typedef
      grid_axes_diff<value_t>
    grid_axes_t
    ;
        typedef 
      array_dyn<value_t> 
    array_t
      ;
        typedef
      index_stack_length_stride_crtp_indices
      <
      > 
    istk_indices_t
      ;
        typedef
      typename array_t::data_t::iterator
    arr_data_iter_t
      ;  
      
      funcs_t&
    funcs()
      {
          return static_cast<funcs_t&>(*this);
      }
      void 
    initial_conditions( arr_data_iter_t& u_iter, istk_indices_t& s_iter)
      {//initial conditions.
          unsigned const n_space=s_iter.space();
        //#define TRACE_INITIAL_CONDITIONS
        #ifdef TRACE_INITIAL_CONDITIONS
          ::boost::trace_scope ts("initial_conditions");
          std::cout<<"n_space="<<n_space<<"\n";
        #endif
          for(unsigned i_space=0; i_space<n_space; ++i_space, ++s_iter) 
          {
              value_t u_val=funcs().ic_indices(s_iter);
              value_t&u_ref=u_iter[s_iter.offset_space_val()];
              u_ref=u_val;
            #ifdef TRACE_INITIAL_CONDITIONS
              std::cout<<":ispace="<<ispace<<":u_val="<<u_val<<"\n";
            #endif      
          }
      }
    
        typedef
      value_t
    (funcs_t::* bc_fun_t)( value_t t_val, istk_indices_t const& s_iter)
      //Boundary condition function
      ;
      
        typedef
      boost::array
      < bc_fun_t
      , index_bounds_value_size
      >
    bc_funs_axis_t  
      ;
        typedef
      std::vector
      < bc_funs_axis_t
      >
    bc_funs_space_t  
      ;
        typedef
      typename istk_indices_t::index_t
    index_t
      ;
      void
    boundary_conditions_axis
      ( value_t t_val
      , arr_data_iter_t& u_iter
      , istk_indices_t& s_iter
      , typename istk_indices_t::axis_t axis_v
      )
      {
        //#define TRACE_BOUNDARY_CONDITIONS_AXIS
        #ifdef TRACE_BOUNDARY_CONDITIONS_AXIS
            ::boost::trace_scope
          ts("boundary_conditions_axis.");
        #endif
              typedef
            typename istk_indices_t::index_t
          index_t
            ;
            bc_funs_axis_t 
          bc_funs_axis_v=funcs().bc_funs_space_v[axis_v];
          index_t offset_lower=0;
          index_t offset_upper=s_iter[axis_v].length_val()-1;
          for
            ( unsigned index_bound_side=index_bound_lower
            ; index_bound_side<index_value
            ; ++index_bound_side
              , std::swap(offset_lower,offset_upper)
            )
          {
              s_iter.axis_offsets_put(axis_v,offset_lower,offset_upper);
            #ifdef TRACE_BOUNDARY_CONDITIONS_AXIS
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
                #ifdef TRACE_BOUNDARY_CONDITIONS_AXIS
                  auto const offset_space=s_iter.offset_space_val();
                    ::boost::trace_scope
                  ts("for(i_space=)");
                  std::cout
                    <<":i_space="<<i_space
                    <<":offset_space="<<offset_space
                    <<"\n";
                #endif
                  value_t u_val=(funcs().*bc_funs_axis_v[index_bound_side])( t_val, s_iter);
                  value_t&u_ref=u_iter[s_iter.offset_space_val()];
                  u_ref=u_val;
                #ifdef TRACE_BOUNDARY_CONDITIONS_AXIS
                  std::cout<<"u_val["<<t_val<<","<<s_iter<<"]="<<u_val<<"\n";
                #endif
              }//exit for(i_space=)
          }//exit for(index_bound_side=)
      }
      void
    boundary_conditions( value_t t_val, arr_data_iter_t& u_iter, istk_indices_t& s_iter)
      {
        #define TRACE_BOUNDARY_CONDITIONS
              typedef
            typename istk_indices_t::axis_t
          axis_t
            ;
            axis_t const
          rank=s_iter.rank();
        #ifdef TRACE_BOUNDARY_CONDITIONS
            ::boost::trace_scope
          ts("boundary_conditions.");
          std::cout<<"rank="<<rank<<"\n"<<"indices_v=\n"<<s_iter<<"\n";
        #endif
          s_iter.axes_offsets_put();
          for
            ( axis_t axis_v=0
            ; axis_v<rank
            ; ++axis_v
            )
          {
              boundary_conditions_axis
              ( t_val
              , u_iter
              , s_iter
              , axis_v
              );
              s_iter.axis_offsets_put(axis_v,1,1)
                //don't write to axis_v boundaries
                //in subsequent calls to boundary_conditions_axis
                //in this loop.
                ;
            #ifdef TRACE_BOUNDARY_CONDITIONS
              std::cout<<"axis_v="<<axis_v<<"\n";
            #endif
          }//exit for(axis_v=)
      }
    
    funcs_grid_iters
      ( grid_axes_t const& a_grid_axes
      )
      : grid_axes_t( a_grid_axes)
      , lengths_u(mk_lengths_u())
      , lengths_s( lengths_u.begin()+1, lengths_u.end())
      , u(lengths_u)
      , u_iter
        ( u.data().begin()+u.offset()
        )
      , space_istk_is
        ( u.length_strides().begin()+1
        , u.length_strides().end()
        )
      , time_istk_is
        ( u.length_strides().begin()
        , u.length_strides().begin()+1
        )
      {
      }

        typedef
      typename array_t::length_dir_t
    length_dir_t
      ;
        typedef
      std::vector
      < length_dir_t
      >
    length_dirs_t
      ;    
      length_dirs_t
    lengths_u
      /**@brief
       *  Lengths of time and space axes.
       */
      ;
      length_dirs_t
    mk_lengths_u()
      {
            auto const&
          axes_l=this->axes();
            unsigned const
          rank=axes_l.size();
            length_dirs_t
          lengths_u
            ( rank
            );
          lengths_u[0]=
          #if 1
            axes_l[0].size() //to keep history of all iterations.
          #else
            2 //to save space.
          #endif
            ;
          for(unsigned i=1; i<rank; ++i)
              lengths_u[i]=axes_l[i].size();
          std::cout<<"lengths_u="<<lengths_u<<"\n";
          return lengths_u;
      }
      length_dirs_t
    lengths_s
      /**@brief
       *  Lengths of the space axes.
       */
      ;
      array_t 
    u
     /**@brief
      * u(it,ix1,ix2,...ixn)=temperature 
      *   at position:
      *     ( this->axes()[1][ix1]
      *     , this->axes()[2][ix2]
      *     ,...
      *     , this->axes()[n][ixn]
      *     )
      *   (where n=this->axes().size()-1)
      *   at time(this->axes()[0][it].
      */
      ;
      arr_data_iter_t
    u_iter
      ;
      istk_indices_t
    space_istk_is
      ;
      istk_indices_t
    time_istk_is
      ;
      void
    solve_estim_err()
      /**@brief
       *  Estimate solution to equation, 
       *  then calculate error in estimated solution.
       */
    {
        funcs().solve();
          array_dyn<estim_exact>
        estim_exact_arr(lengths_u)
          ;
          typename array_dyn<estim_exact>::data_t::iterator
        estim_exact_iter=estim_exact_arr.data().begin()
          ;
        time_istk_is.axes_offsets_put();
        space_istk_is.axes_offsets_put();
          auto const
        t_space = time_istk_is.space()
          ;
          auto const
        s_space = space_istk_is.space()
          ;
          std::vector<hot_spots>
        time_hot_spots
        ;
        for( int i_time=0; i_time<t_space; ++i_time, ++time_istk_is)
        {
            time_hot_spots.push_back(hot_spots(5));
            auto const o_time=time_istk_is.offset_space_val();
            for( int i_space=0; i_space<s_space; ++i_space, ++space_istk_is)
            {
                auto const o_space=space_istk_is.offset_space_val();
                unsigned const o_all=o_time+o_space;
                value_t estim=u_iter[o_all];
                value_t exact=funcs().
                  exact_indices
                  ( this->axes()[0][i_time]
                  , space_istk_is
                  );
                estim_exact_iter[o_all]=estim_exact(estim,exact);
                time_hot_spots.back().push_spot_if
                  ( estim_exact_iter[o_all].err()
                  , space_istk_is
                  );
            }
        }
        
        std::ios_base::fmtflags fmtflags0=std::cout.flags();
        unsigned precision0=std::cout.precision();
        std::cout<<"estim_exact=\n"<<estim_exact_arr<<"\n.";
        std::cout<<"hot_spots=\n";
        std::cout<<"{ ";
        for( int i_time=0; i_time<t_space; ++i_time)
        {
            if(0<i_time)std::cout<<", ";
            std::cout<<indent_buf_in;
            hot_spots const& hot_spots_i=time_hot_spots[i_time];
            int n_spot=hot_spots_i.size();
            std::cout<<"{ ";
            for( int i_spot=0; i_spot<n_spot; ++i_spot)
            {
                if(0<i_spot)std::cout<<", ";
                hot_spot const& hot_spot_i=hot_spots_i[i_spot];
                std::cout<<"{ ";
                std::cout<<"err:"<<hot_spot_i.my_err;
                std::cout<<", ";
                std::cout<<"ndx:"<<hot_spot_i.my_indices;
                std::cout<<"}\n";
            }
            std::cout<<"}\n";
            std::cout<<indent_buf_out;
        }
        std::cout<<"}\n";
        std::cout<<std::resetiosflags(std::cout.flags());
        std::cout<<std::setiosflags(fmtflags0)<<std::setprecision(precision0);
    }
};//exit funcs_grid_iters

#define DIFF_ALT_DIR_EXPLICIT
#ifdef  DIFF_ALT_DIR_EXPLICIT
  template
  < typename FunctionsDerived
  >
struct diff_alt_dir_explicit
  /**@brief
   *  Solves diffusion eq with method described in [DuffyAde2011].
   */
;
  template
  < template< typename V>class FunctionsDerived
  , typename Value
  >
struct diff_alt_dir_explicit
  < FunctionsDerived
    < Value
    >
  >
: funcs_grid_iters
  < FunctionsDerived
    < Value
    >
  >
{
        typedef
      FunctionsDerived
      < Value
      >
    funcs_t
      ;
      funcs_t&
    funcs()
    {
        return static_cast<funcs_t&>(*this);
    }
        typedef
      funcs_grid_iters
      < funcs_t
      >
    super_t
      ;
        typedef
      typename super_t::arr_data_iter_t
    arr_data_iter_t
      ;
        typedef
      typename super_t::array_t
    array_t
      ;
        typedef
      typename super_t::istk_indices_t
    istk_indices_t
      ;
        using
      super_t::
    lengths_s
      ;
        using
      super_t::
    lengths_u
      ;
        using
      super_t::
    u
      ;
        using
      super_t::
    u_iter
      ;
        using
      super_t::
    space_istk_is
      ;
        using
      super_t::
    time_istk_is
      ;
        using
      super_t::
    initial_conditions
      ;
        using
      super_t::
    boundary_conditions
      ;
    diff_alt_dir_explicit
    ( grid_axes_diff<value_t>const& a_grid_axes
    )
    : super_t(a_grid_axes)
    {}
    
    void solve()
    //solve the differential equation:
    {
          unsigned const
        s_rank=space_istk_is.rank();
        initial_conditions( u_iter, space_istk_is);
      #if 1
      //#define TRACE_SOLN_DIFF_EQ
      #ifdef TRACE_SOLN_DIFF_EQ
        ::boost::trace_scope ts("diff_alt_dir_explicit::solve()");
      #endif
          std::vector<value_t>
        t_div_s2(s_rank)
          //These are the lambda's in equation(11) of [DuffyAde2011] 
          //*except* these take into account a diffusivity 
          //other than 1.0.
          ;
          value_t
        sum_tds=0.0
          //This is the sigma of equation(11) of [DuffyAde2011] 
          ;
        for( unsigned s_axis=0; s_axis<s_rank; ++s_axis)
        {
            value_t del_s_axis=this->axes()[s_axis+1].del();
            t_div_s2[s_axis]
              = ( this->axes()[0].del()
                * this->diffusivity //in [DuffyAde201], this was 1.0
                )/
                ( del_s_axis
                * del_s_axis
                );
            sum_tds+=t_div_s2[s_axis];
          #ifdef TRACE_SOLN_DIFF_EQ
            std::cout
              <<":s_axis="<<s_axis
              <<":del_s_axis="<<del_s_axis
              <<":t_div_s2="<<t_div_s2[s_axis]
              <<"\n";
          #endif
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
      #ifdef TRACE_SOLN_DIFF_EQ
        std::cout
          <<"sum_tds="<<sum_tds<<"\n"
          <<"one_plus_sum_tds="<<one_plus_sum_tds<<"\n"
          <<"one_minus_sum_tds="<<one_minus_sum_tds<<"\n"
          <<"one_minus_div_one_plus_sum_tds="<<one_minus_div_one_plus_sum_tds<<"\n"
          ;
      #endif
          std::vector<value_t>
        t_div_s2_div_one_plus_sum_tds(s_rank)
          ;
        for( unsigned s_axis=0; s_axis<s_rank; ++s_axis)
        {
            t_div_s2_div_one_plus_sum_tds[s_axis]
              =t_div_s2[s_axis]/one_plus_sum_tds;
        }
          unsigned const
        n_time=this->axes()[0].size();
        for
          ( unsigned i_time=0
          ; i_time<n_time-1
          #if 0
            && i_time<1 //just for debugging.
          #endif
          ; ++i_time
          )
        {
          #ifdef TRACE_SOLN_DIFF_EQ
            ::boost::trace_scope ts("trace_soln_diff_eq");
            std::cout<<"i_time.{="<<i_time<<"\n";
            std::cout<<"u["<<i_time<<"]=\n"<<u<<".\n";
          #endif
              arr_data_iter_t
            ut_now_iter=u_iter+time_istk_is.offset_space_val()
              //u at it-th time.
              ;
            ++time_istk_is
              //increment time to (i_time+1)-th time.
              ;
              arr_data_iter_t
            ut_nxt_iter=u_iter+time_istk_is.offset_space_val()
              //u at (i_time+1)-th time.
              ;
            //std::cout<<"ut_nxt_iter-ut_now_iter="<<(ut_nxt_iter-ut_now_iter)<<"\n";
            boundary_conditions
              ( this->axes()[0][i_time+1]
              , ut_nxt_iter
              , space_istk_is
              )
              //update boundary nodes in mesh
              ;
              auto const 
            s_space=space_istk_is.space()
              //The number of nodes in inner mesh.
              ;
          #if 0
            std::cout<<"after boundary_conditions:\n";
            std::cout<<"space_istk_is.space()="<<s_space<<"\n";
            std::cout<<"u["<<i_time+1<<"]=\n"<<u<<".\n";
          #endif
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
                  typename istk_indices_t::stride_t
                stride_t;
                  array_t 
                sweeps[sweeps_size]=
                  { array_t(lengths_s)//The U in equation( 9) of [DuffyAde2011]
                  , array_t(lengths_s)//The V in equation(10) of [DuffyAde2011]
                  };
                ;
                    typedef
                  typename istk_indices_t::axis_depth_t
                axis_depth_t
                ;
                    typedef
                  axis_depth_t(istk_indices_t::*
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
                      array_t&
                    sweep_i_arr=sweeps[i_sweep];
                    std::copy_n
                      ( ut_now_iter-u.offset()
                      , sweep_i_arr.data().size()
                      , sweep_i_arr.data().begin()
                      );
                      arr_data_iter_t
                    sweep_i_iter=sweep_i_arr.data().begin()+sweep_i_arr.offset();
                    enum
                    { u_stride_index
                    , s_stride_index
                    };
                      unsigned const
                    stride_indices[sweeps_size]=
                      { i_sweep
                      , (i_sweep+1)%sweeps_size
                      }
                      // =={0,1} during i_sweep==0
                      // =={1,0} during i_sweep==1
                      ;
                    for//each node in inner mesh, calculate sweeps values.
                      ( stride_t s_node=0
                      ; s_node<s_space
                      ; ++s_node
                        , (space_istk_is.*incdec_v)()
                      )
                    {
                      #ifdef TRACE_UPDATE_INNER_MESH
                        ::boost::trace_scope ts("s_node");
                        std::cout<<"s_node="<<s_node<<"\n";
                        std::cout<<"space_istk_is="<<space_istk_is<<"\n";
                      #endif
                          auto const 
                        space_offset=space_istk_is.offset_space_val();
                          arr_data_iter_t
                        uts_node_iter=ut_now_iter+space_offset;
                          arr_data_iter_t
                        sweep_node_iter=sweep_i_iter+space_offset;
                          value_t&
                        sweep_node0=sweep_node_iter[0]
                          //The lhs of equation(9 or 10) of [DuffyAde2011]
                          //divided by (1+lower case sigma).
                        ;
                        sweep_node0=uts_node_iter[0]*one_minus_div_one_plus_sum_tds
                          //The rhs of this assignment is
                          //1st term on rhs of equation(9 or 10)of [DuffyAde2011]
                          //divided by (1+lower case sigma)[in [DuffyAde2011]]
                          //[or one_plus_sum_tds here].
                        ;
                        { //add to sweep_node0, the rhs of equation( 9 or 10)
                          //except for 1st term.
                            for
                              ( unsigned s_axis=0
                              ; s_axis<s_rank
                              ; ++s_axis
                              )
                            {
                              #ifdef TRACE_UPDATE_INNER_MESH
                                ::boost::trace_scope ts("s_axis");
                                std::cout<<"s_axis="<<s_axis<<"\n";
                              #endif
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
                                  ]
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
                              #ifdef TRACE_UPDATE_INNER_MESH
                                std::cout
                                  <<":stride_index_s="<<stride_indices[s_stride_index]
                                  <<":stride_u="<<stride_u
                                  <<":stride_s="<<stride_s
                                  <<":uts_node_stride="<<uts_node_stride
                                  <<":sweep_node_stride="<<sweep_node_stride
                                  <<":indices_s="
                                  <<sweep_i_arr.indexs_at_offset
                                    ( space_offset
                                    + stride_s
                                    )
                                  <<"\n";
                              #endif
                            }//for stride_iter_v
                        } //add to sweep_node0
                    }//for(s_node, for sweeps
                }//for(i_sweep
                for//each node in inner mesh, calculate next u value.
                   //as average of the just calculated sweeps data.
                   //This loop implements equation(6) of [DuffyAde2011].
                  ( stride_t s_node=0
                  ; s_node<s_space
                  ; ++s_node
                    , ++space_istk_is
                  )
                {
                  #if 0
                    ::boost::trace_scope ts("average sweeps");
                    std::cout<<"space_istk_is="<<space_istk_is<<"\n";
                  #endif
                      auto const 
                    space_offset=space_istk_is.offset_space_val();
                      auto&
                    uts_nxt_node=*(ut_nxt_iter+space_offset);
                    uts_nxt_node=0.0;
                    for
                      ( unsigned i_sweep=sweep_up
                      ; i_sweep<sweeps_size
                      ; ++i_sweep
                      )
                    {
                          array_t&
                        sweep_i_arr=sweeps[i_sweep];
                          arr_data_iter_t
                        sweep_iter=sweep_i_arr.data().begin()
                          +sweep_i_arr.offset()
                          +space_offset
                          ;
                        uts_nxt_node+=*sweep_iter;//sum sweeps
                    }//for(i_sweep
                    uts_nxt_node/=value_t(sweeps_size);//average sweeps
                  #if defined(TRACE_UPDATE_INNER_MESH) || 0
                    std::cout
                      <<":exact="<<uts_nxt_node.exact
                      <<":%err="<<uts_nxt_node.err_percent()
                      <<"\n";
                  #endif
                }//for(s_node
              #undef TRACE_UPDATE_INNER_MESH
            } //update inner nodes in mesh
        }//for(i_time=...)
        std::cout<<"u["<<n_time<<"]=\n"<<u<<".\n";
      #undef TRACE_SOLN_DIFF_EQ
      #endif
    }
};//exit diff_alt_dir_explicit
#endif
#define DIFF_ALT_DIR_IMPLICIT_INNOCENT
#ifdef DIFF_ALT_DIR_IMPLICIT_INNOCENT
  template
  < typename FunctionsDerived
  >
struct diff_alt_dir_implicit_innocent
  /**@brief
   *  Solves diffusion eq with "innocent-looking" implicit method 
   *  described in [DuffyFdm2006] in section 19.5 on page 217
   *  in equations(19.34).
   */
;
  template
  < template< typename V>class FunctionsDerived
  , typename Value
  >
struct diff_alt_dir_implicit_innocent
  < FunctionsDerived
    < Value
    >
  >
: funcs_grid_iters
  < FunctionsDerived
    < Value
    >
  >
{
        typedef
      FunctionsDerived
      < Value
      >
    funcs_t
      ;
      funcs_t&
    funcs()
    {
        return static_cast<funcs_t&>(*this);
    }
        typedef
      funcs_grid_iters
      < funcs_t
      >
    super_t
      ;
        typedef
      typename super_t::arr_data_iter_t
    arr_data_iter_t
      ;
        typedef
      typename super_t::array_t
    array_t
      ;
        typedef
      typename super_t::istk_indices_t
    istk_indices_t
      ;
        typedef
      typename array_t::stride_t
    stride_t
      ;
        using
      super_t::
    initial_conditions
      ;
        using
      super_t::
    boundary_conditions
      ;
        using
      super_t::
    boundary_conditions_axis
      ;
        using
      super_t::
    lengths_s
      ;
        using
      super_t::
    lengths_u
      ;
        using
      super_t::
    u
      ;
        using
      super_t::
    u_iter
      ;
        using
      super_t::
    space_istk_is
      ;
        using
      super_t::
    time_istk_is
      ;
    diff_alt_dir_implicit_innocent
    ( grid_axes_diff<value_t>const& a_grid_axes
    )
    : super_t(a_grid_axes)
    {}
    
    void solve()
    //solve the differential equation:
    {
          unsigned const
        s_rank=space_istk_is.rank();
        initial_conditions( u_iter, space_istk_is);
      #if 1
      //#define TRACE_SOLN_DIFF_EQ
      #ifdef TRACE_SOLN_DIFF_EQ
        ::boost::trace_scope ts("diff_alt_dir_implicit_innocent::solve()");
      #endif
          value_t const
        dt_div_s_rank
          //time delta divided by space rank.
          //This is the k/3 (where s_rank replaces the 3) 
          //in [DuffyFdm2006] equaiton(19.34).
          = this->axes()[0].del()/value_t(s_rank)
          ;
            typedef
          std::vector<value_t>
        del_s2_t
          ;
          struct
        del_s2_mk
          {
                  typedef
                typename grid_axes_diff<value_t>::grid_axes_points_t
              axes_t
              ;
                  static
                del_s2_t
              _
                ( axes_t const& a_axes
                )
              {
                  auto const rank=a_axes.size();
                  del_s2_t result(rank-1);
                  for(unsigned s_axis=1; s_axis<rank; ++s_axis)
                  {
                      value_t del_axis=a_axes[s_axis].del();
                      result[s_axis-1]=del_axis*del_axis;
                  }
                  return result;
              }
          };
          del_s2_t const
        del_s2_v
          = del_s2_mk::_( this->axes() )
          ;
          value_t
        t_nxt=this->axes()[0][0];
      #ifdef TRACE_SOLN_DIFF_EQ
        std::cout
          <<":dt_div_s_rank="<<dt_div_s_rank
          <<"\n"
          ;
      #endif
          unsigned const
        n_time=this->axes()[0].size();
        for
          ( unsigned i_time=0
          ; i_time<n_time-1
          #if 0
            && i_time<1 //just for debugging.
          #endif
          ; ++i_time
          )
        {
              value_t
            t_now=t_nxt;
            t_nxt=this->axes()[0][i_time+1];
          #ifdef TRACE_SOLN_DIFF_EQ
            ::boost::trace_scope ts("trace_soln_diff_eq");
            std::cout<<"i_time.{="<<i_time<<"\n";
            std::cout<<"t_now="<<t_now<<"\n";
            std::cout<<"u["<<i_time<<"]=\n"<<u<<".\n";
          #endif
              arr_data_iter_t
            ut_now_iter=u_iter+time_istk_is.offset_space_val()
              //u at i_time-th time.
              ;
            ++time_istk_is
              //increment time to (i_time+1)-th time.
              ;
              arr_data_iter_t
            ut_nxt_iter=u_iter+time_istk_is.offset_space_val()
              //u at (i_time+1)-th time.
              ;
              auto const
            s_rank=space_istk_is.rank()
              ;
            {//EQUATIONS_19_34
             //  This block implements equations(19.34) of
             //  [DuffyFdm2006] for time step, i_time.
              #define TRACE_EQUATIONS_19_34
              #ifdef TRACE_EQUATIONS_19_34
                ::boost::trace_scope ts("EQUATIONS_19_34");
              #endif
                  std::vector<array_t>
                fractional_step(s_rank-1, array_t(lengths_s))
                ;
                  std::vector<arr_data_iter_t>
                steps
                  ( 1+s_rank
                    //= 2 (begin/end steps)
                    //+ s_rank-1 (fractional steps)
                  )
                ;
                steps.front()=ut_now_iter;//begin step
                steps.back()=ut_nxt_iter;//end step
                for
                  ( unsigned i_step=1
                  ; i_step<s_rank
                  ; ++i_step
                  )
                {
                    steps[i_step]=fractional_step[i_step-1].data().begin();
                }//for(i_step
                  value_t 
                t_frac=t_now;
                  istk_indices_t
                space_istk_rotated(space_istk_is)
                  //This will have its axes rotated during each
                  //iteration of the following loop so that
                  //solve_tridiag, which solves for the
                  //last axis, will solve for each axes in
                  //in turn.
                  ;
                for
                  ( unsigned i_step=0
                  ; i_step<s_rank
                  ; ++i_step
                  )
                {
                    space_istk_rotated.rotate(1);
                  #define TRACE_FRACTIONAL_STEPS
                  #ifdef TRACE_FRACTIONAL_STEPS
                    ::boost::trace_scope ts("fractional step");
                    std::cout
                      <<":i_step="<<i_step
                      <<":rotation="<<space_istk_rotated.rotation()
                      <<"\n";
                  #endif
                      array_t
                    rhs(lengths_s);
                      arr_data_iter_t 
                    rhs_iter=rhs.data().begin()
                      //the rhs of equations(19.41).
                      //Calculated below.
                      ;
                      arr_data_iter_t&
                    old_iter=steps[i_step]
                      //the previous fractional step.
                      //IOW, the U on rhs of equations(19.41).
                      ;
                      arr_data_iter_t&
                    lhs_iter=steps[i_step+1]
                      //the current fractional step.
                      //IOW, the U on lhs of equations(19.41).
                      ;
                    t_frac+=dt_div_s_rank;
                    space_istk_is.axes_offsets_put(1,1);
                    space_istk_is.axis_offsets_put(i_step,0,0);
                    boundary_conditions_axis
                      ( t_frac
                      , rhs_iter
                      , space_istk_is
                      , i_step
                      )
                      //This stores into rhs_iter i_step axis boundaries
                      //the rhs of equations(19.44) of [DuffyFdm2006].
                      ;
                  #ifdef TRACE_FRACTIONAL_STEPS
                    {
                        std::cout
                          <<":t_frac="<<t_frac
                          <<":rhs["<<i_time<<","<<(i_step+1)<<"](after boundary_conditions)=\n"<<rhs
                          <<".\n";
                    }
                  #endif
                    {//interior_rhs
                      //#define TRACE_INTERIOR_RHS
                      #ifdef TRACE_INTERIOR_RHS
                          ::boost::trace_scope
                        ts("interior_rhs");
                      #endif
                        space_istk_rotated.axes_offsets_put(1,1)
                          //restrict to interior nodes.
                          ;
                          auto const
                        s_space_inner=space_istk_rotated.space();
                        for
                          ( int s_node=0
                          ; s_node<s_space_inner
                          ; ++s_node
                            , ++space_istk_rotated
                          )
                        //For all interior (i.e. not on boundaries) nodes,
                        //store into rhs_iter 
                        //the rhs of equations(19.41) of [DuffyFdm2006].
                        {
                              auto const
                            offset=space_istk_rotated.offset_space_val();
                            rhs_iter[offset]=old_iter[offset]
                              //this initializes rhs_iter with 
                              //the 1st summand of
                              //the rhs of equation(19.41) 
                              //of [DuffyFdm2006]
                              ;
                          #ifdef TRACE_INTERIOR_RHS
                            std::cout
                              <<":offset="<<offset
                              <<":indices="<<space_istk_rotated.indices()
                              <<":rhs_iter[offset]=old_iter[offset]="<<old_iter[offset]
                              <<"\n"
                              ;
                          #endif
                              value_t
                            d2_sum=0.0;
                            for
                              ( unsigned r_axis=0
                              ; r_axis<s_rank-1
                              ; ++r_axis
                              )
                            {//For axes whose derivatives appear on rhs of
                             //equations(19.41) of [DuffyFdm2006]
                             //sum those those derivatives into d2_sum.
                                  stride_t
                                stride_v=space_istk_rotated[r_axis].stride_val();
                                  value_t 
                                d2_axis
                                  = (   old_iter[offset-stride_v]
                                    - 2*old_iter[offset]
                                    +   old_iter[offset+stride_v]
                                    )
                                  / ( del_s2_v[r_axis]
                                    )
                                  ; //rhs of equation(18.13) of [DuffyFdm2006]
                                    //for axis, r_axis, at node, s_node.
                                d2_sum+=d2_axis;
                            }//for(r_axis)
                            rhs_iter[offset]+=dt_div_s_rank*d2_sum
                              //This adds to rhs_iter
                              //the 2nd summand of
                              //the rhs of equations(19.41)
                              //of [DuffyFdm2006].
                              ;
                          #ifdef TRACE_INTERIOR_RHS
                            std::cout
                              <<":d2_sum="<<d2_sum
                              <<":rhs_iter[offset]="<<rhs_iter[offset]
                              <<"\n"
                              ;
                          #endif
                        }//for(s_node)
                    }//interior_rhs
                  #ifdef TRACE_FRACTIONAL_STEPS
                    std::cout<<"rhs(after equations(19.41))=\n"<<rhs;
                  #endif
                    {//solve tridiagonal system.
                        space_istk_rotated.axis_offsets_put(s_rank-1,0,0)
                          //allow access to borders on s_rank-1 rotated axis.
                          ;
                          auto const
                        l_last=space_istk_rotated[s_rank-1].length_val()
                          //length of last (the (s_rank-1)-th) axis.
                          ;
                          struct
                        mk_tridiag
                        {
                                typedef
                              tridiag<value_t>
                            tridiag_t
                            ;
                                static
                              tridiag_t
                            make 
                              ( unsigned n
                              , value_t del_fract_t//fractional delta time
                              , value_t del_s//delta space.
                              )
                            {
                                  tridiag_t
                                result=tridiag_t(std::size_t(n));
                                  value_t
                                dt_div_ds2=
                                  del_fract_t
                                  / 
                                  ( del_s*del_s
                                  )
                                  ;
                                for
                                  ( unsigned i=1
                                  ; i<n-1
                                  ; ++i 
                                  )
                                  /**@brief
                                   *  For nodes *not* on boundary,
                                   *  use equations(19.41) from page 220
                                   *  of [DuffyFdm2006].
                                   */
                                {
                                    if(0<i)result.l(i)=-dt_div_ds2;
                                    result.d(i)=1.0+2*dt_div_ds2;
                                    if(i<n-1)result.u(i)=-dt_div_ds2;
                                }
                                for
                                  ( unsigned i=0
                                  ; i<n
                                  ; i+=n-1
                                  )
                                  /**@brief
                                   *  For nodes on boundary,
                                   *  use equations(19.44) from page 220
                                   *  of [DuffyFdm2006].
                                   */
                                {
                                    if(0<i)result.l(i)=0.0;
                                    result.d(i)=1.0;//copy boundary condition from rhs.
                                    if(i<n-1)result.u(i)=0.0;
                                }
                                return result;
                            }
                        };
                          tridiag<value_t>
                        a_tridiag
                          = mk_tridiag::make
                            ( l_last
                            , dt_div_s_rank
                            , this->axes()[s_rank].del()
                            )
                          ;
                      #ifdef TRACE_FRACTIONAL_STEPS
                        std::cout<<"a_tridiag=\n"<<a_tridiag;
                      #endif
                          solve_tridiag<value_t>
                        a_solver
                          ( space_istk_rotated
                          , a_tridiag
                          , rhs_iter
                          , lhs_iter
                          );
                        if(a_solver.upper_triangulate_trid(0.001))
                        {
                            a_solver.upper_triangulate_rhs();
                            a_solver.back_substitute();
                          #ifdef TRACE_FRACTIONAL_STEPS
                            istk_indices_t space_istk_border(space_istk_is);
                            space_istk_border.axes_offsets_put(0,0);
                            //std::cout<<"rhs(after solve_tridiag)=\n"<<rhs<<".\n";
                            array_iter_wrap<value_t> lhsw(lhs_iter,space_istk_border);
                            std::cout<<"lhsw["<<i_time<<","<<(i_step+1)<<"](after solve_tridiag)=\n"
                              <<lhsw<<".\n";
                          #endif
                        }
                        else
                        {
                            std::cerr<<"unable to solve tridiagonal system at "
                              <<i_time<<"-th time and"
                              <<i_step+1<<"-th step.\n";
                            throw std::bad_exception();
                        }
                        space_istk_rotated.axis_offsets_put(s_rank-1,1,1);
                    }//solve tridiagonal system.
                }//for(i_step=0)
              #ifdef TRACE_EQUATIONS_19_34
                std::cout
                  <<":t_nxt="<<t_nxt
                  <<":t_frac="<<t_frac
                  <<":rotation="<<space_istk_rotated.rotation()//should be 0.
                  <<"\n";  
              #endif
              #undef TRACE_EQUATIONS_19_34
            }//EQUATIONS_19_34
            {//boundary_conditions_lhs:
             //Purpose:
             //  During last step in the for(i_step=0...) loop in
             //  EQUATIONS_19_34 code block, the boundary conditions
             //  for last axis were set; however, those for the
             //  other axes were not.  This code block sets the
             //  boundary conditions for those other axes.
                typedef typename istk_indices_t::axis_t axis_t;
                axis_t n_axis=space_istk_is.rank();
                space_istk_is.axes_offsets_put()
                  //Allow writing to all borders...
                  ;
                for(axis_t i_axis=0; i_axis<n_axis-1; ++i_axis)
                {
                    boundary_conditions_axis( t_nxt, ut_nxt_iter, space_istk_is, i_axis);
                    space_istk_is.axis_offsets_put(i_axis,1,1)
                      //just like boundary_conditions loop, don't
                      //overwrite already calculated border.
                      ;
                }
            }//boundary_conditions_lhs
        }//for(i_time=...)
        std::cout<<"u["<<n_time<<"]=\n"<<u<<".\n";
      #undef TRACE_SOLN_DIFF_EQ
      #endif
    }
};//exit diff_alt_dir_implicit_innocent
#endif

  template
  < template< typename Soln>class FdmSolver
  >
struct fundamental
{

  template
  < typename Value=double
  >
struct soln
  : FdmSolver
    < soln
      < Value
      > 
    >
{
        typedef
      FdmSolver
      < soln
        < Value
        > 
      >
    solver_super_t
      ;
        typedef
      typename solver_super_t::value_t
    value_t
      ;
        typedef
      typename solver_super_t::istk_indices_t
    istk_indices_t
      ;
        typedef
      typename istk_indices_t::axis_t
    axis_t
      ;
        typedef
      typename solver_super_t::bc_funs_axis_t
    bc_funs_axis_t
      ;
        typedef
      typename solver_super_t::bc_funs_space_t
    bc_funs_space_t
      ;
        typedef
      typename solver_super_t::funcs_t
    funcs_t
      ;
      value_t
    exact_indices
      ( value_t t_val
      , istk_indices_t const& s_iter
      )
      /**@brief
       *  The fundamental solution to heat equation:
       *  References:
       *    [Churchill72]
       *      problem 8, page 150 of:
       *      _Operational Mathematics_
       *      Ruel V. Churchill
       *      McGraw-Hill, 1972.
       *    [Wiki2011]
       *      http:  *  en.wikipedia.org/wiki/Heat_equation#Fundamental_solutions
       *  However:
       *    [Wiki2011] differs from [Churchill72] slightly:
       *      [Wiki2011] has pow( 4*Pi*k*t, n/2) whereas
       *      [Churchill72] has sqrt(t).
       *    Since, in [Churchill72], the dimensionality, n=1,
       *    that's almost the same, the only difference being
       *    a constant factor, pow(4*Pi*k, n/2), both solution functions
       *    satisfy the homogeneous equation if either does.
       **@requires
       *  WHAT:
       *    t_zero<=t_val, for some "large enough" t_zero.
       *  WHY:
       *    See ss_divisor comments below.
       */
      {
        //#define TRACE_EXACT_INDICES
        #ifdef TRACE_EXACT_INDICES
          ::boost::trace_scope ts("exact_indices");
          std::cout<<":t_val="<<t_val<<":s_iter="<<s_iter<<"\n";
        #endif
            value_t
          sumsq=0.0;
            unsigned
          s_rank=s_iter.rank();
          for(unsigned s_axis=0; s_axis<s_rank; ++s_axis) 
          {
                value_t const 
              s_val
                = this->axes()
                  [ s_axis+1]
                  [ s_iter[s_axis].template get<index_value>() ]
                ;
              sumsq+=s_val*s_val;
            #ifdef TRACE_EXACT_INDICES
              std::cout<<":s_val="<<s_val<<":sumsq="<<sumsq<<"\n";
            #endif
          }
            value_t const
          s_rank_div_2=value_t(s_rank)/2.0
            //This is the n/2 in equation following sentence:
            //  The n-variable fundamental solution is the product of the
            //  fundamental solutions in each variable; i.e.,
            //in [Wiki2011].
            ;
            value_t
          ss_divisor=4.0*(this->diffusivity)*t_val
            //sum squares divisor.
            //  t_val must be not be 0; otherwise, divide by zero occurs
            //  in next statement, in 2 places.
            //  To avoid rounding errors, it must be greater than 0.0
            //  by some unknown amount(0.1 seems to work when
            //  diffusivity==1.0).
            ;
        #ifdef TRACE_EXACT_INDICES
          std::cout<<":ss_divisor="<<ss_divisor<<"\n";
        #endif
            value_t
          u_val=exp(-sumsq/ss_divisor)/pow(t_val,s_rank_div_2);
        #ifdef TRACE_EXACT_INDICES
          std::cout<<":u_val="<<u_val<<"\n";
        #endif
          return u_val;
      }
      
      value_t 
    ic_indices( istk_indices_t const& s_iter)
      {//initial conditions at indices, i_iter.
          return exact_indices( this->axes()[0][0], s_iter);
      }
    
      value_t
    bc_indices( value_t t_val, istk_indices_t const& s_iter)
      {//boundary conditions at it-th time at indices i_iter
          return exact_indices( t_val, s_iter);
      }
    
        static
      bc_funs_axis_t
    mk_bc_lower_upper()
      {
          bc_funs_axis_t const arr
          ={{ &funcs_t::bc_indices
            , &funcs_t::bc_indices
            }
           };
         return arr;
      }
      
        static
      bc_funs_space_t
    mk_bc_funs_space(unsigned s_rank)
      {
            bc_funs_space_t
          result
            ( s_rank
            , mk_bc_lower_upper()
            );
          return result;
      }
    
      bc_funs_space_t
    bc_funs_space_v
      ;
      
    soln( grid_axes_diff<value_t>const&a_grid)
      : solver_super_t(a_grid)
      , bc_funs_space_v
        ( mk_bc_funs_space(a_grid.axes().size()-1)
        )
      {}
};//exit soln
};//exit fundamental

  template
  < template<template<typename Asoln>class Asolver>class Problem
  , template<typename Asoln>class Method
  >
  void
solve_problem_method
  ( grid_axes_diff<value_t>const&grid_axes
  )
{
    typename Problem<Method>::template soln<> solver(grid_axes);
    solver.solve_estim_err();
};

int main()
{  
    boost::iostreams::indent_scoped_ostreambuf<char> indent_outbuf(std::cout,2);
        typedef
      grid_axis_size_bounds<value_t>
    grid_bounds_t;
      grid_axes_diff<value_t>
    grid_axes
      ({ grid_bounds_t(  3, 0.1, 1.0)
     #if 1
       , grid_bounds_t( 10, 0.0, 1.0)
       , grid_bounds_t(  9, 0.0, 1.0)
     #else
       , grid_bounds_t(  3, 0.0, 1.0)
       , grid_bounds_t(  4, 0.0, 1.0)
       , grid_bounds_t(  5, 0.0, 1.0)
     #endif
       }
      )
      ;
    std::cout<<grid_axes;
    #ifdef DIFF_ALT_DIR_EXPLICIT
    {
        std::cout<<"***alt_dir_explicit***\n";
        solve_problem_method<fundamental,diff_alt_dir_explicit>(grid_axes);
    }
    #endif
    #ifdef DIFF_ALT_DIR_IMPLICIT_INNOCENT
    {
        std::cout<<"***alt_dir_implicit_innocent***\n";
        solve_problem_method<fundamental,diff_alt_dir_implicit_innocent>(grid_axes);
    }
    #endif
    return 0;
}
