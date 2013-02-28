///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_MP_CPP_BIN_FLOAT_BACKEND_HPP
  #define BOOST_MP_CPP_BIN_FLOAT_BACKEND_HPP

  #include <vector>
  #include <boost/cstdint.hpp>
  #include <boost/multiprecision/number.hpp>
  #include <boost/math/policies/policy.hpp>

  namespace boost { namespace multiprecision {
  namespace backends
  {
    template<const boost::uint32_t my_digits2,
             class my_exponent_type         = boost::int32_t,
             class my_allocator             = void,
             class unsigned_short_data_type = boost::uint32_t,
             class unsigned_long_data_type  = boost::uint64_t,
             class eval_ops_signed_type     = signed long long,
             class eval_ops_unsigned_type   = unsigned long long,
             class eval_ops_float_type      = long double>
    class cpp_bin_float;
  } // namespace backends

  template<const boost::uint32_t my_digits2,
           class my_exponent_type,
           class my_allocator,
           class unsigned_short_data_type,
           class unsigned_long_data_type,
           class eval_ops_signed_type,
           class eval_ops_unsigned_type,
           class eval_ops_float_type>
  struct number_category<backends::cpp_bin_float<my_digits2,
                                                 my_exponent_type,
                                                 my_allocator,
                                                 unsigned_short_data_type,
                                                 unsigned_long_data_type,
                                                 eval_ops_signed_type,
                                                 eval_ops_unsigned_type,
                                                 eval_ops_float_type> > : public mpl::int_<number_kind_floating_point>
  {
  };

  namespace backends {
  namespace detail
  {
    template <class value_type, class my_allocator>
    struct cpp_bin_float_rebind
    {
       typedef typename my_allocator::template cpp_bin_float_rebind<value_type>::other type;
    };

    template <class value_type, const boost::uint32_t elem_number, class my_allocator>
    struct cpp_bin_float_dynamic_array : public std::vector<value_type, typename rebind<value_type, my_allocator>::type>
    {
       cpp_bin_float_dynamic_array() :
         std::vector<value_type, typename cpp_bin_float_rebind<value_type, my_allocator>::type>(static_cast<typename std::vector<value_type, typename cpp_bin_float_rebind<value_type, my_allocator>::type>::size_type>(elem_number), static_cast<value_type>(0))
       {
       }

             value_type* data()       { return &(*(this->begin())); }
       const value_type* data() const { return &(*(this->begin())); }
    };
  } // namespace detail

  template<const boost::uint32_t my_digits2,
           class my_exponent_type,
           class my_allocator,
           class unsigned_short_data_type,
           class unsigned_long_data_type,
           class eval_ops_signed_type,
           class eval_ops_unsigned_type,
           class eval_ops_float_type>
  class cpp_bin_float
  {
  public:
    BOOST_STATIC_ASSERT_MSG(boost::is_signed<my_exponent_type>::value, "ExponentType must be a signed built-in integer type.");

    typedef mpl::list<eval_ops_signed_type>   signed_types;
    typedef mpl::list<eval_ops_unsigned_type> unsigned_types;
    typedef mpl::list<eval_ops_float_type>    float_types;
    typedef my_exponent_type                  exponent_type;

   // Constructors
   cpp_bin_float() : my_data              (),
                     my_exp               (static_cast<my_exponent_type>(0)),
                     my_neg               (false),
                     my_fpclass           (cpp_bin_float_finite),
                     my_precision_in_elems(cpp_bin_float_elem_number)
    {
    }

  private:
    typedef enum enum_fpclass_type
    {
      cpp_bin_float_finite,
      cpp_bin_float_inf,
      cpp_bin_float_NaN
    }
    fpclass_type;

    // TBD: Implement a proper element number!
    static const boost::uint32_t cpp_bin_float_elem_number = static_cast<boost::uint32_t>(10U);

    #ifndef BOOST_NO_CXX11_HDR_ARRAY
      typedef typename mpl::if_<is_void<my_allocator>,
                                std::array<unsigned_short_data_type, cpp_bin_float_elem_number>,
                                detail::cpp_bin_float_dynamic_array<unsigned_short_data_type, cpp_bin_float_elem_number, my_allocator> >::type
      array_type;
    #else
      typedef typename mpl::if_<is_void<my_allocator>,
                                boost::array<unsigned_short_data_type, cpp_dec_float_elem_number>,
                                detail::cpp_bin_float_dynamic_array<unsigned_short_data_type, cpp_bin_float_elem_number, my_allocator> >::type
      array_type;
    #endif

    array_type       my_data;
    my_exponent_type my_exp;
    bool             my_neg;
    fpclass_type     my_fpclass;
    boost::uint32_t  my_precision_in_elems;

    // Construction from the floating-point class
    cpp_bin_float(const fpclass_type fp_class) : my_data              (),
                                                 my_exp               (static_cast<my_exponent_type>(0)),
                                                 my_neg               (false),
                                                 my_fpclass           (fp_class),
                                                 my_precision_in_elems(cpp_bin_float_elem_number)
    {
    }

    void from_eval_ops_unsigned_type(const eval_ops_unsigned_type& u);
  };

  } // namespace backends

  using boost::multiprecision::backends::cpp_bin_float;

  } } // namespace boost::multiprecision

#endif // BOOST_MP_CPP_BIN_FLOAT_BACKEND_HPP
