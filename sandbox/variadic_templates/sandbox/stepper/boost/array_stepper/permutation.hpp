#ifndef BOOST_ARRAY_STEPPER_PERMUTAION_HPP_INCLUDED
#define BOOST_ARRAY_STEPPER_PERMUTAION_HPP_INCLUDED
#include <boost/array_stepper/mk_iota.hpp>
#ifdef __GXX_EXPERIMENTAL_CXX0X__
#include <algorithm>
#endif
#include <boost/assert.hpp>

namespace boost
{
namespace array_stepper
{
struct permutation
: private std::vector<unsigned>
{
    typedef std::vector<unsigned> permute_maybe_t;
    typedef permute_maybe_t::value_type value_type;
    typedef permute_maybe_t::const_iterator const_iterator;
    
    permute_maybe_t const&impl()const
    { 
        return *this;
    }
    
    unsigned operator[](unsigned i)const
    { 
        return impl()[i];
    }
    
    typename permute_maybe_t::const_iterator begin()const
    { 
        return impl().begin();
    }        
    
    typename permute_maybe_t::const_iterator end()const
    { 
        return impl().end();
    }        
    
    static bool is_permutation(permute_maybe_t const& a_permute_maybe)
    {
      #ifdef __GXX_EXPERIMENTAL_CXX0X__
        return 
          std::is_permutation
          ( a_permute_maybe.begin()
          , a_permute_maybe.end()
          , mk_iota(value_type(0),value_type(a_permute_maybe.size())).begin()
          );
      #else
        std::vector<bool> is_found(a_permute_maybe.size(),false);
        unsigned num_found=0;
        unsigned const n=a_permute_maybe.size();
        for(unsigned i=0; i<n; ++i)
        {
            value_type j=a_permute_maybe[i];
            if(n<=j) return false;
            if(is_found[j]) return false;
            is_found[j]=true;
            ++num_found;
        }
        return num_found==n;
      #endif
    }
    
    permutation(std::size_t s=0)
    : permute_maybe_t(mk_iota(value_type(0),value_type(s)))
    {}
    
    permutation(permute_maybe_t const& a_permute_maybe_v)
    : permute_maybe_t(a_permute_maybe_v)
    {
        BOOST_ASSERT(is_permutation(a_permute_maybe_v));
    }
    
    struct assert_is_permutation{};
    
    permutation( assert_is_permutation, permute_maybe_t const& a_permute_maybe_v)
    : permute_maybe_t(a_permute_maybe_v)
    {}

    permutation permute( permute_maybe_t const& other)
    {
        BOOST_ASSERT(is_permutation(other));
        unsigned const n=other.size();
        permute_maybe_t const&me=impl();
        BOOST_ASSERT(n==me.size());
        permute_maybe_t permuted(n);
        for(unsigned i=0; i<n; ++i) permuted[i]=me[other[i]];
        assert_is_permutation is_perm;
        return permutation( is_perm, permuted);
    }    

};

}//exit array_stepper namespace
}//exit boost namespace
#endif
