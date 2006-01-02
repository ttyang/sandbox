//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gazta�aga 2005. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/shmem for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_SHMEM_MAP_INDEX_HPP
#define BOOST_SHMEM_MAP_INDEX_HPP

#include <functional>
#include <utility>
#include <boost/shmem/containers/map.hpp>
#include <boost/shmem/allocators/private_node_allocator.hpp>

/*!\file
   Describes index adaptor of boost::map container, to use it
   as name/shared memory index
*/

namespace boost { namespace shmem {

/*!Helper class to define typedefs from IndexTraits*/
template <class MapConfig>
struct map_index_aux
{
   typedef typename MapConfig::key_type                  key_type;
   typedef typename MapConfig::mapped_type               mapped_type;
   typedef std::less<key_type>                           key_less;
   typedef std::pair<const key_type, mapped_type>        value_type;
   typedef private_node_pool
            <value_type,
               64,
               typename MapConfig::segment_manager>     allocator_type;
   typedef boost::shmem::map<key_type,  mapped_type,
                             key_less, allocator_type>   index_t;
};

/*!Index type based in boost::shmem::map. Just derives from boost::shmem::map 
   and defines the interface needed by the shared named object creation class*/
template <class MapConfig>
class map_index
   //Derive class from map specialization
   : public map_index_aux<MapConfig>::index_t
{
   typedef map_index_aux<MapConfig>             index_aux;
   typedef typename index_aux::index_t          base_type;
   typedef typename MapConfig::segment_manager  segment_manager;

 public:
   /*!Constructor. Takes a pointer to the memory 
      allocation algorithm. Can throw*/
   map_index(segment_manager *segment_mngr)
      : base_type(typename index_aux::key_less(),
                  segment_mngr){}

   /*!This reserves memory to optimize the insertion of n
      elements in the index*/
   void reserve(std::size_t n)
      {  /*Does nothing, map has not reserve or rehash*/  }
};

/*!Trait classes to detect if an index is a node
   index. This allows more efficient operations
   when deallocating named objects.*/
template<class MapConfig>
struct is_node_index
   <boost::shmem::map_index<MapConfig> >
{
   enum {   value = true };
};

}}   //namespace boost { namespace shmem {

#endif   //#ifndef BOOST_SHMEM_MAP_INDEX_HPP
