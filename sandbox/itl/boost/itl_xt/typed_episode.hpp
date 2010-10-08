/*-----------------------------------------------------------------------------+    
Copyright (c) 2007-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
Copyright (c) 1999-2006: Cortex Software GmbH, Kantstrasse 57, Berlin
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
#ifndef BOOST_ITL_TYPED_EPISODE_HPP_HPP_JOFA_011015
#define BOOST_ITL_TYPED_EPISODE_HPP_HPP_JOFA_011015

//JODO #include <boost/itl/interval.hpp>
#include <boost/itl/right_open_interval.hpp>
#include <boost/itl_xt/ordered_type.hpp>

namespace boost{namespace itl
{

/// Serves as a base class for the decomposition of histories in episodes
/**  
    <b>Episoden-Intercace</b>

    Eine Episode besitzt ein Intervall. 
  
    @author  Joachim Faulhaber
*/
template <class TimeT>
class episode_interface
{
public:

    /// virtual dtor: cave leakem
    virtual ~episode_interface(){}

    /// das Intervall der Episode
    //virtual itl::interval<TimeT> interval()const=0; //JODO make IntervalT a template param
    virtual right_open_interval<TimeT> interval()const=0;
};

/// typed_episode is an episode that can be ordered wrt. it's type
/**  
    <b>ein Episode mit Typ dazu</b>

    Die Klasse typed_episode ist nach Typ sortierbar, denn sie 
    implementiert \ref ordered_type. Ausserdem ist es eine Episode, denn
    sie implementiert \ref episode_interface.
  
    @author  Joachim Faulhaber
*/
template <class TimeT, class TypeDomain>
class typed_episode : public ordered_type_base<TypeDomain>, public episode_interface<TimeT>
{
};

}} // namespace itl boost

#endif // BOOST_ITL_TYPED_EPISODE_HPP_HPP_JOFA_011015



