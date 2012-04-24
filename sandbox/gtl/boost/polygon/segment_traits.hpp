/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_SEGMENT_TRAITS_HPP
#define BOOST_POLYGON_SEGMENT_TRAITS_HPP
namespace boost { namespace polygon{
  template <typename Segment>
  struct segment_traits {
    typedef typename Segment::coordinate_type coordinate_type;
    typedef typename Segment::point_type point_type;

    static inline point_type get(const Segment& segment, direction_1d dir) {
      return segment.get(dir);
    }
  };

  template <typename Segment>
  struct segment_mutable_traits {
    template <typename Point>
    static inline void set(Segment& segment, direction_1d dir, const Point& value) {
      typename segment_traits<Segment>::point_type p1;
      assign(p1, value);
      segment.set(dir, p1);
    }

    template <typename Point1, typename Point2>
    static inline Segment construct(const Point1& low_value, const Point2& high_value) {
      typename segment_traits<Segment>::point_type p1, p2;
      assign(p1, low_value);
      assign(p2, high_value);
      return Segment(p1, p2);
    }
  };
}
}
#endif
