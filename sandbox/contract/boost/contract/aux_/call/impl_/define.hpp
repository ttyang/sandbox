
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#define BOOST_CONTRACT_comma_arg_param(z, n, unused) \
    , typename SignTraits::BOOST_PP_CAT(arg_type, n) BOOST_PP_CAT(arg, n)

#define BOOST_CONTRACT_arg(z, n, unused) \
    BOOST_PP_CAT(arg, n)

#define BOOST_CONTRACT_comma_arg(z, n, unused) \
    , BOOST_PP_CAT(arg, n)

#define BOOST_CONTRACT_from \
    BOOST_PP_IIF(BOOST_PP_COMPL(BOOST_CONTRACT_AUX_CALL_IS_MEMBER), \
        FROM_FREE_FUNCTION \
    , BOOST_PP_IIF(BOOST_CONTRACT_AUX_CALL_IS_STATIC, \
        FROM_STATIC_MEMBER_FUNCTION \
    , BOOST_PP_IIF(BOOST_CONTRACT_AUX_CALL_IS_DESTRUCTOR, \
        FROM_DESTRUCTOR \
    , BOOST_PP_IIF(BOOST_PP_BITOR(BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY,\
            BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT), \
        FROM_CONSTRUCTOR \
    , \
        FROM_NONSTATIC_MEMBER_FUNCTION \
    ))))

#define BOOST_CONTRACT_func \
    BOOST_PP_IIF(BOOST_PP_COMPL(BOOST_CONTRACT_AUX_CALL_IS_MEMBER), \
        call_free_function \
    , BOOST_PP_IIF(BOOST_CONTRACT_AUX_CALL_IS_STATIC, \
        call_static_member_function \
    , BOOST_PP_IIF(BOOST_CONTRACT_AUX_CALL_IS_DESTRUCTOR, \
        call_destructor \
    , BOOST_PP_IIF(BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY, \
        call_constructor_entry \
    , BOOST_PP_IIF(BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT, \
        call_constructor_exit \
    , \
        call_nonstatic_member_function \
    )))))

#define BOOST_CONTRACT_entry_class_inv_func \
    BOOST_PP_IIF(BOOST_CONTRACT_AUX_CALL_IS_STATIC, \
        (*sub_static_class_inv) \
    , BOOST_PP_IIF(BOOST_CONTRACT_AUX_CALL_IS_DESTRUCTOR, \
        (obj->*this_class_inv) \
    , BOOST_PP_IIF(BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY, \
        (*this_static_class_inv) \
    , \
        (obj->*sub_class_inv) \
    )))

#define BOOST_CONTRACT_exit_class_inv_func \
    BOOST_PP_IIF(BOOST_CONTRACT_AUX_CALL_IS_STATIC, \
        (*sub_static_class_inv) \
    , BOOST_PP_IIF(BOOST_CONTRACT_AUX_CALL_IS_DESTRUCTOR, \
        (*this_static_class_inv) \
    , BOOST_PP_IIF(BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT, \
        (obj->*this_class_inv) \
    , \
        (obj->*sub_class_inv) \
    )))

#define BOOST_CONTRACT_throw_class_inv_func \
    BOOST_PP_IIF(BOOST_CONTRACT_AUX_CALL_IS_STATIC, \
        (*sub_static_class_inv) \
    , BOOST_PP_IIF(BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT, \
        (*this_static_class_inv) \
    , \
        (obj->*sub_class_inv) /* also for throwing destructors */ \
    ))

#define BOOST_CONTRACT_pre_func \
    BOOST_PP_IIF(BOOST_PP_BITAND(BOOST_CONTRACT_AUX_CALL_IS_MEMBER, \
            BOOST_PP_BITAND(BOOST_PP_COMPL(BOOST_CONTRACT_AUX_CALL_IS_STATIC), \
                    BOOST_PP_COMPL( \
                            BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY))), \
        (obj->*sub_pre) \
    , \
        (*this_pre) \
    )

#define BOOST_CONTRACT_oldof_assignment_func \
    BOOST_PP_IIF(BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT, \
        this_post = (*this_cons_oldof) \
    , BOOST_PP_IIF(BOOST_PP_BITAND(BOOST_CONTRACT_AUX_CALL_IS_MEMBER, \
            BOOST_PP_COMPL(BOOST_CONTRACT_AUX_CALL_IS_STATIC)), \
        sub_post = (obj->*sub_oldof) \
    , \
        this_post = (*this_oldof) \
    ))

#define BOOST_CONTRACT_post_func \
    BOOST_PP_IIF(BOOST_PP_BITAND(BOOST_CONTRACT_AUX_CALL_IS_MEMBER, \
            BOOST_PP_BITAND(BOOST_PP_COMPL(BOOST_CONTRACT_AUX_CALL_IS_STATIC), \
                    BOOST_PP_COMPL( \
                            BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT))), \
        subcontract_postcondition<SignTraits> \
    , \
        this_post \
    )

#define BOOST_CONTRACT_body_func \
    BOOST_PP_IIF(BOOST_PP_BITAND(BOOST_CONTRACT_AUX_CALL_IS_MEMBER, \
            BOOST_PP_COMPL(BOOST_CONTRACT_AUX_CALL_IS_STATIC)), \
        (obj->*body) \
    , \
        (*body) \
    )

