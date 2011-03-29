/*-----------------------------------------------------------------------------+    
Copyright (c) 2007-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
+-----------------------------------------------------------------------------*/
// This code is based on and inspired by designs of:
// The Loki Library by Andrei Alexandrescu et al.
// See:
// Alexandrescu, Andrei. "Modern C++ Design: Generic Programming and Design 
//     Patterns Applied". Copyright (c) 2001. Addison-Wesley.
// and:
// www.sourceforge.net/projects/loki
//
// Parts of the Loki Library have been used for the Icl Library.
// Those parts from the path <itl/loki> can also be included from the 
// original Loki Library sources.

#ifndef LOKI_TypelistGentor_INC_
#define LOKI_TypelistGentor_INC_

// $Id$


#include <boost/validate/loki/Typelist.h>
#include <boost/validate/loki/TypeTraits.h>
#include <boost/validate/loki/EmptyType.h>


namespace Loki
{
#if defined(_MSC_VER) && _MSC_VER >= 1300
#pragma warning( push ) 
 // 'class1' : base-class 'class2' is already a base-class of 'class3'
#pragma warning( disable : 4584 )
#endif // _MSC_VER

    //JODO This should be integrated into Typelist.h
    namespace TL
    {
        template <class TList1, class TList2> struct StrictEquality;

        template<>
        struct StrictEquality<NullType, NullType>
        {
            enum { Result = true };
        };

        template<typename Head1>
        struct StrictEquality<Typelist<Head1, NullType>, NullType>
        {
            enum { Result = false };
        };

        template<typename Head2>
        struct StrictEquality<NullType, Typelist<Head2, NullType> >
        {
            enum { Result = false };
        };

        template<typename Head, class Tail1, class Tail2>
        struct StrictEquality<Typelist<Head, Tail1>, Typelist<Head, Tail2> >
        {
            enum { Result = StrictEquality<Tail1, Tail2>::Result };
        };

        template<typename Head1, class Tail1, typename Head2, class Tail2>
        struct StrictEquality<Typelist<Head1, Tail1>, Typelist<Head2, Tail2> >
        {
            // Does only match if Head1 is unequal to Head2
            enum { Result = false };
        };

        // --------------------------------------------------------------------
        // Extension for Typelist:
        // template class MapUnaryTemplate
        // MapUnaryTemplate(F, Typelist<T1,...,Tn>) = Typelist<F<T1>,...,F<Tn> >
        // --------------------------------------------------------------------
        template<template<typename TypeT>class UnaryTemplate, typename Typelist>
        struct MapUnaryTemplate;

        template<template<typename TypeT>class UnaryTemplate>
        struct MapUnaryTemplate<UnaryTemplate, NullType>
        {
            typedef NullType Result;
        };

        template<template<typename TypeT>class UnaryTemplate, class Head, class Tail>
        struct MapUnaryTemplate<UnaryTemplate, Typelist<Head, Tail> >
        {
            typedef Typelist<UnaryTemplate<Head>, typename MapUnaryTemplate<UnaryTemplate, Tail>::Result> Result;
        };

    }

    /* class template GenTypeList. It serves to generate homogenious
       Typelists of a given size.    */
    template <class T, unsigned int size> struct GenTypeList;

    template <class T>
    struct GenTypeList<T, 0>
    {
        typedef NullType Result;
    };

    template <class T, unsigned int size>
    struct GenTypeList
    {
        typedef Typelist<T, typename GenTypeList<T, size-1>::Result > Result;
    };


#if defined(_MSC_VER) && _MSC_VER >= 1300
#pragma warning( pop ) 
#endif
}   // namespace Loki

#endif // end file guardian
