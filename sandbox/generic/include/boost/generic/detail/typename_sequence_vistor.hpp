/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_TYPENAME_SEQUENCE_VISTOR_HPP
#define BOOST_GENERIC_DETAIL_TYPENAME_SEQUENCE_VISTOR_HPP

#define BOOST_GENERIC_DETAIL_TYPENAME_SEQUENCEaxiom( ... )

#define BOOST_GENERIC_DETAIL_TYPENAME_SEQUENCErequires( ... )

#define BOOST_GENERIC_DETAIL_TYPENAME_SEQUENCEtypename( i, d, name, default_ ) \
((i)(name))

#define BOOST_GENERIC_DETAIL_TYPENAME_SEQUENCEconstrained_typename( i, d       \
                                                                  , constraint \
                                                                  , name       \
                                                                  , default_   \
                                                                  )            \
((i)(name))

// ToDo: Define
#define BOOST_GENERIC_DETAIL_TYPENAME_SEQUENCEmember_typename( i, d, this_type \
                                                             , name            \
                                                             , default_        \
                                                             )


// ToDo: Define
#define BOOST_GENERIC_DETAIL_TYPENAME_SEQUENCEconstrained_member_typename(\
                                                                     i, d      \
                                                                   , constraint\
                                                                   , this_type \
                                                                   , name      \
                                                                   , default_  \
                                                                   )

#define BOOST_GENERIC_DETAIL_TYPENAME_SEQUENCEfunction( ... )

#define BOOST_GENERIC_DETAIL_TYPENAME_SEQUENCEmember_function( ... )

#define BOOST_GENERIC_DETAIL_TYPENAME_SEQUENCEstatic_member_function(...)

#define BOOST_GENERIC_DETAIL_TYPENAME_SEQUENCEprefix_unary_operator( ... )

#define BOOST_GENERIC_DETAIL_TYPENAME_SEQUENCEpostfix_unary_operator(...)

#define BOOST_GENERIC_DETAIL_TYPENAME_SEQUENCEbinary_operator( ... )

#define BOOST_GENERIC_DETAIL_TYPENAME_SEQUENCEcall_operator( ... )

#define BOOST_GENERIC_DETAIL_TYPENAME_SEQUENCEcomma_operator( ... )

#define BOOST_GENERIC_DETAIL_TYPENAME_SEQUENCEarrow_operator( ... )

#define BOOST_GENERIC_DETAIL_TYPENAME_SEQUENCEsubscript_operator( ... )

#define BOOST_GENERIC_DETAIL_TYPENAME_SEQUENCEassign_operator( ... )

#define BOOST_GENERIC_DETAIL_TYPENAME_SEQUENCEallocation_operator( ... )

#define BOOST_GENERIC_DETAIL_TYPENAME_SEQUENCEdeallocation_operator(...)

#define BOOST_GENERIC_DETAIL_TYPENAME_SEQUENCEconstructor( ... )

#define BOOST_GENERIC_DETAIL_TYPENAME_SEQUENCEexplicit_constructor( ... )

#define BOOST_GENERIC_DETAIL_TYPENAME_SEQUENCEdestructor( ... )

#define BOOST_GENERIC_DETAIL_TYPENAME_SEQUENCEconversion( ... )

#define BOOST_GENERIC_DETAIL_TYPENAME_SEQUENCEexplicit_conversion( ... )

#endif // BOOST_GENERIC_DETAIL_TYPENAME_SEQUENCE_VISTOR_HPP
