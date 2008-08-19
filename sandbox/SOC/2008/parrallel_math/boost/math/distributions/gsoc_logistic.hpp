
// Copyright John Maddock 
// Copyright Paul A. Bristow 
// Copyright Gautam Sewani

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)









#include <boost/math/distributions/fwd.hpp>
#include <boost/math/distributions/detail/common_error_handling.hpp>
#include <boost/math/distributions/complement.hpp>
#include <boost/math/special_functions/log1p.hpp>

#include <cmath>
#include <boost/math/constants/constants.hpp>
#include <utility>

namespace boost { namespace math { 
    template <class RealType = double, class Policy = policies::policy<> >
    class logistic_distribution
    {
    public:
      typedef RealType value_type;
      typedef Policy policy_type;
      
      logistic_distribution(RealType location=0, RealType scale=1) // Constructor.
        : m_location(location), m_scale(scale) 
      {
        static const char* function = "boost::math::logistic_distribution<%1%>::logistic_distribution";
        
        RealType result;
        detail::check_scale(function, scale, &result, Policy());
        detail::check_location(function, location, &result, Policy());
      }
      // Accessor functions.
      RealType scale()const
      {
        return m_scale;
      }
      
      RealType location()const
      {
        return m_location;
      }
    private:
      // Data members:
      RealType m_location;  // distribution location aka mu.
      RealType m_scale;  // distribution scale aka s.
    }; // class logistic_distribution
    
    
    typedef logistic_distribution<double> logistic;
    
    template <class RealType, class Policy>
    inline const std::pair<RealType, RealType> range(const logistic_distribution<RealType, Policy>& /* dist */)
    { // Range of permissible values for random variable x.
      using boost::math::tools::max_value;
      return std::pair<RealType, RealType>(-max_value<RealType>(), max_value<RealType>()); // - to + infinity
    }
    
    template <class RealType, class Policy>
    inline const std::pair<RealType, RealType> support(const logistic_distribution<RealType, Policy>& dist)
    { // Range of supported values for random variable x.
      // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
      using boost::math::tools::max_value;
      return std::pair<RealType, RealType>(-max_value<RealType>(), max_value<RealType>()); // - to + infinity
    }
    
    
    template <class RealType, class Policy>
    inline RealType pdf(const logistic_distribution<RealType, Policy>& dist, const RealType& x)
    {
      RealType scale = dist.scale();
      RealType location = dist.location();
      
      static const char* function = "boost::math::pdf(const logistic_distribution<%1%>&, %1%)";
      if((boost::math::isinf)(x))
        {
          return 0; // pdf + and - infinity is zero.
        }
      
      
      RealType result;
      if(false == detail::check_scale(function, scale , &result, Policy()))
        {
          return result;
        }
      if(false == detail::check_location(function, location, &result, Policy()))
        {
          return result;
        }
      if(false == detail::check_x(function, x, &result, Policy()))
        {
          return result;
        }
      
      
      RealType exp_term=exp((location-x)/scale);
      return ( exp_term )/ ( scale*(1+exp_term)*(1+exp_term ) );
      
      
    } 
    
    template <class RealType, class Policy>
    inline RealType cdf(const logistic_distribution<RealType, Policy>& dist, const RealType& x)
    {
      RealType scale = dist.scale();
      RealType location = dist.location();
      RealType result; // of checks.
      static const char* function = "boost::math::cdf(const logistic_distribution<%1%>&, %1%)";
      if(false == detail::check_scale(function, scale, &result, Policy()))
        {
          return result;
        }
      
      if(false == detail::check_location(function, location, &result, Policy()))
        {
          return result;
        }
      
      if((boost::math::isinf)(x))
        {
          if(x < 0) return 0; // -infinity
          return 1; // + infinity
        }
      
      if(false == detail::check_x(function, x, &result, Policy()))
        {
          return result;
        }
      
      RealType power=(location-x)/scale;
      return 1/( 1+exp(power) ); 
    } 
    
    template <class RealType, class Policy>
    inline RealType quantile(const logistic_distribution<RealType, Policy>& dist, const RealType& p)
    {
      RealType location = dist.location();
      RealType scale = dist.scale();
      
      static const char* function = "boost::math::quantile(const logistic_distribution<%1%>&, %1%)";
      
      RealType result;
      if(false == detail::check_scale(function, scale, &result, Policy()))
        return result;
      if(false == detail::check_location(function, location, &result, Policy()))
        return result;
      if(false == detail::check_probability(function, p, &result, Policy()))
        return result;
      
      
      if(p == 0)
        {
          
          result=policies::raise_underflow_error<RealType>(function,"probability argument is 0, must be >0 and <1",Policy());
          return result;
        }
      if(p == 1)
        {
          result=policies::raise_overflow_error<RealType>(function,"probability argument is 0, must be >0 and <1",Policy());
          return result;
          
        }
       //Expressions to try
       //return location+scale*log(p/(1-p));
       //return location+scale*log1p((2*p-1)/(1-p));
      
      //return location - scale*log( (1-p)/p);
       //return location - scale*log1p((1-2*p)/p);

      //return -scale*log(1/p-1) + location;
      return -scale*log1p(1/p-2)+location;
        
     } // RealType quantile(const logistic_distribution<RealType, Policy>& dist, const RealType& p)
    
    template <class RealType, class Policy>
    inline RealType cdf(const complemented2_type<logistic_distribution<RealType, Policy>, RealType>& c)
    {
      RealType location = c.dist.location();
      RealType scale = c.dist.scale();
      RealType x = c.param;
      static const char* function = "boost::math::cdf(const complement(logistic_distribution<%1%>&), %1%)";
      
      if((boost::math::isinf)(x))
        {
          if(x < 0) return 1; // cdf complement -infinity is unity.
          return 0; // cdf complement +infinity is zero
        }
      RealType result;
      if(false == detail::check_scale(function, scale, &result, Policy()))
        return result;
      if(false == detail::check_location(function, location, &result, Policy()))
        return result;
      if(false == detail::check_x(function, x, &result, Policy()))
        return result;
      
      RealType power=(x-location)/scale;
      return 1/( 1+exp(power) ); 
      
    } 
      template <class RealType, class Policy>
  inline RealType quantile(const complemented2_type<logistic_distribution<RealType, Policy>, RealType>& c)
  {
   RealType scale = c.dist.scale();
   RealType location = c.dist.location();
   static const char* function = "boost::math::quantile(const complement(logistic_distribution<%1%>&), %1%)";
   RealType result;
   if(false == detail::check_scale(function, scale, &result, Policy()))
      return result;
   if(false == detail::check_location(function, location, &result, Policy()))
      return result;
   RealType q = c.param;
   if(false == detail::check_probability(function, q, &result, Policy()))
      return result;
   using boost::math::tools::max_value;


      if(q == 1)
        {
          result=policies::raise_underflow_error<RealType>(function,"probability argument is 0, must be >0 and <1",Policy());
          return result;
          
        }
      if(q == 0)
        {
          result=policies::raise_overflow_error<RealType>(function,"probability argument is 0, must be >0 and <1",Policy());
          return result;
          
        }
   //Expressions to try 
   return location+scale*log((1-q)/q);
   //return location+scale*log1p((1-2*q)/(q));
   
   //return location-scale*log(q/(1-q));
   //return location-scale*log1p((2*q-1)/(1-q));
   
   //return location+scale*log(1/q-1);
   //return location+scale*log1p(1/q-2);

  } 
    
    template <class RealType, class Policy>
    inline RealType mean(const logistic_distribution<RealType, Policy>& dist)
    {
      return dist.location();
    } // RealType mean(const logistic_distribution<RealType, Policy>& dist)
    
    template <class RealType, class Policy>
    inline RealType variance(const logistic_distribution<RealType, Policy>& dist)
    {
      BOOST_MATH_STD_USING
      RealType scale = dist.scale();
      return boost::math::constants::pi<RealType>()*boost::math::constants::pi<RealType>()*scale*scale/3;
      
    } // RealType variance(const logistic_distribution<RealType, Policy>& dist)
    
    template <class RealType, class Policy>
    inline RealType mode(const logistic_distribution<RealType, Policy>& dist)
    {
      
      return dist.location();
    }
    
    template <class RealType, class Policy>
    inline RealType median(const logistic_distribution<RealType, Policy>& dist)
    {
      
      return dist.location();
    }
    template <class RealType, class Policy>
    inline RealType skewness(const logistic_distribution<RealType, Policy>& dist)
    {
      
      return 0;
    } // RealType skewness(const logistic_distribution<RealType, Policy>& dist)
    
    template <class RealType, class Policy>
    inline RealType kurtosis_excess(const logistic_distribution<RealType, Policy>& dist)
    {
      
      return static_cast<RealType>(6)/5; 
    } // RealType kurtosis_excess(const logistic_distribution<RealType, Policy>& dist)
  }}
