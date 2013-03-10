///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Copyright 2013 John Maddock. Distributed under the Boost
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
  #include <boost/multiprecision/detail/utype_helper.hpp>

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
  }

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

  namespace backends
  {
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
                            && boost::is_integral<my_exponent_type>::value,
                            "The exponent type must be a signed integral type.");

    BOOST_STATIC_ASSERT_MSG(   (std::numeric_limits<short_limb_type>::is_signed == false)
                            && (std::numeric_limits< long_limb_type>::is_signed == false),
                            "The short and long limb types must both be unsigned.");

    BOOST_STATIC_ASSERT_MSG(   (std::numeric_limits<short_limb_type>::digits * 2) == (std::numeric_limits<long_limb_type>::digits),
                            "The short limb type must be exactly half the width of the long limb type.");

    BOOST_STATIC_ASSERT_MSG(std::numeric_limits<eval_ops_unsigned_type>::digits == (std::numeric_limits<eval_ops_signed_type>::digits + 1),
                            "The signed and unsigned integer evaluation ops types must have the same width.");

    BOOST_STATIC_ASSERT_MSG(std::numeric_limits<eval_ops_unsigned_type>::digits >= std::numeric_limits<short_limb_type>::digits,
                            "The evaluation ops types must be at least as wide as the short limb type.");

    // TBD: Number of guard digits, WRT support for std::numeric_limits<T>(max_digits10).
    static const boost::uint32_t cpp_bin_float_bits_number = boost::uint32_t(my_digits2 + 3);
    static const boost::uint32_t cpp_bin_float_elem_number =    boost::uint32_t(cpp_bin_float_bits_number / std::numeric_limits<short_limb_type>::digits)
                                                             + (boost::uint32_t(cpp_bin_float_bits_number % std::numeric_limits<short_limb_type>::digits) != boost::uint32_t(0U) ? 1U : 0U);

    // TBD: Right-justify the data in the data array (seems to be standard established by GMP, etc.).

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
                                   my_exp              (static_cast<my_exponent_type>(0)),
                                   my_neg              (false),
                                   my_fpclass          (cpp_bin_float_finite),
                                   my_precision_in_bits(cpp_bin_float_bits_number) 
    {
      const bool read_string_is_ok = read_string(s);

      static_cast<void>(read_string_is_ok);

      round_and_truncate();
    }

    template<class unsigned_integer_type>
    cpp_bin_float(unsigned_integer_type ui,
                  typename enable_if<is_unsigned<unsigned_integer_type> >::type* = 0) : my_data             (),
                                                                                        my_exp              (static_cast<my_exponent_type>(0)),
                                                                                        my_neg              (false),
                                                                                        my_fpclass          (cpp_bin_float_finite),
                                                                                        my_precision_in_bits(cpp_bin_float_bits_number)
    {
      from_unsigned_integer_type<unsigned_integer_type>(ui);
      round_and_truncate();
    }

    template<class signed_integer_type>
    cpp_bin_float(signed_integer_type si,
                  typename enable_if<is_signed<signed_integer_type> >::type* = 0) : my_data             (),
                                                                                    my_exp              (static_cast<my_exponent_type>(0)),
                                                                                    my_neg              (si < static_cast<signed_integer_type>(0)),
                                                                                    my_fpclass          (cpp_bin_float_finite),
                                                                                    my_precision_in_bits(cpp_bin_float_bits_number)
    {
      typedef typename boost::multiprecision::detail::utype_helper<std::numeric_limits<signed_integer_type>::digits>::exact unsigned_integer_type;

      if(my_neg)
      {
        from_unsigned_integer_type<unsigned_integer_type>(-si);
      }
      else
      {
        from_unsigned_integer_type<unsigned_integer_type>(si);
      }

      round_and_truncate();
    }

    cpp_bin_float(const cpp_bin_float& other) : my_data             (other.my_data),
                                                my_exp              (other.my_exp),
                                                my_neg              (other.my_neg),
                                                my_fpclass          (other.my_fpclass),
                                                my_precision_in_bits(other.my_precision_in_bits) { }

    template<const boost::uint32_t other_digits2,
             class other_et,
             class other_allocator,
             class other_short_limb_type,
             class other_long_limb_type,
             class other_eval_ops_signed_type,
             class other_eval_ops_unsigned_type,
             class other_eval_ops_float_type>
    cpp_bin_float(const cpp_bin_float<other_digits2,
                                      other_et,
                                      other_allocator,
                                      other_short_limb_type,
                                      other_long_limb_type,
                                      other_eval_ops_signed_type,
                                      other_eval_ops_unsigned_type,
                                      other_eval_ops_float_type>& less_eq_other,
                  typename enable_if_c<other_digits2 <= my_digits2>::type* = 0) : my_data             (),
                                                                                  my_exp              (less_eq_other.my_exp),
                                                                                  my_neg              (less_eq_other.my_neg),
                                                                                  my_fpclass          (less_eq_other.my_fpclass),
                                                                                  my_precision_in_bits(less_eq_other.my_precision_in_bits)
    {
      // TBD: Handle other limb types both larger and smaller than the limb type of *this.
      std::copy(less_eq_other.my_data.begin(),
                less_eq_other.my_data.begin() + less_eq_other.cpp_bin_float_elem_number,
                my_data.begin());
    }

    template<const boost::uint32_t other_digits2,
             class other_et,
             class other_allocator,
             class other_short_limb_type,
             class other_long_limb_type,
             class other_eval_ops_signed_type,
             class other_eval_ops_unsigned_type,
             class other_eval_ops_float_type>
    explicit cpp_bin_float(const cpp_bin_float<other_digits2,
                                               other_et,
                                               other_allocator,
                                               other_short_limb_type,
                                               other_long_limb_type,
                                               other_eval_ops_signed_type,
                                               other_eval_ops_unsigned_type,
                                               other_eval_ops_float_type>& larger_other,
                           typename disable_if_c<other_digits2 <= my_digits2>::type* = 0) : my_data             (),
                                                                                            my_exp              (larger_other.my_exp),
                                                                                            my_neg              (larger_other.my_neg),
                                                                                            my_fpclass          (larger_other.my_fpclass),
                                                                                            my_precision_in_bits(cpp_bin_float_bits_number)
    {
      // TBD: Do a proper rounding here.
      // TBD: Handle other limb types both larger and smaller than the limb type of *this.
      std::copy(larger_other.my_data.begin(),
                larger_other.my_data.begin() + cpp_bin_float_elem_number,
                my_data.begin());
    }

    template<class float_type>
    cpp_bin_float(float_type a,
                  typename enable_if<is_floating_point<float_type> >::type* = 0) : my_data             (),
                                                                                   my_exp              (static_cast<my_exponent_type>(0)),
                                                                                   my_neg              (a < static_cast<eval_ops_float_type>(0)),
                                                                                   my_fpclass          (cpp_bin_float_finite),
                                                                                   my_precision_in_bits(cpp_bin_float_bits_number)
    {
      if(my_neg)
      {
        from_float_type(static_cast<float_type>(-a));
      }
      else
      {
        from_float_type(a);
      }

      round_and_truncate();
    }

    void negate()
    {
      if(!iszero()) { my_neg = !my_neg; }
    }

    bool iszero() const
    {
      return (   (my_fpclass == cpp_bin_float_finite)
              && (my_data[0U] == static_cast<short_limb_type>(0U)));
    }

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
                                           my_precision_in_bits(cpp_bin_float_bits_number) { }

    template<class unsigned_integer_type>
    void from_unsigned_integer_type(unsigned_integer_type u)
    {
      if(u <= (std::numeric_limits<short_limb_type>::max)())
      {
        my_data[0U] = short_limb_type(u);
      }
      else
      {
        boost::uint_least8_t i = boost::uint_least8_t(0U);

        for(;;)
        {
          my_data[i] = short_limb_type(u);

          ++i;

          u >>= std::numeric_limits<short_limb_type>::digits;

          if(u != unsigned_integer_type(0U))
          {
            my_exp += std::numeric_limits<short_limb_type>::digits;
          }
          else
          {
            break;
          }
        }

        std::reverse(my_data.begin(), my_data.begin() + i);
      }

      const int priority_bit = boost::multiprecision::detail::utype_prior(my_data[0U]);

      if(priority_bit < (std::numeric_limits<short_limb_type>::digits - 1))
      {
        const int shift = std::numeric_limits<short_limb_type>::digits - (1 + priority_bit);

        shift_data_to_the_left(shift);

        my_exp -= shift;
      }
    }

    template<class float_type>
    void from_float_type(float_type a)
    {
      BOOST_MATH_STD_USING // ADL of std names, needed for frexp.

      int e2;
      float_type y = frexp(a, &e2);

      my_exp = static_cast<my_exponent_type>(e2);

      int number_of_digits;

      typename array_type::size_type i(0U);

      while(number_of_digits < std::numeric_limits<float_type>::digits)
      {
        if((std::numeric_limits<float_type>::digits - number_of_digits) >= std::numeric_limits<short_limb_type>::digits)
        {
          y *= long_limb_type(long_limb_type(1U) << std::numeric_limits<short_limb_type>::digits);
          number_of_digits += std::numeric_limits<short_limb_type>::digits;
        }
        else if((std::numeric_limits<float_type>::digits - number_of_digits) > 0)
        {
          y *= (short_limb_type(1U) << (std::numeric_limits<float_type>::digits - number_of_digits));
          number_of_digits += (std::numeric_limits<float_type>::digits - number_of_digits);
        }

        my_data[i] = static_cast<short_limb_type>(y);
        y -= my_data[i];
        ++i;
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
    // TBD: Read the input string (and include exception support).
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
    // TBD: Round and truncate the data.
  }

  void shift_data_to_the_left(const int shift)
  {
    // TBD: Shift data to the left.
  }

  void shift_data_to_the_right(const int shift)
  {
    // TBD: Shift data to the right.
  }
  } // namespace backends

  using boost::multiprecision::backends::cpp_bin_float;

  } } // namespace boost::multiprecision

#endif // BOOST_MP_CPP_BIN_FLOAT_BACKEND_HPP
