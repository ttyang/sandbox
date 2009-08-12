//We need to declare:
//
//2 conversions: rv<T> & and const rv<T> &
//1 rv<T> & constructor: move constructor
//1 const rv<T> & constructor: copy constructor
//1 T & constructor: copy constructor
//
//Optimization:
//Since RVO is better than move-construction,
//avoid copy constructor overloading.
#include <boost/move/move.hpp>
#include <iostream>

bool moved = false;

class obj
{
   BOOST_COPYABLE_AND_MOVABLE(obj)
   public:

   obj()
   {
      std::cout << "constructing obj" << "\n";
   }

   ~obj()
   {}

   obj(BOOST_COPY_ASSIGN_REF(obj) trule)
   {
      std::cout << "copy construct from const obj" << "\n";
   }

   // copy construct from movable object (non-const rvalue, explicitly moved lvalue)
   obj(BOOST_RV_REF(obj) trule)
   {
      std::cout << "move construct from movable rvalue" << "\n";
   }

   obj& operator =(BOOST_COPY_ASSIGN_REF(obj) trule)
   {
      std::cout << "copy assign from const obj" << "\n";
      return *this;
   }

   obj& operator =(BOOST_RV_REF(obj) trule)
   {
      std::cout << "move assign from movable rvalue" << "\n";
      return *this;
   }
};


obj        rvalue_func()       { return obj(); }
const obj  const_rvalue_func() { return obj();  }
obj&       lvalue_func()       { static obj o;  return o; }
const obj& const_lvalue_func() { static obj o; return o; }

int main()
{
   {
   obj o1(rvalue_func());
   obj o2 = const_rvalue_func();
   obj o3 = lvalue_func();
   obj o4 = const_lvalue_func();
   // can't explicitly move temporaries
   //obj o5 = boost::move(rvalue_func());
   obj o6 = boost::move(const_rvalue_func());
   obj o7 = boost::move(lvalue_func());
   obj o8 = boost::move(const_lvalue_func());

   obj o;
   o = rvalue_func();
   o = const_rvalue_func();
   o = lvalue_func();
   o = const_lvalue_func();
   // can't explicitly move temporaries
   //o = boost::move(rvalue_func());
   o = boost::move(const_rvalue_func());
   o = boost::move(lvalue_func());
   o = boost::move(const_lvalue_func());
   }

   return 0;
}

//We need to declare:
//
//2 conversions: rv<T> & and const rv<T> &
//1 rv<T> & constructor: move constructor
//1 const rv<T> & constructor: copy constructor
//1 T & constructor: copy constructor

