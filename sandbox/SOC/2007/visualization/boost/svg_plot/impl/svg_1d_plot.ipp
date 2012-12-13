/*!
  \file
  \brief Create 1D plots in Scalable Vector Graphic (SVG) format.
  \details Definitions
 */

// svg_1d_plot.ipp
// Copyright Jacob Voytko 2007
// Copyright Paul A. Bristow 2008, 2009, 2011, 2012

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SVG_SVG_1D_PLOT_IPP
#define BOOST_SVG_SVG_1D_PLOT_IPP

#include <boost/svg_plot/svg_1d_plot.hpp>

namespace boost
{
namespace svg
{

//! class svg_1d_plot_series Constructor.
template <typename C> //! \tparam C an iterator into STL container: array, vector<double>, vector<unc>, vector<Meas> set, map ...
svg_1d_plot_series::svg_1d_plot_series(C begin, C end, const std::string& title)
: // Constructor.
title_(title),
point_style_(black, blank, 5, vertical_line), // Default point style.
limit_point_style_(lightgrey, red, 10, cone), // Default limit (inf or NaN) point style.
//limit_point_style_(lightgrey, whitesmoke, 10, cone), // Default limit (inf or NaN) point style.
line_style_(black, blank, 2, false, false) // Default line style, black, no fill, width, line_on, bezier_on false
{
  /*
    std::cout << "typeid(C).name() = " << typeid(C).name() << std::endl;
    typeid(C).name() =
    class boost::transform_iterator
    <
      class boost::svg::detail::unc_1d_convert, class std::_Vector_const_iterator
      <
        class std::_Vector_val
        <
          class boost::svg::unc, class std::allocator
          <
            class boost::svg::unc
          >
        >
      >,
      struct boost::use_default, struct boost::use_default
    >
  */

  for(C i = begin; i != end; ++i)
  {  // Might be useful to have defaults for begin and end? But unclear how.
    //double temp = *i; // assume type is just double.
    //boost::svg::unc temp = *i; // Assumes unc type.
    //unc<false> temp = *i; // Should provide double, unc, meas ... type.
    // So use auto to automatically make temp the right type.
    auto temp = *i; // Should provide double, unc, meas ... type.
    //std::cout << "typeid(temp).name() = " << typeid(temp).name() << std::endl;
    //   typeid(temp).name() = class Meas
    //   typeid(temp).name() = class boost::svg::unc
    if(detail::is_limit(temp.value()))
    {
      series_limits_.push_back(temp.value()); // 'limit' values: too big, too small or NaN.
      // This assumes that uncertainty info is meaningless?
    }
    else
    {
      series_.push_back(temp); // Normal 'OK to plot' data values (including uncertainty info).
      // Should copy name and other info too if applicable.
    }
  }
} // svg_plot_series constructor.

// Definitions of svg_plot_series Member Functions.
svg_1d_plot_series& svg_1d_plot_series::fill_color(const svg_color& col_)
{ //! Set fill color for plot point marker(s) (chainable).
  point_style_.fill_color_ = col_;
  return *this; //! \return reference to svg_1d_plot_series to make chainable.
}

svg_1d_plot_series& svg_1d_plot_series::stroke_color(const svg_color& col_)
{ //! Set stroke color for plot point marker(s) (chainable).
  point_style_.stroke_color_ = col_;
  return *this; //! \return reference to svg_1d_plot_series to make chainable.
}

svg_1d_plot_series& svg_1d_plot_series::shape(point_shape shape_)
{ //! Set shape for plot point marker(s) (chainable).
  point_style_.shape_ = shape_;
  return *this; //! \return reference to svg_1d_plot_series to make chainable.
}

point_shape svg_1d_plot_series::shape()
{ //! \return  shape for plot point marker(s).
  return point_style_.shape_;
}

svg_1d_plot_series& svg_1d_plot_series::symbols(const std::string s)
{ //! Set symbol for plot point marker(s).
  point_style_.symbols_ = s;
  return *this; //! \return reference to svg_1d_plot_series to make chainable.
}

svg_1d_plot_series& svg_1d_plot_series::size(int size_)
{ //! Set size of plot point marker(s).
  //point_style_.size_ = size_;
  //point_style_.symbols_style_.font_size(i); // in case using a symbol.
  point_style_.size(size_);
  return *this; //! \return reference to svg_1d_plot_series to make chainable.
}

int svg_1d_plot_series::size()
{ //! \return  size of plot point marker(s).
  return point_style_.size();
}

const std::string svg_1d_plot_series::symbols()
{ //! \return  symbol for plot point marker(s).
  return point_style_.symbols_;
}

svg_1d_plot_series& svg_1d_plot_series::line_color(const svg_color& col_)
{ //! Set color of any line joining plot points.
  line_style_.stroke_color_ = col_;
  return *this; // Make chainable.
}

svg_1d_plot_series& svg_1d_plot_series::line_width(double wid_)
{ /*! Set width of any line joining plot points.
   \return @c *this to make chainable.
   */
  line_style_.width_ = wid_;
  return *this; // Make chainable.
}

double svg_1d_plot_series::line_width()
{ //! \return  Width of any line joining plot points.
  return line_style_.width_;
}

svg_1d_plot_series& svg_1d_plot_series::line_on(bool on_)
{ /*! Set @c true if to draw a line joining plot points.
   \return @c *this to make chainable.
   */
  line_style_.line_on_ = on_;
  return *this; // Make chainable.
}

bool svg_1d_plot_series::line_on()
{ //! \return @c true if to draw a line joining plot points.
  return line_style_.bezier_on_;
}

svg_1d_plot_series& svg_1d_plot_series::bezier_on(bool on_)
{ //! Set @c true if to draw bezier curved line joining plot points.
  line_style_.bezier_on_ = on_;
  return *this; // Make chainable.
}

bool svg_1d_plot_series::bezier_on()
{ //! \return @c true if to draw bezier curved line joining plot points.
  return line_style_.bezier_on_;
}

size_t svg_1d_plot_series::series_count()
{ //! \return Number of normal 'OK to plot' data values in data series.
  return series_.size();
}

size_t svg_1d_plot_series::series_limits_count()
{ //!  \return Number of  'at limit' values: too big, too small or NaN data values in data series.
  return series_limits_.size();
}

svg_1d_plot_series& svg_1d_plot_series::limit_point_color(const svg_color& col_)
{ //! Set of stroke color of 'at limits' points.
  limit_point_style_.stroke_color_ = col_;
  return *this; // Make chainable.
}

void svg_1d_plot::update_image()
{ //! Calls functions to add all plot information to the image, including
  //! plot window, axes, ticks, labels, grids, legend, and finally all the data series.

  clear_all(); // Removes all elements that will show up in a subsequent draw.

  // Draw plot background.
  image_.g(detail::PLOT_BACKGROUND).push_back(
    new rect_element(0, 0, image_.x_size(),  image_.y_size()));

  calculate_plot_window();
  calculate_transform();
  draw_title(); // Call after above to the plot_x and y are defined.
  if(x_axis_.axis_line_on_)
  {
    draw_axes();
  }
  if(legend_on_)
  {
    draw_legend();
  }
  if(x_axis_.label_on_)
  {
    draw_x_axis_label();
  }
  double y(0.); // All 1-D points are plotted are on the horizontal X axis (y = 0) axis.
  transform_y(y);
  if ((y < plot_top_) || (y > plot_bottom_))
  { // Should never happen!
    throw std::runtime_error("transform_y(y=0) outside plot window!");
  }

  for(unsigned int i = 0; i < serieses_.size(); ++i)
  { // Plot the data points for each of the data series.
    g_element& g_ptr = image_.g(detail::PLOT_DATA_POINTS).add_g_element();
    g_ptr.style().stroke_color(serieses_[i].point_style_.stroke_color_);
    g_ptr.style().fill_color(serieses_[i].point_style_.fill_color_);

    for(unsigned int j = 0; j < serieses_[i].series_.size(); ++j)
    { // Draw jth point for ith serieses.
      Meas ux = serieses_[i].series_[j];
      // unc<false> ux = serieses_[i].series_[j];
      double x = ux.value();
      // TODO symbols are offset downwards because
      // the origin of the point is the top left of the glyph.
      // Need to offset by the height and width of the font size?
      transform_x(x);
      if((x >= plot_left_) && (x <= plot_right_)) // Check point is inside plot_window.
      // May need a margin here to avoid points just over the window not being shown.
      {
        draw_plot_point(x, y, g_ptr, serieses_[i].point_style_, ux, Meas()); // Marker.
        // (y uncertainty is zero for 1d X values).
        // draw_plot_point(x, y, g_ptr, serieses_[i].point_style_, ux, unc<false>()); // Marker.
        // (y uncertainty is zero).
        if (x_values_on_)
        { // Show the value (& perhaps uncertainty) of the data point too.
          g_element& g_ptr_v = image_.g(detail::PLOT_X_POINT_VALUES).add_g_element();
          draw_plot_point_value(x, y, g_ptr_v, x_values_style_, serieses_[i].point_style_, ux);
          // TODO Might separate X and Y colors?
        }
        else
        { // Don't plot anything?  Might leave a marker to show an "off the scale" value?
        }
      } // if in window
    } // for j
  } // for i all normal

  // Draw all the 'bad' or at_limit points.
  for(unsigned int i = 0; i < serieses_.size(); ++i)
  {
    g_element& g_ptr = image_.g(detail::PLOT_LIMIT_POINTS);

    for (unsigned int j = 0; j != serieses_[i].series_limits_.size(); ++j)
    {
      double x = serieses_[i].series_limits_[j];
      if (limit_NaN(x))
      { // is NaN rather than too big or too small.
        double x = 0.;
        transform_x(x);
        // If include zero, OK, else plot on left or right as appropriate.
        if (x < plot_left_)
        {
          x = plot_left_;
        }
        else if (x > plot_right_)
        {
          x = plot_right_;
        }
        //else X axis includes zero, so x is OK.
        draw_plot_point(x, y, g_ptr, serieses_[i].limit_point_style_, Meas(), Meas());
        // draw_plot_point(x, y, g_ptr, serieses_[i].limit_point_style_, unc<false>(), unc<false>());
      }
      else
      { // Not NaN
        transform_x(x);
        if (x < plot_left_)
        {
          x = plot_left_;
        }
        else if (x > plot_right_)
        {
          x = plot_right_;
        }
        // else is inside plot window, so draw a limit point marker.
        // draw_plot_point(x, y, g_ptr, plot_point_style(lightgray, whitesmoke, s, cone)); default.
        serieses_[i].limit_point_style_.stroke_color_ = image_.g(detail::PLOT_LIMIT_POINTS).style().stroke_color();
        serieses_[i].limit_point_style_.fill_color_ = image_.g(detail::PLOT_LIMIT_POINTS).style().fill_color();
        // This is a kludge.  limit_point_style_ should probably be common to all data series.

        draw_plot_point(x, y, g_ptr, serieses_[i].limit_point_style_, Meas(), Meas());
        //draw_plot_point(x, y, g_ptr, serieses_[i].limit_point_style_, unc<false>(), unc<false>());
      }
    } // for j
  } // for i limits point
} //   void update_image()

  /* Default constructor.
      Many ( but not all - see below) default values here.
      See documentation for default settings rationale.
  */
  svg_1d_plot::svg_1d_plot()  :
  title_style_(18, "Verdana", "", ""),  // last "bold" ?
  legend_style_(14, "Verdana", "", ""), // 2nd "italic"?
  x_axis_label_style_(14, "Verdana", "", ""),
  x_value_label_style_(12, "Verdana", "", ""),
  point_symbols_style_(12, "Lucida Sans Unicode"), // Used for data point marking.
  value_style_(10, "Verdana", "", ""), // Used for data point values.

  title_info_(0, 0, "", title_style_, center_align, horizontal),
  //title_info_(0, 0, "Plot of data", title_style_, center_align, horizontal), when text concatenation solved?
  //x_label_info_(0, 0, "X Axis", x_axis_label_style_, center_align, horizontal),
  //x_units_info_(0, 0, " (units)", x_value_label_style_, center_align, horizontal),
  x_label_info_(0, 0, "", x_axis_label_style_, center_align, horizontal), // Null strings for now.
  x_value_label_info_(0, 0, "", x_value_label_style_, center_align, horizontal), // X-axis tick value label, for example: "1.2" or "1.2e1".
  x_units_info_(0, 0, "", x_value_label_style_, center_align, horizontal),
  x_axis_(X, -10., +10., black, 1, 0, true, false, true),
  y_axis_(Y, 0., +1., black, 1, 0, false, false, false), // Not used for 1D.

  // Might fill in all values, but there are rather many for ticks_labels_style,
  x_ticks_(X, x_value_label_style_),// so for defaults see ticks_labels_style.
  text_margin_(2.), // for text as a multiplier of the font size.
  image_border_(yellow, white, 1, 10, true, true), // margin should be about axis label font size.
  plot_window_border_(lightgoldenrodyellow, svg_color(255, 255, 255), 1, 3, true, false),
  legend_box_(yellow, white, 1, 2, true, true),
  legend_header_(0, 0, "", legend_style_, center_align, horizontal),
  legend_width_(200), // width of legend box (pixels) // TODO isn't this calculated?
  legend_height_(0), // height of legend box (pixels)
  legend_left_(-1), legend_right_(-1),legend_top_(-1),legend_bottom_(-1), // Default top left of plot window.
  x_axis_vertical_(0.5), // Vertical position of 1D horizontal X-axis line as fraction of window.
  legend_place_(outside_right), // default but interacts with using plot_window.
  legend_on_(false),
  legend_longest_(0),
  outside_legend_on_(true),
  legend_lines_(false), // Not very useful for 1 D as already showing data point marker shapes.
  plot_window_clip_("plot_window"), // for <clipPath id="plot_window" ...
  title_on_(true),
  plot_window_on_(true),
  x_values_on_(false), // By default, don't label point values.
  x_values_style_(horizontal, 3, std::ios::dec, true, value_style_, black, black, false, false),
  // Confidence interval parameters.
  // (Could provide functions for the user to control these).
  alpha_(0.05), // oss.iword(confidenceIndex) / 1.e6; 95% confidence.
  epsilon_(0.05), // = oss.iword(roundingLossIndex) / 1.e3; // = allow 5% rounding loss.
  uncSigDigits_(2), // = oss.iword(setUncSigDigitsIndex); // ISO standard =2 by default.
  isNoisyDigit_(false), // Add extra digit to display?
  // Autoscaling.
  autoscale_check_limits_(true), // Do check all value for limits, infinity, max, min, NaN.
  autoscale_plusminus_(3.), // Allow 3 uncertainty (standard deviation) for 99% confidence ellipse.
  text_plusminus_(1.), // Nominal factor of 1. (default) corresponds to 67% confidence limit.
  x_autoscale_(false),
  x_include_zero_(false), // If autoscaled, include zero.
  x_min_ticks_(6),  // If autoscaled, set a minimum number of ticks, default 6.
  x_steps_(0),  // If autoscaled, set any prescaling to decimal 1, 2, 5, 10 etc, default none.
  x_tight_(1e-6), // margin that point can lie outside top and bottom tick.
  y_autoscale_(false), // Not used for 1-D.
  // Used to transform Cartesian to SVG.
  x_scale_(1.), x_shift_(0.),
  y_scale_(1.), y_shift_(0.),
  x_axis_position_(0) // Move into axis_style?
{
  size(500, 200); // Default image size.
  // Only needs to be quite shallow (y_size) for a 1-D plot.
  // (But may need more height (y_size) if long value labels are used, for example: "[time = 1.23 +-0.02 sec]").
  // 200 barely leaves enough room for five data series in any legend box).
  // (2-D usually needs to be much more rectangular).

  using namespace boost::svg::detail; // Avoid detail:: specification.

  // Build the document tree & add all the children of the root node.
  for(int i = 0; i < detail::SVG_PLOT_DOC_CHILDREN; ++i)
  {
    image_.add_g_element();
  }
  set_ids();

  // Set other SVG color, stroke & width defaults for various child PLOT nodes.
  image_.g(PLOT_BACKGROUND).style().stroke_color(image_border_.stroke_);
  image_.g(PLOT_BACKGROUND).style().stroke_width(image_border_.width_); //
  image_.g(PLOT_BACKGROUND).style().fill_color(image_border_.fill_);
  image_.g(PLOT_WINDOW_BACKGROUND).style().fill_color(plot_window_border_.fill_);
  image_.g(PLOT_WINDOW_BACKGROUND).style().stroke_width(plot_window_border_.width_).stroke_color(plot_window_border_.stroke_);
  image_.g(PLOT_LIMIT_POINTS).style().stroke_color(lightslategray).fill_color(antiquewhite);
  image_.g(PLOT_X_AXIS).style().stroke_color(black).stroke_width(x_axis_.width());
  image_.g(PLOT_DATA_UNC3).style().stroke_color(lightgoldenrodyellow).fill_color(lightgoldenrodyellow).stroke_width(1);
  image_.g(PLOT_DATA_UNC2).style().stroke_color(peachpuff).fill_color(peachpuff).stroke_width(1);
  image_.g(PLOT_DATA_UNC1).style().stroke_color(magenta).fill_color(pink).stroke_width(1);

  // Note that widths are stored in member data *and* copied here.
  // Not sure if this is wise but ...
  // Font info defaults are set by the constructor above.
  // Ticks.

  y_ticks_.left_ticks_on_ = false; // Needed to ensure don't extend X-axis line.
  y_ticks_.right_ticks_on_ = false;

  if(x_ticks_.use_up_ticks() || x_ticks_.use_down_ticks())
  {
    image_.g(PLOT_X_MAJOR_TICKS).style().stroke_width(x_ticks_.major_tick_width_).stroke_color(black);
    image_.g(PLOT_X_MINOR_TICKS).style().stroke_width(x_ticks_.minor_tick_width_).stroke_color(black);
  }
  // Grids.
  // Default color & width for grid, used or not.
  image_.g(PLOT_X_MAJOR_GRID).style().stroke_width(x_ticks_.major_grid_width_).stroke_color(svg_color(200, 220, 255));
  image_.g(PLOT_X_MINOR_GRID).style().stroke_width(x_ticks_.minor_grid_width_).stroke_color(svg_color(200, 220, 255));
  //image_.g(PLOT_DATA_LINES).style().stroke_width(2); // default width.
  // Alter with, for example: plot.data_lines_width(4);

  legend_place_ = (plot_window_on_) ? outside_right : inside; // Defaults.
  // Note if set plot_window_on() then also need to set legend_place.
  // (if set a default in plot_window then call to set legend place must to come *after* it.
  // So not set a default?  But leaving it as inside is worse?)

  x_ticks_on_ = x_ticks_.up_ticks_on_ || x_ticks_.down_ticks_on_;
  // Only 2D has left and right y ticks.
  x_ticks_.ticks_on_window_or_on_axis_ = 0; // Make ticks (and ticks value labels) on X-axis line the default.
  // This will place the labels just under the horizontal X-axis line,
  // rather than below the plot window border.
  // This over-rides the default in class ticks_labels_style.
  //

  if (title_info_.text() == "")
  { // Avoid leaving unnecessary space etc for a title.
    title_on_ = false;
  }
  else
  {
    title_on_ = true; // Can be switched off later with `my_1d_plot.title_on(true);`
  }
} // svg_1d_plot::svg_1d_plot() Default constructor.


void svg_1d_plot::calculate_plot_window()
{ //! Calculate the size and position of the plot window,
  //! taking account of the length and font size of axes labels, axis ticks, title and legend box.
  //! This version is only for 1-D.
  //! All calculations use SVG units, pixels by default.

  // Start by assuming we can use all the svg image,
  // but reduce by the width of any image border.
  plot_left_ = 0 + image_border_width(); // Top left of image.
  plot_top_ = 0 + image_border_width();
  plot_right_ = image_.x_size() - image_border_width(); // Bottom right of image.
  plot_bottom_ = image_.y_size() - image_border_width();

  if(title_on_ && title_info_.text() != "")
  { // Leave space at top for title.
    // Title at bottom (or sides even) option not implemented.
    plot_top_ += title_font_size() * (text_margin_ + 0.5);
  }

  // Assume that X-axis labels are always at bottom for 1D plot.
  if(x_axis_.label_on_ == true && x_label_info_.text() != "")
  { // Leave space below plot window at bottom for X axis label (unless empty string).
      plot_bottom_ -= x_axis_label_style_.font_size() * text_margin_;
  }
  if(plot_window_on_ == true)
  { // Needed to allow any plot window border rectangle to show OK.
    // A small margin is to prevent it overlapping the image border.
    // Also allows for axis value labels that mark the min and max
    // that must extend about half a font width beyond the plot window border.
    plot_left_ +=  image_border_.margin_;
    plot_right_ -=  image_border_.margin_;
    plot_top_ += image_border_.margin_;
    plot_bottom_ -=  image_border_.margin_;
  }

  // Size if necessary - else (re-)initialise to zero.
  size_legend_box(); // depending on its contents.
  place_legend_box();

  // Because there may be several datasets,
  // and the scaling can be done by any one or all of them.
  // my_plot.autoscale(my_data1) // for 1 dataset.
  // or my_plot.autoscale(my_datas) // for a vector of several datasets.
  // calculates the min & max, increments & ticks.
  if (x_autoscale_)
  { // Use calculated autoscale values.
    // Autoscale has been done in my_data.autoscale(my_data);
    // and saved in x_auto_min_value_, x_auto_max_value_, & x_auto_tick_interval_,
    // so copy these values to use them:
    x_axis_.min_ = x_auto_min_value_;
    x_axis_.max_ = x_auto_max_value_;
    x_ticks_.major_interval_  = x_auto_tick_interval_;
  }
  else
  { // Ignore auto values, even if they have been calculated.
  }
  // Copy X-axis min & max to ticks.
  x_ticks_.min_ = x_axis_.min_;
  x_ticks_.max_ = x_axis_.max_;
  // Ensure both axis and ticks have the *same* range.
  // (To use them separately (designed to give the potential for different ranges)
  // one would have to *not* do this,
  // but to make sure they are both assigned correctly).

  //x_axis_.axis_ = (plot_bottom_) * x_axis_vertical_ + plot_top_ ;  // too low
  //x_axis_.axis_ = (plot_bottom_) * x_axis_vertical_ - plot_top_ ;  // too high
  //x_axis_.axis_ = (plot_bottom_) * x_axis_vertical_;  // tiny amount too  high.
  // x_axis_.axis_ = (plot_bottom_ + plot_top_) * x_axis_vertical_;
    x_axis_.axis_ = (plot_bottom_ - plot_top_) * x_axis_vertical_ + plot_top_;
  // Put X-axis fraction of way up plot window.
  // 0.5 is at middle(useful if no labels),
  // 0.8 is near bottom (useful if value labels go upward),
  // 0.2 is near top (useful if value labels go downward).

  if(plot_window_on_ == true)
  { // Using a plot window and NOT using all image.
    // Calculate the number of chars of the longest tick value label.
    x_ticks_.longest_label(); // Updates label_max_length_
    x_ticks_.label_max_space_ = 0; // Work out the longest tick value label for X-Axis.
    if (x_ticks_.label_rotation_ == horizontal)
    { // Only 1 char height & 1 space needed if labels are horizontal.
      x_ticks_.label_max_space_ = 2 * x_value_label_style_.font_size() * wh; // SVG chars.
      // Should this be just 2 * font_size
    }
    else if ((x_ticks_.label_rotation_ == upward) || (x_ticks_.label_rotation_ == downward))
    { // ! horizontal so will need more than 2 chars worth.
        x_ticks_.label_max_space_+= x_ticks_.label_max_length_ * x_value_label_style_.font_size() * wh; // SVG chars.
    }
    else
    { // Assume label is sloping, say 45, so * sin(45) = 0.707.
        x_ticks_.label_max_space_+= x_ticks_.label_max_length_ * x_value_label_style_.font_size() * wh * sin45; // SVG 'chars'.
    }

    // Make space for any ticks pointing below the plot window.
    if(x_ticks_.down_ticks_on_)
    { // Start bottom of plot higher to give space for any external down ticks.
      plot_bottom_ -= (std::max)(x_ticks_.major_tick_length_, x_ticks_.minor_tick_length_);// And avoid macro max trap!
    }

    if (x_axis_.axis_line_on_)
    { // Want a X-axis line, so check if range includes zero, meaning that X and Y axes intersect,
      // and x_axis_ is svg coordinate of Y-axis (usually y = 0).
      // If not fix axis to bottom of the plot window.
      if ((x_axis_position_ == bottom) // All X data values definitely > zero.
        && !(x_ticks_.ticks_on_window_or_on_axis_ < 0) ) // & not already on bottom of plot window.
      { // y_min_ > 0 so X-axis will not intersect Y-axis, so use plot window border.
        plot_bottom_ -= x_ticks_.label_max_space_; // Move up for the value labels.
        x_axis_.axis_ = plot_bottom_; // Put X-axis on bottom on plot window.
      }
      else if ((x_axis_position_ == top)  // All x data values definitely < zero.
        && !(x_ticks_.ticks_on_window_or_on_axis_ > 0) ) // & not already on top of plot window.
      { // // y_max_ < 0 so X-axis will not intersect Y-axis, so use plot window border.
          plot_top_ += x_ticks_.label_max_space_; // Move down for labels.
          x_axis_.axis_ = plot_top_; // Put X-axis on top of plot window border.
      }
      else
      { // y_axis_position_ == y_intersects_x
        // Calculate below after transform is calculated.
      }
    } // if (use_x_axis_line_)

    // Make space for any tick value labels.
    if (x_ticks_.major_value_labels_side_ != 0)
    { // There are some tick value labels.
      // If ticks and value labels are on plot window border, the need to allow space for them.
      if ((x_ticks_.ticks_on_window_or_on_axis_ < 0) // ticks on bottom of plot window.
          && (x_ticks_.major_value_labels_side_ < 0) ) // & tick value labels below axis line too.
      {  // Contract plot window bottom edge up to make space for X tick value labels on bottom.
        plot_bottom_ -= x_ticks_.label_max_space_; // Move up.
      }
      else if ((x_ticks_.ticks_on_window_or_on_axis_ > 0) //
          && (x_ticks_.major_value_labels_side_ > 0) ) // & X tick value labels to top of plot window.
      { // Move top of plot window down to give space for X tick value labels.
        plot_top_ += x_ticks_.label_max_space_; // Move window top down.
      }
      else // (x_ticks_.major_value_labels_side_ == 0)
      { // X-ticks on the X-axis line (not on plot window border).
        // Don't need to allow any extra space.
        // (But if X-axis is near plot window border, may overlap it, and any X-axis labels!)
      }
    } // x_ticks_. major_value_labels_side
  } // plot_window_on_
  if(plot_window_on_ == true)
  { // Draw plot window border as a rectangular box.
    image_.g(detail::PLOT_WINDOW_BACKGROUND).push_back(
      new rect_element(plot_left_, plot_top_, (plot_right_ - plot_left_), plot_bottom_ - plot_top_));
  } // plot_window_on_
} //  void calculate_plot_window()

void svg_1d_plot::draw_axes()
{ //! Add information to the plot image for X-axis lines.
  //! (For 1-D, there is, of course, only the horizontal X-axis,
  //! but there can be a vertical Y-axis line at x = 0).
  double x(0.);
  transform_x(x);
  double y1(0.);
  double y2(image_.y_size());
  // Draw origin, making sure it is in the plot window.
  if(x_axis_.axis_line_on_ && (x >= plot_left_) && (x <= plot_right_))
  {
    if(!plot_window_on_)
    { // Use whole image.
      if(title_on_)
      { // Allow space for title, taking account of font size.
        y1 += title_info_.textstyle().font_size() * text_margin_;
      }
      if(x_axis_.label_on_)
      {// Allow space for x tick values, taking account of font size.
        y2 -= x_label_info_.textstyle().font_size() * text_margin_;
      }
    }
    else
    { // Use plot window.
      y1 = plot_top_;
      y2 = plot_bottom_;
    }
    image_.g(detail::PLOT_X_AXIS).line(x, y1, x, y2); // Draw vertical Y-axis line.
  }
  else
  { // Won't fit into window.  Throw or warning message?
  }
  draw_x_axis(); // Draw horizontal X-axis line.
} //  draw_axes()

void svg_1d_plot::set_ids()
{ //! Document ids for use in identifying group elements, for example: <g id = "PLOT_TITLE".../g>
  for(int i = 0; i < detail::SVG_PLOT_DOC_CHILDREN; ++i)
  {
    svg_1d_plot::image_.g(i).id(detail::document_ids_[i]);
  }
} //  void set_ids()

void  svg_1d_plot::calculate_transform()
{ //! Calculate scale and shift factors for transforming from Cartesian to SVG plot.
  //! SVG image is (0, 0) at top left, Cartesian (0, 0) at bottom left.
  x_scale_ = (plot_right_ - plot_left_) / (x_axis_.max_ - x_axis_.min_);
  x_shift_ = plot_left_ - (x_axis_.min_ * (plot_right_ - plot_left_) / (x_axis_.max_ - x_axis_.min_));
  y_scale_ = 1.;
  // y_shift_ = plot_top_ - (plot_top_ - plot_bottom_) / 2.;
  // y_shift_ = plot_top_ - (plot_top_ - plot_bottom_)  * x_axis_vertical_;  // OK at 0.5
  y_shift_ = plot_top_ - (plot_top_ - plot_bottom_) * x_axis_vertical_;
} // void calculate_transform()

// svg_1d_plot Member functions definitions.

svg_1d_plot& svg_1d_plot::write(const std::string& file)
{ /*! Write SVG image to the specified file, providing the suffix .svg if none given.

  \details write() has two versions: to an ostream and to a file.
  The stream version first clears all unnecessary data from the graph,
  builds the document tree, and then calls the write function for the root
  document node, which calls all other nodes through the Visitor pattern.

  \note This file version opens an ostream, and calls the ostream version of write.

  \return *this to make chainable.
  */
  std::string filename(file); // Copy to avoid problems with const if need to append.
  if (filename.find(".svg") == std::string::npos)
  { // No file type suffix, so provide the default .svg.
    filename.append(".svg");
  }
  std::ofstream fout(filename.c_str());
  if(fout.fail())
  {
    throw std::runtime_error("Failed to open " + filename);
  }
  image_.image_filename(filename);
  // Note filename for optional output as comment in the .svg file.
  svg_1d_plot::write(fout); // Use the ostream version.
  return *this;
}

svg_1d_plot& svg_1d_plot::write(std::ostream& s_out)
{ /*! Write SVG image to the specified std::ostream.
      \note This function also is used by the write to file function.
      \return @c *this to make chainable.
  */
  update_image();
  /*!
    The default stream precision of 6 decimal digits is probably excessive.
    4.1 Basic data types, integer or float in decimal or scientific (using E format).
    If image size is under 1000 x 1000, the SVG plot default precision of 3 is probably sufficient.
    This reduces .svg file sizes significantly for curves represented with many data points.
    For example, if a curve is shown using 100 points,
    reducing to coord_precision(3) from default of 6 will reduce file size by 300 bytes.
  */
  image_.write(s_out);
  return (svg_1d_plot&) *this;
} // write

template <typename T> //! \tparam T Floating-point type of the data (@c T must be convertible to double).
svg_1d_plot_series& svg_1d_plot::plot(const T& container, const std::string& title /*= "" */)
{ /*! Add a data series to the plot (by default, converting to unc doubles), with optional title.
    \code
std::vector<float> my_data; // my container.
my_data.push_back(2.f); // Fill container with some data.
my_data.push_back(3.f);
my_data.push_back(4.f);
my_1d_plot.plot(my_data, "All data in my container"); // Plot all data in container.
    \endcode

    \param container Container (for example vector) for the data to be added to the plot.
    \param title Optional title for the data series (default none).

    \return Reference to data series just added (to make chainable).

    \note This version assumes that \b ALL the data values in the container are used.
  */
  serieses_.push_back(
    svg_1d_plot_series(
    boost::make_transform_iterator(container.begin(), detail::meas_1d_convert()),
    boost::make_transform_iterator(container.end(), detail::meas_1d_convert()),
    //boost::make_transform_iterator(container.begin(), detail::unc_1d_convert<false>()),
    //boost::make_transform_iterator(container.end(), detail::unc_1d_convert<false>()),
    title)
  );
  return serieses_[serieses_.size() - 1];
} // plot(const T& container, const std::string& title)

template <class T>  //!  \tparam T floating-point type of the data (T must be convertible to double).
svg_1d_plot_series& svg_1d_plot::plot(const T& begin, const T& end, const std::string& title)
{ /*! Add a data series to the plot (by default, converting to unc doubles), with optional title.
    \note This version permits a partial range of the container, from begin to end, to be used.
    \return a reference to the data series just added.
    \param begin Iterator to 1st data item in container.
    \param end Iterator to one-beyond-end of data in container.
    \param title Optional title for the plot (default is no title).
  */
  serieses_.push_back(
    svg_1d_plot_series(
    boost::make_transform_iterator(begin, detail::unc_1d_convert<false>()),
    boost::make_transform_iterator(end, detail::unc_1d_convert<false>()),
    title)
  );
  /*! For example:\n
    @c my_1d_plot.plot(my_data.begin(), my_data.end(), "My container");\n
    @c my_1d_plot.plot(&my_data[1], &my_data[4], "my_data 1 to 4"); // Add part of data series

    \warning last == end  which is one past the last, so this only does 1, 2 & 3 -  \b not 4!
    */
  return serieses_[serieses_.size() - 1]; // Reference to data series just added.
} // plot


template <typename T, typename U>
/*!
    \tparam T floating-point type of the data (which must be convertible to double).
    \tparam U functor floating-point type (default is @c double_1d_convert).
  */
svg_1d_plot_series& svg_1d_plot::plot(const T& container, const std::string& title /* = "" */, U functor/*= double_1d_convert*/)
{ //! Add a data series to the plot, with optional title.
/*!
  This version of plot includes a functor, allowing other than just convert data values to double(the default).
  \param container Container for data (for example vector) that contains the data to be added to the plot.
  \param title Optional title for the plot (default is no title).
  \param functor Custom functor to convert data value to double.


  \return a reference to data series just added (to make chainable).
 */
  serieses_.push_back(
    svg_1d_plot_series(
    boost::make_transform_iterator(container.begin(), functor),
    boost::make_transform_iterator(container.end(),   functor),
    title)
  );
  return serieses_[serieses_.size() - 1]; // Reference to data series just added.
} // plot


template <typename T, typename U>
   /*!
      \tparam T floating-point type of the data (which must be convertible to double).
      \tparam U functor floating-point type (default is double_1d_convert).
    */
svg_1d_plot_series& svg_1d_plot::plot(const T& begin, const T& end, const std::string& title /* = ""*/,
   U functor /* = double_1d_convert */)
{
  /*! Add a data series to the plot, with optional title. (Version with custom functor, rather than to double).
    \note This version permits a @b partial range, begin to end, of the container to be used.

    \param begin Iterator to 1st data item in container.
    \param end Iterator to one-beyond-end of data in container.
    \param title Optional title for the plot (default is no title).
    \param functor Custom functor.
    \return a reference to data series just added (to make chainable).
  */
  serieses_.push_back(
    svg_1d_plot_series(
      boost::make_transform_iterator(begin, functor),
      boost::make_transform_iterator(end,   functor),
      title)
  );
  return serieses_[serieses_.size() - 1]; //!< \return Reference to data series just added.
} // plot


// End Definitions of svg_plot_series Public Member Functions.
} // namespace svg
} // namespace boost

#endif // BOOST_SVG_SVG_1D_PLOT_IPP
