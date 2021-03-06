/*-----------------------------------------------------------------------------+    
A Law Based Test Automaton 'LaBatea'
Author: Joachim Faulhaber
Copyright (c) 2007-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_VALIDATE_DRIVER_BIT_COLLECTOR_DRIVER_HPP_JOFA_091009
#define BOOST_VALIDATE_DRIVER_BIT_COLLECTOR_DRIVER_HPP_JOFA_091009

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <boost/icl/map.hpp>
#include <boost/icl/interval_map.hpp>
#include <boost/icl/split_interval_map.hpp>
#include <boost/icl_xt/bits.hpp>
#include <boost/validate/validater/collector_validater.hpp>
#include <boost/validate/driver/icl_driver.hpp>
#include <boost/validate/utility.hpp>

namespace boost{namespace icl
{
    
    class bit_collector_driver : public icl_driver
    {
    public:
        bit_collector_driver() { setProfile(); }

        void setProfile()
        {
            setValid(true);
            _rootChoice.setSize(RootType::Types_size);
            _rootChoice.setMaxWeights(100);
            _rootChoice[RootType::icl_set]               = 0;
            _rootChoice[RootType::interval_set]          = 0;
            _rootChoice[RootType::separate_interval_set] = 0;
            _rootChoice[RootType::split_interval_set]    = 0;
            _rootChoice[RootType::icl_map]               = 33;
            _rootChoice[RootType::interval_map]          = 33;
            _rootChoice[RootType::split_interval_map]    = 34;
            setRootTypeNames();
            _rootChoice.init();

            _domainChoice.setSize(DomainType::DomainTypes_size);
            _domainChoice.setMaxWeights(100);
            _domainChoice[DomainType::Int]               = 100;
            _domainChoice[DomainType::Double]            = 0;
            setDomainTypeNames();
            _domainChoice.init();

            _codomainChoice.setSize(CodomainType::CodomainTypes_size);
            _codomainChoice.setMaxWeights(100);
            _codomainChoice[CodomainType::Int]           = 100;
            _codomainChoice[CodomainType::Double]        = 0;
            _codomainChoice[CodomainType::set_int]       = 0;
            setCodomainTypeNames();
            _codomainChoice.init();

            _identityHandlerChoice.setSize(IdentityHandlerType::IdentityHandlerTypes_size);
            _identityHandlerChoice.setMaxWeights(100);
            _identityHandlerChoice[IdentityHandlerType::partial_absorber] = 50;
            _identityHandlerChoice[IdentityHandlerType::partial_enricher] = 50;
            _identityHandlerChoice[IdentityHandlerType::total_absorber]   = 0;
            _identityHandlerChoice[IdentityHandlerType::total_enricher]   = 0;
            setIdentityHandlerTypeNames();
            _identityHandlerChoice.init();

            if(!_rootChoice.is_consistent())
            {
                setValid(false);
                std::cout << _rootChoice.inconsitencyMessage("bit_collector_driver::setProfile()") << std::endl;
            }

            if(!_domainChoice.is_consistent())
            {
                setValid(false);
                std::cout << _domainChoice.inconsitencyMessage("bit_collector_driver::setProfile()") << std::endl;
            }

            if(!_codomainChoice.is_consistent())
            {
                setValid(false);
                std::cout << _codomainChoice.inconsitencyMessage("bit_collector_driver::setProfile()") << std::endl;
            }

            if(!_identityHandlerChoice.is_consistent())
            {
                setValid(false);
                std::cout << _identityHandlerChoice.inconsitencyMessage("bit_collector_driver::setProfile()") << std::endl;
            }

        }


        concept_validater* chooseValidater()
        {
            int rootChoice         = _rootChoice.some();
            int identityHandlerChoice  = _identityHandlerChoice.some();

            switch(rootChoice)
            {
            ////-----------------------------------------------------------------
            case RootType::icl_map: {
                switch(identityHandlerChoice) {
                case IdentityHandlerType::partial_absorber: 
                    return new collector_validater< icl::map<int, icl::bits8, partial_absorber, std::less, inplace_bit_add, inplace_bit_and> >;
                case IdentityHandlerType::partial_enricher: 
                    return new collector_validater< icl::map<int, icl::bits32, partial_enricher, std::less, inplace_bit_add, inplace_bit_and> >;
                default: return choiceError(ICL_LOCATION("\nRootType::icl_map: identityHandlerChoice:\n"), identityHandlerChoice, _identityHandlerChoice);
                }//switch identityHandlerChoice
            }//case icl_map 
            ////-----------------------------------------------------------------
            case RootType::interval_map: {
                switch(identityHandlerChoice) {
                case IdentityHandlerType::partial_absorber: 
                    return new collector_validater<interval_map<int, icl::bits64, partial_absorber, std::less, inplace_bit_add, inplace_bit_and> >;
                case IdentityHandlerType::partial_enricher: 
                    return new collector_validater<interval_map<int, icl::bits16, partial_enricher, std::less, inplace_bit_add, inplace_bit_and> >;
                default: return choiceError(ICL_LOCATION("\nRootType::interval_map: identityHandlerChoice:\n"), identityHandlerChoice, _identityHandlerChoice);
                }//switch identityHandlerChoice
            }//case interval_map 
            ////-----------------------------------------------------------------
            case RootType::split_interval_map: {
                switch(identityHandlerChoice) {
                case IdentityHandlerType::partial_absorber: 
                    return new collector_validater<split_interval_map<int, icl::bits32, partial_absorber, std::less, inplace_bit_add, inplace_bit_and> >;
                case IdentityHandlerType::partial_enricher: 
                    return new collector_validater<split_interval_map<double, icl::bits8, partial_enricher, std::less, inplace_bit_add, inplace_bit_and> >;
                default: return choiceError(ICL_LOCATION("\nRootType::split_interval_map: identityHandlerChoice:\n"), identityHandlerChoice, _identityHandlerChoice);
                }//switch identityHandlerChoice
            }//case split_interval_map 
            //-----------------------------------------------------------------

            default: return choiceError(ICL_LOCATION("rootChoice:\n"), rootChoice, _rootChoice);
            } //switch()

        }

    };


}} // namespace icl boost

#endif // BOOST_VALIDATE_DRIVER_BIT_COLLECTOR_DRIVER_HPP_JOFA_091009
