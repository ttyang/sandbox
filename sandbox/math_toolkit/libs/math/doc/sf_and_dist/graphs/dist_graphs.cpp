//  (C) Copyright John Maddock 2008.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_MATH_OVERFLOW_ERROR_POLICY ignore_error

#include <boost/math/distributions.hpp>
#include <boost/math/tools/roots.hpp>
#include <boost/svg_plot/svg_2d_plot.hpp>
#include <list>
#include <map>
#include <string>

template <class Dist>
struct value_finder
{
   value_finder(Dist const& d, typename Dist::value_type v) 
      : m_dist(d), m_value(v) {}

   inline typename Dist::value_type operator()(const typename Dist::value_type& x)
   {
      return pdf(m_dist, x) - m_value;
   }

private:
   Dist m_dist;
   typename Dist::value_type m_value;
};

template <class Dist>
class distribution_plotter
{
public:
   distribution_plotter() : m_min_x(0), m_max_x(0), m_min_y(0), m_max_y(0) {}

   void add(const Dist& d, const std::string& name)
   {
      //
      // Add to our list for later:
      //
      m_distributions.push_back(std::make_pair(name, d));
      //
      // Get the extent:
      //
      double a, b;
      std::tr1::tie(a, b) = support(d);
      //
      // PDF maximimum is at the mode:
      //
      double mod;
      try
      { 
         mod = mode(d); 
      } 
      catch(const std::domain_error& )
      {
         mod = a;
      }
      if(mod <= a)
      {
         if(a)
            mod = a * (1 + 1e-2);
         else
            mod = 1e-2;
      }
      double peek_y = pdf(d, mod);
      double min_y = peek_y / 20;
      //
      // If the extent is "infinite" then find out how large it 
      // has to be for the PDF to decay to min_y:
      //
      if(a <= -(std::numeric_limits<double>::max)())
      {
         boost::uintmax_t max_iter = 500;
         double guess = mod;
         if((pdf(d, 0) > min_y) || (guess == 0))
            guess = -1e-3;
         a = boost::math::tools::bracket_and_solve_root(
            value_finder<Dist>(d, min_y),
            guess,
            8.0,
            true,
            boost::math::tools::eps_tolerance<double>(10),
            max_iter).first;
      }
      if(b >= (std::numeric_limits<double>::max)())
      {
         boost::uintmax_t max_iter = 500;
         double guess = mod;
         if(a <= 0)
            if((pdf(d, 0) > min_y) || (guess == 0))
               guess = 1e-3;
         b = boost::math::tools::bracket_and_solve_root(
            value_finder<Dist>(d, min_y),
            guess,
            8.0,
            false,
            boost::math::tools::eps_tolerance<double>(10),
            max_iter).first;
      }
      //
      // Recalculate peek_y and location of mod so that
      // it's not too close to one end of the graph: 
      // otherwise we may be shooting off to infinity.
      //
      if(mod <= a + (b-a)/50)
      {
         mod = a + (b-a)/50;
      }
      if(mod >= b - (b-a)/50)
      {
         mod = b - (b-a)/50;
      }
      peek_y = pdf(d, mod);
      //
      // Now set our limits:
      //
      if(peek_y > m_max_y)
         m_max_y = peek_y;
      if(m_max_x == m_min_x)
      {
         m_max_x = b;
         m_min_x = a;
      }
      else
      {
         if(a < m_min_x) 
            m_min_x = a;
         if(b > m_max_x)
            m_max_x = b;
      }
   }

   void plot(const std::string& title, const std::string& file)
   {
      using namespace boost::svg;

      static const svg_color colors[5] = 
      {
         darkblue,
         darkred,
         darkgreen,
         darkorange,
         chartreuse
      };

      svg_2d_plot plot;
      plot.image_size(750, 400);
      plot.title_font_size(20);
      plot.legend_title_font_size(15);
      plot.title(title);
      plot.legend_on(true).title_on(true);
      //plot.x_major_labels_on(true).y_major_labels_on(true);
      double x_delta = (m_max_x - m_min_x) / 10;
      double y_delta = (m_max_y - m_min_y) / 10;
      plot.x_range(m_min_x, m_max_x)
         .y_range(m_min_y, m_max_y + y_delta);
      plot.x_label_on(true).x_label("Random Variable");
      plot.y_label_on(true).y_label("Probability");
      plot.plot_border_color(lightslategray).legend_border_color(lightslategray).background_border_color(lightslategray);
      //
      // Work out axis tick intervals:
      //
      double l = std::floor(std::log10((m_max_x - m_min_x) / 10) + 0.5);
      double interval = std::pow(10.0, (int)l);
      if(((m_max_x - m_min_x) / interval) > 10)
         interval *= 5;
      plot.x_major_interval(interval);
      l = std::floor(std::log10((m_max_y - m_min_y) / 10) + 0.5);
      interval = std::pow(10.0, (int)l);
      if(((m_max_y - m_min_y) / interval) > 10)
         interval *= 5;
      plot.y_major_interval(interval);

      int color_index = 0;

      for(std::list<std::pair<std::string, Dist> >::const_iterator i = m_distributions.begin();
         i != m_distributions.end(); ++i)
      {
         double x = m_min_x;
         double interval = (m_max_x - m_min_x) / 1000;
         std::map<double, double> data;
         while(x <= m_max_x)
         {
            data[x] = pdf(i->second, x);
            x += interval;
         }
         plot.plot(data, i->first)
            .line_on(true)
            .line_color(colors[color_index])
            .line_width(0.5)
            .shape(none);
         ++color_index;
         color_index = color_index % (sizeof(colors)/sizeof(colors[0]));
      }
      plot.write(file);
   }

private:
   std::list<std::pair<std::string, Dist> > m_distributions;
   double m_min_x, m_max_x, m_min_y, m_max_y;
};

int main()
{
   distribution_plotter<boost::math::gamma_distribution<> > 
      gamma_plotter;
   gamma_plotter.add(boost::math::gamma_distribution<>(1), "shape = 0.5");
   gamma_plotter.add(boost::math::gamma_distribution<>(2), "shape = 1");
   gamma_plotter.add(boost::math::gamma_distribution<>(4), "shape = 3");
   gamma_plotter.plot("Gamma Distribution PDF With Scale = 1", "gamma1_pdf.svg");

   distribution_plotter<boost::math::gamma_distribution<> > 
      gamma_plotter2;
   gamma_plotter2.add(boost::math::gamma_distribution<>(2, 0.5), "scale = 2");
   gamma_plotter2.add(boost::math::gamma_distribution<>(2, 1), "scale = 0.5");
   gamma_plotter2.add(boost::math::gamma_distribution<>(2, 2), "scale = 2");
   gamma_plotter2.plot("Gamma Distribution PDF With Shape = 2", "gamma2_pdf.svg");

   distribution_plotter<boost::math::normal> 
      normal_plotter;
   normal_plotter.add(boost::math::normal(0, 1), "&#x3BC; = 0, &#x3C3; = 1");
   normal_plotter.add(boost::math::normal(0, 0.5), "&#x3BC; = 0, &#x3C3; = 0.5");
   normal_plotter.add(boost::math::normal(0, 2), "&#x3BC; = 0, &#x3C3; = 2");
   normal_plotter.add(boost::math::normal(-1, 1), "&#x3BC; = -1, &#x3C3; = 1");
   normal_plotter.add(boost::math::normal(1, 1), "&#x3BC; = 1, &#x3C3; = 1");
   normal_plotter.plot("Normal Distribution PDF", "normal_pdf.svg");

   distribution_plotter<boost::math::non_central_chi_squared> 
      nc_cs_plotter;
   nc_cs_plotter.add(boost::math::non_central_chi_squared(20, 0), "v=20, &#x3BB;=0");
   nc_cs_plotter.add(boost::math::non_central_chi_squared(20, 1), "v=20, &#x3BB;=1");
   nc_cs_plotter.add(boost::math::non_central_chi_squared(20, 5), "v=20, &#x3BB;=5");
   nc_cs_plotter.add(boost::math::non_central_chi_squared(20, 10), "v=20, &#x3BB;=10");
   nc_cs_plotter.add(boost::math::non_central_chi_squared(20, 20), "v=20, &#x3BB;=20");
   nc_cs_plotter.add(boost::math::non_central_chi_squared(20, 100), "v=20, &#x3BB;=100");
   nc_cs_plotter.plot("Non Central Chi Squared PDF", "nccs_pdf.svg");

   distribution_plotter<boost::math::beta_distribution<> > 
      beta_plotter;
   beta_plotter.add(boost::math::beta_distribution<>(0.5, 0.5), "alpha=0.5, beta=0.5");
   beta_plotter.add(boost::math::beta_distribution<>(5, 1), "alpha=5, beta=1");
   beta_plotter.add(boost::math::beta_distribution<>(1, 3), "alpha=1, beta=3");
   beta_plotter.add(boost::math::beta_distribution<>(2, 2), "alpha=2, beta=2");
   beta_plotter.add(boost::math::beta_distribution<>(2, 5), "alpha=2, beta=5");
   beta_plotter.plot("Beta Distribution PDF", "beta_pdf.svg");

   distribution_plotter<boost::math::cauchy_distribution<> > 
      cauchy_plotter;
   cauchy_plotter.add(boost::math::cauchy_distribution<>(-5, 1), "location = -5");
   cauchy_plotter.add(boost::math::cauchy_distribution<>(0, 1), "location = 0");
   cauchy_plotter.add(boost::math::cauchy_distribution<>(5, 1), "location = 5");
   cauchy_plotter.plot("Cauchy Distribution PDF (scale = 1)", "cauchy_pdf1.svg");

   distribution_plotter<boost::math::cauchy_distribution<> > 
      cauchy_plotter2;
   cauchy_plotter2.add(boost::math::cauchy_distribution<>(0, 0.5), "scale = 0.5");
   cauchy_plotter2.add(boost::math::cauchy_distribution<>(0, 1), "scale = 1");
   cauchy_plotter2.add(boost::math::cauchy_distribution<>(0, 2), "scale = 2");
   cauchy_plotter2.plot("Cauchy Distribution PDF (location = 0)", "cauchy_pdf2.svg");

   distribution_plotter<boost::math::chi_squared_distribution<> > 
      chi_squared_plotter;
   chi_squared_plotter.add(boost::math::chi_squared_distribution<>(1), "v=1");
   chi_squared_plotter.add(boost::math::chi_squared_distribution<>(2), "v=2");
   chi_squared_plotter.add(boost::math::chi_squared_distribution<>(5), "v=5");
   chi_squared_plotter.plot("Chi Squared Distribution PDF", "chi_squared_pdf.svg");

   distribution_plotter<boost::math::exponential_distribution<> > 
      exponential_plotter;
   exponential_plotter.add(boost::math::exponential_distribution<>(0.5), "&#x3BB;=1");
   exponential_plotter.add(boost::math::exponential_distribution<>(1), "&#x3BB;=2");
   exponential_plotter.add(boost::math::exponential_distribution<>(2), "&#x3BB;=5");
   exponential_plotter.plot("Exponential Distribution PDF", "exponential_pdf.svg");

   distribution_plotter<boost::math::extreme_value_distribution<> > 
      extreme_value_plotter;
   extreme_value_plotter.add(boost::math::extreme_value_distribution<>(-5), "location=1");
   extreme_value_plotter.add(boost::math::extreme_value_distribution<>(0), "location=2");
   extreme_value_plotter.add(boost::math::extreme_value_distribution<>(5), "location=5");
   extreme_value_plotter.plot("Extreme Value Distribution PDF (shape=1)", "extreme_value_pdf1.svg");

   distribution_plotter<boost::math::extreme_value_distribution<> > 
      extreme_value_plotter2;
   extreme_value_plotter2.add(boost::math::extreme_value_distribution<>(0, 0.5), "shape=0.5");
   extreme_value_plotter2.add(boost::math::extreme_value_distribution<>(0, 1), "shape=1");
   extreme_value_plotter2.add(boost::math::extreme_value_distribution<>(0, 2), "shape=2");
   extreme_value_plotter2.plot("Extreme Value Distribution PDF (location=0)", "extreme_value_pdf2.svg");

   distribution_plotter<boost::math::fisher_f_distribution<> > 
      fisher_f_plotter;
   fisher_f_plotter.add(boost::math::fisher_f_distribution<>(4, 4), "n=4, m=4");
   fisher_f_plotter.add(boost::math::fisher_f_distribution<>(10, 4), "n=10, m=4");
   fisher_f_plotter.add(boost::math::fisher_f_distribution<>(10, 10), "n=10, m=10");
   fisher_f_plotter.add(boost::math::fisher_f_distribution<>(4, 10), "n=4, m=10");
   fisher_f_plotter.plot("F Distribution PDF", "fisher_f_pdf.svg");

   distribution_plotter<boost::math::lognormal_distribution<> > 
      lognormal_plotter;
   lognormal_plotter.add(boost::math::lognormal_distribution<>(-1), "location=-1");
   lognormal_plotter.add(boost::math::lognormal_distribution<>(0), "location=0");
   lognormal_plotter.add(boost::math::lognormal_distribution<>(1), "location=1");
   lognormal_plotter.plot("Lognormal Distribution PDF (scale=1)", "lognormal_pdf1.svg");

   distribution_plotter<boost::math::lognormal_distribution<> > 
      lognormal_plotter2;
   lognormal_plotter2.add(boost::math::lognormal_distribution<>(0, 0.5), "scale=0.5");
   lognormal_plotter2.add(boost::math::lognormal_distribution<>(0, 1), "scale=1");
   lognormal_plotter2.add(boost::math::lognormal_distribution<>(0, 2), "scale=2");
   lognormal_plotter2.plot("Lognormal Distribution PDF (location=0)", "lognormal_pdf2.svg");

   distribution_plotter<boost::math::pareto_distribution<> > 
      pareto_plotter;
   pareto_plotter.add(boost::math::pareto_distribution<>(1), "location=1");
   pareto_plotter.add(boost::math::pareto_distribution<>(2), "location=2");
   pareto_plotter.add(boost::math::pareto_distribution<>(3), "location=3");
   pareto_plotter.plot("Pareto Distribution PDF (scale=1)", "pareto_pdf1.svg");

   distribution_plotter<boost::math::pareto_distribution<> > 
      pareto_plotter2;
   pareto_plotter2.add(boost::math::pareto_distribution<>(1, 0.5), "scale=0.5");
   pareto_plotter2.add(boost::math::pareto_distribution<>(1, 1), "scale=1");
   pareto_plotter2.add(boost::math::pareto_distribution<>(1, 2), "scale=2");
   pareto_plotter2.plot("Pareto Distribution PDF (location=1)", "pareto_pdf2.svg");

   distribution_plotter<boost::math::rayleigh_distribution<> > 
      rayleigh_plotter;
   rayleigh_plotter.add(boost::math::rayleigh_distribution<>(0.5), "&#x3C3;=0.5");
   rayleigh_plotter.add(boost::math::rayleigh_distribution<>(1), "&#x3C3;=1");
   rayleigh_plotter.add(boost::math::rayleigh_distribution<>(2), "&#x3C3;=2");
   rayleigh_plotter.add(boost::math::rayleigh_distribution<>(4), "&#x3C3;=4");
   rayleigh_plotter.add(boost::math::rayleigh_distribution<>(10), "&#x3C3;=10");
   rayleigh_plotter.plot("Rayleigh Distribution PDF", "rayleigh_pdf.svg");

   distribution_plotter<boost::math::triangular_distribution<> > 
      triangular_plotter;
   triangular_plotter.add(boost::math::triangular_distribution<>(-1,0,1), "{-1,0,1}");
   triangular_plotter.add(boost::math::triangular_distribution<>(0,1,1), "{0,1,1}");
   triangular_plotter.add(boost::math::triangular_distribution<>(0,1,3), "{0,1,3}");
   triangular_plotter.add(boost::math::triangular_distribution<>(0,0.5,1), "{0,0.5,1}");
   triangular_plotter.add(boost::math::triangular_distribution<>(-2,0,3), "{-2,0,3}");
   triangular_plotter.plot("Triangular Distribution PDF", "triangular_pdf.svg");

   distribution_plotter<boost::math::students_t_distribution<> > 
      students_t_plotter;
   students_t_plotter.add(boost::math::students_t_distribution<>(1), "v=1");
   students_t_plotter.add(boost::math::students_t_distribution<>(5), "v=5");
   students_t_plotter.add(boost::math::students_t_distribution<>(30), "v=30");
   students_t_plotter.plot("Students T Distribution PDF", "students_t_pdf.svg");

   distribution_plotter<boost::math::weibull_distribution<> > 
      weibull_plotter;
   weibull_plotter.add(boost::math::weibull_distribution<>(0.2), "shape=0.2");
   weibull_plotter.add(boost::math::weibull_distribution<>(1), "shape=1");
   weibull_plotter.add(boost::math::weibull_distribution<>(5), "shape=5");
   weibull_plotter.plot("Weibull Distribution PDF (scale=1)", "weibull_pdf1.svg");

   distribution_plotter<boost::math::weibull_distribution<> > 
      weibull_plotter2;
   weibull_plotter2.add(boost::math::weibull_distribution<>(3, 0.5), "scale=0.5");
   weibull_plotter2.add(boost::math::weibull_distribution<>(3, 1), "scale=1");
   weibull_plotter2.add(boost::math::weibull_distribution<>(3, 2), "scale=2");
   weibull_plotter2.plot("weibull Distribution PDF (shape=3)", "weibull_pdf2.svg");

   distribution_plotter<boost::math::uniform_distribution<> > 
      uniform_plotter;
   uniform_plotter.add(boost::math::uniform_distribution<>(0, 1), "{0,1}");
   uniform_plotter.add(boost::math::uniform_distribution<>(0, 3), "{0,3}");
   uniform_plotter.add(boost::math::uniform_distribution<>(-2, 3), "{-2,3}");
   uniform_plotter.add(boost::math::uniform_distribution<>(-1, 1), "{-1,1}");
   uniform_plotter.plot("Uniform Distribution PDF", "uniform_pdf.svg");

}
