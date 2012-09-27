#ifndef BOOST_GENERIC_DETAIL_IS_NOT_SAME_HPP
#define BOOST_GENERIC_DETAIL_IS_NOT_SAME_HPP

namespace boost { namespace generic { namespace detail {

template< class L, class R >
struct is_not_same { static bool const value = true; };

template< class T >
struct is_not_same< T, T > { static bool const value = false; };

} } }

#endif // BOOST_GENERIC_DETAIL_IS_NOT_SAME_HPP
