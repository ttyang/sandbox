// Boost.Units - A C++ library for zero-overhead dimensional analysis and 
// unit/quantity manipulation and conversion
//
// Copyright (C) 2003-2008 Matthias Christian Schabel
// Copyright (C) 2008 Steven Watanabe
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/** 
\file
    
\brief radar_beam_height.cpp

\detailed
Demonstrate library usage for user test cases suggested by Michael Fawcett.

Output:
@verbatim

//[radar_beam_height_output
radar range        : 300 nmi
earth radius       : 6.37101e+06 m
beam height 1      : 18169.7 m
beam height 2      : 9.81085 nmi
beam height 3      : 18169.7 m
beam height 4      : 9.81085 nmi
beam height approx : 59488.4 ft
beam height approx : 18132.1 m
//]

@endverbatim
**/

#include <iostream>
#include <sstream>
#include <algorithm>

#include <boost/units/conversion.hpp>
#include <boost/units/io.hpp>
#include <boost/units/pow.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/prefixes.hpp>

namespace boost {

namespace units {

//[radar_beam_height_class_snippet_1
namespace nautical {

struct length_base_unit : base_unit<length_base_unit, length_dimension, 1>
{
    static std::string name()       { return "nautical mile"; }
    static std::string symbol()     { return "nmi"; }
};

typedef make_system<length_base_unit>::type system;

/// unit typedefs
typedef unit<length_dimension,system>            length;

static const length mile,miles;

} // namespace nautical

// helper for conversions between nautical length and SI length

} // namespace units

} // namespace boost

BOOST_UNITS_DEFINE_CONVERSION_FACTOR(boost::units::nautical::length_base_unit,
                                     boost::units::SI::meter_base_unit,
                                     double, 1.852e3);

namespace boost {

namespace units {

//]

//[radar_beam_height_class_snippet_2
namespace imperial {

struct length_base_unit : base_unit<length_base_unit, length_dimension, 2>
{
    static std::string name()       { return "foot"; }
    static std::string symbol()     { return "ft"; }
};

typedef make_system<length_base_unit>::type system;

/// unit typedefs
typedef unit<length_dimension,system>            length;

static const length foot,feet;

} // imperial

} // namespace units

} // namespace boost

BOOST_UNITS_DEFINE_CONVERSION_FACTOR(boost::units::imperial::length_base_unit,
                                     boost::units::SI::meter_base_unit,
                                     double, 1.0/3.28083989501312);

namespace boost {

namespace units {

//]

// radar beam height functions
//[radar_beam_height_function_snippet_1
template<class System,typename T>
quantity<unit<length_dimension,System>,T>
radar_beam_height(const quantity<unit<length_dimension,System>,T>& radar_range,
                  const quantity<unit<length_dimension,System>,T>& earth_radius,
                  T k = 4.0/3.0)
{
    return quantity<unit<length_dimension,System>,T>(
        pow<2>(radar_range)/(2.0*k*earth_radius));
}
//]

//[radar_beam_height_function_snippet_2
template<class return_type,class System1,class System2,typename T>
return_type
radar_beam_height(const quantity<unit<length_dimension,System1>,T>& radar_range,
                 const quantity<unit<length_dimension,System2>,T>& earth_radius,
                  T k = 4.0/3.0)
{
    // need to decide which system to use for calculation
    const return_type   rr(radar_range),
                        er(earth_radius);

    return return_type(pow<2>(rr)/(2.0*k*er));
}
//]

//[radar_beam_height_function_snippet_3
quantity<imperial::length>
radar_beam_height(const quantity<nautical::length>& range)
{
    return quantity<imperial::length>(
        pow<2>(range/(1.23*nautical::miles/root<2>(imperial::feet))));
}
//]

} // namespace units

} // namespace boost

int main(void)
{
    using namespace boost::units;
    using namespace boost::units::SI;
    using namespace boost::units::nautical;

    std::stringstream sstream1, sstream2;
    
    //[radar_beam_height_snippet_1
    const quantity<nautical::length> radar_range(300.0*miles);
    const quantity<SI::length>       earth_radius(6371.0087714*kilo*meters);
    
    const quantity<SI::length>       beam_height_1(radar_beam_height(quantity<SI::length>(radar_range),earth_radius));
    const quantity<nautical::length> beam_height_2(radar_beam_height(radar_range,quantity<nautical::length>(earth_radius)));
    const quantity<SI::length>       beam_height_3(radar_beam_height< quantity<SI::length> >(radar_range,earth_radius));
    const quantity<nautical::length> beam_height_4(radar_beam_height< quantity<nautical::length> >(radar_range,earth_radius));
    //]
    
    sstream1  << "radar range        : " << radar_range << std::endl
              << "earth radius       : " << earth_radius << std::endl
              << "beam height 1      : " << beam_height_1 << std::endl
              << "beam height 2      : " << beam_height_2 << std::endl
              << "beam height 3      : " << beam_height_3 << std::endl
              << "beam height 4      : " << beam_height_4 << std::endl
              << "beam height approx : " << radar_beam_height(radar_range)
              << std::endl
              << "beam height approx : "
              << quantity<SI::length>(radar_beam_height(radar_range))
              << std::endl << std::endl;
    
    sstream2 << "radar range        : 300 nmi" << std::endl;
    sstream2 << "earth radius       : " << 6371008.7714 << " m" << std::endl;
    sstream2 << "beam height 1      : " << 18169.690884692 << " m" << std::endl;
    sstream2 << "beam height 2      : " << 9.81084820987694 << " nmi" << std::endl;
    sstream2 << "beam height 3      : " << 18169.6908846921 << " m" << std::endl;
    sstream2 << "beam height 4      : " << 9.81084820987694 << " nmi" << std::endl;
    sstream2 << "beam height approx : " << 59488.3997620464 << " ft" << std::endl;
    sstream2 << "beam height approx : " << 18132.0642474718 << " m" << std::endl;
    sstream2 << std::endl;

    std::string str1(sstream1.str());
    std::string str2(sstream2.str());

    std::cout << str1;
    
    if(str1 == str2) 
    {
        return(0);
    } 
    else 
    {
        std::cout << std::endl << str2 << std::endl;
        
        if(str1.size() < str2.size()) 
        {
            std::string::iterator iter =
                std::mismatch(str1.begin(), str1.end(), str2.begin()).first;
            
            std::cout << iter - str1.begin() << std::endl;
            std::cout << std::count(str1.begin(), iter, '\n') << std::endl;
        } 
        else 
        {
            std::string::iterator iter =
                std::mismatch(str2.begin(), str2.end(), str1.begin()).first;
            
            std::cout << iter - str2.begin() << std::endl;
            std::cout << std::count(str2.begin(), iter, '\n') << std::endl;
        }
        
        return(-1);
    }
}
