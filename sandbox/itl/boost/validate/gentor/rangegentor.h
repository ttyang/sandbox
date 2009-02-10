/*----------------------------------------------------------------------------+
Copyright (c) 2007-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
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
+----------------------------------------------------------------------------*/
/* ------------------------------------------------------------------
class IntevalGentor
    A random generator for Sets.
--------------------------------------------------------------------*/
#pragma once

#include <boost/itl/interval.hpp>
#include <boost/itl_xt/gentorit.hpp>
#include <boost/itl_xt/numbergentor.hpp>

namespace boost{namespace itl
{
    //JODO: RangeGentor is similat to ItvGentorT. RangeGentor might be replaced by ItvGentorT
    // with some modifications applied to ItvGentorT.

    template <class Type> 
    class RangeGentor: public RandomGentorAT<interval<Type> >
    {
    public:
        virtual void some(interval<Type>& x);
        interval<Type> last()const;

        void setLowerBoundRange(int lwb, int upb)
        { setLowerBoundRange(rightopen_interval(lwb,upb)); }
        void setLowerBoundRange(const interval<int>& range)
        { BOOST_ASSERT(range.is_rightopen()||range.is_closed()); _lwbGentor.setRange(range); }

        void setUpperBoundRange(int lwb, int upb)
        { setUpperBoundRange(rightopen_interval(lwb,upb)); }
        void setUpperBoundRange(const interval<int>& range)
        { BOOST_ASSERT(range.is_rightopen()||range.is_closed()); _upbGentor.setRange(range); }

    private:
        NumberGentorT<Type>   _lwbGentor;
        NumberGentorT<Type>   _upbGentor;
        interval<Type>          _last;
    };

    template <class Type> 
    void RangeGentor<Type>::some(interval<Type>& x)
    {
        Type lwb, upb;
        _lwbGentor.some(lwb);
        _upbGentor.some(upb);
        _last = rightopen_interval(lwb, upb);
        x = _last;
    }

    template <class Type> 
    interval<Type> RangeGentor<Type>::last()const
    {
        return _last;
    }

}} // namespace itl boost



