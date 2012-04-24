/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_SEGMENT_CONCEPT_HPP
#define BOOST_POLYGON_SEGMENT_CONCEPT_HPP
#include "isotropy.hpp"
#include "segment_data.hpp"
#include "segment_traits.hpp"
#include "rectangle_concept.hpp"
#include "detail/polygon_arbitrary_formation.hpp"

namespace boost { namespace polygon{
  struct segment_concept {};

  template <typename Segment>
  struct is_segment_concept { typedef gtl_no type; };

  template <>
  struct is_segment_concept<segment_concept> {
    typedef gtl_yes type;
  };

  template <typename Segment>
  struct is_mutable_segment_concept { typedef gtl_no type; };

  template <>
  struct is_mutable_segment_concept<segment_concept> {
    typedef gtl_yes type;
  };

  template <typename Segment, typename CT>
  struct segment_distance_type_by_concept {
    typedef void type;
  };

  template <typename Segment>
  struct segment_distance_type_by_concept<Segment, gtl_yes> {
    typedef typename coordinate_traits<
      typename segment_traits<Segment>::coordinate_type
    >::coordinate_distance type;
  };

  template <typename Segment>
  struct segment_distance_type {
    typedef typename segment_distance_type_by_concept<
      Segment,
      typename is_segment_concept<
        typename geometry_concept<Segment>::type
      >::type
    >::type type;
  };

  template <typename Segment, typename CT>
  struct segment_point_type_by_concept { typedef void type; };

  template <typename Segment>
  struct segment_point_type_by_concept<Segment, gtl_yes> {
    typedef typename segment_traits<Segment>::point_type type;
  };

  template <typename Segment>
  struct segment_point_type {
    typedef typename segment_point_type_by_concept<
      Segment,
      typename is_segment_concept<
        typename geometry_concept<Segment>::type
      >::type
    >::type type;
  };

  template <typename Segment, typename CT>
  struct segment_coordinate_type_by_concept {
    typedef void type;
  };

  template <typename Segment>
  struct segment_coordinate_type_by_concept<Segment, gtl_yes> {
    typedef typename segment_traits<Segment>::coordinate_type type;
  };

  template <typename Segment>
  struct segment_coordinate_type {
    typedef typename segment_coordinate_type_by_concept<
      Segment,
      typename is_segment_concept<
        typename geometry_concept<Segment>::type
      >::type
    >::type type;
  };

  struct y_s_get : gtl_yes {};

  template <typename Segment>
  typename enable_if<
    typename gtl_and<
      y_s_get,
      typename is_segment_concept<
        typename geometry_concept<Segment>::type
      >::type
    >::type,
    typename segment_point_type<Segment>::type
  >::type
  get(const Segment& segment, direction_1d dir) {
    return segment_traits<Segment>::get(segment, dir);
  }

  struct y_s_set : gtl_yes {};

  template <typename Segment, typename Point>
  typename enable_if<
    typename gtl_and<
      y_s_set,
      typename is_mutable_segment_concept<
        typename geometry_concept<Segment>::type
      >::type
    >::type,
    void
  >::type
  set(Segment& segment, direction_1d dir, const Point& value) {
    segment_mutable_traits<Segment>::set(segment, dir, value);
  }

  struct y_s_construct : gtl_yes {};

  template <typename Segment, typename Point1, typename Point2>
  typename enable_if<
    typename gtl_and<
      y_s_construct,
      typename is_mutable_segment_concept<
        typename geometry_concept<Segment>::type
      >::type
    >::type,
    Segment
  >::type
  construct(const Point1& low, const Point2& high) {
    return segment_mutable_traits<Segment>::construct(low, high);
  }

  struct y_s_copy_construct : gtl_yes {};

  template <typename Segment1, typename Segment2>
  typename enable_if<
    typename gtl_and_3<
      y_s_copy_construct,
      typename is_mutable_segment_concept<
        typename geometry_concept<Segment1>::type
      >::type,
      typename is_segment_concept<
        typename geometry_concept<Segment2>::type
      >::type
    >::type,
    Segment1
  >::type
  copy_construct(const Segment2& segment) {
    return construct<Segment1>(get(segment, LOW), get(segment, HIGH));
  }

  struct y_s_assign : gtl_yes {};

  template <typename Segment1, typename Segment2>
  typename enable_if<
    typename gtl_and_3<
      y_s_assign,
        typename is_mutable_segment_concept<
          typename geometry_concept<Segment1>::type
        >::type,
        typename is_segment_concept<
          typename geometry_concept<Segment2>::type
        >::type
    >::type,
    Segment1
  >::type &
  assign(Segment1& lvalue, const Segment2& rvalue) {
    return lvalue = copy_construct<Segment1>(rvalue);
  }

  struct y_s_equivalence : gtl_yes {};

  template <typename Segment1, typename Segment2>
  typename enable_if<
    typename gtl_and_3<
      y_s_equivalence,
      typename is_segment_concept<
        typename geometry_concept<Segment1>::type
      >::type,
      typename is_segment_concept<
        typename geometry_concept<Segment2>::type
      >::type
    >::type,
    bool
  >::type
  equivalence(const Segment1& segment1, const Segment2& segment2) {
    return get(segment1, LOW) == get(segment2, LOW) &&
           get(segment1, HIGH) == get(segment2, HIGH);
  }

  struct y_s_on_above_or_below : gtl_yes {};

  //-1 for below, 0 for on and 1 for above
  template <typename Segment>
  typename enable_if<
    typename gtl_and<
      y_s_on_above_or_below,
      typename is_segment_concept<
        typename geometry_concept<Segment>::type
      >::type
    >::type,
    bool
  >::type
  on_above_or_below(const Segment& segment,
                    const typename segment_point_type<Segment>::type& point) {
    typedef polygon_arbitrary_formation<
      typename segment_coordinate_type<Segment>::type
    > paf;
    typename paf::Point pt, l, h;
    assign(pt, point);
    assign(l, low(segment));
    assign(h, high(segment));
    return paf::on_above_or_below(pt, typename paf::half_edge(l, h));
  }

  struct y_s_contains : gtl_yes {};

  template <typename Segment>
  typename enable_if<
    typename gtl_and<
      y_s_contains,
      typename is_segment_concept<
        typename geometry_concept<Segment>::type
      >::type
    >::type,
    bool
  >::type
  contains(const Segment& segment,
           const typename segment_point_type<Segment>::type& point,
           bool consider_touch = true ) {
    if(on_above_or_below(segment, point) == 0) {
      rectangle_data<typename segment_coordinate_type<Segment>::type> rect;
      set_points(rect, low(segment), high(segment));
      if(area(rect) == 0.0) {
        if(!consider_touch) {
          return !equivalence(point, low(segment)) &&
                 !equivalence(point, high(segment));
        }
      }
      return contains(rect, value, consider_touch);
    }
    return false;
  }

  struct y_s_contains2 : gtl_yes {};

  template <typename Segment1, typename Segment2>
  typename enable_if<
    typename gtl_and_3<
      y_s_contains2,
      typename is_segment_concept<
        typename geometry_concept<Segment1>::type
      >::type,
      typename is_segment_concept<
        typename geometry_concept<Segment2>::type
      >::type
    >::type,
    bool
  >::type
  contains(const Segment1& segment,
           const Segment2& value,
           bool consider_touch = true) {
    return contains(segment, get(value, LOW), consider_touch) &&
           contains(segment, get(value, HIGH), consider_touch);
  }

  struct y_s_low : gtl_yes {};

  // get the low point
  template <typename Segment>
  typename enable_if<
    typename gtl_and<
      y_s_low,
      typename is_segment_concept<
        typename geometry_concept<Segment>::type
      >::type
    >::type,
    typename segment_point_type<Segment>::type
  >::type
  low(const Segment& segment) {
    return get(segment, LOW);
  }

  struct y_s_high : gtl_yes {};

  // get the high point
  template <typename Segment>
  typename enable_if<
    typename gtl_and<
      y_s_high,
      typename is_segment_concept<
        typename geometry_concept<Segment>::type
      >::type
    >::type,
    typename segment_point_type<Segment>::type
  >::type
  high(const Segment& segment) {
    return get(segment, HIGH);
  }

  struct y_s_center : gtl_yes {};

  // get the center point
  template <typename Segment>
  typename enable_if<
    typename gtl_and<
      y_s_center,
      typename is_segment_concept<
        typename geometry_concept<Segment>::type
      >::type
    >::type,
    typename segment_point_type<Segment>::type
  >::type
  center(const Segment& segment) {
    return construct<typename segment_coordinate_type<Segment>::type>(
        (x(high(segment)) + x(low(segment)))/2,
        (y(high(segment)) + y(low(segment)))/2);
  }

  struct y_s_low2 : gtl_yes {};

  // set the low point to v
  template <typename Segment>
  typename enable_if<
    typename gtl_and<
      y_s_low2,
      typename is_mutable_segment_concept<
        typename geometry_concept<Segment>::type
      >::type
    >::type,
    void
  >::type
  low(Segment& segment,
      const typename segment_point_type<Segment>::type& point) {
    set(segment, LOW, point);
  }

  struct y_s_high2 : gtl_yes {};

  // set the high coordinate to v
  template <typename Segment>
  typename enable_if<
    typename gtl_and<
      y_s_high2,
      typename is_mutable_segment_concept<
        typename geometry_concept<Segment>::type
      >::type
    >::type,
    void
  >::type
  high(Segment& segment,
       const typename segment_point_type<Segment>::type& point) {
    set(segment, HIGH, point);
  }

  struct y_s_length : gtl_yes {};

  template <typename Segment>
  typename enable_if<
    typename gtl_and<
      y_s_length,
      typename is_segment_concept<
        typename geometry_concept<Segment>::type
      >::type
    >::type,
    typename segment_distance_type<Segment>::type
  >::type
  length(const Segment& segment) {
    return euclidean_distance(low(segment), high(segment));
  }

  struct y_s_scale_up : gtl_yes {};

  // scale segment by factor
  template <typename Segment>
  typename enable_if<
    typename gtl_and<
      y_s_scale_up,
      typename is_mutable_segment_concept<
        typename geometry_concept<Segment>::type
      >::type
    >::type,
    Segment
  >::type &
  scale_up(Segment& segment,
           typename coordinate_traits<
             typename segment_coordinate_type<Segment>::type
           >::unsigned_area_type factor) {
    typename segment_point_type<Segment>::type l = low(segment), h = high(segment);
    low(segment, scale_up(l, factor));
    high(segment, scale_up(h, factor));
    return segment;
  }

  struct y_s_scale_down : gtl_yes {};

  template <typename Segment>
  typename enable_if<
    typename gtl_and<
      y_s_scale_down,
      typename is_mutable_segment_concept<
        typename geometry_concept<Segment>::type
      >::type
    >::type,
    Segment
  >::type &
  scale_down(Segment& segment,
             typename coordinate_traits<
               typename segment_coordinate_type<Segment>::type
             >::unsigned_area_type factor) {
    typename segment_point_type<Segment>::type l = low(segment), h = high(segment);
    low(segment, scale_down(l, factor));
    high(segment, scale_down(h, factor));
    return segment;
  }

  struct y_s_scale : gtl_yes {};

  template <typename Segment, typename scaling_type>
  typename enable_if<
    typename gtl_and<
      y_s_scale,
      typename is_mutable_segment_concept<
        typename geometry_concept<Segment>::type
      >::type
    >::type,
    Segment
  >::type &
  scale(Segment& segment, scaling_type factor) {
    typename segment_point_type<Segment>::type l = low(segment), h = high(segment);
    low(segment, scale(l, factor));
    high(segment, scale(h, factor));
    return segment;
  }


  struct y_s_transform : gtl_yes {};

  template <typename Segment, typename transform_type>
  typename enable_if<
    typename gtl_and<
      y_s_transform,
      typename is_mutable_segment_concept<
        typename geometry_concept<Segment>::type
      >::type
    >::type,
    Segment
  >::type &
  transform(Segment& segment, const transform_type& val) {
    typename segment_point_type<Segment>::type l = low(segment), h = high(segment);
    low(segment, transform(l, val));
    high(segment, transform(h, val));
    return segment;
  }

  struct y_s_move : gtl_yes {};

  // move segment by delta
  template <typename Segment>
  typename enable_if<
    typename gtl_and<
      y_s_move,
      typename is_mutable_segment_concept<
        typename geometry_concept<Segment>::type
      >::type
    >::type,
    Segment
  >::type &
  move(Segment& segment, orientation_2d orient,
       typename segment_coordinate_type<Segment>::type displacement) {
    typename segment_point_type<Segment>::type l = low(segment), h = high(segment);
    low(segment, move(l, orient, displacement));
    high(segment, move(h, orient, displacement));
    return segment;
  }

  struct y_s_convolve : gtl_yes {};

  // convolve this with point
  template <typename Segment>
  typename enable_if<
    typename gtl_and<
      y_s_convolve,
      typename is_mutable_segment_concept<
        typename geometry_concept<Segment>::type
      >::type
    >::type,
    Segment
  >::type &
  convolve(Segment& segment,
      const typename segment_point_type<Segment>::type& point) {
    typename segment_point_type<Segment>::type l = low(segment), h = high(segment);
    low(segment, convolve(l, point));
    high(segment, convolve(h, point));
    return segment;
  }

  struct y_s_deconvolve : gtl_yes {};

  // deconvolve this with point
  template <typename Segment>
  typename enable_if<
    typename gtl_and<
      y_s_deconvolve,
      typename is_mutable_segment_concept<
        typename geometry_concept<Segment>::type
      >::type
    >::type,
    Segment
  >::type &
  deconvolve(Segment& segment,
      const typename segment_point_type<Segment>::type& point) {
    typename segment_point_type<Segment>::type l = low(segment), h = high(segment);
    low(segment, deconvolve(l, point));
    high(segment, deconvolve(h, point));
    return segment;
  }

  struct y_s_e_dist : gtl_yes {};

  // distance from a point to a segment
  template <typename Segment>
  typename enable_if<
    typename gtl_and<
      y_s_e_dist,
      typename is_segment_concept<
        typename geometry_concept<Segment>::type
      >::type
    >::type,
    typename segment_distance_type<Segment>::type
  >::type
  euclidean_distance(const Segment& segment,
      const typename segment_point_type<Segment>::type& position) {
    typedef typename segment_distance_type<Segment>::type Unit;
    Unit x1 = x(low(segment));
    Unit y1 = y(low(segment));
    Unit x2 = x(high(segment));
    Unit y2 = y(high(segment));
    Unit X = x(position);
    Unit Y = y(position);
    Unit A = X - x1;
    Unit B = Y - y1;
    Unit C = x2 - x1;
    Unit D = y2 - y1;
    Unit length_sq = C * C + D * D;
    Unit param = (A * C + B * D)/length_sq;
    if(param > 1.0) {
      return euclidean_distance(high(segment), position);
    } else if(param < 0.0) {
      return euclidean_distance(low(segment), position);
    }
    Unit denom = sqrt(length_sq);
    if(denom == 0.0)
      return 0.0;
    Unit result = (A * D - C * B) / denom;
    if(result < 0.0)
      result *= -1;
    return result;
  }

  struct y_s_e_dist2 : gtl_yes {};

  // distance between two segments
  template <typename Segment1, typename Segment2>
  typename enable_if<
    typename gtl_and_3<
      y_s_e_dist2,
      typename is_segment_concept<
        typename geometry_concept<Segment1>::type
      >::type,
      typename is_segment_concept<
        typename geometry_concept<Segment2>::type
      >::type
    >::type,
    typename segment_distance_type<Segment1>::type
  >::type
  euclidean_distance(const Segment1& segment1,
                     const Segment2& segment2) {
    typename segment_distance_type<Segment1>::type
        result1 = euclidean_distance(segment1, low(segment2)),
        result2 = euclidean_distance(segment1, high(segment2));
    if(result2 < result1) return result2;
    return result1;
  }

  struct y_s_e_intersects : gtl_yes {};

  // check if Interval b intersects `this` Interval
  template <typename Segment1, typename Segment2>
  typename enable_if<
    typename gtl_and_3<
      y_s_e_intersects,
      typename is_segment_concept<
        typename geometry_concept<Segment1>::type
      >::type,
      typename is_segment_concept<
        typename geometry_concept<Segment2>::type
      >::type
    >::type,
    bool
  >::type
  intersects(const Segment1& segment1,
             const Segment2& segment2,
             bool consider_touch = true) {
    if(consider_touch) {
      if(low(segment1) == low(segment2) || low(segment1) == high(segment2) ||
         high(segment1) == low(segment2) || high(segment1) == high(segment2))
        return true;
    }
    typedef polygon_arbitrary_formation<
      typename segment_coordinate_type<Segment1>::type
    > paf;
    typename paf::Point l1, h1, l2, h2;
    assign(l1, low(segment1));
    assign(h1, high(segment1));
    assign(l2, low(segment2));
    assign(h2, high(segment2));
    return paf::intersects(typename paf::half_edge(l1, h1),
                           typename paf::half_edge(l2, h2));
  }

  struct y_s_e_bintersect : gtl_yes {};

  // check if Interval b partially overlaps `this` Interval
  template <typename Segment1, typename Segment2>
  typename enable_if<
    typename gtl_and_3<
      y_s_e_bintersect,
      typename is_segment_concept<
        typename geometry_concept<Segment1>::type
      >::type,
      typename is_segment_concept<
        typename geometry_concept<Segment2>::type
      >::type
    >::type,
    bool
  >::type
  boundaries_intersect(const Segment1& segment1, const Segment2& segment2,
                       bool consider_touch = true) {
    return (contains(segment1, low(segment2), consider_touch) ||
            contains(segment1, high(segment2), consider_touch)) &&
           (contains(segment2, low(segment1), consider_touch) ||
            contains(segment2, high(segment1), consider_touch));
  }

  struct y_s_abuts1 : gtl_yes {};

  // check if they are end to end
  template <typename Segment1, typename Segment2>
  typename enable_if<
    typename gtl_and_3<
      y_s_abuts1,
      typename is_segment_concept<
        typename geometry_concept<Segment1>::type
      >::type,
      typename is_segment_concept<
        typename geometry_concept<Segment2>::type
      >::type
    >::type,
    bool
  >::type
  abuts(const Segment1& segment1, const Segment2& segment2, direction_1d dir) {
    return dir.to_int() ? equivalence(low(segment2) , high(segment1)) :
                          equivalence(low(segment1) , high(segment2));
  }

  struct y_s_abuts2 : gtl_yes {};

  // check if they are end to end
  template <typename Segment1, typename Segment2>
  typename enable_if<
    typename gtl_and_3<
      y_s_abuts2,
      typename is_segment_concept<
        typename geometry_concept<Segment1>::type
      >::type,
      typename is_segment_concept<
        typename geometry_concept<Segment2>::type
      >::type
    >::type,
    bool
  >::type
  abuts(const Segment1& segment1, const Segment2& segment2) {
    return abuts(segment1, segment2, HIGH) || abuts(segment1, segment2, LOW);
  }

  struct y_s_intersect : gtl_yes {};

  // set point to the intersection of segment and b
  template <typename Point, typename Segment1, typename Segment2>
  typename enable_if<
    typename gtl_and_4<
      y_s_intersect,
      typename is_mutable_point_concept<
        typename geometry_concept<Point>::type
      >::type,
      typename is_segment_concept<
        typename geometry_concept<Segment1>::type
      >::type,
      typename is_segment_concept<
        typename geometry_concept<Segment2>::type
      >::type
    >::type,
    bool
  >::type
  intersection(Point& intersection,
               const Segment1& segment1,
               const Segment2& segment2,
               bool projected = false,
               bool round_closest = false) {
    typedef polygon_arbitrary_formation<
      typename segment_coordinate_type<Segment1>::type
    > paf;
    typename paf::Point pt;
    typename paf::Point l1, h1, l2, h2;
    assign(l1, low(segment1));
    assign(h1, high(segment1));
    assign(l2, low(segment2));
    assign(h2, high(segment2));
    typename paf::half_edge he1(l1, h1), he2(l2, h2);
    typename paf::compute_intersection_pack pack;
    if(pack.compute_intersection(pt, he1, he2, projected, round_closest)) {
      assign(intersection, pt);
      return true;
    }
    return false;
  }

  template <class T>
  template <class Segment>
  segment_data<T>& segment_data<T>::operator=(const Segment& rvalue) {
    assign(*this, rvalue);
    return *this;
  }

  template <typename T>
  struct geometry_concept<segment_data<T> > {
    typedef segment_concept type;
  };
}
}
#endif
