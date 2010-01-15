///////////////////////////////////////////////////////////////////////////////
// accumulator::statistics::empirical_distribution::count.hpp     			 //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_EMPIRICAL_DISTRIBUTION_COUNT_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_EMPIRICAL_DISTRIBUTION_COUNT_HPP_ER_2010
#include <map>
#include <functional>

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/bool.hpp>

#include <boost/range.hpp>

#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/parameters/accumulator.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>

#include <boost/statistics/detail/non_parametric/empirical_distribution/ordered_sample.hpp>

namespace boost { 
namespace statistics{
namespace detail{
namespace empirical_distribution{

namespace impl{

	template<typename Int,bool Cum>
	class count : public boost::accumulators::accumulator_base{
		typedef std::less<Int> comp_;
		typedef std::size_t size_;
        typedef boost::accumulators::dont_care dont_care_;

        public:

		typedef size_ result_type;

		count(dont_care_){}

		void operator()(dont_care_){}
		
        template<typename Args>
        result_type result(const Args& args)const{
        	Int key 
            	= args[boost::accumulators::sample];
        	typedef typename boost::mpl::bool_<Cum> is_cum_;
            typedef statistics::detail::empirical_distribution
            	::tag::ordered_sample tag_;
        	return this->result_impl(
            	boost::accumulators::extract_result<tag_>(
                	args[boost::accumulators::accumulator]
                ),
                key,
                is_cum_()
            ); 
        }

		private:
		
        template<typename Map,typename N>
		result_type result_impl(
        	Map& map,
            const N& key,
            boost::mpl::bool_<false> cum
        )const{
        	return (map[key]); 
        }

        template<typename Map,typename N>
		result_type result_impl(
        	Map& map, 
            const N& key,
            boost::mpl::bool_<true> cum
        )const{
        	return std::for_each(
            	boost::begin(map),
                map.upper_bound(key),
            	accumulator()
            ).value; 
        }

		struct accumulator{
        	mutable size_ value;
        	
            accumulator():value(0){}
			accumulator(const accumulator& that)
            	:value(that.value){}
            
            template<typename Data>
            void operator()(const Data& data)const{
            	value += data.second;
            }
        
        };
	};
    
}

namespace tag
{
	template<bool Cum>
    struct count
      : boost::accumulators::depends_on<
      	statistics::detail
        	::empirical_distribution::tag::ordered_sample
    >
    {

// TODO compile error
//      typedef statistics::detail::accumulator::empirical_distribution
//      	impl::count<boost::mpl::_1,Cum> impl;
// must explicitly have:        
        
        struct impl{
        	template<typename Int,typename W>
            struct apply{
            	typedef statistics::detail::empirical_distribution
                	::impl::count<Int,Cum> type;
            };
        };
    };
}

namespace extract
{

  	template<bool Cum,typename AccumulatorSet,typename Int>
	typename boost::mpl::apply<
		AccumulatorSet,
        boost::statistics::detail
        	::empirical_distribution::tag::count<Cum>
    >::type::result_type
  	count(AccumulatorSet const& acc,const Int& i)
    {
    	typedef boost::statistics::detail
        	::empirical_distribution::tag::count<Cum> the_tag;
        return boost::accumulators::extract_result<the_tag>(
            acc,
            (boost::accumulators::sample = i)
        );
  	}

}

using extract::count;

}// empirical_distribution
}// detail
}// statistics
}// boost

#endif
