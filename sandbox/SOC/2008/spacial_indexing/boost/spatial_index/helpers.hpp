//
// Boost.SpatialIndex - geometry helper functions
//
// Copyright 2008 Federico J. Fernandez.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/ for latest version.
//


#ifndef BOOST_SPATIAL_INDEX_HELPERS_HPP
#define BOOST_SPATIAL_INDEX_HELPERS_HPP

namespace boost
{
  namespace spatial_index
  {


    /// given two boxes, create the minimal box that contains them
    template < typename Point >
      geometry::box < Point > enlarge_box(const geometry::box < Point > &b1,
                                          const geometry::box < Point > &b2)
    {
      Point min(geometry::get < 0 > (b1.min()) < geometry::get < 0 >
                (b2.min())? geometry::get < 0 > (b1.min()) : geometry::get < 0 >
                (b2.min()),
                geometry::get < 1 > (b1.min()) < geometry::get < 1 >
                (b2.min())? geometry::get < 1 > (b1.min()) : geometry::get < 1 >
                (b2.min()));

      Point max(geometry::get < 0 > (b1.max()) > geometry::get < 0 >
                (b2.max())? geometry::get < 0 > (b1.max()) : geometry::get < 0 >
                (b2.max()),
                geometry::get < 1 > (b1.max()) > geometry::get < 1 >
                (b2.max())? geometry::get < 1 > (b1.max()) : geometry::get < 1 >
                (b2.max()));

        return geometry::box < Point > (min, max);
    }

    /// compute the area of the union of b1 and b2
    template < typename Point >
      double compute_union_area(const geometry::box < Point > &b1,
                                const geometry::box < Point > &b2)
    {
      geometry::box < Point > enlarged_box = enlarge_box(b1, b2);
      return geometry::area(enlarged_box);
    }


    template < typename Point >
      bool overlaps(const geometry::box < Point > &b1,
                    const geometry::box < Point > &b2)
    {

      bool overlaps_x, overlaps_y;
      overlaps_x = overlaps_y = false;

      if (geometry::get < 0 > (b1.min()) >= geometry::get < 0 > (b2.min())
          && geometry::get < 0 > (b1.min()) <= geometry::get < 0 > (b2.max()))
        {
          overlaps_x = true;
        }
      if (geometry::get < 0 > (b1.max()) >= geometry::get < 0 > (b2.min())
          && geometry::get < 0 > (b1.min()) <= geometry::get < 0 > (b2.max()))
        {
          overlaps_x = true;
        }

      if (geometry::get < 1 > (b1.min()) >= geometry::get < 1 > (b2.min())
          && geometry::get < 1 > (b1.min()) <= geometry::get < 1 > (b2.max()))
        {
          overlaps_y = true;
        }
      if (geometry::get < 1 > (b1.max()) >= geometry::get < 1 > (b2.min())
          && geometry::get < 1 > (b1.min()) <= geometry::get < 1 > (b2.max()))
        {
          overlaps_y = true;
        }

      return overlaps_x && overlaps_y;
    }


  }                             // namespace spatial_index
}                               // namespace boost

#endif // BOOST_SPATIAL_INDEX_HELPERS_HPP
