#ifndef BOOST_GENERIC_DETAIL_STARTS_EMPTY_OR_PARENTHESIZED_HPP
#define BOOST_GENERIC_DETAIL_STARTS_EMPTY_OR_PARENTHESIZED_HPP

#include <boost/generic/detail/is_empty.hpp>
#include <boost/generic/detail/is_parenthesized.hpp>
#include <boost/preprocessor/logical/bitor.hpp>

#define BOOST_GENERIC_DETAIL_STARTS_EMPTY_OR_PARENTHESIZED( ... )              \
BOOST_PP_BITOR( BOOST_GENERIC_DETAIL_STARTS_EMPTY( __VA_ARGS__ )               \
              , BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED( __VA_ARGS__ )       \
              )

#endif // BOOST_GENERIC_DETAIL_STARTS_EMPTY_OR_PARENTHESIZED_HPP
