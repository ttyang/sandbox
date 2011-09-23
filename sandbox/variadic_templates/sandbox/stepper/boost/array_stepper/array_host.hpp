#ifndef BOOST_ARRAY_STEPPER_ARRAY_HOST_HPP_INCLUDED
#define BOOST_ARRAY_STEPPER_ARRAY_HOST_HPP_INCLUDED
namespace boost
{
namespace array_stepper
{
  template
  < typename Array
  >
  struct
array_host
{
      Array&
    my_array
    ;
        typedef typename
      Array::domain_t
    domain_t
    ;
        typedef typename
      domain_t::index_t
    index_t
    ;
        typedef typename
      domain_t::offset_t
    offset_t
    ;
        typedef typename
      domain_t::length_stride_t
    length_stride_t
    ;
        typedef typename
      domain_t::length_strides_t::const_iterator
    axis_iter_t
    ;
      axis_iter_t
    my_axis_beg
    ;
      axis_iter_t const
    my_axis_end
    ;
    array_host
      ( Array& a_array
      )
    : my_array(a_array)
    , my_axis_beg
      ( my_array.length_strides().begin()
      )
    , my_axis_end
      ( my_array.length_strides().end()
      )
    {
    }
    
      template
      < typename Visitor
      >
      void
    accept
      ( Visitor& a_viz
      )
    {
        if(my_array.rank() == 0)
        {
            a_viz.null_array();
        }
        else
        {
            accept_off_ax
            ( a_viz
            , my_array.offset()
            , my_axis_beg
            );
        }
    }
 private:
      template
      < typename Visitor
      >
      void
    accept_off_ax
      ( Visitor& a_viz
      , index_t offset
      , axis_iter_t axis_now
      )
    {
        if(axis_now==my_axis_end)
        {
            a_viz.visit_child(my_array.data()[offset]);
        }
        else
        {
            axis_iter_t axis_nxt=axis_now+1;
            length_stride_t const axis_length_stride=*axis_now;
            typedef typename length_stride_t::stride_t stride_t;
            typedef typename length_stride_t::length_t length_t;
            stride_t const axis_stride=axis_length_stride.stride();
            length_t const axis_length=axis_length_stride.length();
          #if 0
            std::cout
              <<":axis="<<axis_now-my_axis_beg
              <<":offset="<<offset
              <<":length="<<axis_length
              <<":stride="<<axis_stride
              <<"\n";
          #endif
            a_viz.pre_children();
            for(length_t i=0; i<axis_length; ++i)
            {
              #if 0
                std::cout
                  <<":i="<<i
                  <<"\n";
              #endif
                a_viz.pre_child( i);
                this->accept_off_ax
                  ( a_viz
                  , offset
                  , axis_nxt
                  );
                a_viz.post_child();
                offset+=axis_stride;
            }
            a_viz.post_children();
        }
    }
};  

}//exit array_stepper namespace
}//exit boost namespace
#endif
