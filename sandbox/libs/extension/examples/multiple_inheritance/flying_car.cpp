/*
 * Boost.Extension / multiple inheritance example (flying car)
 *
 * (C) Copyright Jeremy Pack 2007
 * Distributed under the Boost Software License, Version 1.0. (See             
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/ for latest version.
 */


/* The following lines are only necessary because when
are linking to this dll at compile time with another
dll on Windows. As such, standard __declspec stuff
is required.

This example is something of a special case - normally
these types of macros are not necessary for classes 
- see the FAQ.
  */
#include <boost/extension/extension.hpp>
#include <string>
#define BOOST_EXTENSION_FLYING_CAR_DECL BOOST_EXTENSION_EXPORT_DECL


#include "flying_car.hpp"
#include <boost/extension/factory_map.hpp>

std::string flying_car::list_capabilities()
{
  return car::list_capabilities() + plane::list_capabilities() 
    + "\nIt takes off from your driveway";
}

extern "C" void BOOST_EXTENSION_EXPORT_DECL 
extension_export(boost::extensions::factory_map & z)
{
  z.get<vehicle, 
    std::string>()["A flying car exported as a vehicle"].set<flying_car>();
  z.get<plane, std::string>()["A flying car exported as a plane"]
    .set<flying_car>();
  z.get<car, std::string>()["A flying car exported as a car"].set<flying_car>();
  z.get<flying_car, 
    std::string>()["A flying car exported as a flying car"].set<flying_car>();
}
