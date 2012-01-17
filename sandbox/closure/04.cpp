
#include <boost/closure/detail/preprocessor/keyword/void.hpp>
#include <boost/closure/detail/preprocessor/keyword/thisunderscore.hpp>
#include <boost/preprocessor.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>

////////////////////////////////////////////////////////////////////////////

// Argument: (token1)...
#define TO_LIST_FROM_SEQ_(unused, seq) \
    BOOST_PP_TUPLE_TO_LIST(BOOST_PP_SEQ_SIZE(seq), BOOST_PP_SEQ_TO_TUPLE(seq))

// Token: void | token1
#define TO_LIST_HANDLE_VOID_(is_void_macro, token) \
    /* REM to properly handle empty on MSVC, IS_BACK for leading symbols */ \
    BOOST_PP_IIF(is_void_macro(token), \
        BOOST_PP_NIL \
    , \
        (token, BOOST_PP_NIL) \
    )

// Token: (a)(b)... | empty | void | token
#define TO_LIST_HANDLE_SEQ_(is_void_macro, token) \
    /* REM to properly handle empty on MSVC */ \
    BOOST_PP_IIF(BOOST_PP_IS_UNARY(token), \
        TO_LIST_FROM_SEQ_ \
    , \
        TO_LIST_HANDLE_VOID_ \
    )(is_void_macro, token)

#ifdef BOOST_NO_VARIADIC_MACROS

#define TO_LIST(is_void_macro, seq) \
    TO_LIST_HANDLE_SEQ_(is_void_macro, seq)

#else // variadic

// Argument: token1, ...
#define TO_LIST_FROM_VARIADIC_(unused, ...) \
    BOOST_PP_TUPLE_TO_LIST(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__), (__VA_ARGS__))

#define TO_LIST(is_void_macro, ...) \
    BOOST_PP_IIF(BOOST_PP_EQUAL(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__), 1), \
        TO_LIST_HANDLE_SEQ_ \
    , \
        TO_LIST_FROM_VARIADIC_ \
    )(is_void_macro, __VA_ARGS__)

#endif // variadic

///////////////////////////////////////////////////////////////////////////

#define TRAITS_THIS_(d, binds, this01, this_) \
    (binds, 1 /* has this */)

#define TRAITS_BIND_(d, binds, this01, bind) \
    (BOOST_PP_LIST_APPEND(binds, (bind, BOOST_PP_NIL)), this01)

#define TRAITS_(d, binds_this, bind) \
    BOOST_PP_IIF(BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_THISUNDERSCORE_BACK(bind), \
        TRAITS_THIS_ \
    , \
        TRAITS_BIND_ \
    )(d, BOOST_PP_TUPLE_ELEM(2, 0, binds_this), \
            BOOST_PP_TUPLE_ELEM(2, 1, binds_this), bind)

#define TRAITS_ALL_(ref_val, traits) \
    ( \
        BOOST_PP_LIST_APPEND((ref_val, BOOST_PP_NIL), TRAITS_BINDS(traits)) \
    , \
        TRAITS_HAS_THIS(traits) \
    )

#define TRAITS(binds) \
    BOOST_PP_LIST_FOLD_LEFT(TRAITS_, (BOOST_PP_NIL, 0), binds)

#define TRAITS_ALL(binds) \
    TRAITS_ALL_(BOOST_PP_LIST_FIRST(binds), TRAITS(BOOST_PP_LIST_REST(binds)))

#define TRAITS_BINDS(traits) BOOST_PP_TUPLE_ELEM(2, 0, traits)

#define TRAITS_HAS_THIS(traits) BOOST_PP_TUPLE_ELEM(2, 1, traits)

////////////////////////////////////////////////////////////////////////////

template<typename This = void>
struct guard {
    explicit guard(This _this) : this_(_this) {}
    ~guard() { if(f_) f_(this_); }
    template<typename Lambda>
    void operator=(Lambda f) { f_ = f; }
private:
    This this_;
    boost::function<void (This)> f_;
};

template<>
struct guard<void> {
    ~guard() { if(f_) f_(); }
    template<typename Lambda>
    void operator=(Lambda f_) { f_ = f; }
private:
    boost::functon<void (void)> f_;
};

#define SCOPE_EXIT_AUX_GUARD_(id) \
    BOOST_PP_CAT(boost_se_guard_, id)

#define SCOPE_EXIT_AUX(id, typename01, traits) \
    guard< \
        BOOST_PP_EXPR_IIF(TRAITS_HAS_THIS(traits), \
            BOOST_TYPEOF(this) \
        ) \
    > SCOPE_EXIT_AUX_GUARD_(id)( \
        BOOST_PP_EXPR_IIF(TRAITS_HAS_THIS(traits), \
            this \
        ) \
    ); \
    SCOPE_EXIT_AUX_GUARD_(id) = [ BOOST_PP_LIST_ENUM(TRAITS_BINDS(traits)) ]( \
        BOOST_PP_EXPR_IIF(TRAITS_HAS_THIS(traits), \
            BOOST_TYPEOF(this) this_ \
        ) \
    ) mutable -> void

#ifdef BOOST_NO_VARIADIC_MACROS
#   define SCOPE_EXIT(seq) \
        SCOPE_EXIT_AUX(__LINE__, 0 /* no typename */, TRAITS(TO_LIST( \
                BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_VOID_BACK, seq)))
#else
#   define SCOPE_EXIT(...) \
        SCOPE_EXIT_AUX(__LINE__, 0 /* no typename */, TRAITS(TO_LIST( \
                BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_VOID_BACK, __VA_ARGS__)))
#endif

#define NEVER_VOID_(tokens) 0 /* always false */

#ifdef BOOST_NO_VARIADIC_MACROS
#   define SCOPE_EXIT_ALL(seq) \
        SCOPE_EXIT_AUX(__LINE__, 0 /* no typename */, TRAITS_ALL(TO_LIST( \
                NEVER_VOID_, seq)))
#else
#   define SCOPE_EXIT_ALL(...) \
        SCOPE_EXIT_AUX(__LINE__, 0 /* no typename */, TRAITS_ALL(TO_LIST( \
                NEVER_VOID_, __VA_ARGS__)))
#endif

//////////////////////////////////////////////////////////////////////////////

//SCOPE_EXIT( ) // no because IS_EMPTY(&r) fails :(
SCOPE_EXIT( void )
SCOPE_EXIT( &r )

SCOPE_EXIT( (&r) (v) (this_) )
SCOPE_EXIT( (&r) (v) (this) ) // C++11 only

SCOPE_EXIT_ALL( & ) // C++11 only
SCOPE_EXIT_ALL( = ) // C++11 only

SCOPE_EXIT_ALL( (&) ) // C++11 only
SCOPE_EXIT_ALL( (=) ) // C++11 only
SCOPE_EXIT_ALL( (&) (v) (this_) ) // C++11 only
SCOPE_EXIT_ALL( (=) (&r) (this) ) // C++11 only

#ifndef BOOST_NO_VARIADIC_MACROS

SCOPE_EXIT( &r, v, this_ )
SCOPE_EXIT( &r, v, this ) // C++11 only

SCOPE_EXIT_ALL( &, v, this_ ) // C++11 only
SCOPE_EXIT_ALL( =, &r, this ) // C++11 only

#endif

