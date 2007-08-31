/*
 * Copyright Jeremy Pack 2007
 * Distributed under the Boost Software License, Version 1.0. (See
                                                               * accompanying file LICENSE_1_0.txt or copy at
                                                               * http://www.boost.org/LICENSE_1_0.txt)
                                                               *
                                                               * See http://www.boost.org/ for latest version.
                                                               */

#ifndef BOOST_EXTENSION_INSTANCE_HPP
#define BOOST_EXTENSION_INSTANCE_HPP
namespace boost {namespace reflections {
class instance {
public:
  instance(void * val = 0, void (*destructor)(void * val) = 0) 
  : val_(val),
    destructor_(destructor) {}
  ~instance() {
    if (val_)
      (*destructor_)(val_);
  }
  instance(const instance & first)
  : val_(first.val_),
    destructor_(first.destructor_)
  {
    if (this != &first) {
      //  Check for self assignment
      first.val_ = 0;
    }
  }
  instance & operator=(instance & first) {
    if (this != &first) {
      //  Check for self assignment
      this->val_ = first.val_;
      this->destructor_ = first.destructor_;
      first.val_ = 0;
    }
    return *this;
  }
private:
  template <class ReturnValue>
  friend class function;
  mutable void * val_;
  void (*destructor_)(void *);
};
}}
#endif