#ifndef BOOST_GENERIC_DETAIL_AND_HPP
#define BOOST_GENERIC_DETAIL_AND_HPP

#ifndef BOOST_GENERIC_GENERATE_PREPROCESSED_HEADERS

#include <boost/mpl/bool.hpp>

namespace boost { namespace generic { namespace detail {

template< bool L, class R >
struct and_impl : mpl::false_ {};

template< class R >
struct and_impl< true, R > : R {};

template< class... P >
struct and_;

template<>
struct and_<> : mpl::true_ {};

template< class H >
struct and_< H > : H {};

template< class H, class... P >
struct and_< H, P... > : and_impl< H::value, and_< P... > > {};

} } }

#endif

#endif // BOOST_GENERIC_DETAIL_AND_HPP
