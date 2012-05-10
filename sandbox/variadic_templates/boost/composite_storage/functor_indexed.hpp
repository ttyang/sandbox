//
#ifndef BOOST_COMPOSITE_STORAGE_FUNCTOR_INDEXED_HPP_INCLUDED
#define BOOST_COMPOSITE_STORAGE_FUNCTOR_INDEXED_HPP_INCLUDED
//  (C) Copyright Larry Evans 2010.
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//====================================================================
//[switch #includes
//  These are from:
//
//    http://svn.boost.org/svn/boost/sandbox/switch/
//
  #include <boost/control/switch.hpp>
  #include <boost/control/case.hpp>
//]switch #includes
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/package_range_c.hpp>
#include <boost/mpl/front.hpp>

namespace boost
{
namespace composite_storage
{
namespace functor_indexed
//  This namespace defines support templates
//  for use of "Index Functors" taking only index arguments.
//  A "Index Functor" is a functor with the 
//  "Index Functor Interface":
//
//    IndexFunctor::result_type IndexFunctor::operator()
//    ( mpl::integral_c<IndexType,IndexValu> case_c )
//
//  where:
//    
//    IndexFunctor is an Index Functor.
//    typedef IndexFunctor::cases::value_type IndexType;
//    IndexType IndexValu;
//
{

using namespace boost::control;

  template
  < typename IndexFunctor //an Index Functor (see above).
  , typename Indexes
  >
  struct
dispatch_indexes
;
  template
  < typename IndexFunctor
  , typename IndexType
  , IndexType Start
  , IndexType Finish
  >
  struct
dispatch_indexes
  < IndexFunctor
  , mpl::range_c< IndexType, Start, Finish>
  >
{
        typedef
      typename IndexFunctor::result_type
    result_type
    ;
        typedef
      mpl::range_c< IndexType, Start, Finish>
    indexes
    ;
        static
      result_type
    apply  
      ( IndexFunctor& index_functor
      , IndexType a_index
      )
      {
            return 
          switch_<typename IndexFunctor::result_type>
            ( a_index
            , case_<typename IndexFunctor::indexes>(index_functor)
            );
      }      
};

  template
  < typename IndexFunctor
  , typename IndexType
  , IndexType... Indexes
  >
  struct
dispatch_indexes
  < IndexFunctor
  , mpl::package_c
    < IndexType
    , Indexes...
    >
  >
{
        typedef
      typename IndexFunctor::result_type
    result_type
    ;
    template<IndexType IndexVal> 
    struct fun_index
    {
            static
          result_type 
        apply(IndexFunctor& f)
        {
            mpl::integral_c<IndexType, IndexVal> arg;
            return f(arg);
        }
    };
        static
      result_type
    apply  
      ( IndexFunctor& index_functor
      , IndexType a_index
      )
      {
                static
              unsigned const
            vec_size
              = sizeof...(Indexes)
              ;
                typedef
              result_type
              (*
            fun_type
              )(IndexFunctor&)
              ;
                static 
              fun_type constexpr 
            vec_funs[vec_size]=
              { &fun_index<Indexes>::apply...
              };
                typedef typename
              mpl::front
              < mpl::package_c
                < IndexType
                , Indexes...
                >
              >::type
            start_t
              ;
              int const
            vec_offset=a_index-start_t::value;
            return vec_funs[vec_offset](index_functor);
      }
};

  template
  < typename IndexFunctor //an Index Functor (see above).
  >
  typename IndexFunctor::result_type
apply
  ( IndexFunctor& index_functor
  , typename IndexFunctor::indexes::value_type a_index
  )
{
        typedef
      dispatch_indexes
      < IndexFunctor
      , typename IndexFunctor::indexes
      >
    dispatcher;
      return 
    dispatcher::
      apply
      ( index_functor
      , a_index
      );
};

//]functor_indexed_implementation

  template
  < typename Layout
  , typename Index0=typename Layout::index_undefined 
    //***CAUTION***
    //  If Layout is a one_of_maybe container type
    //  and Index0 has the default value,
    //  then calling Layout::project<Index0::value>()
    //  gives a special_type<nothing_id> value.
    //  (see ./special_components.hpp).
  ,   template
      < typename IndexType
      , IndexType Start
      , IndexType Finish
      >class 
    Container=mpl::
    #define LAYOUT_DOMAIN_CONTAINER_PACK
    #ifdef LAYOUT_DOMAIN_CONTAINER_PACK
      package_range_c
    #else
      range_c
    #endif
  >
struct layout_domain
  /**@brief
   *  Define domain of a composite, where 'domain'
   *  means the possible values of the indexes used
   *  to retrieve some component of the composite.
   */
{
        typedef
      typename Index0::value_type
    index_type
    ;  
        typedef
        typename 
      Container
      < index_type
      , Index0::value
      , Layout::index_end::value
      >::type
    indexes
    ;
};

}//exit namespace functor_indexed

}//exit composite_storage namespace
}//exit boost namespace
#endif
