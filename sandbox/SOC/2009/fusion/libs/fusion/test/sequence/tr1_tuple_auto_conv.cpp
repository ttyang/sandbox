// Copyright Christopher Schmidt 2009.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//TODO Authors???

//TODO!!!
#include <boost/tr1/memory.hpp>
#include <boost/tr1/tuple.hpp>
#include <boost/any.hpp>
#include <iostream>

//TODO cschmidt: In C++0x this won't work any more?!

namespace Core
{
    class AutoConverter
    {
        std::tr1::shared_ptr<boost::any> t_;

    public:
        AutoConverter(std::tr1::shared_ptr<boost::any> const& t)
          : t_(t)
        {}

        template <typename C>
        operator C ()
        {
            try
            {
                boost::any & a = (*t_);

                return boost::any_cast<C>(a);
            }
            catch(boost::bad_any_cast & e)
            {
                std::cerr << "Internal conversion bug: "
                          << "Failed to convert data holder to "
                          << typeid(C).name() << "\n"
                          << e.what()
                          << std::endl;

                C c = C();
                return c;
            }
        }
    };

    inline AutoConverter Demo()
    {
        std::tr1::shared_ptr<boost::any> p_result
            (new boost::any(std::tr1::make_tuple(1, 2, 3, 4)));
        return p_result;
    }
} // namespace Core


int main(int argc, char* argv[])
{
    //std::tr1::tuple<int, int, int, int> test = Core::Demo();
    return 0;
}

