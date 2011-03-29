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

#include <boost/validate/icl/functors.hpp>
#include <boost/validate/laws/function_equality.hpp>
#include <boost/validate/validater/law_validater.hpp>
#include <boost/validate/validater/concept_validater.hpp>

namespace boost{namespace icl
{

    template <typename SourceT, typename TargetT>
    class function_equality_validater : public concept_validater
    {
    public:
        enum Laws 
        { 
            insertion_loop_hint,
            insertion_loop_copy,
            addition_loop_hint,
            addition_loop_copy,
            Laws_size 
        };

        function_equality_validater() {setProfile();}

        void setProfile()
        {
            const int volume = 100;
            _lawChoice.setSize(Laws_size);
            _lawChoice.setMaxWeights(volume);
            _lawChoice[insertion_loop_hint]     = 25;
            _lawChoice[insertion_loop_copy]     = 25;
            _lawChoice[addition_loop_hint]      = 25;
            _lawChoice[addition_loop_copy]      = 25;
            _lawChoice.init();
        }


        LawValidaterI* chooseValidater()
        {
            switch(_lawChoice.some())
            {
            case insertion_loop_hint: return new LawValidater<FunctionEquality<SourceT, TargetT, base_insertion, hint_insertion>, RandomGentor>();
            case insertion_loop_copy: return new LawValidater<FunctionEquality<SourceT, TargetT, base_insertion, copy_insertion>, RandomGentor>();
            case addition_loop_hint:  return new LawValidater<FunctionEquality<SourceT, TargetT, base_addition,  hint_addition>,  RandomGentor>();
            case addition_loop_copy:  return new LawValidater<FunctionEquality<SourceT, TargetT, base_addition,  copy_addition>,  RandomGentor>();
            default: return NULL;
            }
        }

    private:
        ChoiceT        _lawChoice;
    }; //class function_equality_validater



}} // namespace icl boost
