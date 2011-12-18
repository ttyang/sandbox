
#ifndef BOOST_CLOSURE_AUX_CLOSURE_TYPEOF_HPP_
#define BOOST_CLOSURE_AUX_CLOSURE_TYPEOF_HPP_

#include <boost/closure/aux_/symbol.hpp>

// PUBLIC //

// Actual type-name for specified symbol name.
#define BOOST_CLOSURE_AUX_CLOSURE_TYPEOF_TYPE(name) \
    /* cannot prefix in front of name because it could start with non */ \
    /* alphanumeric symbols (e.g., & for binding by reference) */ \
    BOOST_CLOSURE_AUX_SYMBOL_POSTFIX( (name)(typeof_type) )

#endif // #include guard

