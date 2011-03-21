#if !defined(TTI_TEMPLATE_GEN_HPP)
#define TTI_TEMPLATE_GEN_HPP

#include <boost/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include "trait_gen.hpp"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/// Generates the macro metafunction name for BOOST_TTI_HAS_TEMPLATE.
/**
    name  = the name of the class template.

    returns = the generated macro metafunction name.
*/
#define BOOST_TTI_HAS_TEMPLATE_GEN_BASE(name) \
  BOOST_PP_CAT(has_template_,name) \
/**/

/// Generates the macro metafunction name for BOOST_TTI_MTFC_HAS_TEMPLATE.
/**
    name  = the name of the class template.

    returns = the generated macro metafunction name.
*/
#define BOOST_TTI_MTFC_HAS_TEMPLATE_GEN_BASE(name) \
  BOOST_PP_CAT(mtfc_has_template_,name) \
/**/

/// Generates the macro metafunction name within the Boost TTI namespace for BOOST_TTI_HAS_TEMPLATE.
/**
    name  = the name of the class template.

    returns = the generated macro metafunction name.
*/
#define BOOST_TTI_HAS_TEMPLATE_GEN(name) \
  BOOST_TTI_NAMESPACE::BOOST_TTI_HAS_TEMPLATE_GEN_BASE(name) \
/**/

/// Generates the macro metafunction name within the Boost TTI namespace for BOOST_TTI_MTFC_HAS_TEMPLATE.
/**
    name  = the name of the class template.

    returns = the generated macro metafunction name.
*/
#define BOOST_TTI_MTFC_HAS_TEMPLATE_GEN(name) \
  BOOST_TTI_NAMESPACE::BOOST_TTI_MTFC_HAS_TEMPLATE_GEN_BASE(name) \
/**/

#endif // TTI_TEMPLATE_GEN_HPP
