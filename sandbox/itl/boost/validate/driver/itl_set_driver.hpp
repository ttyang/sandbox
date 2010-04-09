/*-----------------------------------------------------------------------------+    
A Law Based Test Automaton 'LaBatea'
Author: Joachim Faulhaber
Copyright (c) 2007-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_VALIDATE_DRIVER_ITL_SET_DRIVER_HPP_JOFA_080405
#define BOOST_VALIDATE_DRIVER_ITL_SET_DRIVER_HPP_JOFA_080405

#include <iostream>
#include <stdio.h>
#include <boost/validate/validater/itl_set_validater.hpp>
#include <boost/validate/driver/itl_driver.hpp>
#include <boost/validate/utility.hpp>

namespace boost{namespace itl
{
    
    class itl_set_driver : public itl_driver
    {
    public:
        itl_set_driver() { setProfile(); }


        void setProfile()
        {
            setValid(true);
            _rootChoice.setSize(RootType::Types_size);
            _rootChoice.setMaxWeights(100);
            _rootChoice[RootType::itl_set]               = 25;
            _rootChoice[RootType::interval_set]          = 25;
            _rootChoice[RootType::separate_interval_set] = 25;
            _rootChoice[RootType::split_interval_set]    = 25;
            _rootChoice[RootType::itl_map]               = 0;
            _rootChoice[RootType::interval_map]          = 0;
            _rootChoice[RootType::split_interval_map]    = 0;
            setRootTypeNames();
            _rootChoice.init();

            _domainChoice.setSize(DomainType::DomainTypes_size);
            _domainChoice.setMaxWeights(100);
            _domainChoice[DomainType::Int]               = 50;
            _domainChoice[DomainType::Double]            = 50;
            setDomainTypeNames();
            _domainChoice.init();

            _codomainChoice.setSize(CodomainType::CodomainTypes_size);
            _codomainChoice.setMaxWeights(100);
            _codomainChoice[CodomainType::Int]           = 100;
            _codomainChoice[CodomainType::Double]        = 0;
            _codomainChoice[CodomainType::set_int]       = 0;
            setCodomainTypeNames();
            _codomainChoice.init();

            _neutronizerChoice.setSize(NeutronHandlerType::NeutronHandlerTypes_size);
            _neutronizerChoice.setMaxWeights(100);
            _neutronizerChoice[NeutronHandlerType::partial_absorber] = 100;
            _neutronizerChoice[NeutronHandlerType::partial_enricher] = 0;
            _neutronizerChoice[NeutronHandlerType::total_absorber]   = 0;
            _neutronizerChoice[NeutronHandlerType::total_enricher]   = 0;
            setNeutronHandlerTypeNames();
            _neutronizerChoice.init();

            if(!_rootChoice.is_consistent())
            {
                setValid(false);
                std::cout << _rootChoice.inconsitencyMessage("itl_set_driver::setProfile()") << std::endl;
            }

            if(!_domainChoice.is_consistent())
            {
                setValid(false);
                std::cout << _domainChoice.inconsitencyMessage("itl_set_driver::setProfile()") << std::endl;
            }

            if(!_codomainChoice.is_consistent())
            {
                setValid(false);
                std::cout << _codomainChoice.inconsitencyMessage("itl_set_driver::setProfile()") << std::endl;
            }

            if(!_neutronizerChoice.is_consistent())
            {
                setValid(false);
                std::cout << _neutronizerChoice.inconsitencyMessage("itl_set_driver::setProfile()") << std::endl;
            }

        }


        algebra_validater* chooseValidater()
        {
            typedef int    intT;
            typedef double doubleT;

            int rootChoice         = _rootChoice.some();
            int domainChoice       = _domainChoice.some();
            //int codomainChoice     = _codomainChoice.some();
            //int neutronizerChoice  = _neutronizerChoice.some();

            switch(rootChoice)
            {
            case RootType::itl_set: {
                    switch(domainChoice) {
                    case DomainType::Int:    return new itl_set_validater<itl::set<int> >; 
                    case DomainType::Double: return new itl_set_validater<itl::set<double> >; 
                    default: return choiceError(ITL_LOCATION("\nRootType::itl_set: domainChoice:\n"), 
                                                domainChoice, _domainChoice);
                    }
                }
            case RootType::interval_set: {
                    switch(domainChoice) {
                    case DomainType::Int:    return new itl_set_validater<interval_set<intT> >;
                    case DomainType::Double: return new itl_set_validater<interval_set<doubleT> >;
                    default: return choiceError(ITL_LOCATION("\nRootType::interval_set: domainChoice:\n"), 
                                                domainChoice, _domainChoice);
                    }
                }
            case RootType::separate_interval_set: {
                    switch(domainChoice) {
                    case DomainType::Int:    return new itl_set_validater<separate_interval_set<intT> >;
                    case DomainType::Double: return new itl_set_validater<separate_interval_set<doubleT> >;
                    default: return choiceError(ITL_LOCATION("\nRootType::separate_interval_set: domainChoice:\n"), 
                                                domainChoice, _domainChoice);
                    }
                 }
            case RootType::split_interval_set: {
                    switch(domainChoice) {
                    case DomainType::Int:    return new itl_set_validater<split_interval_set<intT> >;
                    case DomainType::Double: return new itl_set_validater<split_interval_set<doubleT> >;
                    default: return choiceError(ITL_LOCATION("\nRootType::split_interval_set: domainChoice:\n"), 
                                                domainChoice, _domainChoice);
                    }
                }
            default: return choiceError(ITL_LOCATION("rootChoice:\n"), rootChoice, _rootChoice);
            } //switch()

        }

    };


}} // namespace itl boost

#endif // BOOST_VALIDATE_DRIVER_ITL_SET_DRIVER_HPP_JOFA_080405
