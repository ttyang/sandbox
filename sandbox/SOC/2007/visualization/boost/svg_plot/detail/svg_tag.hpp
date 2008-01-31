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

// -----------------------------------------------------------------------------
// This file svg_tag.hpp defines all classes that can occur in the 
// SVG parse tree.
// -----------------------------------------------------------------------------

#include <boost/ptr_container/ptr_container.hpp>
// using boost::vec_ptr;
#include <boost/array.hpp>
// using boost::array;

#include "../svg_style.hpp"
#include "svg_style_detail.hpp"

#include <ostream>
// using std::ostream;
#include <string>
// using std::string;
#include <vector>
// using std::vector;

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

  // --------------------------------------------------------------------------
  // svg_element is base class for all the leaf elements:
  // rect_element, circle_element, line_element, text_element,
  // polygon_element, polyline_element, path_element, clip_path_element, 
  // g_element
  //
  // g_element ('g' element is a container element
  // for grouping together related graphics elements).
  // http://www.w3.org/TR/SVG/struct.html#NewDocument 5.2.1 Overview
  // --------------------------------------------------------------------------

  class svg_element
  { // Base class 
  protected:
    svg_style style_info_; // fill, stroke, width, get by function style.
    std::string id_name_; // set & get by function id.
    std::string class_name_; // set & get by class id.
    std::string clip_name_; // set & get by function clip_id.

    void write_attributes(std::ostream& s_out)
    { // group_element id and clip-path.
      if(id_name_.size() != 0)
      { // Example: id="imageBackground"
        s_out << " id=\"" << id_name_ << "\""; // Prefix with space.
      }
      if(class_name_.size() != 0)
      {
        s_out << " class=\"" << class_name_ << "\"";
      }
      if(clip_name_.size() != 0)
      { // Example: clip-path="url(#plot_window)" 
        s_out << " clip-path=\"url(#" << clip_name_ << ")\""; // Prefix with space.
      }
      // Inherited classes add other references, 5.3.1, like color, fill, stroke, gradients...
      // Example id: <g id="yMinorGrid" ></g>
      // Example class: <g class="grid_style"></g>
      // Example URI: fill="url(#Gradient01) // local URL
    } // void write_attributes(std::ostream& s_out)

  public:

    svg_element(const svg_style& style_info, 
                const std::string& id_name = "",
                const std::string& class_name = "",
                const std::string& clip_name = "")
                :style_info_(style_info),
                id_name_(id_name),
                class_name_(class_name),
                clip_name_(clip_name)
    {
    }

    svg_element()
    {
    }

    virtual void write(std::ostream& rhs) = 0;
    virtual ~svg_element()
    {
    }

    bool operator==(const svg_element& lhs)
    { // might be useful for Boost.Test.
      return lhs.id_name_ == id_name_;
    }

    // Set and get member functions.
    svg_style& style()
    {
      return style_info_;
    }

    const svg_style& style() const
    { // const version.
      return style_info_;
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
      id_name_ = id;
      // Example: id="plotBackground"
    }

    std::string id()
    { // Unique name for an element.
      return id_name_;
    }

    void class_id(const std::string& class_id)
    { // Non-unique identifier for an element.
      // http://www.w3.org/TR/2001/REC-SVG-20010904/styling.html#ClassAttribute
      // 6.12 Attributes common to all elements: id and xml:base
      // Example: class="info"
      class_name_ = class_id;
    }

    std::string class_id()
    { // Unique name for an element.
      return class_name_;
    }

    void clip_id(const std::string& id)
    { // Named clip, for example: g_ptr.clip_id(plot_window_clip_);
      clip_name_ = id;
    }

    std::string clip_id()
    {
      return clip_name_;
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
    double x1_; // Line from (x1_, x2_) to (y1_, y2_)
    double x2_;
    double y1_;
    double y2_;

  public:
    line_element(double x1, double y1, double x2,  double y2)
      :   x1_(x1), y1_(y1),  x2_(x2), y2_(y2)
    {
    }

    line_element(double x1, double y1,
                 double x2, double y2, 
                 const svg_style& style_info, 
                 const std::string& id_name="", 
                 const std::string& class_name="",
                 const std::string& clip_name = "") 
                : x1_(x1), y1_(y1), x2_(x2), y2_(y2),
                  svg_element(style_info, id_name, class_name, clip_name)
    {
    }

    void write(std::ostream& rhs)
    {
      rhs << "<line x1=\"" << x1_ << "\" y1=\"" << y1_
          << "\" x2=\"" << x2_ << "\" y2=\"" << y2_ << "\"/>";
      // Example: <line x1="5" y1="185" x2="340" y2="185"/>
    }
  }; // class line_element


  // --------------------------------------------------
  // class rect_element: Represents a single rectangle.
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

    rect_element(double x, double y, double w, double h,
                 const svg_style& style_info,
                 const std::string& id_name,
                 const std::string& class_name,
                 const std::string& clip_name)
      : x_(x), y_(y), width_(w), height_(h),
        svg_element(style_info, id_name, class_name, clip_name)
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

    circle_element(double x, double y, double radius,
                 const svg_style& style_info,
                 const std::string& id_name="",
                 const std::string& class_name="",
                 const std::string& clip_name=""
                 )
      : x(x), y(y), radius(radius),
        svg_element(style_info, id_name, class_name, clip_name)
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

    ellipse_element(double cx, double cy, double rx,  double ry,
                 const svg_style& style_info,
                 const std::string& id_name="",
                 const std::string& class_name="",
                 const std::string& clip_name="")
      : cx(cx), cy(cy), rx(rx), ry(ry), 
        svg_element(style_info, id_name, class_name, clip_name)
    { // Define all private data.
    }

    ellipse_element(double cx, double cy,
                 const svg_style& style_info,
                 const std::string& id_name="",
                 const std::string& class_name="",
                 const std::string& clip_name="")
      : cx(cx), cy(cy), rx(4), ry(8), // 4 and 8 are the same defaults used above
        svg_element(style_info, id_name, class_name, clip_name)
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

class text_parent
{ // An ancestor to both tspan and strings for the text_element
  //    class. This allows an array of both to be stored in text_element.
  protected:
    std::string text_;

  public:
    virtual void write(std::ostream& o_str) { } 

    text_parent(const std::string& text): text_(text) { }
};

class text_element_text: public text_parent
{
public:
  text_element_text(const std::string& text): text_parent(text) { }

  void write(std::ostream& o_str)
  {
    o_str<<text_;
  }
};

class tspan_element: public text_parent, public svg_element
{
private:
  
  // Absolute position
  double x_, y_;

  // Relative position
  double dx_, dy_;

  int rotate_;
  
  // Allows the author to provide exact alignment
  double text_length_;

  // dx_, dy_, and rotate_ can all be omitted if they have a certain value,
  // but x_, y_, and text_length need a flag.
  bool use_x_, use_y_, use_text_length_;

  text_style style_; // font variants.

public:
  tspan_element(const std::string& text, const text_style& style = no_style):
    x_(0), y_(0), dx_(0), dy_(0), rotate_(0), text_length_(0),
    use_x_(false), use_y_(false), use_text_length_(false),
    style_(style), text_parent(text)
  {
  }

  // All of the setters.
  tspan_element& text(const std::string& text) 
  { 
    text_=text; 
    return *this;
  }

  tspan_element& dx(double dx) 
  { 
    dx_ = dx; 
    return *this;
  }

  tspan_element& dy(double dy) 
  { 
    dy_ = dy; 
    return *this;
  }

  tspan_element& rotation(int rotation) 
  { 
    rotate_ = rotation; 
    return *this;
  }

  tspan_element& x(double x)
  {
    x_ = x;
    use_x_ = true;
    return *this;
  }

  tspan_element& y(double y)
  {
    y_ = y;
    use_y_ = true;
    return *this;
  }

  tspan_element& text_length(double text_length)
  {
    text_length_ = text_length;
    use_text_length_ = true;
    return *this;
  }

  // All of the getters.
  std::string text(){ return text_; }
  double x() { return x_; }
  double y() { return y_; }
  double dx() { return dx_; }
  double dy() { return dy_; }
  int rotation() { return rotate_; }
  double text_length() { return text_length_; }

  text_style& font_style()
  { // Access to font family, size ...
    return style_;
  }

  const text_style& font_style() const
  {
    return style_;
  }


  void write(std::ostream& os)
  {
    os<<"<tspan";

    write_attributes(os); // id & clip_path
    style_info_.write(os); // fill, stroke, width...

    // All of the conditional writes within tspan_element.
    
    // First, all of the elements that can be tested based on their value.
    if(rotate_ != 0)
    {
      os<<" rotate=\""<<rotate_<<"\"";
    }

    if(dx_!= 0)
    {
      os<<" dx=\""<<dx_<<"\"";
    }

    if(dy_!= 0)
    {
      os<<" dy=\""<<dy_<<"\"";
    }

    // Now, add all of the elements that can be tested with the flags.
    if(use_x_)
    {
      os<<"x=\""<<x_<<"\"";
    }

    if(use_y_)
    {
      os<<"y=\""<<y_<<"\"";
    }

    if(use_text_length_)
    {
      os<<"textLength=\""<<text_length_<<"\"";
    }

    if (style_.font_size() != 0)
    {
      os << " font-size=\"" << style_.font_size() << "\"";
    }
    if (style_.font_family() != "")
    { // Example: Arial.
      os << " font-family=\"" << style_.font_family() << "\"";
    }
    if (style_.font_style().size() != 0)
    { // Example: italic.
      os << " font-style=\"" << style_.font_style() << "\"";
    }
    if (style_.font_weight().size() != 0)
    { // Example: bold.
    os << " font-weight=\"" << style_.font_weight() << "\"";
    }
    if (style_.font_stretch().size() != 0)
    {
    os << " font-stretch=\"" << style_.font_stretch() << "\"";
    }
    if (style_.font_decoration().size() != 0)
    {
    os << " font-decoration=\"" << style_.font_decoration() << "\"";
    }
    os<<">"<<text_<<"</tspan>";

  }
};

class text_element: public svg_element
{ // Holds text with position, size, font, (& styles) & orientation.
  // Not necessarily shown correctly by all browsers, alas.
 private: // Access only via member functions below.
  // SVG Coordinates of 1st character EM box, see
  // http://www.w3.org/TR/SVG/text.html#TextElement 10.2
  // So any text with y coordinate = 0  shows only any roman lower case descenders!
  double x_; // Left edge.
  double y_; // Bottom of roman capital character.
  ptr_vector<text_parent> data_; // Stores all of the containing data.
  text_style style_; // font variants.
  align_style align_; // left_align, right_align, center_align
  rotate_style rotate_; // horizontal, upward, downward, upsidedown
  
  void _generate_text(std::ostream& os)
  {
    for(ptr_vector<text_parent>::iterator i = data_.begin(); 
        i!=data_.end(); 
        ++i)
    {
      (*i).write(os);
    }
  }
  // (Text may contain embedded xml Unicode characters
  // for Greek, math etc, for example: &#x3A9;).
  //int size; // " font-size = 12"
  // http://www.w3.org/TR/SVG/text.html#CharactersAndGlyphs
  //std::string font;  // font-family: "Arial" | "Times New Roman" | "Verdana" | "Lucida Sans Unicode"
  // "sans", "serif", "times"
  // http://www.w3.org/TR/SVG/text.html#FontFamilyProperty
  // 10.10 Font selection properties
  //std::string style_; // font-style: normal | bold | italic | oblique
  //std::string weight; // font-weight: normal | bold | bolder | lighter | 100 | 200 .. 900
  //std::string stretch; // font-stretch: normal | wider | narrower ...
  //std::string decoration; // // "underline" | "overline" | "line-through"
  // Example:
  // <text x="250" y="219.5" text-anchor="middle"  font-family="verdana" font-size="12">0 </text>

public:

  text_style& style()
  { // Access to font family, size ...
    return style_;
  }

  const text_style& style() const
  {
    return style_;
  }

  void alignment(align_style a)
  { // left_align, right_align, center_align
    align_ = a;
  }

  align_style alignment()
  { // left_align, right_align, center_align
    return align_;
  }

  void rotation(rotate_style rot)
  { // Degrees: horizontal  = 0, upward = -90, downward, upsidedown
    rotate_ = rot;
  }

  rotate_style rotation() const
  {
    return rotate_;
  }

  void x(double x)
  { // x coordinate of text to write.
    x_ = x;
  }

  double x() const
  { // x coordinate of text to write.
    return x_;
  }

  void y(double y)
  { // y coordinate of text to write.
    y_ = y;
  }

  double y() const
  { // y coordinate of text to write.
    return y_;
  }

  void text(const std::string& t)
  { // text to write.
    data_.push_back(new text_element_text(t));
  }

  tspan_element& tspan(const std::string& t)
  {
    data_.push_back(new tspan_element(t, style_));
    return *(static_cast<tspan_element*>(&data_[data_.size()-1]));
  }

  text_element(
    // Coordinates of 1st character EM box, see
    // http://www.w3.org/TR/SVG/text.html#TextElement 10.2
    double x = 0., // Left edge.
    double y = 0., // Bottom of character (roman capital).
    // So any text with y coordinate = 0  shows only the roman lower case descenders!
    const std::string text = "",
    text_style ts = no_style, // Left to SVG defaults.
    align_style align = left_align,
    rotate_style rotate = horizontal)
    : // Constructor.
    x_(x), y_(y), // location.
    data_(ptr_vector<text_parent>()),
    //size(size), font(font), style_(style), weight(weight), stretch(stretch), decoration(decoration),
    style_(ts),
    align_(align),
    rotate_(rotate)
  { // text_element default constructor, defines defaults for all private members.
    data_.push_back(new text_element_text(text));
  }

  // Interestingly, we only need to define the copy constructor and 
  // operator=().. we don't need the destructor
  text_element(const text_element& rhs):
    x_(rhs.x_), y_(rhs.y_), data_(rhs.data_.clone()), style_(rhs.style_),
    align_(rhs.align_), rotate_(rhs.rotate_)
  {

  }

  text_element& operator=(const text_element& rhs)
  {
    x_ = rhs.x_;
    y_ = rhs.y_;
    data_ = rhs.data_.clone();
    style_ = rhs.style_;
    align_ = rhs.align_; 
    rotate_ = rhs.rotate_;
  }

  std::string text()
  {
   std::stringstream os;

    _generate_text(os);

   return os.str();
  }
  void write(std::ostream& os)
  { // text_element, style & attributes to stream.
    // Changed to new convention on spaces:
    // NO trailing space, but *start* each item with a space.
    // For debug, may be convenient to start with newline.
    // os << " <text x=\"" << x_ << "\" y=\"" << y_ << "\"";
    os << "\n<text x=\"" << x_ << "\" y=\"" << y_ << "\"";
    std::string anchor;
    switch(align_)
    {
    case left_align:
      // anchor = "start"; // This is the initial == default.
      // so should be possible to reduce file size this by:
      anchor = "";
      break;
    case right_align:
      anchor = "end";
      break;
    case center_align:
      anchor = "middle";
      break;
    default:
      anchor = "";
      break;
    }
    if(anchor != "")
    {
      os << " text-anchor=\"" << anchor << "\"";
    }
    if(rotate_ != 0)
    {
      os << " transform = \"rotate("
        << rotate_ << " "
        << x_ << " "
        << y_ << " )\"";
    }
    if (style_.font_size() != 0)
    {
      os << " font-size=\"" << style_.font_size() << "\"";
    }
    if (style_.font_family() != "")
    { // Example: Arial.
      os << " font-family=\"" << style_.font_family() << "\"";
    }
    if (style_.font_style().size() != 0)
    { // Example: italic.
      os << " font-style=\"" << style_.font_style() << "\"";
    }
    if (style_.font_weight().size() != 0)
    { // Example: bold.
    os << " font-weight=\"" << style_.font_weight() << "\"";
    }
    if (style_.font_stretch().size() != 0)
    {
    os << " font-stretch=\"" << style_.font_stretch() << "\"";
    }
    if (style_.font_decoration().size() != 0)
    {
    os << " font-decoration=\"" << style_.font_decoration() << "\"";
    }
    os << '>' ;

    _generate_text(os);

    os << "</text>";
    // Example:
  } // void write(std::ostream& os)
}; // class text_element_

  std::ostream& operator<< (std::ostream& os, text_element& t)
  {  //
      t.write(os);
    // Usage: text_element t(20, 30, "sometest", left_align, horizontal);  cout << t << endl; 
    // Outputs:  
    return os;
  } // std::ostream& operator<<

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
        o_str << "l";
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
        o_str << "c";
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

    path_element(const svg_style& style_info, 
        const std::string& id_name="", 
        const std::string& class_name="",
        const std::string& clip_name="")
        : svg_element(style_info, id_name, class_name, clip_name)
    {
    }

    path_element() : fill(true)
    { // TODO why is the default fill(true)?
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
      if (path.begin() != path.end() )
      { // Is some path info (trying to avoid useless <path d=""/>"
        // TODO or would this omit useful style & attributes?
        o_str << "<path d=\"";
        for(ptr_vector<path_point>::iterator i = path.begin(); i != path.end(); ++i)
        {
          (*i).write(o_str); // M1,2
        }
        o_str << "\"";

        write_attributes(o_str); // id & clip_path

        style_info_.write(o_str); // fill, stroke, width...

        if(!fill)
        {
          o_str << " fill=\"none\"";
        }
        o_str<<"/>"; // closing to match <path d=
      }
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
    os << "(" << p.x << ", " << p.y  << ")";
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
    friend std::ostream& operator<< (std::ostream&, const polygon_element&);
    friend std::ostream& operator<< (std::ostream&, polygon_element&);

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
/*
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
*/
    // Member function to add more points to polygon.
    polygon_element& P(double x, double y)
    { // Add another  (x, y) - absolute only.
      poly_points.push_back(new poly_path_point(x, y));
      return *this;
    }

    void write(std::ostream& o_str)
    {
      o_str << "<polygon points=\"";
      for(ptr_vector<poly_path_point>::iterator i = poly_points.begin(); i != poly_points.end(); ++i)
      {
        (*i).write(o_str); //  x, y coordinates as " 1,2"
      }
      o_str << "\"";
      write_attributes(o_str);
      style_info_.write(o_str);
      if(!fill)
      {
        o_str << " fill = \"none\"";
      }
      o_str<<"/>";
      // Example: <polygon fill="lime" stroke="blue" stroke-width="10"
      //      points="850,75  958,137.5 958,262.5
      //             850,325 742,262.6 742,137.5" />
    } // void write(std::ostream& o_str)

    std::ostream& operator<< (std::ostream& os)
    { // May be needed for Boost.Test. 
      for(ptr_vector<poly_path_point>::iterator i = poly_points.begin(); i != poly_points.end(); ++i)
      {
        os << (*i); //  x, y coordinates as " (1, 2)"
      }
      // using os << "(" << p.x << ", " << p.y  << ")" ;
      // Usage:  polygon_element p(1, 2, 3, 4, 5, 6);
      //   my_polygon.operator<<(cout);  
      // But NOT cout << my_polygon << endl;
      // Outputs: (1, 2)(3, 4)(5, 6)
      return os;
    } // std::ostream& operator<<

  }; // class polygon_element

  std::ostream& operator<< (std::ostream& os, polygon_element& p)
  { // May be needed for Boost.Test.
    // ptr_vector<poly_path_point> poly_points; // All the x, y coordinate pairs,
    for(ptr_vector<poly_path_point>::iterator i = p.poly_points.begin(); i != p.poly_points.end(); ++i)
    {
      os << (*i); //  x, y coordinates as " (1, 2)(3, 4)..."
      // using os << "(" << p.x << ", " << p.y  << ")" ;
    }
    // Usage:  polygon_element p(1, 2, 3, 4, 5, 6);
    // cout << p << endl;
    // Outputs: (1, 2)(3, 4)(5, 6)
    return os;
  } // std::ostream& operator<<

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
  friend std::ostream& operator<< (std::ostream&, polyline_element&);

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
      style_info_.write(o_str);
      o_str<<"/>";
      // Example: <polyline points=" 100,100 200,100 300,200 400,400"/>
    } // void write(std::ostream& o_str)

  }; // class polyline_element

  std::ostream& operator<< (std::ostream& os, polyline_element& p)
  { // May be needed for Boost.Test.
    // ptr_vector<poly_path_point> poly_points; // All the x, y coordinate pairs,
    for(ptr_vector<poly_path_point>::iterator i = p.poly_points.begin(); i != p.poly_points.end(); ++i)
    {
      os << (*i); //  x, y coordinates as " (1, 2)(3, 4)..."
      // using os << "(" << p.x << ", " << p.y  << ")" ;
    }
    // Usage:  polyline_element p(1, 2, 3, 4, 5, 6);
    // cout << p << endl;
    // Outputs: (1, 2)(3, 4)(5, 6)
    return os;
  } // std::ostream& operator<<


  // -------------------------------------------------------------------
  // g_element (group element) is the node element of our document tree.
  // 'g' element is a container element for grouping together <g /></g>
  // related graphics elements, for example:
  // <g id="background" fill="rgb(255,255,255)"><rect width="500" height="350"/></g>
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

    void write(std::ostream& os)
    {
      // Would be nice to avoid useless <g id="yMinorGrid"></g>
      // TODO but would this mean that useful style is lost?

      os << "<g"; // Do NOT need space if convention is to start following item with space.
      write_attributes(os); // id="background" (or clip_path)
      style_info_.write(os); // stroke="rgb(0,0,0)"
      os << ">" ;
      for(unsigned int i = 0; i < children.size(); ++i)
      {
        children[i].write(os); 
      }
      os << "</g>" << std::endl;
      // Example:
      // <g fill="rgb(255,255,255)" id="background"><rect x="0" y="0" width="500" height="350"/></g>
    } // void write(std::ostream& rhs)

    g_element& g(int i)
    { // i is index of children nodes.
      return *(static_cast<g_element*>(&children[i]));
    }

    // Returns a reference to the new child node just created.
    g_element& g()
    {
      children.push_back(new g_element());
      return *(static_cast<g_element*>(&children[children.size()-1]));
    }

    line_element& line(double x1, double y1, double x2, double y2)
    {
      children.push_back(new line_element(x1, y1, x2, y2));
      return *(static_cast<line_element*>(&children[children.size()-1])); 
    }

    rect_element& rect(double x1, double y1, double x2, double y2)
    {
      children.push_back(new rect_element(x1, y1, x2, y2));
      return *(static_cast<rect_element*>(&children[children.size()-1])); 
    }

    circle_element& circle(double x, double y, unsigned int radius = 5)
    {
      children.push_back(new circle_element(x, y, radius));
      return *(static_cast<circle_element*>(&children[children.size()-1])); 
    }

    ellipse_element& ellipse(double rx, double ry, double cx, double cy)
    {
      children.push_back(new ellipse_element(rx, ry, cx, cy));
      return *(static_cast<ellipse_element*>(&children[children.size()-1])); 
    }

    text_element& text(double x = 0., double y = 0.,
    const std::string& text = "",
    const text_style& style = no_style, // Use svg implementation's defaults.
    const align_style& align = left_align,
    const rotate_style& rotate = horizontal)
    {
      children.push_back(new text_element(x, y, text, style, align, rotate));
      return *(static_cast<text_element*>(&children[children.size()-1])); 
    }

    // push_back info about polygon shapes:
    // Polygon for shapes with many vertices.
    polygon_element& polygon(double x, double y, bool f = true)
    {
      children.push_back(new polygon_element(x, y, f));
      return *(static_cast<polygon_element*>(&children[children.size()-1])); 
    }

    //JVTODO: Replace with template version
    polygon_element& polygon(std::vector<poly_path_point>& v, bool f = true)
    { // push_back a complete many-sided polygon to the document.
      children.push_back(new polygon_element(v, f));
      return *(static_cast<polygon_element*>(&children[children.size()-1])); 
    }
    
    //JVTODO: Replace with template version
    polyline_element& polyline(std::vector<poly_path_point>& v)
    { // push_back a complete many-sided polygon to the document.
      children.push_back(new polyline_element(v));
      return *(static_cast<polyline_element*>(&children[children.size()-1])); 
    }

    polyline_element& polyline(double x, double y) // 1st point only, add others later with .P(x, y).
    {
      children.push_back(new polyline_element(x, y));
      return *(static_cast<polyline_element*>(&children[children.size()-1])); 
    }

    void push_back(svg_element* g)
    {
      children.push_back(g);
    }

    polygon_element& triangle(double x1, double y1, double x2, double y2, double x3, double y3, bool f)
    {
      children.push_back(new polygon_element(x1, y1, x2, y2, x3, y3, f));
      return *(static_cast<polygon_element*>(&(children[(unsigned int)(children.size()-1)])));
    }

    polygon_element& rhombus(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, bool f)
    {
      children.push_back(new polygon_element(x1, y1, x2, y2, x3, y3, x4, y4, f = true));
      return *(static_cast<polygon_element*>(&(children[(unsigned int)(children.size()-1)])));
    }

    polygon_element& pentagon(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5, bool f = true)
    { // push_back a complete pentagon to the document.
      children.push_back(new polygon_element(x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, f));
      return *(static_cast<polygon_element*>(&(children[(unsigned int)(children.size()-1)])));
    }

    polygon_element& hexagon(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5, double x6, double y6, bool f = true)
    { // push_back a complete 6-sided star to the document.
      children.push_back(new polygon_element(x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, f));
      return *(static_cast<polygon_element*>(&(children[(unsigned int)(children.size()-1)])));
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

    void clear()
    {
      children.clear();
    }


  }; // class g_element

} // namespace svg
} // namespace boost

#endif // BOOST_SVG_TAG_HPP
