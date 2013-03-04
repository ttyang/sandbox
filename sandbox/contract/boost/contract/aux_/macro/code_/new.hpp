
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BOOST_CONTRACT_AUX_CODE_NEW_HPP_
#define BOOST_CONTRACT_AUX_CODE_NEW_HPP_

#include <boost/contract/aux_/mpl_assert.hpp>
#include <boost/contract/aux_/macro/code_/virtual.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>

// PRIVATE //

#define BOOST_CONTRACT_AUX_CODE_NEW_CHECK_BASE_(r, n, id_f) \
    BOOST_CONTRACT_AUX_MPL_ASSERT_MSG( \
        /* base == class && !has_virtual_function_tag<base::func> */ \
          (::boost::mpl::or_< \
              ::boost::is_same< \
                  BOOST_CONTRACT_AUX_CODE_BASE_TYPE(n) \
                , BOOST_CONTRACT_AUX_CODE_CLASS_TYPE \
              > \
            , ::boost::mpl::not_< BOOST_CONTRACT_AUX_CODE_HAS_VIRTUAL( \
                    BOOST_PP_TUPLE_ELEM(2, 0, id_f), BOOST_PP_TUPLE_ELEM(2, 1, \
                            id_f), BOOST_CONTRACT_AUX_CODE_BASE_TYPE(n)) > \
          >::value) \
        , BOOST_PP_SEQ_CAT( \
  (ERROR_matching_virtual_function_already_declared_by_base_class_number_) \
                (BOOST_PP_INC(n))(_at_line_)(BOOST_PP_TUPLE_ELEM(2, 0, id_f))) \
        , (types< BOOST_CONTRACT_AUX_CODE_BASE_TYPE(n) >) \
    ); /* MPL assert requires trailing `;` */

#define BOOST_CONTRACT_AUX_CODE_NEW_CHECK_(id, tpl, k, f) \
    BOOST_PP_REPEAT(BOOST_CONTRACT_CONFIG_INHERITANCE_MAX, \
            BOOST_CONTRACT_AUX_CODE_NEW_CHECK_BASE_, (id, f)) \

// PUBLIC //

#define BOOST_CONTRACT_AUX_CODE_NEW_CHECK(id, tpl, k, f) \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY(BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_NEW( \
            f)),\
        BOOST_PP_TUPLE_EAT(4) \
    , \
        BOOST_CONTRACT_AUX_CODE_NEW_CHECK_ \
    )(id, tpl, k, f)

#endif // #include guard

