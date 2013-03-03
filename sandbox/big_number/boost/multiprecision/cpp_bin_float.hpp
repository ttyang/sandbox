///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_MP_CPP_BIN_FLOAT_BACKEND_HPP
  #define BOOST_MP_CPP_BIN_FLOAT_BACKEND_HPP

  #include <limits>
  #include <boost/cstdint.hpp>
  #include <boost/multiprecision/number.hpp>
  #include <boost/math/policies/policy.hpp>
  #include <boost/multiprecision/detail/dynamic_array.hpp>

  namespace boost { namespace multiprecision {
  namespace backends
  {
  template<const boost::uint32_t my_digits2,
           class my_exponent_type       = boost::int32_t,
           class my_allocator           = void,
           class short_limb_type        = boost::uint32_t,
           class long_limb_type         = boost::uint64_t,
           class eval_ops_signed_type   = signed long long,
           class eval_ops_unsigned_type = unsigned long long,
           class eval_ops_float_type    = long double>
  class cpp_bin_float;

  template<const boost::uint32_t my_digits2,
           class my_exponent_type,
           class my_allocator,
           class short_limb_type,
           class long_limb_type,
           class eval_ops_signed_type,
           class eval_ops_unsigned_type,
           class eval_ops_float_type>
  struct number_category<backends::cpp_bin_float<my_digits2,
                                                 my_exponent_type,
                                                 my_allocator,
                                                 short_limb_type,
                                                 long_limb_type,
                                                 eval_ops_signed_type,
                                                 eval_ops_unsigned_type,
                                                 eval_ops_float_type> > : public mpl::int_<number_kind_floating_point>
  {
  };

  template<const boost::uint32_t my_digits2,
           class my_exponent_type,
           class my_allocator,
           class short_limb_type,
           class long_limb_type,
           class eval_ops_signed_type,
           class eval_ops_unsigned_type,
           class eval_ops_float_type>
  class cpp_bin_float
  {
  public:
    BOOST_STATIC_ASSERT_MSG(   boost::is_signed  <my_exponent_type>::value
                            && boost::is_integral<my_exponent_type>::value, "The exponent type must be a signed integral type.");

    static const boost::uint32_t cpp_bin_float_bits_number = my_digits2;
    static const boost::uint32_t cpp_bin_float_elem_number =    boost::uint32_t(boost::uint32_t(cpp_bin_float_bits_number * 2U) / std::numeric_limits<short_limb_type>::digits)
                                                             + (boost::uint32_t(boost::uint32_t(cpp_bin_float_bits_number * 2U) % std::numeric_limits<short_limb_type>::digits) != boost::uint32_t(0U) ? 1U : 0U);

    typedef mpl::list<eval_ops_signed_type>   signed_types;
    typedef mpl::list<eval_ops_unsigned_type> unsigned_types;
    typedef mpl::list<eval_ops_float_type>    float_types;
    typedef my_exponent_type                  exponent_type;

    // Constructors
    cpp_bin_float() : my_data             (),
                      my_exp              (static_cast<my_exponent_type>(0)),
                      my_neg              (false),
                      my_fpclass          (cpp_bin_float_finite),
                      my_precision_in_bits(cpp_bin_float_bits_number) { }

    cpp_bin_float(const char* s) : my_data             (),
                                   my_exp              (static_cast<ExponentType>(0)),
                                   my_neg              (false),
                                   my_fpclass          (cpp_bin_float_finite),
                                   my_precision_in_bits(cpp_bin_float_bits_number) 
    {
      const bool read_string_is_ok = read_string(s);
      static_cast<void>(read_string_is_ok);

      const bool is_neg = my_neg;
      my_neg = false;

      round_and_truncate();

      if(is_neg) { negate(); }
    }

    template<class integer_type>
    cpp_bin_float(integer_type i,
                  typename enable_if<is_unsigned<integer_type> >::type* = 0) : my_data             (),
                                                                               my_exp              (static_cast<my_exponent_type>(0)),
                                                                               my_neg              (false),
                                                                               my_fpclass          (cpp_bin_float_finite),
                                                                               my_precision_in_bits(cpp_bin_float_bits_number)
    {
      from_unsigned_type(i);
      round_and_truncate();
    }

    template<class integer_type>
    cpp_bin_float(integer_type i,
                  typename enable_if<is_signed<integer_type> >::type* = 0) : my_data             (),
                                                                             my_exp              (static_cast<my_exponent_type>(0)),
                                                                             my_neg              (false),
                                                                             my_fpclass          (cpp_bin_float_finite),
                                                                             my_precision_in_bits(cpp_bin_float_bits_number)
    {
      const bool is_neg = (i < static_cast<integer_type>(0));

      if(is_neg)
      {
        from_unsigned_type(static_cast<eval_ops_unsigned_type>(-i));
      }
      else
      {
        from_unsigned_type(static_cast<eval_ops_unsigned_type>(i));
      }

      round_and_truncate();

      if(is_neg) { negate(); }
    }

    cpp_bin_float(const cpp_bin_float& other) : data     (other.my_data),
                                                exp      (other.my_exp),
                                                neg      (other.my_neg),
                                                fpclass  (other.my_fpclass),
                                                prec_elem(other.my_precision_in_bits) { }

    template<const boost::uint32_t other_digits2,
             class other_et,
             class other_allocator>
    cpp_bin_float(const cpp_bin_float<other_digits2, other_et, other_allocator>& smaller_other,
                  typename enable_if_c<other_digits2 <= my_digits2>::type* = 0) : my_data             (),
                                                                                  my_exp              (smaller_other.my_exp),
                                                                                  my_neg              (smaller_other.my_neg),
                                                                                  my_fpclass          (smaller_other.my_fpclass),
                                                                                  my_precision_in_bits(smaller_other.my_precision_in_bits)
    {
      std::copy(smaller_other.my_data.begin(),
                smaller_other.my_data.begin() + smaller_other.cpp_bin_float_elem_number,
                my_data.begin());
    }

    template<const boost::uint32_t other_digits2,
             class other_et,
             class other_allocator>
    explicit cpp_bin_float(const cpp_bin_float<other_digits2, other_et, other_allocator>& larger_other,
                           typename disable_if_c<other_digits2 <= my_digits2>::type* = 0) : my_data             (),
                                                                                            my_exp              (larger_other.my_exp),
                                                                                            my_neg              (larger_other.my_neg),
                                                                                            my_fpclass          (larger_other.my_fpclass),
                                                                                            my_precision_in_bits(cpp_bin_float_bits_number)
    {
      // TODO: this doesn't round!
      std::copy(larger_other.my_data.begin(),
                larger_other.my_data.begin() + cpp_bin_float_elem_number,
                my_data.begin());
    }

    template<class float_type>
    cpp_bin_float(float_type val,
                  typename enable_if<is_floating_point<float_type> >::type* = 0) : my_data             (),
                                                                                   my_exp              (static_cast<my_exponent_type>(0)),
                                                                                   my_neg              (false),
                                                                                   my_fpclass          (cpp_bin_float_finite),
                                                                                   my_precision_in_bits(cpp_bin_float_bits_number) 
    {
      const bool is_neg = (val < float_type(0));

      from_float_type(static_cast<eval_ops_float_type>((!is_neg) ? val : -val));

      round_and_truncate();

      if(is_neg) { negate(); }
    }

    void negate() { if(!iszero()) { my_neg = !my_neg; } }

    bool iszero() const { return ((my_fpclass == cpp_bin_float_finite) && (my_data[0U] == static_cast<short_limb_type>(0U))); }

  private:
    typedef enum enum_fpclass_type
    {
      cpp_bin_float_finite,
      cpp_bin_float_inf,
      cpp_bin_float_NaN
    }
    fpclass_type;

    #ifndef BOOST_NO_CXX11_HDR_ARRAY
      typedef typename mpl::if_<is_void<my_allocator>,
                                std::array<short_limb_type, cpp_bin_float_elem_number>,
                                detail::dynamic_array<short_limb_type, cpp_bin_float_elem_number, my_allocator> >::type
      array_type;
    #else
      typedef typename mpl::if_<is_void<my_allocator>,
                                boost::array<short_limb_type, cpp_bin_float_elem_number>,
                                detail::dynamic_array<short_limb_type, cpp_bin_float_elem_number, my_allocator> >::type
      array_type;
    #endif

    array_type       my_data;
    my_exponent_type my_exp;
    bool             my_neg;
    fpclass_type     my_fpclass;
    boost::uint32_t  my_precision_in_bits;

    // Construction from the floating-point class
    cpp_bin_float(fpclass_type fp_class) : my_data             (),
                                           my_exp              (static_cast<my_exponent_type>(0)),
                                           my_neg              (false),
                                           my_fpclass          (fp_class),
                                           my_precision_in_bits(cpp_bin_float_elem_number) { }

    void from_unsigned_type(eval_ops_unsigned_type u)
    {
      boost::uint_least8_t i = boost::uint_least8_t(0U);

      while(u != unsigned_type(0U))
      {
        my_data[i] = short_limb_type(u);
        ++i;
        u >>= std::numeric_limits<short_limb_type>::digits;
        my_exp += std::numeric_limits<short_limb_type>::digits;
      }

      std::reverse(my_data.begin(), my_data.begin() + i);
    }

    void from_float_type(eval_ops_float_type a)
    {
      BOOST_MATH_STD_USING // ADL of std names, needed for frexp.

      int e2;
      eval_ops_float_type y = frexp(a, &e2);

      my_exp = static_cast<my_exponent_type>(e2);

      boost::uint_least8_t i = boost::uint_least8_t(0U);

      for( ; i < boost::uint_least8_t(std::numeric_limits<eval_ops_float_type>::digits / std::numeric_limits<short_limb_type>::digits); ++i)
      {
        y *= long_limb_type(long_limb_type(1U) << std::numeric_limits<short_limb_type>::digits);
        my_data[i] = static_cast<short_limb_type>(y);
        y -= my_data[i];
      }

      if((std::numeric_limits<eval_ops_float_type>::digits % std::numeric_limits<short_limb_type>::digits) != 0)
      {
        y *= long_limb_type(long_limb_type(1U) << (std::numeric_limits<eval_ops_float_type>::digits % std::numeric_limits<short_limb_type>::digits));
        my_data[i] = static_cast<short_limb_type>(y);
        y -= my_data[i];
      }
    }

    bool read_string(const char* s);

    void round_and_truncate();
  };

  template<const boost::uint32_t my_digits2,
           class my_exponent_type,
           class my_allocator,
           class short_limb_type,
           class long_limb_type,
           class eval_ops_signed_type,
           class eval_ops_unsigned_type,
           class eval_ops_float_type>
  bool cpp_bin_float<my_digits2,
                     my_exponent_type,
                     my_allocator,
                     short_limb_type,
                     long_limb_type,
                     eval_ops_signed_type,
                     eval_ops_unsigned_type,
                     eval_ops_float_type>::read_string(const char* s)
  {
    static_cast<void>(s);
    return false;
  }

  template<const boost::uint32_t my_digits2,
           class my_exponent_type,
           class my_allocator,
           class short_limb_type,
           class long_limb_type,
           class eval_ops_signed_type,
           class eval_ops_unsigned_type,
           class eval_ops_float_type>
  void cpp_bin_float<my_digits2,
                     my_exponent_type,
                     my_allocator,
                     short_limb_type,
                     long_limb_type,
                     eval_ops_signed_type,
                     eval_ops_unsigned_type,
                     eval_ops_float_type>::round_and_truncate()
  {
  }

  } // namespace backends

  using boost::multiprecision::backends::cpp_bin_float;

  } } // namespace boost::multiprecision

#endif // BOOST_MP_CPP_BIN_FLOAT_BACKEND_HPP
