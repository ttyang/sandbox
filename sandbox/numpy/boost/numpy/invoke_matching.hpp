#ifndef BOOST_NUMPY_INVOKE_MATCHING_HPP_INCLUDED
#define BOOST_NUMPY_INVOKE_MATCHING_HPP_INCLUDED

/**
 *  @file boost/numpy/invoke_matching.hpp
 *  @brief Template invocation based on dtype matching.
 */

#include <boost/numpy/dtype.hpp>
#include <boost/numpy/ndarray.hpp>

#include <boost/mpl/integral_c.hpp>

namespace boost 
{
namespace numpy 
{
namespace detail 
{

struct add_pointer_meta 
{
  template <typename T>
  struct apply 
  {
    typedef typename boost::add_pointer<T>::type type;
  };

};

struct dtype_template_match_found {};
struct nd_template_match_found {};

template <typename Function>
struct dtype_template_invoker 
{
    
  template <typename T>
  void operator()(T *) const 
  {
    if (dtype::get_builtin<T>() == m_dtype) 
    {
      m_func.template apply<T>();
      throw dtype_template_match_found();
    }
  }

  dtype_template_invoker(dtype const & dtype_, Function func) 
    : m_dtype(dtype_), m_func(func) {}

private:
  dtype const & m_dtype;
  Function m_func;
};

template <typename Function>
struct dtype_template_invoker< boost::reference_wrapper<Function> > 
{
    
  template <typename T>
  void operator()(T *) const 
  {
    if (dtype::get_builtin<T>() == m_dtype) 
    {
      m_func.template apply<T>();
      throw dtype_template_match_found();
    }
  }

  dtype_template_invoker(dtype const & dtype_, Function & func)
    : m_dtype(dtype_), m_func(func) {}

private:
  dtype const & m_dtype;
  Function & m_func;
};

template <typename Function>
struct nd_template_invoker 
{    
  template <int N>
  void operator()(boost::mpl::integral_c<int,N> *) const 
  {
    if (m_nd == N) 
    {
      m_func.template apply<N>();
      throw nd_template_match_found();
    }
  }

  nd_template_invoker(int nd, Function func) : m_nd(nd), m_func(func) {}

private:
  int m_nd;
  Function m_func;
};

template <typename Function>
struct nd_template_invoker< boost::reference_wrapper<Function> > 
{    
  template <int N>
  void operator()(boost::mpl::integral_c<int,N> *) const 
  {
    if (m_nd == N) 
    {
      m_func.template apply<N>();
      throw nd_template_match_found();
    }
  }

  nd_template_invoker(int nd, Function & func) : m_nd(nd), m_func(func) {}

private:
  int m_nd;
  Function & m_func;
};

} // namespace boost::numpy::detail

template <typename Sequence, typename Function>
void invoke_matching_nd(int nd, Function f) 
{
  detail::nd_template_invoker<Function> invoker(nd, f);
  try { boost::mpl::for_each< Sequence, detail::add_pointer_meta >(invoker);}
  catch (detail::nd_template_match_found &) { return;}
  PyErr_SetString(PyExc_TypeError, "number of dimensions not found in template list.");
  python::throw_error_already_set();
}

template <typename Sequence, typename Function>
void invoke_matching_dtype(dtype const & dtype_, Function f) 
{
  detail::dtype_template_invoker<Function> invoker(dtype_, f);
  try { boost::mpl::for_each< Sequence, detail::add_pointer_meta >(invoker);}
  catch (detail::dtype_template_match_found &) { return;}
  PyErr_SetString(PyExc_TypeError, "dtype not found in template list.");
  python::throw_error_already_set();
}

namespace detail 
{

template <typename T, typename Function>
struct array_template_invoker_wrapper_2 
{
  template <int N>
  void apply() const { m_func.template apply<T,N>();}
  array_template_invoker_wrapper_2(Function & func) : m_func(func) {}

private:
  Function & m_func;
};

template <typename DimSequence, typename Function>
struct array_template_invoker_wrapper_1 
{
  template <typename T>
  void apply() const { invoke_matching_nd<DimSequence>(m_nd, array_template_invoker_wrapper_2<T,Function>(m_func));}
  array_template_invoker_wrapper_1(int nd, Function & func) : m_nd(nd), m_func(func) {}

private:
  int m_nd;
  Function & m_func;
};

template <typename DimSequence, typename Function>
struct array_template_invoker_wrapper_1< DimSequence, boost::reference_wrapper<Function> >
  : public array_template_invoker_wrapper_1< DimSequence, Function >
{
  array_template_invoker_wrapper_1(int nd, Function & func)
    : array_template_invoker_wrapper_1< DimSequence, Function >(nd, func) {}
};

} // namespace boost::numpy::detail

template <typename TypeSequence, typename DimSequence, typename Function>
void invoke_matching_array(ndarray const & array_, Function f) 
{
  detail::array_template_invoker_wrapper_1<DimSequence,Function> wrapper(array_.get_nd(), f);
  invoke_matching_dtype<TypeSequence>(array_.get_dtype(), wrapper);
}

} // namespace boost::numpy
} // namespace boost

#endif // !BOOST_NUMPY_INVOKE_MATCHING_HPP_INCLUDED
