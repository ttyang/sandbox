///////////////////////////////////////////////////////////////////////////////
// accumulator::statistics::empirical_distribution::frequency.hpp     	 	 //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_ACCUMULATOR_STATISTICS_FREQUENCY_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_ACCUMULATOR_STATISTICS_FREQUENCY_HPP_ER_2010
#include <iostream> // tmp

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/if.hpp>

#include <boost/parameter/binding.hpp>

#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/parameters/accumulator.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>

#include <boost/statistics/detail/non_parametric/empirical_distribution/count.hpp>

namespace boost { 
namespace statistics{
namespace detail{
namespace empirical_distribution{

namespace impl{

	// Same as count but expressed as a percentage of the sample size
	template<typename T,typename Int,bool Cum>
	class frequency : public boost::accumulators::accumulator_base{
    	
		typedef std::size_t size_;
        typedef boost::accumulators::dont_care dont_care_;

        public:

		frequency(dont_care_){}

		typedef size_ size_type;
		typedef T result_type;

        void operator()(dont_care_)const{}

        template<typename Args>
        result_type result(const Args& args) const
        {
			typedef boost::accumulators::tag::accumulator tag_acc_;        
            typedef boost::parameter::binding<Args,tag_acc_> bind_;
            typedef typename bind_::type cref_;
        	typedef boost::accumulators::tag::count tag_n_;
            cref_ acc = args[boost::accumulators::accumulator];
            size_ i =  boost::statistics::detail::empirical_distribution
            	::extract::count<Cum>( 
            		acc,
                	args[boost::accumulators::sample]
            	);
			size_ n = boost::accumulators::extract_result<tag_n_>( acc );
            return static_cast<T>(i)/static_cast<T>(n);
        }
	};
    
}

namespace tag
{
	template<bool Cum,typename T = double>
    struct frequency
      : boost::accumulators::depends_on<
      	statistics::detail::empirical_distribution::tag::count<Cum>,
        boost::accumulators::tag::count
    >
    {
      	// typedef statistics::detail::accumulator::
      	// 	impl::frequency<T,boost::mpl::_1,Cum> impl;
        
        struct impl{
        	template<typename Int,typename W>
            struct apply{
        		typedef statistics::detail::empirical_distribution
                	::impl::frequency<T,Int,Cum> type;    	
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
        	::empirical_distribution::tag::frequency<Cum>
    >::type::result_type
  	frequency(AccumulatorSet const& acc,const Int& i)
    {
    	typedef double T;
    	typedef boost::statistics::detail::empirical_distribution
    		::tag::frequency<Cum,T> the_tag;
        return boost::accumulators::extract_result<the_tag>(
            acc,
            (boost::accumulators::sample = i)
        );
  	}

}

using extract::frequency;

}// empirical_distribution
}// detail
}// statistics
}// boost

#endif
