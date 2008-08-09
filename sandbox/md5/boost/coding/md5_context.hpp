// Boost coding/md5_context.hpp header file  ---------------------------------//
/** \file
    \brief  Declaration of MD5 core computation object.

    \author  Daryle Walker

    Contains the declaration of the type used for the actual computing of MD5
    message digests.  Non-inline items declared here are defined in
    &quot;$BOOST_ROOT/libs/coding/src/md5.cpp&quot;.
 
    (C) Copyright Daryle Walker 2008.  Distributed under the Boost Software
    License, Version 1.0. (See the accompanying file LICENSE_1_0.txt or a copy
    at <http://www.boost.org/LICENSE_1_0.txt>.)
 */
// See <http://www.boost.org/libs/coding> for documentation.

#ifndef BOOST_CODING_MD5_CONTEXT_HPP
#define BOOST_CODING_MD5_CONTEXT_HPP

#include <boost/coding_fwd.hpp>
#include <boost/coding/md5_digest_core.hpp>  // for boost::coding::md5_digest

#include <boost/array.hpp>    // for boost::array
#include <boost/cstdint.hpp>  // for boost::uint_fast8_t
#include <boost/integer.hpp>  // for boost::sized_integral, fast_integral

#include <boost/mpl/times.hpp>  // for boost::mpl::times
#include <boost/mpl/int.hpp>    // for boost::mpl::int_

#include <boost/serialization/access.hpp>  // for boost::serialization::access

#include <algorithm>  // for std::equal, copy


namespace boost
{
namespace coding
{


//  Forward declarations  ----------------------------------------------------//

// None right now


//  MD5 message-digest core computation class declaration  -------------------//

/** \brief  A computer that produces MD5 message digests from consuming bits.

    This class is the bare-bones engine for the MD5 message-digest algorithm
    described in RFC 1321.  Besides computation, it also supports comparisons
    (equivalence only, not ordering) and serialization.

    \see  boost::coding::md5_digest
 */
class md5_context
{
    typedef md5_context  self_type;

public:
    // Types
    /** \brief  Type of the produced output

        Represents the result type, the checksums from hashing.
     */
    typedef md5_digest  product_type;
    /** \brief  Type of the consumed input

        Represents the argument type, the data to hash.
     */
    typedef bool       consumed_type;

    // Lifetime management (use automatic copy constructor and destructor)
    //! Default construction
    md5_context();

    /*! \name Operators */ //@{
    // Operators (use automatic copy-assignment)
    //! Application, consumer
    void          operator ()( consumed_type bit );
    //! Equals
    bool          operator ==( self_type const &o ) const;
    //! Not-equals
    bool          operator !=( self_type const &o ) const;
    //! Application, producer
    product_type  operator ()() const;//@}

private:
    friend class md5_computer;

    // Implementation types and meta-constants
    typedef md5_digest::bits_per_word        bits_per_word;
    typedef md5_digest::word_type                word_type;
    typedef md5_digest::words_per_digest  words_per_digest;

    typedef mpl::int_<2>                                words_per_length;
    typedef mpl::times<words_per_length, bits_per_word>  bits_per_length;
    typedef mpl::int_<16>                                words_per_block;
    typedef mpl::times<words_per_block, bits_per_word>    bits_per_block;

    typedef sized_integral<bits_per_length::value, unsigned>::type  length_type;
    typedef fast_integral<length_type>::type                       length_ftype;
    typedef fast_integral<word_type>::type                           word_ftype;
    typedef array<word_ftype, words_per_digest::value>              buffer_type;
    typedef array<consumed_type, bits_per_block::value>              queue_type;
    typedef array<word_ftype, 64>                               hash_table_type;

    // Implementation constants
    static  buffer_type const     initial_buffer;
    static  hash_table_type const  hashing_table;

    // Member data
    length_ftype  length;
    buffer_type   buffer;
    queue_type    queue;

    // Implementation
    void  consume_bit( bool bit );
    void  consume_octet( uint_fast8_t octet );
    void  consume_word( word_ftype word );
    void  consume_dword( length_ftype dword );

    void  update_hash();
    void  finish();

    /*! \name Persistence */ //@{
    // Serialization
    friend class boost::serialization::access;

    template < class Archive >
    void  serialize( Archive &ar, const unsigned int version );//@}  // not defined yet

};  // md5_context


//  MD5 message-digest core computation constructor definitions  -------------//

/** Constructs a \c md5_context set to initial conditions.  That is, with the
    buffer initialized as in RFC 1321, section 3.3, and no bits ever read.

    \post  Sorry, there is no externally-accessible state.  (However,
           <code>std::cout &lt;&lt; this-&gt;operator ()()</code> should write
           &quot;d41d8cd98f00b204e9800998ecf8427e&quot; to the console.)
 */
inline
md5_context::md5_context()  : length(), buffer( initial_buffer ), queue()  {}


//  MD5 message-digest core computation member operator func. definitions  ---//

/** Submits a bit for processing.

    \param bit  The bit value to be submitted.

    \post  Sorry, there is no externally-accessible state.  (However, the bit is
           queued until enough have been collected to update the internal hash.
           If an update occurs, the queue is emptied.)
 */
inline void
md5_context::operator ()( consumed_type bit )  { this->consume_bit( bit ); }

/** Compares computation contexts for equivalence.  Such contexts are equal if
    their internal states are equal.  (This means that they should both return
    the same checksum, and continue to do so as long as the same bit sequence is
    submitted to both contexts.)

    \param o  The right-side operand to be compared.

    \retval true   \c *this and \p o are equivalent.
    \retval false  \c *this and \p o are not equivalent.
 */
inline bool
md5_context::operator ==( self_type const &o ) const
{
    return ( this->length == o.length ) && ( this->buffer == o.buffer ) &&
     std::equal( this->queue.begin(), this->queue.begin() + this->length %
     bits_per_block::value, o.queue.begin() );
}

/** Compares computation contexts for non-equivalence.  Such engines are unequal
    if their internal states are unequal.  (Usually, the two contexts would
    return checksums that differ either immediately or after the same bit
    sequence is submitted to both contexts.  However, it is possible for two
    contexts with differing input histories to have the same output checksum.
    Worse, it is possible to deliberately create such a collision.)

    \param o  The right-side operand to be compared.

    \retval true   \c *this and \p o are not equivalent.
    \retval false  \c *this and \p o are equivalent.
 */
inline bool
md5_context::operator !=( self_type const &o ) const
{ return !this->operator ==( o ); }


//  MD5 message-digest core computation private member function definitions  -//

// Input a single bit.
inline void
md5_context::consume_bit( bool bit )
{
    this->queue[ this->length++ % bits_per_block::value ] = bit;
    if ( this->length % bits_per_block::value == 0u )
        this->update_hash();
}

// Input an octet (8 bits).  Needed for word-input.
inline void
md5_context::consume_octet( uint_fast8_t octet )
{
    // Start from high-order bit, go down; hopefully will be compiler-unrolled
    for ( int  i = 0 ; i < 8 ; ++i, octet <<= 1 )
        this->consume_bit( octet & 0x80u );
}

// Input a word (32 bits).  Needed for double-word-input.
inline void
md5_context::consume_word( word_ftype word )
{
    // Start from low-order octet, go up; hopefully will be compiler-unrolled
    for ( int  i = 0 ; i < 4 ; ++i, word >>= 8 )
        this->consume_octet( word & 0xFFu );
}

// Input a double-word (64 bits).  Needed for the finishing procedure.
inline void
md5_context::consume_dword( length_ftype dword )
{
    // Do the low word, then high; hopefully will be compiler-unrolled
    for ( int  i = 0 ; i < 2 ; ++i, dword >>= 32 )
        this->consume_word( dword & 0xFFFFFFFFul );
}


}  // namespace coding
}  // namespace boost


#endif  // BOOST_CODING_MD5_CONTEXT_HPP
