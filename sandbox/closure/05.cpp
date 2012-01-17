
#include <boost/closure/detail/preprocessor/keyword/void.hpp>
#include <boost/closure/detail/preprocessor/keyword/thisunderscore.hpp>
#include <boost/preprocessor.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>

///////////////////////////////////////////////////////////////////////////

#define SCOPE_EXIT_AUX_TRAITS_THIS_(d, binds, this01, this_) \
    (binds, 1 /* has this */)

#define SCOPE_EXIT_AUX_TRAITS_BIND_(d, binds, this01, bind) \
    (BOOST_PP_LIST_APPEND(binds, (bind, BOOST_PP_NIL)), this01)

#define SCOPE_EXIT_AUX_TRAITS_(d, binds_this, bind) \
    BOOST_PP_IIF(BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_THISUNDERSCORE_BACK(bind), \
        SCOPE_EXIT_AUX_TRAITS_THIS_ \
    , \
        SCOPE_EXIT_AUX_TRAITS_BIND_ \
    )(d, BOOST_PP_TUPLE_ELEM(2, 0, binds_this), \
            BOOST_PP_TUPLE_ELEM(2, 1, binds_this), bind)

#define SCOPE_EXIT_AUX_TRAITS_ALL_(ref_val, traits) \
    ( \
        BOOST_PP_LIST_APPEND((ref_val, BOOST_PP_NIL), \
                SCOPE_EXIT_AUX_TRAITS_BINDS(traits)) \
    , \
        SCOPE_EXIT_AUX_TRAITS_HAS_THIS(traits) \
    )

#define SCOPE_EXIT_AUX_TRAITS(binds) \
    BOOST_PP_LIST_FOLD_LEFT(SCOPE_EXIT_AUX_TRAITS_, (BOOST_PP_NIL, 0), binds)

#define SCOPE_EXIT_AUX_TRAITS_ALL(binds) \
    SCOPE_EXIT_AUX_TRAITS_ALL_(BOOST_PP_LIST_FIRST(binds), \
            SCOPE_EXIT_AUX_TRAITS(BOOST_PP_LIST_REST(binds)))

#define SCOPE_EXIT_AUX_TRAITS_BINDS(traits) BOOST_PP_TUPLE_ELEM(2, 0, traits)

#define SCOPE_EXIT_AUX_TRAITS_HAS_THIS(traits) BOOST_PP_TUPLE_ELEM(2, 1, traits)

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
        BOOST_PP_EXPR_IIF(SCOPE_EXIT_AUX_TRAITS_HAS_THIS(traits), \
            BOOST_TYPEOF(this) \
        ) \
    > SCOPE_EXIT_AUX_GUARD_(id)( \
        BOOST_PP_EXPR_IIF(SCOPE_EXIT_AUX_TRAITS_HAS_THIS(traits), \
            this \
        ) \
    ); \
    SCOPE_EXIT_AUX_GUARD_(id) = [ \
        BOOST_PP_LIST_ENUM(SCOPE_EXIT_AUX_TRAITS_BINDS(traits)) \
    ]( \
        BOOST_PP_EXPR_IIF(SCOPE_EXIT_AUX_TRAITS_HAS_THIS(traits), \
            BOOST_TYPEOF(this) this_ \
        ) \
    ) mutable -> void

#ifdef BOOST_NO_VARIADIC_MACROS
#   define SCOPE_EXIT(seq) \
        SCOPE_EXIT_AUX(__LINE__, 0 /* no typename */, SCOPE_EXIT_AUX_TRAITS( \
                SCOPE_EXIT_AUX_BINDS( \
                BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_VOID_BACK, seq)))
#else
#   define SCOPE_EXIT(...) \
        SCOPE_EXIT_AUX(__LINE__, 0 /* no typename */, SCOPE_EXIT_AUX_TRAITS( \
                SCOPE_EXIT_AUX_BINDS( \
                BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_VOID_BACK, __VA_ARGS__)))
#endif

#ifdef BOOST_NO_VARIADIC_MACROS
#   define SCOPE_EXIT_ALL(seq) \
        SCOPE_EXIT_AUX(__LINE__, 0 /* no typename */, \
                SCOPE_EXIT_AUX_TRAITS_ALL(SCOPE_EXIT_AUX_BINDS( \
                SCOPE_EXIT_AUX_BINDS_NEVER_VOID, seq)))
#else
#   define SCOPE_EXIT_ALL(...) \
        SCOPE_EXIT_AUX(__LINE__, 0 /* no typename */, \
                SCOPE_EXIT_AUX_TRAITS_ALL(SCOPE_EXIT_AUX_BINDS( \
                SCOPE_EXIT_AUX_BINDS_NEVER_VOID, __VA_ARGS__)))
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

