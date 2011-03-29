/////////////////////////////////////////////////////////////////////////////
//
//  smart_ptr_test.cpp
//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) David B. Held 2002-2003.
//
//  See http://www.boost.org/ for most recent version, including documentation.
//
//  Permission is hereby granted, free of charge, to any person or organization
//  obtaining a copy of the software and accompanying documentation covered by
//  this license (the "Software") to use, reproduce, display, distribute,
//  execute, and transmit the Software, and to prepare derivative works of the
//  Software, and to permit third-parties to whom the Software is furnished to
//  do so, all subject to the following:
//
//  The copyright notices in the Software and this entire statement, including
//  the above license grant, this restriction and the following disclaimer,
//  must be included in all copies of the Software, in whole or in part, and
//  all derivative works of the Software, unless such copies or derivative
//  works are solely in the form of machine-executable object code generated by
//  a source language processor.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
//  SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
//  FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
//  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.
//
//////////////////////////////////////////////////////////////////////////////
//
//  This is the main test program for the policy-based smart pointer library.
//  All tests should pass.  The ordering_test.cpp tests the ordering comparison
//  operators (in a separate file, because they are enabled via a macro).  See
//  libs/policy_ptr/doc/index.html
//
//////////////////////////////////////////////////////////////////////////////
#define BOOST_SMART_POINTER_BASIC_INTERFACE
//#define UTILITY_OBJECT_TRACKED_TRACE_MODE
//#include "boost/utility/trace_scope.hpp"
#include "libs/utility/src/obj_id.cpp"
#include "libs/utility/src/object_tracked.cpp"
#include <string>
#include <iostream>
#include "boost/test/unit_test.hpp"
#include "boost/managed_ptr/marg_ostream_refcnt_overhead_ptr.hpp"
#define INCLUDE_REFCYCLE
#ifdef INCLUDE_REFCYCLE
#include "boost/managed_ptr/refcycle_prox_visitor_abs.hpp"
#include "boost/managed_ptr/refcycle_prox_visitor_abs.cpp"
#define TEST_CYCLE
#define TEST_STLCONT
#endif
#include "parent2children.hpp"

// Hack for VC's lack of ADL
namespace boost
{

namespace test = unit_test_framework;
using mpl::_;

class object
: public chk_dbl_die
//***DIFF_POLICY_PTR : rm'ed dead member variable because
//  its purpose is now handled by object_tracked::our_members
//  and because basis_adaptor template requires Referent
//  to have default CTOR.
{
public:
    object(void) : dummy_(3.14159) { }
    virtual ~object(void) 
    { 
    }

    int foo(void) const { return 42; }
    double bar(void) const { return dummy_; }
private:
    double dummy_;
};

class child : public object
//***DIFF_POLICY_PTR : rm'ed dead member variable
//  and made CTOR default for same reasons as cited in
//  object.
{
public:
    child(int age=0) : age_(age) { }

    int age(void) const { return age_; }
    void age_put(int a_age) { age_=a_age; }
private:
    int age_;
};

class element
: public chk_dbl_die
{
public:
    element(int a_x=-1):x_(a_x)
    {
    }
    element(element const& a_elem):x_(a_elem.x_)
    {
    }
    ~element(void)
    {
    }
    int x(void) const { return x_; }
    element& operator=(int x) { x_ = x; return *this; }

private:
    int x_;
};

class dolly
{
public:
    dolly(int x=0) : x_(x) { ++births_; }
    ~dolly() { ++deaths_; }
    int x(void) const { return x_; }
    void put_x(int a_x) { x_=a_x; }
    dolly* clone(void) const { ++births_; return new dolly(*this); }
    static int births(void) { return births_; }
    static int deaths(void) { return deaths_; }
private:
    static int births_;
    static int deaths_;
    int x_;
};

int dolly::births_;
int dolly::deaths_;

template
  < template
    < typename //ReferentPtr
    >class OwnershipPolicy
  >
  std::string
owner_policy_name
  (void)
;
template
  <
  >
  std::string
owner_policy_name
  < ref_counted
  >
  (void)
{
    return std::string("<ref_counted>::");
}

template
  <
  >
  std::string
owner_policy_name
  < managed_ptr::refcycle_counted_curry_prox_visitor
    <managed_ptr::refcycle_prox_visitor_abs>
    ::owner
  >
  (void)
{
    return std::string("<refcycle_counted>::");
}

template
  < template
    < typename //ReferentPtr
    >class OwnershipPolicy
  >
struct owner_tests
{

  static
void default_test(void)
{
  #ifdef TRACE_SCOPE_HPP
    utility::trace_scope ts(owner_policy_name<OwnershipPolicy>()+"default_test");
  #endif
    smart_ptr<object,OwnershipPolicy<_> > p;
    object* q = 0;
    BOOST_CHECK_EQUAL(sizeof(p), sizeof(object*) + sizeof(int));
    BOOST_CHECK(!p);
    BOOST_CHECK(p == q);
    BOOST_CHECK(!get_impl(p));
}

    static
void init_const_test(smart_ptr<object,OwnershipPolicy<_> > const& p)
{
  #ifdef TRACE_SCOPE_HPP
    utility::trace_scope ts(owner_policy_name<OwnershipPolicy>()+"init_const_test");
  #endif
    BOOST_CHECK_EQUAL(p->foo(), 42);
    BOOST_CHECK_EQUAL((*p).bar(), 3.14159);
}

    static
void init_test(void)
{
  #ifdef TRACE_SCOPE_HPP
    utility::trace_scope ts(owner_policy_name<OwnershipPolicy>()+"init_test");
  #endif
    utility::object_tracked::our_members.reset();
    {
        managed_ptr::basis_adaptor<OwnershipPolicy<object*> > 
          l_basis_arg(managed_ptr::default_ctor_tag);
        smart_ptr<object,OwnershipPolicy<_> > p(l_basis_arg.as_basis_source());
        BOOST_CHECK_EQUAL(use_count(p), unsigned(1));
        BOOST_CHECK_EQUAL(p->foo(), 42);
        BOOST_CHECK_EQUAL((*p).bar(), 3.14159);
        init_const_test(p);
        smart_ptr<object> q;
        BOOST_CHECK(p != q);
        BOOST_CHECK(p ? true : false);
    }
    BOOST_CHECK(utility::object_tracked::our_members.size()==0);
}

    static
void copy_test(void)
{
  #ifdef TRACE_SCOPE_HPP
    utility::trace_scope ts(owner_policy_name<OwnershipPolicy>()+"copy_test");
  #endif
    utility::object_tracked::our_members.reset();
    utility::object_tracked const* dead(0);
    {
      #ifdef TRACE_SCOPE_HPP
        utility::trace_scope ts("nest_outer");
      #endif
        typedef managed_ptr::basis_adaptor<OwnershipPolicy<object*> > 
          basis_adaptor_super_type;
        typedef typename basis_adaptor_super_type::basis_spec_type
          basis_spec_super_type;
        basis_adaptor_super_type l_object_basis(managed_ptr::default_ctor_tag);
        dead=l_object_basis.referent();
        typedef smart_ptr<object, OwnershipPolicy<_>, assert_check<_> > sp_object_type;
        sp_object_type p(l_object_basis.as_basis_source());
        BOOST_CHECK_EQUAL(use_count(p), unsigned(1));
        utility::object_tracked const* dead_child(0);
        {
          #ifdef TRACE_SCOPE_HPP
            utility::trace_scope ts("nest_inner");
          #endif
            smart_ptr<object, scalar_storage<_>, OwnershipPolicy<_> > q(p);
            BOOST_CHECK(p == q);
            BOOST_CHECK_EQUAL(q->foo(), 42);
            BOOST_CHECK_EQUAL(use_count(p), 2u );
            BOOST_CHECK_EQUAL(use_count(q), 2u );
            {
              #ifdef TRACE_SCOPE_HPP
                utility::trace_scope ts("copy_test:reset call:");
              #endif
                typedef typename basis_adaptor_super_type::template rebind<child>::other
                  basis_adaptor_der_type;
                basis_adaptor_der_type l_child_basis(managed_ptr::default_ctor_tag);
                dead_child=l_child_basis.referent();
                typename basis_adaptor_der_type::basis_source_type 
                  l_basis_adapt_der_src(l_child_basis.as_basis_source());
                reset<child>(q, l_basis_adapt_der_src);
                //***DIFF_POLICY_PTR : explicit template argument is needed
                //   because it's used in non-deduced context in the 
                //   reset declaration.
            }
            BOOST_CHECK_EQUAL(use_count(q), 1u );
            smart_ptr<child,OwnershipPolicy<_> > c(
                static_pointer_cast<child>(q)
                );
            BOOST_CHECK_EQUAL(use_count(c), 2u );
            smart_ptr<child,OwnershipPolicy<_> > d(dynamic_pointer_cast<child>(q));
            BOOST_CHECK_EQUAL(use_count(q), 3u );
        }
        BOOST_CHECK( !utility::object_tracked::our_members.contains(dead_child) );
        BOOST_CHECK_EQUAL(use_count(p), 1u );
    }
    BOOST_CHECK(!utility::object_tracked::our_members.contains(dead));
}

    static
void assign_test(void)
{
  #ifdef TRACE_SCOPE_HPP
    utility::trace_scope ts(owner_policy_name<OwnershipPolicy>()+"assign_test");
  #endif
    utility::object_tracked::our_members.reset();
    using boost::swap;
    utility::object_tracked const* dead(0);
    utility::object_tracked const* dead2(0);
    typedef smart_ptr<child,OwnershipPolicy<_> > sp_child_type;
    typedef smart_ptr<object,OwnershipPolicy<_> > sp_object_type;
    typedef managed_ptr::basis_adaptor<OwnershipPolicy<child*> > basis_adaptor_type;
    basis_adaptor_type x(managed_ptr::default_ctor_tag);
    {
        basis_adaptor_type l_child_basis(managed_ptr::default_ctor_tag);
        l_child_basis.referent()->age_put(14);
        dead = l_child_basis.referent();
        sp_child_type p(l_child_basis.as_basis_source());
        sp_object_type q;
        q = p;
        BOOST_CHECK(p == q);
        BOOST_CHECK_EQUAL(use_count(p), 2u );
        sp_child_type c;
        c = p;
        BOOST_CHECK_EQUAL(use_count(p), 3u );
        basis_adaptor_type l_child_basis2(managed_ptr::default_ctor_tag);
        l_child_basis2.referent()->age_put(27);
        dead2 = l_child_basis2.referent();
        sp_child_type d(l_child_basis2.as_basis_source());
        swap(c, d);
        BOOST_CHECK_EQUAL(d->age(), 14);
        BOOST_CHECK_EQUAL(c->age(), 27);
        BOOST_CHECK_EQUAL(use_count(c), 1u );
        basis_adaptor_type::basis_sink_type& x_basis_sink(x.as_basis_sink_ref());
        release(c, x_basis_sink);
        BOOST_CHECK(x_basis_sink != 0);
        BOOST_CHECK_EQUAL(use_count(c), 0u );
        BOOST_CHECK(!c);
    }
    BOOST_CHECK(!utility::object_tracked::our_members.contains(dead));
    BOOST_CHECK(utility::object_tracked::our_members.contains(dead2));
}

    static
void conversion_test(void)
{
  #ifdef TRACE_SCOPE_HPP
    utility::trace_scope ts(owner_policy_name<OwnershipPolicy>()+"conversion_test");
  #endif
    utility::object_tracked::our_members.reset();
    utility::object_tracked const* dead(0);
    {
        managed_ptr::basis_adaptor<OwnershipPolicy<object*> > 
          l_object_basis(managed_ptr::default_ctor_tag);
        smart_ptr<object, allow_conversion<_>, OwnershipPolicy<_> > 
          p(l_object_basis.as_basis_source());
        object* x = p;
        dead=x;
        (void) x;
    }
    BOOST_CHECK(!utility::object_tracked::our_members.contains(dead));
}

    static
void concept_interface_test(void)
{
  #ifdef TRACE_SCOPE_HPP
    utility::trace_scope ts(owner_policy_name<OwnershipPolicy>()+"concept_interface_test");
  #endif
    typedef managed_ptr::basis_adaptor<OwnershipPolicy<object*> > basis_adaptor_object_type;
    typedef smart_ptr<object, OwnershipPolicy<_> > smart_ptr_object_type;
    basis_adaptor_object_type l_objectx_basis(managed_ptr::default_ctor_tag);
    smart_ptr_object_type p(l_objectx_basis.as_basis_source());
    object* x = get_pointer(p);
    BOOST_CHECK(x == p);
    basis_adaptor_object_type l_objecty_basis(managed_ptr::default_ctor_tag);
    object& y=*(l_objecty_basis.referent());
    smart_ptr<object, OwnershipPolicy<_> > q(l_objecty_basis.as_basis_source());
    less<
        object, OwnershipPolicy<_>, assert_check<_>,
        disallow_conversion<_>, scalar_storage<_>
    > comp;
    if (x < &y)
    {
        BOOST_CHECK(comp(p, q));
    }
    else
    {
        BOOST_CHECK(comp(q, p));
    }
    release(q, l_objecty_basis.as_basis_sink_ref());
    BOOST_CHECK(!q);
}

};//end owner_tests<OwnershipPolicy> class

#ifdef TEST_CYCLE
void auto_overhead_test(void)
{
  #ifdef TRACE_SCOPE_HPP
    utility::trace_scope ts("auto_overhead_test");
  #endif
    utility::object_tracked::our_members.reset();
        typedef
      smart_ptr
        < object
        , managed_ptr::refcycle_counted_curry_prox_visitor
          < managed_ptr::refcycle_prox_visitor_abs
          >
          ::owner
          < _
          >
        >
    object_sp_type
    ;
        typedef
      object_sp_type::basis_source_type
    object_source_type
    ;
        typedef
      object_sp_type::basis_sink_type
    object_sink_type
    ;
    {
      #ifdef TRACE_SCOPE_HPP
        utility::trace_scope ts("create/destroy sink");
      #endif
          object_sink_type 
        l_obj_sink(managed_ptr::default_ctor_tag)
        ;
    }//exit create/destroy sink
    BOOST_CHECK(utility::object_tracked::our_members.size()==0);
    {
      #ifdef TRACE_SCOPE_HPP
        utility::trace_scope ts("release to source while refcount>1");
      #endif
          object_sink_type 
        l_obj_sink(managed_ptr::default_ctor_tag)
        ;
        BOOST_CHECK(l_obj_sink.is_valid());
          object_source_type 
        l_obj_source(l_obj_sink)
        ;
        {
          #ifdef TRACE_SCOPE_HPP
            utility::trace_scope ts("create sp1; sink release; destroy sp1");
          #endif
              object_sp_type
            l_obj_sp1(l_obj_source)
            ;
            BOOST_CHECK(!l_obj_sink.is_valid());
            {
              #ifdef TRACE_SCOPE_HPP
                utility::trace_scope ts("create sp2; sink release; destroy sp2");
              #endif
                  object_sp_type
                l_obj_sp2(l_obj_sp1)
                ;
                  bool
                l_caught_bad_release
                =false
                ;
                try
                {
                    release(l_obj_sp2,l_obj_sink);
                }
                catch (managed_ptr::bad_release&)
                {
                    l_caught_bad_release=true;
                }
                BOOST_CHECK(l_caught_bad_release);
                BOOST_CHECK_EQUAL(use_count(l_obj_sp1), unsigned(2));
            }
            BOOST_CHECK_EQUAL(use_count(l_obj_sp1), unsigned(1));
              bool
            l_caught_bad_release
            =false
            ;
            try
            {
                release(l_obj_sp1,l_obj_sink);
            }
            catch (managed_ptr::bad_release&)
            {
                l_caught_bad_release=true;
            }
            BOOST_CHECK(!l_caught_bad_release);
            BOOST_CHECK_EQUAL(use_count(l_obj_sp1), unsigned(0));
            BOOST_CHECK(l_obj_sink.is_valid());
        }
    }//exit release to source while refcount>1
    BOOST_CHECK(utility::object_tracked::our_members.size()==0);
}//end auto_overhead_test
#endif
void deep_copy_test(void)
{
  #ifdef TRACE_SCOPE_HPP
    utility::trace_scope ts("deep_copy_test");
  #endif
    {
        smart_ptr<dolly, deep_copy<_> > p(new dolly(8));
        BOOST_CHECK_EQUAL(sizeof(p), sizeof(dolly*));
        BOOST_CHECK_EQUAL(p->x(), 8);
        smart_ptr<dolly, deep_copy<_> > q;
        q = p;
        BOOST_CHECK(p != q);
        BOOST_CHECK_EQUAL(dolly::births(), 2);
        typedef managed_ptr::basis_specializer
          < dolly
          , managed_ptr::rm_nondeduced::nester_of<deep_copy<dolly*> >::type 
          >::basis_source_type 
          basis_source_type;
        dolly* a_newdolly=new dolly(16);
        basis_source_type a_basis=a_newdolly;
        reset(q, a_basis);
        BOOST_CHECK(p != q);
        BOOST_CHECK_EQUAL(dolly::deaths(), 1);
        BOOST_CHECK_EQUAL((*q).x(), 16);
        dolly* x = 0;
        release(q, x);
        BOOST_CHECK(x != 0);
        BOOST_CHECK(!q);
        delete x;
    }
    BOOST_CHECK_EQUAL(dolly::births(), 3);
    BOOST_CHECK_EQUAL(dolly::deaths(), 3);
}

void no_copy_test(void)
{
  #ifdef TRACE_SCOPE_HPP
    utility::trace_scope ts("no_copy_test");
  #endif
    utility::object_tracked::our_members.reset();
    utility::object_tracked const* dead(0);
    utility::object_tracked const* dead2(0);
    {
        object*object1=new object;
        dead=object1;
        smart_ptr<object, no_copy<_> > p(object1);
        BOOST_CHECK_EQUAL(sizeof(p), sizeof(object*));
        BOOST_CHECK_EQUAL(p->foo(), 42);
        object* x = 0;
        release(p, x);
        BOOST_CHECK(x != 0);
        BOOST_CHECK(!p);
        object*object2=new object;
        dead2=object2;
        reset(p, object2);
        BOOST_CHECK(p != x);
        delete x;
        smart_ptr<object>::rebind<dolly>::other q;
    }
    BOOST_CHECK(!utility::object_tracked::our_members.contains(dead));
    BOOST_CHECK(!utility::object_tracked::our_members.contains(dead2));
}

void array_test(void)
{
  #ifdef TRACE_SCOPE_HPP
    utility::trace_scope ts("array_test");
  #endif
    utility::object_tracked::our_members.reset();
    {
        smart_ptr<element, array_storage<_> > p(new element[4]);
        BOOST_CHECK_EQUAL(use_count(p), unsigned(1));
        BOOST_CHECK_EQUAL(sizeof(p), sizeof(element*) + sizeof(int));
        p[0] = 3;
        p[1] = 5;
        p[2] = 7;
        p[3] = 11;
        BOOST_CHECK_EQUAL(p[2].x(), 7);
        BOOST_CHECK_EQUAL(p[0].x(), 3);
        BOOST_CHECK_EQUAL(p[3].x(), 11);
        BOOST_CHECK_EQUAL(p[1].x(), 5);
        smart_ptr<element, array_storage<_> > q;
        q = p;
        BOOST_CHECK_EQUAL(use_count(p), unsigned(2));
        BOOST_CHECK(q == p);
        element* x;
        reset(q, 0);
        BOOST_CHECK_EQUAL(use_count(p), unsigned(1));
        release(p, x);
        BOOST_CHECK(x != 0);
        BOOST_CHECK(!p);
        reset(q, x);
    }
    BOOST_CHECK_EQUAL(utility::object_tracked::our_members.size(), 0);
}

#ifdef TEST_STLCONT
void prox_extern_array_test(void)
{
        typedef 
      managed_ptr
      ::stlcont_prox_extern
      ::scoped_cyclic_container
        < std::vector
        , element
        >
    container_type
    ;
        typedef
      smart_ptr
        < container_type
        , managed_ptr::refcycle_counted_curry_prox_visitor
          < managed_ptr::refcycle_prox_visitor_abs
          >
          ::owner
          < _
          >
        >
    container_sp_type
    ;
        typedef
      container_sp_type::basis_sink_type
    container_sink_type
    ;
        typedef
      container_sp_type::basis_source_type
    container_source_type
    ;
  #ifdef TRACE_SCOPE_HPP
    utility::trace_scope ts("prox_extern_array_test");
  #endif
    utility::object_tracked::our_members.reset();
    unsigned const container_capacity=4;
    {
      #ifdef TRACE_SCOPE_HPP
        utility::trace_scope ts("basis_source creation");
      #endif
        container_sink_type sink_container(boost::mpl::vector<int>(),container_capacity);
        container_source_type src_container(sink_container);
        container_sp_type sp_container(src_container);
        BOOST_CHECK_EQUAL(use_count(sp_container), unsigned(1));
    }
    BOOST_CHECK_EQUAL(utility::object_tracked::our_members.size(), 0);
    utility::object_tracked::our_members.reset();
    {
      #ifdef TRACE_SCOPE_HPP
        utility::trace_scope ts("block");
      #endif
        container_sink_type sink_container(boost::mpl::vector<int>(),container_capacity);
        container_source_type src_container(sink_container);
        container_sp_type p(src_container);
        BOOST_CHECK_EQUAL(use_count(p), unsigned(1));
        //BOOST_CHECK_EQUAL(sizeof(p), sizeof(element*) + sizeof(int));
        container_type& rp=*p;
        rp[0] = 3;
        rp[1] = 5;
        rp[2] = 7;
        rp[3] = 11;
        BOOST_CHECK_EQUAL(rp[2].x(), 7);
        BOOST_CHECK_EQUAL(rp[0].x(), 3);
        BOOST_CHECK_EQUAL(rp[3].x(), 11);
        BOOST_CHECK_EQUAL(rp[1].x(), 5);
        container_sp_type q;
        q = p;
        BOOST_CHECK_EQUAL(use_count(p), unsigned(2));
        BOOST_CHECK(q == p);
        {
          #ifdef TRACE_SCOPE_HPP
            utility::trace_scope ts("reset(q,z)");
          #endif
            container_sink_type z;
            reset(q, container_source_type(z));
            BOOST_CHECK(!q);
            BOOST_CHECK(!(z.is_valid()));
        }
        BOOST_CHECK_EQUAL(use_count(p), unsigned(1));
        container_sink_type x;
        container_source_type ix(x);
        {
          #ifdef TRACE_SCOPE_HPP
            utility::trace_scope ts("release(p,ix)");
          #endif
            release(p, ix);
        }
        BOOST_CHECK(x.is_valid());
        BOOST_CHECK(!p);
        {
          #ifdef TRACE_SCOPE_HPP
            utility::trace_scope ts("reset(q,ix)");
          #endif
            reset(q, ix);
        }
    }
    BOOST_CHECK_EQUAL(utility::object_tracked::our_members.size(), 0);
}
#endif

//***DIFF_POLICY_PTR : com_test and ref_linked_test rm'ed because 
//  not needed to demonstrate cycle collection.
    
}//exit boost namespace

#ifdef TEST_CYCLE

    typedef 
  boost::parent2children::parent_scalar
    < boost::ref_counted
    >
refcnt_scalar
;

    typedef
  boost::managed_ptr::refcycle_prox_visitor_abs
prox_visitor_type
;

    typedef
  boost::parent2children::parent_scalar
    < boost::managed_ptr::refcycle_counted_curry_prox_visitor
      < prox_visitor_type
      >
      ::owner 
    >
refcycle_scalar
;

DECLARE_PROX_CHILDREN_FOR_REFERENT_VISITOR(refcycle_scalar, refcycle_prox_visitor_abs)

#ifdef TEST_STLCONT
    typedef
  boost::parent2children::parent_vector
    < boost::managed_ptr::refcycle_counted_curry_prox_visitor
      < boost::managed_ptr::refcycle_prox_visitor_abs
      >
      ::owner 
    >
refcycle_vector
;

DECLARE_PROX_CHILDREN_FOR_REFERENT_VISITOR(refcycle_vector, refcycle_prox_visitor_abs)

#endif

#include "binary_node_tests.hpp"
namespace boost
{
  namespace binary_node_tests
  {
        typedef
      void(*
    test_fun_type
      )(void)
    ;
    
    template
      < test_fun_type TestFun
      >
      bool
    expect_pass
      (void)
    {
        return true;
    }
    
    template
      <
      >
      bool
    expect_pass
      < test<refcnt_scalar>::simple_cycle_1_external_sp
      >
      (void)
      {
          return false;
      }

    template
      < test_fun_type TestFun
      >
        static
      void
    run(void)
    {
      #ifdef TRACE_SCOPE_HPP
        utility::trace_scope ts("binary_node_tests::run<TestFun>");
      #endif
        utility::object_tracked::our_members.reset();
        (*TestFun)(); //Assumes that TestFun uses objects derived from object_tracked
        unsigned n_members = utility::object_tracked::our_members.size();
        BOOST_CHECK_EQUAL(n_members == 0u, expect_pass<TestFun>());
    }
    
  }//exit binary_node_tests namespace
}//exit boost namespace


namespace boost
{
namespace managed_ptr
{
struct enum_prox_children
//Purpose:
//  Enumerate the children of a node at a given depth. 
: public prox_visitor_type
{
      struct
    void_owner_set_type
      : public std::set<void_owner_type*>
    {
            friend
          marg_ostream&
        operator<<
          ( marg_ostream& sout
          , void_owner_set_type const& a_set
          )
          {
              typedef void_owner_set_type::const_iterator iter_type;
              iter_type const end=a_set.end();
              for
              ( iter_type cur=a_set.begin()
              ; cur != end
              ; ++cur
              )
              {
                  sout<<*cur<<"\n";
              }
              return sout;
          }
    };
    
      void_owner_set_type
    my_visited_children
    //The nodes that were "enumerated"
    ;
      unsigned
    my_depth
    //depth at which enumeration is done.
    ;
    enum_prox_children(unsigned a_depth)
    : my_depth(a_depth)
    {}
    
      void 
    visit_children
    ( void_owner_type& a_void_owner
    , prox_iter_acc_type& l_iter 
      //^iterator over the children of a_void_owner
    )
    {
        if(my_depth>0)
        {    
            --my_depth;
            accept_each(l_iter);
            ++my_depth;
        }
        else
        {
            my_visited_children.insert(&a_void_owner);
        }    
    }
};//end enum_prox_children

template
  < typename BinaryNode
  >
  std::string
binary_node_name
  (void)
;
  
template
  <
  >
  std::string
binary_node_name
  < refcycle_scalar
  >
  (void)
{
    return std::string("<refcycle_scalar>::");
}

#ifdef TEST_STLCONT
  
template
  <
  >
  std::string
binary_node_name
  < refcycle_vector
  >
  (void)
{
    return std::string("<refcycle_vector>::");
}

#endif
  
template
  < typename BinaryNode
  >
void refcycle_enum_children_test(void)
{
  #ifdef TRACE_SCOPE_HPP
    utility::trace_scope ts(binary_node_name<BinaryNode>()+"refcycle_enum_children_test");
  #endif
    typedef prox_children<prox_visitor_type>::prox_descriptor prox_desc_type;
    typedef prox_children<prox_visitor_type>::detail_iterators::prox_iterator_con_described 
      desc_iter_type;
    typedef BinaryNode binary_node_type;
    typedef typename binary_node_type::basis_adapt_type basis_adapt_type;
    {
        typename binary_node_type::sp_type sp_parent;
        boost::mpl::vector<void> default_ctor;
        {
          #ifdef TRACE_SCOPE_HPP
            utility::trace_scope ts("sp_parent=i.as_basis_source()");
          #endif
            basis_adapt_type i(default_ctor);
            sp_parent = i.as_basis_source();
            BOOST_CHECK(bool(sp_parent));
        }
        {
          #ifdef TRACE_SCOPE_HPP
            utility::trace_scope ts("enum_children(1)");
          #endif
            enum_prox_children enum_children(1);
            {
              #ifdef TRACE_SCOPE_HPP
                utility::trace_scope ts("left_child test");
              #endif
                basis_adapt_type i(default_ctor);
              #ifdef TRACE_SCOPE_HPP
                mout()<<":enum_children(1)::b4 = i.as_basis_source()\n";
              #endif
                sp_parent->left() = i.as_basis_source();
              #ifdef TRACE_SCOPE_HPP
                mout()<<":enum_children(1)::b4 visit_prox\n";
              #endif
                enum_children.visit_prox(sp_parent);
              #ifdef TRACE_SCOPE_HPP
                mout()<<":enum_children(1)::b4 visited_children=\n";
              #endif
                typedef enum_prox_children::void_owner_set_type void_owner_set_type;
                void_owner_set_type& visited_children=enum_children.my_visited_children;
              #ifdef TRACE_SCOPE_HPP
                mout()<<":child_count="<<visited_children.size()<<"\n";
              #endif
                void_owner_set_type all_children;
                all_children.insert
                  (static_cast<prox_visitor_type::void_owner_type*>(&(sp_parent->left())));
                bool all_found = (all_children == visited_children);
              #ifdef TRACE_SCOPE_HPP
                if(!all_found)
                {
                    mout()<<"all_children=\n"<<all_children;
                    mout()<<"visited_children=\n"<<visited_children;
                }
              #endif
                BOOST_CHECK(all_found);
            }
        }
    }
}

}//exit managed_ptr namespace
}//exit boost namespace

#endif //TEST_CYCLE

using namespace boost;

#define ADD_REFCOUNT_TESTS(OWNER_POLICY) \
    test->add(BOOST_TEST_CASE(&owner_tests<OWNER_POLICY>::default_test)); \
    test->add(BOOST_TEST_CASE(&owner_tests<OWNER_POLICY>::init_test)); \
    test->add(BOOST_TEST_CASE(&owner_tests<OWNER_POLICY>::copy_test)); \
    test->add(BOOST_TEST_CASE(&owner_tests<OWNER_POLICY>::assign_test)); \
    test->add(BOOST_TEST_CASE(&owner_tests<OWNER_POLICY>::conversion_test)); \
    test->add(BOOST_TEST_CASE(&owner_tests<OWNER_POLICY>::concept_interface_test)); \
    

test::test_suite* init_unit_test_suite(int argc, char* argv[])
{
    test::test_suite* test = BOOST_TEST_SUITE("Basic smart_ptr framework tests");
  #if 1
    test->add(BOOST_TEST_CASE(&auto_overhead_test));
    test->add(BOOST_TEST_CASE(&deep_copy_test));
    test->add(BOOST_TEST_CASE(&no_copy_test));
    test->add(BOOST_TEST_CASE(&array_test));
  #endif
  #ifdef TEST_STLCONT
    test->add(BOOST_TEST_CASE(&prox_extern_array_test));
  #endif
  #if 1
    ADD_REFCOUNT_TESTS(ref_counted);
    ADD_REFCOUNT_TESTS(managed_ptr::refcycle_counted_curry_prox_visitor<managed_ptr::refcycle_prox_visitor_abs>::owner);
  #endif
  #ifdef TEST_CYCLE
    //test->add(BOOST_TEST_CASE(&managed_ptr::refcycle_enum_children_test<refcycle_scalar>));
    #ifdef TEST_STLCONT
    test->add(BOOST_TEST_CASE(&managed_ptr::refcycle_enum_children_test<refcycle_vector>));
    #endif
    {//begin binary_node_tests
      #define BINARY_NODE_TESTS
      #ifdef BINARY_NODE_TESTS
        namespace bnt = binary_node_tests;
        #if 1
        {
            test->add(BOOST_TEST_CASE(&bnt::run<bnt::test<refcnt_scalar>::simple_list>));
            test->add(BOOST_TEST_CASE(&bnt::run<bnt::test<refcnt_scalar>::simple_cycle_1_external_sp>));
        }
        {
           test->add(BOOST_TEST_CASE(&bnt::run<bnt::test<refcycle_scalar>::simple_list>));
           test->add(BOOST_TEST_CASE(&bnt::run<bnt::test<refcycle_scalar>::simple_cycle_1_external_sp>));
           test->add(BOOST_TEST_CASE(&bnt::run<bnt::test<refcycle_scalar>::simple_cycle_2_external_sp>));
        }
        #endif
        #ifdef TEST_STLCONT
        {
            test->add(BOOST_TEST_CASE(&bnt::run<bnt::test<refcycle_vector>::simple_list>));
            test->add(BOOST_TEST_CASE(&bnt::run<bnt::test<refcycle_vector>::simple_cycle_1_external_sp>));
            test->add(BOOST_TEST_CASE(&bnt::run<bnt::test<refcycle_vector>::simple_cycle_2_external_sp>));
        }
        #endif
      #endif 
    }//end binary_node_tests
    
  #endif
  
    return test;
}