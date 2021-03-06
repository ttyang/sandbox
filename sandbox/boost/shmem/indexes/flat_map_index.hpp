//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gazta�aga 2005. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/shmem for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SHMEM_FLAT_MAP_INDEX_HPP
#define BOOST_SHMEM_FLAT_MAP_INDEX_HPP

#include <functional>
#include <utility>
#include <boost/shmem/containers/flat_map.hpp>
#include <boost/shmem/allocators/allocator.hpp>

/*!\file
   Describes index adaptor of boost::map container, to use it
   as name/shared memory index
*/

namespace boost { namespace shmem {

/*!Helper class to define typedefs from IndexTraits*/
template <class MapConfig>
struct flat_map_index_aux
{
   typedef typename MapConfig::key_type            key_type;
   typedef typename MapConfig::mapped_type         mapped_type;
   typedef typename MapConfig::segment_manager     segment_manager;
   typedef std::less<key_type>                     key_less;
   typedef std::pair<key_type, mapped_type>        value_type;
   typedef allocator<value_type, segment_manager>  allocator_type;
   typedef flat_map<key_type,  mapped_type,
                    key_less, allocator_type>      index_t;
};

/*!Index type based in flat_map. Just derives from flat_map and
   defines the interface needed by the shared named object creation class*/
template <class MapConfig>
class flat_map_index
   //Derive class from map specialization
   : public flat_map_index_aux<MapConfig>::index_t
{
   typedef flat_map_index_aux<MapConfig>        index_aux;
   typedef typename index_aux::index_t          base_type;
   typedef typename index_aux::segment_manager  segment_manager;

   public:
   /*!Constructor. Takes a pointer to the
      segment manager. Can throw*/
   flat_map_index(segment_manager *segment_mngr)
      : base_type(typename index_aux::key_less(),
                  typename index_aux::allocator_type(segment_mngr))
   {}

   /*!This reserves memory to optimize the insertion of n
      elements in the index*/
   void reserve(std::size_t n)
   {  base_type::reserve(n);  }
};

}}   //namespace boost { namespace shmem

#endif   //#ifndef BOOST_SHMEM_FLAT_MAP_INDEX_HPP
