// Copyright (C) 2012 Vicente J. Botet Escriba
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <boost/role/entity_role.hpp>
#include <boost/detail/lightweight_test.hpp>

using namespace boost::entity_role;

namespace Ex
{
  class User: public entity<User, 3>
  {
    typedef entity<User, 3> base_type;
  public:
    User(int id=0) :
      base_type(new impl(id))
    {
    }
  protected:
    struct impl : public base_type::impl
    {
      impl() : id_(0) {}
      impl(int id) : id_(id) {}
      int id_;
    };
    User(impl* i) :
      base_type(i)
    {
    }
  };
  class Rake: public unique_role<User, Rake>
  {
  public:
    Rake(User& u) :
      unique_role<User, Rake> (u), i(0)
    {
    }
    int i;
  };
  class Searcher: public unique_role<User, Searcher>
  {
  public:
    Searcher(User& u) :
      unique_role<User, Searcher> (u), i(0)
    {
    }
    int i;
  };
  class Tracker: public entity<Tracker, 2>, public unique_role<User, Tracker>
  {
  public:
    Tracker(User& u) :
      entity<Tracker, 2>(), unique_role<User, Tracker>(u), i(0)
    {
    }
    int i;
  };
  class HsupaUser: public entity<HsupaUser, 2, User>
  {
  };
  class Role1: public unique_role<HsupaUser, Role1>
  {
  public:
    Role1(HsupaUser& u) :
      unique_role<HsupaUser, Role1> (u), i(0)
    {
    }
    int i;
  };
}

int main()
{
  std::cout << __FILE__ << ":" << __LINE__ << std::endl;
  {
    Ex::User u;
    add_role<Ex::Rake> (u);
    BOOST_TEST( has_role<Ex::Rake> (u));
  }
  {
    Ex::HsupaUser u;
    add_role<Ex::Rake> (u);
    BOOST_TEST( has_role<Ex::Rake> (u));
  }
  {
    Ex::HsupaUser u;
    add_role<Ex::Role1> (u);
    BOOST_TEST( has_role<Ex::Role1> (u));
  }
  {
    Ex::User u;
    add_role<Ex::Rake> (u);
    add_role<Ex::Rake> (u);
    BOOST_TEST( has_role<Ex::Rake> (u));
  }
  {
    Ex::User u;
    add_role<Ex::Rake> (u);
    use_role<Ex::Rake> (u)->i = 1;
  }
  {
    Ex::User u;
    add_role<Ex::Rake> (u);
    BOOST_TEST(&use_role<Ex::Rake> (u)->get_entity() == &u);
  }
  {
    Ex::HsupaUser u;
    add_role<Ex::Rake> (u);
    use_role<Ex::Rake> (u)->i = 1;
  }
  {
    Ex::User u;
    add_role<Ex::Rake> (u);
    remove_role<Ex::Rake> (u);
    BOOST_TEST(!has_role<Ex::Rake> (u));
  }
  {
    Ex::HsupaUser u;
    add_role<Ex::Rake> (u);
    remove_role<Ex::Rake> (u);
    BOOST_TEST(!has_role<Ex::Rake> (u));
  }
  {
    Ex::User u, v;
    add_role<Ex::Rake> (u);
    BOOST_TEST( has_role<Ex::Rake> (u));
    BOOST_TEST(!has_role<Ex::Rake> (v));
    move_role<Ex::Rake> (v, u);
    BOOST_TEST(!has_role<Ex::Rake> (u));
    BOOST_TEST( has_role<Ex::Rake> (v));
  }
  {
    Ex::HsupaUser u, v;
    add_role<Ex::Rake> (u);
    BOOST_TEST( has_role<Ex::Rake> (u));
    BOOST_TEST(!has_role<Ex::Rake> (v));
    move_role<Ex::Rake> (v, u);
    BOOST_TEST(!has_role<Ex::Rake> (u));
    BOOST_TEST( has_role<Ex::Rake> (v));
  }
  std::cout << __FILE__ << ":" << __LINE__ << std::endl;
  return 1 + boost::report_errors();
}

