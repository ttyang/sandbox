

#include <boost/random/acml/engine.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/acml/variate_generator_specialization_0x_distributions.hpp>
#include <random>
#include <vector>

namespace boost {

namespace random {

template <long genid, bool single, long subid>
class variate_generator< boost::random::acml::engine<genid,single,subid>, std::uniform_int_distribution<int> >
{
	public:
	void test(){}
};

}
}

int main()
{
	boost::variate_generator<boost::random::acml::engine<1,false,1>,std::uniform_int_distribution<int> > vgen;
	vgen.test();

	std::vector<double> vec(100);

	std::cauchy_distribution<double> dist;
	boost::random::acml::mt19937 gen;

	boost::variate_generator<boost::random::acml::mt19937, std::cauchy_distribution<double> > vgen1(gen,dist);

	vgen1(vec.begin(), vec.end());

	boost::generate(vec.begin(), vec.end(), vgen1);
	

	return 0;
}


