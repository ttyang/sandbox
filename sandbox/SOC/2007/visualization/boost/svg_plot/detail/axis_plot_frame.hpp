 /*!  \file axis_plot_frame.hpp
  \brief SVG Plot functions common to 1D, 2D and Boxplots.
  \details Functions are derived from base class axis_plot_frame.
  \date Mar 2009
  \author Jacob Voytko and Paul A. Bristow
*/

// Copyright Jacob Voytko 2007
// Copyright Paul A. Bristow 2007, 2008, 2009, 2012

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SVG_AXIS_PLOT_FRAME_HPP
#define BOOST_SVG_AXIS_PLOT_FRAME_HPP

#include <boost/svg_plot/svg_style.hpp>
#include <boost/svg_plot/svg.hpp>
#include <boost/svg_plot/detail/svg_tag.hpp>
#include <boost/svg_plot/detail/numeric_limits_handling.hpp>
// using boost::math::fpclassify for
// boost::math::
// template <class T>bool isfinite (T);
// template <class T>bool isinf (T);
// template <class T> bool isnan (T);
#include <boost/svg_plot/detail/auto_axes.hpp>
#include <boost/quan/unc.hpp>
// using boost::svg::unc;
#include <boost/quan/meas.hpp>

#include <limits>
#include <string>
// using std::string;

#include <iostream> // for testing only.
 //using std::cerr;
 //using std::cout;
 //using std::endl;

#include <sstream>
//using std::ostream;
#include <utility>
// using std::pair

namespace boost
{
  namespace svg
  {
    // JV: G++ can't resolve names in these enums in axis_plot_frame
    //    when they are in svg_2d_plot.hpp

    //static const double text_plusminus = 2.; /*!< Number of standard deviations used for text_plusminus text display.\n
    //Nominal factor of 2 (strictly 1.96) corresponds to 95% confidence limit. */

    static const double sin45 = 0.707; //!< Use to calculate 'length' if axis value labels are sloping.
    static const double reducer = 0.9; //!< To make std_dev and degrees of freedom estimates a bit smaller font to help distinguish from value.

    // x_axis_position_ and y_axis_position_ use x_axis_intersect & y_axis_intersect
    enum x_axis_intersect
    { //! \enum x_axis_intersect If and how the X axes intersects Y axis.
      bottom = -1, //!< X-axis free below bottom of end of Y-axis (case of all Y definitely < 0).
      x_intersects_y = 0, //!< x_intersects_y when Y values include zero, so X intersects the Y axis.
      top = +1 //!< X-axis free above top of X-axis (case of all Y definitely > 0).
      };

    enum y_axis_intersect
    { //! \enum y_axis_intersect  If and how the Y axes intersects X axis.
      left = -1, //!< Y-axis free to left of end of X-axis (case of all X definitely < 0).
      y_intersects_x = 0, //!< y_intersects_x when X values include zero, so intersects the X axis.
      right = +1 //!< Y-axis free to left of end of X-axis (case of all X definitely > 0).
     };

    enum legend_places
    { //! \enum legend_places Placing of legend box, if requested by legend_on == true.
      nowhere = 0, //!< Placing of legend box not requested or not calculated yet.
      inside = -1,  //!< Default place for inside is top left of plot window, (exact location controlled by legend_top_left()).
      outside_left = 1, //!< Outside on the left of the graph.
      outside_right = +2, //!< Outside right (Default).
      outside_top = +3, //!< Outside at top.
      outside_bottom = +4, //!< Outside at bottom.
      somewhere = +5 //!< legend_top_left(x, y)
    };

    namespace detail
    { //! \namespace detail Holds base class axis_plot_frame for 1D, 2D and Box plots.
      template <class Derived>
      class axis_plot_frame
      { /*! \class boost::svg::detail::axis_plot_frame
         \brief Used as base class for 1D, 2D and Box plots.
         \details For example, svg_1d_plot, svg_2d_plot, svg_boxplot\n
         class svg_1d_plot : public detail::axis_plot_frame<svg_1d_plot>\n
         class svg_2d_plot : public detail::axis_plot_frame<svg_2d_plot>
        */
      protected:
        // We don't use the SVG coordinate transform because then text would
        // be flipped. Might use it to scale the image for resizes.

        // Protected (?) Member Functions Declarations (defined below):

         void transform_point(double &x, double &y); // Scale & shift both X & Y to graph Cartesian coordinates.
         void transform_x(double &x); // Scale & shift both X to graph Cartesian coordinates.
         void transform_y(double &y); // Scale & shift both Y to graph Cartesian coordinates.
         void draw_x_minor_tick(double j, path_element& tick_path, path_element& grid_path); // (& grid).
         void draw_x_major_tick(double i, path_element& tick_path, path_element& grid_path); // (& grid).
         void draw_x_axis();
         void draw_legend();
         void size_legend_box();
         void place_legend_box();
         void draw_title();
         void adjust_limits(double& x, double& y);
         void draw_x_axis_label();
         void draw_plot_point(double x, double y, g_element& g_ptr, const plot_point_style& sty);
         void draw_plot_point(double x, double y, g_element& g_ptr, plot_point_style& sty, unc<false> ux, unc<false> uy);
         void draw_plot_point_value(double x, double y, g_element& g_ptr, value_style& val_style, plot_point_style& point_style, Meas uvalue);
         void draw_plot_point_values(double x, double y, g_element& x_g_ptr, g_element& y_g_ptr, const value_style& x_sty, const value_style& y_sty, Meas uncx, Meas uncy);
         void draw_plot_point_values(double x, double y, g_element& x_g_ptr, g_element& y_g_ptr, const value_style& x_sty, const value_style& y_sty, Meas uncx, unc<false> uncy);

        // Clear functions.
         void clear_all(); // Calls all the other clear_* functions.
         void clear_legend();
         void clear_background();
         void clear_x_axis();
         void clear_y_axis();
         void clear_title();
         void clear_points();
         void clear_plot_background();
         void clear_grids();


  public: // Could be private but benefits unclear?

//        private:
          Derived& derived()
          { //! Uses Curiously Recurring Template Pattern to allow 1D and 2D to reuse common code.
            //! See http://en.wikipedia.org/wiki/Curiously_Recurring_Template_Pattern .
            return static_cast<Derived&>(*this);
          }
          const Derived& derived()const
          {  //! const version of derived()
            return static_cast<const Derived&>(*this);
          }
        public:
          // Set & get member function Declarations:
          // All set functions return derived() == *this to permit chaining,
          // for example: my_plot.background_color(red).background_border_color(blue)...

          // Shapes and glyphs can have (or may need) BOTH fill and stroke to be set.
          // Both are usually the same in this application.
          // If both are set, stroke is considered 'more important',
          // and so is returned by get functions.

          Derived& size(unsigned int x, unsigned int y); //!< Set SVG image size (SVG units, default pixels).
          std::pair<double, double> size(); //!< \return SVG image size, both horizontal width and vertical height (SVG units, default pixels).

          Derived& x_size(unsigned int i); //!< Set SVG image X-axis size (SVG units, default pixels).
          unsigned int x_size(); //!< \return SVG image X-axis size as horizontal width (SVG units, default pixels).
          unsigned int image_x_size(); //!< Obselete - deprecated use x_size()
          Derived& image_x_size(unsigned int i); //!< Obselete - deprecated - use x_size().

          unsigned int y_size(); //!< \return SVG image Y-axis size as horizontal width (SVG units, default pixels).
          Derived& y_size(unsigned int i); //!< Set SVG image Y-axis size (SVG units, default pixels).
          unsigned int image_y_size(); //!< Obselete - deprecated - use y_size()
          Derived& image_y_size(unsigned int i); //!< Obselete - deprecated - use y_size()

          svg_color background_color(); //!< \return  plot background color.
          Derived& background_color(const svg_color& col); //!< Set plot background color.
          Derived& background_border_color(const svg_color& col); //!< Set plot background border color.
          svg_color background_border_color(); //!< \return plot background border color.
          Derived& background_border_width(double w); //!< Set plot background border width.
          double background_border_width(); //!< \return plot background border width.
          Derived& description(const std::string d);
          //!< Writes description to the document for header as \verbatim <desc> My Description </desc>. \endverbatim
          const std::string& description(); //!< \return  description of the document for header as \verbatim <desc> My description </desc>. \endverbatim
          Derived& document_title(const std::string d); //!< Set document title to the document for header as \verbatim <title> My Title </title>. \endverbatim
          std::string document_title(); //!< \return  document title to the document for header as \verbatim <title> My Title </title>. \endverbatim
          Derived& copyright_holder(const std::string d);/*!< Writes copyright_holder metadata to the SVG document
            (for header as <!-- SVG Plot Copyright Paul A. Bristow 2007 --> )
            /and as metadata: \verbatim <meta name="copyright" content="Paul A. Bristow" /> \endverbatim
            */
          const std::string copyright_holder(); //!< \return SVG document copyright holder.
          Derived& copyright_date(const std::string d); //!< Writes copyright date to the SVG document.
            //! and as metadata: \verbatim <meta name="date" content="2007" /> \endverbatim
          const std::string copyright_date(); //!< \return SVG document copyright_date.
          Derived& license(
            std::string repro= "permits",
            std::string distrib = "permits",
            std::string attrib = "requires",
            std::string commercial = "permits",
            std::string derivative = "permits"); /*!< Set license conditions for reproduction, attribution, commercial use, and derivative works,
            usually "permits", "requires", or "prohibits", and set license_on == true.
          */
          Derived&  license_on(bool l); //!< Set if license conditions should be included in the SVG document.
          bool license_on(); //!< \return true if license conditions should be included in the SVG document.
          Derived& boost_license_on(bool l); //!< Set true if the Boost license conditions should be included in the SVG document.
          bool boost_license_on();  //!< \return  true if the Boost license conditions should be included in the SVG document.
          const std::string license_reproduction(); //!< \return  SVG document  reproduction license conditions, usually "permits", "requires", or "prohibits".
          const std::string license_distribution(); //!< \return  SVG document  distribution license conditions, usually "permits", "requires", or "prohibits".
          const std::string license_attribution(); //!< \return  SVG document  attribution license conditions, usually "permits", "requires", or "prohibits".
          const std::string license_commercialuse();  //!< \return  SVG document  commercial use license conditions, usually "permits", "requires", or "prohibits".
          Derived& coord_precision(int digits); /*!< Precision of SVG coordinates in decimal digits (default 3).
              3 decimal digits precision is sufficient for small images.
              4 or 5 decimal digits precision will give higher quality plots,
              especially for larger images, at the expense of larger .svg files,
              particularly if there are very many data points.
           */
          int coord_precision(); //!< \return  precision of SVG coordinates in decimal digits.
          Derived& x_value_precision(int digits); /*!< Precision of X tick label values in decimal digits (default 3).
              3 decimal digits precision is sufficient for small images.
              4 or 5 decimal digits precision will give more cluttered plots.
              If the range of labels is very small, then more digits will be essential.
            */
          int x_value_precision(); //!< \return  precision of X tick label values in decimal digits
          Derived& x_value_ioflags(std::ios_base::fmtflags flags); /*!< Set iostream std::ios::fmtflags for X value label (default decimal == 0X201).
              Mainly useful for changing to scientific, fixed or hexadecimal format.
              For example:
              \code
                 myplot.x_value_ioflags(std::ios::dec | std::ios::scientific)
              \endcode
            */
          std::ios_base::fmtflags x_value_ioflags(); //!< \return  stream std::ios::fmtflags for control of format of X value labels.
          Derived& x_labels_strip_e0s(bool cmd); //!< Set if to strip redundant zeros, signs and exponents, for example, reducing "1.2e+000" to "1.2"
            //! This markedly reduces visual clutter, and is the default.
          bool y_labels_strip_e0s(); //!< \return  if to strip redundant zeros, signs and exponents, for example, reducing "1.2e+000" to "1.2"
          Derived& title(const std::string title); /*!<
              Set a title for plot.
              The string may include Unicode for greek letter and symbols.
              For example a title that includes a greek omega and degree symbols:
              \code
                my_plot.title("Plot of &#x3A9; function (&#x00B0;C)");
              \endcode

              Unicode symbols are at http://unicode.org/charts/symbols.html.
            */
          const std::string title(); //!< \return  a title for plot, whose string may include Unicode for greek letter and symbols.
          Derived& title_font_size(unsigned int i); //!< Sets the font size for the title (svg units, default pixels).
          unsigned int title_font_size(); //!< \return  the font size for the title (svg units, default pixels).
          Derived& title_font_family(const std::string& family); //!< Set the font family for the title (for example: .title_font_family("Lucida Sans Unicode");
          const std::string& title_font_family(); //!< \return  the font family for the title.
          Derived& title_font_style(const std::string& style);  //!< Set the font style for the title (default normal).
          const std::string& title_font_style(); //!< \return  the font style for the title (default normal).
          Derived& title_font_weight(const std::string& weight); //!< Set the font weight for the title (default normal).
          const std::string& title_font_weight(); //!< \return  the font weight for the title.
          Derived& title_font_stretch(const std::string& stretch); //!< Set the font stretch for the title (default normal), wider or narrow.
          const std::string& title_font_stretch(); //!< \return  the font stretch for the title.
          Derived& title_font_decoration(const std::string& decoration); //!< Set the font decoration for the title (default normal, or underline, overline or strike-thru).
          const std::string& title_font_decoration(); //!< \return  the font decoration for the title (default normal, or underline, overline or strike-thru).
          Derived& title_font_rotation(rotate_style rotate); //!< Set the rotation for the title font (degrees, 0 to 360 in steps using rotate_style, for example horizontal, uphill...
          int title_font_rotation(); //!< \return  the rotation for the title font (degrees).
          Derived& title_font_alignment(align_style alignment);  //!< Set the alignment for the title.
          align_style title_font_alignment(); //!< \return  the alignment for the title.
          // Legend.
          Derived& legend_width(double width); //!< Set the width for the legend box.
          double legend_width(); //!< \return  the width for the legend box.
          Derived& legend_title(const std::string title); //!< Set the title for the legend.
          const std::string legend_title(); //!< \return  the title for the legend.
          Derived& legend_font_weight(const std::string& weight); //!< Set the font weight for the legend title.
          const std::string& legend_font_weight(); //!< \return  the font weight for the legend title.
          Derived& legend_font_family(const std::string& family); //!< Set the font family for the legend title.
          const std::string& legend_font_family(); //!< \return  the font family for the legend title.
          Derived& legend_title_font_size(unsigned int size); //!< \return  the font family for the legend title.
          unsigned int legend_title_font_size(); //!< \return  the font size for the legend title (svg units, default pixels).
          Derived& legend_top_left(double x, double y); //!< Set position of top left of legend box (svg coordinates, default pixels).
            //! (Bottom right is controlled by contents, so the user cannot set it).
          const std::pair<double, double> legend_top_left(); //!< \return  svg coordinate (default pixels) of top left of legend box.
          const std::pair<double, double> legend_bottom_right(); //!< \return  svg coordinate (default pixels) of bottom right of legend box.
          Derived& legend_lines(bool is); /*!< Set true if legend should include samples of the lines joining data points.
            This allows different series of data points to be distinguished by different color and/or width.
            This is especially useful to show plots of different functions and/or different parameters in different colors.
            */
          bool legend_lines();//!< \return  true if legend should include samples of the lines joining data points.
          Derived& legend_on(bool cmd); //!< Set true if a legend is wanted.
          bool legend_on(); //!< \return  true if a legend is wanted.
          Derived& x_axis_vertical(double fraction); //! Set vertical position of X-axis for 1D as fraction of plot window.
          bool x_axis_vertical(); //! \return vertical position of X-axis for 1D as fraction of plot window.
          Derived& legend_place(legend_places l); //!< Set the position of the legend, \see  boost::svg::legend_places
          legend_places legend_place(); //!< \return  the position of the legend, \see  boost::svg::legend_places
          bool legend_outside(); //!< \return  if the legend should be outside the plot area.
          Derived& legend_header_font_size(int size); //!< Set legend header font size (svg units, default pixels).
          int legend_header_font_size(); //!< \return  legend header font size (svg units, default pixels).
          Derived& plot_window_on(bool cmd); //!< Set true if a plot window is wanted (or false if the whole image is to be used).
          bool plot_window_on();//!< \return  true if a plot window is wanted (or false if the whole image is to be used).
          Derived& plot_border_color(const svg_color& col); //!< Set the color for the plot window background.
          svg_color plot_border_color(); //!< \return  the color for the plot window background.
          Derived& plot_border_width(double w); //!< Set the margin around the plot window border (svg units, default pixels).
            //! \details This prevents the plot window getting too close to other elements of the plot.
          double plot_border_width(); //!< \return  the width for the plot window border (svg units, default pixels).
          Derived& image_border_margin(double w); //!< Set the margin around the plot window border (svg units, default pixels).
            //! \details This prevents the plot window getting too close to other elements of the plot.
          double image_border_margin(); //!< \return  the margin around the plot window border (svg units, default pixels).
          Derived& image_border_width(double w); //!< Set the svg image border width (svg units, default pixels).
          double image_border_width(); //!< \return  the svg image border width (svg units, default pixels).
          Derived& plot_window_x(double min_x, double max_x);//!< Set the minimum and maximum (cartesian data units) for the plot window X axis.
            //! This is normally calculated from other plot values.
          Derived& plot_window_y(double min_y, double max_y);//!< Set the minimum and maximum (cartesian data units) for the plot window Y axis.
            //! This is normally calculated from other plot values.
          std::pair<double, double> plot_window_x(); //!< \return  both the left and right (X axis) of the plot window.
          double plot_window_x_left(); //!< \return  left of the plot window.
          double plot_window_x_right(); //!< \return  right of the plot window.
          double plot_window_y_top(); //!< \return  top of the plot window.
          double plot_window_y_bottom(); //!< \return  top of the plot window.
          std::pair<double, double> plot_window_y(); //!< \return  both the top and bottom (Y axis) of the plot window.
          double x_minor_interval(); //!< \return  interval between X minor ticks.
          double y_minor_interval(); //!< \return  interval between Y minor ticks.
          Derived& x_ticks_up_on(bool cmd); //!< Set true if X major ticks should mark upwards.
          bool x_ticks_up_on(); //!< \return  true if X major ticks should mark upwards.
          Derived& x_ticks_down_on(bool cmd); //!< Set true if Y major ticks should mark upwards.
          bool x_ticks_down_on(); //!< \return  true if Y major ticks should mark upwards.
          Derived& x_label_on(bool cmd); //!< \return  true if X major ticks should mark downwards.
          bool x_label_on(); /*!< Set true if want to show X-axis label text.
            Also switched on by setting label text.
            (on the assumption that if label text is set, display is also wanted,
            but can be switched off if  \b not required).
           */
          Derived& x_label_font_size(unsigned int i); //!< Set X axis label font size (svg units, default pixels).
          unsigned int x_label_font_size(); //!< \return  X axis label font size (svg units, default pixels).
          Derived& x_value_font_size(unsigned int i); //!< Set X tick value label font size (svg units, default pixels).
          unsigned int x_value_font_size(); //!< \return  X tick value label font size (svg units, default pixels).
          Derived& x_label_font_family(const std::string& family); /*!< Set X tick value label font family.
           Available fonts depend on the program rendering the SVG XML, usually a browser.
          The default font (usually "verdana") is used if a render program does not provide the font specified.
          These are probably usable:
          \code
            "arial", "impact", "courier", "lucida console",  "Lucida sans unicode", "verdana", "calibri", "century",
            "lucida calligraphy", "tahoma", "vivaldi", "informal roman", "lucida handwriting", "lucida bright", "helvetica"
          \endcode
          */
          const std::string& x_label_font_family(); //!< \return  X tick value label font family.
          Derived& x_axis_label_color(const svg_color& col); //!< Set X axis label color, for example, red.
          svg_color x_axis_label_color(); //!< \return  X axis label color.
          // X-axis ticks values label style.
          Derived& x_ticks_values_color(const svg_color& col);  //!< Set X axis tick value label color.
          svg_color x_ticks_values_color(); //!< \return  X-axis ticks value label color.
          Derived& x_ticks_values_precision(int p); //!< Set iostream decimal digits precision of data point X values near data points markers.
          int x_ticks_values_precision(); //!< \return  iostream decimal digits precision of data point X values near data points markers.
          Derived& x_ticks_values_ioflags(std::ios_base::fmtflags f); //!< Set iostream format flags of data point X values near data points markers.
          std::ios_base::fmtflags x_ticks_values_ioflags(); //!< \return  iostream format flags of data point X values near data points markers.

          Derived& x_ticks_values_font_family(const std::string& family); /*!< Set X ticks value label font family.
            Available fonts depend on the program rendering the SVG XML, usually a browser.
            The default font (usually "verdana") is used if a render program does not provide the font specified.
             These are probably usable:
             \code
 "arial", "impact", "courier", "lucida console",  "Lucida sans unicode", "verdana", "calibri", "century",
 "lucida calligraphy", "tahoma", "vivaldi", "informal roman", "lucida handwriting", "lucida bright", "helvetica"
             \endcode
           */
          const std::string& x_ticks_values_font_family(); //!< \return  X ticks value label font family.
          Derived& x_ticks_values_font_size(unsigned int i); //!< Set X ticks value label font size (svg units, default pixels).
          unsigned int x_ticks_values_font_size(); //!< Set X ticks value label font size (svg units, default pixels).

          Derived& x_ticks_on_window_or_axis(int side);
            /*!<  Set position of X ticks on window or axis.
              \param side -1 X ticks on bottom of plot window,
                       0 X ticks on X-axis horizontal line,
                       +1 X ticks top of plot window.
            */
          int x_ticks_on_window_or_axis(); //!< \return true if X axis ticks wanted on the window (rather than on axis).\n
            //!< -1 bottom of plot window, 0 on horiztonal X axis , +1 top of plot window.
          Derived& x_label_units_on(bool cmd); //!< Set true if want X axis label to include units (as well as label like "length").
            //!< \see x_label_units which also sets true.
          bool x_label_units_on(); //!< Set true if want X axis label to include units (as well as label like "length").
          Derived& x_major_labels_side(int side); /*!< Position of labels for X major ticks on horizontal X axis line.
               \param side > 0 X tick value labels to left of Y axis line (default), 0 (false) no major X tick value labels on Y axis, 0 X tick labels to right of Y axis line.
            */
          int x_major_labels_side(); //!< \return the side for X ticks major value labels.
          Derived& x_major_label_rotation(rotate_style rot); /*!< Set rotation for X ticks major value labels. (Default horizontal).
               \see rotate_style
            */
          rotate_style x_major_label_rotation(); /*!< \return rotation for X ticks major value labels.
                \see rotate_style
             */
          Derived& title_on(bool cmd); //!< If set true, show a title for the plot. Note: is set true by setting a title.
          bool title_on(); //!< \return true if will show a title for the plot.
          Derived& x_major_grid_on(bool is); //!< If set true, will include a major X-axis grid.
          bool x_major_grid_on();  //!< \return true if will include a major X-axis grid.
          Derived& x_minor_grid_on(bool is); //!< If set true, will include a minor X-axis grid.
          bool x_minor_grid_on();   //!< \return true if will include a major X-axis grid.
          Derived& axes_on(bool is); //!< If set true, draw \b both x and y axes (note plural axes).
          bool axes_on(); //!< \return true if \b both x and y axis on.
          Derived& x_axis_on(bool is); //!< If set true, draw a horizontal X-axis line.
          bool x_axis_on(); //!< \return true if will draw a horizontal X-axis line.
          Derived& y_axis_on(bool is); //!< If set true, draw a vertical Y-axis line.
          bool y_axis_on(); //!< \return true if will draw a horizontal X-axis line.
          Derived& title_color(const svg_color& col); //!< Set the color of any title of the plot.
          svg_color title_color(); //!< \return the color of any title of the plot.
          Derived& legend_color(const svg_color& col); //!< Set the color of the title of the legend.
          svg_color legend_color(); //!< \return  the color of the title of the legend.
          Derived& legend_background_color(const svg_color& col); //!< Set the background fill color of the legend box.
          svg_color legend_background_color(); //!< \return  the background fill color of the legend box.
          bool legend_box_fill_on(); //!< \return true if legend box has a background fill color.
          Derived& legend_border_color(const svg_color& col); //!< Set the border stroke color of the legend box.
          svg_color legend_border_color(); //!< \return  the border stroke color of the legend box.
          Derived& plot_background_color(const svg_color& col); //!< Set the fill color of the plot window background.
          svg_color plot_background_color(); //!< \return  the fill color of the plot window background.
          const std::string x_axis_position(); //!< \return  the position (or intersection with Y-axis) of the X-axis.
          Derived& x_axis_color(const svg_color& col); //!< Set the color of the X-axis line.
          svg_color x_axis_color(); //!< \return  the color of the X-axis line.
          Derived& y_axis_color(const svg_color& col); //!< Set the color of the Y-axis line.
          svg_color y_axis_color(); //!< \return  the color of the Y-axis line.
          Derived& x_label_color(const svg_color& col); //!< \return  the color of the Y-axis line.
          svg_color x_label_color(); //!< \return  the color of X-axis label (including any units).
          Derived& x_label_width(double width); //!< Set the width (boldness) of X-axis label (including any units).
            //! (not recommended until browsers implement better).
          double x_label_width(); //!< \return  the width (boldness) of X-axis label (including any units).
          Derived& y_label_color(const svg_color& col); //!< Set the color of Y-axis label (including any units).
          svg_color y_label_color(); //!< \return  the color of Y-axis label (including any units).
          Derived& x_major_tick_color(const svg_color& col); //!< Set the color of X-axis major ticks.
          svg_color x_major_tick_color(); //!< \return  the color of X-axis major ticks.
          Derived& x_minor_tick_color(const svg_color& col); //!< Set the color of X-axis minor ticks.
          svg_color x_minor_tick_color(); //!< \return  the color of X-axis minor ticks.
          Derived& x_major_grid_color(const svg_color& col); //!< Set the color of X-axis major grid lines.
          svg_color x_major_grid_color(); //!< Set the color of X-axis major grid lines.
          Derived& x_major_grid_width(double w); //!< Set the width of X-axis major grid lines.
          double x_major_grid_width(); //!< \return  the color of X-axis major grid lines.
          Derived& x_minor_grid_color(const svg_color& col); //!< Set the color of X-axis minor grid lines.
          svg_color x_minor_grid_color(); //!< \return  the color of X-axis minor grid lines.
          Derived& x_minor_grid_width(double w); //!< Set the width of X-axis minor grid lines.
          double x_minor_grid_width(); //!< \return  the width of X-axis minor grid lines.
          Derived& x_axis_width(double width); //!< Set the width of X-axis lines.
          double x_axis_width(); //!< \return  the width of X-axis lines.
          Derived& data_lines_width(double width); //!< Set the width of lines joining data points.
          double data_lines_width(); //!< \return  the width of lines joining data points.
          Derived& x_label(const std::string& str); //!< Set the text to label the X-axis (and set x_label_on(true)).
          std::string x_label(); //!< \return  the text to label the X-axis.
          Derived& x_label_units(const std::string& str); //!< Set the text to add units to the X-axis label.
          std::string x_label_units(); //!< \return  the text to add units to the X-axis label.
            //!< The label will only be shown if  x_label_on() == true.
          Derived& y_label(const std::string& str); //!< Set the text for the Y-axis label (and set y_label_on(true)).
          std::string y_label(); //!< \return  the text for the Y-axis label.
            //!< The label will only be shown if  y_label_on() == true.
          Derived& y_label_units(const std::string& str); //!< Set the text to add units to the Y-axis label.
          std::string y_label_units(); //!< \return  the text to add units to the X-axis label.
          Derived& x_values_on(bool b); //!< Set true to show data point values near data points markers.
          bool x_values_on(); //!< \return true if to show data point values near data points markers.
          Derived& x_values_font_size(unsigned int i); //!< Set font size of data point X values near data points markers.
          unsigned int x_values_font_size(); //!< \return  font size of data point X values near data points markers.
          Derived& x_values_font_family(const std::string& family); //!< Set font family of data point X values near data points markers.
          const std::string& x_values_font_family(); //!< \return font family of data point X values near data points markers.
          Derived& x_major_interval(double inter); //!< Set the interval between X-axis major ticks.
          double x_major_interval();  //!< \return  the interval between X-axis major ticks.

          Derived& x_values_color(const svg_color& col); //!< Set the color of data point X values near data points markers.
          svg_color x_values_color(); //!< \return  the color of data point X values near data points markers.
          Derived& x_values_rotation(rotate_style rotate); //!< \return  the rotation (rotate_style) of data point X values near data points markers.
          int x_values_rotation(); //!< Set the rotation (rotate_style) of data point X values near data points markers.
          Derived& x_values_precision(int p); //!< Set iostream decimal digits precision of data point X values near data points markers.
          int x_values_precision(); //!< \return  iostream decimal digits precision of data point X values near data points markers.
          Derived& x_values_ioflags(std::ios_base::fmtflags f); //!< Set iostream format flags of data point X values near data points markers.
          std::ios_base::fmtflags x_values_ioflags(); //!< \return  iostream format flags of data point X values near data points markers.
          Derived& x_plusminus_on(bool b); //!< Set if to append std_dev estimate to data point X values near data points markers.
          bool x_plusminus_on(); //!< \return true if to append std_dev estimate to data point X values near data points markers.
          Derived& x_plusminus_color(const svg_color& col); //!< Set the color of X std_dev of value, for example, the color of 0.02 in "1.23 +-0.02 (9)".
          svg_color x_plusminus_color(); //!< \return the color of X std_dev of value, for example, the color of 0.02 in "1.23 +-0.02 (9)".

          Derived& x_addlimits_on(bool b); //!< Set if to append confidence limits to data point X values near data points markers.
          bool x_addlimits_on(); //!< \return true if to append confidence limits estimate to data point X values near data points markers.
          Derived& x_addlimits_color(const svg_color& col); //!< Set the color of X confidence limits of value, for example, the color  in "<1.23, 1.45>".
          svg_color x_addlimits_color(); //!< \return the color of X confidence limits of value, for example, the color of  "<1.23, 1.45>)".


          Derived& x_df_on(bool b); //!< Set true if to append a degrees of freedom estimate to data point X values near data points markers.
          bool x_df_on(); //!< \return true if to append a degrees of freedom estimate to data point X values near data points markers.
          Derived& x_df_color(const svg_color& col); //!< Set the color of X degrees of freedom, for example, the color of 9 in "1.23 +-0.02 (9)".
          svg_color x_df_color(); //!< \return the color of X degrees of freedom, for example, the color of 9 in "1.23 +-0.02 (9)".
          Derived& x_id_on(bool b); //!< Set true if to append append an ID or name to data point X values near data points markers.
          bool x_id_on(); //!< \return true if to append an ID or name to data point X values near data points markers.
          Derived& x_id_color(const svg_color& col); //!< Set the color of X id or name, for example, the color of text in "my_id".
          svg_color x_id_color(); //!< \return the color of X X id or name, for example, the color of text in "my_id".
          Derived& x_datetime_on(bool b); //!< Set true if to append date time to data point X values near data points markers.
          bool x_datetime_on(); //!< \return true if to append an date time to data point X values near data points markers.
          Derived& x_datetime_color(const svg_color& col); //!< Set the color of X  date time , for example, the color of text in "".
          svg_color x_datetime_color(); //!< \return the color of X date time, for example, the color of text in "".
          Derived& x_order_on(bool b); //!< Set true if to append append an order # to data point X values near data points markers.
          bool x_order_on(); //!< \return true if to append an order # to data point X values near data points markers.
          Derived& x_order_color(const svg_color& col); //!< Set the color of X order #, for example, the color of #42.
          svg_color x_order_color(); //!< \return the color of X order #, for example, the color of #42.
          Derived& x_decor(const std::string& pre, const std::string& sep = "", const std::string& suf = "");
          /*!< Set prefix, separator and suffix together for x_ values.
            Note if you want a space, you must use a Unicode space "&#x00A0;",
            for example, ",&#x00A0;" rather than ASCII space", ".
            If 1st char in separator == \n, then Y values and info will be on a newline below.
          */
          const std::string x_suffix(); //!< \return the suffix (only used if separator != "")
          const std::string x_separator(); //!< \return the separator, perhaps including Unicode.
          const std::string x_prefix(); //!< \return the prefix.

          Derived& x_major_tick_length(double length); //!< Set length of X major ticks (SVG units, default pixels).
          double x_major_tick_length(); //!< Set length of X major ticks (SVG units, default pixels).
          Derived& x_major_tick_width(double width); //!< Set width of X major ticks (SVG units, default pixels).
          double x_major_tick_width(); //!< Set width of X major ticks (SVG units, default pixels).
          Derived& x_minor_tick_length(double length); //!< Set length of X minor ticks (SVG units, default pixels).
          double x_minor_tick_length(); //!< \return  length of X minor ticks (SVG units, default pixels).
          Derived& x_minor_tick_width(double width); //!< Set width of X minor ticks (SVG units, default pixels).
          double x_minor_tick_width(); //!< \return  width of X minor ticks (SVG units, default pixels).
          Derived& x_major_tick(double d); //!< Set interval (Cartesian units) between major ticks.
          double x_major_tick(); //!< \return  interval (Cartesian units) between major ticks.
          Derived& x_minor_interval(double interval); //!< Set interval between X-axis minor ticks.
          Derived& x_num_minor_ticks(unsigned int num); //!< Set number of X-axis minor ticks between major ticks.
          unsigned int x_num_minor_ticks(); //!< \return  number of X-axis minor ticks between major ticks.
          Derived& x_range(double min_x, double max_x); /*!< Set the range of values on the X-axis.
            The minimum and maximum values must be finite and not too near
            to the minima or maxima that can be represented by floating point double,
            std::numeric_limits<double>::min() or std::numeric_limits<double>::max(),
            and the range must not be too small.
            */
          std::pair<double, double> x_range(); //!< \return  the range of values on the X-axis.
          Derived& x_min(double min_x); //!< Set the minimum value on the X-axis.
          double x_min(); //!< \return  the minimum value on the X-axis.
          Derived& x_max(double x); //!< Set the maximum value on the X-axis.
          double x_max(); //!< \return  the maximum value on the X-axis.

          // autoscale set & get parameters,
          // Note: all these *MUST* preceed x_autoscale(data) call.
          Derived& autoscale_plusminus(double); //!< Set how many std_dev or standard deviation to allow for ellipse when autoscaling.
          double autoscale_plusminus(); //!< \return  how many std_dev or standard deviations to allow for ellipse when autoscaling.

          Derived& confidence(double); //!< Set confidence alpha for display of confidence intervals (default 0.05 for 95%).
          double confidence(); //!< \return Confidence alpha for display of confidence intervals (default 0.05 for 95%).

          Derived& autoscale_check_limits(bool b); //!< Set to check that values used for autoscale are within limits.
            //! Default is true, but can switch off checks for speed if can be sure all are 'inside limits'.
          bool autoscale_check_limits();//!< \return True if to check that values used for autoscale are within limits.
          bool x_autoscale();  //!< \return true if to use autoscale value for X-axis.
          Derived& x_autoscale(bool b); //!< Set true if to use autoscale values for X-axis.
          bool autoscale(); //!< \return true if to use autoscale values for X-axis.
          Derived& autoscale(bool b);  //!< Set true if to use autoscale values for X-axis.
          Derived& x_autoscale(std::pair<double, double> p); //!< autoscale X axis using a pair of doubles.
          template <class T> //!< \tparam T an STL container: array, vector ...
          Derived& x_autoscale(const T& container); //!< autoscale X axis using the whole data series.
          template <class T> //!< \tparam T an STL container: array, vector ...
          Derived& x_autoscale(const T& begin, const T& end); //!< Data series using iterators.
          Derived& x_with_zero(bool b); //!< Set X-axis autoscale to include zero (default = false).
          bool x_with_zero(); //!< \return  true if X-axis autoscale to include zero (default = false).
          Derived& x_min_ticks(int min_ticks); //!< Set X-axis autoscale to include at least minimum number of ticks (default = 6).
          int x_min_ticks(); //!< \return  X-axis autoscale minimum number of ticks.
          Derived& x_steps(int steps); /*!< Set autoscale to set ticks in steps multiples of:\n
             2,4,6,8,10, if 2\n
             or 1,5,10 if 5\n
             or 2,5,10 if 10.\n
             default = 0 (none).
             \note: Must \b preceed x_autoscale(data) call).
             */
          int x_steps(); //!< \return  autoscale to set ticks in steps.
          Derived& x_tight(double tight); //!< Set tolerance to autoscale to permit data points slightly outside both end ticks.
          double x_tight(); //!< \return  tolerance given to autoscale to permit data points slightly outside both end ticks.
          // Get results of autoscaling.
          double x_auto_min_value(); //!< \return  the X-axis minimum value computed by autoscale.
          double x_auto_max_value(); //!< \return  the X-axis maximum value computed by autoscale.
          double x_auto_tick_interval(); //!< \return  the X-axis major tick interval computed by autoscale.
          int x_auto_ticks(); //!< \return  the X-axis number of major ticks computed by autoscale.
          Derived& limit_color(const svg_color&); //!< Set the color for 'at limit' point stroke color.
          svg_color limit_color(); //!< \return  the color for the 'at limit' point stroke color.
          Derived& limit_fill_color(const svg_color&); //!< Set the color for 'at limit' point fill color.
          svg_color limit_fill_color(); //!< \return  the color for the 'at limit' point fill color.
          Derived& draw_note
            (double x, double y, std::string note, rotate_style rot = horizontal, align_style al = center_align, const svg_color& = black, text_style& tsty = no_style);
           /*!< \brief Annotate plot with a  text string (perhaps including Unicode), putting note at SVG Coordinates X, Y.
            \details Defaults color black, rotation horizontal and align = center_align
            Using center_align is recommended as it will ensure that will center correctly
            (even if original string is made much longer because it contains Unicode,
            for example Greek or math symbols, taking about 6 characters per symbol)
            because the render engine does the centering.
          */
          Derived& draw_line(double x1, double y1, double x2, double y2, const svg_color& col = black);
          /*!< Annotate plot with a line from SVG Coordinates X1, Y1 to X2, Y2. (Default color black).
              Note \b NOT the data values. See draw_plot_line if want to use user coordinates.
            */
          Derived& draw_plot_line(double x1, double y1, double x2, double y2, const svg_color& col = black);
          /*!< \brief Annotate plot with a line from user's Cartesian Coordinates X1, Y1 to X2, Y2.
              \details For example, -10, -10, +10, +10, Default color black.
            */
          Derived& draw_plot_curve(double x1, double y1, double x2, double y2, double x3, double y3,const svg_color& col = black);
          /*!< \brief Annotate plot with a line from user's Cartesian Coordinates X1, Y1 via X2, Y2 to X3, Y3.
              \details For example, -10, -10, +10, +10, Default color black.
          */

          Derived& one_sd_color(const svg_color&); //!< Set the color for the one standard deviation (~67% confidence) ellipse fill.
          svg_color one_sd_color(); //!< \return Color for the one standard deviation (~67% confidence) ellipse fill.
          Derived& two_sd_color(const svg_color&); //!< Set the color for two standard deviation (~95% confidence) ellipse fill.
          svg_color two_sd_color(); //!< \return Color for two standard deviation (~95% confidence) ellipse fill.
          Derived& three_sd_color(const svg_color&); //!< Set the color for three standard deviation (~99% confidence) ellipse fill.
          svg_color three_sd_color(); //!< \return Color for three standard deviation (~99% confidence) ellipse fill.

          // Image info (& identical const version).

          //svg& get_svg()
          //{
          //  derived()._update_image();
          //  return derived().image_;
          //}

          //const svg& get_svg() const
          //{
          //  derived()._update_image();
          //  return derived().image_;
          //}
        }; // template <class Derived> class axis_plot_frame

        // class axis_plot_frame Member function Definitions (for .ipp file):


//          template <typename Derived>/*! \tparam Derived plot class, svg_1d_plot or svg_2d_plot or svg_boxplot. */
//          template <typename T> /*! \tparam T an STL container: array, vector, list, map ...  */
//          Derived& axis_plot_frame<Derived>::x_autoscale(const T& begin, const T& end);
//
//          template <class Derived>
//          template <class T> // T an STL container: array, vector...
//          Derived& axis_plot_frame<Derived>::x_autoscale(const T& container); // Use whole 1D data series.
//
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::size(unsigned int x, unsigned int y);
//
//          template <class Derived>
//          std::pair<double, double> axis_plot_frame<Derived>::size();
//          template <class Derived>
//          unsigned int axis_plot_frame<Derived>::image_x_size(); //!< Obselete - deprecated.
//
//           template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_size(unsigned int i);
//
//          template <class Derived>
//          unsigned int axis_plot_frame<Derived>::x_size();
//
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::image_x_size(unsigned int i); //!< Obselete - deprecated.
//
//          template <class Derived>
//          unsigned int axis_plot_frame<Derived>::image_y_size(); //!< Obselete - deprecated.
//
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::image_y_size(unsigned int i); //!< Obselete - deprecated.
//
//          template <class Derived>
//          unsigned int axis_plot_frame<Derived>::y_size();
//
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::y_size(unsigned int i);
//                    template <class Derived>
//          svg_color axis_plot_frame<Derived>::background_color();
//
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::background_color(const svg_color& col);
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::background_border_color(const svg_color& col);
//          template <class Derived>
//          svg_color axis_plot_frame<Derived>::background_border_color();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::background_border_width(double w);
//          template <class Derived>
//          double axis_plot_frame<Derived>::background_border_width();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::description(const std::string d);
//
//          template <class Derived>
//          const std::string& axis_plot_frame<Derived>::description();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::document_title(const std::string d);
//          template <class Derived>
//          std::string axis_plot_frame<Derived>::document_title();
//
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::copyright_holder(const std::string d);
//
//          template <class Derived>
//          const std::string axis_plot_frame<Derived>::copyright_holder();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::copyright_date(const std::string d);
//          template <class Derived>
//          const std::string axis_plot_frame<Derived>::copyright_date();
//
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::license(std::string repro,
//            std::string distrib,
//            std::string attrib,
//            std::string commercial,
//            std::string derivative);
//
//          template <class Derived>
//          bool axis_plot_frame<Derived>::license_on();
//          template <class Derived>
//          Derived&  axis_plot_frame<Derived>::license_on(bool l);
//
//          template <class Derived>
//          bool axis_plot_frame<Derived>::boost_license_on();
//
//          template <class Derived>
//          const std::string axis_plot_frame<Derived>::license_reproduction();
//          template <class Derived>
//          const std::string axis_plot_frame<Derived>::license_distribution();
//          template <class Derived>
//          const std::string axis_plot_frame<Derived>::license_attribution();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::coord_precision(int digits);
//          template <class Derived>
//          int axis_plot_frame<Derived>::coord_precision();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_value_precision(int digits);
//          template <class Derived>
//          int axis_plot_frame<Derived>::x_value_precision();
//
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_value_ioflags(std::ios_base::fmtflags flags);
//          template <class Derived>
//          std::ios_base::fmtflags axis_plot_frame<Derived>::x_value_ioflags();
//
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_labels_strip_e0s(bool cmd);
//
//          template <class Derived>
//          bool axis_plot_frame<Derived>::y_labels_strip_e0s();
//
//          template <class Derived>
//          const std::string axis_plot_frame<Derived>::title();
//
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::title_font_size(unsigned int i);
//
//          template <class Derived>
//          unsigned int axis_plot_frame<Derived>::title_font_size();
//
//
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::title_font_family(const std::string& family);
//
//          template <class Derived>
//          const std::string& axis_plot_frame<Derived>::title_font_family();
//
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::title_font_style(const std::string& style);
//          template <class Derived>
//          const std::string& axis_plot_frame<Derived>::title_font_style();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::title_font_weight(const std::string& weight);
//          template <class Derived>
//          const std::string& axis_plot_frame<Derived>::title_font_weight();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::title_font_stretch(const std::string& stretch);
//          template <class Derived>
//          const std::string& axis_plot_frame<Derived>::title_font_stretch();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::title_font_decoration(const std::string& decoration);
//          template <class Derived>
//          const std::string& axis_plot_frame<Derived>::title_font_decoration();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::title_font_rotation(rotate_style rotate);
//          template <class Derived>
//          int axis_plot_frame<Derived>::title_font_rotation();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::title_font_alignment(align_style alignment);
//          template <class Derived>
//          align_style axis_plot_frame<Derived>::title_font_alignment();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::legend_width(double width);
//          template <class Derived>
//          double axis_plot_frame<Derived>::legend_width();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::legend_title(const std::string title);
//          template <class Derived>
//          const std::string axis_plot_frame<Derived>::legend_title();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::legend_font_weight(const std::string& weight);
//          template <class Derived>
//          const std::string& axis_plot_frame<Derived>::legend_font_weight();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::legend_font_family(const std::string& family);
//          template <class Derived>
//          const std::string& axis_plot_frame<Derived>::legend_font_family();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::legend_title_font_size(unsigned int size);
//          template <class Derived>
//          unsigned int axis_plot_frame<Derived>::legend_title_font_size();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::legend_top_left(double x, double y);
//          template <class Derived>
//          const std::pair<double, double> axis_plot_frame<Derived>::legend_top_left();
//          template <class Derived>
//          const std::pair<double, double> axis_plot_frame<Derived>::legend_bottom_right();
//
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::legend_lines(bool is);
//          template <class Derived>
//          bool axis_plot_frame<Derived>::legend_lines();
//
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::legend_on(bool cmd);
//          template <class Derived>
//          bool axis_plot_frame<Derived>::legend_on();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_axis_vertical(double fraction);
//
//          template <class Derived>
//          bool axis_plot_frame<Derived>::x_axis_vertical();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::legend_place(legend_places l);
//          template <class Derived>
//          legend_places axis_plot_frame<Derived>::legend_place();
//          template <class Derived>
//          bool axis_plot_frame<Derived>::legend_outside();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::legend_header_font_size(int size);
//          template <class Derived>
//          int axis_plot_frame<Derived>::legend_header_font_size();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::plot_window_on(bool cmd);
//          template <class Derived>
//          bool axis_plot_frame<Derived>::plot_window_on();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::plot_border_color(const svg_color& col);
//          template <class Derived>
//          double axis_plot_frame<Derived>::plot_border_width();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::plot_border_width(double w);
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::image_border_margin(double w);
//           template <class Derived>
//          double axis_plot_frame<Derived>::image_border_margin();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::image_border_width(double w);
//          template <class Derived>
//          double axis_plot_frame<Derived>::image_border_width();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::plot_window_x(double min_x, double max_x);
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::plot_window_y(double min_y, double max_y);
//
//          template <class Derived>
//          double axis_plot_frame<Derived>::plot_window_x_left();
//
//          template <class Derived>
//          double axis_plot_frame<Derived>::plot_window_x_right();
//          template <class Derived>
//          double axis_plot_frame<Derived>::plot_window_y_top();
//          template <class Derived>
//          double axis_plot_frame<Derived>::plot_window_y_bottom();
//
//          template <class Derived>
//          std::pair<double, double> axis_plot_frame<Derived>::plot_window_x();
//          template <class Derived>
//          std::pair<double, double> axis_plot_frame<Derived>::plot_window_y();
//          template <class Derived>
//          double axis_plot_frame<Derived>::x_minor_interval();
//          template <class Derived>
//          double axis_plot_frame<Derived>::y_minor_interval();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_ticks_up_on(bool cmd);
//          template <class Derived>
//          bool axis_plot_frame<Derived>::x_ticks_up_on();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_ticks_down_on(bool cmd);
//          template <class Derived>
//          bool axis_plot_frame<Derived>::x_ticks_down_on();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_label_on(bool cmd);
//          template <class Derived>
//          bool axis_plot_frame<Derived>::x_label_on();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_label_font_size(unsigned int i);
//          template <class Derived>
//          unsigned int axis_plot_frame<Derived>::x_label_font_size();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_value_font_size(unsigned int i);
//          template <class Derived>
//          unsigned int axis_plot_frame<Derived>::x_value_font_size();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_label_font_family(const std::string& family);
//          template <class Derived>
//          const std::string& axis_plot_frame<Derived>::x_label_font_family();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_axis_label_color(const svg_color& col);
//          template <class Derived>
//          svg_color axis_plot_frame<Derived>::x_axis_label_color();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_ticks_values_color(const svg_color& col);
//
//          template <class Derived>
//          svg_color axis_plot_frame<Derived>::x_ticks_values_color();
//
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_ticks_values_precision(int p);
//
//          template <class Derived>
//          int axis_plot_frame<Derived>::x_ticks_values_precision();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_ticks_values_ioflags(std::ios_base::fmtflags f);
//          template <class Derived>
//          std::ios_base::fmtflags axis_plot_frame<Derived>::x_ticks_values_ioflags();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_ticks_values_font_size(unsigned int i);
//          template <class Derived>
//          unsigned int axis_plot_frame<Derived>::x_ticks_values_font_size();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_ticks_values_font_family(const std::string& family);
//          template <class Derived>
//          const std::string& axis_plot_frame<Derived>::x_ticks_values_font_family();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_ticks_on_window_or_axis(int cmd);
//          template <class Derived>
//          int axis_plot_frame<Derived>::x_ticks_on_window_or_axis();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_label_units_on(bool cmd);
//          template <class Derived>
//          bool axis_plot_frame<Derived>::x_label_units_on();
//
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_major_labels_side(int place);
//          template <class Derived>
//          int axis_plot_frame<Derived>::x_major_labels_side();
//
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_major_label_rotation(rotate_style rot);
//
//          template <class Derived>
//          rotate_style axis_plot_frame<Derived>::x_major_label_rotation();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::title_on(bool cmd);
//          template <class Derived>
//          bool axis_plot_frame<Derived>::title_on();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_major_grid_on(bool is);
//          template <class Derived>
//          bool axis_plot_frame<Derived>::x_major_grid_on();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_minor_grid_on(bool is);
//          template <class Derived>
//          bool axis_plot_frame<Derived>::x_minor_grid_on();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::axes_on(bool is);
//          template <class Derived>
//          bool axis_plot_frame<Derived>::axes_on();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_axis_on(bool is);
//          template <class Derived>
//          bool axis_plot_frame<Derived>::x_axis_on();
//
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::background_border_width(double w);
//          template <class Derived>
//          double axis_plot_frame<Derived>::background_border_width();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::description(const std::string d);
//          template <class Derived>
//          const std::string& axis_plot_frame<Derived>::description();
//
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::y_axis_on(bool is);
//
//          template <class Derived>
//          bool axis_plot_frame<Derived>::y_axis_on();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::title_color(const svg_color& col);
//
//          template <class Derived>
//          svg_color axis_plot_frame<Derived>::title_color();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::legend_color(const svg_color& col);
//          template <class Derived>
//          svg_color axis_plot_frame<Derived>::legend_color();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::legend_background_color(const svg_color& col);
//          template <class Derived>
//          svg_color axis_plot_frame<Derived>::legend_background_color();
//          template <class Derived>
//          bool axis_plot_frame<Derived>::legend_box_fill_on();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::legend_border_color(const svg_color& col);
//          template <class Derived>
//          svg_color axis_plot_frame<Derived>::legend_border_color();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::plot_background_color(const svg_color& col);
//          template <class Derived>
//          svg_color axis_plot_frame<Derived>::plot_background_color();
//          template <class Derived>
//          const std::string axis_plot_frame<Derived>::x_axis_position();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_axis_color(const svg_color& col);
//          template <class Derived>
//          svg_color axis_plot_frame<Derived>::x_axis_color();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::y_axis_color(const svg_color& col);
//          template <class Derived>
//          svg_color axis_plot_frame<Derived>::y_axis_color();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_label_color(const svg_color& col);
//          template <class Derived>
//          svg_color axis_plot_frame<Derived>::x_label_color();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_label_width(double width);
//          template <class Derived>
//          double axis_plot_frame<Derived>::x_label_width();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::y_label_color(const svg_color& col);
//          template <class Derived>
//          svg_color axis_plot_frame<Derived>::y_label_color();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_major_tick_color(const svg_color& col);
//          template <class Derived>
//          svg_color axis_plot_frame<Derived>::x_major_tick_color();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_minor_tick_color(const svg_color& col);
//          template <class Derived>
//          svg_color axis_plot_frame<Derived>::x_minor_tick_color();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_major_grid_color(const svg_color& col);
//          template <class Derived>
//          svg_color axis_plot_frame<Derived>::x_minor_tick_color();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_major_grid_color(const svg_color& col);
//          template <class Derived>
//          svg_color axis_plot_frame<Derived>::x_major_grid_color();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_major_grid_width(double w);
//          template <class Derived>
//          double axis_plot_frame<Derived>::x_major_grid_width();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_minor_grid_color(const svg_color& col);
//          template <class Derived>
//          svg_color axis_plot_frame<Derived>::x_minor_grid_color();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_minor_grid_width(double w);
//          template <class Derived>
//          double axis_plot_frame<Derived>::x_minor_grid_width();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_axis_width(double width);
//          template <class Derived>
//          double axis_plot_frame<Derived>::x_axis_width();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::data_lines_width(double width);
//          template <class Derived>
//          double axis_plot_frame<Derived>::data_lines_width();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_label(const std::string& str);
//          template <class Derived>
//          std::string axis_plot_frame<Derived>::x_label();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_label_units(const std::string& str);
//          template <class Derived>
//          std::string axis_plot_frame<Derived>::x_label_units();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::y_label(const std::string& str);
//          template <class Derived>
//          std::string axis_plot_frame<Derived>::y_label();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::y_label_units(const std::string& str);
//          template <class Derived>
//          std::string axis_plot_frame<Derived>::y_label_units();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_values_on(bool b);
//          template <class Derived>
//          bool axis_plot_frame<Derived>::x_values_on();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_values_font_size(unsigned int i);
//
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_values_font_family(const std::string& family);
//          template <class Derived>
//          unsigned int axis_plot_frame<Derived>::x_values_font_size();
//
//          template <class Derived>
//          const std::string& axis_plot_frame<Derived>::x_values_font_family();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_major_interval(double inter);
//          template <class Derived>
//          double axis_plot_frame<Derived>::x_major_interval();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_values_color(const svg_color& col);
//          template <class Derived>
//          svg_color axis_plot_frame<Derived>::x_values_color();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_values_rotation(rotate_style rotate);
//          template <class Derived>
//          int axis_plot_frame<Derived>::x_values_rotation();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_values_precision(int p);
//          template <class Derived>
//          int axis_plot_frame<Derived>::x_values_precision();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_values_ioflags(std::ios_base::fmtflags f);
//          template <class Derived>
//          std::ios_base::fmtflags axis_plot_frame<Derived>::x_values_ioflags();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_plusminus_on(bool b);
//          template <class Derived>
//          bool axis_plot_frame<Derived>::x_plusminus_on();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_plusminus_color(const svg_color& col);
//          template <class Derived>
//          svg_color axis_plot_frame<Derived>::x_plusminus_color();
//
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_addlimits_on(bool b);
//          template <class Derived>
//          bool axis_plot_frame<Derived>::x_addlimits_on();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_addlimits_color(const svg_color& col);
//          template <class Derived>
//          svg_color axis_plot_frame<Derived>::x_addlimits_color();
//
//
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_df_on(bool b);
//          template <class Derived>
//          bool axis_plot_frame<Derived>::x_df_on();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_df_color(const svg_color& col);
//          template <class Derived>
//          svg_color axis_plot_frame<Derived>::x_df_color();
//         template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_id_on(bool b);
//          template <class Derived>
//          bool axis_plot_frame<Derived>::x_id_on();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_id_color(const svg_color& col);
//          template <class Derived>
//          svg_color axis_plot_frame<Derived>::x_id_color();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_datetime_on(bool b);
//          template <class Derived>
//          bool axis_plot_frame<Derived>::x_datetime_on();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_datetime_color(const svg_color& col);
//          template <class Derived>
//          svg_color axis_plot_frame<Derived>::x_datetime_color();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_order_on(bool b);
//          template <class Derived>
//          bool axis_plot_frame<Derived>::x_order_on();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_order_color(const svg_color& col);
//          template <class Derived>
//          svg_color axis_plot_frame<Derived>::x_order_color();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_decor(const std::string& pre, const std::string& sep, const std::string& suf);
//          template <class Derived>
//          const std::string axis_plot_frame<Derived>::x_prefix();
//          template <class Derived>
//          const std::string axis_plot_frame<Derived>::x_suffix();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_major_tick_length(double length);
//          template <class Derived>
//          double axis_plot_frame<Derived>::x_major_tick_length();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_major_tick_width(double width);
//          template <class Derived>
//          double axis_plot_frame<Derived>::x_major_tick_width();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_minor_tick_length(double length);
//          template <class Derived>
//          double axis_plot_frame<Derived>::x_minor_tick_length();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_minor_tick_width(double width);
//          template <class Derived>
//          double axis_plot_frame<Derived>::x_minor_tick_width();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_major_tick(double d);
//          template <class Derived>
//          double axis_plot_frame<Derived>::x_major_tick();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_minor_interval(double interval);
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_num_minor_ticks(unsigned int num);
//          template <class Derived>
//          unsigned int axis_plot_frame<Derived>::x_num_minor_ticks();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_range(double min_x, double max_x);
//          template <class Derived>
//          double axis_plot_frame<Derived>::x_max();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::autoscale_check_limits(bool b);
//          template <class Derived>
//          bool axis_plot_frame<Derived>::autoscale_check_limits();
//          template <class Derived>
//          bool axis_plot_frame<Derived>::x_autoscale();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_autoscale(bool b);
//          template <class Derived>
//          bool axis_plot_frame<Derived>::autoscale();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::autoscale_plusminus(double pm);
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::autoscale(bool b);
//          template <class Derived>
//          double axis_plot_frame<Derived>::autoscale_plusminus();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_autoscale(std::pair<double, double> p);
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_with_zero(bool b);
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_min_ticks(int min_ticks);
//          template <class Derived>
//          int axis_plot_frame<Derived>::x_min_ticks();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_steps(int steps);
//          template <class Derived>
//          int axis_plot_frame<Derived>::x_steps();
//          template <class Derived>
//          Derived& axis_plot_frame<Derived>::x_tight(double tight);
//         template <class Derived>
//         double axis_plot_frame<Derived>::x_tight();
//         template <class Derived>
//         double axis_plot_frame<Derived>::x_auto_min_value();
//         template <class Derived>
//         double axis_plot_frame<Derived>::x_auto_max_value();
//         template <class Derived>
//         double axis_plot_frame<Derived>::x_auto_tick_interval();
//        template <class Derived>
//        int axis_plot_frame<Derived>::x_auto_ticks();
//        template <class Derived>
//        Derived& axis_plot_frame<Derived>::limit_color(const svg_color& col);
//        template <class Derived>
//        svg_color axis_plot_frame<Derived>::limit_color();
//        template <class Derived>
//        Derived& axis_plot_frame<Derived>::limit_fill_color(const svg_color& col);
//        template <class Derived>
//        svg_color axis_plot_frame<Derived>::limit_fill_color();
//        template <class Derived>
//        Derived& axis_plot_frame<Derived>::one_sd_color(const svg_color& col);
//       template <class Derived>
//       svg_color axis_plot_frame<Derived>::one_sd_color();
//        template <class Derived>
//        Derived& axis_plot_frame<Derived>::two_sd_color(const svg_color& col);
//       template <class Derived>
//       svg_color axis_plot_frame<Derived>::two_sd_color();
//        template <class Derived>
//        Derived& axis_plot_frame<Derived>::three_sd_color(const svg_color& col);
//       template <class Derived>
//       svg_color axis_plot_frame<Derived>::three_sd_color();
//        template <class Derived>
//        Derived& axis_plot_frame<Derived>::draw_note(double x, double y, std::string note, rotate_style rot /*= horizontal*/, align_style al/* = center_align*/, const svg_color& col /* black */, text_style& tsty/* = no_style*/);
//        template <class Derived>
//        Derived& axis_plot_frame<Derived>::draw_line(double x1, double y1, double x2, double y2, const svg_color& col /* black */);
//        template <class Derived>
//        Derived& axis_plot_frame<Derived>::draw_plot_line(double x1, double y1, double x2, double y2, const svg_color& col /* black */);

    } // detail
    } // svg
  } // boost

#ifndef BOOST_SVG_AXIS_PLOT_FRAME_IPP
#  include <boost/svg_plot/impl/axis_plot_frame.ipp>
#endif

#endif // BOOST_SVG_AXIS_PLOT_FRAME_HPP
