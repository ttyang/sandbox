
#ifndef BOOST_MPL_AUX_TEMPLATE_ARITYV_HPP_INCLUDED
#define BOOST_MPL_AUX_TEMPLATE_ARITYV_HPP_INCLUDED

#include <boost/mpl/aux_/template_arity.hpp>

namespace boost { namespace mpl { namespace aux {

template
< template<typename...>class F
, typename... T
> 
struct template_arity
< F<T...>
>
: int_ <sizeof...(T)>
{
};

}}}

#endif // BOOST_MPL_AUX_TEMPLATE_ARITYV_HPP_INCLUDED