#ifndef BOOST_ARRAY_STEPPER_VECTOR_PRINT_HPP_INCLUDED
#define BOOST_ARRAY_STEPPER_VECTOR_PRINT_HPP_INCLUDED
#include <vector>
#include <iostream>
  template
  < typename T
  >
  std::ostream&
operator<<
  ( std::ostream& sout
  , std::vector<T> const& a_container
  )
{
   sout<<"{ ";
   unsigned const size=a_container.size();
   for(unsigned i=0; i<size; ++i)
   {
      if(0<i) sout<<", ";
      sout<<a_container[i];
   }
   sout<<"} ";
   return sout;
}
#endif
