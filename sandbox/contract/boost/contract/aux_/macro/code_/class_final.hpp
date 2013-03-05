
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_AUX_CODE_CLASS_FINAL_HPP_
#define BOOST_CONTRACT_AUX_CODE_CLASS_FINAL_HPP_

#include <boost/contract/aux_/has_xxx_member_function.hpp>
#include <boost/contract/aux_/mpl_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>

// PRIVATE //

#define BOOST_CONTRACT_AUX_CODE_CLASS_FINAL_TAG_FUNC_ \
    BOOST_CONTRACT_AUX_SYMBOL( (final_class_tag) ) /* no class name, id, etc */

#define BOOST_CONTRACT_AUX_CODE_CLASS_FINAL_TAG_FUNC_SIGNATURE_(name) \
    /* NOTE: final classes decl this member func tag then derived classes */ \
    /* statically assert (using introspection) that none of their base */ \
    /* classes have the final tag member func (i.e., they were decl final) */ \
    void name ( )

#define BOOST_CONTRACT_AUX_CODE_CLASS_FINAL_TAG_DECL_ \
    public: /* must be public to be accessed from introspection metafunc */ \
    BOOST_CONTRACT_AUX_CODE_CLASS_FINAL_TAG_FUNC_SIGNATURE_( \
            BOOST_CONTRACT_AUX_CODE_CLASS_FINAL_TAG_FUNC_) \
    ; /* no tag func definition needed for SFINAE so `;` */

#define BOOST_CONTRACT_AUX_CODE_CLASS_FINAL_TAG_(c) \
    BOOST_PP_EXPR_IIF(BOOST_PP_COMPL(BOOST_PP_IS_EMPTY( \
            BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_FINAL(c))), \
        BOOST_CONTRACT_AUX_CODE_CLASS_FINAL_TAG_DECL_ \
    )

#define BOOST_CONTRACT_AUX_CODE_CLASS_FINAL_CHECK_BASE_(r, id_tpl_c, i, b) \
    BOOST_CONTRACT_AUX_MPL_ASSERT_MSG( \
        /* use introspection metafunc has_... decl below in this file */ \
          (!::contract::aux::has_final_class_tag< \
            BOOST_CONTRACT_AUX_CODE_CLASS_FINAL_TAG_FUNC_SIGNATURE_( \
                ( \
                    /* no outer typename here because constructor */ \
                    /* requires no typename (known to be a type), IDENTITY */ \
                    /* with add/remove reference to handle unwrapped commas */ \
                    ::boost::remove_reference< \
                        BOOST_CONTRACT_AUX_CODE_CLASS_TYPENAME( \
                                BOOST_PP_TUPLE_ELEM(3, 1, id_tpl_c), \
                                BOOST_PP_TUPLE_ELEM(3, 2, id_tpl_c)) \
                        BOOST_IDENTITY_TYPE(( \
                            BOOST_CONTRACT_AUX_CODE_CLASS_TYPENAME( \
                                    BOOST_PP_TUPLE_ELEM(3, 1, id_tpl_c), \
                                    BOOST_PP_TUPLE_ELEM(3, 2, id_tpl_c)) \
                            ::boost::add_reference< \
                                BOOST_PP_ARRAY_ENUM( \
  BOOST_CONTRACT_DETAIL_PP_BASE_TRAITS_TYPE( \
                                        b))\
                            >::type \
                        )) \
                    >::type \
                    ::* \
                ) \
            ) \
          >::value) \
        , BOOST_PP_SEQ_CAT( (ERROR_cannot_extend_final_base_class_number_) \
                (BOOST_PP_INC(i))(_at_line_) \
                (BOOST_PP_TUPLE_ELEM(3, 0, id_tpl_c)) ) \
        , (types< \
            /* keep eventual typename prefix here and no need for IDENTITY */ \
            BOOST_PP_ARRAY_ENUM(BOOST_CONTRACT_DETAIL_PP_BASE_TRAITS_TYPE(b)) \
          >) \
    ); /* MPL assert requires trailing `;` */

#define BOOST_CONTRACT_AUX_CODE_CLASS_FINAL_CHECK_(id, tpl, c) \
    BOOST_PP_LIST_FOR_EACH_I(BOOST_CONTRACT_AUX_CODE_CLASS_FINAL_CHECK_BASE_, \
            (id, tpl, c), BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_BASES(c))

// PRIVATE //

#define BOOST_CONTRACT_AUX_CODE_CLASS_FINAL(id, tpl, c) \
    BOOST_CONTRACT_AUX_CODE_CLASS_FINAL_TAG_(c) \
    BOOST_CONTRACT_AUX_CODE_CLASS_FINAL_CHECK_(id, tpl, c)

namespace boost { namespace contract { namespace aux {

BOOST_CONTRACT_AUX_HAS_XXX_MEMBER_FUNCTION(has_final_class_tag,
        BOOST_CONTRACT_AUX_CODE_CLASS_FINAL_TAG_FUNC_)

} } } // namespace

#endif // #include guard

