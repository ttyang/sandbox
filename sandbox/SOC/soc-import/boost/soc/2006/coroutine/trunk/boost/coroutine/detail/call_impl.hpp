#ifndef BOOST_COROUTINE_DETAIL_CALL_IMPL_HPP_20060728
#define BOOST_COROUTINE_DETAIL_CALL_IMPL_HPP_20060728

#include <boost/preprocessor/repetition.hpp>
#include <boost/call_traits.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/bind.hpp>
#include <boost/coroutine/coroutine.hpp>
#include <boost/coroutine/detail/arg_max.hpp>
#include <boost/coroutine/detail/signal.hpp>
#include <boost/coroutine/detail/coroutine_accessor.hpp>
namespace boost { namespace coroutines { namespace detail {

#define BOOST_COROUTINE_tuple_param_n(z, n, tuple)\
  BOOST_DEDUCED_TYPENAME                          \
  boost::tuples::element<n, tuple>::type          \
  BOOST_PP_CAT(arg, n)                            \
  /**/

  template<typename Future, typename CoroutineSelf>                       
  class callback {
  public:
    typedef BOOST_DEDUCED_TYPENAME 
    CoroutineSelf::coroutine_type 
    coroutine_type;

    typedef void result_type;
    
    callback(Future& future, 
	     CoroutineSelf& coroutine_self) :
      m_future(future),
      m_pimpl(coroutine_accessor::get_impl(coroutine_self)){
      wait_gateway::mark_pending(m_future);
    }
    
    typedef BOOST_DEDUCED_TYPENAME                
    Future::tuple_type tuple_type;              

    typedef BOOST_DEDUCED_TYPENAME                
    Future::tuple_traits_type tuple_traits_type;              


#define BOOST_COROUTINE_gen_argn_type(z, n, unused) \
    typedef BOOST_DEDUCED_TYPENAME                  \
    tuple_traits_type::                             \
    template at<n>::type                            \
    BOOST_PP_CAT(BOOST_PP_CAT(arg, n), _type);      \
    /**/

    BOOST_PP_REPEAT(BOOST_COROUTINE_ARG_MAX,
		    BOOST_COROUTINE_gen_argn_type,
		    ~);
      
#define BOOST_COROUTINE_param_with_default(z, n, type_prefix) \
    BOOST_DEDUCED_TYPENAME call_traits                   \
    <BOOST_PP_CAT(BOOST_PP_CAT(type_prefix, n), _type)>  \
    ::param_type                                         \
    BOOST_PP_CAT(arg, n) =                               \
    BOOST_PP_CAT(BOOST_PP_CAT(type_prefix, n), _type)()  \
/**/
    
    void operator() 
      (BOOST_PP_ENUM
       (BOOST_COROUTINE_ARG_MAX,
	BOOST_COROUTINE_param_with_default,
	arg)) {
      wait_gateway::assign(m_future,tuple_type
	(BOOST_PP_ENUM_PARAMS
	 (BOOST_COROUTINE_ARG_MAX, arg)));
      if(m_pimpl->signal()) {
	m_pimpl->invoke();
      }
    }

  private:
    Future& m_future;
    BOOST_DEDUCED_TYPENAME coroutine_type::impl_ptr m_pimpl;
  };  
  
  /* 
   * Asio does not support movable types yet,
   * so for now this adapter will reference count
   * a coroutine<void()>.
   * This adapter takes ownership of the coroutine,
   * that will be destroyed when the adapter is destroyed
   * (usually after its operator() has completed).
   * To extend the lifetime of the coroutine_impl object
   * use make_callback().
   */
  class asio_adapter {
  public:
    typedef coroutine<void()> coroutine_type;

    asio_adapter(move_from<coroutine_type> coroutine) :
      m_pimpl(coroutine_accessor::get_impl(*coroutine)){
    }

    void operator()() {
      BOOST_ASSERT(m_pimpl);

      coroutine_type::arg_slot_type 
        void_args;

      coroutine_type::result_slot_type 
        void_result;
      // This binding is required because
      // do_call expect args() and result()
      // to return a non NULL result.
      m_pimpl->bind_args(&void_args);
      m_pimpl->bind_result(&void_result);

      m_pimpl->invoke();
    }
    coroutine_type::impl_ptr m_pimpl;
  };

#undef BOOST_COROUTINE_gen_future_assigner
#undef BOOST_COROUTINE_tuple_param_n

  template<typename Future, typename Functor, typename CoroutineSelf>
  Future call_impl(Functor fun, const CoroutineSelf& coro_self) {
    Future future;
    fun(callback<Future, CoroutineSelf>(future, coro_self));
    return future;
  }

} } }

#endif
