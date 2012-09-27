#ifndef BOOST_GENERIC_DETAIL_ALWAYS_VOID_HPP
#define BOOST_GENERIC_DETAIL_ALWAYS_VOID_HPP

namespace boost { namespace generic { namespace detail {

template< class... >
struct always_void { typedef void type; };

struct enabler {};

template< class... >
struct always_enabler { typedef enabler type; };

} } }

#endif // BOOST_GENERIC_DETAIL_ALWAYS_VOID_HPP
