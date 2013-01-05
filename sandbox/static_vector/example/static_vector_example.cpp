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
 
#include <iostream>
#include <string>
#include <set>
#include "boost/container/static_vector.hpp"

using namespace std;
using namespace boost;

  
void print(std::size_t value){
  cout << " " << value;
}


int main(int argc, char** argv){
  
  // create static_vector with a capacity of 3
  boost::container::static_vector<std::size_t,3> three; // size: 0 capacity: 3

  three.push_back(5); // size: 1 capacity: 3
  three.push_back(2); // size: 2 capacity: 3
  three.push_back(1); // size: 3 capacity: 3
  
  cout << "Values: ";
  std::for_each(three.begin(),three.end(),print);
  cout << "size: " << three.size() << " capacity: "  << three.capacity() << std::endl; // size: 3 capacity: 3
  
  // three.push_back(3); // uncomment for undefined behavior, adding a 4th element goes over the end. capacity: 3 size: 3
  
  std::sort(three.begin(), three.end());
  cout << "Sorted:";
  std::for_each(three.begin(),three.end(),print);
  cout << "size: " << three.size() << " capacity: "  << three.capacity() << std::endl; // size: 3 capacity: 3
  
  three.pop_back(); // size: 2 capacity: 3
  three.shrink_to_fit(); // has no effect, size: 2 capacity: 3
  
  cout << "Popped: ";
  std::for_each(three.begin(),three.end(),print);
  cout << "  size: " << three.size() << " capacity: "  << three.capacity() << std::endl; // size: 2 capacity: 3
}