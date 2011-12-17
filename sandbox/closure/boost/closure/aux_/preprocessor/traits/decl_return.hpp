
#ifndef BOOST_CLOSURE_AUX_PP_DECL_TRAITS_RETURN_HPP_
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_RETURN_HPP_

#include <boost/closure/aux_/preprocessor/traits/decl_/index.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// PUBLIC //

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_RETURNS(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_INDEX_RETURNS, decl_traits)

#endif // #include guard

