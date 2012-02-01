
#include <boost/local_function.hpp>
#define BOOST_TEST_MODULE TestImplFactorial
#include <boost/test/unit_test.hppp>
#include <vector>
#include <algorithm>

struct calculator {
    std::vector<int> results;
    void factorials(const std::vector<int>& nums) {
        int // The local function result type (just before the `BOOST_LOCAL_FUNCTION_PARAMS` macro).

        // *BEGIN* The macro
        //  BOOST_LOCAL_FUNCTION(bind this_, int num,
        //          bool recursion, default false)
        // expands (at line/counter 19) to:

        // DEDUCE RESULT TYPE
        // Long name `ERROR_...` gives meaningful compiler-error message if
        // programmers forget result type before the macro. 
        (*
  ERROR_missing_result_type_before_the_local_function_parameter_macro_id19
        )(); 
        // Use Boost.ScopeExit type deduction technique (tagging, wrapping,
        // struct, etc) so to work on all compilers (specifically, some GCC
        // version give internal errors otherwise).
        typedef void (*boost_local_function_auxXdeduce_result_tagX19X)(int 
  ERROR_missing_result_type_before_the_local_function_parameter_macro_id19
                ) ; 
        typedef BOOST_TYPEOF(::boost::scope_exit::detail::wrap(
                ::boost::scope_exit::detail::deref( 
  ERROR_missing_result_type_before_the_local_function_parameter_macro_id19, 
                        (boost_local_function_auxXdeduce_result_tagX19X)0 ) ))
                boost_local_function_auxXdeduce_result_wrapX19X ;
        typedef boost_local_function_auxXdeduce_result_wrapX19X::type
                boost_local_function_auxXdeduce_result_captureX19X ; 
        struct boost_local_function_auxXdeduce_result_paramsX19X {
            typedef boost_local_function_auxXdeduce_result_captureX19X
                    function_ptr;
        };
        typedef ::boost::remove_pointer<
                boost_local_function_auxXdeduce_result_paramsX19X::
                function_ptr >::type 
                boost_local_function_auxXdeduce_result_function_typeX19X ; 
        typedef ::boost::function_traits< 
                boost_local_function_auxXdeduce_result_function_typeX19X 
                >::result_type 
                boost_local_function_auxXresult_typeX19X ; 
        
        // HANDLE BOUND VARIABLES
        // Deduce bound variable types.
#if BOSOT_WORKAROUND(BOOST_MSVC, >= 1300)
        enum {
            boost_se_this_type_indexX19X = sizeof(
                    *boost::scope_exit::msvc_typeof_this::encode_start(this))
        };
        typedef boost::scope_exit::msvc_typeof_this::msvc_typeid_wrapper<
                boost::se_this_type_indexX19X>::type
                boost_local_function_auxXthis_typeX19X;
#else
        typedef BOOST_TYPEOF(this) boost_local_function_auxXthis_typeX19X;
#endif
        // Store bound variables (by reference or value).
        struct boost_se_params_t_19 {
            boost_local_function_auxXthis_typeX19X 
                    boost_local_function_auxXthis_varX;
        } boost_local_function_auxXparamsX19X = { this };
        // Set bound variables in variable `...args` without line/counter
        // postfix so it can be accessed also by different macro NAME (so this
        // variable must be declared using a template meta-programming thick
        // that will declare it only once in each scope, no-op otherwise).
        ::boost::scope_exit::detail::declared<
            boost::scope_exit::detail::resolve< 
                sizeof(boost_local_function_auxXargsX) 
            >::cmp1<0>::cmp2 
        > boost_local_function_auxXargsX;
        boost_local_function_auxXargsX.value =
                &boost_local_function_auxXparamsX19X;
        
        // LOCAL FUNCTOR
        class boost_local_function_auxXfunctorX19X {
            typedef boost_local_function_auxXresult_typeX19X
                    (boost_local_function_auxXfunction_typeX)
                    ( int num , bool recursion ); 
            typedef boost::function_traits< void (
                ::boost::local_function::aux::function< 
                    boost_local_function_auxXfunction_typeX , 1 , boost_local_function_auxXthis_typeX19X , ::boost::local_function::aux::nobind_t , ::boost::local_function::aux::nobind_t , ::boost::local_function::aux::nobind_t , ::boost::local_function::aux::nobind_t , ::boost::local_function::aux::nobind_t , ::boost::local_function::aux::nobind_t , ::boost::local_function::aux::nobind_t , ::boost::local_function::aux::nobind_t , ::boost::local_function::aux::nobind_t > ) >::arg1_type boost_local_function_auxXfunctor_typeX ; typedef boost_local_function_auxXthis_typeX19X this_Xtypeof_typeXboost_local_function_auxX ; public: enum { arity = ::boost::function_traits< boost_local_function_auxXfunction_typeX >::arity }; typedef boost_local_function_auxXresult_typeX19X result_type; typedef ::boost::function_traits< boost_local_function_auxXfunction_typeX >::arg1_type arg1_type ; typedef ::boost::function_traits< boost_local_function_auxXfunction_typeX >::arg2_type arg2_type ; inline explicit boost_local_function_auxXfunctorX19X( void* bind_params) : boost_local_function_auxXbind_thisX( static_cast< boost_se_params_t_19* >( bind_params)-> boost_local_function_auxXthis_varX ) { } inline boost_local_function_auxXresult_typeX19X operator()( ::boost::call_traits< ::boost::function_traits< boost_local_function_auxXfunction_typeX >::arg1_type >::param_type arg1 , ::boost::call_traits< ::boost::function_traits< boost_local_function_auxXfunction_typeX >::arg2_type >::param_type arg2 ) { return boost_local_function_auxXbodyX( boost_local_function_auxXbind_thisX , arg1 , arg2 ); } inline boost_local_function_auxXresult_typeX19X operator()( ::boost::call_traits< ::boost::function_traits< boost_local_function_auxXfunction_typeX >::arg1_type >::param_type arg1 ) { return boost_local_function_auxXbodyX( boost_local_function_auxXbind_thisX , arg1 ); } inline static boost_local_function_auxXresult_typeX19X boost_local_function_auxXcallX0X( void* object , boost_local_function_auxXthis_typeX19X & bind_this , ::boost::local_function::aux::nobind_t & , ::boost::local_function::aux::nobind_t & , ::boost::local_function::aux::nobind_t & , ::boost::local_function::aux::nobind_t & , ::boost::local_function::aux::nobind_t & , ::boost::local_function::aux::nobind_t & , ::boost::local_function::aux::nobind_t & , ::boost::local_function::aux::nobind_t & , ::boost::local_function::aux::nobind_t & , ::boost::call_traits< ::boost::function_traits< boost_local_function_auxXfunction_typeX >::arg1_type >::param_type arg1 , ::boost::call_traits< ::boost::function_traits< boost_local_function_auxXfunction_typeX >::arg2_type >::param_type arg2 ) { return static_cast< boost_local_function_auxXfunctorX19X* >(object)-> boost_local_function_auxXbodyX( bind_this , arg1 , arg2 ) ; } inline static boost_local_function_auxXresult_typeX19X boost_local_function_auxXcallX1X( void* object , boost_local_function_auxXthis_typeX19X & bind_this , ::boost::local_function::aux::nobind_t & , ::boost::local_function::aux::nobind_t & , ::boost::local_function::aux::nobind_t & , ::boost::local_function::aux::nobind_t & , ::boost::local_function::aux::nobind_t & , ::boost::local_function::aux::nobind_t & , ::boost::local_function::aux::nobind_t & , ::boost::local_function::aux::nobind_t & , ::boost::local_function::aux::nobind_t & , ::boost::call_traits< ::boost::function_traits< boost_local_function_auxXfunction_typeX >::arg1_type >::param_type arg1 ) { return static_cast< boost_local_function_auxXfunctorX19X* >(object)-> boost_local_function_auxXbodyX( bind_this , arg1 ) ; } inline static void boost_local_function_auxXinit_callX( void* object , boost_local_function_auxXfunctor_typeX& functor ) { functor.boost_local_function_auxXinit_callX( object , static_cast< boost_local_function_auxXfunctorX19X* >( object)->boost_local_function_auxXbind_thisX , ::boost::local_function::aux::nobind , ::boost::local_function::aux::nobind , ::boost::local_function::aux::nobind , ::boost::local_function::aux::nobind , ::boost::local_function::aux::nobind , ::boost::local_function::aux::nobind , ::boost::local_function::aux::nobind , ::boost::local_function::aux::nobind , ::boost::local_function::aux::nobind , &boost_local_function_auxXcallX0X , &boost_local_function_auxXcallX1X ); } private: boost_local_function_auxXthis_typeX19X boost_local_function_auxXbind_thisX ; boost::scope_exit::detail::undeclared boost_local_function_auxXargsX; inline boost_local_function_auxXresult_typeX19X boost_local_function_auxXbodyX( boost_local_function_auxXthis_typeX19X const this_ , int num , bool recursion = false ) {
            int result = 0;
            if(num <= 0) result = 1;
            else result = num * factorial(num - 1, true);
            if(!recursion) this_->results.push_back(result);
            return result;
        } public: boost_local_function_auxXfunctor_typeX factorial; inline void boost_local_function_auxXinit_recursionX( boost_local_function_auxXfunctor_typeX& functor) { factorial = functor; } } boost_local_function_auxXfactorialX(boost_local_function_auxXargsX.value); __typeof__(boost::type_of::ensure_obj(boost_local_function_auxXfactorialX. factorial)) factorial; boost_local_function_auxXfactorialX.boost_local_function_auxXinit_callX( &boost_local_function_auxXfactorialX, factorial); boost_local_function_auxXfactorialX.boost_local_function_auxXinit_recursionX( factorial);
        std::for_each(nums.begin(), nums.end(), factorial);
    }
};

BOOST_AUTO_TEST_CASE( test_impl_factorial ) {
    std::vector<int> v(3);
    v[0] = 1; v[1] = 3; v[2] = 4;
    calculator calc;
    calc.factorials(v);

    BOOST_CHECK( cals.results[0] == 1 );
    BOOST_CHECK( cals.results[1] == 6 );
    BOOST_CHECK( cals.results[2] == 24 );
}
