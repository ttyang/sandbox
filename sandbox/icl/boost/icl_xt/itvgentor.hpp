/*-----------------------------------------------------------------------------+    
Copyright (c) 2007-2010: Joachim Faulhaber
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
/* ------------------------------------------------------------------
class ItvGentorT
--------------------------------------------------------------------*/
#ifndef __ITVGENTOR_H_JOFA_000714__
#define __ITVGENTOR_H_JOFA_000714__

#undef min
#undef max

#include <boost/icl_xt/gentorit.hpp>
#include <boost/icl_xt/numbergentor.hpp>
#include <boost/icl_xt/seqgentor.hpp>

namespace boost{namespace icl
{

template <class ItvDomTV, class ItvTV=typename icl::interval<ItvDomTV>::type> 
class ItvGentorT: public RandomGentorAT<ItvTV>
{
public:
    typedef typename icl::interval<ItvDomTV>::type range_type;

    virtual void some(ItvTV& x);

    void setRange(const range_type& range)
    { m_valueRange = range; }

    void setValueRange(ItvDomTV low, ItvDomTV up)
    { 
        m_valueRange = icl::construct<range_type>(low, up); 
    }

    void setMaxIntervalLength(ItvDomTV len) { m_maxIntervalLength=len; }
    void setProbDerivation();

private:
    NumberGentorT<ItvDomTV> m_ItvDomTVGentor;

    range_type    m_valueRange;
    ItvDomTV      m_maxIntervalLength;

private:
    template<class IntervalT, bool has_static_bounds>
    struct construct_interval;

    template<class IntervalT>
    struct construct_interval<IntervalT, true>
    {
        typedef typename IntervalT::domain_type domain_type;
        static IntervalT apply(const domain_type& lo, const domain_type& up, 
                               interval_bounds)
        {
            return construct<IntervalT>(lo, up);
        }
    };

    template<class IntervalT>
    struct construct_interval<IntervalT, false>
    {
        typedef typename IntervalT::domain_type domain_type;
        static IntervalT apply(const domain_type& lo, const domain_type& up, 
                               interval_bounds bounds)
        {
            return construct<IntervalT>(lo, up, bounds);
        }
    };
};


template <class ItvDomTV, class ItvTV>
void ItvGentorT<ItvDomTV,ItvTV>::some(ItvTV& x)
{
    NumberGentorT<unsigned> NATGentor;
    ItvDomTV x1   = m_ItvDomTVGentor(m_valueRange);
    icl::bound_type bndTypes = NATGentor(4);
    unsigned upOrDown = NATGentor(1);
    unsigned decideEmpty = NATGentor(2);

    if(decideEmpty==0)
    {        
        ItvDomTV x2   = m_ItvDomTVGentor(m_valueRange);
        x = construct_interval<ItvTV, has_static_bounds<ItvTV>::value>
            ::apply(x1, x1-x2, interval_bounds(bndTypes));
    }
    else if(upOrDown==0) {
        ItvDomTV up 
            = m_ItvDomTVGentor(x1, static_cast<ItvDomTV>((std::min)(m_valueRange.upper(), x1+m_maxIntervalLength)));
        x = construct_interval<ItvTV, has_static_bounds<ItvTV>::value>
            ::apply(x1, up, interval_bounds(bndTypes));
    } else {
        ItvDomTV low 
            = m_ItvDomTVGentor(static_cast<ItvDomTV>((std::max)(m_valueRange.lower(), x1-m_maxIntervalLength)), x1);
        x = construct_interval<ItvTV, has_static_bounds<ItvTV>::value>
            ::apply(low, x1, interval_bounds(bndTypes));
    }
};

}} // namespace icl boost

#endif

