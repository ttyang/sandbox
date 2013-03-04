
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BOOST_CONTRACT_AUX_CODE_CLASS_CONCEPT_HPP_
#define BOOST_CONTRACT_AUX_CODE_CLASS_CONCEPT_HPP_

#include <boost/contract/aux_/concept_assert.hpp>

// PRIVATE //

#define BOOST_CONTRACT_AUX_CODE_CLASS_CONCEPT_ASSERT_(r, id, i, concept) \
    /* can expand multiple of this macros on same line because of id */ \
    BOOST_CONTRACT_AUX_CONCEPT_ASSERT( (BOOST_PP_ARRAY_ENUM(concept)), \
        /* pp-cat infix because Boost.ConceptCheck will cat it again */ \
        BOOST_CONTRACT_AUX_SYMBOL( (concept_check)(id)(i) ) \
    ) ; /* `;` ends concept assertion */

// PUBLIC //

#define BOOST_CONTRACT_AUX_CODE_CLASS_CONCEPT_TYPE(id, c) \
    BOOST_CONTRACT_AUX_SYMBOL( (BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_NAME(c)) \
            (check_class_concepts) (id) )

#define BOOST_CONTRACT_AUX_CODE_CLASS_CONCEPT(id, tpl, c) \
    BOOST_CONTRACT_AUX_CODE_TEMPLATE_DECL( \
            BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_IS_TEMPLATE(c), \
            BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                    BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_PARAMS(c))) \
    struct BOOST_CONTRACT_AUX_CODE_CLASS_CONCEPT_TYPE(id, c) \
    { \
        BOOST_PP_LIST_FOR_EACH_I(BOOST_CONTRACT_AUX_CODE_CLASS_CONCEPT_ASSERT_,\
                id, BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_CONCEPTS(c)) \
    };

#define BOOST_CONTRACT_AUX_CODE_CLASS_CONCEPT_BASE_SEQ(id, tpl, c) \
    ( /* seq elem */ \
        /* NOTE: inheritance is private because impl detail and it has to */ \
        /* be virtual because otherwise eventual other virtual bases will */ \
        /* be initialized before this one */ \
        private virtual \
        /* IDENTITY_TYPE is needed here because this code passes multiple */ \
        /* tparams separated by unwrapped commas to the enclosing macro */ \
        /* (but no outer typename in base class list) plus add/remove ref */ \
        /* to handle abstract types */ \
        ::boost::remove_reference< \
            BOOST_CONTRACT_AUX_CODE_CLASS_TYPENAME(tpl, c) \
            BOOST_IDENTITY_TYPE(( \
                BOOST_CONTRACT_AUX_CODE_CLASS_TYPENAME(tpl, c) \
                ::boost::add_reference< \
                    BOOST_CONTRACT_AUX_CODE_CLASS_CONCEPT_TYPE(id, c) \
                    BOOST_CONTRACT_AUX_CODE_TEMPLATE_INSTANCE( \
                            BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \  BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_PARAMS( \
                                    c))) \
                >::type \
            )) \
        >::type \
    )

#endif // #include guard

