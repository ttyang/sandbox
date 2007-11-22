// svg_tag.hpp

// Copyright Jacob Voytko 2007
// Copyright Paul A Bristow 2007

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
// -----------------------------------------------------------------

#ifndef BOOST_SVG_TAG_HPP
#define BOOST_SVG_TAG_HPP

// -------------------------------------------------------------------------------
// This file svg_tag.hpp defines all classes that can occur in the SVG parse tree.
// -------------------------------------------------------------------------------

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning(disable: 4127) // "conditional expression is constant."
#  pragma warning(disable: 4512) // "assignment operator could not be generated."
#  pragma warning(disable: 4100) // "'boost_parameter_enabler_argument' : unreferenced formal parameter"
#endif

#include <boost/ptr_container/ptr_container.hpp>
// using boost::vec_ptr;
#include <boost/array.hpp>
// using boost::array;

#include "../svg_style.hpp"

#include <ostream>
// using std::ostream;
#include <string>
// using std::string;
#include <vector>
// using std::vector;

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

namespace boost
{
namespace svg
{
  // Forward declarations of classes defined in this module.
  // Copied to svg_fwd.hpp TODO delete?

  class svg_element; // svg_element is base class for:
  // g_element (group element)
  // rect_element, circle_element, line_element, text_element,
  // polyline_element, polygon_element, path_element, clip_path_element,
  class text_element; // text with position, size, font, (& styles) & orientation.
  class rect_element; // clipping path restricts the region to which paint can be applied.
  class circle_element; // Represents a single circle.
  class ellipse_element; // Represents a single ellipse.
  class line_element; // Represents a single line.
  struct path_point; // Base class for m_path, z_path, q_path, h_path, v_path, c_path, s_path.
  struct poly_path_point; // for polyline & polygon
  class polygon_element; // closed shape consisting of a set of connected straight line segments.
  class polyline_element; // a set of connected straight line segments.
  class path_element; // d= moveto, lineto...
  class clip_path_element; // Restricts the region to which paint can be applied.
  struct m_path; // moveto coordinates (x, y), outputs "M1.2,3.4"
  struct l_path; // lineto coordinates (x, y).
  struct z_path; // z indicates a closepath.
  struct h_path; // Draws a horizontal line from the current point (cpx, cpy) to (x, cpy).
  struct v_path; // Draws a vertical line from the current point (cpx, cpy) to (cpx, y).
  struct c_path; // Draws a cubic B�zier curve from the current point to (x,y) using (x1,y1).
  struct q_path; // Draws a quadratic B�zier curve from the current point to (x,y).
  struct s_path; // Draws a cubic B�zier curve from the current point to (x,y).
  struct t_path; // Draws a quadratic B�zier curve from the current point to (x,y).
  struct a_path; // Draws a elliptical arc from the current point to (x,y).
  struct P_path; // Adds another (absolute) point to a polyline or polygon.
  class g_element; // 'g' element is a container element, <g ... /> </g>
  // for grouping together related graphics elements, for example:
  // <g stroke="rgb(255,0,0)" <rect x="0" y="0"  width="500"  height="600"/> </g>

  // -----------------------------------------------------------------------------
  // svg_element is base class for all the leaf elements:
  // rect_element, circle_element, line_element, text_element,
  // polygon_element, polyline_element, path_element, clip_path_element, g_element
  // g_element ('g' element is a container element
  // for grouping together related graphics elements).
  // http://www.w3.org/TR/SVG/struct.html#NewDocument 5.2.1 Overview
  // -----------------------------------------------------------------------------

  class svg_element
  { // Base class 
  protected:
    svg_style style_info; // fill, stroke, width, get by function style.
    std::string id_name; // set & get by function id.
    std::string clip_name; // set & get by function clip_id.

    void write_attributes(std::ostream& s_out)
    { // group_element id and clip-path.
      if(id_name.size() != 0)
      {
        s_out << " id=\"" << id_name << "\""; // Prefix with space.
      }
      if(clip_name.size() != 0)
      {
        s_out << " clip-path=\"url(#" << clip_name << ")\""; // Prefix with space.
      }
      // Other references, 5.3.1, like color, fill, stroke, gradients...
      // Example id: <g id="yMinorGrid" ></g>
      // Example URI: fill="url(#Gradient01) // local URL
    } // void write_attributes(std::ostream& s_out)

  public:
    virtual void write(std::ostream& rhs) = 0;
    virtual ~svg_element()
    {
    }

    bool operator==(const svg_element& lhs)
    { // might be useful for Boost.Test.
      return lhs.id_name == id_name;
    }

    // Set and get member functions.
    svg_style& style()
    {
      return style_info;
    }

    const svg_style& style() const
    { // const version.
      return style_info;
    }

    void id(const std::string& id)
    { // Unique name for an element.
      // http://www.w3.org/TR/SVG/struct.html#IDAttribute
      // 5.10.1 Attributes common to all elements: id and xml:base
      // The id and xml:base attributes are available on all SVG elements:
      // Attribute definitions:
      // id = "name"
      // Standard XML attribute for assigning a unique name to an element.
      // Refer to the "Extensible Markup Language (XML) 1.0" Recommendation [XML10].
      // xml:base = "<uri>"
      // Specifies a base URI other than the base URI of the document or external entity.
      // Refer to the "XML Base" specification [XML-BASE].
      // A group of elements, as well as individual objects,
      // can be given a name using the id attribute.
      // Named groups are needed for several purposes such as animation and re-usable objects.
      id_name = id;
      // Example: id="plotBackground"
    }

    std::string id()
    { // Unique name for an element.
      return id_name;
    }

    void clip_id(const std::string& id)
    { // Named clip, for example: g_ptr.clip_id(plot_window_clip);
      clip_name = id;
    }

    std::string clip_id()
    {
      return clip_name;
    }
  }; // class svg_element

  // Derived elements whose write member functions
  // output SVG XML for line, circle, rectangle, text...
  // Reminder: Within a literal C string, \"  is needed to output a " ;-)

  // -----------------------------------------------------------------
  // Represents a line
  // -----------------------------------------------------------------
  class line_element: public svg_element
  {
  private:
    double x1; // Line from (x1, x2) to (y1, y2)
    double x2;
    double y1;
    double y2;

  public:
    line_element(double x1, double y1, double x2,  double y2)
      :   x1(x1), y1(y1),  x2(x2), y2(y2)
    {
    }

    void write(std::ostream& rhs)
    {
      rhs << "<line x1=\"" << x1 << "\" y1=\"" << y1
          << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\"/>";
      // Example: <line x1="5" y1="185" x2="340" y2="185"/>
    }
  }; // class line_element
  // --------------------------------------------------
  // class rect_element; Represents a single rectangle.
  // --------------------------------------------------

  class rect_element : public svg_element
  {
    friend bool operator==(const rect_element&, const rect_element&);
    friend bool operator!=(const rect_element&, const rect_element&);

  private:
    double x_;
    double y_;
    double height_;
    double width_;
  public:

    rect_element(double x, double y, double w, double h)
      : x_(x), y_(y), width_(w), height_(h)
    { // Constructor defines all private data (no defaults).
    }

    double x() const
    {
      return x_;
    }

    double y() const
    {
      return y_;
    }

    double width() const
    {
      return width_;
    }

    double height() const
    {
      return height_;
    }

    void write(std::ostream& rhs)
    { // SVG xml
      rhs << "<rect";
      write_attributes(rhs); // id (& clip_path)
      rhs << " x=\"" << x_ << "\""
        << " y=\"" << y_ << "\""
        << " width=\"" << width_ << "\""
        << " height=\""<< height_<< "\"/>";
      // For example: <rect  x="0" y="0"  width="500"  height="350"/>
    }

    bool operator==(const rect_element& lhs)
    { // Useful for Boost.Test.
      return (lhs.x() == x_) && (lhs.y() == y_) &&  (lhs.width() == width_) && (lhs.height() == height_);
    }
    bool operator!=(const rect_element& lhs)
    {
      return (lhs.x() != x_) || (lhs.y() != y_) ||  (lhs.width() != width_) || (lhs.height() != height_);
    }
  }; // class rect_element

  bool operator==(const rect_element& lhs, const rect_element& rhs)
  { //
    return (lhs.x() == rhs.x()) && (lhs.y() == rhs.y()) && (lhs.width() == rhs.width()) && (lhs.height() == rhs.height());
  }

  bool operator!=(const rect_element& lhs, const rect_element& rhs)
  { //
    return (lhs.x() != rhs.x()) || (lhs.y() == rhs.y()) || (lhs.width() == rhs.width()) || (lhs.height() == rhs.height());
  }

  std::ostream& operator<< (std::ostream& os, const rect_element& r)
  {  //
      os << "rect(" << r.x() << ", " << r.y()
         << ", " << r.width() << ", " << r.height() << ")" ;
    // Usage: rect_element r(20, 20, 50, 50);  cout << r << endl; 
    // Outputs:  rect(20, 20, 50, 50)
    return os;
  } // std::ostream& operator<<

  // -----------------------------------------------------------------
  // class circle_element  Represents a single circle.
  // -----------------------------------------------------------------
  class circle_element : public svg_element
  {
  private:
    double x;
    double y;
    double radius;
  public:
    circle_element(double x, double y, double radius = 5)
      : x(x), y(y), radius(radius)
    { // Define all private data.
    }

    void write(std::ostream& rhs)
    {
      rhs << "<circle";
      write_attributes(rhs);
      rhs << " cx=\"" << x << "\" cy=\"" << y << "\" r=\"" << radius << "\"/>";
      // Example: <circle cx="9.78571" cy="185" r="5"/>
    }
  }; // class circle_element


  // -----------------------------------------------------------------
  // Represents a single ellipse.
  // -----------------------------------------------------------------
  class ellipse_element : public svg_element
  { // http://www.w3.org/TR/SVG/shapes.html#EllipseElement
    // 9.4 The 'ellipse'  element.
  private:
    double cx; // coordinate x of center of ellipse, default 0
    double cy; // coordinate y, default 0
    double rx; // radius x
    double ry; // radius x
  public:
    ellipse_element(double cx, double cy, double rx = 4,  double ry = 8)
      : cx(cx), cy(cy), rx(rx), ry(ry)
    { // Define all private data.
    }

    void write(std::ostream& rhs)
    {
      rhs << "<ellipse";
      write_attributes(rhs);
      rhs << " cx=\"" << cx << "\" cy=\"" << cy << "\""
          << " rx=\"" << rx << "\" ry=\"" << ry  << "\"/>";
      // Example: <ellipse rx="250" ry="100" fill="red"  />
    }
  }; // class ellipse_element



  // ----------------------------------------------------------------------
  // text_element Represents a single block of text, with font & alignment.
  // ----------------------------------------------------------------------
  enum align_style
  {
    left_align, right_align, center_align
  };

  enum rotate_style
  { // Rotation in degrees from horizontal.
    horizontal = 0, // normal left to right.
    upward = -90, // vertical writing up.
    downward = 90,  // vertical writing down.
    upsidedown = 180 //
  };

  // text_element::text_element(double x, double y,
  //  const std::string&,
  //  int,
  //  const std::string& font,
  //  const std::string& style, const std::string& weight,
  //  const std::string& stretch, const std::string& decoration,
  //  int align, int rotate);

  class text_element: public svg_element
  { // Holds text with position, size, font, (& styles) & orientation.
    // Not necessarily shown correctly by all browsers, alas.
   private: // Access only via member functions below.
    double x_coord; // Cartesian units.
    double y_coord;
    // http://www.w3.org/TR/SVG/text.html#FontFamilyProperty
    // 10.10 Font selection properties
    std::string txt; // Actual text to display
    // (may contain embedded xml characters for Greek, math etc, for example &#x3A9;).
    int size; // " font-size = 12"
    // http://www.w3.org/TR/SVG/text.html#CharactersAndGlyphs
    std::string font;  // font-family: "Arial" | "Times New Roman" | "Verdana" | "Lucida Sans Unicode"
    std::string style; // font-style: normal | bold | italic | oblique
    std::string weight; // font-weight: normal | bold | bolder | lighter | 100 | 200 .. 900
    std::string stretch; // font-stretch: normal | wider | narrower ...
    std::string decoration; // // "underline" | "overline" | "line-through"
    align_style align; // left_align, right_align, center_align
    int rotate; // horizontal, upward, downward, upsidedown

    // Example:
    // <text x="250" y="219.5" text-anchor="middle"  font-family="verdana" font-size="12">0 </text>

  public:
    // Set and get member functions.
    void font_alignment(align_style a)
    { // left_align, right_align, center_align
      align = a;
    }

    align_style font_alignment()
    { // left_align, right_align, center_align
      return align;
    }

    void font_family(const std::string& s)
    { // Examples: "Arial", "Times New Roman", "Verdana", "Lucida Sans Unicode"
      font = s;
    }

    const std::string& font_family() const
    {
      return font;
    }

    void font_style(const std::string& s)
    {
      style = s;
    }

    const std::string& font_style() const
    {
      return style;
    }

    void font_weight(const std::string& s)
    { // normal | bold | bolder | lighter | 100 | 200 .. 900
      weight = s;
    }

    const std::string& font_weight() const
    {
      return weight;
    }

    void font_stretch(const std::string& s)
    { // normal | wider | narrower .
      stretch = s;
    }

    const std::string& font_stretch() const
    {
      return stretch;
    }

    void font_decoration(const std::string& s)
    { // "underline" | "overline" | "line-through"
      decoration = s;
    }

    const std::string& font_decoration() const
    {
      return decoration;
    }

    void font_size(unsigned int i)
    { // pixels, default 10.
      size = i;
    }

    int font_size() const
    {
      return size;
    }

    void font_rotation(int rot)
    { // Degrees: horizontal  = 0, upward = -90, downward, upsidedown
      rotate = rot;
    }

    int font_rotation() const
    {
      return rotate;
    }

    void x(double x)
    { // x coordinate of text to write.
      x_coord = x;
    }

    double x() const
    { // x coordinate of text to write.
      return x_coord;
    }

    void y(double y)
    { // y coordinate of text to write.
      y_coord = y;
    }

    double y() const
    { // y coordinate of text to write.
      return y_coord;
    }

    void text(const std::string& t)
    { // text to write.
      txt = t;
    }

    std::string text()
    {
      return txt;
    }

    text_element(double x = 0., double y = 0.,
      const std::string& text = "",
      int size = 12,
      const std::string& font = "Lucida Sans Unicode",
      const std::string& style = "", const std::string& weight = "",
      const std::string& stretch = "", const std::string& decoration = "",
      align_style align = center_align, int rotate = horizontal)
      :
    x_coord(x), y_coord(y),
      txt(text),
      size(size),
      font(font),
      style(style), weight(weight), stretch(stretch), decoration(decoration),
      align(align), rotate(rotate)
    { // text_element default constructor, defines defaults for all private members.
    }

    void write(std::ostream& rhs)
    { // text & atributes to stream.
      // Changed to new convention on spaces:
      // NO trailing space, but *start* each item with a space.
      rhs << "<text x=\"" << x_coord << "\" y=\"" << y_coord << "\"";
      std::string anchor;
      switch(align)
      {
      case left_align:
        anchor = " start";
        break;
      case right_align:
        anchor = " end";
        break;
      case center_align:
        anchor = " middle";
        break;
      default:
        anchor = "";
        break;
      }
      if(anchor != "")
      {
        rhs << " text-anchor=\"" << anchor << "\"";
      }
      if(rotate != 0)
      {
        rhs << " transform = \"rotate("
          << rotate << " "
          << x_coord << " "
          << y_coord << " )\"";
      }
      if (font.size() != 0)
      {
        rhs << " font-family=\"" << font << "\"";
      }
      if (style.size() != 0)
      {
        rhs << " font-style=\"" << style << "\"";
      }
      if (weight.size() != 0)
      {
      rhs << " font-weight=\"" << weight << "\"";
      }
      if (stretch.size() != 0)
      {
      rhs << " font-stretch=\"" << stretch << "\"";
      }
      if (decoration.size() != 0)
      {
      rhs << " font-decoration=\"" << decoration << "\"";
      }
      if(size == 0)
      { // Use a default font size of 12 if none specified.
        rhs << " font-size=\"12\">";
      }
      else
      {
        rhs << " font-size=\"" << size << "\">";
      }
      rhs << txt << "</text>";
      // Example: <text x="149" y="207" text-anchor=" middle" font-family="Lucida Sans Unicode" font-size="12">3 </text>
    } // void write(std::ostream& rhs)

  }; // class text_element

  class clip_path_element: public svg_element
  { // The clipping path restricts the region to which paint can be applied.
    // 14.3 Clipping paths http://www.w3.org/TR/SVG/masking.html#ClipPathProperty
  private:
    std::string element_id;
    rect_element rect; // Clipping rectangle.

  public:

    clip_path_element(const std::string& id, const rect_element& rect)
      : element_id(id), rect(rect)
      { // Constructor defines all member variables.
      }

      void write(std::ostream& os)
      {
        os << "<clipPath id=\"" << element_id << "\">";
        rect.write(os);
        os  << "</clipPath>" << std::endl;
      }
  }; // class clip_path_element

  struct path_point
  { // Base class for m_path, z_path, q_path, h_path, v_path, c_path, s_path.
    // Paths represent the outline of a shape which can be
    // filled, stroked, used as a clipping path, or any combination of the three.
    bool relative; // or if false then absolute.

    virtual void write(std::ostream& rhs) = 0;
    virtual ~path_point()
    {
    }

    path_point(bool relative) : relative(relative)
    { // Constructor defines all member variables.
    }
  }; // struct path_point


  struct m_path: public path_point
  { // moveto coordinates (x, y)
    //    8.3.2 The "moveto" commands.
    double x;
    double y;

    void write(std::ostream& o_str)
    {
      if(relative)
      {
        o_str << "m";
      }
      else
      { // absolute
        o_str << "M";
      }
      o_str << x << "," << y << " "; // separator changed to comma for clarity.
      // Example: "M52.8571 180 "
    } // void write(std::ostream& o_str)

    m_path(double x, double y, bool relative = false)
      : x(x), y(y), path_point(relative)
    {
    }
  }; // struct m_path

  struct z_path: public path_point
  { // http://www.w3.org/TR/SVG/paths.html#PathElement
    // 8.3.1 General information about path data.
    // z indicates a closepath.
    // Close the current subpath by drawing a straight line
    // from the current point to current subpath's initial point.
    void write(std::ostream& o_str)
    {
      o_str << "Z";
    }

    z_path() : path_point(false)
    { // Constructor defines all member variables.
    }
  }; // struct z_path

  // 8.3.4 The "lineto" commands L, H & V.
  struct l_path: public path_point
  {
    // Draw a line from the current point to the given (x,y) coordinate
    // which becomes the new current point.
    double x;
    double y;

    void write(std::ostream& o_str)
    {
      if(relative)
      {
        o_str<<"l";
      }
      else
      { // Absolute.
        o_str << "L";
      }
      o_str << x << "," << y << " ";
    }

    l_path(double x, double y, bool relative = false)
      : x(x), y(y), path_point(relative)
    { // Constructor defines all member variables.
    }
  }; // struct l_path

  struct h_path: public path_point
  { // Draws a horizontal line from the current point (cpx, cpy) to (x, cpy).
    double x;
    // No y needed, start from current point y.

    void write(std::ostream& o_str)
    {
      if(relative)
      {
        o_str << "h";
      }
      else
      { // Absolute.
        o_str << "H";
      }
      o_str << x << " ";
    }

    h_path(double x, bool relative = false)
      : x(x), path_point(relative)
    { // Constructor defines all member variables.
    }
  }; // struct h_path

  struct v_path: public path_point
  { // Draws a vertical line from the current point (cpx, cpy) to (cpx, y).
    double y;
    // No x coordinate needed - use current point x
    void write(std::ostream& o_str)
    {
      if(relative)
      {
        o_str << "v";
      }
      else
      { // Absolute.
        o_str << "V";
      }
      o_str << y << " ";
    }

    v_path(double y, bool relative = false)
      : y(y), path_point(relative)
    { // Constructor defines all member variables.
    }
  }; // struct v_path

  // 8.3.5 The curve commands: C, Q & A.

  struct c_path: public path_point
  { // Draws a cubic B�zier curve from the current point to (x,y) using (x1,y1).
    double x1;
    double y1;
    double x2;
    double y2;
    double x;
    double y;

    void write(std::ostream& o_str)
    {
      if(relative)
      {
        o_str<<"c";
      }
      else
      { // Absolute.
        o_str<<"C";
      }
      o_str << x1 << "," << y1 << " "
        << x2 << "," << y2 << " "
        << x << "," << y << " ";
    }

    c_path(double x1, double y1, double x2, double y2,
            double x, double y, bool relative = false)
      : x1(x1), y1(y1), x2(x2), y2(y2), x(x), y(y), path_point(relative)
    { // Constructor defines all member variables.
    }
  }; // struct c_path

  struct q_path: public path_point
  { // Draws a quadratic B�zier curve from the current point to (x,y).
    // using (x1,y1) as the control point.
    double x1, y1, x, y;

    void write(std::ostream& o_str)
    {
      if(relative)
      {
        o_str << "q";
      }
      else
      { // Absolute.
        o_str << "Q";
      }
      o_str << x1 << " " << y1 << " "
         << x << " " << y << " ";
    }

    q_path(double x1, double y1, double x, double y, bool relative = false)
      : x1(x1), y1(y1), x(x), y(y), path_point(relative)
    { // Constructor.
    }
  }; //struct q_path

  struct s_path : public path_point
  { // Draws a cubic B�zier curve from the current point to (x,y).
    double x1, y1, x, y;

    void write(std::ostream& o_str)
    {
      if(relative)
      {
        o_str << "s";
      }
      else
      { // Absolute.
        o_str << "S";
      }
      o_str << x1 << "," << y1 << " "
        << x << "," << y << " ";
    }

    s_path(double x1, double y1, double x, double y, bool relative = false)
      : x1(x1), y1(y1), x(x), y(y), path_point(relative)
    { // Constructor.
    }
  }; // struct s_path

  struct t_path: public path_point
  { // Draws a quadratic B�zier curve from the current point to (x,y).
    double x;
    double y;

    void write(std::ostream& o_str)
    {
      if(relative)
      {
        o_str << "t";
      }
      else
      { // Absolute.
        o_str << "T";
      }
      o_str << x << "," << y << " ";
    }

    t_path(double x, double y, bool relative = false)
      : x(x), y(y), path_point(relative)
    { // Constructor
    }
  }; // struct t_path

  struct a_path: public path_point
  { // Draws a elliptical arc from the current point to (x,y),
    // using two radii, axis rotation, and control two flags.
    // See 8.3.8 The elliptical arc curve commands.
    // Needed for pie charts, etc.
    double x;
    double y;
    double rx;
    double ry;
    double x_axis_rotation;
    bool large_arc; // true if arc >= 180 degrees wanted.
    bool sweep; // true if to draw in positive-angle direction

    void write(std::ostream& o_str)
    {
      if(relative)
      {
        o_str << "a";
      }
      else
      { // Absolute.
        o_str << "A";
      }
      o_str << rx << "," << ry << " " << x_axis_rotation
        << ((large_arc) ? 1 : 0) << "," << ((sweep) ? 1 : 0) << " "
        << x << "," << y << " ";
    }

    a_path(double x, double y, double rx, double ry, double x_axis_rotation, bool large_arc = false, bool sweep = false, bool relative = false)
      : x(x), y(y), rx(rx), ry(ry), x_axis_rotation(x_axis_rotation), large_arc(large_arc), sweep(sweep), path_point(relative)
    { // Constructor
    }
  }; // struct a_path

  class path_element: public svg_element
  { // http://www.w3.org/TR/SVG/paths.html#PathElement
    // 8.3.1 General information about path data.
    // A path is defined by including a 'path'  element
    // which contains a d="(path data)"  attribute,
    // where the d attribute contains the moveto, line, curve
    // (both cubic and quadratic B�ziers), arc and closepath instructions.
  private:
    ptr_vector<path_point> path; // All the (x, y) coordinate pairs,
    // filled by calls of m, M, l , L... that push_back.
  public:
    bool fill;

    path_element(const path_element& rhs)
    {
      path = (const_cast<path_element&>(rhs)).path.release();
    }

    path_element() : fill(true)
    {
    }

    // Note 1: return of path_element& permits chaining calls like
    // my_path.M(3, 3).l(150, 150).l(200, 200)...;

    // Note 2: By convention:
    // lower case (like m call m_path(x, y, true) for relative
    // but upper case (like M) calls m_path(x, y, false) for absolute.

    path_element& m(double x, double y)
    { // relative.
      path.push_back(new m_path(x, y, true));
      return *this;
    }

    path_element& M(double x, double y)
    { // absolute.
      path.push_back(new m_path(x, y, false));
      return *this;
    }

    path_element& z()
    {
      path.push_back(new z_path());
      return *this;
    }

    path_element& l(double x, double y)
    {
      path.push_back(new l_path(x, y, true));
      return *this;
    }

    path_element& L(double x, double y)
    {
      path.push_back(new l_path(x, y, false));
      return *this;
    }

    path_element& h(double x)
    {
      path.push_back(new h_path(x, true));
      return *this;
    }

    path_element& H(double x)
    {
      path.push_back(new h_path(x, false));
      return *this;
    }

    path_element& v(double y)
    {
      path.push_back(new v_path(y, true));
      return *this;
    }

    path_element& V(double y)
    {
      path.push_back(new v_path(y, false));
      return *this;
    }

    path_element& c(double x1, double y1, double x2, double y2, double x, double y)
    {
      path.push_back(new c_path(x1, y1, x2, y2, x, y, true));
      return *this;
    }

    path_element& C(double x1, double y1, double x2, double y2, double x, double y)
    {
      path.push_back(new c_path(x1, y1, x2, y2, x, y, false));
      return *this;
    }

    path_element& q(double x1, double y1, double x, double y)
    {
      path.push_back(new q_path(x1, y1, x, y, true));
      return *this;
    }

    path_element& Q(double x1, double y1, double x, double y)
    {
      path.push_back(new q_path(x1, y1, x, y, false));
      return *this;
    }

    path_element& s(double x1, double y1, double x, double y)
    {
      path.push_back(new s_path(x1, y1, x, y, true));
      return *this;
    }

    path_element& S(double x1, double y1, double x, double y)
    { // 
      path.push_back(new s_path(x1, y1, x, y, false));
      return *this;
    }

    path_element& t(double x, double y)
    {
      path.push_back(new t_path(x, y, true));
      return *this;
    }

    path_element& T(double x, double y)
    {
      path.push_back(new t_path(x, y, false));
      return *this;
    }

    void write(std::ostream& o_str)
    {
      o_str << "<path d=\"";
      for(ptr_vector<path_point>::iterator i = path.begin(); i != path.end(); ++i)
      {
        (*i).write(o_str); // M1,2
      }
      o_str << "\""; 
      write_attributes(o_str); // id & clip_path
      style_info.write(o_str); // fill, stroke, width...
      if(!fill)
      {
        o_str << " fill = \"none\"";
      }
      o_str<<"/>";
      // Example: <path d="M5,175 L5,195 M148.571,175" />
    } // void write(std::ostream& o_str)
  }; // class path_element

  struct poly_path_point
  { // polyline or polygon point coordinates (x, y)
    // 9.6 polyline & 9.7 The 'polygon' element.
    double x;
    double y;
    // Polygon & polyline points are always absolute, never relative,
    // and values have no preceeding letter like M or L,
    // So NOT derived from path_point.

    void write(std::ostream& o_str)
    {
      o_str << " " << x << "," << y; // x, y separator comma for clarity.
      // Leading space is redundant for 1st after "points= ",
      // but others are separators, and arkward to know which is 1st.
      // Example: " 250,180"
    } // void write(std::ostream& o_str)

    poly_path_point(double x, double y)
      : x(x), y(y)
    {
    }

    poly_path_point()
      : x(0.), y(0.)
    { // Default constructor.
    }

  }; // struct poly_path_point

  std::ostream& operator<< (std::ostream& os, const poly_path_point& p)
  { // May be needed for Boost.Test.
    os << "(" << p.x << ", " << p.y  << ")" ;
    // Usage:  poly_path_point p0(100, 200);
    // cout << p0 << endl;
    // Outputs: (100, 200)
    return os;
  } // std::ostream& operator<<

  class polygon_element: public svg_element
  { // http://www.w3.org/TR/SVG/shapes.html#PolygonElement
    // 9. 9.7 The 'polygon'  element
    // The 'polygon' element defines a closed shape
    // consisting of a set of connected straight line segments.
    // A polygon is defined by including a 'path'  element
    // which contains a points="(path data)"  attribute,
    // where the d attribute contains the x, y coordinate pairs.
  private:
    //using boost::ptr_vector;
    ptr_vector<poly_path_point> poly_points; // All the x, y coordinate pairs,
    // push_backed by calls of p_path(x, y).
  public:
    bool fill; // polygon to have fill color.

    polygon_element(const polygon_element& rhs)
    { // Copy constructor.
      poly_points = (const_cast<polygon_element&>(rhs)).poly_points.release();
      // 'empty' the vector of points.
    }

    polygon_element() : fill(true)
    {
    }

    polygon_element (double x, double y, bool f = true) : fill(f)
    { // Constructor - One absolute (x, y) point only.
      // Can add more path points using member function P.
      poly_points.push_back(new poly_path_point(x, y));
    }

    polygon_element (double x1, double y1, double x2, double y2, double x3, double y3, bool f = true) : fill(f)
    { // Constructor - Absolute (x, y) only. Used by triangle.
      poly_points.push_back(new poly_path_point(x1, y1));
      poly_points.push_back(new poly_path_point(x2, y2));
      poly_points.push_back(new poly_path_point(x3, y3));
    }

    polygon_element (double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, bool f = true)
      :
      fill(f)
    { // Constructor - Absolute (x, y) only. Used by rhombus.
      poly_points.push_back(new poly_path_point(x1, y1));
      poly_points.push_back(new poly_path_point(x2, y2));
      poly_points.push_back(new poly_path_point(x3, y3));
      poly_points.push_back(new poly_path_point(x4, y4));
    }
    
    polygon_element (double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5, bool f = true)
      :
      fill(f)
    { // Constructor - Absolute (x, y) only. Used by pentagon.
      poly_points.push_back(new poly_path_point(x1, y1));
      poly_points.push_back(new poly_path_point(x2, y2));
      poly_points.push_back(new poly_path_point(x3, y3));
      poly_points.push_back(new poly_path_point(x4, y4));
      poly_points.push_back(new poly_path_point(x5, y5));
    }

    polygon_element (double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5, double x6, double y6, bool f = true)
      :
      fill(f)
    { // Constructor - Six absolute (x, y) only. Used by hexagon.
      // Might be done more efficiently with fixed size boost::array?
      poly_points.push_back(new poly_path_point(x1, y1));
      poly_points.push_back(new poly_path_point(x2, y2));
      poly_points.push_back(new poly_path_point(x3, y3));
      poly_points.push_back(new poly_path_point(x4, y4));
      poly_points.push_back(new poly_path_point(x5, y5));
      poly_points.push_back(new poly_path_point(x6, y6));
    }

    polygon_element (std::vector<poly_path_point>& points, bool f = true)
      :
      fill(f)
    { // Constructor from vector of path points.
      poly_points.reserve(points.size()); // Since we know how many will be pushed.
      for(std::vector<poly_path_point>::iterator i = points.begin(); i != points.end(); ++i)
      {
        poly_path_point p = (*i);
        poly_points.push_back(new poly_path_point(p.x, p.y));
      }
    }

    template<int n> 
    polygon_element (boost::array<const poly_path_point, n>& points, bool f = true)
      :
      fill(f)
    { // Constructor from const array of path points.
      poly_points.reserve(n); // Since we know how many will be pushed.
      //poly_points.reserve(points.size()); // Since we know how many will be pushed.
      for(array<const poly_path_point, n>::iterator i = points.begin(); i != points.end(); ++i)
      {
        poly_path_point p = (*i);
        poly_points.push_back(new poly_path_point(p.x, p.y));
      }
    }

    // And non-const poly_path_point version, in case needed.
    template<int n> 
    polygon_element (boost::array<poly_path_point, n>& points, bool f = true)
      :
      fill(f)
    { // Constructor from const array of path points.
      poly_points.reserve(n); // Since we know how many will be pushed.
      // == poly_points.reserve(points.size()); // Since we know how many will be pushed.
      for(array<poly_path_point, n>::iterator i = points.begin(); i != points.end(); ++i)
      {
        poly_path_point p = (*i);
        poly_points.push_back(new poly_path_point(p.x, p.y));
      }
    }

    // Member function to add more points to polygon.
    polygon_element& P(double x, double y)
    { // Add another  (x, y) - absolute only.
      poly_points.push_back(new poly_path_point(x, y));
      return *this;
    }

    void write(std::ostream& o_str)
    {
      o_str << "<polygon points=\"";
      for(ptr_vector<poly_path_point>::iterator i = poly_points.begin(); i!=poly_points.end(); ++i)
      {
        (*i).write(o_str); //  x, y coordinates as " 1,2"
      }
      o_str << "\"";
      write_attributes(o_str);
      style_info.write(o_str);
      if(!fill)
      {
        o_str << " fill = \"none\"";
      }
      o_str<<"/>";
      // Example: <polygon fill="lime" stroke="blue" stroke-width="10"
      //      points="850,75  958,137.5 958,262.5
      //             850,325 742,262.6 742,137.5" />
    } // void write(std::ostream& o_str)

  }; // class polygon_element

  class polyline_element: public svg_element
  { // http://www.w3.org/TR/SVG/shapes.html#PolylineElement
    // 9.6 The 'polyline'  element: defines a set of connected straight line segments.
    // Typically, 'polyline' elements define open shapes.
    // A polyline is defined by including a 'path'  element
    // which contains a points="(path data)"  attribute,
    // where the points attribute contains the x, y coordinate pairs.
    // * perform an absolute moveto operation
    //   to the first coordinate pair in the list of points
    // * for each subsequent coordinate pair,
    //   perform an absolute lineto operation to that coordinate pair.
    // The advantage of polyline is in reducing file size,
    // avoiding M and repeated L before x & y coordinate pairs.

  private:
    ptr_vector<poly_path_point> poly_points; // All the (x, y) coordinate pairs,
    // push_back by calls of p_path(x, y).
  public:
    //bool fill; // not needed for polyline, unlike polygon.

    polyline_element(const polyline_element& rhs)
    { // copy constructor.
      poly_points = (const_cast<polyline_element&>(rhs)).poly_points.release();
    }

    polyline_element()
    { // Construct an 'empty' line.
      // Can new line path points add using polyline_element member function P.
    }

    polyline_element (double x1, double y1)
    { // One (x, y) path point, absolute only.
      poly_points.push_back(new poly_path_point(x1, y1));
    }

    polyline_element (double x1, double y1, double x2, double y2)
    { // Two (x, y) path points, absolute only.
      poly_points.push_back(new poly_path_point(x1, y1));
      poly_points.push_back(new poly_path_point(x2, y2));
    }

    polyline_element (std::vector<poly_path_point>& points)
    { // Constructor from vector of path points.
      for(std::vector<poly_path_point>::iterator i = points.begin(); i != points.end(); ++i)
      {
        poly_path_point p = (*i);
        poly_points.push_back(new poly_path_point(p.x, p.y));
      }
    }

    // Member function to add new points to existing line.
    polyline_element& P(double x, double y)
    { // Absolute (x, y) only, so Capital letter P.
      poly_points.push_back(new poly_path_point(x, y));
      return *this;
    }

    void write(std::ostream& o_str)
    {
      o_str << "<polyline points=\"";
      for(ptr_vector<poly_path_point>::iterator i = poly_points.begin(); i!= poly_points.end(); ++i)
      {
        (*i).write(o_str); //  x, y coordinates as " 1,2"
      } 
      o_str << "\"";
      write_attributes(o_str);
      style_info.write(o_str);
      o_str<<"/>";
      // Example: <polyline points=" 100,100 200,100 300,200 400,400"/>
    } // void write(std::ostream& o_str)

  }; // class polyline_element

  // -------------------------------------------------------------------
  // g_element (group element) is the node element of our document tree.
  // 'g' element is a container element for grouping together <g /></g>
  // related graphics elements, for example:
  // <g fill="rgb(255,255,255)" id="background"><rect width="500" height="350"/></g>
  // -------------------------------------------------------------------
  class g_element: public svg_element
  {
  private:
    ptr_vector<svg_element> children; // of this group element node,
    // containg graphics elements like text, circle line, polyline...
    std::string clip_name;
    bool clip_on;
  public:

    g_element() : clip_on(false)
    {
    }

    svg_element& operator[](unsigned int i)
    {
      return children[i];
    }

    size_t size()
    {
      return children.size();
    }

    void write(std::ostream& rhs)
    {
      rhs << "<g"; // Do NOT need space if convention is to start following with space.
      write_attributes(rhs); // id="background"
      style_info.write(rhs); // stroke="rgb(0,0,0)"
      rhs << ">" ;
      for(unsigned int i = 0; i < children.size(); ++i)
      {
        children[i].write(rhs); 
      }
      rhs << "</g>" << std::endl;
      // Example:
      // <g fill="rgb(255,255,255)" id="background"><rect x="0" y="0" width="500" height="350"/></g>
    } // void write(std::ostream& rhs)

    g_element& g_tag(int i)
    { // i is index of children nodes.
      return *(static_cast<g_element*>(&children[i]));
    }

    // Returns a reference to the new child node just created.
    g_element& add_g_element()
    {
      children.push_back(new g_element);
      return *(static_cast<g_element*>(&children[children.size()-1]));
    }

    // get ith g_element or child node.
    g_element& get_g_element(int i)
    {
      return *(static_cast<g_element*>(&children[i]));
    }

    void push_back(svg_element* g)
    {
      children.push_back(g);
    }

    void clear()
    {
      children.clear();
    }

    // Push_back the several elements:
    // circle, ellipse, rect, line, path, text, polyline, polygon.
    g_element& circle(double x, double y, double radius = 5.)
    {
      children.push_back(new circle_element(x, y, radius));
      return *this;
    }

    g_element& ellipse(double x, double y, double radius_x = 3., double radius_y = 6.)
    {
      children.push_back(new ellipse_element(x, y, radius_x, radius_y));
      return *this;
    }

    g_element& text(double x = 0., double y = 0.,
      // The order of arguments DOES NOW match svg& text_element!
      // text_element::text_element(double x, double y,
      //  const std::string&,
      //  int,
      //  const std::string& font,
      //  const std::string& style, const std::string& weight,
      //  const std::string& stretch, const std::string& decoration,
      //  int align, int rotate);

      const std::string& text = "",
      int text_size = 12,
      const std::string& font = "Lucida Sans Unicode",
      const std::string& style = "", const std::string& weight = "",
      const std::string& stretch = "", const std::string& decoration = "",
      align_style align = center_align, int rotate = horizontal)
    {
      children.push_back(new text_element(x, y, text, text_size, font, style, weight, stretch, decoration, align, rotate));
      return *this;
    }

    g_element& rect(double x1, double y1, double x2, double y2)
    {
      children.push_back(new rect_element(x1, y1, x2, y2));
      return *this;
    }

    g_element& line(double x1, double y1, double x2, double y2)
    {
      children.push_back(new line_element(x1, y1, x2, y2));
      return *this;
    }

    g_element& polygon(double x1, double y1, bool f)
    {
      children.push_back(new polygon_element(x1, y1, f));
      return *this;
    }

    g_element& polygon(std::vector<poly_path_point>& points, bool f)
    {
      children.push_back(new polygon_element(points, f));
      return *this;
    }

    g_element& triangle(double x1, double y1, double x2, double y2, double x3, double y3, bool f)
    {
      children.push_back(new polygon_element(x1, y1, x2, y2, x3, y3, f));
      return *this;
    }

    g_element& rhombus(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, bool f)
    {
      children.push_back(new polygon_element(x1, y1, x2, y2, x3, y3, x4, y4, f));
      return *this;
    }

    g_element& polyline(double x1, double y1, bool f)
    {
      children.push_back(new polygon_element(x1, y1, f));
      return *this;
    }

   // These return a reference to the last child node just pushed.
    // (Unlike the above functions that return a g_element&).
    polygon_element& polygon()
    {
      children.push_back(new polygon_element()); // Empty polygon,
      // to which poly_path_points can be added later using member function P.
      return *(static_cast<polygon_element*>(&(children[(unsigned int)(children.size()-1)])));
    }

    polyline_element& polyline()
    {
      children.push_back(new polyline_element()); // Empty polyline.
      return *(static_cast<polyline_element*>(&(children[(unsigned int)(children.size()-1)])));
    }

    path_element& path()
    {
      children.push_back(new path_element()); // Empty path.
      return *(static_cast<path_element*>(&(children[(unsigned int)(children.size()-1)])));
    }

  }; // class g_element

} // namespace svg
} // namespace boost

#endif // BOOST_SVG_TAG_HPP
