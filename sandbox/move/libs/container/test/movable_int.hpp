///////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
///////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_TEST_MOVABLE_INT_HEADER
#define BOOST_CONTAINER_TEST_MOVABLE_INT_HEADER

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/move/move.hpp>

namespace boost {
namespace container {
namespace test {

class movable_int
{
   BOOST_MOVABLE_BUT_NOT_COPYABLE(movable_int)

   public:
   movable_int()
      :  m_int(0)
   {}

   explicit movable_int(int a)
      :  m_int(a)
   {}

   movable_int(BOOST_RV_REF(movable_int) mmi)
      :  m_int(mmi.m_int)
   {  mmi.m_int = 0; }

   movable_int & operator= (BOOST_RV_REF(movable_int) mmi)
   {  this->m_int = mmi.m_int;   mmi.m_int = 0;  return *this;  }

   movable_int & operator= (int i)
   {  this->m_int = i;  return *this;  }

   bool operator ==(const movable_int &mi) const
   {  return this->m_int == mi.m_int;   }

   bool operator !=(const movable_int &mi) const
   {  return this->m_int != mi.m_int;   }

   bool operator <(const movable_int &mi) const
   {  return this->m_int < mi.m_int;   }

   bool operator <=(const movable_int &mi) const
   {  return this->m_int <= mi.m_int;   }

   bool operator >=(const movable_int &mi) const
   {  return this->m_int >= mi.m_int;   }

   bool operator >(const movable_int &mi) const
   {  return this->m_int > mi.m_int;   }

   int get_int() const
   {  return m_int;  }

   private:
   int m_int;
};

template<class E, class T> 
std::basic_ostream<E, T> & operator<< 
   (std::basic_ostream<E, T> & os, movable_int const & p)

{
    os << p.get_int();
    return os;
}

class movable_and_copyable_int
{
   BOOST_COPYABLE_AND_MOVABLE(movable_and_copyable_int)

   public:
   movable_and_copyable_int()
      :  m_int(0)
   {}

   explicit movable_and_copyable_int(int a)
      :  m_int(a)
   {}

   movable_and_copyable_int(const movable_and_copyable_int& mmi)
      :  m_int(mmi.m_int)
   {}
   
   movable_and_copyable_int(BOOST_RV_REF(movable_and_copyable_int) mmi)
      :  m_int(mmi.m_int)
   {  mmi.m_int = 0; }

   movable_and_copyable_int &operator= (BOOST_COPY_ASSIGN_REF(movable_and_copyable_int) mi)
   {  this->m_int = mi.m_int;    return *this;  }

   movable_and_copyable_int & operator= (BOOST_RV_REF(movable_and_copyable_int) mmi)
   {  this->m_int = mmi.m_int;   mmi.m_int = 0;    return *this;  }

   movable_and_copyable_int & operator= (int i)
   {  this->m_int = i;  return *this;  }

   bool operator ==(const movable_and_copyable_int &mi) const
   {  return this->m_int == mi.m_int;   }

   bool operator !=(const movable_and_copyable_int &mi) const
   {  return this->m_int != mi.m_int;   }

   bool operator <(const movable_and_copyable_int &mi) const
   {  return this->m_int < mi.m_int;   }

   bool operator <=(const movable_and_copyable_int &mi) const
   {  return this->m_int <= mi.m_int;   }

   bool operator >=(const movable_and_copyable_int &mi) const
   {  return this->m_int >= mi.m_int;   }

   bool operator >(const movable_and_copyable_int &mi) const
   {  return this->m_int > mi.m_int;   }

   int get_int() const
   {  return m_int;  }

   private:
   int m_int;
};

template<class E, class T> 
std::basic_ostream<E, T> & operator<< 
   (std::basic_ostream<E, T> & os, movable_and_copyable_int const & p)

{
    os << p.get_int();
    return os;
}

class copyable_int
{
   public:
   copyable_int()
      :  m_int(0)
   {}

   explicit copyable_int(int a)
      :  m_int(a)
   {}

   copyable_int(const copyable_int& mmi)
      :  m_int(mmi.m_int)
   {}
   
   copyable_int & operator= (int i)
   {  this->m_int = i;  return *this;  }

   bool operator ==(const copyable_int &mi) const
   {  return this->m_int == mi.m_int;   }

   bool operator !=(const copyable_int &mi) const
   {  return this->m_int != mi.m_int;   }

   bool operator <(const copyable_int &mi) const
   {  return this->m_int < mi.m_int;   }

   bool operator <=(const copyable_int &mi) const
   {  return this->m_int <= mi.m_int;   }

   bool operator >=(const copyable_int &mi) const
   {  return this->m_int >= mi.m_int;   }

   bool operator >(const copyable_int &mi) const
   {  return this->m_int > mi.m_int;   }

   int get_int() const
   {  return m_int;  }

   private:
   int m_int;
};

template<class E, class T> 
std::basic_ostream<E, T> & operator<< 
   (std::basic_ostream<E, T> & os, copyable_int const & p)

{
    os << p.get_int();
    return os;
}

}  //namespace test {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //#ifndef BOOST_CONTAINER_TEST_MOVABLE_INT_HEADER
