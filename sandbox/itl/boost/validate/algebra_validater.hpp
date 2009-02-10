/*----------------------------------------------------------------------------+
A Law Based Test Automaton 'LaBatea'
Author: Joachim Faulhaber
Copyright (c) 2007-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+----------------------------------------------------------------------------*/
#pragma once

#include <boost/itl/type_traits/is_continuous.hpp>
#include <boost/itl/functors.hpp>
#include <boost/validate/validater/law_validater.hpp>

namespace boost{namespace itl
{
    typedef WeightedNumberGentor<int> ChoiceT;

    class AlgebraValidater
    {
    public:
        virtual ~AlgebraValidater(){}
        // the choice probability, and also the availability of laws is individual to each type
        // Somehow it has to be defined in conjunction to every type. So it is an aspect of
        // type traits.
        virtual void setProfile()=0;
        virtual void validate()=0;
        virtual void addFrequencies(ValidationCounterT&)=0;
        virtual void addViolations(ViolationCounterT&, ViolationMapT&)=0;

        virtual bool hasValidProfile()const{ return true; }

		static int share(int total, int& index, int& rest_shares);
    };

	inline int AlgebraValidater::share(int total, int& index, int& rest_shares)
	{
		BOOST_ASSERT(index_ == index);
		int count = total - index;
		int share = rest_shares / count;
		rest_shares -= share;
		++index;
		return share;
	}

}} // namespace itl boost

