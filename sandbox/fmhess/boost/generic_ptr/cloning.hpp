//
//  generic_ptr/cloning.hpp
//
//  Copyright (c) 2009 Frank Mori Hess
//  Copyright (c) 2001, 2002 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/generic_ptr for documentation.
//

#ifndef BOOST_GENERIC_PTR_CLONING_HPP_INCLUDED
#define BOOST_GENERIC_PTR_CLONING_HPP_INCLUDED

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/generic_ptr/pointer_traits.hpp>
#include <boost/generic_ptr/shared.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/noncopyable.hpp>
#include <boost/ptr_container/clone_allocator.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/utility/swap.hpp>

namespace boost
{
  namespace generic_ptr
  {
    namespace detail
    {
      class clone_factory_impl_base
      {
      public:
        virtual ~clone_factory_impl_base() {}
        virtual void * get_pointer() = 0;
        virtual clone_factory_impl_base* make_clone() = 0;
      };

      template<typename T>
      class clone_factory_impl: public clone_factory_impl_base
      {
      public:
        explicit clone_factory_impl(T *p): px(p)
        {}
        ~clone_factory_impl()
        {
          delete_clone(px);
        }
        virtual void * get_pointer() { return px; }
        virtual clone_factory_impl* make_clone()
        {
          if(px == 0) return new clone_factory_impl(0);
          return new clone_factory_impl(new_clone(*px));
        }
      private:
        T * px;
      };

      class clone_factory
      {
      public:
        clone_factory(): _impl()
        {}
        template<typename T>
        explicit clone_factory(T * p): _impl(new clone_factory_impl<T>(p))
        {}
        clone_factory(const clone_factory &other): _impl(other._impl->make_clone())
        {}
#ifndef BOOST_NO_RVALUE_REFERENCES
        clone_factory(clone_factory && other)
        {
          swap(other);
        }
#endif
        void * get_pointer()
        {
          if(_impl.get() == 0) return 0;
          return _impl->get_pointer();
        }
        void swap(clone_factory &other)
        {
          boost::swap(_impl, other._impl);
        }
      private:
        clone_factory& operator=(const clone_factory &);  // could be implemented if we need it

        scoped_ptr<clone_factory_impl_base> _impl;
      };
      void swap(clone_factory &a, clone_factory &b)
      {
        a.swap(b);
      }
    }

    template<typename T>
    class cloning
    {
      typedef cloning this_type; // for detail/operator_bool.hpp
      template<typename U>
      friend class cloning;
    public:
      typedef typename pointer_traits<T>::value_type value_type;
      typedef T pointer;
      typedef typename pointer_traits<T>::reference reference;

      template<typename ValueType>
      struct rebind
      {
        typedef cloning<typename generic_ptr::rebind<pointer, ValueType>::other> other;
      };

      cloning(): _cloner(), px()
      {}
      template<typename U>
      cloning( U p ): _cloner(get_plain_old_pointer(p)), px( p )
      {}
      cloning(const cloning & other):
        _cloner(other._cloner),
        px
        (
          static_cast<value_type *>(_cloner.get_pointer())
        )
      {}
      template<typename U>
      cloning(const cloning<U> & other):
        _cloner(other._cloner),
        px
        (
          static_cast
          <
            typename pointer_traits<U>::value_type *
          >(_cloner.get_pointer())
        )
      {}
#ifndef BOOST_NO_RVALUE_REFERENCES
      cloning(cloning && other): _cloner(std::move(other._cloner)), px(std::move(other.px))
      {}
      template<typename U>
      cloning(cloning<U> && other): _cloner(std::move(other._cloner)), px(std::move(other.px))
      {}
#endif

      void swap(cloning & other)
      {
        boost::swap(px, other.px);
        boost::swap(_cloner, other._cloner);
      }

      cloning & operator=(const cloning & other)
      {
        cloning(other).swap(*this);
        return *this;
      }

      template<typename U>
      cloning & operator=(const cloning<U> & other)
      {
        cloning(other).swap(*this);
        return *this;
      }
#ifndef BOOST_NO_RVALUE_REFERENCES
      cloning & operator=(cloning && other)
      {
        cloning(std::move(other)).swap(*this);
        return *this;
      }
      template<typename U>
      cloning & operator=(cloning<U> && other)
      {
        cloning(std::move(other)).swap(*this);
        return *this;
      }
#endif
      void reset()
      {
        cloning().swap(*this);
      }
      template<typename U> void reset(U p)
      {
        cloning(p).swap(*this);
      }

      pointer get() const {return px;}

// implicit conversion to "bool"
#include <boost/generic_ptr/detail/operator_bool.hpp>

      pointer operator->() const
      {
        BOOST_ASSERT(get_plain_old_pointer(px) != 0);
        return px;
      }

      reference operator*() const
      {
        BOOST_ASSERT(get_plain_old_pointer(px) != 0);
        return *px;
      }

    private:
      detail::clone_factory _cloner;
      pointer px;
    };

    template<typename T>
    T get_pointer(const cloning<T> &p)
    {
      return p.get();
    }

    // casts
    template<typename ToValueType, typename U>
    typename rebind<cloning<U>, ToValueType>::other static_pointer_cast
    (
      cloning<U> const & p,
      mpl::identity<ToValueType> to_type_iden = mpl::identity<ToValueType>()
    )
    {
      typedef typename rebind<cloning<U>, ToValueType>::other result_type;
      typename result_type::pointer wrapped_p(static_pointer_cast(p.get(), to_type_iden));
      typename result_type::value_type *plain_p = get_plain_old_pointer(wrapped_p);
      if(plain_p == 0) return result_type(plain_p);
      return result_type(new_clone(*plain_p));
    }
    template<typename ToValueType, typename U>
    typename rebind<cloning<U>, ToValueType>::other const_pointer_cast
    (
      cloning<U> const & p,
      mpl::identity<ToValueType> to_type_iden = mpl::identity<ToValueType>()
    )
    {
      typedef typename rebind<cloning<U>, ToValueType>::other result_type;
      typename result_type::pointer wrapped_p(const_pointer_cast(p.get(), to_type_iden));
      typename result_type::value_type *plain_p = get_plain_old_pointer(wrapped_p);
      if(plain_p == 0) return result_type(plain_p);
      return result_type(new_clone(*plain_p));
    }
    template<typename ToValueType, typename U>
    typename rebind<cloning<U>, ToValueType>::other dynamic_pointer_cast
    (
      cloning<U> const & p,
      mpl::identity<ToValueType> to_type_iden = mpl::identity<ToValueType>()
    )
    {
      typedef typename rebind<cloning<U>, ToValueType>::other result_type;
      return result_type(dynamic_pointer_cast(p.get(), to_type_iden));
      typename result_type::pointer wrapped_p(static_pointer_cast(p.get(), to_type_iden));
      typename result_type::value_type *plain_p = get_plain_old_pointer(wrapped_p);
      if(plain_p == 0) return result_type(plain_p);
      return result_type(new_clone(*plain_p));
    }

    // comparisons
    template<class T, class U> inline bool operator==(cloning<T> const & a, cloning<U> const & b)
    {
      return a.get() == b.get();
    }
    template<class T, class U> inline bool operator!=(cloning<T> const & a, cloning<U> const & b)
    {
      return a.get() != b.get();
    }
    template<class T, class U> inline bool operator==(cloning<T> const & a, U const & b)
    {
      return a.get() == b;
    }
    template<class T, class U> inline bool operator!=(cloning<T> const & a, U const & b)
    {
      return a.get() != b;
    }
    template<class T, class U> inline bool operator==(T const & a, cloning<U> const & b)
    {
      return a == b.get();
    }
    template<class T, class U> inline bool operator!=(T const & a, cloning<U> const & b)
    {
      return a != b.get();
    }
    #if __GNUC__ == 2 && __GNUC_MINOR__ <= 96
    // Resolve the ambiguity between our op!= and the one in rel_ops
    template<class T> inline bool operator!=(cloning<T> const & a, cloning<T> const & b)
    {
      return a.get() != b.get();
    }
    #endif
    template<class T> inline bool operator<(cloning<T> const & a, cloning<T> const & b)
    {
      return std::less<typename cloning<T>::pointer>()(a.get(), b.get());
    }
  } // namespace generic_ptr
} // namespace boost

#endif  // #ifndef BOOST_GENERIC_PTR_CLONING_HPP_INCLUDED
