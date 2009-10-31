/*-----------------------------------------------------------------------------+    
Author: Joachim Faulhaber
Copyright (c) 2009-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_LIBS_ITL_EXAMPLE_LARGE_BITSET__LARGE_BITSET_HPP_JOFA_091019
#define BOOST_LIBS_ITL_EXAMPLE_LARGE_BITSET__LARGE_BITSET_HPP_JOFA_091019
//[large_bitset_includes
#include <iostream>                   // to organize output
#include <boost/cstdint.hpp>          // portable boost integers
#include <boost/operators.hpp>        // to define operators with minimal effort
#include "meta_log.hpp"               // a meta logarithm
#include "bits.hpp"                   // a minimal bitset implementation
#include <boost/itl/interval_map.hpp> // base of large bitsets

namespace mini // minimal implementations for example projects
{
//]

//[large_bitset_natural_typedefs
typedef boost::uint8_t  nat8; // nati i: number bits
typedef boost::uint16_t nat16;
typedef boost::uint32_t nat32; 
typedef boost::uint64_t nat64; 
typedef nat32           nat; 

typedef bits<nat8>  bits8;
typedef bits<nat16> bits16;
typedef bits<nat32> bits32;
typedef bits<nat64> bits64;
//]

//[large_bitset_class_template_header
template 
<
    typename    DomainT = nat64, 
    typename    BitSetT = bits64, 
    ITL_COMPARE Compare = ITL_COMPARE_INSTANCE(std::less, DomainT),
    template<class, ITL_COMPARE>class Interval = boost::itl::interval,
    ITL_ALLOC   Alloc   = std::allocator
> 
class large_bitset
    : boost::equality_comparable < large_bitset<DomainT,BitSetT,Compare,Interval,Alloc>
    , boost::less_than_comparable< large_bitset<DomainT,BitSetT,Compare,Interval,Alloc>

    , boost::addable       < large_bitset<DomainT,BitSetT,Compare,Interval,Alloc>
    , boost::orable        < large_bitset<DomainT,BitSetT,Compare,Interval,Alloc>
    , boost::subtractable  < large_bitset<DomainT,BitSetT,Compare,Interval,Alloc>
    , boost::andable       < large_bitset<DomainT,BitSetT,Compare,Interval,Alloc>
    , boost::xorable       < large_bitset<DomainT,BitSetT,Compare,Interval,Alloc>

    , boost::addable2      < large_bitset<DomainT,BitSetT,Compare,Interval,Alloc>, DomainT
    , boost::orable2       < large_bitset<DomainT,BitSetT,Compare,Interval,Alloc>, DomainT
    , boost::subtractable2 < large_bitset<DomainT,BitSetT,Compare,Interval,Alloc>, DomainT
    , boost::andable2      < large_bitset<DomainT,BitSetT,Compare,Interval,Alloc>, DomainT
    , boost::xorable2      < large_bitset<DomainT,BitSetT,Compare,Interval,Alloc>, DomainT

    , boost::addable2      < large_bitset<DomainT,BitSetT,Compare,Interval,Alloc>, Interval<DomainT,Compare>
    , boost::orable2       < large_bitset<DomainT,BitSetT,Compare,Interval,Alloc>, Interval<DomainT,Compare>
    , boost::subtractable2 < large_bitset<DomainT,BitSetT,Compare,Interval,Alloc>, Interval<DomainT,Compare>
    , boost::andable2      < large_bitset<DomainT,BitSetT,Compare,Interval,Alloc>, Interval<DomainT,Compare>
    , boost::xorable2      < large_bitset<DomainT,BitSetT,Compare,Interval,Alloc>, Interval<DomainT,Compare>
      > > > > > > > > > > > > > > > > >
    //^ & - | + ^ & - | + ^ & - | + < == 
    //segment   element   container
//]
{
public:
    //[large_bitset_associated_types
    typedef boost::itl::interval_map
        <DomainT, BitSetT, boost::itl::partial_absorber, 
         std::less, boost::itl::inplace_bit_add, boost::itl::inplace_bit_and> interval_bitmap_type;

    typedef DomainT                                      domain_type;
    typedef DomainT                                      element_type;
    typedef BitSetT                                      bitset_type;
    typedef typename BitSetT::word_type                  word_type;
    typedef typename interval_bitmap_type::interval_type interval_type;
    typedef typename interval_bitmap_type::value_type    value_type;
    //]
//[large_bitset_operators
public:
    bool     operator ==(const large_bitset& rhs)const { return _map == rhs._map; }
    bool     operator < (const large_bitset& rhs)const { return _map <  rhs._map; }

    large_bitset& operator +=(const large_bitset& rhs) {_map += rhs._map; return *this;}
    large_bitset& operator |=(const large_bitset& rhs) {_map |= rhs._map; return *this;}
    large_bitset& operator -=(const large_bitset& rhs) {_map -= rhs._map; return *this;}
    large_bitset& operator &=(const large_bitset& rhs) {_map &= rhs._map; return *this;}
    large_bitset& operator ^=(const large_bitset& rhs) {_map ^= rhs._map; return *this;}

    large_bitset& operator +=(const element_type& rhs) {return add(interval_type(rhs, rhs));      }
    large_bitset& operator |=(const element_type& rhs) {return add(interval_type(rhs, rhs));      }
    large_bitset& operator -=(const element_type& rhs) {return subtract(interval_type(rhs, rhs)); }
    large_bitset& operator &=(const element_type& rhs) {return intersect(interval_type(rhs, rhs));}
    large_bitset& operator ^=(const element_type& rhs) {return flip(interval_type(rhs, rhs));     }

    large_bitset& operator +=(const interval_type& rhs){return add(rhs);      }
    large_bitset& operator |=(const interval_type& rhs){return add(rhs);      }
    large_bitset& operator -=(const interval_type& rhs){return subtract(rhs); }
    large_bitset& operator &=(const interval_type& rhs){return intersect(rhs);}
    large_bitset& operator ^=(const interval_type& rhs){return flip(rhs);     }
    //]
    //[large_bitset_fundamental_functions
    large_bitset& add      (const interval_type& rhs){return segment_apply(&large_bitset::add_,      rhs);}
    large_bitset& subtract (const interval_type& rhs){return segment_apply(&large_bitset::subtract_, rhs);}
    large_bitset& intersect(const interval_type& rhs){return segment_apply(&large_bitset::intersect_,rhs);}
    large_bitset& flip     (const interval_type& rhs){return segment_apply(&large_bitset::flip_,     rhs);}
    //]

    //[large_bitset_demo_functions
    size_t interval_count()const { return _map.interval_count(); }

    void show_segments()const
    {
        for(typename interval_bitmap_type::const_iterator it_ = _map.begin();
            it_ != _map.end(); ++it_)
        {
            interval_type   itv  = it_->first;
            bitset_type     bits = it_->second;
            std::cout << itv << "->" << bits.as_string("01") << std::endl;
        }
    }

    void show_matrix(const char off_on[2] = " 1")const
    {
        typename interval_bitmap_type::const_iterator iter = _map.begin();
        while(iter != _map.end())
        {
            element_type fst = iter->first.first(), lst = iter->first.last();
            for(element_type chunk = fst; chunk <= lst; chunk++)
                std::cout << iter->second.as_string(off_on) << std::endl;
            ++iter;
        }
    }
    //]

//[large_bitset_impl_constants
private:                                      // Example value
    static const word_type                    //   8-bit case  
        digits  = sizeof(word_type)*CHAR_BIT, //   8           Size of the associated bitsets 
        divisor = digits                    , //   8           Divisor to find intervals for values
        shift   = log2_<divisor>::value     , //   3           To express the division as bit shift
        w1      = static_cast<word_type>(1) , //               Helps to avoid static_casts for long long
        mask    = divisor - w1              , //   7=11100000  Helps to express the modulo operation as bit_and
        all     = ~static_cast<word_type>(0), // 255=11111111  Helps to express a complete associated bitset
        top     = w1 << (digits-w1)      ;    // 128=00000001  Value of the most significant bit of associated bitsets
                                              //            !> Note: Most signigicant bit on the right.
    //]
    //[large_bitset_segment_combiner
    typedef void (large_bitset::*segment_combiner)(element_type, element_type, bitset_type);
    //]

    //[large_bitset_bitset_filler
    word_type from_lower_to(word_type bit){return bit==digits-w1 ? all : (1<<(bit+1))-1;}
    word_type to_upper_from(word_type bit){return bit==digits-w1 ? top : ~((1<<bit)-1); }
    //]

    //[large_bitset_segment_apply
    large_bitset& segment_apply(segment_combiner combine, const interval_type& operand)
    {                                                   // same as
        element_type   base = operand.first() >> shift, // operand.first()/ divisor
                       ceil = operand.last()  >> shift; // operand.last() / divisor
        word_type base_rest = operand.first() &  mask , // operand.first()% divisor
                  ceil_rest = operand.last()  &  mask ; // operand.last() % divisor  

        if(base == ceil) // [first, last] are within one bitset (chunk)
            (this->*combine)(base, base+1, bitset_type(  to_upper_from(base_rest)
                                                       & from_lower_to(ceil_rest)));
        else // [first, last] spread over more than one bitset (chunk)
        {
            element_type mid_low = base_rest == 0   ? base   : base+1, // first element of mid part 
                         mid_up  = ceil_rest == all ? ceil+1 : ceil  ; // last  element of mid part

            if(base_rest > 0)    // Bitset of base interval has to be filled from base_rest to last
                (this->*combine)(base, base+1, bitset_type(to_upper_from(base_rest)));
            if(ceil_rest < all)  // Bitset of ceil interval has to be filled from first to ceil_rest
                (this->*combine)(ceil, ceil+1, bitset_type(from_lower_to(ceil_rest)));
            if(mid_low < mid_up) // For the middle part all bits have to set.
                (this->*combine)(mid_low, mid_up, bitset_type(all));
        }
        return *this;
    }
    //]

    //[large_bitmap_combiners
    void       add_(DomainT lo, DomainT up, BitSetT bits){_map += value_type(interval_type::rightopen(lo,up), bits);}
    void  subtract_(DomainT lo, DomainT up, BitSetT bits){_map -= value_type(interval_type::rightopen(lo,up), bits);}
    void intersect_(DomainT lo, DomainT up, BitSetT bits){_map &= value_type(interval_type::rightopen(lo,up), bits);}
    void      flip_(DomainT lo, DomainT up, BitSetT bits){_map ^= value_type(interval_type::rightopen(lo,up), bits);}
    //]

//[large_bitmap_impl_map
private:
    interval_bitmap_type _map;
//]
};

} // mini
#endif


