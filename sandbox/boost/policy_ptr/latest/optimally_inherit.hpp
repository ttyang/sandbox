//----------------------------------------------------------------------------
//
// optimally_inherit.hpp
//
//----------------------------------------------------------------------------
// Copyright (C) 2002, David B. Held.
//
// Code inspired by Andrei Alexandrescu's OptionallyInherit template as well
// as boost::compressed_pair.
//
// See http://www.boost.org/ for most recent version, including documentation.
// Boost Software License - Version 1.0 - August 17th, 2003
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//----------------------------------------------------------------------------
// optimally_inherit<> helps avoid EBO pessimization with multiple inheritance
// by only inheriting from non-empty base classes.  See
// libs/optimally_inherit/doc/index.html
//
// 02-02-2004: Jonathan Turkanis added disambiguation machinery for broken
//             compilers. Needed for Intel 7.1, Comeau 4.3.3 and Borland 5.x.
//----------------------------------------------------------------------------
#ifndef BOOST_OPTIMALLY_INHERIT_20020703_HPP
#define BOOST_OPTIMALLY_INHERIT_20020703_HPP
//----------------------------------------------------------------------------
#include <boost/type_traits/object_traits.hpp>

//----------------------------------------------------------------------------
// Machinery to help broken compilers resolve smart_ptr and optimal_parents 
// constructor invocations. Currently, compilers requiring this workaround 
// include Intel 7.1 for Windows, Comeau 4.3.3, Borland 5.6.4 and MSVC 6.0.
//----------------------------------------------------------------------------

// Coniditionally placed at the end of argument lists in base class
// constructor invocations.
namespace boost { namespace detail { struct disambiguator_tag { }; } }

// Usage: add BOOST_SMART_PTR_DISAMBIGUATOR_TAG at the end of constructor 
// argument lists which end with init_first_tag, static_cast_tag, 
// dynamic_cast_tag or polymorphic_cast_tag; add BOOST_SMART_PTR_DISAMBIGUATOR
// to the end of the argument lists of invocations of such constructors.
#if defined(__INTEL_COMPILER) && (__INTEL_COMPILER < 800) || \
    defined(__COMO__) ||                                     \
    defined(__BORLANDC__) && (__BORLANDC__ < 0x600)          \
    defined(BOOST_MSVC) && (BOOST_MSVC < 1310)               \
    /**/
# define BOOST_SMART_PTR_DISAMBIGUATOR_TAG , detail::disambiguator_tag const&
# define BOOST_SMART_PTR_DISAMBIGUATOR     , detail::disambiguator_tag()
#else
# define BOOST_SMART_PTR_DISAMBIGUATOR_TAG
# define BOOST_SMART_PTR_DISAMBIGUATOR
#endif

//----------------------------------------------------------------------------
// Definition of optimally_inherit
//----------------------------------------------------------------------------
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
//----------------------------------------------------------------------------
namespace boost
{
    //------------------------------------------------------------------------
    namespace detail
    {
        //--------------------------------------------------------------------
        // Initialization tags - bad hack
        //   These tags allow c'tors which pass an argument to just selected
        // derived classes.  Clearly, this is not an optimal solution, but
        // is a necessary evil until a better one is found.
        //--------------------------------------------------------------------
        struct init_first_tag { };
        //--------------------------------------------------------------------
        // Child implementation
        template <class T1, class T2, bool FirstIsEmpty, bool SecondIsEmpty>
        class optimal_parents;
        //--------------------------------------------------------------------
        // Inherit both
        template <class T1, class T2>
        class optimal_parents<T1, T2, false, false>
            : public T1, public T2
        {
        public:
            typedef T1 base1_type;
            typedef T2 base2_type;
        public:
                    optimal_parents(void)           { }

                    template <class U1, class U2>
                    optimal_parents(optimal_parents<U1, U2, false, false> const& rhs)
                        : T1(static_cast<U1 const&>(rhs)), T2(static_cast<U2 const&>(rhs))
                                                    { }

                    template <typename U>
                    optimal_parents(U const& x)
                        : T1(x), T2(x)              { }

                    template <typename U>
                    optimal_parents( U const& x, detail::init_first_tag const&
                                     BOOST_SMART_PTR_DISAMBIGUATOR_TAG )
                        : T1(x)                     { }

                    template <typename U, typename V>
                    optimal_parents(U const& x, V const& y)
                        : T1(x, y), T2(x, y)        { }

                    template <typename U, typename V>
                    optimal_parents(U const& x, V& y)
                        : T1(x, y), T2(x, y)        { }

                    template <typename U, typename V>
                    optimal_parents( U const& x, V& y, detail::init_first_tag const&
                                     BOOST_SMART_PTR_DISAMBIGUATOR_TAG )
                        : T1(x, y)                  { }

            void    swap(optimal_parents& rhs)
            {
                T1::swap(static_cast<T1&>(rhs));
                T2::swap(static_cast<T2&>(rhs));
            }
        };
        //--------------------------------------------------------------------
        // Inherit first
        template <class T1, class T2>
        class optimal_parents<T1, T2, false, true>
            : public T1
        {
        public:
            typedef T1 base1_type;
            typedef T2 base2_type;
        public:
                    optimal_parents(void)           { }

                    template <class U1, class U2>
                    optimal_parents(optimal_parents<U1, U2, false, true> const& rhs)
                        : T1(static_cast<U1 const&>(rhs))
                                                    { U2 u2; T2 t2(u2); (void) t2; }

                    template <typename U>
                    optimal_parents(U const& x)
                        : T1(x)                     { T2 t2(x); (void) t2; }

                    template <typename U>
                    optimal_parents( U const& x, detail::init_first_tag const&
                                     BOOST_SMART_PTR_DISAMBIGUATOR_TAG )
                        : T1(x)                     { }

                    template <typename U, typename V>
                    optimal_parents(U const& x, V const& y)
                        : T1(x, y)                 { T2 t2(x, y); (void) t2; }

                    template <typename U, typename V>
                    optimal_parents(U const& x, V& y)
                        : T1(x, y)                  { T2 t2(x, y); (void) t2; }

                    template <typename U, typename V>
                    optimal_parents( U const& x, V& y, detail::init_first_tag const&
                                     BOOST_SMART_PTR_DISAMBIGUATOR_TAG )
                        : T1(x, y)                  { }

            void    swap(optimal_parents& rhs)
            {
                T1::swap(static_cast<T1&>(rhs));
            }
        };
        //--------------------------------------------------------------------
        // Inherit second
        template <class T1, class T2>
        class optimal_parents<T1, T2, true, false>
            : public T2
        {
        public:
            typedef T1 base1_type;
            typedef T2 base2_type;
        public:
                    optimal_parents(void)           { }

                    template <class U1, class U2>
                    optimal_parents(optimal_parents<U1, U2, true, false> const& rhs)
                        : T2(static_cast<U2 const&>(rhs))
                                                    { U1 u1; T1 t1(u1); (void) t1; }

                    template <typename U>
                    optimal_parents(U const& x)
                        : T2(x)                     { T1 t1(x); (void) t1; }

                    template <typename U>
                    optimal_parents( U const& x, detail::init_first_tag const&
                                     BOOST_SMART_PTR_DISAMBIGUATOR_TAG )
                                                    { T1 t1(x); (void) t1; }

                    template <typename U, typename V>
                    optimal_parents(U const& x, V const& y)
                        : T2(x, y)                  { T1 t1(x, y); (void) t1; }

                    template <typename U, typename V>
                    optimal_parents(U const& x, V& y)
                        : T2(x, y)                  { T1 t1(x, y); (void) t1; }

                    template <typename U, typename V>
                    optimal_parents( U const& x, V& y, detail::init_first_tag const& 
                                     BOOST_SMART_PTR_DISAMBIGUATOR_TAG )
                                                    { T1 t1(x, y); (void) t1; }

            void    swap(optimal_parents& rhs)
            {
                T2::swap(static_cast<T2&>(rhs));
            }
        };
        //--------------------------------------------------------------------
        // Inherit neither
        template <class T1, class T2>
        class optimal_parents<T1, T2, true, true>
        {
        public:
            typedef T1 base1_type;
            typedef T2 base2_type;
        public:
                    optimal_parents(void)           { }

                    template <class U1, class U2>
                    optimal_parents(optimal_parents<U1, U2, true, true> const& rhs)
                                                    { U1 u1; T1 t1(u1); U2 u2; T2 t2(u2); (void) t1; (void) t2; }

                    template <typename U>
                    optimal_parents(U const& x)     { T1 t1(x); T2 t2(x); (void) t1; (void) t2; }

                    template <typename U>
                    optimal_parents( U const& x, detail::init_first_tag const&
                                     BOOST_SMART_PTR_DISAMBIGUATOR_TAG )
                                                    { T1 t1(x); (void) t1; }

                    template <typename U, typename V>
                    optimal_parents(U const& x, V const& y)
                                                    { T1 t1(x, y); T2 t2(x, y); (void) t1; (void) t2; }

                    template <typename U, typename V>
                    optimal_parents(U const& x, V& y)
                                                    { T1 t1(x, y); T2 t2(x, y); (void) t1; (void) t2; }

                    template <typename U, typename V>
                    optimal_parents( U const& x, V& y, detail::init_first_tag const&
                                     BOOST_SMART_PTR_DISAMBIGUATOR_TAG )
                                                    { T1 t1(x, y); (void) t1; }

            void    swap(optimal_parents& rhs)      { }
        };
        //--------------------------------------------------------------------
    }   // namespace detail
    //------------------------------------------------------------------------
    // type generator optimally_inherit
    //------------------------------------------------------------------------
    template <class T1, class T2>
    class optimally_inherit
    {
    public:
        typedef detail::optimal_parents<T1, T2,
            ::boost::is_empty<T1>::value,
            ::boost::is_empty<T2>::value
        > type;
    };
    //------------------------------------------------------------------------
}   // namespace boost
//----------------------------------------------------------------------------
#else  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include "detail/ob_optimally_inherit.hpp"
#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
//----------------------------------------------------------------------------
#endif // BOOST_OPTIMALLY_INHERIT_20020703_HPP

