// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_FUSE_PROPERTY_WRITER_HPP
#define BOOST_GRAPH_FUSE_PROPERTY_WRITER_HPP

#include <boost/fusion/support/pair.hpp>
#include <boost/graph/visitors.hpp>

//[reference__fuse_property_writer
namespace boost {

    template <typename Filter, typename PropertyMap, typename OutputIterator>
    ::boost::fusion::pair<
        Filter
      , property_writer<PropertyMap,OutputIterator,Filter>
    >
        fuse_property_writer(PropertyMap property_map, OutputIterator out_itr);

    //<-
    template <typename Filter, typename PropertyMap, typename OutputIterator>
    inline ::boost::fusion::pair<
        Filter
      , property_writer<PropertyMap,OutputIterator,Filter>
    >
        fuse_property_writer(PropertyMap property_map, OutputIterator out_itr)
    {
        return ::boost::fusion::pair<
            Filter
          , property_writer<PropertyMap,OutputIterator,Filter>
        >(
            property_writer<PropertyMap,OutputIterator,Filter>(
                property_map
              , out_itr
            )
        );
    }
    //->
}  // namespace boost
//]

#endif  // BOOST_GRAPH_FUSE_PROPERTY_WRITER_HPP

