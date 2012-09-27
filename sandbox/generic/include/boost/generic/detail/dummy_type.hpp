#ifndef BOOST_GENERIC_DETAIL_DUMMY_TYPE_HPP
#define BOOST_GENERIC_DETAIL_DUMMY_TYPE_HPP

#ifndef BOOST_GENERIC_GENERATE_PREPROCESSED_HEADERS

#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/add_rvalue_reference.hpp>
#include <boost/type_traits/is_void.hpp>
#include <utility>

namespace boost { namespace generic { namespace detail {

struct dummy_type {};

template< class T >
struct void_safe_declval_result_type
{
  typedef typename add_rvalue_reference
          < typename mpl::if_< is_void< T >, dummy_type, T >::type >::type
          type;
};

template< class T >
typename void_safe_declval_result_type< T >::type void_safe_declval();

template< unsigned UniqueId >
struct dummy_type_ {};

template< class Type >
struct is_dummy_type : mpl::false_ {};

template<>
struct is_dummy_type< dummy_type > : mpl::true_ {};

template< unsigned ID >
struct is_dummy_type< dummy_type_< ID > > : mpl::true_ {};

template< class Type >
struct is_not_dummy_type : mpl::not_< is_dummy_type< Type > > {};

} } }

#endif

#endif // BOOST_GENERIC_DETAIL_DUMMY_TYPE_HPP
