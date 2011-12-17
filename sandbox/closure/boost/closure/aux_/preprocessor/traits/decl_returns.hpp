
#ifndef BOOST_CLOSURE_AUX_PP_DECL_TRAITS_RETURNS_HPP_
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_RETURNS_HPP_

#include <boost/closure/aux_/preprocessor/traits/decl_/index.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// PUBLIC //

// Expand: pp-list of result types (size <= 1 after validation).
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_RETURNS(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_INDEX_RETURNS, decl_traits)

#endif // #include guard

