/**
 * \file boost/mirror/meta_mem_functions.hpp
 * Meta data concerning class' member functions
 *
 *  Copyright 2008 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_MIRROR_META_MEM_FUNCTIONS_HPP
#define BOOST_MIRROR_META_MEM_FUNCTIONS_HPP

#include <boost/mirror/meta_constructors.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/mpl/eval_if.hpp>

namespace boost {
namespace mirror {

/** Forward declaration of the meta-constructors base template
 */
template <class Class /*, class VariantTag*/ >
struct meta_mem_functions_base;

/** Begins the registering of template class' member_functions
 */
#define BOOST_MIRROR_REG_TEMPLATE_MEM_FUNCTIONS_BEGIN(TEMPLATE, TEMPL_ARG_COUNT)\
BOOST_MIRROR_REG_TEMPLATE_META_FUNCTIONS_BEGIN( \
        TEMPLATE, \
        TEMPL_ARG_COUNT, \
        meta_mem_functions_base \
)

/** Begins the registering of class' member functions
 */
#define BOOST_MIRROR_REG_MEM_FUNCTIONS_BEGIN(CLASS) \
BOOST_MIRROR_REG_META_FUNCTIONS_BEGIN(CLASS, meta_mem_functions_base)


/** Ends the registering of (template) class' member functions
 */
#define BOOST_MIRROR_REG_MEM_FUNCTIONS_END \
        param_type_lists; \
};

/** Registers a member function without parameters
 */
#define BOOST_MIRROR_REG_PARAMLESS_MEM_FUNCTION( \
	FUNC_INDEX, \
	RET_VAL, \
	FUNC_NAME \
) \
        param_type_lists_ ## FUNC_INDEX ; \
	static RET_VAL get_result_of(mpl::int_< FUNC_INDEX >); \
        BOOST_MIRROR_REG_META_FUNCTION_DEFINE_EMPTY_PARAM_TYPELIST(FUNC_INDEX)\
        BOOST_MIRROR_REG_META_FUNCTION_PUSH_BACK_PARAM_TYPES(\
                FUNC_INDEX, \
                BOOST_PP_EMPTY()\
        )

/** Implements the get_function_name helper member function
 *  for the meta-member-functions-base class
 */
#define BOOST_MIRROR_REG_MEM_FN_IMPL_GET_FUNCTION_NAME(R, PARAMS, I, CHAR_T)\
        inline static const ::std::basic_string<CHAR_T>& \
        get_function_name( \
                mpl::false_, \
                const ::std::char_traits<CHAR_T>& traits, \
                mpl::int_< BOOST_PP_ARRAY_ELEM(0, PARAMS) > \
        ) \
        { \
		static ::std::basic_string<CHAR_T> result( \
			BOOST_CTS_STRINGIZE_CHAR_T( \
				CHAR_T, \
				BOOST_PP_ARRAY_ELEM(1, PARAMS) \
			) \
		); \
		return result; \
        }

/** This macro does the registering of the member function
 *  name for all supported character types 
 */
#define BOOST_MIRROR_REG_META_FUNCTION_NAME( \
	FUNC_INDEX, \
	FUNC_NAME \
) \
	BOOST_CTS_FOR_EACH_CHAR_T_2( \
		BOOST_MIRROR_REG_MEM_FN_IMPL_GET_FUNCTION_NAME, \
		(2, (FUNC_INDEX, FUNC_NAME)) \
	)


/** registers a single function with parameters
 */
#define BOOST_MIRROR_DO_REG_CLASS_OR_TEMPL_MEM_FUNCTION(\
        FUNC_INDEX, \
	RET_VAL, \
	FUNC_NAME, \
        PARAM_SEQ, \
        TYPENAME_KW\
) \
        param_type_lists_ ## FUNC_INDEX ; \
	static RET_VAL get_result_of(mpl::int_< FUNC_INDEX >); \
        BOOST_MIRROR_REG_META_FUNCTION_DEFINE_PARAM_TYPELIST( \
                FUNC_INDEX, \
                PARAM_SEQ \
        ) \
	BOOST_MIRROR_REG_META_FUNCTION_NAME(FUNC_INDEX, FUNC_NAME) \
        BOOST_MIRROR_REG_META_FUNCTION_PARAM_NAMES( \
                FUNC_INDEX, \
                PARAM_SEQ \
        ) \
        BOOST_MIRROR_REG_META_FUNCTION_PUSH_BACK_PARAM_TYPES( \
                FUNC_INDEX, \
                TYPENAME_KW \
        )


/** expands into the paramless function registering macro
 */
#define BOOST_MIRROR_REG_CLASS_OR_TEMPL_MEM_FUNCTION_1( \
        FUNC_INDEX, \
	RET_VAL, \
	FUNC_NAME, \
        PARAM_SEQ, \
        TYPENAME_KW \
) BOOST_MIRROR_REG_PARAMLESS_MEM_FUNCTION(FUNC_INDEX, RET_VAL, FUNC_NAME)

/** expands into the member function registering macro
 */
#define BOOST_MIRROR_REG_CLASS_OR_TEMPL_MEM_FUNCTION_0( \
        FUNC_INDEX, \
	RET_VAL, \
	FUNC_NAME, \
        PARAM_SEQ, \
        TYPENAME_KW \
) BOOST_MIRROR_DO_REG_CLASS_OR_TEMPL_MEM_FUNCTION( \
        FUNC_INDEX, \
	RET_VAL, \
	FUNC_NAME, \
        PARAM_SEQ, \
        TYPENAME_KW \
)

#define BOOST_MIRROR_REG_CLASS_OR_TEMPL_MEM_FUNCTION( \
        FUNC_INDEX, \
	RET_VAL, \
	FUNC_NAME, \
        PARAM_SEQ, \
        TYPENAME_KW \
) BOOST_PP_CAT( \
        BOOST_MIRROR_REG_CLASS_OR_TEMPL_MEM_FUNCTION_, \
        BOOST_MIRROR_IS_VOID_FN_ARG_LIST(PARAM_SEQ) \
) (FUNC_INDEX, RET_VAL, FUNC_NAME, PARAM_SEQ, TYPENAME_KW)


/** Registers a member function of a non-template class
 */
#define BOOST_MIRROR_REG_MEM_FUNCTION( \
	FUNC_INDEX, \
	RET_VAL, \
	FUNC_NAME, \
	PARAM_SEQ \
) BOOST_MIRROR_REG_CLASS_OR_TEMPL_MEM_FUNCTION( \
	FUNC_INDEX, \
	RET_VAL, \
	FUNC_NAME, \
	PARAM_SEQ, \
	BOOST_PP_EMPTY() \
)

/** Registers a member function of a template class
 */
#define BOOST_MIRROR_REG_TEMPLATE_MEM_FUNCTION( \
	FUNC_INDEX, \
	RET_VAL, \
	FUNC_NAME, \
	PARAM_SEQ \
) BOOST_MIRROR_REG_CLASS_OR_TEMPL_MEM_FUNCTION( \
	FUNC_INDEX, \
	RET_VAL, \
	FUNC_NAME, \
	PARAM_SEQ, \
	typename \
)


/** Template providing meta-data about the member functions
 *  (methods) of the Class.
 */
template <class Class /*, class VariantTag*/ >
struct meta_member_functions : public meta_mem_functions_base<Class>
{
private:
	// internal only
	typedef meta_mem_functions_base<Class> base_meta_data;
public:
	template <class FunctionIndex>
	struct function
	 : detail::meta_function<meta_member_functions, FunctionIndex>
	{
	private:
		template <typename T>
		static mpl::true_ returns_something(T(*)(FunctionIndex));
		static mpl::false_ returns_something(void(*)(FunctionIndex));

		typedef BOOST_TYPEOF(
			returns_something(&base_meta_data::get_result_of)
		) non_void_rv;

		template <typename Idx>
		struct reflected_result
		{
			typedef BOOST_MIRRORED_CLASS(
                        	BOOST_TYPEOF(
					base_meta_data::get_result_of(
						Idx()
					)
				)
                	) type;
		};

		template <typename T>
		struct reflected_type
		{
			typedef BOOST_MIRRORED_CLASS(T) type;
		};
		
	public:
		// meta-class reflecting the result type of this function
		typedef typename mpl::eval_if<
			non_void_rv, 
			reflected_result<FunctionIndex>, 
			reflected_type<void>
		>::type result_type;
	};
};

} // namespace mirror
} // namespace boost

#endif //include guard

