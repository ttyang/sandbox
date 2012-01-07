
#ifndef BOOST_CLOSURE_AUX_NOBIND_HPP_
#define BOOST_CLOSURE_AUX_NOBIND_HPP_

#include <boost/closure/aux_/config.hpp>

// NOTE: The current implementation needs no-bind placeholders only when
// local types cannot be passed as template parameters.
#if !BOOST_CLOSURE_AUX_CONFIG_LOCAL_TYPES_AS_TEMPLATE_PARAMS_01

namespace boost { namespace closure { namespace aux {

typedef int nobind_t;

nobind_t nobind;

}}} // namespace

#endif

#endif // #include guard

