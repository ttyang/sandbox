/*=============================================================================
    Copyright (c) 2007-2012 Marco Cecchetti

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/


#ifndef _BOOST_DETAIL_OVERLOAD_MACRO_UNDEF_HPP_
#define _BOOST_DETAIL_OVERLOAD_MACRO_UNDEF_HPP_


// cleanup macro defs

#undef BOOST_OVERLOAD_FUNCTOR_ADAPTOR
#undef BOOST_OVERLOAD_MAKE_NTH_MAKE_OVERLOAD
#undef BOOST_OVERLOAD_CTOR
#undef BOOST_OVERLOAD_SET
#undef BOOST_OVERLOAD_SET_IMPL
#undef BOOST_OVERLOAD_ENUM_SHIFTED_PARAMS_WITH_A_DEFAULT
#undef BOOST_OVERLOAD_MAKE_NTH_PARAM_WITH_A_DEFAULT
#undef BOOST_OVERLOAD_ENUM_NUM_CALLS_TPL
#undef BOOST_OVERLOAD_MAKE_NTH_NUM_CALL
#undef BOOST_OVERLOAD_ENUM_CALLS_TPL
#undef BOOST_OVERLOAD_MAKE_NTH_CALL
#undef BOOST_OVERLOAD_WRAPPED_FUNC

// macro workarounds for MSVC < 8.0 tested on MSVC 7.1
#undef BOOST_OVERLOAD_FUNC_CALL_OPERATORS
#undef BOOST_OVERLOAD_FUNC_CALL_OPERATOR_M_N
#undef BOOST_OVERLOAD_FC_OP_PARAM
#undef BOOST_OVERLOAD_REAL_OR_DUMMY_SIG_M
#undef BOOST_OVERLOAD_REAL_OR_DUMMY_SIG_M_N

// so we can include the header responsible of defining macro once more
#undef _BOOST_OVERLOAD_DETAIL_MACRO_DEF_HPP_

#endif // _BOOST_DETAIL_OVERLOAD_MACRO_UNDEF_HPP_

