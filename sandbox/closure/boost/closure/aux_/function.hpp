
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#if !BOOST_PP_IS_ITERATING
#   ifndef BOOST_CLOSURE_AUX_FUNCTION_HPP_
#       define BOOST_CLOSURE_AUX_FUNCTION_HPP_

#       include <boost/closure/aux_/config.hpp>
#       include <boost/closure/aux_/member.hpp>
#       include <boost/call_traits.hpp>
#       include <boost/preprocessor/iteration/iterate.hpp>
#       include <boost/preprocessor/repetition/repeat.hpp>
#       include <boost/preprocessor/repetition/enum.hpp>
#       include <boost/preprocessor/punctuation/comma_if.hpp>
#       include <boost/preprocessor/arithmetic/sub.hpp>
#       include <boost/preprocessor/arithmetic/inc.hpp>
#       include <boost/preprocessor/cat.hpp>

// PRIVATE //

#define BOOST_CLOSURE_AUX_FUNCTION_THIS_FILE_ \
    "boost/closure/aux_/function.hpp"

// PUBLIC //

#define BOOST_CLOSURE_AUX_FUNCTION_INIT_CALL_FUNC \
    BOOST_CLOSURE_AUX_SYMBOL( (init_call) )

#define BOOST_CLOSURE_AUX_arg_type(z, arg_n, unused) \
    BOOST_PP_CAT(A, arg_n)

#define BOOST_CLOSURE_AUX_comma_arg_tparam(z, arg_n, unused) \
    , typename BOOST_CLOSURE_AUX_arg_type(z, arg_n, ~)

#define BOOST_CLOSURE_AUX_arg_param_type(z, arg_n, comma01) \
    BOOST_PP_COMMA_IF(comma01) \
    typename ::boost::call_traits< \
        BOOST_CLOSURE_AUX_arg_type(z, arg_n, ~) \
    >::param_type

#define BOOST_CLOSURE_AUX_arg_name(z, arg_n, comma01) \
    BOOST_PP_COMMA_IF(comma01) \
    BOOST_PP_CAT(a, arg_n)

#define BOOST_CLOSURE_AUX_arg_param_decl(z, arg_n, unused) \
    BOOST_CLOSURE_AUX_arg_param_type(z, arg_n, 0 /* no leading comma */) \
    BOOST_CLOSURE_AUX_arg_name(z, arg_n, 0 /* no leading comma */)

#define BOOST_CLOSURE_AUX_bind_type(z, bind_n, unused) \
    BOOST_PP_CAT(B, bind_n)

#define BOOST_CLOSURE_AUX_comma_bind_type(z, bind_n, unused) \
    , BOOST_CLOSURE_AUX_bind_type(z, bind_n, ~)

#define BOOST_CLOSURE_AUX_comma_bind_ref(z, bind_n, unused) \
    , BOOST_CLOSURE_AUX_bind_type(z, bind_n, ~) &

#define BOOST_CLOSURE_AUX_comma_bind_tparam(z, bind_n, unused) \
    , typename BOOST_CLOSURE_AUX_bind_type(z, bind_n, ~)

#define BOOST_CLOSURE_AUX_bind_name(z, bind_n, unused) \
    BOOST_PP_CAT(b, bind_n)

#define BOOST_CLOSURE_AUX_comma_bind_param_decl(z, bind_n, unused) \
    , \
    BOOST_CLOSURE_AUX_bind_type(z, bind_n, ~) & \
    BOOST_CLOSURE_AUX_bind_name(z, bind_n, ~)
    
#define BOOST_CLOSURE_AUX_bind_member(z, bind_n, unsued) \
    BOOST_PP_CAT(BOOST_CLOSURE_AUX_bind_name(z, bind_n, ~), _)

#define BOOST_CLOSURE_AUX_comma_bind_member_deref(z, bind_n, unsued) \
    , member_deref<BOOST_CLOSURE_AUX_bind_type(z, bind_n, ~)>( \
            BOOST_CLOSURE_AUX_bind_member(z, bind_n, ~))

#define BOOST_CLOSURE_AUX_bind_member_init(z, bind_n, unused) \
    BOOST_CLOSURE_AUX_bind_member(z, bind_n, ~) = member_addr( \
            BOOST_CLOSURE_AUX_bind_name(z, bind_n, ~));

#define BOOST_CLOSURE_AUX_bind_member_decl(z, bind_n, unused) \
    /* must be ptr (not ref) so can use default constr */ \
    typename member_type< BOOST_CLOSURE_AUX_bind_type(z, bind_n, ~) >::pointer \
    BOOST_CLOSURE_AUX_bind_member(z, bind_n, ~) \
    ;

#define BOOST_CLOSURE_AUX_call_ptr(z, n, unused) \
    BOOST_PP_CAT(call_ptr, n)

#define BOOST_CLOSURE_AUX_call_name(z, n, unused) \
    BOOST_PP_CAT(call, n)

#define BOOST_CLOSURE_AUX_call_member(z, n, unused) \
    BOOST_PP_CAT(BOOST_CLOSURE_AUX_call_name(z, n, unused), _)

#define BOOST_CLOSURE_AUX_call_typedef(z, n, arity) \
    typedef R (*BOOST_CLOSURE_AUX_call_ptr(z, n, ~))( \
        object_ptr \
        BOOST_PP_IIF( \
                BOOST_CLOSURE_AUX_CONFIG_LOCAL_TYPES_AS_TEMPLATE_PARAMS_01, \
            BOOST_PP_TUPLE_EAT(3) \
        , \
            BOOST_PP_REPEAT_ ## z \
        )(BOOST_CLOSURE_CONFIG_BIND_MAX, BOOST_CLOSURE_AUX_comma_bind_ref, ~) \
        BOOST_PP_REPEAT_ ## z(BOOST_PP_SUB(arity, n), \
                BOOST_CLOSURE_AUX_arg_param_type, 1 /* leading comma */) \
    );

#define BOOST_CLOSURE_AUX_comma_call_param_decl(z, n, unused) \
    , \
    BOOST_CLOSURE_AUX_call_ptr(z, n, ~) \
    BOOST_CLOSURE_AUX_call_name(z, n, ~)

#define BOOST_CLOSURE_AUX_call_decl(z, n, unused) \
    BOOST_CLOSURE_AUX_call_ptr(z, n, ~) \
    BOOST_CLOSURE_AUX_call_member(z, n, ~);

#define BOOST_CLOSURE_AUX_call_init(z, n, unused) \
    BOOST_CLOSURE_AUX_call_member(z, n, ~) = \
            BOOST_CLOSURE_AUX_call_name(z, n, ~);
                
#define BOOST_CLOSURE_AUX_operator_call(z, defaults_n, arity) \
    /* precondition: object_ && call_function_ */ \
    inline R operator()( \
        BOOST_PP_ENUM_ ## z(BOOST_PP_SUB(arity, defaults_n), \
                BOOST_CLOSURE_AUX_arg_param_decl, ~) \
    ) /* cannot be const (because of binds) */ { \
        /* run-time: do not assert preconditions here for efficiency */ \
        /* run-time: this function call is done via a function pointer */ \
        /* so unfortunately does not allow for compiler inlining */ \
        /* optimizations (an alternative using virtual function was also */ \
        /* investigated but also virtual functions cannot be optimized */ \
        /* plus they require virtual table lookups to the alternative */ \
        /* performed worst) */ \
        return BOOST_CLOSURE_AUX_call_member(z, defaults_n, ~)( \
            object_ \
            BOOST_PP_IIF( \
                    BOOST_CLOSURE_AUX_CONFIG_LOCAL_TYPES_AS_TEMPLATE_PARAMS_01,\
                BOOST_PP_TUPLE_EAT(3) \
            , \
                BOOST_PP_REPEAT_ ## z \
            )(BOOST_CLOSURE_CONFIG_BIND_MAX, \
                    BOOST_CLOSURE_AUX_comma_bind_member_deref, ~) \
            BOOST_PP_REPEAT_ ## z(BOOST_PP_SUB(arity, defaults_n), \
                    BOOST_CLOSURE_AUX_arg_name, 1 /* leading comma */) \
        ); \
    }

namespace boost { namespace closure { namespace aux {

template<
      typename F
    , size_t defaults
#if !BOOST_CLOSURE_AUX_CONFIG_LOCAL_TYPES_AS_TEMPLATE_PARAMS_01
    BOOST_PP_REPEAT(BOOST_CLOSURE_CONFIG_BIND_MAX,
            BOOST_CLOSURE_AUX_comma_bind_tparam, ~)
#endif
>
class function {
    // Empty template cannot be used directly (only via its specializations).
};

// Iterate within namespace.
#       define BOOST_PP_ITERATION_PARAMS_1 \
                (3, (0, BOOST_CLOSURE_CONFIG_FUNCTION_ARITY_MAX, \
                BOOST_CLOSURE_AUX_FUNCTION_THIS_FILE_))
#       include BOOST_PP_ITERATE() // Iterate over function arity.

}}} // namespace boost::loca::aux

/** @todo undef all local macros */
#undef BOOST_CLOSURE_AUX_arg_type
#undef BOOST_CLOSURE_AUX_arg_param_type
#undef BOOST_CLOSURE_AUX_arg_name
#undef BOOST_CLOSURE_AUX_arg_param_decl
#undef BOOST_CLOSURE_AUX_comma_arg_tparam
#undef BOOST_CLOSURE_AUX_call_ptr
#undef BOOST_CLOSURE_AUX_call_name
#undef BOOST_CLOSURE_AUX_call_member
#undef BOOST_CLOSURE_AUX_call_typedef
#undef BOOST_CLOSURE_AUX_call_param
#undef BOOST_CLOSURE_AUX_call_decl
#undef BOOST_CLOSURE_AUX_call_init
#undef BOOST_CLOSURE_AUX_operator_call

#   endif // #include guard

#elif BOOST_PP_ITERATION_DEPTH() == 1
#   define BOOST_CLOSURE_AUX_arity BOOST_PP_FRAME_ITERATION(1)
#   define BOOST_PP_ITERATION_PARAMS_2 \
            (3, (0, BOOST_CLOSURE_AUX_arity, \
            BOOST_CLOSURE_AUX_FUNCTION_THIS_FILE_))
#   include BOOST_PP_ITERATE() // Iterate over default params count.
#   undef BOOST_CLOSURE_AUX_arity

#elif BOOST_PP_ITERATION_DEPTH() == 2
#   define BOOST_CLOSURE_AUX_defaults BOOST_PP_FRAME_ITERATION(2)

// Iterating within namespace `boost::closure::aux`.
template<
    typename R
    BOOST_PP_REPEAT(BOOST_CLOSURE_AUX_arity,
            BOOST_CLOSURE_AUX_comma_arg_tparam, ~)
#if !BOOST_CLOSURE_AUX_CONFIG_LOCAL_TYPES_AS_TEMPLATE_PARAMS_01
    BOOST_PP_REPEAT(BOOST_CLOSURE_CONFIG_BIND_MAX,
            BOOST_CLOSURE_AUX_comma_bind_tparam, ~)
#endif
>
class function<
      R (BOOST_PP_ENUM(BOOST_CLOSURE_AUX_arity, BOOST_CLOSURE_AUX_arg_type, ~))
    , BOOST_CLOSURE_AUX_defaults
#if !BOOST_CLOSURE_AUX_CONFIG_LOCAL_TYPES_AS_TEMPLATE_PARAMS_01
    BOOST_PP_REPEAT(BOOST_CLOSURE_CONFIG_BIND_MAX,
            BOOST_CLOSURE_AUX_comma_bind_type, ~)
#endif
> {
    // The object type will actually be a local class which cannot be passed as
    // a template parameter so a generic `void*` pointer is used to hold the
    // object (this pointer will then be cased by the call-function implemented
    // by the local class itself). This is the trick used to pass a local
    // function as a template parameter. This trick uses function pointers for
    // the call-functions and function pointers cannot always be optimized by
    // the compiler (they cannot be inlined) thus this trick increased run-time
    // (another trick using virtual functions for the local class was also
    // investigated but also virtual functions cannot be inlined plus they
    // require virtual tables lookups so the virtual functions trick measured
    // worst run-time performance than the function pointer trick).
    typedef void* object_ptr;
    BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_CLOSURE_AUX_defaults), // INC so no dflt.
            BOOST_CLOSURE_AUX_call_typedef, BOOST_CLOSURE_AUX_arity)

public:
    // NOTE: Must have default constructor for init without function name in
    // function macro expansion.

    // Cannot be private but it should never be used by programmers directly
    // so used internal symbol.
    inline void BOOST_CLOSURE_AUX_FUNCTION_INIT_CALL_FUNC(
        object_ptr object
#if !BOOST_CLOSURE_AUX_CONFIG_LOCAL_TYPES_AS_TEMPLATE_PARAMS_01
        BOOST_PP_REPEAT(BOOST_CLOSURE_CONFIG_BIND_MAX,
                BOOST_CLOSURE_AUX_comma_bind_param_decl, ~)
#endif
        BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_CLOSURE_AUX_defaults),// INC no dflt.
                BOOST_CLOSURE_AUX_comma_call_param_decl, ~)
    ) {
        object_ = object;
#if !BOOST_CLOSURE_AUX_CONFIG_LOCAL_TYPES_AS_TEMPLATE_PARAMS_01
        BOOST_PP_REPEAT(BOOST_CLOSURE_CONFIG_BIND_MAX,
                BOOST_CLOSURE_AUX_bind_member_init, ~)
#endif
        BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_CLOSURE_AUX_defaults),
                BOOST_CLOSURE_AUX_call_init, ~)
        unused_ = 0; // To avoid a GCC uninitialized variable error.
    }
    
    // Result operator(Arg1, ..., ArgN-1, ArgN) -- iff defaults >= 0
    // Result operator(Arg1, ..., ArgN-1)       -- iff defaults >= 1
    // ...                                      -- etc
    BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_CLOSURE_AUX_defaults), // INC no dflt.
            BOOST_CLOSURE_AUX_operator_call, BOOST_CLOSURE_AUX_arity)

private:
    object_ptr object_;
#if !BOOST_CLOSURE_AUX_CONFIG_LOCAL_TYPES_AS_TEMPLATE_PARAMS_01
    BOOST_PP_REPEAT(BOOST_CLOSURE_CONFIG_BIND_MAX,
            BOOST_CLOSURE_AUX_bind_member_decl, ~)
#endif
    BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_CLOSURE_AUX_defaults), // INC no dflt.
            BOOST_CLOSURE_AUX_call_decl, ~)
    // run-time: this unused void* member variable allows for compiler
    // optimizations (at least on MSVC it reduces invocation time of about 50%)
    void* unused_; /** @todo do I really need this? */
};

#   undef BOOST_CLOSURE_AUX_defaults
#endif // iteration

