// (C) Copyright 2003-2004: Reece H. Dunn
// Use, modification, and distribution are subject to the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This code is based on boost-sandbox/boost/wave/util/flex_string.hpp by Andrei Alexandrescu,
// modified my Hartmut Kasier

// The main changes are:
// *  uses an iterator_adaptor-style approach instead of StoragePolicy
// *  uses an ErrorPolicy class to handle out_of_range and length_error exceptions
// *  uses the traits_type functions instead of the POD functions
//       pod_move( const Pod * b, const Pod * e, Pod * d ) --> traits_type::move( d, b, ( e - b ))
//       pod_copy( const Pod * b, const Pod * e, Pod * d ) --> traits_type::copy( d, b, ( e - b ))
//       pod_fill( Pod * b, Pod * e, T c )                 --> traits_type::assign( b, ( e - b ), c )
// *  added exception handling for resize and reserve
// *  uses an MPL-based approach to check InputIterator on replace( iterator i1, iterator i2, InputIterator j1, InputIterator j2 )
// *  uses basic_string as the substring type (currently via a typedef: will make this a template policy at some point)
// *  uses optimized versions of find and rfind for searching for single characters

#ifndef BOOST_BASIC_STRING_IMPL_HPP
#define BOOST_BASIC_STRING_IMPL_HPP
#  include <boost/config.hpp>
#  include <boost/mpl/if.hpp>
#  include <boost/mpl/bool.hpp>
#  include <algorithm>
#  include <iostream>

   namespace boost{ namespace detail
   {
      inline size_t min_( size_t a, size_t b )
      {
         return(( a < b ) ? a : b );
      }

      struct noerror_string_policy
      {
         static inline void                      out_of_range()
         {
         }
         static inline void                      length_error()
         {
         }
      };

      struct exception_string_policy
      {
         static inline void                      out_of_range()
         {
            throw( std::out_of_range( "" ));
         }
         static inline void                      length_error()
         {
            throw( std::length_error( "" ));
         }
      };
      
      /*
         begin() | end() :: rbegin() | rend()
         length() | capacity() | max_size()
         data() | c_str() | at( size_t i )

         resize(  size_type n, value_type c )
         reserve( size_type n )

         assign( const char_type * s, size_type n )
         append( const char_type * s, size_type n )
         push_back( char_type c )
      */

      template
      <
         class StringPolicy, typename CharT = char,
         class CharPolicy = std::char_traits< CharT >,
         class ErrorPolicy = noerror_string_policy
      >
      class basic_string_impl
      {
         public: // types
            typedef StringPolicy                                     string_type;
            typedef std::basic_string< CharT, CharPolicy >           substring_type;
            typedef typename CharPolicy                              traits_type;
            typedef typename traits_type::char_type                  value_type;
            typedef typename traits_type::char_type                  char_type;
            typedef std::allocator< value_type >                     allocator_type;
         public:
            typedef typename allocator_type::size_type               size_type;
            typedef typename allocator_type::difference_type         difference_type;
            typedef typename allocator_type::reference               reference;
            typedef typename allocator_type::const_reference         const_reference;
            typedef typename allocator_type::pointer                 pointer;
            typedef typename allocator_type::const_pointer           const_pointer;
         public:
            typedef typename allocator_type::pointer                 iterator;
            typedef typename allocator_type::const_pointer           const_iterator;
#           if !defined(BOOST_NO_STD_ITERATOR)
               typedef std::reverse_iterator< iterator >             reverse_iterator;
               typedef std::reverse_iterator< const_iterator >       const_reverse_iterator;
#           else
               typedef std::reverse_iterator< iterator, value_type > reverse_iterator;
               typedef std::reverse_iterator< const_iterator, const value_type >
                                                                     const_reverse_iterator;
#           endif
         public:
            BOOST_STATIC_CONSTANT( size_type, npos = -1 );
         private: // implementation helpers
            inline string_type &                 get_impl()
            {
               return( *static_cast< string_type * >( this ));
            }
            inline const string_type &           get_impl() const
            {
               return( *static_cast< const string_type * >( this ));
            }
            inline const char_type *             offset( size_type pos )
            {
               return( &*( begin() + pos ));
            }
         public: // 21.3.2: iterators
            inline const_iterator                begin() const
            {
               return( get_impl().begin());
            }
            inline iterator                      begin()
            {
               return( get_impl().begin());
            }
            inline const_iterator                end() const
            {
               return( get_impl().end()); 
            }
            inline iterator                      end()
            {
               return( get_impl().end());
            }
            inline const_reverse_iterator        rbegin() const
            {
               return( get_impl().rbegin());
            }
            inline reverse_iterator              rbegin()
            {
               return( get_impl().rbegin());
            }
            inline const_reverse_iterator        rend() const
            {
               return( get_impl().rend());
            }
            inline reverse_iterator              rend()
            {
               return( get_impl().rend());
            }
         public: // 21.3.3: capacity
            inline size_type                     size() const
            {
               return( get_impl().length());
            }
            inline size_type                     length() const
            {
               return( get_impl().length());
            }
            inline size_type                     max_size() const
            {
               return( get_impl().max_size());
            }
            inline void                          resize( size_type n, char_type c )
            {
               if( n > max_size())     ErrorPolicy::length_error();
               get_impl().resize( n, c );
            }
            inline void                          resize( size_type n )
            {
               resize( n, value_type());
            }
            inline size_type                     capacity() const
            {
               return( get_impl().capacity());
            }
            inline void                          reserve( size_type n = 0 )
            {
               if( n > max_size())     ErrorPolicy::length_error();
               get_impl().reserve( n );
            }
            inline void                          clear()
            {
               erase();
            }
            inline bool                          empty() const
            {
               return( get_impl().length() == 0 );
            }
         public: // 21.3.4: element access
            inline const_reference operator[]( size_type i ) const
            {
               return( get_impl().at( i ));
            }
            inline reference       operator[]( size_type i )
            {
               return( get_impl().at( i ));
            }
            inline const_reference               at( size_type i ) const
            {
               if( i > length())       ErrorPolicy::out_of_range();
               return( get_impl().at( i ));
            }
            inline reference                     at( size_type i )
            {
               if( i > length())       ErrorPolicy::out_of_range();
               return( get_impl().at( i ));
            }
         public: // 21.3.5: modifiers
            inline string_type &                 assign( const string_type & s )
            {
               if( &s != this )        assign( s.data(), s.length());
               return( get_impl());
            }
            inline string_type &                 assign( const string_type & s, size_type pos, size_type n )
            {
               if( pos > s.size())     ErrorPolicy::out_of_range();
               return( assign( s.data() + pos, min_( n, s.size() - pos )));
            }
            inline string_type &                 assign( const char_type * s, size_type n )
            {
               return( get_impl().assign( s, n ));
            }
            inline string_type &                 assign( const char_type * s )
            {
               return( assign( s, traits_type::length( s )));
            }
            inline string_type &                 assign( size_type n, char_type c )
            {
               return( replace( begin(), end(), n, c ));
            }
            template< typename InputIterator >
            inline size_type &                   assign( InputIterator first, InputIterator last )
            {
               clear();
               while( first != last )  get_impl().push_back( *first++ );
            }
         public:
            inline string_type &  operator=( const string_type & s )
            {
               return( assign( s ));
            }
            inline string_type &  operator=( const char_type * s )
            {
               return( assign( s ));
            }
            inline string_type &  operator=( char_type c )
            {
               clear();
               get_impl().push_back( c );
               return( get_impl());
            }
         public:
            inline string_type &                 append( const string_type & s )
            {
               return( append( s, 0, npos ));
            }
            inline string_type &                 append( const string_type & s, size_type pos, size_type n )
            {
               const size_type         sz = s.size();
               if( pos > sz )          ErrorPolicy::out_of_range();
               return( append( s.c_str() + pos, min_( n, sz - pos )));
            }
            inline string_type &                 append( const char_type * s, size_type n )
            {
               return( get_impl().append( s, n ));
            }
            inline string_type &                 append( const char_type * s )
            {
               return( append( s, traits_type::length( s )));
            }
            inline string_type &                 append( size_type n, char_type c )
            {
               get_impl().resize( size() + n, c );
               return( get_impl());
            }
            template< typename InputIterator >
            inline size_type &                   append( InputIterator first, InputIterator last )
            {
               while( first != last )  get_impl().push_back( *first++ );
            }
            inline void                          push_back( const char_type c )
            {
               get_impl().push_back( c );
            }
         public:
            inline string_type &  operator+=( const string_type & s )
            {
               return( append( s ));
            }
            inline string_type &  operator+=( const char_type * s )
            {
               return( append( s ));
            }
            inline string_type &  operator+=( char_type c )
            {
               push_back( c );
               return( get_impl());
            }
         public:
            inline string_type &                 insert( size_type pos1, const string_type & s )
            {
               return( insert( pos1, str, 0, npos ));
            }
            inline string_type &                 insert( size_type pos1, const string_type & s, size_type pos2, size_type n )
            {
               return( replace( pos1, 0, s, pos2, n ));
            }
            inline string_type &                 insert( size_type pos, const char_type * s, size_type n )
            {
               return( replace( pos, 0, s, n ));
            }
            inline string_type &                 insert( size_type pos, const char_type * s )
            {
               return( insert( pos, s, traits_type::length( s )));
            }
            inline string_type &                 insert( size_type pos, size_type n, value_type c )
            {
               return( replace( pos, 0, n, c ));
            }
            inline iterator                      insert( iterator p, value_type c = value_type())
            {
               const size_type         pos = p - begin();
               insert( pos, &c, 1 );
               return( begin() + pos );
            }
            inline void                          insert( iterator p, size_type n, char_type c )
            {
               insert( p - begin(), n, c );
            }
            template< typename InputIterator >
            inline void                          insert( iterator p, InputIterator first, InputIterator last )
            {
               replace( p, p, first, last );
            }
         public:
            inline string_type &                 erase( size_type pos = 0, size_type n = npos )
            {
               return( replace( pos, min_( n, size() - pos ), 0, value_type()));
            }
            inline iterator                      erase( iterator pos )
            {
               const size_type         pos = position - begin();
               erase( pos, 1 );
               return( begin() + pos );
            }
            inline iterator                      erase( iterator first, iterator last )
            {
               const size_type         pos = first - begin();
               erase( pos, last - first );
               return( begin() + pos );
            }
         public:
            inline string_type &                 replace( size_type pos1, size_type n1, const string_type & s )
            {
               return( replace( pos1, n1, s, 0, npos ));
            }
            inline string_type &                 replace( size_type pos1, size_type n1, const string_type & s, size_type pos2, size_type n2 )
            {
               if( pos1 > length())    ErrorPolicy::out_of_range();
               return( replace( pos1, n1, s.offset( pos2 ), min_( n2, s.length() - pos2 )));
            }
            inline string_type &                 replace( size_type d, size_type n1, const char_type * s, size_type n2 )
            {
               if( d > size())         ErrorPolicy::out_of_range();
               if( d + n1 > size())    n1 = size() - d;
               static const std::less_equal< const value_type * > le = std::less_equal< const value_type * >();

               const int               delta   = int( n2 - n1 );
               const bool              aliased = le( &*begin(), s1 ) && le( s1, &*end());
               if( delta > 0 )
               {
                  if( capacity() < size() + delta ) // realloc the string
                  {
                     if( aliased )
                     {
                        const size_type off = s1 - &*begin();
                        reserve( size() + delta );
                        s1 = offset( off );
                     }
                     else reserve( size() + delta );
                  }

                  const value_type *   s2   = s1 + n2;
                  value_type *         d1   = offset( d );
                  value_type *         d2   = d1 + n1;
                  const int            len_ = int( &*end() - d2 );
                  if( delta <= len_ )
                  {
                     value_type *      end_ = &*end();
                     get_impl().append( end_ - delta, delta );
                     traits_type::move( d2 + delta, d2, ( len_ - delta ));
                     if( le( d2, s1 ))
                     {
                        if( aliased )  traits_type::copy( d1, s1 + delta, ( s2 - s1 ));
                        else           traits_type::copy( d1, s1, ( s2 - s1 ));
                     }
                     else
                     {
                        if( le( d2, s2 ))
                        {
                           // assert( aliased );
                           traits_type::move( d1, s1, ( d2 - s1 ));
                           traits_type::move( d1 + ( d2 - s1 ), d2 + delta, ( s2 - d2 ));
                        }
                        else traits_type::move( d1, s1, ( s2 - s1 ));
                     }
                  }
                  else
                  {
                     const size_type   sz = delta - len_;
                     get_impl().append( s2 - sz, sz );
                     get_impl().append( d2, len_ );
                     traits_type::move( d1, s1, (( s2 - delta + len_ ) - s1 ));
                  }
               }
               else
               {
                  traits_type::move( offset( d ), s1, n2 );
                  traits_type::move( offset( d + n1 + delta ), offset( d + n1 ), ( &*end() - offset( d + n1 )));
                  resize( size() + delta );
               }
               return( get_impl());
            }
            inline string_type &                 replace( size_type d, size_type n1, const char_type * s )
            {
               return( replace( d, n1, s, traits_type::length( s )));
            }
            inline string_type &                 replace( size_type pos, size_type n1, size_type n2, char_type c )
            {
               if( pos + n1 > size())  n1    = size() - pos;
               const size_type         size_ = size();
               if( pos + n2 > size_ )
               {
                  resize( pos + n2, c );
                  get_impl().append( offset( pos + n1 ), size_ - pos - n1 );
                  traits_type::assign( offset( pos ), size_ - pos, c );
               }
               else
               {
                  if( n2 > n1 )
                  {
                     const size_type   delta = n2 - n1;
                     get_impl().append( offset( size_ - delta ), delta );
                     traits_type::move( offset( pos + n2 ), offset( pos + n1 ), ( size_ - delta - pos - n1 ));
                  }
                  else
                  {
                     traits_type::move( offset( pos + n2 ), offset( pos + n1 ), size() - pos - n1 );
                     resize( size_ - ( n1 - n2 ));
                  }
                  traits_type::assign( offset( pos ), n2, c );
               }
               return( get_impl());
            }
            inline string_type &                 replace( iterator i1, iterator i2, const string_type & s )
            {
               return( replace( i1, i2, s.c_str(), s.length()));
            }
            inline string_type &                 replace( iterator i1, iterator i2, const char_type * s, size_type n )
            {
               return( replace( i1 - begin(), i2 - i1, s, n ));
            }
            inline string_type &                 replace( iterator i1, iterator i2, const char_type * s )
            {
               return( replace( i1, i2, s, traits_type::length( s )));
            }
            inline string_type &                 replace( iterator i1, iterator i2, size_type n, char_type c )
            {
               return( replace( i1 - begin(), i2 - i1, n, c ));
            }
            template< typename InputIterator >
            inline string_type &                 replace( iterator i1, iterator i2, InputIterator j1, InputIterator j2 )
            {
               struct ok{ typedef char value; };
               struct non_integral_type_error{};
               typedef typename mpl::if_< mpl::bool_< std::numeric_limits<InputIterator>::is_specialized >,
                                          ok, non_integral_type_error
                                        >::type::value               non_integral_type_check;

               return( replace( i1, i2, static_cast< size_type >( n ), static_cast< value_type >( c )));
            }
         public:
            inline size_type                     copy( char_type * s, size_type n, size_type pos = 0 ) const
            {
               if( pos > size())       ErrorPolicy::out_of_range();
               n = min_( n, size() - pos );
               traits_type::copy( s, offset( pos ), n );
               s[ n ] = char_type( '\0' );
               return( n );
            }
            inline void                          swap( string_type & s )
            {
               get_impl().swap( s );
            }
         public: // 21.3.6: string operations
            inline const char_type *             c_str() const
            {
               return( get_impl().c_str());
            }
            inline const char_type *             data() const
            {
               return( get_impl().data());
            }
            inline allocator_type                get_allocator() const
            {
               return( get_impl().get_allocator());
            }
         public:
            inline size_type                     find( const string_type & s, size_type pos = 0 ) const
            {
               return( find( s.data(), pos, s.length()));
            }
            inline size_type                     find( const char_type * s, size_type pos, size_type n ) const
            {
               const size_type         sz = size();
               for( ; pos <= sz; ++pos )
               {
                  if( traits_type::compare( offset( pos ), s, n ) == 0 )
                     return( pos );
               }
               return( npos );
            }
            inline size_type                     find( const char_type * s, size_type pos = 0 ) const
            {
               return( find( s, pos, traits_type::length( s )));
            }
            inline size_type                     find( char_type c, size_type pos = 0 ) const
            {
               const_iterator          last( end());
               for( const_iterator first( begin() + pos ); first != last; ++first )
               {
                  if( traits_type::eq( *first, c ))
                     return( pos );
               }
               return( npos );
            }
         public:
            inline size_type                     rfind( const string_type & s, size_type pos = npos ) const
            {
               return( rfind( s.c_str(), pos, s.length()));
            }
            inline size_type                     rfind( const char_type * s, size_type pos, size_type n ) const
            {
               if( n > length())       return( npos );
               pos = min_( pos, length() - n );
               if( n == 0 )            return( pos );
               
               for( const_iterator i( begin() + pos );; --i )
               {
                  if( traits_type::eq( *i, *s ) && traits_type::compare( &*i, s, n ) == 0 )
                     return( i - begin());
                  if( i == begin())    break;
               }
               return( npos );
            }
            inline size_type                     rfind( const char_type * s, size_type pos = npos ) const
            {
               return( rfind( s, pos, traits_type::length( s )));
            }
            inline size_type                     rfind( char_type c, size_type pos = npos ) const
            {
               if( n > length())       return( npos );
               pos = min_( pos, length() - n );
               if( n == 0 )            return( pos );
               
               for( const_iterator i( begin() + pos );; --i )
               {
                  if( traits_type::eq( *i, c ))
                     return( i - begin());
                  if( i == begin())    break;
               }
               return( npos );
            }
         public:
            inline size_type                     find_first_of( const string_type & s, size_type pos = 0 ) const
            {
               return( find_first_of( s.c_str(), pos, s.length()));
            }
            inline size_type                     find_first_of( const char_type * s, size_type pos, size_type n ) const
            {
               if( pos > length() || n == 0 )
                  return( npos );
                  
               const_iterator          last( end());
               for( const_iterator first( begin() + pos ); i != last; ++i )
               {
                  if( traits_type::find( s, n, *i ) != 0 )
                     return( i - begin());
               }
               return( npos );
            }
            inline size_type                     find_first_of( const char_type * s, size_type pos = 0 ) const
            {
               return( find_first_of( s, pos, traits_type::length( s )));
            }
            inline size_type                     find_first_of( char_type c, size_type pos = 0 ) const
            {
               return( find_first_of( &c, pos, 1 )); // optimize?
            }
         public:
            inline size_type                     find_last_of( const string_type & s, size_type pos = 0 ) const
            {
               return( find_last_of( s.c_str(), pos, s.length()));
            }
            inline size_type                     find_last_of( const char_type * s, size_type pos, size_type n ) const
            {
               if( !empty() && n > 0 )
               {
                  pos = min_( pos, length() - 1 );
                  for( const_iterator i( begin() + pos );; --i )
                  {
                     if( traits_type::find( s, n, *i ) != 0 )
                        return( i - begin());
                     if( i == begin()) break;
                  }
               }
               return( npos );
            }
            inline size_type                     find_last_of( const char_type * s, size_type pos = 0 ) const
            {
               return( find_last_of( s, pos, traits_type::length( s )));
            }
            inline size_type                     find_last_of( char_type c, size_type pos = 0 ) const
            {
               return( find_last_of( &c, pos, 1 )); // optimize?
            }
         public:
            inline size_type                     find_first_not_of( const string_type & s, size_type pos = 0 ) const
            {
               return( find_first_not_of( s.data(), pos, s.length()));
            }
            inline size_type                     find_first_not_of( const char_type * s, size_type pos, size_type n ) const
            {
               if( pos < length())
               {
                  const_iterator       last( end());
                  for( const_iterator first( begin() + pos ); i != last; ++i )
                  {
                     if( traits_type::find( s, n, *i ) == 0 )
                        return( i - begin());
                  }
               }
               return( npos );
            }
            inline size_type                     find_first_not_of( const char_type * s, size_type pos = 0 ) const
            {
               return( find_first_not_of( s, pos, traits_type::length( s )));
            }
            inline size_type                     find_first_not_of( char_type c, size_type pos = 0 ) const
            {
               return( find_first_not_of( &c, pos, 1 )); // optimize?
            }
         public:
            inline size_type                     find_last_not_of( const string_type & s, size_type pos = 0 ) const
            {
               return( find_last_not_of( s.c_str(), pos, s.length()));
            }
            inline size_type                     find_last_not_of( const char_type * s, size_type pos, size_type n ) const
            {
               if( !empty())
               {
                  pos = min_( pos, size() - 1 );
                  for( const_iterator i( begin() + pos );; --i )
                  {
                     if( traits_type::find( s, n, *i ) == 0 )
                        return( i - begin());
                     if( i == begin()) break;
                  }
               }
               return( npos );
            }
            inline size_type                     find_last_not_of( const char_type * s, size_type pos = 0 ) const
            {
               return( find_last_not_of( s, pos, traits_type::length( s )));
            }
            inline size_type                     find_last_not_of( char_type c, size_type pos = 0 ) const
            {
               return( find_last_not_of( &c, pos, 1 )); // optimize?
            }
         public:
            inline substring_type                substr( size_type pos = 0, size_type n = npos ) const
            {
               if( pos > s.size())     ErrorPolicy::out_of_range();
               return( substring_type( data() + pos, min_( n, size() - pos )));
            }
         public:
            inline int                           compare( const string_type & s ) const
            {
               return( compare( 0, size(), s.data(), s.length()));
            }
            inline int                           compare( size_type pos1, size_type n1, const string_type & s ) const
            {
               return( compare( pos1, n1, s.data(), s.length()));
            }
            inline int                           compare( size_type pos1, size_type n1, const string_type & s, size_type pos2, size_type n2 ) const
            {
               if( pos2 > s.size())    ErrorPolicy::out_of_range();
               return( compare( pos1, n1, s.data() + pos2, min_( n2, s.size() - pos2 )));
            }
            inline int                           compare( const char_type * s ) const
            {
               return( compare( 0, size(), s, traits_type::length( s )));
            }
            inline int                           compare( size_type pos1, size_type n1, const char_type * s, size_type n2 = npos ) const
            {
               if( pos1 > size())      ErrorPolicy::out_of_range();
               n1 = min_( size() - pos1, n1 );
               const int               res = traits_type::compare( data() + pos1, s, min_( n1, n2 ));
               return(( res != 0 ) ? res : int( n1 - n2 ));
            }
         public:
            inline explicit  basic_string_impl()
            {
            }
      };

      template< typename CharT, class StreamPolicy, class StringPolicy, class ErrorPolicy >
      inline std::basic_ostream< CharT, StreamPolicy > & 
                                  operator<<
                                  (
                                     std::basic_ostream< CharT, StreamPolicy > & os,
                                     const basic_string_impl< StringPolicy, CharT, StreamPolicy, ErrorPolicy > & str
                                  )
      {
         return( os << str.c_str());
      }
   }}
#endif
