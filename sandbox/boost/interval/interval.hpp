#ifndef BOOST_INTERVAL_INTERVAL_HPP
#define BOOST_INTERVAL_INTERVAL_HPP

#include <stdexcept>
#include <boost/interval/detail/interval_prototype.hpp>

namespace boost {

  namespace interval_lib {
    
class comparison_error
  : public std::runtime_error 
{
public:
  comparison_error()
    : std::runtime_error("boost::interval: uncertain comparison")
  { }
};

  } // namespace interval_lib;

/*
 * interval class
 */

template<class T, class Policies>
class interval
{
private:
  struct interval_holder;
  struct number_holder;
public:
  typedef T base_type;
  typedef Policies traits_type;

  interval(const T& v = T());
  interval(const T& l, const T& u);

  // The following needs to be defined in the class body for VC++.
  template<class Policies2>
  interval(const interval<T, Policies2>& r)
    : low(r.lower()), up(r.upper())
  {
    if (boost::empty(r)) set_empty();
  }

  // compiler-generated copy constructor and assignment operator are fine

  interval& operator=(const T& x);
  void assign(const T& l, const T& u);

  static interval empty();
  static interval whole();
  static interval hull(const T& x, const T& y);

  const T& lower() const;
  const T& upper() const;

  interval& operator+= (const T& r);
  interval& operator+= (const interval& r);
  interval& operator-= (const T& r);
  interval& operator-= (const interval& r);
  interval& operator*= (const T& r);
  interval& operator*= (const interval& r);
  interval& operator/= (const T& r);
  interval& operator/= (const interval& r);

  bool operator< (const interval_holder& r) const;
  bool operator> (const interval_holder& r) const;
  bool operator<= (const interval_holder& r) const;
  bool operator>= (const interval_holder& r) const;
  bool operator== (const interval_holder& r) const;
  bool operator!= (const interval_holder& r) const;

  bool operator< (const number_holder& r) const;
  bool operator> (const number_holder& r) const;
  bool operator<= (const number_holder& r) const;
  bool operator>= (const number_holder& r) const;
  bool operator== (const number_holder& r) const;
  bool operator!= (const number_holder& r) const;

  // the following is for internal use only, it is not a published interface
  // nevertheless, it's public because friends don't always work correctly.
  interval(const T& l, const T& u, bool): low(l), up(u) {}
  void set_empty();
  void set_whole();
  void set(const T& l, const T& u);

private:
  struct interval_holder {
    template<class Policies2>
    interval_holder(const interval<T, Policies2>& r)
      : low(r.lower()), up(r.upper())
    {
      typedef typename Policies2::checking checking2;
      if (checking2::is_empty(low, up))
	throw interval_lib::comparison_error();
    }

    const T& low;
    const T& up;
  };

  struct number_holder {
    number_holder(const T& r) : val(r)
    {
      if (checking::is_nan(r))
	throw interval_lib::comparison_error();
    }
    
    const T& val;
  };

  typedef typename Policies::checking checking;
  typedef typename Policies::rounding rounding;

  T low;
  T up;
};

template<class T, class Traits> inline
interval<T, Traits>::interval(const T& v): low(v), up(v)
{
  if (checking::is_nan(v)) set_empty();
}

template<class T, class Traits> inline
interval<T, Traits>::interval(const T& l, const T& u): low(l), up(u)
{
  if (checking::is_nan(l) || checking::is_nan(u) || !(l <= u))
    set_empty();
}

template<class T, class Traits> inline
interval<T, Traits>& interval<T, Traits>::operator=(const T& x)
{
  if (checking::is_nan(x)) set_empty();
  else low = up = x;
  return *this;
}

template<class T, class Traits> inline
void interval<T, Traits>::assign(const T& l, const T& u)
{
  if (checking::is_nan(l) || checking::is_nan(u) || !(l <= u))
    set_empty();
  else set(l, u);
}

template<class T, class Traits> inline
void interval<T, Traits>::set(const T& l, const T& u)
{
  low = l;
  up  = u;
}

template<class T, class Traits> inline
void interval<T, Traits>::set_empty()
{
  low = checking::empty_lower();
  up  = checking::empty_upper();
}

template<class T, class Traits> inline
void interval<T, Traits>::set_whole()
{
  const T& inf = checking::inf();
  low = -inf;
  up  =  inf;
}

template<class T, class Traits> inline
interval<T, Traits> interval<T, Traits>::hull(const T& x, const T& y)
{
  bool bad_x = checking::is_nan(x);
  bool bad_y = checking::is_nan(y);
  if (bad_x)
    if (bad_y) return interval::empty();
    else       return interval(y, y, true);
  else
    if (bad_y) return interval(x, x, true);
  if (x < y) return interval(x, y, true);
  else       return interval(y, x, true);
}

template<class T, class Traits> inline
interval<T, Traits> interval<T, Traits>::empty()
{
  return interval(checking::empty_lower(),
		  checking::empty_upper(), true);
}

template<class T, class Traits> inline
interval<T, Traits> interval<T, Traits>::whole()
{
  const T& inf = checking::inf();
  return interval(-inf, inf, true);
}

template<class T, class Traits> inline
const T& interval<T, Traits>::lower() const
{
  return low;
}

template<class T, class Traits> inline
const T& interval<T, Traits>::upper() const
{
  return up;
}

/*
 * interval/interval comparisons
 */

template<class T, class Policies> inline
bool interval<T, Policies>::operator< (const interval_holder& r) const
{
  if (checking::is_empty(low, up))
  if (up < r.low) return true;
  else if (low >= r.up) return false;
  else throw interval_lib::comparison_error();
}

template<class T, class Policies> inline
bool interval<T, Policies>::operator> (const interval_holder& r) const
{
  if (up > r.low) return true;
  else if (low <= r.up) return false;
  else throw interval_lib::comparison_error();
}

template<class T, class Policies> inline
bool interval<T, Policies>::operator<= (const interval_holder& r) const
{
  if (up <= r.low) return true;
  else if (low > r.up) return false;
  else throw interval_lib::comparison_error();
}

template<class T, class Policies> inline
bool interval<T, Policies>::operator>= (const interval_holder& r) const
{
  if (up >= r.low) return true;
  else if (low < r.up) return false;
  else throw interval_lib::comparison_error();
}

template<class T, class Policies> inline
bool interval<T, Policies>::operator== (const interval_holder& r) const
{
  if (up == r.low && low == r.up) return true;
  else if (up < r.low || low > r.up) return false;
  else throw interval_lib::comparison_error();
}

template<class T, class Policies> inline
bool interval<T, Policies>::operator!= (const interval_holder& r) const
{
  if (up < r.low || low > r.up) return true;
  else if (up == r.low && low == r.up) return false;
  else throw interval_lib::comparison_error();
}

/*
 * interval/number comparisons
 */

template<class T, class Policies> inline
bool interval<T, Policies>::operator< (const number_holder& r) const
{
  if (up < r.val) return true;
  else if (low >= r.val) return false;
  else throw interval_lib::comparison_error();
}

template<class T, class Policies> inline
bool interval<T, Policies>::operator> (const number_holder& r) const
{
  if (up > r.val) return true;
  else if (low <= r.val) return false;
  else throw interval_lib::comparison_error();
}

template<class T, class Policies> inline
bool interval<T, Policies>::operator<= (const number_holder& r) const
{
  if (up <= r.val) return true;
  else if (low > r.val) return false;
  else throw interval_lib::comparison_error();
}

template<class T, class Policies> inline
bool interval<T, Policies>::operator>= (const number_holder& r) const
{
  if (up >= r.val) return true;
  else if (low < r.val) return false;
  else throw interval_lib::comparison_error();
}

template<class T, class Policies> inline
bool interval<T, Policies>::operator== (const number_holder& r) const
{
  if (up == r.val && low == r.val) return true;
  else if (up < r.val || low > r.val) return false;
  else throw interval_lib::comparison_error();
}

template<class T, class Policies> inline
bool interval<T, Policies>::operator!= (const number_holder& r) const
{
  if (up < r.val || low > r.val) return true;
  else if (up == r.val && low == r.val) return false;
  else throw interval_lib::comparison_error();
}

} // namespace boost

#endif // BOOST_INTERVAL_INTERVAL_HPP
