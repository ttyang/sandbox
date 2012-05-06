//Purpose:
//  The following code is modified from that in the
//  original code[oc]:
//
//    http://svn.boost.org/svn/boost/trunk/libs/variant/test/variant_visit_test.cpp
//
//  as it was on 2012-04-20.
//
//  The purpose is to show that the following code:
//
//    http://svn.boost.org/svn/boost/sandbox/variadic_templates/boost/composite_storage/pack/multiple_dispatch/
//
//  can be used as an alternative implementation.
//
//-----------------------------------------------------------------------------
#include <boost/utility/demangled_type_name.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/arg.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/test/minimal.hpp>

//#define MULTIPLE_DISPATCH_DEBUG
//#define MULTIPLE_DISPATCH_TEMP_DEBUG
#include <boost/composite_storage/pack/multiple_dispatch/reify_apply.hpp>
  #include <boost/composite_storage/pack/multiple_dispatch/reifier_switch.hpp>
  #include <boost/composite_storage/pack/multiple_dispatch/reifier_funvec.hpp>
#include <boost/composite_storage/pack/container_one_of_maybe.hpp>
#include <deque>

namespace bcst=::boost::composite_storage;
namespace bcsp=bcst::pack;
namespace bmpl=::boost::mpl;

typedef unsigned instances_t;
//#define UDT_INSTANCES_TRACE
struct udt_instances
/**@brief
 *  Used to check how many instances
 *  are created.  This is useful
 *  to demonstrate that no unnecessary
 *  CTOR's are called.
 */
{
    static instances_t _(){ return our_instances;}
    instances_t instance()const{ return my_instance;}
    udt_instances()
    : my_instance(our_instances++)
    {
      #ifdef UDT_INSTANCES_TRACE
        std::cout<<":udt_instances():instance()="<<instance()<<"\n";
      #endif
    }
    udt_instances(udt_instances const&from)
    : my_instance(our_instances++)
    {
      #ifdef UDT_INSTANCES_TRACE
        std::cout<<":udt_instances(udt_instances const&from):from.instance()="
        <<from.instance()
        <<":this->instance()="<<this->instance()<<"\n";
      #endif
    }
    void operator=(udt_instances const&){}
 protected:
    static instances_t our_instances;
 private:
    instances_t my_instance;
}; 
instances_t udt_instances::our_instances=0;

template<unsigned Id>
struct udt
/**@brief
 *  This template is used in place of the
 *  udt1 and udt2 structs in [oc].
 */
: public udt_instances
{
 public:
    instances_t val()const{ return my_val;}
    udt()
    : my_val(this->instance())
    {}
    udt( instances_t a_val)
    : my_val( a_val)
    {}
      char 
    pad[Id+1]
      /**@brief
       *  To assure offset of my_val is
       *  different depending on Id.
       *  This *may* be useful in checking
       *  that the proper value type has
       *  been stored in the variant.
       *  However, this has not been tested
       *  yet(2012-05-03).
       */
    ;
 private:
    instances_t my_val;
};

template<unsigned Id>
  std::ostream&
operator<<
  ( std::ostream& sout
  , udt<Id>const& x
  )
{
    sout<<"udt<"<<Id<<">\n"
    <<"  .instance()="<<x.instance()
    <<"  .val()="<<x.val()
    <<"\n";
    return sout;
}

template <typename... T>
class nary_check_content_type
/**@brief
 *  This template is used in place of the templates:
 *    unary_check_content_type
 *    binary_check_content_type
 *  in [oc]
 */
{
public:

    typedef bool result_type;
    
    nary_check_content_type
      (
      )
        {}
      template <typename... U>
      result_type 
    operator()
      ( U&... u
      ) const
        {
                typedef typename
              bmpl::and_
              < typename ::boost::is_same
                < T
                , U
                >::type...
              >
              ::type
            all_same_t;  
          #if 0
            std::cout
            <<__FILE__<<":"<<__LINE__
            <<":nary_check_content_type "
            <<"\n:T="
            <<utility::demangled_type_names<T...>()
            <<"\n:U="
            <<utility::demangled_type_names<U...>()
            <<"\n";
          #endif
            bool result_value=all_same_t::value;
            return result_value;
        }

};

  template 
  < typename Checker
  , typename... Variant
  >
  inline void 
nary_test
  ( Checker& checker
  , Variant&... var
  )
  /**@brief
   *  
   *  This template is used in place of the templates:
   *    unary_test
   *    binary_test
   *  in [oc]
   */  
{
    // standard tests
    
        typedef 
      bool 
    result_type;
      result_type 
    result_valu=
      bcsp::multiple_dispatch::reify_apply
      < bcsp::multiple_dispatch::
      #if 0
        reifier_switch
      #else
        reifier_funvec
      #endif
      >
      ( checker
      , var...
      )
      ;
    BOOST_CHECK( result_valu);
}

int test_main(int , char* [])
{
      unsigned const
    index0=0;
      unsigned const
    uns1=index0+0;
      unsigned const
    uns2=index0+1;
      bmpl::integral_c<unsigned,uns1> const
    ndx1;
      bmpl::integral_c<unsigned,uns2> const
    ndx2;
       typedef
      udt<uns1>
    udt1; 
       typedef
      udt<uns2>
    udt2;
        typedef
      bcst::special_components::special_type
      < bcst::special_components::nothing_id
      >
    nothing_t;
        typedef 
      bcsp::container 
      < bcst::tags::one_of_maybe
      , bmpl::integral_c<unsigned,index0>
      , udt1
      , udt2 
      >
    var_t;
      var_t 
    var_nothing
      //This instance of var_t did not occur in [oc]
      //because boost::variant doesn't allow it.
      //IOW, with a boost::variant, the actual type of
      //the value stored in the variant is always one
      //of the variant's bound types.
      //  http://www.boost.org/doc/libs/1_49_0/doc/html/variant/design.html#variant.design.never-empty
      //In contrast, the default CTOR for var_t results
      //in a nothing_t stored in the var_t instance.
      ;
    {
        int which=var_nothing.which();
        std::cout<<"var_nothing.which()="<<which<<"\n";
        BOOST_CHECK(which==var_t::index_undefined::value);
    }
      var_t 
    var1
      ( ndx1
      );
    {
        int which=var1.which();
        std::cout<<"var1.which()="<<which<<"\n";
        BOOST_CHECK(which==int(uns1));
        std::cout<<"var1.project<"<<uns1<<">().instance()="<<var1.project<uns1>().instance()<<"\n";
    }
      var_t 
    var2
      ( ndx2
      );
    {
        int which=var2.which();
        std::cout<<"var2.which()="<<which<<"\n";
        BOOST_CHECK(which==int(uns2));
        std::cout<<"var2.project<"<<uns2<<">().instance()="<<var2.project<uns2>().instance()<<"\n";
    }
      
    const var_t& cvar1 = var1;
    const var_t& cvar2 = var2;

    //
    // unary tests
    //
 
    typedef nary_check_content_type< nothing_t> check1nothing_t;
    typedef nary_check_content_type< udt1> check1_t;
    typedef nary_check_content_type< udt1 const> check1_const_t;
    typedef nary_check_content_type< udt2> check2_t;
    typedef nary_check_content_type< udt2 const> check2_const_t;

  #if 1
    //The next test has no counterpart in [oc] due to reasons 
    //given in comments under var_nothing declaration.
    check1nothing_t check1nothing_v;
    std::cout<<"test(check1nothing_v,var_nothing)\n";
    nary_test< check1nothing_t>( check1nothing_v, var_nothing);

    //The following tests all have counterparts in [oc].
    check1_t check1_v;
    std::cout<<"test(check1_v,var1)\n";
    nary_test< check1_t>( check1_v, var1);
    check1_const_t check1_const_v;
    std::cout<<"test(check1_const_v,cvar1)\n";
    nary_test< check1_const_t>( check1_const_v, cvar1);
 
    check2_t check2_v;
    std::cout<<"test(check2_v,var2)\n";
    nary_test< check2_t       >( check2_v, var2);
    check2_const_t check2_const_v;
    std::cout<<"test(check2_const_v,cvar2)\n";
    nary_test< check2_const_t >( check2_const_v, cvar2);
 
    //
    // nary tests
    //
    
    typedef nary_check_content_type<      udt1,       udt2 > check12_t;
    typedef nary_check_content_type<const udt1, const udt2 > check12_const_t;
    typedef nary_check_content_type<      udt2,       udt1 > check21_t;
    typedef nary_check_content_type<const udt2, const udt1 > check21_const_t;
 
    check12_t check12_v;
    std::cout<<"test(check12_v,var1,var2)\n";
    nary_test< check12_t       >( check12_v      ,  var1,  var2);
    check12_const_t check12_const_v;
    std::cout<<"test(check12_const_v,cvar1,cvar2)\n";
    nary_test< check12_const_t >( check12_const_v, cvar1, cvar2);
 
    check21_t check21_v;
    std::cout<<"test(check21_v,var2,var1)\n";
    nary_test< check21_t       >( check21_v      ,  var2,  var1);
    check21_const_t check21_const_v;
    std::cout<<"test(check21_const_v,cvar2,cvar1)\n";
    nary_test< check21_const_t >( check21_const_v, cvar2, cvar1);
  #endif
    return boost::exit_success;
}
