/**
 *  @file   static_vector_example.cpp
 *  @date   Aug 14, 2011
 *  @author Andrew Hundt <ATHundt@gmail.com>
 *
 *  (C) 2011-2012 Andrew Hundt <ATHundt@gmail.com>
 *
 *  Distributed under the Boost Software License, Version 1.0. (See
 *  accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @brief  static_vector_example.cpp demonstrates the use of boost::container::static_vector
 *
 */
 
//[static_vector_example_cpp

// static_vector_example.cpp

#include "boost/container/static_vector.hpp"

int main(int argc, char** argv){
  
  // static_vector of ints, fixed capacity: 3
  boost::container::static_vector<int,3> three; // size: 0

  three.push_back(1);    // size: 1
  three.push_back(2);    // size: 2
  three.push_back(3);    // size: 3
  
  //three.reserve(4);    // no effect, fixed capacity: 3
  //three.push_back(3);  // size: 4, undefined behavior
  
  three.pop_back();      // size: 2
  three.shrink_to_fit(); // no effect, fixed capacity: 3
  
  return 0;
}

//]