
#ifndef BOOST_CLOSURE_DETAIL_PP_LINE_COUNTER_HPP_
#define BOOST_CLOSURE_DETAIL_PP_LINE_COUNTER_HPP_

#include <boost/config.hpp>

// PUBLIC //

// MSVC has problems expanding __LINE__ so use (the non standard) __COUNTER__.
#ifdef BOOST_MSVC
#   define BOOST_CLOSURE_DETAIL_PP_LINE_COUNTER __COUNTER__
#else
#   define BOOST_CLOSURE_DETAIL_PP_LINE_COUNTER __LINE__
#endif

#endif // #include guard

