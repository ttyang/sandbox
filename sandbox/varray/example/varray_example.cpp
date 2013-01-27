/**
 *  @file   varray_example.cpp
 *  @date   Aug 14, 2011
 *  @author Andrew Hundt <ATHundt@gmail.com>
 *
 *  (C) 2011-2012 Andrew Hundt <ATHundt@gmail.com>
 *
 *  Distributed under the Boost Software License, Version 1.0. (See
 *  accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @brief  varray_example.cpp demonstrates the use of boost::container::varray
 *
 */
 
//[varray_example_cpp

// varray_example.cpp

#include <boost/container/varray.hpp>

int main(int argc, char** argv){
  
  // varray of ints, fixed capacity: 3
  boost::container::varray<int, 3> three; // size: 0

  three.push_back(1);    // size: 1
  three.push_back(2);    // size: 2
  three.push_back(3);    // size: 3
  
  //three.reserve(4);    // no effect, fixed capacity: 3
  //three.push_back(3);  // size: 4, behavior depends on strategy, assert by default
  
  three.pop_back();      // size: 2
  three.shrink_to_fit(); // no effect, fixed capacity: 3
  
  return 0;
}

//]
