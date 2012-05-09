//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2012.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/role for documentation.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @file
 * @brief Defines the entity/role facilities.
 *
 */

#ifndef BOOST_ROLE_ENTITY_ROLE_HPP
#define BOOST_ROLE_ENTITY_ROLE_HPP

#include <boost/config.hpp>
#include <boost/role/delete.hpp>

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/static_assert.hpp>

#include <vector>

/**
 * std::tuple<void*, void*, ...> subject;
 */
namespace boost
{
  namespace entity_role
  {
    /**
     * A static id generator.
     */
    template <typename Tag, typename Int = std::size_t>
    class id
    {
    public:
      typedef Tag tag_tpe;
      typedef Int int_type;

      id() :
        id_(next_id_++)
      {
      }
      int_type get()
      {
        return id_;
      }
    private:
      int_type id_;
      static int_type next_id_;
    };

    template <typename Tag, typename Int>
    Int id<Tag, Int>::next_id_ = 0;

    /**
     * A Roles specification consists of the entity, the role type and the tag.
     */
    template <typename Entity, typename Role, typename Tag>
    struct role_spec
    {
      typedef Entity entity_type;
      typedef Role role_type;
      static const id<Entity> id_;
    };

    template <typename Entity, typename Role, typename Tag>
    const id<Entity> role_spec<Entity, Role, Tag>::id_;

    /**
     * All the Entities have this class as base class.
     */
    class entity_base;

    /**
     * All the Roles have this class as base class.
     * A Role is non-copyable and contains a pointer to its entity.
     */
    class role_base
    {
    public:
      BOOST_ROLE_NO_COPYABLE( role_base)

      entity_base& get_entity()
      {
        return *entity_;
      }
      void set_entity(entity_base& e)
      {
        entity_ = &e;
      }
      void unset_entity()
      {
        entity_ = 0;
      }

    protected:
      entity_base* entity_;
      explicit role_base(entity_base& e) :
        entity_(&e)
      {
      }
    };

    /**
     * @example
     *
     * class Rake : public role<User>
     * {
     * public:
     *   Rake(User&);
     *   ...
     * };
     * struct F1 : role_spec<User, Rake, F1> {};
     *
     * User u;
     * add_tagged_role<F1>(u);
     */

    template <typename Entity, typename Base = role_base>
    class role: public Base
    {
    public:
      typedef Entity entity_type;
      typedef Base base_type;

      explicit role(entity_type& e) :
        base_type(e)
      {
      }

      ~role()
      {
      }

      entity_type& get_entity()
      {
        return *static_cast<entity_type*> (this->entity_);
      }
      void set_entity(entity_type& e)
      {
        this->entity_ = &e;
      }
      void unset_entity()
      {
        this->entity_ = 0;
      }
    };

    /**
     * @example
     *
     * class Rake : public unique_role<User, Rake>
     * {
     * public:
     *   Rake(User&);
     *   ...
     * };
     * User u;
     * add_role<Rake>(u);
     */
    template <typename Entity, typename Role, typename Base = role_base>
    class unique_role: public role<Entity, Base> , public role_spec<Entity, Role, Role>
    {
    public:
      typedef Entity entity_type;
      typedef role<Entity, Base> base_type;

      explicit unique_role(entity_type& e) :
        base_type(e)
      {
      }
    };

    /**
     *
     */
    class entity_base
    {
    public:
      static const std::size_t max_num_of_roles = 0;
      entity_base()
BOOST_NOEXCEPT      ;
      entity_base(const entity_base& e) BOOST_NOEXCEPT;
    protected:
      class impl;
      shared_ptr<impl> impl_;

      entity_base(impl*) BOOST_NOEXCEPT;

      bool has_role2(std::size_t id) const;
      shared_ptr<role_base> use_role2(std::size_t);
      void add_role2(shared_ptr<role_base> r, std::size_t id);
      void remove_role2(std::size_t id);
      void move_role2(entity_base& e, std::size_t to, std::size_t from);

    };

    /////////////////////////
    // This should be placed on a specific header file available to
    class entity_base::impl
    {
      std::vector<shared_ptr<role_base> > roles_;
    public:
      BOOST_ROLE_NO_COPYABLE(impl)
      explicit impl()
      {
      }
      ~impl()
      {}

      bool has_role(std::size_t id) const
      {
        return (id < roles_.size()) && roles_[id];
      }

      shared_ptr<role_base> use_role(std::size_t id)
      {
        return roles_[id];
      }

      void add_role(shared_ptr<role_base> r, std::size_t id)
      {
        if (roles_.size() <= id)
        {
          roles_.resize(id+1);
        }
        roles_[id] = r;
      }
      void remove_role(std::size_t id)
      {
        if (!has_role(id)) return;

        roles_[id]->unset_entity();
        roles_[id].reset();
      }

      void move_role(entity_base& target, std::size_t to, std::size_t from)
      {
        if (!has_role(from)) return;

        roles_[from]->set_entity(target);
        target.add_role2(roles_[from], to);
        roles_[from].reset();
      }
    };

    entity_base::entity_base()
    : impl_(new impl())
    {
    }
    entity_base::entity_base(const entity_base& rhs)
    : impl_(rhs.impl_)
    {
    }
    entity_base::entity_base(entity_base::impl *impl)
    : impl_(impl)
    {
    }

    bool
    entity_base::has_role2(std::size_t id) const
    {
      return impl_->has_role(id);
    }
    shared_ptr<role_base>
    entity_base::use_role2(std::size_t id)
    {
      return impl_->use_role(id);
    }

    void
    entity_base::add_role2(shared_ptr<role_base> r, std::size_t id)
    {
      impl_->add_role(r, id);
    }
    void
    entity_base::remove_role2(std::size_t id)
    {
      impl_->remove_role(id);
    }
    void
    entity_base::move_role2(entity_base& target, std::size_t to, std::size_t from)
    {
      impl_->move_role(target, to, from);
    }
    /////////////////////////

    /**
     * This mixin provides access of up to @c N Roles associated to the entity @c Entity.
     *
     * @TParams
     * @TParam{Entity,the entity to been defined}
     * @TParam{N,the number of roles of this entity}
     * @TParam{Base,the base class}
     *
     * @Example
     * <code>
     * class User : public entity<User, 3>
     * {
     * };
     * class Subscriber : public entity<Subscriber, 5, User>
     * {
     * };
     * </code>
     */
    template <typename Entity, std::size_t N, typename Base=entity_base>
    class entity : public Base
    {
    public:
      /**
       * Default constructor
       */
      entity() BOOST_NOEXCEPT
      : Base()
      {}
      /**
       * Copy constructor
       */
      entity(const entity& e) BOOST_NOEXCEPT
      : Base(e)
      {}

    protected:
      /**
       * First role id associated to this entity slice.
       */
      static const std::size_t first_role = Base::max_num_of_roles;
      /**
       * Last+1 role id associated to this entity slice.
       */
      static const std::size_t max_num_of_roles = N+Base::max_num_of_roles;

      /**
       * The implementation type
       */
      typedef typename Base::impl impl;

      /**
       * constructor from impl
       */
      entity(impl* i)
      : Base(i)
        {}

      bool has_role(id<Entity> id) const;
      shared_ptr<role<Entity> > use_role(id<Entity>);
      void add_role(shared_ptr<role<Entity> > r, id<Entity> id);
      void remove_role(id<Entity> id);
      void move_role(Entity& e, id<Entity> to, id<Entity> from);

      template <typename Tag, typename Entity2>
      friend bool has_tagged_role(const Entity2& e) BOOST_NOEXCEPT;
      template <typename Tag, typename Entity2>
      friend shared_ptr<typename Tag::role_type> use_tagged_role(Entity2& e);
      template <typename Tag, typename Entity2, typename Role>
      friend shared_ptr<Role> add_tagged_role(Entity2& e, Role* r);
      template <typename Tag, typename Entity2>
      friend void remove_tagged_role(Entity2& e);
      template <typename ToTag, typename FromTag, typename Entity2>
      friend void move_tagged_role(Entity2& to, Entity2& from);

    };

    template <typename Entity, std::size_t N, typename Base>
    bool
    entity<Entity,N,Base>::has_role(id<Entity> id) const
    {
      return this->has_role2(first_role+id.get());
    }

    template <typename Entity, std::size_t N, typename Base>
    shared_ptr<role<Entity> >
    entity<Entity,N,Base>::use_role(id<Entity> id)
    {
      return static_pointer_cast<role<Entity> >(this->use_role2(first_role+id.get()));
    }

    template <typename Entity, std::size_t N, typename Base>
    void
    entity<Entity,N,Base>::add_role(shared_ptr<role<Entity> > r, id<Entity> id)
    {
      this->add_role2(static_pointer_cast<role_base>(r), first_role+id.get());
    }

    template <typename Entity, std::size_t N, typename Base>
    void
    entity<Entity,N,Base>::remove_role(id<Entity> id)
    {
      this->remove_role2(first_role+id.get());
    }

    template <typename Entity, std::size_t N, typename Base>
    void
    entity<Entity,N,Base>::move_role(Entity& target, id<Entity> to, id<Entity> from)
    {
      this->move_role2(target, first_role+to.get(), first_role+from.get());
    }

    //////////////////

    template <typename Tag, typename Entity>
    const shared_ptr<typename Tag::role_type> use_tagged_role(const Entity& e)
    {
      typedef typename Tag::role_type Role;
      typedef typename Tag::entity_type entity_type;
      return static_pointer_cast<Role>(static_cast<const entity_type&>(e).use_role(Tag::id_));
    }
    template <typename Tag, typename Entity>
    shared_ptr<typename Tag::role_type> use_tagged_role(Entity& e)
    {
      typedef typename Tag::entity_type entity_type;
      typedef typename Tag::role_type Role;
      return static_pointer_cast<Role>(static_cast<entity_type&>(e).use_role(Tag::id_));
    }
    template <class Role, typename Entity>
    const shared_ptr<Role> use_role(const Entity& e)
    {
      return use_tagged_role<Role>(e);
    }
    template <class Role, typename Entity>
    shared_ptr<Role> use_role(Entity& e)
    {
      return use_tagged_role<Role>(e);
    }

    template <typename Tag, typename Entity>
    bool has_tagged_role(const Entity& e) BOOST_NOEXCEPT
    {
      typedef typename Tag::entity_type entity_type;
      return static_cast<const entity_type&>(e).has_role(Tag::id_);
    }
    template <class Role, typename Entity>
    bool has_role(const Entity& e) BOOST_NOEXCEPT
    {
      return has_tagged_role<Role>(e);
    }

    template <typename Tag, typename Entity, typename Role>
    shared_ptr<Role> add_tagged_role(Entity& e, Role* r)
    {
      typedef typename Tag::entity_type entity_type;
      shared_ptr<role<typename Tag::entity_type> > sp(r);
      static_cast<entity_type&>(e).add_role(sp, Tag::id_);
      r->set_entity(e);
      return static_pointer_cast<Role>(sp);
    }
    template <typename Entity, class Role>
    shared_ptr<Role> add_role(Entity& e, Role* r)
    {
      return add_tagged_role<Role>(e, r);
    }
    template <typename Tag, typename Entity>
    shared_ptr<typename Tag::role_type> add_tagged_role(Entity& e)
    {
      typedef typename Tag::role_type Role;
      return add_tagged_role<Tag>(e, new Role(e));
    }
    template <class Role, typename Entity>
    shared_ptr<Role> add_role(Entity& e)
    {
      return add_tagged_role<Role>(e);
    }

    template <typename Tag, typename Entity>
    void remove_tagged_role(Entity& e)
    {
      typedef typename Tag::entity_type entity_type;
      static_cast<entity_type&>(e).remove_role(Tag::id_);
    }
    template <class Role, typename Entity>
    void remove_role(Entity& e)
    {
      remove_tagged_role<Role>(e);
    }

    template <typename ToTag, typename FromTag, typename Entity>
    void move_tagged_role(Entity& to, Entity& from)
    {
      typedef typename ToTag::entity_type entity_type;
      static_cast<entity_type&>(from).move_role(to, ToTag::id_, FromTag::id_);
    }
    template <class Role, typename Entity>
    void move_role(Entity& to, Entity& from)
    {
      move_tagged_role<Role,Role>(to, from);
    }

  }
}

#endif // header
