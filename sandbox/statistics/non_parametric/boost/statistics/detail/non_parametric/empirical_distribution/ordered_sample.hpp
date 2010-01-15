///////////////////////////////////////////////////////////////////////////////
// accumulator::statistics::empirical_distribution::ordered_sample.hpp     	 //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_EMPIRICAL_DISTRIBUTION_ORDERED_SAMPLE_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_EMPIRICAL_DISTRIBUTION_ORDERED_SAMPLE_HPP_ER_2010
#include <map>
#include <functional>

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/apply.hpp>

#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/parameters/accumulator.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>

namespace boost { 
namespace statistics{
namespace detail{
namespace empirical_distribution{

namespace impl{

	template<typename Int>
	class ordered_sample 
    		: public boost::accumulators::accumulator_base{
		typedef std::less<Int> comp_;
		typedef std::size_t size_;
        typedef boost::accumulators::dont_care dont_care_;
        typedef std::map<Int,size_,comp_> map_;

        public:

		typedef size_ size_type;

		// non-const because map::operator[](key) returns a non-const
		typedef map_& result_type;

		ordered_sample(dont_care_){}

		template<typename Args>
		void operator()(const Args& args){
        	++(this->freq[args[boost::accumulators::sample]]);
        }
		
		// Returns the entire distribution, represented by a map
        result_type result(dont_care_)const{
        	return (this->freq); 
        }

		private:
        mutable map_ freq;
	};
    
}

namespace tag
{
    struct ordered_sample
      : boost::accumulators::depends_on<>
    {
      typedef statistics::detail::empirical_distribution::
      	impl::ordered_sample<boost::mpl::_1> impl;
    };
}

namespace extract
{

  	template<typename AccumulatorSet>
	typename boost::mpl::apply<
		AccumulatorSet,
        boost::statistics::detail::empirical_distribution
        	::tag::ordered_sample
    >::type::result_type
  	ordered_sample(AccumulatorSet const& acc)
    {
    	typedef boost::statistics::detail::empirical_distribution
    		::tag::ordered_sample the_tag;
        return boost::accumulators::extract_result<the_tag>(acc);
  	}

}

using extract::ordered_sample;

}// empirical_distribution
}// detail
}// statistics
}// boost

#endif