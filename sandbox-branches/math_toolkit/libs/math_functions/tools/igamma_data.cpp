//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/math/tools/ntl.hpp>
#include <boost/test/included/test_exec_monitor.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/tools/test.hpp>
#include <boost/lexical_cast.hpp>
#include <fstream>

#include <boost/math/tools/test_data.hpp>
#include "ntl_rr_lanczos.hpp"

using namespace boost::math::tools;

//
// Force trunctation to float precision of input values:
// we must ensure that the input values are exactly representable
// in whatever type we are testing, or the output values will all
// be thrown off:
//
float external_f;
float force_truncate(const float* f)
{
   external_f = *f;
   return external_f;
}

float truncate_to_float(NTL::RR r)
{
   float f = boost::math::tools::real_cast<float>(r);
   return force_truncate(&f);
}

//
// Our generator takes two arguments, but the second is interpreted
// as an instruction not a value, the second argument won't be placed
// in the output matrix by class test_data, so we add our algorithmically
// derived second argument to the output.
//
struct igamma_data_generator
{
   std::tr1::tuple<NTL::RR, NTL::RR, NTL::RR, NTL::RR, NTL::RR> operator()(NTL::RR a, NTL::RR x)
   {
      // very naively calculate spots:
      NTL::RR z;
      switch((int)real_cast<float>(x))
      {
      case 1:
         z = truncate_to_float((std::min)(NTL::RR(1), a/100));
         break;
      case 2:
         z = truncate_to_float(a / 2);
         break;
      case 3:
         z = truncate_to_float((std::max)(0.9*a, a - 2));
         break;
      case 4:
         z = a;
         break;
      case 5:
         z = truncate_to_float((std::min)(1.1*a, a + 2));
         break;
      case 6:
         z = truncate_to_float(a * 2);
         break;
      case 7:
         z = truncate_to_float((std::max)(NTL::RR(100), a*100));
         break;
      default:
         BOOST_ASSERT(0 == "Can't get here!!");
      }

      //NTL::RR g = boost::math::tgamma(a);
      NTL::RR lg = boost::math::tgamma_lower(a, z);
      NTL::RR ug = boost::math::tgamma(a, z);
      NTL::RR rlg = boost::math::gamma_P(a, z);
      NTL::RR rug = boost::math::gamma_Q(a, z);

      return std::tr1::make_tuple(z, ug, rug, lg, rlg);
   }
};

struct gamma_inverse_generator
{
   std::tr1::tuple<NTL::RR, NTL::RR> operator()(const NTL::RR a, const NTL::RR p)
   {
      NTL::RR x1 = boost::math::gamma_P_inv(a, p);
      NTL::RR x2 = boost::math::gamma_Q_inv(a, p);
      std::cout << "Inverse for " << a << " " << p << std::endl;
      return std::tr1::make_tuple(x1, x2);
   }
};

struct gamma_inverse_generator_a
{
   std::tr1::tuple<NTL::RR, NTL::RR> operator()(const NTL::RR x, const NTL::RR p)
   {
      NTL::RR x1 = boost::math::gamma_P_inva(x, p);
      NTL::RR x2 = boost::math::gamma_Q_inva(x, p);
      std::cout << "Inverse for " << x << " " << p << std::endl;
      return std::tr1::make_tuple(x1, x2);
   }
};


int test_main(int argc, char*argv [])
{
   NTL::RR::SetPrecision(1000);
   NTL::RR::SetOutputPrecision(100);

   bool cont;
   std::string line;

   parameter_info<NTL::RR> arg1, arg2;
   test_data<NTL::RR> data;

   if((argc >= 2) && (std::strcmp(argv[1], "-inverse") == 0))
   {
      std::cout << "Welcome.\n"
         "This program will generate spot tests for the inverse incomplete gamma function:\n"
         "  gamma_P_inv(a, p) and gamma_Q_inv(a, q)\n\n";
      do{
         get_user_parameter_info(arg1, "a");
         get_user_parameter_info(arg2, "p");
         data.insert(gamma_inverse_generator(), arg1, arg2);

         std::cout << "Any more data [y/n]?";
         std::getline(std::cin, line);
         boost::algorithm::trim(line);
         cont = (line == "y");
      }while(cont);
   }
   else if((argc >= 2) && (std::strcmp(argv[1], "-inverse_a") == 0))
   {
      std::cout << "Welcome.\n"
         "This program will generate spot tests for the inverse incomplete gamma function:\n"
         "  gamma_P_inva(a, p) and gamma_Q_inva(a, q)\n\n";
      do{
         get_user_parameter_info(arg1, "x");
         get_user_parameter_info(arg2, "p");
         data.insert(gamma_inverse_generator_a(), arg1, arg2);

         std::cout << "Any more data [y/n]?";
         std::getline(std::cin, line);
         boost::algorithm::trim(line);
         cont = (line == "y");
      }while(cont);
   }
   else
   {
      arg2 = make_periodic_param(NTL::RR(1), NTL::RR(8), 7);
      arg2.type |= boost::math::tools::dummy_param;

      std::cout << "Welcome.\n"
         "This program will generate spot tests for the incomplete gamma function:\n"
         "  gamma(a, z)\n\n";

      do{
         get_user_parameter_info(arg1, "a");
         data.insert(igamma_data_generator(), arg1, arg2);

         std::cout << "Any more data [y/n]?";
         std::getline(std::cin, line);
         boost::algorithm::trim(line);
         cont = (line == "y");
      }while(cont);
   }

   std::cout << "Enter name of test data file [default=igamma_data.ipp]";
   std::getline(std::cin, line);
   boost::algorithm::trim(line);
   if(line == "")
      line = "igamma_data.ipp";
   std::ofstream ofs(line.c_str());
   write_code(ofs, data, "igamma_data");
   
   return 0;
}

