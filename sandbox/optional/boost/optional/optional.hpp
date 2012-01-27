////////////////////////////////////////////////////////////////////////////////
///
/// \file optional.hpp
/// ------------------
///
/// Copyright (C) 2003, 2008 Fernando Luis Cacciola Carballal.
/// Copyright (c) 2012. Domagoj Saric (Little Endian Ltd).
///
/// You are welcome to contact the author at:
///  fernando_cacciola@hotmail.com
///
/// Revisions:
/// 27 Apr 2008 (improved swap) Fernando Cacciola, Niels Dekker, Thorsten Ottosen
///    Jan 2012 (major rewrite) Domagoj Saric
///
/// Use, modification, and distribution is subject to the Boost Software
/// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
/// http://www.boost.org/LICENSE_1_0.txt)
///
/// See http://www.boost.org/libs/optional for documentation.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef optional_hpp__7A6241F3_FB9E_4EDF_A698_39CB296F3D8D
#define optional_hpp__7A6241F3_FB9E_4EDF_A698_39CB296F3D8D
#pragma once
//------------------------------------------------------------------------------
#include "boost/assert.hpp"
#include "boost/config.hpp"
#include "boost/mpl/bool.hpp"
#include "boost/none.hpp"
#include "boost/range/detail/safe_bool.hpp"
#include "boost/optional/optional_fwd.hpp"
#include "boost/type_traits/alignment_of.hpp"
#include "boost/type_traits/has_nothrow_constructor.hpp"
#include "boost/type_traits/has_nothrow_copy.hpp"
#include "boost/type_traits/has_trivial_destructor.hpp"
#include "boost/type_traits/is_fundamental.hpp"
#include "boost/type_traits/is_reference.hpp"
#include "boost/type_traits/remove_reference.hpp"
#include "boost/type_traits/type_with_alignment.hpp"
#include "boost/utility/addressof.hpp"
#include "boost/utility/compare_pointees.hpp"
#include "boost/utility/in_place_factory.hpp"
#include "boost/utility/swap.hpp"

#include <algorithm>
#include <new>
//------------------------------------------------------------------------------

//...zzz...extract into a proper header...
#if defined( _MSC_VER )
    #define BOOST_ASSUME( condition ) BOOST_ASSERT_MSG( condition, "Assumption broken." ); __assume( condition )
#elif defined( __GNUC__ )
    #if ( __clang_major__ >= 2 ) || ( ( ( __GNUC__ * 10 ) + __GNUC_MINOR__ ) >= 45 )
        #define BOOST_ASSUME( condition ) BOOST_ASSERT_MSG( condition, "Assumption broken." ); do { if ( !( condition ) ) __builtin_unreachable(); } while ( 0 )
    #else
        #define BOOST_ASSUME( condition ) BOOST_ASSERT_MSG( condition, "Assumption broken." );
    #endif
#else
    #define BOOST_ASSUME( condition ) BOOST_ASSERT_MSG( condition, "Assumption broken." );
#endif

namespace boost
{
    class in_place_factory_base;
    class typed_in_place_factory_base;

    class in_place_factory0;
    template <typename T> class typed_in_place_factory0;
} //namespace boost

// Daniel Wallin discovered that bind/apply.hpp badly interacts with the apply<>
// member template of a factory as used in the optional<> implementation.
// He proposed this simple fix which is to move the call to apply<> outside
// namespace boost.
/// \todo Reinvestigate and properly document this issue (in which contexts does
/// it occur and what exactly does "bad interaction" mean here).
///                                           (12.01.2012.) (Domagoj Saric)
namespace boost_optional_detail
{
    template <class T, class Factory>
    T & construct( Factory const & factory, T * const address, ::boost::in_place_factory_base const * )
    {
        /// \note
        ///   Help the compiler (e.g. MSVC10) detect that placement new will
        /// never return a nullptr.
        ///                                   (11.01.2012.) (Domagoj Saric)
        BOOST_ASSUME( address );
        T * const p_object( static_cast<T *>( factory. BOOST_NESTED_TEMPLATE apply<T>( address ) ) );
        BOOST_ASSUME( p_object );
        return *p_object;
    }

    template <class T, class Factory>
    T & construct( Factory const & factory, T * const address, ::boost::typed_in_place_factory_base const * )
    {
        BOOST_ASSUME( address );
        T * const p_object( static_cast<T *>( factory.apply( address ) ) );
        BOOST_ASSUME( p_object );
        return *p_object;
    }
} // namespace boost_optional_detail

namespace boost
{
//------------------------------------------------------------------------------

namespace optional_detail
{

template <typename T, bool is_pod>
struct placeholder
{
public:
    typedef T const & reference_const_type;
    typedef T       & reference_type      ;
    typedef T const * pointer_const_type  ;
    typedef T       * pointer_type        ;
    typedef T const & argument_type       ;

public:
    #ifdef NDEBUG
        placeholder() {}
    #else
         placeholder() : initialised_( false ) {}
        ~placeholder() { BOOST_ASSERT_MSG( !initialised_ || has_trivial_destructor<T>::value, "Placeholder destroyed w/o its contents being cleared." ); }
    #endif // NDEBUG

    template <class Expr>
    reference_type construct( Expr const & expr )
    {
        return construct( expr, boost::addressof( expr ) );
    }

    void destroy()
    {
        BOOST_ASSERT_MSG( initialised_, "Nothing in placeholder to destroy." );
        #ifndef NDEBUG
            initialised_ = false;
        #endif // NDEBUG
        /// \note Avoid calling the destructor virtually.
        ///                                   (11.01.2012.) (Domagoj Saric)
        address()->T::~T();
    }

    reference_type get()
    {
        BOOST_ASSERT_MSG( initialised_, "Placeholder not initialised." );
        return *address();
    }

    reference_const_type get() const { return const_cast<placeholder &>( *this ).get(); }

protected:
    placeholder( placeholder const & ) {}

    T       * get_pointer_unchecked()       { return address(); }
    T const * get_pointer_unchecked() const { return address(); }

private:
    void operator=( placeholder const & );

private:
    // Constructs in-place using the given factory
    template <class Expr>
    T & construct( Expr const & factory, in_place_factory_base const * )
    {
        BOOST_ASSERT_MSG
        (
            !initialised_ || has_trivial_destructor<T>::value,
            "Placeholder already filled."
        );
        BOOST_VERIFY( &boost_optional_detail::construct<T>( factory, address(), &factory ) == address() );
        #ifndef NDEBUG
            initialised_ = true;
        #endif // NDEBUG
        return get();
    }

    // Constructs in-place using the given typed factory
    template <class Expr>
    T & construct( Expr const & factory, typed_in_place_factory_base const * )
    {
        BOOST_ASSERT_MSG( !initialised_, "Placeholder already filled." );
        BOOST_VERIFY( &boost_optional_detail::construct<T>( factory, address(), &factory ) == address() );
        #ifndef NDEBUG
            initialised_ = true;
        #endif // NDEBUG
        return get();
    }

    // Constructs using any expression implicitly convertible to the single argument
    // of a one-argument T constructor.
    // Converting constructions of optional<T> from optional<U> uses this function with
    // 'Expr' being of type 'U' and relying on a converting constructor of T from U.
    template <class Expr>
    T & construct( Expr const & expr, void const * )
    {
        BOOST_ASSERT_MSG( !initialised_, "Placeholder already filled." );
        T * const p_object( new ( address() ) T( expr ) );
        /// \note
        ///   Help the compiler (e.g. MSVC10) detect that placement new will
        /// never return a nullptr.
        ///                                   (11.01.2012.) (Domagoj Saric)
        BOOST_ASSUME( p_object );
        BOOST_ASSERT( p_object == address() );
        #ifndef NDEBUG
            initialised_ = true;
        #endif // NDEBUG
        return get();
    }

    pointer_type       address()       { return static_cast<pointer_type>( static_cast<void *>( static_cast<char *>( storage_.data ) ) ); }
    pointer_const_type address() const { return const_cast<placeholder &>( *this ).address(); }

private:
    typedef BOOST_DEDUCED_TYPENAME type_with_alignment< ::boost::alignment_of<T>::value>::type aligner_t;
    union
    {
        char      data[ sizeof( T ) ];
        aligner_t aligner;
    } storage_;

#ifndef NDEBUG
    bool initialised_;
#endif // NDEBUG
};


template <typename T>
struct placeholder<T, true /*is_pod*/>
{
public:
    typedef T const & reference_const_type;
    typedef T       & reference_type      ;
    typedef T const * pointer_const_type  ;
    typedef T       * pointer_type        ;
    typedef T const & argument_type       ;

public:
    placeholder() {}

    template <class Expr>
    reference_type construct( Expr const & expr )
    {
        return construct( expr, boost::addressof( expr ) );
    }

    void destroy() {}

    reference_type       get()       { return storage_; }
    reference_const_type get() const { return storage_; }

protected:
    placeholder( placeholder const & ) { BOOST_ASSERT( !"unreachable" ); }

    pointer_type       get_pointer_unchecked()       { return &get(); }
    pointer_const_type get_pointer_unchecked() const { return &get(); }

private:
    void operator=( placeholder const & );

private:
    template <class Expr>
    reference_type construct( Expr const & factory, in_place_factory_base const * )
    {
        BOOST_VERIFY( &boost_optional_detail::construct<T>( factory, &storage_, &factory ) == &storage_ );
        return storage_;
    }

    template <class Expr>
    reference_type construct( Expr const & factory, typed_in_place_factory_base const * )
    {
        BOOST_VERIFY( &boost_optional_detail::construct<T>( factory, &storage_, &factory ) == &storage_ );
        return storage_;
    }

    template <class Expr>
    reference_type construct( Expr const & expr, void const * )
    {
        /// \note
        ///   MSVC10 has problems detecting that placement new will never
        /// return a nullptr (and thus generates bogus branching code) so we
        /// avoid it for PODs altogether.
        ///                                   (11.01.2012.) (Domagoj Saric)
        storage_ = expr;
        return storage_;
    }

private:
    T storage_;
};

template <typename T, bool is_pod>
struct placeholder<T &, is_pod>
{
private:
    typedef BOOST_DEDUCED_TYPENAME remove_reference<T>::type raw_type;

public:
    typedef raw_type & reference_const_type;
    typedef raw_type & reference_type      ;
    typedef raw_type * pointer_const_type  ;
    typedef raw_type * pointer_type        ;
    typedef raw_type & argument_type       ;

public:
    placeholder() : storage_( NULL ) {}

    reference_type construct( argument_type const source )
    {
        storage_ = &source;
        return source;
    }

    void destroy() { storage_ = NULL; }

    reference_type       get()       { BOOST_ASSERT_MSG( storage_, "Placeholder not initialised." ); return *storage_; }
    reference_const_type get() const { return const_cast<placeholder &>( *this ).get(); }

protected:
    placeholder( placeholder const & ) {}

    pointer_type       get_pointer_unchecked()       { return storage_; }
    pointer_const_type get_pointer_unchecked() const { return storage_; }

private:
    void operator=( placeholder const & );

private:
    pointer_type storage_;
};


template <class Derived, bool trivial>
struct destructor
{
protected:
    // No-throw (assuming Derived::direct_destroy_wo_marking() doesn't)
    ~destructor()
    {
        BOOST_ASSUME( this );
        Derived & this_optional( static_cast<Derived &>( *this ) );
        if ( this_optional.is_initialized() )
            this_optional.direct_destroy_wo_marking();
    }
};

template <class Derived              > struct destructor<Derived  , true   > {};
template <class Derived, bool trivial> struct destructor<Derived &, trivial> {};

struct optional_tag {};

} // namespace optional_detail

#ifdef BOOST_MSVC
    #pragma warning( push )
    #pragma warning( disable : 4127 ) // Conditional expression is constant.
#endif // BOOST_MSVC

template <typename T>
class optional2
    :
    private optional_detail::placeholder<T, is_pod<T>::value>,
    private optional_detail::destructor<optional2<T>, has_trivial_destructor<T>::value || is_reference<T>::value>,
    public  optional_detail::optional_tag
{
public:
    typedef optional_detail::placeholder<T, is_pod<T>::value> placeholder_t;

    typedef T value_type;

    typedef BOOST_DEDUCED_TYPENAME placeholder_t::reference_type       reference_type      ;
    typedef BOOST_DEDUCED_TYPENAME placeholder_t::reference_const_type reference_const_type;
    typedef BOOST_DEDUCED_TYPENAME placeholder_t::pointer_type         pointer_type        ;
    typedef BOOST_DEDUCED_TYPENAME placeholder_t::pointer_const_type   pointer_const_type  ;
    typedef BOOST_DEDUCED_TYPENAME placeholder_t::argument_type        argument_type       ;

private:
    typedef mpl::bool_<is_pod<T>::value || is_reference<T>::value> direct_create_assign;

    typedef boost::range_detail::safe_bool<pointer_type optional2::*> safe_bool_t;

    pointer_type pointer_;

public: // Construction.

    // Creates an optional<T> uninitialized.
    // No-throw
    optional2() : pointer_( NULL ) {}

    // Creates an optional<T> uninitialized.
    // No-throw
    optional2( none_t ) : pointer_( NULL ) {}

    // Creates an optional<T> initialized with 'val'.
    // Can throw if T::T( T const & ) does
    optional2( argument_type const val ) { construction( val ); }

    // Creates an optional<T> initialized with 'val' IFF cond is true, otherwise creates an uninitialized optional<T>.
    // Can throw if T::T(T const&) does
    template <class Expr>
    optional2( bool const cond, Expr          const & expr ) { conditional_construction( cond, &expr ); }
    optional2( bool const cond, argument_type const   val  ) { conditional_construction( cond, &val  ); }

    // Creates an optional<T> with an expression which can be either
    //  (a) An instance of InPlaceFactory (i.e. in_place(a,b,...,n);
    //  (b) An instance of TypedInPlaceFactory ( i.e. in_place<T>(a,b,...,n);
    //  (c) Any expression implicitly convertible to the single type of a
    //      one-argument T's constructor.
    // Depending on the above some T ctor is called.
    // Can throw is the resolved T ctor throws.
    template <class Expr>
    explicit optional2( Expr const & expr ) { construction( expr ); }


    // Creates a deep copy of another optional<T> or convertible optional<U>.
    // Can throw if T::T( U const & ) does
    optional2( optional2 const & rhs )
    {
        conditional_construction( rhs.is_initialized(), rhs.get_pointer_unchecked() );
    }

    template <class U>
    explicit optional2( optional2<U> const & rhs )
    {
        conditional_construction( rhs.is_initialized(), rhs.get_pointer_unchecked() );
    }

public: // Assignment.

    // Assigns from an expression. See corresponding constructor.
    // Basic Guarantee: If the resolved T ctor throws, this is left UNINITIALIZED
    template <class Expr>
    optional2 & operator=( Expr const & expr )
    {
        assign_expr( expr, boost::addressof( expr ) );
        return *this;
    }

    // Assigns from another optional<T> or convertible optional<U> (deep-copies
    // the rhs value). Requires a valid conversion from U to T.
    // Basic Guarantee: If T::T( U const & ) throws, this is left UNINITIALIZED
    optional2 & operator=( optional2    const & rhs ) { return assign_optional<T>( rhs ); }
    template <class U>
    optional2 & operator=( optional2<U> const & rhs ) { return assign_optional<U>( rhs ); }

    // Assigns from a T (deep-copies the rhs value)
    // Basic Guarantee: If T::( T const & ) throws, this is left UNINITIALIZED
    optional2 & operator=( argument_type const val ) { reset( val ); return *this; }

    // Assigns from "none", destroying the current value, if any, leaving this
    // UNINITIALIZED.
    // No-throw (assuming T::~T() doesn't)
    optional2 & operator=( none_t                  ) { reset(     ); return *this; }

public: // Utility interface.

    // Destroys the current value, if any, leaving this UNINITIALIZED
    // No-throw (assuming T::~T() doesn't)
    void reset() { destroy(); }

    // Replaces the current value -if any- with 'val'
    template <class U>
    void reset( U & val ) { assign( val, direct_create_assign() ); }

    // Returns a pointer to the value if this is initialized, otherwise, returns
    // NULL.
    // No-throw
    pointer_const_type get_ptr() const { return pointer_; }
    pointer_type       get_ptr()       { return pointer_; }

    bool is_initialized() const { return pointer_ != NULL; }

    // Returns a reference to the value if this is initialized, otherwise,
    // the behaviour is UNDEFINED
    // No-throw
    reference_const_type get() const { BOOST_ASSERT( this->is_initialized() ); return storage().get(); }
    reference_type       get()       { BOOST_ASSERT( this->is_initialized() ); return storage().get(); }

    // Returns a copy of the value if this is initialized, 'v' otherwise
    reference_const_type get_value_or( reference_const_type v ) const { return this->is_initialized() ? get() : v; }
    reference_type       get_value_or( reference_type       v )       { return this->is_initialized() ? get() : v; }

    // Returns a pointer to the value if this is initialized, otherwise,
    // the behaviour is UNDEFINED
    // No-throw
    pointer_const_type operator->() const { BOOST_ASSERT( this->is_initialized() ); return this->get_pointer_unchecked(); }
    pointer_type       operator->()       { BOOST_ASSERT( this->is_initialized() ); return this->get_pointer_unchecked(); }

    // Returns a reference to the value if this is initialized, otherwise,
    // the behaviour is UNDEFINED
    // No-throw
    reference_const_type operator *() const { return this->get(); }
    reference_type       operator *()       { return this->get(); }

    // implicit conversion to "bool"
    // No-throw
    operator BOOST_DEDUCED_TYPENAME safe_bool_t::unspecified_bool_type() const
    {
        return safe_bool_t::to_unspecified_bool( is_initialized(), &optional2::pointer_ );
    }

    // This is provided for those compilers which don't like the conversion to
    // bool in some contexts.
    bool operator!() const { return !this->is_initialized(); }

    void swap( optional2 & arg )
    {
        // allow for Koenig lookup
        using boost::swap;
        swap( *this, arg );
    }

public: // Direct, unchecked lifetime management.

    template <class Expr>
    void direct_create( Expr          const & expr  ) { pointer_ = boost::addressof( storage().construct( expr  ) ); }
    void direct_create( argument_type const   value ) { pointer_ = boost::addressof( storage().construct( value ) ); }

    void direct_destroy() { pointer_ = NULL; direct_destroy_wo_marking(); }

private:
    // Assigns from a T or a _convertible_ U (deep-copies the source value).
    template <class U>
    void assign( U & value, mpl::true_ /*direct create*/ ) { direct_create( value ); }

    template <class U>
    void assign( U & value, mpl::false_ /*direct create*/ )
    {
        if ( !this->is_initialized() )
            direct_create( value );
        else
            get() = value;
    }

    // Assigns using a form any expression implicitly convertible to the single argument
    // of a T's assignment operator.
    // Converting assignments of optional<T> from optional<U> uses this function with
    // 'Expr' being of type 'U' and relying on a converting assignment of T from U.
    template <class Expr>
    void assign_expr( Expr & expr, void const * ) { reset( expr ); }

    template <class Expr>
    void assign_expr( Expr const & factory,       in_place_factory_base const * ) { assign_factory( factory ); }
    template <class Expr>
    void assign_expr( Expr const & factory, typed_in_place_factory_base const * ) { assign_factory( factory ); }

    // Constructs in-place using the given typed factory
    template <class Factory>
    void assign_factory( Factory const & factory )
    {
        if ( !has_trivial_destructor<T>::value && is_initialized() )
        {
            mark_as_uninitialised_if_construction_can_throw( factory, boost::addressof( factory ) );
            direct_destroy();
        }
        direct_create( factory );
    }

    template <class U>
    optional2 & assign_optional( optional2<U> const & rhs )
    {
        if ( rhs.is_initialized() )
            reset( *rhs );
        else
            destroy();
        return *this;
    }

    void destroy()
    {
        if ( is_initialized() )
        {
            pointer_ = NULL;
            if ( !has_trivial_destructor<T>::value )
                direct_destroy();
        }
    }

    template <class U>
    void construction( U & source )
    {
        mark_as_uninitialised_if_construction_can_throw( source, boost::addressof( source ) );
        direct_create( source );
    }

    template <class U>
    void conditional_construction( std::size_t const condition, U * p_source )
    {
        if ( condition )
        {
            BOOST_ASSERT(  p_source );
            construction( *p_source );
        }
        else
        {
            pointer_ = NULL;
        }
    }

    template <class SourceExpr>
    void mark_as_uninitialised_if_construction_can_throw( SourceExpr const &, void const * )
    {
        /// \note
        ///   A POD can have a conversion operator which might throw so
        /// SourceExpr has to be a fundamental type to safely assume nothrow
        /// converting construction.
        ///                                   (12.01.2012.) (Domagoj Saric)
        if ( !is_pod<T>::value || !is_fundamental<SourceExpr>::value )
            pointer_ = NULL;
    }

    void mark_as_uninitialised_if_construction_can_throw( argument_type, void const * )
    {
        if ( !has_nothrow_copy<T>::value )
            pointer_ = NULL;
    }

    void mark_as_uninitialised_if_construction_can_throw( in_place_factory0 const &, in_place_factory_base const * )
    {
        if ( !has_nothrow_default_constructor<T>::value )
            pointer_ = NULL;
    }

    void mark_as_uninitialised_if_construction_can_throw( typed_in_place_factory0<T> const &, typed_in_place_factory_base const * )
    {
        if ( !has_nothrow_default_constructor<T>::value )
            pointer_ = NULL;
    }

    template <class Derived, bool trivial> friend struct optional_detail::destructor;
    void direct_destroy_wo_marking() { storage().destroy(); }

    template <class U> friend class optional2;
    using placeholder_t::get_pointer_unchecked;

    placeholder_t       & storage()       { return static_cast<placeholder_t &>( *this )   ; }
    placeholder_t const & storage() const { return const_cast<optional2 &>( *this ).storage(); }
}; // class optional

#ifdef BOOST_MSVC
    #pragma warning( push )
#endif // BOOST_MSVC

// Returns optional<T>(v)
template<class T>
inline optional2<T> make_optional( T const & v )
{
  return optional2<T>( v );
}

// Returns optional<T>(cond,v)
template<class T>
inline optional2<T> make_optional( bool const cond, T const & v )
{
  return optional2<T>( cond, v );
}

// Returns a reference to the value if this is initialized, otherwise, the behaviour is UNDEFINED.
// No-throw
template<class T>
inline BOOST_DEDUCED_TYPENAME optional2<T>::reference_const_type
get( optional2<T> const & opt ) { return opt.get(); }

template<class T>
inline BOOST_DEDUCED_TYPENAME optional2<T>::reference_type
get( optional2<T>       & opt ) { return opt.get(); }

// Returns a pointer to the value if this is initialized, otherwise, returns NULL.
// No-throw
template<class T>
inline BOOST_DEDUCED_TYPENAME optional2<T>::pointer_const_type
get( optional2<T> const * opt ) { return opt->get_ptr(); }

template<class T>
inline BOOST_DEDUCED_TYPENAME optional2<T>::pointer_type
get( optional2<T>       * opt ) { return opt->get_ptr(); }

// Returns a reference to the value if this is initialized, otherwise, the behaviour is UNDEFINED.
// No-throw
template<class T>
inline BOOST_DEDUCED_TYPENAME optional2<T>::reference_const_type
get_optional_value_or( optional2<T> const & opt, BOOST_DEDUCED_TYPENAME optional2<T>::reference_const_type v )
{
    return opt.get_value_or( v );
}

template<class T>
inline BOOST_DEDUCED_TYPENAME optional2<T>::reference_type
get_optional_value_or( optional2<T> & opt, BOOST_DEDUCED_TYPENAME optional2<T>::reference_type v )
{
    return opt.get_value_or( v );
}

// Returns a pointer to the value if this is initialized, otherwise, returns NULL.
// No-throw
template<class T>
inline BOOST_DEDUCED_TYPENAME optional2<T>::pointer_const_type
get_pointer( optional2<T> const & opt ) { return opt.get_ptr(); }

template<class T>
inline BOOST_DEDUCED_TYPENAME optional2<T>::pointer_type
get_pointer( optional2<T>       & opt ) { return opt.get_ptr(); }

// optional's relational operators ( ==, !=, <, >, <=, >= ) have deep-semantics (compare values).
// WARNING: This is UNLIKE pointers. Use equal_pointees()/less_pointess() in generic code instead.


//
// optional<T> vs optional<T> cases
//

template<class T>
inline
bool operator == ( optional2<T> const& x, optional2<T> const& y )
{ return equal_pointees(x,y); }

template<class T>
inline
bool operator < ( optional2<T> const& x, optional2<T> const& y )
{ return less_pointees(x,y); }

template<class T>
inline
bool operator != ( optional2<T> const& x, optional2<T> const& y )
{ return !( x == y ) ; }

template<class T>
inline
bool operator > ( optional2<T> const& x, optional2<T> const& y )
{ return y < x ; }

template<class T>
inline
bool operator <= ( optional2<T> const& x, optional2<T> const& y )
{ return !( y < x ) ; }

template<class T>
inline
bool operator >= ( optional2<T> const& x, optional2<T> const& y )
{ return !( x < y ) ; }


//
// optional<T> vs T cases
//
template<class T>
inline
bool operator == ( optional2<T> const& x, T const& y )
{ return equal_pointees(x, optional2<T>(y)); }

template<class T>
inline
bool operator < ( optional2<T> const& x, T const& y )
{ return less_pointees(x, optional2<T>(y)); }

template<class T>
inline
bool operator != ( optional2<T> const& x, T const& y )
{ return !( x == y ) ; }

template<class T>
inline
bool operator > ( optional2<T> const& x, T const& y )
{ return y < x ; }

template<class T>
inline
bool operator <= ( optional2<T> const& x, T const& y )
{ return !( y < x ) ; }

template<class T>
inline
bool operator >= ( optional2<T> const& x, T const& y )
{ return !( x < y ) ; }

//
// T vs optional<T> cases
//

template<class T>
inline
bool operator == ( T const& x, optional2<T> const& y )
{ return equal_pointees( optional2<T>(x), y ); }

template<class T>
inline
bool operator < ( T const& x, optional2<T> const& y )
{ return less_pointees( optional2<T>(x), y ); }

template<class T>
inline
bool operator != ( T const& x, optional2<T> const& y )
{ return !( x == y ) ; }

template<class T>
inline
bool operator > ( T const& x, optional2<T> const& y )
{ return y < x ; }

template<class T>
inline
bool operator <= ( T const& x, optional2<T> const& y )
{ return !( y < x ) ; }

template<class T>
inline
bool operator >= ( T const& x, optional2<T> const& y )
{ return !( x < y ) ; }


//
// optional<T> vs none cases
//

template<class T>
inline
bool operator == ( optional2<T> const& x, none_t )
{ return equal_pointees(x, optional2<T>() ); }

template<class T>
inline
bool operator < ( optional2<T> const& x, none_t )
{ return less_pointees(x,optional2<T>() ); }

template<class T>
inline
bool operator != ( optional2<T> const& x, none_t y )
{ return !( x == y ) ; }

template<class T>
inline
bool operator > ( optional2<T> const& x, none_t y )
{ return y < x ; }

template<class T>
inline
bool operator <= ( optional2<T> const& x, none_t y )
{ return !( y < x ) ; }

template<class T>
inline
bool operator >= ( optional2<T> const& x, none_t y )
{ return !( x < y ) ; }

//
// none vs optional<T> cases
//

template<class T>
inline
bool operator == ( none_t x, optional2<T> const& y )
{ return equal_pointees(optional2<T>() ,y); }

template<class T>
inline
bool operator < ( none_t x, optional2<T> const& y )
{ return less_pointees(optional2<T>() ,y); }

template<class T>
inline
bool operator != ( none_t x, optional2<T> const& y )
{ return !( x == y ) ; }

template<class T>
inline
bool operator > ( none_t x, optional2<T> const& y )
{ return y < x ; }

template<class T>
inline
bool operator <= ( none_t x, optional2<T> const& y )
{ return !( y < x ) ; }

template<class T>
inline
bool operator >= ( none_t x, optional2<T> const& y )
{ return !( x < y ) ; }

namespace optional_detail {

template<bool use_default_constructor> struct swap_selector;

template<>
struct swap_selector<true>
{
    template <class T>
    static void optional_swap ( optional2<T> & x, optional2<T> & y )
    {
        const bool hasX = !!x;
        const bool hasY = !!y;

        if ( !hasX && !hasY )
            return;

        if ( !hasX )
            x = boost::in_place();
        else if ( !hasY )
            y = boost::in_place();

        // Boost.Utility.Swap will take care of ADL and workarounds for broken compilers
        boost::swap( *x, *y );

        if ( !hasX )
            y = boost::none;
        else if ( !hasY )
            x = boost::none;
    }
};

template<>
struct swap_selector<false>
{
    template <class T>
    static void optional_swap ( optional2<T> & x, optional2<T> & y )
    {
        const bool hasX = !!x;
        const bool hasY = !!y;

        if ( !hasX && hasY )
        {
            x = *y;
            y = boost::none;
        }
        else if ( hasX && !hasY )
        {
            y = *x;
            x = boost::none;
        }
        else if ( hasX && hasY )
        {
            // Boost.Utility.Swap will take care of ADL and workarounds for broken compilers
            boost::swap( *x, *y );
        }
    }
};

} // namespace optional_detail

template <class T>
struct optional_swap_should_use_default_constructor : has_nothrow_default_constructor<T> {} ;

template <class T> inline void swap ( optional2<T> & x, optional2<T> & y )
{
    optional_detail::swap_selector<optional_swap_should_use_default_constructor<T>::value>::optional_swap(x, y);
}

//------------------------------------------------------------------------------
} // namespace boost
//------------------------------------------------------------------------------
#endif // optional_hpp
