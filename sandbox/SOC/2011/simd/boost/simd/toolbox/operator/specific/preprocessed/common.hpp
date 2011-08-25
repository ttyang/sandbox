////////////////////////////////////////////////////////////////////////////////
// Register all tag and extension agnostic call for common code sharing
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  } } } namespace boost { namespace dispatch { namespace meta { template<class A0 , class Tag> inline boost :: simd :: ext :: implement< Tag(generic_< unspecified_<A0> >) , tag::cpu_ > dispatching( Tag , tag::cpu_ , generic_< unspecified_<A0> > const , adl_helper = adl_helper() ) { boost :: simd :: ext :: implement< Tag(generic_< unspecified_<A0> > ) , tag::cpu_ > that; return that; } } } } namespace boost { namespace simd { namespace ext { } } } namespace boost { namespace dispatch { namespace meta { template<class A0 , class Tag> inline boost :: simd :: ext :: implement< Tag(generic_< unspecified_<A0> > , generic_< unspecified_<A0> >) , tag::cpu_ > dispatching( Tag , tag::cpu_ , generic_< unspecified_<A0> > const , generic_< unspecified_<A0> > const , adl_helper = adl_helper() ) { boost :: simd :: ext :: implement< Tag(generic_< unspecified_<A0> > , generic_< unspecified_<A0> > ) , tag::cpu_ > that; return that; } } } } namespace boost { namespace simd { namespace ext { } } } namespace boost { namespace dispatch { namespace meta { template<class A0 , class Tag> inline boost :: simd :: ext :: implement< Tag(generic_< unspecified_<A0> > , generic_< unspecified_<A0> > , generic_< unspecified_<A0> >) , tag::cpu_ > dispatching( Tag , tag::cpu_ , generic_< unspecified_<A0> > const , generic_< unspecified_<A0> > const , generic_< unspecified_<A0> > const , adl_helper = adl_helper() ) { boost :: simd :: ext :: implement< Tag(generic_< unspecified_<A0> > , generic_< unspecified_<A0> > , generic_< unspecified_<A0> > ) , tag::cpu_ > that; return that; } } } } namespace boost { namespace simd { namespace ext { } } } namespace boost { namespace dispatch { namespace meta { template<class A0 , class Tag> inline boost :: simd :: ext :: implement< Tag(generic_< unspecified_<A0> > , generic_< unspecified_<A0> > , generic_< unspecified_<A0> > , generic_< unspecified_<A0> >) , tag::cpu_ > dispatching( Tag , tag::cpu_ , generic_< unspecified_<A0> > const , generic_< unspecified_<A0> > const , generic_< unspecified_<A0> > const , generic_< unspecified_<A0> > const , adl_helper = adl_helper() ) { boost :: simd :: ext :: implement< Tag(generic_< unspecified_<A0> > , generic_< unspecified_<A0> > , generic_< unspecified_<A0> > , generic_< unspecified_<A0> > ) , tag::cpu_ > that; return that; } } } } namespace boost { namespace simd { namespace ext { } } } namespace boost { namespace dispatch { namespace meta { template<class A0 , class Tag> inline boost :: simd :: ext :: implement< Tag(generic_< unspecified_<A0> > , generic_< unspecified_<A0> > , generic_< unspecified_<A0> > , generic_< unspecified_<A0> > , generic_< unspecified_<A0> >) , tag::cpu_ > dispatching( Tag , tag::cpu_ , generic_< unspecified_<A0> > const , generic_< unspecified_<A0> > const , generic_< unspecified_<A0> > const , generic_< unspecified_<A0> > const , generic_< unspecified_<A0> > const , adl_helper = adl_helper() ) { boost :: simd :: ext :: implement< Tag(generic_< unspecified_<A0> > , generic_< unspecified_<A0> > , generic_< unspecified_<A0> > , generic_< unspecified_<A0> > , generic_< unspecified_<A0> > ) , tag::cpu_ > that; return that; } } } } namespace boost { namespace simd { namespace ext {
} } }
////////////////////////////////////////////////////////////////////////////////
// Generate all the common map calls over Tag using boost::simd::map
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext { template<class A0,class Tag, class Dummy> struct implement<Tag( generic_< unspecified_<A0> > ), tag::cpu_, Dummy> { BOOST_SIMD_MAP_LOG(Tag); typedef typename dispatch::meta:: call<tag::map_ ( dispatch::functor<Tag> , A0 )>::type result_type; inline result_type operator()( A0 const& a0 ) const { return boost::simd::map( dispatch::functor<Tag>(), a0); } }; } } } namespace boost { namespace simd { namespace ext { template<class A0 , class A1,class Tag, class Dummy> struct implement<Tag( generic_< unspecified_<A0> > , generic_< unspecified_<A1> > ), tag::cpu_, Dummy> { BOOST_SIMD_MAP_LOG(Tag); typedef typename dispatch::meta:: call<tag::map_ ( dispatch::functor<Tag> , A0 , A1 )>::type result_type; inline result_type operator()( A0 const& a0 , A1 const& a1 ) const { return boost::simd::map( dispatch::functor<Tag>(), a0 , a1); } }; } } } namespace boost { namespace simd { namespace ext { template<class A0 , class A1 , class A2,class Tag, class Dummy> struct implement<Tag( generic_< unspecified_<A0> > , generic_< unspecified_<A1> > , generic_< unspecified_<A2> > ), tag::cpu_, Dummy> { BOOST_SIMD_MAP_LOG(Tag); typedef typename dispatch::meta:: call<tag::map_ ( dispatch::functor<Tag> , A0 , A1 , A2 )>::type result_type; inline result_type operator()( A0 const& a0 , A1 const& a1 , A2 const& a2 ) const { return boost::simd::map( dispatch::functor<Tag>(), a0 , a1 , a2); } }; } } } namespace boost { namespace simd { namespace ext { template<class A0 , class A1 , class A2 , class A3,class Tag, class Dummy> struct implement<Tag( generic_< unspecified_<A0> > , generic_< unspecified_<A1> > , generic_< unspecified_<A2> > , generic_< unspecified_<A3> > ), tag::cpu_, Dummy> { BOOST_SIMD_MAP_LOG(Tag); typedef typename dispatch::meta:: call<tag::map_ ( dispatch::functor<Tag> , A0 , A1 , A2 , A3 )>::type result_type; inline result_type operator()( A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 ) const { return boost::simd::map( dispatch::functor<Tag>(), a0 , a1 , a2 , a3); } }; } } } namespace boost { namespace simd { namespace ext { template<class A0 , class A1 , class A2 , class A3 , class A4,class Tag, class Dummy> struct implement<Tag( generic_< unspecified_<A0> > , generic_< unspecified_<A1> > , generic_< unspecified_<A2> > , generic_< unspecified_<A3> > , generic_< unspecified_<A4> > ), tag::cpu_, Dummy> { BOOST_SIMD_MAP_LOG(Tag); typedef typename dispatch::meta:: call<tag::map_ ( dispatch::functor<Tag> , A0 , A1 , A2 , A3 , A4 )>::type result_type; inline result_type operator()( A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 ) const { return boost::simd::map( dispatch::functor<Tag>(), a0 , a1 , a2 , a3 , a4); } }; } } }
