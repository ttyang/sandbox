/*!
  \file svg_1d_plot.hpp
  \brief Create 1D plots in Scalable Vector Graphic (SVG) format.
  \details Provides svg_1d_plot data and function to create plots, and svg_1d_plot_series to allow data values to be added.
  Very many functions allow fine control of the appearance and layout of plots and data markers.
  Items common to 1D and 2D use axis_plot_frame.
  \date Mar 2009
 */

// Copyright Jacob Voytko 2007
// Copyright Paul A. Bristow 2008, 2009, 2011, 2012

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SVG_SVG_1D_PLOT_HPP
#define BOOST_SVG_SVG_1D_PLOT_HPP

#if defined (_MSC_VER)
#  pragma warning (push)
#  pragma warning (disable: 4512) // "assignment operator could not be generated."
#  pragma warning (disable: 4180) // qualifier applied to function type has no meaning; ignored
#endif

#include <boost/iterator/transform_iterator.hpp>
// using boost::make_transform_iterator;

#include <boost/svg_plot/svg.hpp>
#include <boost/svg_plot/svg_style.hpp>
#include <boost/svg_plot/detail/axis_plot_frame.hpp> // Code shared with 2D.
#include <boost/svg_plot/detail/functors.hpp>
//using boost::svg::detail::unc_1d_convert;
#include <boost/svg_plot/detail/numeric_limits_handling.hpp>
//#include <boost/quan/unc.hpp>
//#include <boost/quan/unc_init.hpp>
//#include <boost/quan/meas.hpp>
//#include <boost/svg_plot/impl/src.hpp>

using boost::svg::detail::limit_NaN;

#include <boost/svg_plot/detail/auto_axes.hpp>
/*! provides:
void boost::svg::scale_axis(double min_value, double max_value, // Input range
               double* axis_min_value,  double* axis_max_value, double* axis_tick_increment, int* auto_ticks, // All 4 updated.
               bool origin, // If true, ensures that zero is a tick value.
               double tight, // Allows user to avoid a small fraction over a tick using another tick.
               int min_ticks, // Minimum number of ticks.
               int steps); // Round up and down to 2, 4, 6, 8, 10, or 5, 10 or 2, 5, 10 systems.

template<typename T>
void boost::svg::scale_axis(const T&, double*, double*, double*, int*, double*, double*, double*, int*, bool, double, bool, double, int, int, bool, double, int, int);
 */

#include <vector>
#include <ostream>
#include <sstream>
#include <fstream>
#include <string>
#include <exception>

namespace boost
{
namespace svg
{
  // Forward declarations.
  const std::string strip_e0s(std::string s); // Strip unnecessary zeros and e and sign.

  class svg_1d_plot; //! 1D Plot (that may include one or more data series).

  class svg_1d_plot_series; //! A data series to be added to a 1D Plot.

// ------------------------------------------------------------------
// This allows us to store plot state locally in svg_plot.
// Not stored in "svg" because transforming the points after they are
// written to the document would be difficult. We store the Cartesian
// coordinates locally and transform them before we write them.
// ------------------------------------------------------------------
class svg_1d_plot_series
{ /*! \class boost::svg::svg_1d_plot_series
   \brief Holds a series of data values (points) to be plotted.
   \details Scan each data point sorting them into the appropriate
   std::vectors, normal or not (NaN or infinite).\n
   Member functions allow control of data points markers and lines joining them,
   and their appearance, shape, color and size.\n
   Each data series can have a title that can be shown on a legend box with identifying symbols.
*/

public:
  std::vector<Meas> series_; //!< Normal 'OK to plot' data values.
  //std::vector<unc<false> > series_; //!< Normal 'OK to plot' data values.
  std::vector<double> series_limits_; //!< 'limit' values: too big, too small or NaN.
  // TODO should these be unc too?  Uncertainty info is meaningless, but timestamp etc are OK.

  std::string title_; //!< title of data series (to show on legend).
  plot_point_style point_style_; //!< circle, square...
  plot_point_style limit_point_style_; //!< Default is cone pointing down.
  plot_line_style line_style_; //!< No line style for 1-D, only for 2-D.

  // Constructor svg_1d_plot_series.
  //! Scan each data point between the iterators that are passed,
  //! sorting them into the appropriate std::vectors, normal or not (NaN or infinite).

  template <class C> //! \tparam C an STL container: array, vector<double>, set, map ...<
  svg_1d_plot_series(C begin, C end, const std::string& title = "");

  // Declarations of Set functions for the plot series.

  svg_1d_plot_series& fill_color(const svg_color& col_); //!< Set fill color for plot point marker(s) (chainable).
  svg_1d_plot_series& stroke_color(const svg_color& col_); //!< Set stroke color for plot point marker(s) (chainable).
  svg_1d_plot_series& shape(point_shape shape_); //!< Set shape for plot point marker(s) (chainable).
  svg_1d_plot_series& symbols(const std::string s); //!< Set symbol(s) for plot point marker(s) (chainable).
  svg_1d_plot_series& size(int size_); //!< Set font size for plot point marker(s) (chainable).
  svg_1d_plot_series& line_color(const svg_color& col_); //!< Set color for line joining data points (chainable).
  svg_1d_plot_series& line_width(double wid_); //!< Set line width for plot point marker(s) (chainable).
  svg_1d_plot_series& line_on(bool on_); //!< Set true for line joining points for plot point marker(s) (chainable).
  svg_1d_plot_series& bezier_on(bool on_); //!< Set true for curve joining points for plot point marker(s) (chainable).
  svg_1d_plot_series& limit_point_color(const svg_color& col_); //!< Set stroke color for 'at limits' point marker.

  // Get functions for the plot series.
  svg_color fill_color(); //!< Get fill color for plot point marker(s).
  svg_color stroke_color(); //!< Get stroke color for plot point marker(s).
  int size(); //!< Get size for plot point marker(s).
  point_shape shape(); //!< Get shape for plot point marker(s).
  const std::string symbols(); //!< Get sumbols for plot point marker(s).
  double line_width(); //!< Get line width for plot point marker(s).
  bool line_on(); //!< Get true if line is to join data points.
  bool bezier_on(); //!< Get true if curve if to join data points.
  size_t series_count(); //!< Get number of normal data points in this data series.
  size_t series_limits_count();//!< Get number of 'at limits' data points in this data series.
}; // class svg_1d_plot_series


class svg_1d_plot : public detail::axis_plot_frame<svg_1d_plot>
{ /*! \class boost::svg::svg_1d_plot
     \brief All settings for a plot that control the appearance, and functions to get and set these settings.
      axis_plot_frame.hpp contains functions common to 1 and 2-D.
      \details Several versions of the function plot are provided to allow data to be in different sources,
      and to allow either all data in a container to just a sub-range to be plotted.
      \see also svg_2d_plot.hpp for the 2-D version.
  */

  friend void show_1d_plot_settings(svg_1d_plot&);
  //friend void show_2d_plot_settings(svg_1d_plot&); // Surely not needed?
  friend class detail::axis_plot_frame<svg_1d_plot>;

public:
  //protected: // but seems little benefit?
  // Member data names conventionally end with _, for example: border_margin_,
  // and set & get accessor functions are named *without* _ suffix,
  // for example: border_margin() & border_margin(int).

  double x_scale_; //!< Scale used for transform from Cartesian to SVG coordinates.
  double x_shift_; //!< Shift from SVG origin is top left, Cartesian is bottom right.
  double y_scale_; //!< Scale used for transform from Cartesian to SVG coordinates.
  double y_shift_; //!< Shift from SVG origin is top left, Cartesian is bottom right.

  svg image_; //!< Stored so as to avoid rewriting style information constantly.

  double text_margin_; //!< Marginal space around text items like title,

  text_style a_style_; //!< Default text style that contains font size & type etc.
  text_style title_style_; //!< style (font etc) of title.
  text_style legend_style_; //!<  style (font etc of legend.
  text_style x_axis_label_style_; //!< style of X axis label.
  text_style y_axis_label_style_;  //!< Not used for 1D but needed by axis_plot_frame.hpp.
  text_style x_value_label_style_; //!< style of X ticks value label.
  text_style y_value_label_style_; //!< Not used for 1D but needed by axis_plot_frame.hpp.
  text_style point_symbols_style_; //!< Used for data point marking.
  text_style value_style_; //!< Used for data point value label.

  value_style x_values_style_; //!< Used for data point value marking.
  //rotate_style x_value_label_rotation_; // Direction point value labels written.
  //int x_value_precision_;
  //std::ios_base::fmtflags x_value_ioflags_;

  // text_elements hold position & alignment, and indirectly via text_style, font_family, font_size, bold, italic...
  text_element title_info_; //!< Title of whole plot.
  text_element legend_header_; //!< legend box header or title (if any).
  text_element x_label_info_; //!< X-axis label, Example: "length of widget"
  text_element x_value_label_info_; //!< X-axis tick value label, for example: "1.2" or "1.2e1"
  text_element x_units_info_; //!< For example, to display, "length (meter)"

  // No Y-axis info for 1D.

  // Border information for the plot window (not the full image size).
  box_style image_border_; //!< rectangular border of all image width, color...
  box_style plot_window_border_; //!< rectangular border of plot window width, color...
  box_style legend_box_; //!< rectangular box of legend width, color...

  double plot_left_; //!< svg left of plot window (calculate_plot_window() sets these values).
  double plot_top_; //!< svg top of plot window (calculate_plot_window() sets these values).
  double plot_right_; //!< svg right of plot window (calculate_plot_window() sets these values).
  double plot_bottom_; //!< svg bottom of plot window (calculate_plot_window() sets these values).

  // enum legend_places{ nowhere, inside...}
  legend_places legend_place_; //!< Place for any legend box.
  double legend_width_; //!< Width of legend box (pixels).
  double legend_height_; //!< Height of legend box (in pixels).
  //!< Size of legend box is controlled by its contents,
  //!< but helpful to store computed coordinates.
  double legend_left_; //!< Left of legend box.
  double legend_top_; //!< Top of legend box.
  // Both optionally set by legend_top_left.
  double legend_right_; //!< SVG Coordinates of right of legend box,
  double legend_bottom_; //!< bottom of legend box.
  double x_axis_vertical_; //!< Vertical position of 1D horizontal X-axis line as fraction of window.
  //! 0.5 is at middle(useful if no labels) (default),
  //! 0.8 is near bottom (useful if value labels go upward),
  //! 0.2 is near top (useful if value labels go downward).

  size_t legend_longest_; //!< longest (both header & data) string in legend box,

  axis_line_style x_axis_; //!< style of X axis line.
  axis_line_style y_axis_; //!< style of Y axis line.

  ticks_labels_style x_ticks_; //!< style of X axis tick value labels.
  ticks_labels_style y_ticks_; //!< style of Y axis tick value labels. (Meaningless for 1D but added to permit shared code!)

  bool title_on_; //!< If true include a title for the whole plot.
  bool legend_on_; //!< If true include a legend box.
  bool outside_legend_on_; //!< If true, place legend box outside the plot window.
  bool legend_lines_; //!< If true, include data colored line type in legend box.
  bool plot_window_on_; //!< Use a separate plot window (not whole image).
  bool x_ticks_on_; //!< Ticks on X axis will be shown.
  bool x_values_on_; //!< values of data are shown by markers.
  int  x_axis_position_; //!< \see boost::svg::x_axis_intersect.

  // Parameters for calculating confidence intervals (for both X and Y values).
  // These might be picked up from uncertain types.
  double alpha_; // = 0.05; // oss.iword(confidenceIndex) / 1.e6; // Pick up alpha.
  double epsilon_; // = 0.01; // = oss.iword(roundingLossIndex) / 1.e3; // Pick up rounding loss.
  int uncSigDigits_; // = 2; // = oss.iword(setUncSigDigitsIndex);  // Pick up significant digits for uncertainty.
  bool isNoisyDigit_; // = false; // Pick up?

  // Autoscaling
  bool autoscale_check_limits_; //!< If true, then check autoscale values for infinity, NaN, max, min.
  bool x_autoscale_; //!< If true, use any autoscale values for scaling the X axis.
  double autoscale_plusminus_; //!< For uncertain values, allow for text_plusminus ellipses showing 67%, 95% and 99% confidence limits.\n
  //!< For example, if a max value is 1.2 +or- 0.02, then 1.4 will be used for autoscaling the maximum.\n
  //!< Similarly, if a min value is 1.2 +or- 0.02, then 1.0 will be used for autoscaling the minimum.
  double text_plusminus_; // Nominal factor of 1. (default) corresponds to 67% confidence limit.
  bool x_include_zero_; //!< If autoscaled, include zero.
  int  x_min_ticks_;  //!< If autoscaled, set a minimum number of ticks.
  double x_tight_; //!< How much a value can go beyond the tick value before another tick is required.
  int  x_steps_;  //!< If autoscaled, set any prescaling to decimal 1, 2, 5, 10 etc.

  // Values calculated by scale_axis, and is used only if x_autoscale == true.
  double x_auto_min_value_; //!< X minimum value calculated by autoscaling.
  double x_auto_max_value_;//!< X maximum value calculated by autoscaling.
  double x_auto_tick_interval_; //!< X axis tick major interval.
  int x_auto_ticks_; //!< Number of X axis ticks.

  // Similar y_auto value for 2-D
  bool y_autoscale_; //!< Always false for 1-D plot because Y axis is not autoscaled.

  std::string plot_window_clip_; //!< = "clip_plot_window" id for clippath
  //!< http://www.w3.org/TR/SVG/masking.html#ClipPathElement 14.1 Introduction
  //!< clipping paths, which uses any combination of 'path', 'text' and basic shapes
  //!< to serve as the outline where everything on the "inside" of the outline
  //!< is allowed to show through but everything on the outside is masked out.
  //!< So the plot_window_clip_ limits display to a plot_window rectangle.

  std::vector<svg_1d_plot_series> serieses_;  //!< The (perhaps several) series of data points for transformation.
  //!< These are sorted into two vectors for normal and abnormal (max, inf and NaN).

public:

  svg_1d_plot::svg_1d_plot(); //! Constructor of a 1-D plot.
  void set_ids(); //! Set the XML ids for various layers of the plot.
  void calculate_plot_window(); //! Calculate the position of the plot window.
  void calculate_transform(); //! Calculate transform form euclidian to svg coordinate.
  void draw_axes(); //! Draw the X axis (and, for 2-D, also the Y axis) of the plot.
  void update_image(); /*! Calls functions to add all plot information to the image, including
  plot window, axes, ticks, labels, grids, legend, and finally all the data series.*/

  // ------------------------------------------------------------------------
  // write() has two versions: to an ostream and to a file.
  // The stream version first clears all unnecessary data from the graph,
  // builds the document tree, and then calls the write function for the root
  // document node, which calls all other nodes through the Visitor pattern.
  // The file version opens an ostream, and calls the stream version.
  // ------------------------------------------------------------------------
  svg_1d_plot& write(const std::string& file);
  svg_1d_plot& write(std::ostream& s_out);

  // Declarations of several versions of function plot to add data series (with defaults).
  template <typename T>
  svg_1d_plot_series& plot(const T& container, const std::string& title = "");
  template <typename T>
  svg_1d_plot_series& plot(const T& begin, const T& end, const std::string& title = "");
 
  template <typename T, typename U>
  svg_1d_plot_series& plot(const T& container, const std::string& title = "", U functor = boost::svg::detail::double_1d_convert());
  template <typename T, typename U>
  svg_1d_plot_series& plot(const T& begin, const T& end, const std::string& title = "", U functor = boost::svg::detail::double_1d_convert());
  // GCC seems to need functor to have trailing (), but MSVC does not.
}; // class svg_1d_plot


// End svg_1d_plot Member functions definitions.

#if defined (_MSC_VER)
#  pragma warning(pop)
#endif

} // namespace svg
} // namespace boost

// Definitions are in svg_1d_plot.ipp
#ifndef BOOST_SVG_SVG_1D_PLOT_IPP
#  include <boost/svg_plot/impl/svg_1d_plot.ipp>
#endif

#endif // BOOST_SVG_SVG_1D_PLOT_HPP
