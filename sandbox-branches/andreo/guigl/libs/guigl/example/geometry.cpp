#define NOMINMAX

//*=================================---------------------------------------------
//Copyright 2009 Andrey Torba
//
//Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE_1_0.txt or copy at
//http://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------===============================*/

#include "geometry.hpp"

#include <boost/guigl/application.hpp>
#include <boost/guigl/window.hpp>
#include <boost/guigl/widget/custom.hpp>

#include <boost/guigl/ggl.hpp>
#include <boost/guigl/gl.hpp>

#include <geometry/geometries/geometries.hpp>
#include <geometry/geometry.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/assign/std.hpp>
#include <boost/foreach.hpp>

#include <geometry/io/wkt/streamwkt.hpp>

#include <geometry/algorithms/correct.hpp>
#include <geometry/geometry.hpp>
#include <geometry/algorithms/centroid.hpp>
#include "graph.hpp"

using namespace boost::guigl;

class RenderVisitor : public IVisitor
  {
  public:
    void visit(int key, source_point& g) const
      {
      gl::color(blue(0.7f));
      ggl::draw(g.result);
      }

    void visit(int key, line_from_two_points& g) const
      {
      gl::line_width(4);
      gl::color(red(0.8f));
      ggl::draw(g.result);
      }

    void visit(int key, plane_from_three_points& g) const
      {
      gl::color(green(0.5f));
      glBegin(GL_POLYGON);
      ggl::vertex(g.result.outer());
      glEnd();

      gl::line_width(2);
      gl::color(black(0.2));
      ggl::draw<geometry::ring_tag>(g.result.outer());
      }
  };

class RecomputeVisitor : public IVisitor
  {
  public:
    void visit(int key, line_from_two_points& g) const
      {
      g.result = line_type(g.pt1, g.pt2);
      };

    void visit(int key, plane_from_three_points& g) const
      {
      using namespace boost::assign;
      g.result.outer().clear();
      g.result.outer() += g.pt1, g.pt2, g.pt3;
      geometry::correct(g.result);
      };
  };

struct StreamWriter
  {
  template<class T>
  void operator()(int key, T& g) const
    {
    std::cout << g.result << std::endl;
    }

  template<>
  void operator()<line_from_two_points>(int key, line_from_two_points& g) const
    {
    geometry::linestring<point_type> s;
    geometry::append(s, g.result.first);
    geometry::append(s, g.result.second);
    std::cout << s << std::endl;
    }

  };

template<class Tag>
struct StreamByTag
  {
  template<class T>
  void operator()(int key, T& g) const
    {
    return ;
    }

  template<>
  void operator()<Tag>(int key, Tag& g) const
    {
    std::cout << g.result << std::endl;
    }
  };

void drawString(const char *str, int x, int y, color_type const& clr, void *font)
  {
  glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
  glDisable(GL_LIGHTING);     // need to disable lighting for proper text color

  gl::color(clr);
  glRasterPos2i(x, y);        // place text position

  // loop all characters in the string
  while(*str)
    {
    glutBitmapCharacter(font, *str);
    ++str;
    }

  glEnable(GL_LIGHTING);
  glPopAttrib();
  }

struct PrintDescription
  {
  std::map<int, std::string> const& descriptions;
  dependency_graph const& g;

  PrintDescription(
    std::map<int, std::string> const& descriptions_,
    dependency_graph const& g_)
    :descriptions(descriptions_), g(g_) {}

  template<class T>
  point_type get_center(T const& obj) const
    {
    point_type center;
    geometry::centroid(obj, center);
    return center;
    }

  template<>
  point_type get_center<point_type>(point_type const& obj) const
    {
    return obj;
    }

  template<>
  point_type get_center<line_type>(line_type const& obj) const
    {
    return point_type(
      (obj.first.x + obj.second.x)/2,
      (obj.first.y + obj.second.y)/2);
    }

  //template<class T>
  //point_type get_center<base_result<line_type> >(T const& obj)
  //  {
  //  return geometry::centet
  //  }

  //template<class T>
  //point_type get_center<base_result<line_type> >(T const& obj)
  //  {

  //  }

  template<class T>
  void operator()(int key, T const& obj) const
    {
    boost::optional<int> i = g.get_key(key);
    if(!i) return ;

    point_type center = get_center(obj.result);
    drawString(descriptions.find(*i)->second.c_str(), center.x + 10, center.y, grey(0.1f), GLUT_BITMAP_8_BY_13);
    }
  };

widget::custom *w;

struct drawer {
  typedef boost::shared_ptr<IAcceptor> IAcceptorPtr;
  dependency_graph g;
  std::map<int, std::string> names;

  void init_geometry_graph();

  enum {
    middle_notch_point,
    femoral_head_point,
    lateral_epi_point,
    medial_epi_point,

    point1,

    mechanical_axis,
    epi_axis,

    axial_plane
    };

  drawer()
    {
    using namespace boost::assign;

    typedef GraphVertex<int, point_type> Point;
    typedef GraphVertex<int, line_type> Line;
    typedef GraphVertex<int, plane_type> Plane;


    insert(names)
      (middle_notch_point, "middle notch point")
      (femoral_head_point, "femoral head point")
      (lateral_epi_point, "lateral epi point")
      (medial_epi_point, "medial epi point")
      (point1, "point1")
      (mechanical_axis, "mechanical axis")
      (epi_axis, "epi axis")
      (axial_plane, "axial plane")
      ;

    init_geometry_graph();

    std::for_each(
      g.objects.begin(),
      g.objects.end(),
      accept_each(RecomputeVisitor()));

    std::for_each(
      g.objects.begin(),
      g.objects.end(),
      accept_each(Visitor<StreamWriter>()));
    }

  void operator()() const
    {
    gl::line_width(0.5);
    gl::color(black(0.5));
    ggl::draw(w->segment<HC>());
    ggl::draw(w->segment<VC>());

    gl::scoped_matrix m;
    gl::translate(250., 250.);

//    drawString("center", 0, 0, grey(0.1), GLUT_BITMAP_8_BY_13);

    gl::point_size(10);
    //gl::line_width(2);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);


    std::for_each(
      g.objects.begin(),
      g.objects.end(),
      accept_each(RecomputeVisitor()));

    std::for_each(
      g.objects.begin(),
      g.objects.end(),
      accept_each(RenderVisitor()));

    std::for_each(
      g.objects.begin(),
      g.objects.end(),
      accept_each(Visitor<PrintDescription>(PrintDescription(names, g))));
    }
  };

int main()
  {
  window wnd((
    _label = "geometry example",
    _size = size_type(500, 500),
    _background = white()
    ));

  w = new widget::custom((
    _size = size_type(500,500),
    _position = position_type(0, 0),
    _draw_prologue = drawer()
    ));

  wnd << w;

  application::run();
  return 0;
  }




void drawer::init_geometry_graph()
  {
  using namespace boost::assign;

  typedef GraphVertex<int, point_type> Point;
  typedef GraphVertex<int, line_type> Line;
  typedef GraphVertex<int, plane_type> Plane;

  Point
    pt_mnp = g.make_source_point(middle_notch_point, point_type(90, 90)),
    pt_fh = g.make_source_point(femoral_head_point, point_type(-90, -90)),
    pt_laepi = g.make_source_point(lateral_epi_point, point_type(90, -90)),
    pt_meepi = g.make_source_point(medial_epi_point, point_type(0, -180));

  ////Point
  ////  pt_mnp = g.make_indicatable_point(middle_notch_point);

  Line
    ax_mech = g.make_line(mechanical_axis, pt_mnp, pt_fh),
    ax_epi = g.make_line(epi_axis, pt_meepi, pt_laepi);

  Plane
    pl_axial = g.make_plane(axial_plane, pt_mnp, pt_fh, pt_laepi);

  Point pt1 = g.make_source_point(point1, point_type(120, 30));

  g.make_plane(
    g.make_source_point(point_type(-90, 90)),
    pt1,
    pt_mnp);
  }