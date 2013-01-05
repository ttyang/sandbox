/**
 *  @file   static_vector_set_example.cpp
 *  @date   Aug 14, 2011
 *  @author Andrew Hundt <ATHundt@gmail.com>
 *
 *  (C) Andrew Hundt 2011 <ATHundt@gmail.com>
 *
 *  Distributed under the Boost Software License, Version 1.0. (See
 *  accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @brief  static_vector_set_example.cpp demonstrates the use of boost::container::static_vector
 *
 */
 
#include <iostream>
#include <string>
#include <set>
#include "boost/container/static_vector.hpp"

namespace boost
{
#ifdef BOOST_NO_EXCEPTIONS
void throw_exception(std::exception const & e){}; // user defined
#endif // BOOST_NO_EXCEPTIONS
} // namespace boost

using namespace std;
using namespace boost;

typedef boost::container::static_vector<std::set<std::size_t>,3> ThreeSetType;
  
void print(std::size_t value){
  cout << " " << value;
}


void printSet(std::set<std::size_t> value){
  cout << " (";
  std::for_each(value.begin(),value.end(),print);
  cout << ")";
}

ThreeSetType makeThreeSet(){
  ThreeSetType t;
  std::set<std::size_t> s;
  s.insert(3);
  t.push_back(s);
  s.insert(2);
  t.push_back(s);
  s.insert(1);
  t.push_back(s);
  return t;
}

int main(int argc, char** argv){
  cout << "Creating threeSet, a boost::container::static_vector of 3 std::set objects containing (3), (3 2), and (3 2 1), respectively" << std::endl;
  ThreeSetType threeSet = makeThreeSet();
  cout << "threeSet Values:" << std::endl;
  std::for_each(threeSet.begin(),threeSet.end(),printSet);
  
  cout << std::endl;
  cout << "Sorting threeSet:" << std::endl;
  std::sort(threeSet.begin(), threeSet.end());
  std::for_each(threeSet.begin(),threeSet.end(),printSet);
  
  cout << std::endl << "Success!" << std::endl;
  
}