//  Copyright 2011 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#include <boost/chrono/date.hpp>
#include <boost/chrono/date/conversions.hpp>

//namespace boost
//{
//  namespace chrono
//  {
//inline days::rep to_days(int y, int m, int d) BOOST_NOEXCEPT
//{
//  bool leap = is_leap(y);
//  year::rep by = y - 32799;
//  return days_before_year(by) +
//      days_in_year_before(leap,m-1) +
//      d;
//}
//  }}

using namespace boost::chrono;
const int Ymin = 1900;
const int Ymax = 2100;
volatile int y;
volatile int m;
volatile int d;
volatile boost::int_least16_t m16;
volatile boost::int_least16_t d16;

//#define VOLATILE
//#define CHECK_IS_VALID(d) if(d.is_valid())

#define VOLATILE volatile
#define CHECK_IS_VALID(d)


void empty_encoding_perf()
{
  int count = 0;
  auto t0 = boost::chrono::high_resolution_clock::now();
  for (int y = Ymin; y <= Ymax; ++y)
  {
    bool is_l = year(y).is_leap();
    for (int m = 1; m <= 12; ++m)
    {
      int last = month(m).days_in(is_l).count();
      for (int d = 1; d <= last; ++d)
      {
        ++count;
      }
    }
  }
  auto t1 = boost::chrono::high_resolution_clock::now();
  typedef boost::chrono::duration<float, boost::nano> sec;
  auto encode = t1 - t0;
  //std::cout << encode.count() / count << '\n';
  std::cout << "ENCODE empty " << sec(encode).count() / count << '\n';
}

void raw_encoding_perf()
{
  int count = 0;
  auto t0 = boost::chrono::high_resolution_clock::now();
  for (int y = Ymin; y <= Ymax; ++y)
  {
    bool is_l = year(y).is_leap();
    for (int m = 1; m <= 12; ++m)
    {
      int last = month(m).days_in(is_l).count();
      for (int d = 1; d <= last; ++d)
      {
        volatile days::rep ds = to_days(y, m, d);
        ++count;
      }
    }
  }
  auto t1 = boost::chrono::high_resolution_clock::now();
  typedef boost::chrono::duration<float, boost::nano> sec;
  auto encode = t1 - t0;
  //std::cout << encode.count() / count << '\n';
  std::cout << "ENCODE raw   " << sec(encode).count() / count << '\n';
}

void raw_space_encoding_perf()
{
  int count = 0;
  auto t0 = boost::chrono::high_resolution_clock::now();
  for (int y = Ymin; y <= Ymax; ++y)
  {
    bool is_l = year(y).is_leap();
    for (int m = 1; m <= 12; ++m)
    {
      int last = month(m).days_in(is_l).count();
      for (int d = 1; d <= last; ++d)
      {
        volatile days::rep ds = to_days((boost::int_least32_t)y, (boost::int_least16_t)m, (boost::int_least16_t)d);
        ++count;
      }
    }
  }
  auto t1 = boost::chrono::high_resolution_clock::now();
  typedef boost::chrono::duration<float, boost::nano> sec;
  auto encode = t1 - t0;
  //std::cout << encode.count() / count << '\n';
  std::cout << "ENCODE space " << sec(encode).count() / count << '\n';
}

void class_encoding_perf()
{
  int count = 0;
  auto t0 = boost::chrono::high_resolution_clock::now();
  for (int y = Ymin; y <= Ymax; ++y)
  {
    bool is_l = year(y).is_leap();
    for (int m = 1; m <= 12; ++m)
    {
      int last = month(m).days_in(is_l).count();
      for (int d = 1; d <= last; ++d)
      {
        volatile days::rep ds = days_date(ymd_date(year(y), month(m), d)).days_since_epoch().count();

        ++count;
      }
    }
  }
  auto t1 = boost::chrono::high_resolution_clock::now();
  typedef boost::chrono::duration<float, boost::nano> sec;
  auto encode = t1 - t0;
  //std::cout << encode.count() / count << '\n';
  std::cout << "ENCODE class " << sec(encode).count() / count << '\n';
}

void empty_decoding_perf()
{

  const int k0 = days_date(year(Ymin)/month(1)/1).days_since_epoch().count();
  const int k1 = days_date(year(Ymax)/month(12)/31).days_since_epoch().count();
  int count = 0;
  auto t0 = boost::chrono::high_resolution_clock::now();
  for (int k = k0; k <= k1; ++k)
  {
    VOLATILE days_date dt1((days(k)));
    ++count;

  }
  auto t1 = boost::chrono::high_resolution_clock::now();
  typedef boost::chrono::duration<float, boost::nano> sec;
  auto decode = t1 - t0;
  //std::cout << decode.count() / count << '\n';
  std::cout << "DECODE empty " << sec(decode).count() / count << '\n';
}
void raw_decoding_perf()
{

  const int k0 = days_date(year(Ymin)/month(1)/1).days_since_epoch().count();
  const int k1 = days_date(year(Ymax)/month(12)/31).days_since_epoch().count();
  int count = 0;
  auto t0 = boost::chrono::high_resolution_clock::now();
  for (int k = k0; k <= k1; ++k)
  {
    VOLATILE days_date dt1((days(k)));
    to_ymd(const_cast<days_date&>(dt1).days_since_epoch().count(), const_cast<int&>(y),const_cast<int &>(m),const_cast<int&>(d));
    ++count;

  }
  auto t1 = boost::chrono::high_resolution_clock::now();
  typedef boost::chrono::duration<float, boost::nano> sec;
  auto decode = t1 - t0;
  //std::cout << decode.count() / count << '\n';
  std::cout << "DECODE raw   " << sec(decode).count() / count << '\n';
}

void raw_space_decoding_perf()
{

  const int k0 = days_date(year(Ymin)/month(1)/1).days_since_epoch().count();
  const int k1 = days_date(year(Ymax)/month(12)/31).days_since_epoch().count();
  int count = 0;
  auto t0 = boost::chrono::high_resolution_clock::now();
  for (int k = k0; k <= k1; ++k)
  {
    VOLATILE days_date dt1((days(k)));
    to_ymd(const_cast<days_date&>(dt1).days_since_epoch().count(), const_cast<boost::int_least32_t&>(y),const_cast<boost::int_least16_t &>(m16),const_cast<boost::int_least16_t&>(d16));
    ++count;

  }
  auto t1 = boost::chrono::high_resolution_clock::now();
  typedef boost::chrono::duration<float, boost::nano> sec;
  auto decode = t1 - t0;
  //std::cout << decode.count() / count << '\n';
  std::cout << "DECODE space " << sec(decode).count() / count << '\n';
}

void class_decoding_perf()
{

  const int k0 = days_date(year(Ymin)/month(1)/1).days_since_epoch().count();
  const int k1 = days_date(year(Ymax)/month(12)/31).days_since_epoch().count();
  int count = 0;
  auto t0 = boost::chrono::high_resolution_clock::now();
  for (int k = k0; k <= k1; ++k)
  {
    VOLATILE days_date dt1((days(k)));
    VOLATILE ymd_date dt2(const_cast<days_date&>(dt1));
    ++count;

  }
  auto t1 = boost::chrono::high_resolution_clock::now();
  typedef boost::chrono::duration<float, boost::nano> sec;
  auto decode = t1 - t0;
  //std::cout << decode.count() / count << '\n';
  std::cout << "DECODE class " << sec(decode).count() / count << '\n';
}

int main()
{
  empty_encoding_perf();
  raw_encoding_perf();
  raw_space_encoding_perf();
  class_encoding_perf();
  empty_decoding_perf();
  raw_decoding_perf();
  raw_space_decoding_perf();
  class_decoding_perf();

  return 1;
}

