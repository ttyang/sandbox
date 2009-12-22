$TEMPLATE[lapack.hpp]
//
// Copyright (c) 2003--2009
// Toon Knapen, Karl Meerbergen, Kresimir Fresl,
// Thomas Klimpel and Rutger ter Borg
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// THIS FILE IS AUTOMATICALLY GENERATED
// PLEASE DO NOT EDIT!
//

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_$DIRNAME_$GROUPNAME_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_$DIRNAME_$GROUPNAME_HPP

$INCLUDES

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//
// The detail namespace contains value-type-overloaded functions that
// dispatch to the appropriate back-end LAPACK-routine.
//
namespace detail {

$OVERLOADS} // namespace detail

$LEVEL1
$LEVEL2
} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
$TEMPLATE[lapack_overloads]
//
// Overloaded function for the $SPECIALIZATION value-type.
//
inline void $groupname( $LEVEL0 ) {
    LAPACK_$SUBROUTINE( $CALL_BLAS_HEADER );
}

$TEMPLATE[lapack_include_hierarchy]
//
// Copyright (c) 2003--2009
// Toon Knapen, Karl Meerbergen, Kresimir Fresl,
// Thomas Klimpel and Rutger ter Borg
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// THIS FILE IS AUTOMATICALLY GENERATED
// PLEASE DO NOT EDIT!
//

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_$LEVEL_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_$LEVEL_HPP

$CONTENT
#endif
$TEMPLATE[level1_pre_header]
//
// Value-type based template class. Use this class if you need a type
// for dispatching to $groupname.
//
template< typename Value, typename Enable = void >
struct $groupname_impl{};

$TEMPLATE[level1_header1]
//
// Value-type based template class. Use this class if you need a type
// for dispatching to $groupname.
//
template< typename Value >
struct $groupname_impl {

$TEMPLATE[level1_header2]
//
// This implementation is enabled if Value is a $SPECIALIZATION type.
//
template< typename Value >
struct $groupname_impl< Value, typename boost::enable_if< is_$SPECIALIZATION< Value > >::type > {

$TEMPLATE[level1_workspace]
    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

$INCLUDE_TEMPLATES
    // user-defined workspace specialization
    template< $TYPES, $WORKSPACE_TYPENAMES >
    static void invoke( $LEVEL1, detail::workspace$WORKSPACE_SIZE< $WORKSPACE_TYPES > work ) {
        $STATIC_ASSERTS
        $INIT_USER_DEFINED_VARIABLES
        $ASSERTS
        detail::$groupname( $CALL_LEVEL0 );
    }

    // minimal workspace specialization
    template< $TYPES >
    static void invoke( $LEVEL1, minimal_workspace work ) {
        $INIT_USER_DEFINED_VARIABLES
$SETUP_MIN_WORKARRAYS_POST
        invoke( $CALL_LEVEL1, workspace( $TMP_WORKARRAYS ) );
    }

    // optimal workspace specialization
    template< $TYPES >
    static void invoke( $LEVEL1, optimal_workspace work ) {
$OPT_WORKSPACE_FUNC
    }

$MIN_SIZE_FUNCS
};

$TEMPLATE[level1_opt_workspace]
        $INIT_USER_DEFINED_OPT_VARIABLES
        $SETUP_OPT_WORKARRAYS_PRE
        detail::$groupname( $WORKSPACE_QUERY );
        $SETUP_OPT_WORKARRAYS_POST
        invoke( $CALL_LEVEL1, workspace( $TMP_WORKARRAYS ) );
$TEMPLATE[level1_opt_workspace_is_min]
        invoke( $CALL_LEVEL1, minimal_workspace() );
$TEMPLATE[level2_workspace]
//
// Overloaded function for $groupname
// * User-defined workspace
//
template< $TYPES, typename Workspace >
inline integer_t $groupname( $LEVEL2, Workspace work ) {
    integer_t info(0);
    $groupname_impl< typename value< $FIRST_TYPENAME >::type >::invoke( $CALL_LEVEL1, work );
    return info;
}

//
// Overloaded function for $groupname
// * Default workspace-type (optimal)
//
template< $TYPES >
inline integer_t $groupname( $LEVEL2 ) {
    integer_t info(0);
    $groupname_impl< typename value< $FIRST_TYPENAME >::type >::invoke( $CALL_LEVEL1, optimal_workspace() );
    return info;
}
$TEMPLATE[setup_min_workspace]
        traits::detail::array< $WORKSPACE_TYPE > tmp_$NAME( min_size_$NAME( $CALL_MIN_SIZE ) );
$TEMPLATE[setup_opt_workspace]
        traits::detail::array< $WORKSPACE_TYPE > tmp_$NAME( $TMP_SIZE );
$TEMPLATE[min_size_func]
    static integer_t min_size_$NAME( $ARGUMENTS ) {
        $MIN_SIZE
    }

$TEMPLATE[level1_noworkspace]
    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

$INCLUDE_TEMPLATES
    // templated specialization
    template< $TYPES >
    static void invoke( $LEVEL1 ) {
        $STATIC_ASSERTS
        $ASSERTS
        detail::$groupname( $CALL_LEVEL0 );
    }
};

$TEMPLATE[level2_noworkspace]
//
// Overloaded function for $groupname
//
template< $TYPES >
inline integer_t $groupname( $LEVEL2 ) {
    integer_t info(0);
    $groupname_impl< typename value< $FIRST_TYPENAME >::type >::invoke( $CALL_LEVEL1 );
    return info;
}
$TEMPLATE[end]
