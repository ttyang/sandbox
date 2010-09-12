/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ITL_DETAIL_INTERVAL_MORPHISM_HPP_JOFA_080315
#define BOOST_ITL_DETAIL_INTERVAL_MORPHISM_HPP_JOFA_080315

#include <boost/itl/detail/notate.hpp>
namespace boost{namespace itl
{
    namespace segmental
    {
        template <typename ElementContainerT, typename IntervalContainerT>
        void atomize(ElementContainerT& result, const IntervalContainerT& src)
        {
            ITL_const_FORALL(typename IntervalContainerT, itv_, src)
            {
                const typename IntervalContainerT::key_type& itv   = IntervalContainerT::key_value(itv_);
                typename IntervalContainerT::codomain_type   coval = IntervalContainerT::co_value(itv_);

                for(typename IntervalContainerT::domain_type element = first(itv); element <= last(itv); ++element)
                {
                    insert(result, ElementContainerT::make_value(element, coval));
                    //CL result.insert(ElementContainerT::make_element(element, coval));
                }
            }
        }

        template <typename IntervalContainerT, typename ElementContainerT>
        void cluster(IntervalContainerT& result, const ElementContainerT& src)
        {
			typedef typename IntervalContainerT::key_type key_type;
            ITL_const_FORALL(typename ElementContainerT, element_, src)
            {
                const typename ElementContainerT::key_type&  key  = ElementContainerT::key_value(element_);
                const typename ElementContainerT::data_type& data = ElementContainerT::co_value(element_);

                result += IntervalContainerT::make_value(key_type(key), data);
            }
        }

        template <typename AtomizedType, typename ClusteredType>
        struct atomizer
        {
            void operator()(AtomizedType& atomized, const ClusteredType& clustered)
            {
                segmental::atomize(atomized, clustered);
            }
        };

        template <typename ClusteredType, typename AtomizedType>
        struct clusterer
        {
            void operator()(ClusteredType& clustered, const AtomizedType& atomized)
            {
                segmental::cluster(clustered, atomized);
            }
        };

        template <typename JointType, typename SplitType>
        struct joiner
        {
            void operator()(JointType& joint, SplitType& split)
            {
				itl::join(split);
                ITL_FORALL(typename SplitType, split_, split)
                    joint.insert(*split_);
            }
        };

        template <typename AbsorberType, typename EnricherType>
        struct neutron_absorber
        {
            void operator()(AbsorberType& absorber, EnricherType& enricher)
            {
				itl::absorb_neutrons(enricher);
                ITL_FORALL(typename EnricherType, enricher_, enricher)
                    absorber.insert(*enricher_);
            }
        };

    } // namespace Interval


    template<> 
    inline std::string binary_template_to_string<segmental::atomizer>::apply() { return "@"; }
    template<> 
    inline std::string binary_template_to_string<segmental::clusterer>::apply() { return "&"; }
    template<> 
    inline std::string binary_template_to_string<segmental::joiner>::apply() { return "j"; }
    template<> 
    inline std::string binary_template_to_string<segmental::neutron_absorber>::apply() { return "a0"; }
}} // namespace boost itl

#endif // BOOST_ITL_DETAIL_INTERVAL_MORPHISM_HPP_JOFA_080315



