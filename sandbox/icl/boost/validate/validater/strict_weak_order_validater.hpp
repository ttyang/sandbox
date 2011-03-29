/*-----------------------------------------------------------------------------+    
A Law Based Test Automaton 'LaBatea'
Author: Joachim Faulhaber
Copyright (c) 2007-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#pragma once

#include <boost/mpl/bool.hpp> 
#include <boost/mpl/if.hpp> 
#include <boost/icl/type_traits/is_continuous.hpp>
#include <boost/icl/type_traits/has_inverse.hpp>
#include <boost/icl/functors.hpp>
#include <boost/validate/laws/order.hpp>
#include <boost/validate/validater/law_validater.hpp>
#include <boost/validate/validater/concept_validater.hpp>

namespace boost{namespace icl
{

    template <typename Type, template<class>class Relation>
    class strict_weak_order_validater : public concept_validater
    {
    public:
        enum Laws 
        { 
            transitivity,
            asymmetry,
            irreflexivity,
            Laws_size 
        };

        strict_weak_order_validater() {setProfile();}

        void setProfile()
        {
            _lawChoice.setSize(Laws_size);
            _lawChoice.setMaxWeights(100);
            _lawChoice[transitivity]  = 33;
            _lawChoice[asymmetry]     = 33;
            _lawChoice[irreflexivity] = 34;
            _lawChoice.init();
        }


        LawValidaterI* chooseValidater()
        {
            switch(_lawChoice.some())
            {
            case transitivity:   return new LawValidater<Transitivity <Type, Relation >, RandomGentor >;
            case asymmetry:      return new LawValidater<Asymmetry<Type, Relation >, RandomGentor >;
            case irreflexivity:  return new LawValidater<Irreflexivity<Type, Relation >, RandomGentor >;
            default: return NULL;
            }
        }

    private:
        ChoiceT _lawChoice;
    }; //class concept_validater



}} // namespace icl boost
