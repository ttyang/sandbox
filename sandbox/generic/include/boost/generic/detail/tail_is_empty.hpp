#ifndef BOOST_GENERIC_DETAIL_TAIL_IS_EMPTY_HPP
#define BOOST_GENERIC_DETAIL_TAIL_IS_EMPTY_HPP

#include <boost/generic/detail/is_empty.hpp>
#include <boost/generic/detail/tail_arguments.hpp>

#define BOOST_GENERIC_DETAIL_TAIL_IS_EMPTY( ... )                              \
BOOST_GENERIC_DETAIL_IS_EMPTY                                                  \
( BOOST_GENERIC_DETAIL_TAIL_ARGUMENTS( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_TAIL_IS_EMPTY_AFTER_RESCAN( ... )                 \
BOOST_GENERIC_DETAIL_IS_EMPTY                                                  \
( BOOST_GENERIC_DETAIL_TAIL_ARGUMENTS_AFTER_RESCAN( __VA_ARGS__ ) )

#endif // BOOST_GENERIC_DETAIL_TAIL_IS_EMPTY_HPP
