//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2010.
// Distributed under the Boost
// Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/association for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_BIASSOCIATION__HPP
#define BOOST_BIASSOCIATION__HPP

#include <stddef.h>
#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>
//#include <boost/bimap.hpp>
#include <boost/bimap/tags/tagged.hpp>
#include <boost/bimap/relation/member_at.hpp>
#include <boost/bimap/tags/support/default_tagged.hpp>

namespace boost
{
  namespace association
  {

    // import bimaps directly to the association namespace

    using ::boost::bimaps::tags::tagged;

    namespace member_at = ::boost::bimaps::relation::member_at;

    namespace detail
    {

      template <typename T>
      struct left_tagged
      {
        typedef tagged<T, member_at::left> type;
      };

      template <typename T, typename Tag>
      struct left_tagged<tagged<T, Tag> >
      {
        typedef tagged<T, Tag> type;
      };

      template <typename T>
      struct right_tagged
      {
        typedef tagged<T, member_at::right> type;
      };

      template <typename T, typename Tag>
      struct right_tagged<tagged<T, Tag> >
      {
        typedef tagged<T, Tag> type;
      };
    }

    // specializations of get_field must define a static function apply
    // with the following prototype
    // typename TaggedType::type& apply(T&);

    template <typename TaggedType, typename T>
    struct get_field;

    // specializations of get_embeding must define a static function apply
    // with the following prototype
    // T& apply(FieldType&);

    template <typename T, typename Tag, typename FieldType>
    struct get_embeding;

    /**
     * An association end pointer is an object that manages the consistency with the other association end pointer.
     *
     * More precisely, and end pointer is an object @c u that stores a pointer to a second object @c p and
     * will disconnect both when @c u is destroyed.
     * In this context @u is said to be connected to T.
     *
     * The mechanism by which @c u connects/disconnects to/from @c p
     */
    template <typename Entity, typename T>
    class end_ptr
    {

    public:
      typedef typename Entity::value_type entity_type;
      typedef typename Entity::tag entity_tag;
      typedef typename T::value_type element_type;
      typedef typename T::tag element_tag;
    private:
      element_type* element_ptr_;
      entity_type* entity_ptr_;

    public:

      //typedef element_type value_type;
      typedef element_type * pointer;

      /**
       * @Effects Constructs a end_ptr object that is not associated, value-initializing the stored pointer.
       * Postconditions: get() == nullptr.
       */
      BOOST_CONSTEXPR end_ptr(entity_type* entity_ptr) BOOST_NOEXCEPT :
      element_ptr_(0),
      entity_ptr_(entity_ptr)
      {
      }

      ~end_ptr()
      {
        reset();
      }

      /**
       * @Returns The stored pointer.
       */
      pointer get() const BOOST_NOEXCEPT
      {
        return element_ptr_;
      }

      /**
       * @Requires get() != nullptr.
       * @Returns get().
       * @Note use typically requires that T be a complete type.
       */
      const element_type* operator->() const
      {
        BOOST_ASSERT(get() != 0);
        return get();
      }
      pointer operator->()
      {
        BOOST_ASSERT(get() != 0);
        return get();
      }

      /*
       * @Requires get() != nullptr.
       * @Returns *get().
       */
      element_type const& operator*() const
      {
        BOOST_ASSERT(get() != 0);
        return *get();
      }

      /*
       * @Requires get() != nullptr.
       * @Returns *get().
       */
      element_type& operator*()
      {
        BOOST_ASSERT(get() != 0);
        return *get();
      }

      // C c; c.f=&u;
      end_ptr& operator=(element_type* ptr)
      {
        reset(ptr);
        return *this;
      }
      end_ptr& operator=(end_ptr& rhs)
      {
        if (this != &rhs)
        {
          reset(rhs.element_ptr_);
        }
        return *this;
      }

      void reset()
      {
        if (element_ptr_ == 0) return;
        element_type* tmp = element_ptr_;
        element_ptr_ = 0;
        get_field<tagged<end_ptr<T, Entity> , entity_tag> , element_type>::apply(*tmp).disconnect_one();
      }
      /**
       * Effects: assigns p to the stored pointer, and then if the old value of the stored pointer, old_p,
       * was not equal to nullptr, calls get_deleter()(old_p).
       * @Postconditions get() == p.
       */
      void reset(element_type* ptr)
      {
        if (ptr == element_ptr_) return;
        reset();
        if (ptr == 0) return;
        element_ptr_ = ptr;
        get_field<tagged<end_ptr<T, Entity> , entity_tag> , element_type>::apply(*ptr).connect_one(
            get_entity());
            //&get_embeding<entity_type, entity_tag, end_ptr<Entity, T> >::apply(*this));
      }
      void swap(end_ptr& other)
      {
        T* entity_u = element_ptr_;
        T* element_u = other.element_ptr_;

        reset(element_u);
        other.reset(entity_u);
      }
      void connect(element_type* ptr) { reset(ptr); }
      void disconnect() { reset(); }

      friend class end_ptr<T, Entity> ;

    protected:

      entity_type* get_entity()
      {
        return entity_ptr_;
      }
      void connect_one(element_type* ptr)
      {
        if (ptr == element_ptr_) return;
        reset();
        element_ptr_ = ptr;
      }

      void disconnect_one()
      {
        element_ptr_ = 0;
      }
    };

    template <typename T, typename U>
    class intrinsic
    {

//      typedef typename ::boost::bimaps::tags::support::default_tagged
//      <
//          typename left_set_type::user_type,
//          ::boost::bimaps::relation::member_at::left
//
//      >::type left_tagged_type;
//
//      typedef typename ::boost::bimaps::tags::support::default_tagged
//      <
//          typename right_set_type::user_type,
//          ::boost::bimaps::relation::member_at::right
//
//      >::type right_tagged_type;

      typedef typename detail::left_tagged<T>::type TTag;
      typedef typename detail::right_tagged<U>::type UTag;
    public:
      typedef typename TTag::value_type left_type;
      typedef typename TTag::tag left_tag;
      typedef typename UTag::value_type right_type;
      typedef typename UTag::tag right_tag;
      typedef end_ptr<TTag, UTag> left_end_point;
      typedef end_ptr<UTag, TTag> right_end_point;

    public:
      template <typename WTag>
      struct end_point
      {
        typedef typename mpl::if_<is_same<WTag, right_tag> , left_end_point, typename mpl::if_<
            is_same<WTag, left_tag> , right_end_point, void>::type>::type type;
      };

      static left_end_point& get_left_end_point(left_type& lptr)
      {
        return get_field<tagged<left_end_point, right_tag> , left_type>::apply(lptr);
      }
      static right_end_point& get_right_end_point(right_type& lptr)
      {
        return get_field<tagged<right_end_point, left_tag> , right_type>::apply(lptr);
      }

      template <typename WTag>
      static typename enable_if<is_same<WTag, right_tag> , right_type*>::type get(left_type& ptr)
      {
        return get_field<tagged<left_end_point, right_tag> , left_type>::apply(ptr).get();
      }

      template <typename WTag>
      static typename enable_if<is_same<WTag, left_tag> , left_type*>::type get(right_type& ptr)
      {
        return get_field<tagged<right_end_point, left_tag> , right_type>::apply(ptr).get();
      }

      static void connect(left_type* lptr, right_type* rptr)
      {
        if (lptr != 0)
        {
          get_left_end_point(*lptr).connect(rptr);
        }
        else if (rptr != 0)
        {
          get_right_end_point(*rptr).connect(lptr);
        }
      }

      static void connect(left_type& lptr, right_type& rptr)
      {
        get_left_end_point(lptr).connect(&rptr);
      }

      template <typename WTag>
      static typename enable_if<is_same<WTag, left_tag> , void>::type disconnect(left_type& ptr)
      {
        get_left_end_point(ptr).disconnect();
      }

      template <typename WTag>
      static typename enable_if<is_same<WTag, right_tag> , void>::type disconnect(right_type& ptr)
      {
        get_right_end_point(ptr).disconnect();
      }

    };

  } // namespace association
} // namespace boost

#define BOOST_GET_OBJECT(T, FIELD, VAR) \
    *(reinterpret_cast<T*>(reinterpret_cast<char*>(&VAR) - offsetof(T, FIELD)))

#define BOOST_ASSOCIATION_FIELD_DCL(A,ATAG, B, BTAG, FIELD)\
namespace boost {\
namespace association {\
template <>\
struct get_field<tagged<association::end_ptr<tagged<A,ATAG>,tagged<B,BTAG> >,BTAG>,A> {\
    static association::end_ptr<tagged<A,ATAG>,tagged<B,BTAG> >& apply(A&v) {\
        return v.FIELD;\
    }\
};\
   \
}\
}

#if 0
template <>\
struct get_embeding<A,ATAG,association::end_ptr<tagged<A,ATAG>,tagged<B,BTAG> > > {\
    static A& apply(association::end_ptr<tagged<A,ATAG>,tagged<B,BTAG> >&v) {\
        return BOOST_GET_OBJECT(A, FIELD, v);\
    }\
};\

#endif

#define BOOST_ASSOCIATION_DCL(ASSOC, LEFT, RIGHT) \
BOOST_ASSOCIATION_FIELD_DCL(ASSOC::left_type, ASSOC::left_tag, ASSOC::right_type, ASSOC::right_tag, RIGHT); \
BOOST_ASSOCIATION_FIELD_DCL(ASSOC::right_type, ASSOC::right_tag, ASSOC::left_type, ASSOC::left_tag, LEFT)

#endif
