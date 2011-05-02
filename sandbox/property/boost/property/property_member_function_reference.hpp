#if !defined(PROPERTY_MEMBER_FUNCTION_REFERENCE_HPP)
#define PROPERTY_MEMBER_FUNCTION_REFERENCE_HPP

#include "PropertyReferenceInterface.h"
#include "PropertyException.h"

namespace properties
{

  template <class T, class C, T & (C::*g)()>
  class prop_member_function_reference : 
    public i_property_reference_read<T>
  {
    public:
    
    prop_member_function_reference(C & c) : 
      cf(c) 
      { 
      }
    
    operator T const & () const 
      { 
      return(get()); 
      }
      
    operator T & () 
      { 
      return(get()); 
      }
    
    T const & get() const 
      { 
      if (g == 0) 
        { 
        throw property_read_exception(); 
        } 
      return((cf.*g)()); 
      }
      
    T & get() 
      { 
      if (g == 0) 
        { 
        throw property_read_exception(); 
        } 
      return((cf.*g)()); 
      }
    
    private:
    
    C & cf;
    
  };

}

#endif