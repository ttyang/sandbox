/*
  Copyright 2008 Intel Corporation
 
  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef GTL_ITERATOR_GEOMETRY_TO_SET_HPP
#define GTL_ITERATOR_GEOMETRY_TO_SET_HPP
namespace gtl {
template <typename concept_type, typename geometry_type>
class iterator_geometry_to_set {};

template <typename concept_type, typename iterator_type>
class iterator_geometry_range_to_set {
  typedef typename std::iterator_traits<iterator_type>::value_type geometry_type;
  typedef iterator_geometry_to_set<concept_type, geometry_type> internal_iterator_type;
  typedef typename internal_iterator_type::value_type value_type;
  typedef std::forward_iterator_tag iterator_category;
  typedef std::ptrdiff_t difference_type;
  typedef const value_type* pointer; //immutable
  typedef const value_type& reference; //immutable
private:
  iterator_type itr_;
  mutable internal_iterator_type itrb_, itre_;
  mutable bool dereferenced_;
  orientation_2d orient_;
public:
  iterator_geometry_range_to_set(iterator_type itr,
                           orientation_2d orient = HORIZONTAL) : 
    itr_(itr), dereferenced_(false), orient_(orient) {}
  
  inline iterator_geometry_range_to_set& operator++() {
    if(!dereferenced_) **this;
    if(itrb_ == itre_) {
      ++itr_;
      dereferenced_ = false;
    } else {
      ++itrb_;
      if(itrb_ == itre_) {
        ++itr_;
        dereferenced_ = false;
      }
    }
    return *this;
  }
  inline iterator_geometry_range_to_set operator++(int) {
    iterator_geometry_range_to_set tmp(*this);
    ++(*this);
    return tmp;
  }
  inline bool operator==(const iterator_geometry_range_to_set& that) const {
    return (itr_ == that.itr_);
  }
  inline bool operator!=(const iterator_geometry_range_to_set& that) const {
    return !(*this == that);
  }
  inline reference operator*() const {
    if(!dereferenced_) {
      itrb_ = iterator_geometry_to_set<concept_type, geometry_type>(*itr_, LOW, orient_);
      itre_ = iterator_geometry_to_set<concept_type, geometry_type>(*itr_, HIGH, orient_);
      dereferenced_ = true;
    }
    return *itrb_; 
  }
};

template <typename rectangle_type>
class iterator_geometry_to_set<rectangle_concept, rectangle_type> {
public:
  typedef typename rectangle_traits<rectangle_type>::coordinate_type coordinate_type;
  typedef std::forward_iterator_tag iterator_category;
  typedef std::pair<coordinate_type, std::pair<coordinate_type, int> > value_type;
  typedef std::ptrdiff_t difference_type;
  typedef const value_type* pointer; //immutable
  typedef const value_type& reference; //immutable
private:
  rectangle_data<coordinate_type> rectangle_;
  mutable value_type vertex_;
  unsigned int corner_;
  orientation_2d orient_;
public:
  iterator_geometry_to_set() : corner_(4) {}
  iterator_geometry_to_set(const rectangle_type& rectangle, direction_1d dir, 
                           orientation_2d orient = HORIZONTAL) : corner_(0), orient_(orient) {
    rectangle_concept::assign(rectangle_, rectangle);
    if(dir == HIGH) corner_ = 4;
  }
  inline iterator_geometry_to_set& operator++() {
    ++corner_;
    return *this;
  }
  inline iterator_geometry_to_set operator++(int) {
    iterator_geometry_to_set tmp(*this);
    ++(*this);
    return tmp;
  }
  inline bool operator==(const iterator_geometry_to_set& that) const {
    return corner_ == that.corner_;
  }
  inline bool operator!=(const iterator_geometry_to_set& that) const {
    return !(*this == that);
  }
  inline reference operator*() const {
    if(corner_ == 0) {
      vertex_.first = interval_concept::get(rectangle_concept::get(rectangle_, orient_.get_perpendicular()), LOW);
      vertex_.second.first = interval_concept::get(rectangle_concept::get(rectangle_, orient_), LOW);
      vertex_.second.second = 1;
    } else if(corner_ == 1) {
      vertex_.second.first = interval_concept::get(rectangle_concept::get(rectangle_, orient_), HIGH);
      vertex_.second.second = -1;
    } else if(corner_ == 2) {
      vertex_.first = interval_concept::get(rectangle_concept::get(rectangle_, orient_.get_perpendicular()), HIGH);
      vertex_.second.first = interval_concept::get(rectangle_concept::get(rectangle_, orient_), LOW);
    } else {
      vertex_.second.first = interval_concept::get(rectangle_concept::get(rectangle_, orient_), HIGH);
      vertex_.second.second = 1;
    }
    return vertex_; 
  }
};

template <typename polygon_type>
class iterator_geometry_to_set<polygon_90_concept, polygon_type> {
public:
  typedef typename polygon_traits<polygon_type>::coordinate_type coordinate_type;
  typedef std::forward_iterator_tag iterator_category;
  typedef std::pair<coordinate_type, std::pair<coordinate_type, int> > value_type;
  typedef std::ptrdiff_t difference_type;
  typedef const value_type* pointer; //immutable
  typedef const value_type& reference; //immutable
  typedef typename polygon_traits<polygon_type>::iterator_type coord_iterator_type;
private:
  value_type vertex_;
  typename polygon_traits<polygon_type>::iterator_type itrb, itre;
  bool last_vertex_;
  bool is_hole_;
  int multiplier_;
  point_data<coordinate_type> first_pt, second_pt, pts[3];
  bool use_wrap;
  orientation_2d orient_;
  int polygon_index;
public:
  iterator_geometry_to_set() : polygon_index(-1) {}
  iterator_geometry_to_set(const polygon_type& polygon, direction_1d dir, orientation_2d orient = HORIZONTAL, bool is_hole = false) : 
    is_hole_(is_hole), orient_(orient), polygon_index(0) {
    itrb = polygon_90_concept::begin(polygon);
    itre = polygon_90_concept::end(polygon);
    use_wrap = false;
    if(itrb == itre || dir == HIGH || polygon_90_concept::size(polygon) < 4) {
      polygon_index = -1;
    } else {
      direction_1d wdir = polygon_90_concept::winding(polygon);
      multiplier_ = wdir == LOW ? -1 : 1;
      if(is_hole_) multiplier_ *= -1;
      first_pt = pts[0] = *itrb;
      ++itrb;
      second_pt = pts[1] = *itrb;
      ++itrb;
      pts[2] = *itrb;
    }
    evaluate_();
  }
  
  inline iterator_geometry_to_set& operator++() {
    ++polygon_index;
    if(itrb == itre) {
      if(first_pt == pts[1]) polygon_index = -1;
      else {
        pts[0] = pts[1];
        pts[1] = pts[2];
        if(first_pt == pts[2]) {
          pts[2] = second_pt;
        } else {
          pts[2] = first_pt;
        }
      }
    } else {
      ++itrb;
      pts[0] = pts[1];
      pts[1] = pts[2];
      if(itrb == itre) {
        if(first_pt == pts[2]) {
          pts[2] = second_pt;
        } else {
          pts[2] = first_pt;
        }
      } else {
        pts[2] = *itrb;
      }
    }
    evaluate_();
    return *this;
  }
  inline iterator_geometry_to_set operator++(int) {
    iterator_geometry_to_set tmp(*this);
    ++(*this);
    return tmp;
  }
  inline bool operator==(const iterator_geometry_to_set& that) const {
    return polygon_index == that.polygon_index;
  }
  inline bool operator!=(const iterator_geometry_to_set& that) const {
    return !(*this == that);
  }
  inline reference operator*() const {
    return vertex_; 
  }

  inline void evaluate_() {
    vertex_.first = pts[1].get(orient_.get_perpendicular());
    vertex_.second.first =pts[1].get(orient_);
    if(pts[0].get(HORIZONTAL) != pts[1].get(HORIZONTAL)) {
      vertex_.second.second = -1; 
    } else {
      vertex_.second.second = 1;
    }
    vertex_.second.second *= multiplier_;
  }
};

template <typename polygon_with_holes_type>
class iterator_geometry_to_set<polygon_90_with_holes_concept, polygon_with_holes_type> {
public:
  typedef typename rectangle_traits<polygon_with_holes_type>::coordinate_type coordinate_type;
  typedef std::forward_iterator_tag iterator_category;
  typedef std::pair<coordinate_type, std::pair<coordinate_type, int> > value_type;
  typedef std::ptrdiff_t difference_type;
  typedef const value_type* pointer; //immutable
  typedef const value_type& reference; //immutable
private:
  iterator_geometry_to_set<polygon_90_concept, polygon_with_holes_type> itrb, itre;
  iterator_geometry_to_set<polygon_90_concept, typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type> itrhib, itrhie;
  typename polygon_with_holes_traits<polygon_with_holes_type>::iterator_holes_type itrhb, itrhe;
  orientation_2d orient_;
  bool started_holes;
public:
  iterator_geometry_to_set() {}
  iterator_geometry_to_set(const polygon_with_holes_type& polygon, direction_1d dir, 
                           orientation_2d orient = HORIZONTAL) : orient_(orient) {
    itre = iterator_geometry_to_set<polygon_90_concept, polygon_with_holes_type>(polygon, HIGH, orient);
    itrhe = polygon_90_with_holes_concept::end_holes(polygon);
    if(dir == HIGH) {
      itrb = itre;
      itrhb = itrhe;
      started_holes = true;
    } else {
      itrb = iterator_geometry_to_set<polygon_90_concept, polygon_with_holes_type>(polygon, LOW, orient);
      itrhb = polygon_90_with_holes_concept::begin_holes(polygon);
      started_holes = false;
    }
  }
  inline iterator_geometry_to_set& operator++() {
    //this code can be folded with flow control factoring
    if(itrb == itre) {
      if(itrhib == itrhie) {
        if(itrhb != itrhe) {
          itrhib = iterator_geometry_to_set<polygon_90_concept, 
            typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>(*itrhb, LOW, orient_, true);
          itrhie = iterator_geometry_to_set<polygon_90_concept, 
            typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>(*itrhb, HIGH, orient_, true);
          ++itrhb;
        } else {
          itrhib = itrhie = iterator_geometry_to_set<polygon_90_concept, 
            typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>();
        }
      } else {
        ++itrhib;
        if(itrhib == itrhie) {
          if(itrhb != itrhe) {
            itrhib = iterator_geometry_to_set<polygon_90_concept, 
              typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>(*itrhb, LOW, orient_, true);
            itrhie = iterator_geometry_to_set<polygon_90_concept, 
              typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>(*itrhb, HIGH, orient_, true);
            ++itrhb;
          } else {
            itrhib = itrhie = iterator_geometry_to_set<polygon_90_concept, 
              typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>();
          }
        }
      }
    } else {
      ++itrb;
      if(itrb == itre) {
        if(itrhb != itrhe) {
          itrhib = iterator_geometry_to_set<polygon_90_concept, 
            typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>(*itrhb, LOW, orient_, true);
          itrhie = iterator_geometry_to_set<polygon_90_concept, 
            typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>(*itrhb, HIGH, orient_, true);
          ++itrhb;
        }
      }
    }
    return *this;
  }
  inline iterator_geometry_to_set operator++(int) {
    iterator_geometry_to_set tmp(*this);
    ++(*this);
    return tmp;
  }
  inline bool operator==(const iterator_geometry_to_set& that) const {
    return itrb == that.itrb && itrhb == that.itrhb && itrhib == that.itrhib;
  }
  inline bool operator!=(const iterator_geometry_to_set& that) const {
    return !(*this == that);
  }
  inline reference operator*() const {
    if(itrb != itre) return *itrb;
    return *itrhib;
  }
};

}
#endif

