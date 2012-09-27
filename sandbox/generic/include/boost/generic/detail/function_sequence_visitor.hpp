#ifndef BOOST_GENERIC_DETAIL_FUNCTION_SEQUENCE_VISITOR_HPP
#define BOOST_GENERIC_DETAIL_FUNCTION_SEQUENCE_VISITOR_HPP

// Note: visitation generates a sequence of function ids for typename deduction

#define BOOST_GENERIC_DETAIL_FUNCTION_SEQUENCEaxiom( ... )

#define BOOST_GENERIC_DETAIL_FUNCTION_SEQUENCErequires( ... )

#define BOOST_GENERIC_DETAIL_FUNCTION_SEQUENCEtypename( ... )

#define BOOST_GENERIC_DETAIL_FUNCTION_SEQUENCEconstrained_typename( ... )

#define BOOST_GENERIC_DETAIL_FUNCTION_SEQUENCEmember_typename( ... )

#define BOOST_GENERIC_DETAIL_FUNCTION_SEQUENCEconstrained_member_typename( ... )

#define BOOST_GENERIC_DETAIL_FUNCTION_SEQUENCEfunction( i, ... ) (i)

#define BOOST_GENERIC_DETAIL_FUNCTION_SEQUENCEmember_function( i, ... ) (i)

#define BOOST_GENERIC_DETAIL_FUNCTION_SEQUENCEstatic_member_function(i,...) (i)

#define BOOST_GENERIC_DETAIL_FUNCTION_SEQUENCEprefix_unary_operator( i,... ) (i)

#define BOOST_GENERIC_DETAIL_FUNCTION_SEQUENCEpostfix_unary_operator(i,...) (i)

#define BOOST_GENERIC_DETAIL_FUNCTION_SEQUENCEbinary_operator( i, ... ) (i)

#define BOOST_GENERIC_DETAIL_FUNCTION_SEQUENCEcall_operator( i, ... ) (i)

#define BOOST_GENERIC_DETAIL_FUNCTION_SEQUENCEcomma_operator( i, ... ) (i)

#define BOOST_GENERIC_DETAIL_FUNCTION_SEQUENCEarrow_operator( i, ... ) (i)

#define BOOST_GENERIC_DETAIL_FUNCTION_SEQUENCEsubscript_operator( i, ... ) (i)

#define BOOST_GENERIC_DETAIL_FUNCTION_SEQUENCEassign_operator( i, ... ) (i)

#define BOOST_GENERIC_DETAIL_FUNCTION_SEQUENCEallocation_operator( i, ... )

#define BOOST_GENERIC_DETAIL_FUNCTION_SEQUENCEdeallocation_operator(i,...)

#define BOOST_GENERIC_DETAIL_FUNCTION_SEQUENCEconstructor( i, ... )

#define BOOST_GENERIC_DETAIL_FUNCTION_SEQUENCEexplicit_constructor( i, ... )

#define BOOST_GENERIC_DETAIL_FUNCTION_SEQUENCEdestructor( i, ... )

#define BOOST_GENERIC_DETAIL_FUNCTION_SEQUENCEconversion( i, ... )

#define BOOST_GENERIC_DETAIL_FUNCTION_SEQUENCEexplicit_conversion( i, ... )

#endif // BOOST_GENERIC_DETAIL_FUNCTION_SEQUENCE_VISITOR_HPP
