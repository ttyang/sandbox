//  Boost rational.hpp header file  ------------------------------------------//

//  (C) Copyright Paul Moore 1999. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or
//  implied warranty, and with no claim as to its suitability for any purpose.

// boostinspect:nolicense (don't complain about the lack of a Boost license)
// (Paul Moore hasn't been in contact for years, so there's no way to change the
// license.)

//  See http://www.boost.org/libs/rational for documentation.

//  Credits:
//  Thanks to the boost mailing list in general for useful comments.
//  Particular contributions included:
//    Andrew D Jewell, for reminding me to take care to avoid overflow
//    Ed Brey, for many comments, including picking up on some dreadful typos
//    Stephen Silver contributed the test suite and comments on user-defined
//    IntType
//    Nickolay Mladenov, for the implementation of operator+=

//  Revision History
//  31 Jul 12  Added "CheckingMode" template parameter and support for
//             over/underflow checking (new exception: rational_overflow)
//             (Dan Searles)
//  05 May 12  Reduced use of implicit gcd (Mario Lang)
//  05 Nov 06  Change rational_cast to not depend on division between different
//             types (Daryle Walker)
//  04 Nov 06  Off-load GCD and LCM to Boost.Math; add some invariant checks;
//             add std::numeric_limits<> requirement to help GCD (Daryle Walker)
//  31 Oct 06  Recoded both operator< to use round-to-negative-infinity
//             divisions; the rational-value version now uses continued fraction
//             expansion to avoid overflows, for bug #798357 (Daryle Walker)
//  20 Oct 06  Fix operator bool_type for CW 8.3 (Joaqu�n M L�pez Mu�oz)
//  18 Oct 06  Use EXPLICIT_TEMPLATE_TYPE helper macros from Boost.Config
//             (Joaqu�n M L�pez Mu�oz)
//  27 Dec 05  Add Boolean conversion operator (Daryle Walker)
//  28 Sep 02  Use _left versions of operators from operators.hpp
//  05 Jul 01  Recode gcd(), avoiding std::swap (Helmut Zeisel)
//  03 Mar 01  Workarounds for Intel C++ 5.0 (David Abrahams)
//  05 Feb 01  Update operator>> to tighten up input syntax
//  05 Feb 01  Final tidy up of gcd code prior to the new release
//  27 Jan 01  Recode abs() without relying on abs(IntType)
//  21 Jan 01  Include Nickolay Mladenov's operator+= algorithm,
//             tidy up a number of areas, use newer features of operators.hpp
//             (reduces space overhead to zero), add operator!,
//             introduce explicit mixed-mode arithmetic operations
//  12 Jan 01  Include fixes to handle a user-defined IntType better
//  19 Nov 00  Throw on divide by zero in operator /= (John (EBo) David)
//  23 Jun 00  Incorporate changes from Mark Rodgers for Borland C++
//  22 Jun 00  Change _MSC_VER to BOOST_MSVC so other compilers are not
//             affected (Beman Dawes)
//   6 Mar 00  Fix operator-= normalization, #include <string> (Jens Maurer)
//  14 Dec 99  Modifications based on comments from the boost list
//  09 Dec 99  Initial Version (Paul Moore)

#ifndef BOOST_RATIONAL_HPP
#define BOOST_RATIONAL_HPP

#include <iostream>              // for std::istream and std::ostream
#include <ios>                   // for std::noskipws
#include <stdexcept>             // for std::domain_error
#include <string>                // for std::string implicit constructor
#include <boost/operators.hpp>   // for boost::addable etc
#include <cstdlib>               // for std::abs
#include <boost/call_traits.hpp> // for boost::call_traits
#include <boost/config.hpp>      // for BOOST_NO_STDC_NAMESPACE, BOOST_MSVC
#include <boost/detail/workaround.hpp> // for BOOST_WORKAROUND
#include <boost/assert.hpp>      // for BOOST_ASSERT
#include <boost/math/common_factor_rt.hpp>  // for boost::math::gcd, lcm
#include <limits>                // for std::numeric_limits
#include <boost/static_assert.hpp>  // for BOOST_STATIC_ASSERT

namespace boost {

    enum rational_checktype {rational_no_checking, rational_check_for_overflow};

namespace detail {
// This is just a helper function for the overflow checking path.
// For a given integer type (signed), multiply 2 values into separate 'high'
// and 'low' variables of the same type.
template <typename IntType>
void mul2int(IntType& res_hi, IntType& res_lo, IntType f1, IntType f2)
{
    BOOST_STATIC_ASSERT(::std::numeric_limits<IntType>::is_signed);
    BOOST_STATIC_ASSERT(((sizeof(IntType)*CHAR_BIT) & 1) == 0);
    const IntType zero(0);    
   
    // Operate on positive values, and track sign for final result.
    // This requires IntType be signed.
    bool sign_neg = false;
    if(f1<zero) {
        f1=-f1; sign_neg = !sign_neg;
    }
    if(f2<zero){
        f2=-f2; sign_neg = !sign_neg;
    }

    const int half_num_bits = sizeof(IntType)*CHAR_BIT/2;
    const IntType lo_half_mask = (((IntType)(1))<<half_num_bits)-(IntType)(1);
    IntType f1h = (f1>>half_num_bits)&lo_half_mask, f1l = f1&lo_half_mask,
            f2h = (f2>>half_num_bits)&lo_half_mask, f2l = f2&lo_half_mask;

    res_lo = f1l * f2l;

    IntType acc = (res_lo >> half_num_bits) & lo_half_mask;
    acc += f1l * f2h;
    acc += f1h * f2l;

    res_lo = (res_lo & lo_half_mask) + ((acc & lo_half_mask) << half_num_bits);
    acc = (acc>>half_num_bits) & lo_half_mask;
    res_hi = acc + f1h * f2h;

    if(sign_neg)
    {
        res_lo = ~res_lo;
        res_hi = ~res_hi;
        res_lo += 1;
        if(res_lo == 0)
        {
            res_hi++;
        }
    }
}

// This is just a helper function for the overflow checking path.
// Add two "high","low" operands to a "high","low" result.
// Returns true if over/underflow occured ("high","low" sum cannot hold correct result).
template <typename IntType>
bool add2int(IntType& res_hi, IntType& res_lo, IntType f1h, IntType f1l, IntType f2h, IntType f2l)
{
    BOOST_STATIC_ASSERT(::std::numeric_limits<IntType>::is_signed);
    bool overflow = false;
    const int num_bits = sizeof(IntType)*CHAR_BIT;
    const IntType msb_mask = (IntType)(((IntType)(1)) << (num_bits-1));
    const IntType zero(0);    
    const IntType one(1);    
   
    // This requires Inttype be signed.
    if(f1l<zero)
    {
        if(f2l<zero)
        {   // Both low parts are negative, 1 will always carry to high part
            res_lo = f1l+f2l;
            res_hi = f1h+f2h+one;
        }
        else
        {   // f1l negative, f2l positive
            f1l &= ~msb_mask;
            res_lo = f1l+f2l;
            if(res_lo&msb_mask) res_hi = f1h+f2h+one;
            else                res_hi = f1h+f2h;
            res_lo += msb_mask;
        }
    }
    else
    {
        if(f2l<zero)
        {   // f1l positive, f2l negative
            f2l &= ~msb_mask;
            res_lo = f1l+f2l;
            if(res_lo&msb_mask) res_hi = f1h+f2h+one;
            else                res_hi = f1h+f2h;
            res_lo += msb_mask;
        }
        else
        {   // Both low parts are positive, 1 will never carry to high part
            res_lo = f1l+f2l;
            res_hi = f1h+f2h;
        }
    }
    if(((res_hi^f1h) & ((~(f1h^f2h))) & msb_mask))
        overflow = true;
    return overflow;
}

} // namespace detail

} // namespace boost

// Control whether depreciated GCD and LCM functions are included (default: yes)
#ifndef BOOST_CONTROL_RATIONAL_HAS_GCD
#define BOOST_CONTROL_RATIONAL_HAS_GCD  1
#endif

namespace boost {

#if BOOST_CONTROL_RATIONAL_HAS_GCD
template <typename IntType>
IntType gcd(IntType n, IntType m)
{
    // Defer to the version in Boost.Math
    return math::gcd( n, m );
}

template <typename IntType>
IntType lcm(IntType n, IntType m)
{
    // Defer to the version in Boost.Math
    return math::lcm( n, m );
}
#endif  // BOOST_CONTROL_RATIONAL_HAS_GCD

class bad_rational : public std::domain_error
{
public:
    explicit bad_rational() : std::domain_error("bad rational: zero denominator") {}
};

class rational_overflow : public std::domain_error
{
public:
    explicit rational_overflow() : std::domain_error("rational error: over or underflow") {}
};



template <typename IntType, rational_checktype CheckingMode=rational_no_checking>
class rational :
    less_than_comparable < rational<IntType, CheckingMode>,
    equality_comparable < rational<IntType, CheckingMode>,
    less_than_comparable2 < rational<IntType, CheckingMode>, IntType,
    equality_comparable2 < rational<IntType, CheckingMode>, IntType,
    addable < rational<IntType, CheckingMode>,
    subtractable < rational<IntType, CheckingMode>,
    multipliable < rational<IntType, CheckingMode>,
    dividable < rational<IntType, CheckingMode>,
    addable2 < rational<IntType, CheckingMode>, IntType,
    subtractable2 < rational<IntType, CheckingMode>, IntType,
    subtractable2_left < rational<IntType, CheckingMode>, IntType,
    multipliable2 < rational<IntType, CheckingMode>, IntType,
    dividable2 < rational<IntType, CheckingMode>, IntType,
    dividable2_left < rational<IntType, CheckingMode>, IntType,
    incrementable < rational<IntType, CheckingMode>,
    decrementable < rational<IntType, CheckingMode>
    > > > > > > > > > > > > > > > >
{
    // Class-wide pre-conditions
    BOOST_STATIC_ASSERT( ::std::numeric_limits<IntType>::is_specialized );

    // Checking for overflow requires IntType be signed.
    BOOST_STATIC_ASSERT(CheckingMode==rational_no_checking || (CheckingMode==rational_check_for_overflow && ::std::numeric_limits<IntType>::is_signed));

    // Helper types
    typedef typename boost::call_traits<IntType>::param_type param_type;

    struct helper { IntType parts[2]; };
    typedef IntType (helper::* bool_type)[2];

public:
    typedef IntType int_type;
    rational() : num(0), den(1) {}
    rational(param_type n) : num(n), den(1) {}
    rational(param_type n, param_type d) : num(n), den(d) {normalize();}

    // Default copy constructor and assignment are fine

    // Add assignment from IntType
    rational& operator=(param_type i) { num = i; den = 1; return *this; }

    // Assign in place
    rational& assign(param_type n, param_type d);

    // Access to representation
    IntType numerator() const { return num; }
    IntType denominator() const { return den; }

    // Unary plus, minus
    rational operator+() const;
    rational operator-() const;

    // Arithmetic assignment operators
    rational& operator+= (const rational& r);
    rational& operator-= (const rational& r);
    rational& operator*= (const rational& r);
    rational& operator/= (const rational& r);

    rational& operator+= (param_type i);
    rational& operator-= (param_type i);
    rational& operator*= (param_type i);
    rational& operator/= (param_type i);

    // Increment and decrement
    const rational& operator++();
    const rational& operator--();

    // Operator not
    bool operator!() const { return !num; }

    // Boolean conversion
    
#if BOOST_WORKAROUND(__MWERKS__,<=0x3003)
    // The "ISO C++ Template Parser" option in CW 8.3 chokes on the
    // following, hence we selectively disable that option for the
    // offending memfun.
#pragma parse_mfunc_templ off
#endif

    operator bool_type() const { return operator !() ? 0 : &helper::parts; }

#if BOOST_WORKAROUND(__MWERKS__,<=0x3003)
#pragma parse_mfunc_templ reset
#endif

    // Comparison operators
    bool operator<  (const rational& r) const;
    bool operator== (const rational& r) const;

    bool operator<  (param_type i) const;
    bool operator>  (param_type i) const;
    bool operator== (param_type i) const;


private:
    // Implementation - numerator and denominator (normalized).
    // Other possibilities - separate whole-part, or sign, fields?
    IntType num;
    IntType den;

    rational& assignNoNorm(param_type n, param_type d) { num = n; den = d; return *this;}

    // Representation note: Fractions are kept in normalized form at all
    // times. Normalized form is defined as gcd(num,den) == 1 and den > 0.
    // In particular, note that the implementation of abs() below relies
    // on den always being positive.
    bool test_invariant() const
    {
        return  ( this->den > int_type(0) ) && ( math::gcd(this->num, this->den) == int_type(1) );
    }

    void normalize();
};



// Partially specialize the class for the overflow checking.  
template <typename IntType> 
class rational<IntType, rational_check_for_overflow> :
    less_than_comparable < rational<IntType, rational_check_for_overflow>,
    equality_comparable < rational<IntType, rational_check_for_overflow>,
    less_than_comparable2 < rational<IntType, rational_check_for_overflow>, IntType,
    equality_comparable2 < rational<IntType, rational_check_for_overflow>, IntType,
    addable < rational<IntType, rational_check_for_overflow>,
    subtractable < rational<IntType, rational_check_for_overflow>,
    multipliable < rational<IntType, rational_check_for_overflow>,
    dividable < rational<IntType, rational_check_for_overflow>,
    addable2 < rational<IntType, rational_check_for_overflow>, IntType,
    subtractable2 < rational<IntType, rational_check_for_overflow>, IntType,
    subtractable2_left < rational<IntType, rational_check_for_overflow>, IntType,
    multipliable2 < rational<IntType, rational_check_for_overflow>, IntType,
    dividable2 < rational<IntType, rational_check_for_overflow>, IntType,
    dividable2_left < rational<IntType, rational_check_for_overflow>, IntType,
    incrementable < rational<IntType, rational_check_for_overflow>,
    decrementable < rational<IntType, rational_check_for_overflow>
    > > > > > > > > > > > > > > > >
{
    // Class-wide pre-conditions
    BOOST_STATIC_ASSERT( ::std::numeric_limits<IntType>::is_specialized );

    // Checking for overflow requires IntType be signed.
    BOOST_STATIC_ASSERT( ::std::numeric_limits<IntType>::is_signed);

    // Helper types
    typedef typename boost::call_traits<IntType>::param_type param_type;

    struct helper { IntType parts[2]; };
    typedef IntType (helper::* bool_type)[2];

public:
    typedef IntType int_type;
    rational() : num(0), den(1) {}
    rational(param_type n) : num(n), den(1) {}
    rational(param_type n, param_type d) : num(n), den(d) {normalize();}

    // Default copy constructor and assignment are fine

    // Add assignment from IntType
    rational& operator=(param_type i) { num = i; den = 1; return *this; }

    // Assign in place
    rational& assign(param_type n, param_type d);

    // Access to representation
    inline IntType numerator() const { return num; }
    inline IntType denominator() const { return den; }

    // Unary plus, minus
    rational operator+() const;
    rational operator-() const;

    // Arithmetic assignment operators
    rational& operator+= (const rational& r);
    rational& operator-= (const rational& r);
    rational& operator*= (const rational& r);
    rational& operator/= (const rational& r);

    rational& operator+= (param_type i);
    rational& operator-= (param_type i);
    rational& operator*= (param_type i);
    rational& operator/= (param_type i);

    // Increment and decrement
    const rational& operator++();
    const rational& operator--();

    // Operator not
    bool operator!() const { return !num; }

    // Boolean conversion
    
#if BOOST_WORKAROUND(__MWERKS__,<=0x3003)
    // The "ISO C++ Template Parser" option in CW 8.3 chokes on the
    // following, hence we selectively disable that option for the
    // offending memfun.
#pragma parse_mfunc_templ off
#endif

    operator bool_type() const { return operator !() ? 0 : &helper::parts; }

#if BOOST_WORKAROUND(__MWERKS__,<=0x3003)
#pragma parse_mfunc_templ reset
#endif

    // Comparison operators
    bool operator<  (const rational& r) const;
    bool operator== (const rational& r) const;

    bool operator<  (param_type i) const;
    bool operator>  (param_type i) const;
    bool operator== (param_type i) const;


private:
    // Implementation - numerator and denominator (normalized).
    // Other possibilities - separate whole-part, or sign, fields?
    IntType num;
    IntType den;

    rational& assignNoNorm(param_type n, param_type d) { num = n; den = d; return *this;}

    // Representation note: Fractions are kept in normalized form at all
    // times. Normalized form is defined as gcd(num,den) == 1 and den > 0.
    // In particular, note that the implementation of abs() below relies
    // on den always being positive.
    bool test_invariant() const;
    void normalize();
};

// Assign in place
template <typename IntType, rational_checktype CheckingMode>
inline rational<IntType, CheckingMode>& rational<IntType, CheckingMode>::assign(param_type n, param_type d)
{
    num = n;
    den = d;
    normalize();
    return *this;
}
template <typename IntType>
inline rational<IntType, rational_check_for_overflow>& rational<IntType, rational_check_for_overflow>::assign(param_type n, param_type d)
{
    num = n;
    den = d;
    normalize();
    return *this;
}

// Unary plus
template <typename IntType, rational_checktype CheckingMode>
rational<IntType, CheckingMode> rational<IntType, CheckingMode>::operator+ () const
{
    rational<IntType, CheckingMode> retRational;
    retRational.assignNoNorm(num, den);
    return retRational;
}
template <typename IntType>
rational<IntType, rational_check_for_overflow> rational<IntType, rational_check_for_overflow>::operator+ () const
{
    rational<IntType, rational_check_for_overflow> retRational;
    retRational.assignNoNorm(num, den);
    return retRational;
}

// Unary minus
template <typename IntType, rational_checktype CheckingMode>
rational<IntType, CheckingMode> rational<IntType, CheckingMode>::operator- () const
{
    rational<IntType, CheckingMode> retRational;
    retRational.assignNoNorm(-num, den);
    return retRational;
}
template <typename IntType>
rational<IntType, rational_check_for_overflow> rational<IntType, rational_check_for_overflow>::operator- () const
{
    IntType negnumer = -num;
    if(negnumer && (num == negnumer))
        throw rational_overflow();

    rational<IntType, rational_check_for_overflow> retRational;
    retRational.assignNoNorm(-num, den);
    return retRational;
}


template <typename IntType, rational_checktype CheckingMode>
rational<IntType, CheckingMode> abs(const rational<IntType, CheckingMode>& r);

// Arithmetic assignment operators
template <typename IntType, rational_checktype CheckingMode>
rational<IntType, CheckingMode>& rational<IntType, CheckingMode>::operator+= (const rational<IntType, CheckingMode>& r)
{
    // This calculation avoids overflow, and minimises the number of expensive
    // calculations. Thanks to Nickolay Mladenov for this algorithm.
    //
    // Proof:
    // We have to compute a/b + c/d, where gcd(a,b)=1 and gcd(b,c)=1.
    // Let g = gcd(b,d), and b = b1*g, d=d1*g. Then gcd(b1,d1)=1
    //
    // The result is (a*d1 + c*b1) / (b1*d1*g).
    // Now we have to normalize this ratio.
    // Let's assume h | gcd((a*d1 + c*b1), (b1*d1*g)), and h > 1
    // If h | b1 then gcd(h,d1)=1 and hence h|(a*d1+c*b1) => h|a.
    // But since gcd(a,b1)=1 we have h=1.
    // Similarly h|d1 leads to h=1.
    // So we have that h | gcd((a*d1 + c*b1) , (b1*d1*g)) => h|g
    // Finally we have gcd((a*d1 + c*b1), (b1*d1*g)) = gcd((a*d1 + c*b1), g)
    // Which proves that instead of normalizing the result, it is better to
    // divide num and den by gcd((a*d1 + c*b1), g)

    // Protect against self-modification
    IntType r_num = r.num;
    IntType r_den = r.den;

    IntType g = math::gcd(den, r_den);
    den /= g;  // = b1 from the calculations above
    num = num * (r_den / g) + r_num * den;
    g = math::gcd(num, g);
    num /= g;
    den *= r_den/g;

    return *this;
}
template <typename IntType>
rational<IntType, rational_check_for_overflow>& rational<IntType, rational_check_for_overflow>::operator+= (const rational<IntType, rational_check_for_overflow>& r)
{
    const int num_bits = sizeof(IntType)*CHAR_BIT;
    const IntType zero(0);
    const IntType one(1);
    const IntType neg1(-1);
    IntType part1_h,part1_l,part2_h,part2_l,new_num_h,tmp;

    // Protect against self-modification
    IntType r_num = r.num;
    IntType r_den = r.den;
    IntType r_den_g = r.den;

    IntType g = math::gcd(den, r_den);

    if(g != one)
    {
        den /= g;
        r_den_g /= g;
    }

    detail::mul2int<IntType>(part1_h,part1_l,   num,  r_den_g);
    detail::mul2int<IntType>(part2_h,part2_l, r_num,    den);
    bool  ovfl = detail::add2int<IntType>(new_num_h,  num,part1_h,part1_l,part2_h,part2_l);
    tmp = num>>(num_bits-1);
    if(new_num_h!=tmp)
        throw rational_overflow();

    g = math::gcd(num, g);
    if(g!=one)
    {
        num /= g;
        r_den /= g;
    }

    detail::mul2int<IntType>(part1_h,den,   den,  r_den);
    if((part1_h!=zero) || (den<zero))
        throw rational_overflow();

    return *this;
}

template <typename IntType, rational_checktype CheckingMode>
rational<IntType, CheckingMode>&
    rational<IntType, CheckingMode>::operator-= (const rational<IntType, CheckingMode>& r)
{
    // Protect against self-modification
    IntType r_num = r.num;
    IntType r_den = r.den;

    // This calculation avoids overflow, and minimises the number of expensive
    // calculations. It corresponds exactly to the += case above
    IntType g = math::gcd(den, r_den);
    den /= g;
    num = num * (r_den / g) - r_num * den;
    g = math::gcd(num, g);
    num /= g;
    den *= r_den/g;

    return *this;
}
template <typename IntType>
rational<IntType, rational_check_for_overflow>& rational<IntType, rational_check_for_overflow>::operator-= (const rational<IntType, rational_check_for_overflow>& r)
{
    if((num==r.num) && (den==r.den)) {
        num = IntType(0);
        den = IntType(1);
        return *this;
    }
            
    // Negate the denominator (which is safe), and use constructor 'normalize' to check for overflow.
    IntType negrden = -r.den;
    rational<IntType, rational_check_for_overflow> negOperand(r.num, negrden);
    return operator+= (negOperand);
}

template <typename IntType, rational_checktype CheckingMode>
rational<IntType, CheckingMode>&
rational<IntType, CheckingMode>::operator*= (const rational<IntType, CheckingMode>& r)
{
    // Protect against self-modification
    IntType r_num = r.num;
    IntType r_den = r.den;

    // Avoid overflow and preserve normalization
    IntType gcd1 = math::gcd(num, r_den);
    IntType gcd2 = math::gcd(r_num, den);

    num = (num/gcd1) * (r_num/gcd2);
    den = (den/gcd2) * (r_den/gcd1);
    return *this;
}
template <typename IntType>
rational<IntType, rational_check_for_overflow>& rational<IntType, rational_check_for_overflow>::operator*= (const rational<IntType, rational_check_for_overflow>& r)
{
    // Protect against self-modification
    IntType r_num = r.num;
    IntType r_den = r.den;

    // Avoid overflow and preserve normalization
    IntType gcd1 = math::gcd(num, r_den);
    IntType gcd2 = math::gcd(r_num, den);

    const int num_bits = sizeof(IntType)*CHAR_BIT;
    const IntType one = IntType(1);
    const IntType zero = IntType(0);
    IntType num_gcd1=num, den_gcd2=den, signbits;
    if(gcd1!=one) {
        num_gcd1 /= gcd1;
        r_den    /= gcd1;
    }
    if(gcd2!=one) {
        den_gcd2 /= gcd2;
        r_num    /= gcd2;
    }
    detail::mul2int<IntType>(signbits,num, num_gcd1, r_num);
    if(IntType(num>>(num_bits-1)) != signbits)
        throw rational_overflow();

    detail::mul2int<IntType>(signbits,den, den_gcd2, r_den);
    if((signbits!=zero) || (den<zero))
        throw rational_overflow();
    return *this;
}

template <typename IntType, rational_checktype CheckingMode>
rational<IntType, CheckingMode>& 
rational<IntType, CheckingMode>::operator/= (const rational<IntType, CheckingMode>& r)
{
    // Protect against self-modification
    IntType r_num = r.num;
    IntType r_den = r.den;

    // Avoid repeated construction
    const IntType zero(0);

    // Trap division by zero
    if (r_num == zero)
        throw bad_rational();
    if (num == zero)
        return *this;

    // Avoid overflow and preserve normalization
    IntType gcd1 = math::gcd(num, r_num);
    IntType gcd2 = math::gcd(r_den, den);

    num = (num/gcd1) * (r_den/gcd2);
    den = (den/gcd2) * (r_num/gcd1);

    if (den < zero) {
        num = -num;
        den = -den;
    }
    return *this;
}
template <typename IntType>
rational<IntType, rational_check_for_overflow>& rational<IntType, rational_check_for_overflow>::operator/= (const rational<IntType, rational_check_for_overflow>& r)
{
    // Protect against self-modification
    IntType r_num = r.num;
    IntType r_den = r.den;

    // Avoid repeated construction
    const IntType zero(0);

    // Trap division by zero
    if (r_num == zero)
        throw bad_rational();
    if (num == zero)
        return *this;

    // Avoid overflow and preserve normalization
    IntType gcd1 = math::gcd(num, r_num);
    IntType gcd2 = math::gcd(r_den, den);

    const int num_bits = sizeof(IntType)*CHAR_BIT;
    const IntType one = IntType(1);
    IntType num_gcd1=num, den_gcd2=den, signbits;
    if(gcd1!=one) {
        num_gcd1 /= gcd1;
        r_num    /= gcd1;
    }
    if(gcd2!=one) {
        den_gcd2 /= gcd2;
        r_den    /= gcd2;
    }
    detail::mul2int<IntType>(signbits,num, num_gcd1, r_den);
    if(IntType(num>>(num_bits-1)) != signbits)
        throw rational_overflow();

    detail::mul2int<IntType>(signbits,den, den_gcd2, r_num);
    if(IntType(den>>(num_bits-1)) != signbits)
        throw rational_overflow();

    if (den < zero)
    {
        IntType neg_den = -den;
        IntType neg_num = -num;
        if(den == neg_den) // den never zero here
            throw rational_overflow();
        if(num && (num == neg_num))
            throw rational_overflow();

        num = neg_num;
        den = neg_den;
    }
    return *this;
}

// Mixed-mode operators
template <typename IntType, rational_checktype CheckingMode>
inline rational<IntType, CheckingMode>&
    rational<IntType, CheckingMode>::operator+= (param_type i)
{
    num += i * den;
    return *this;
}
template <typename IntType>
inline rational<IntType, rational_check_for_overflow>&
    rational<IntType, rational_check_for_overflow>::operator+= (param_type i)
{
    return operator+= (rational<IntType, rational_check_for_overflow>(i));
}

template <typename IntType, rational_checktype CheckingMode>
inline rational<IntType, CheckingMode>&
    rational<IntType, CheckingMode>::operator-= (param_type i)
{
    num -= i * den;
    return *this;
}

template <typename IntType>
inline rational<IntType, rational_check_for_overflow>&
    rational<IntType, rational_check_for_overflow>::operator-= (param_type i)
{
    return operator-= (rational<IntType, rational_check_for_overflow>(i));
}


template <typename IntType, rational_checktype CheckingMode>
inline rational<IntType, CheckingMode>&
    rational<IntType, CheckingMode>::operator*= (param_type i)
{
    // Avoid overflow and preserve normalization
    IntType gcd = math::gcd(i, den);
    num *= i / gcd;
    den /= gcd;

    return *this;
}
template <typename IntType>
inline rational<IntType, rational_check_for_overflow>&
    rational<IntType, rational_check_for_overflow>::operator*= (param_type i)
{
    return operator*= (rational<IntType, rational_check_for_overflow>(i));
}

template <typename IntType, rational_checktype CheckingMode>
inline rational<IntType, CheckingMode>&
    rational<IntType, CheckingMode>::operator/= (param_type i)
{
    // Avoid repeated construction
    IntType const zero(0);

    if (i == zero) 
        throw bad_rational();
    if (num == zero) return *this;

    // Avoid overflow and preserve normalization
    IntType const gcd = math::gcd(num, i);
    num /= gcd;
    den *= i / gcd;

    if (den < zero) {
        num = -num;
        den = -den;
    }

    return *this;
}
template <typename IntType>
inline rational<IntType, rational_check_for_overflow>&
    rational<IntType, rational_check_for_overflow>::operator/= (param_type i)
{
    return operator/= (rational<IntType, rational_check_for_overflow>(i));
}


// Increment and decrement
template <typename IntType, rational_checktype CheckingMode>
const rational<IntType, CheckingMode>& rational<IntType, CheckingMode>::operator++()
{ 
    num += den;
    return *this;
}
template <typename IntType>
const rational<IntType, rational_check_for_overflow>& rational<IntType, rational_check_for_overflow>::operator++()
{
    const IntType zero( 0 );
    if((num>zero) && (IntType(num + den) < zero))
        throw rational_overflow();

    // This can never denormalise the fraction
    num += den;
    return *this;
}

template <typename IntType, rational_checktype CheckingMode>
const rational<IntType, CheckingMode>& rational<IntType, CheckingMode>::operator--()
{
    num -= den;
    return *this;
}
template <typename IntType>
inline const rational<IntType, rational_check_for_overflow>& rational<IntType, rational_check_for_overflow>::operator--()
{
    const IntType zero( 0 );
    if((num<zero) && (IntType(num - den) >= zero))
        throw rational_overflow();

    // This can never denormalise the fraction
    num -= den;
    return *this;
}

// Comparison operators
template <typename IntType, rational_checktype CheckingMode>
bool
rational<IntType, CheckingMode>::operator< (const rational<IntType, CheckingMode>& r) const
{
    // Avoid repeated construction
    int_type const  zero( 0 );

    {
        // This should really be a class-wide invariant.  The reason for these
        // checks is that for 2's complement systems, INT_MIN has no corresponding
        // positive, so negating it during normalization keeps it INT_MIN, which
        // is bad for later calculations that assume a positive denominator.
        BOOST_ASSERT( this->den > zero );
        BOOST_ASSERT( r.den > zero );

        // Determine relative order by expanding each value to its simple continued
        // fraction representation using the Euclidian GCD algorithm.
        struct { int_type  n, d, q, r; }  ts = { this->num, this->den, this->num /
            this->den, this->num % this->den }, rs = { r.num, r.den, r.num / r.den,
            r.num % r.den };
        unsigned  reverse = 0u;

        // Normalize negative moduli by repeatedly adding the (positive) denominator
        // and decrementing the quotient.  Later cycles should have all positive
        // values, so this only has to be done for the first cycle.  (The rules of
        // C++ require a nonnegative quotient & remainder for a nonnegative dividend
        // & positive divisor.)
        while ( ts.r < zero )  { ts.r += ts.d; --ts.q; }
        while ( rs.r < zero )  { rs.r += rs.d; --rs.q; }

        // Loop through and compare each variable's continued-fraction components
        while ( true )
        {
            // The quotients of the current cycle are the continued-fraction
            // components.  Comparing two c.f. is comparing their sequences,
            // stopping at the first difference.
            if ( ts.q != rs.q )
            {
                // Since reciprocation changes the relative order of two variables,
                // and c.f. use reciprocals, the less/greater-than test reverses
                // after each index.  (Start w/ non-reversed @ whole-number place.)
                return reverse ? ts.q > rs.q : ts.q < rs.q;
            }

            // Prepare the next cycle
            reverse ^= 1u;

            if ( (ts.r == zero) || (rs.r == zero) )
            {
                // At least one variable's c.f. expansion has ended
                break;
            }

            ts.n = ts.d;         ts.d = ts.r;
            ts.q = ts.n / ts.d;  ts.r = ts.n % ts.d;
            rs.n = rs.d;         rs.d = rs.r;
            rs.q = rs.n / rs.d;  rs.r = rs.n % rs.d;
        }

        // Compare infinity-valued components for otherwise equal sequences
        if ( ts.r == rs.r )
        {
            // Both remainders are zero, so the next (and subsequent) c.f.
            // components for both sequences are infinity.  Therefore, the sequences
            // and their corresponding values are equal.
            return false;
        }
        else
        {
    #ifdef BOOST_MSVC
    #pragma warning(push)
    #pragma warning(disable:4800)
    #endif
            // Exactly one of the remainders is zero, so all following c.f.
            // components of that variable are infinity, while the other variable
            // has a finite next c.f. component.  So that other variable has the
            // lesser value (modulo the reversal flag!).
            return ( ts.r != zero ) != static_cast<bool>( reverse );
    #ifdef BOOST_MSVC
    #pragma warning(pop)
    #endif
        }
    }
}
template <typename IntType>
bool rational<IntType, rational_check_for_overflow>::operator< (const rational<IntType, rational_check_for_overflow>& r) const
{
    // Avoid repeated construction
    int_type const  zero( 0 );

    IntType prod_left_h, prod_left_l, prod_right_h, prod_right_l;
    detail::mul2int<IntType>(prod_left_h, prod_left_l, num, r.den);
    detail::mul2int<IntType>(prod_right_h, prod_right_l, r.num, den);
    if(prod_left_h < prod_right_h)
        return true;
    else if(prod_left_h == prod_right_h)
    {
        const int num_bits = sizeof(IntType)*CHAR_BIT;
        const IntType msb_mask = (IntType)(((IntType)(1)) << (num_bits-1));
        prod_left_l ^= msb_mask; // Convert to signed
        prod_right_l ^= msb_mask; // Convert to signed
        return prod_left_l < prod_right_l;
    }
    else 
        return false;
}

template <typename IntType, rational_checktype CheckingMode>
bool rational<IntType, CheckingMode>::operator<  (param_type i) const
{
    // Avoid repeated construction
    int_type const  zero( 0 );

    // Break value into mixed-fraction form, w/ always-nonnegative remainder
    BOOST_ASSERT( this->den > zero );
    int_type  q = this->num / this->den, r = this->num % this->den;
    while ( r < zero )  { r += this->den; --q; }

    // Compare with just the quotient, since the remainder always bumps the
    // value up.  [Since q = floor(n/d), and if n/d < i then q < i, if n/d == i
    // then q == i, if n/d == i + r/d then q == i, and if n/d >= i + 1 then
    // q >= i + 1 > i; therefore n/d < i iff q < i.]
    return q < i;
}

template <typename IntType>
bool rational<IntType, rational_check_for_overflow>::operator< (param_type i) const
{
    IntType prod_left_h, prod_left_l, prod_right_h, prod_right_l;
    detail::mul2int<IntType>(prod_left_h, prod_left_l, num, IntType(1));
    detail::mul2int<IntType>(prod_right_h, prod_right_l, i, den);
    if(prod_left_h < prod_right_h)
        return true;
    else if(prod_left_h == prod_right_h)
    {
        const int num_bits = sizeof(IntType)*CHAR_BIT;
        const IntType msb_mask = (IntType)(((IntType)(1)) << (num_bits-1));
        prod_left_l ^= msb_mask; // Convert to signed
        prod_right_l ^= msb_mask; // Convert to signed
        return prod_left_l < prod_right_l;
    }
    else 
        return false;
}

template <typename IntType, rational_checktype CheckingMode>
bool rational<IntType, CheckingMode>::operator> (param_type i) const
{
    return operator==(i)? false: !operator<(i);
}
template <typename IntType>
bool rational<IntType, rational_check_for_overflow>::operator> (param_type i) const
{
    return rational<IntType, rational_check_for_overflow>::operator==(i)? false: !rational<IntType, rational_check_for_overflow>::operator<(i);
}

template <typename IntType, rational_checktype CheckingMode>
 bool rational<IntType, CheckingMode>::operator== (const rational<IntType, CheckingMode>& r) const
{
    return ((num == r.num) && (den == r.den));
}
template <typename IntType>
bool rational<IntType, rational_check_for_overflow>::operator== (const rational<IntType, rational_check_for_overflow>& r) const
{
    return ((num == r.num) && (den == r.den));
}

template <typename IntType, rational_checktype CheckingMode>
inline bool rational<IntType, CheckingMode>::operator== (param_type i) const
{
    return ((den == IntType(1)) && (num == i));
}
template <typename IntType>
bool rational<IntType, rational_check_for_overflow>::operator== (param_type i) const
{
    return ((num == i) && (den == 1));
}

// Invariant check
template <typename IntType>
inline bool rational<IntType, rational_check_for_overflow>::test_invariant() const
{
    return  ( this->den > int_type(0) ) && ( math::gcd(this->num, this->den) == int_type(1) );
}

// Normalisation
template <typename IntType, rational_checktype CheckingMode>
void rational<IntType, CheckingMode>::normalize()
{
    // Avoid repeated construction
    const IntType zero(0);

    if (den == zero)
        throw bad_rational();

    // Handle the case of zero separately, to avoid division by zero
    const IntType one(1);
    if (num == zero) {
        den = one;
        return;
    }

    IntType g = math::gcd(num, den);

    if(g != one)
    {
        num /= g;
        den /= g;
    }

    // Ensure that the denominator is positive
    if (den < zero)
    {
        den = -den;
        num = -num;
    }

    BOOST_ASSERT( this->test_invariant() );
}
template <typename IntType>
void rational<IntType, rational_check_for_overflow>::normalize()
{
    // Avoid repeated construction
    const IntType zero(0);

    if (den == zero)
        throw bad_rational();

    // Handle the case of zero separately, to avoid division by zero
    const IntType one(1);
    if (num == zero) {
        den = one;
        return;
    }

    IntType g = math::gcd(num, den);

    if(g != one)
    {
        num /= g;
        den /= g;
    }

    // Ensure that the denominator is positive
    if (den < zero)
    {
        IntType neg_den = -den;
        IntType neg_num = -num;
        if(den == neg_den)  // den never zero here
            throw rational_overflow();
        if(num == neg_num)  // num never zero here
            throw rational_overflow();
        den = neg_den;
        num = neg_num;
    }

    BOOST_ASSERT( this->test_invariant() );
}

namespace detail {

    // A utility class to reset the format flags for an istream at end
    // of scope, even in case of exceptions
    struct resetter {
        resetter(std::istream& is) : is_(is), f_(is.flags()) {}
        ~resetter() { is_.flags(f_); }
        std::istream& is_;
        std::istream::fmtflags f_;      // old GNU c++ lib has no ios_base
    };

}

// Input and output
template <typename IntType, rational_checktype CheckingMode>
std::istream& operator>> (std::istream& is, rational<IntType, CheckingMode>& r)
{
    IntType n = IntType(0), d = IntType(1);
    char c = 0;
    detail::resetter sentry(is);

    is >> n;
    c = is.get();

    if (c != '/')
        is.clear(std::istream::badbit);  // old GNU c++ lib has no ios_base

#if !defined(__GNUC__) || (defined(__GNUC__) && (__GNUC__ >= 3)) || defined __SGI_STL_PORT
    is >> std::noskipws;
#else
    is.unsetf(ios::skipws); // compiles, but seems to have no effect.
#endif
    is >> d;

    if (is)
        r.assign(n, d);

    return is;
}

template <typename IntType>
std::istream& operator>> (std::istream& is, rational<IntType, rational_check_for_overflow>& r)
{
    IntType n = IntType(0), d = IntType(1);
    char c = 0;
    detail::resetter sentry(is);

    is >> n;
    c = is.get();

    if (c != '/')
        is.clear(std::istream::badbit);  // old GNU c++ lib has no ios_base

#if !defined(__GNUC__) || (defined(__GNUC__) && (__GNUC__ >= 3)) || defined __SGI_STL_PORT
    is >> std::noskipws;
#else
    is.unsetf(ios::skipws); // compiles, but seems to have no effect.
#endif
    is >> d;

    if (is)
        r.assign(n, d);

    return is;
}
// Add manipulators for output format?
template <typename IntType, rational_checktype CheckingMode>
std::ostream& operator<< (std::ostream& os, const rational<IntType, CheckingMode>& r)
{
    os << r.numerator() << '/' << r.denominator();
    return os;
}

template <typename IntType>
std::ostream& operator<< (std::ostream& os, const rational<IntType, rational_check_for_overflow>& r)
{
    os << r.numerator() << '/' << r.denominator();
    return os;
}

// Create overloads for signed char, so numbers will get printed, instead of characters.
std::ostream& operator<< (std::ostream& os, const rational<signed char, rational_no_checking>& r)
{
    os << (int)r.numerator() << '/' << (int)r.denominator();
    return os;
}

std::ostream& operator<< (std::ostream& os, const rational<signed char, rational_check_for_overflow>& r)
{
    os << (int)r.numerator() << '/' << (int)r.denominator();
    return os;
}


// Type conversion
template <typename T, typename IntType, rational_checktype CheckingMode>
inline T rational_cast(
    const rational<IntType, CheckingMode>& src BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(T))
{
    return static_cast<T>(src.numerator())/static_cast<T>(src.denominator());
}

// Do not use any abs() defined on IntType - it isn't worth it, given the
// difficulties involved (Koenig lookup required, there may not *be* an abs()
// defined, etc etc).
template <typename IntType>
inline rational<IntType, rational_no_checking> abs(const rational<IntType, rational_no_checking>& r)
{
    return r.numerator() >= IntType(0)? r: -r;
}
template <typename IntType>
inline rational<IntType, rational_check_for_overflow> abs(const rational<IntType, rational_check_for_overflow>& r)
{
    const IntType zero(0);

    if (r.numerator() >= zero)
        return r;
    else
    {
        IntType negnumer = -r.numerator();
        if(r.numerator() == negnumer) // negnumer is never zero here
            throw rational_overflow();

        return -r;
    }
}

typedef rational<signed char,rational_check_for_overflow>  RatSCharwOvCk;
typedef rational<signed char,rational_no_checking>         RatSChar;

typedef rational<short,rational_check_for_overflow>        RatSShortwOvCk;
typedef rational<short,rational_no_checking>               RatShort;

typedef rational<int,rational_check_for_overflow>          RatSIntwOvCk;
typedef rational<int,rational_no_checking>                 RatSInt;

typedef rational<long long,rational_check_for_overflow>    RatSLLwOvCk;
typedef rational<long long,rational_no_checking>           RatSLL;


} // namespace boost


#endif  // BOOST_RATIONAL_HPP

