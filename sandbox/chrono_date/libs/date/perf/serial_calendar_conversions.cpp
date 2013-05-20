//  Copyright 2013 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#include <boost/chrono/date.hpp>
#include <boost/chrono/date/conversions.hpp>

using namespace boost::chrono;
const int Ymin = 1900;
const int Ymax = 4100;
volatile int y;
volatile int m;
volatile int d;
volatile boost::int_least16_t m16;
volatile boost::int_least16_t d16;

#if 1
void empty_unchecked_ymd_dcl()
{
  int count = 0;
  int ycount = 0;
  auto t0 = boost::chrono::high_resolution_clock::now();
  for (int y = Ymin; y <= Ymax; ++y)
  {
    bool is_l = year(y).is_leap();
    for (int m = 1; m <= 12; ++m)
    {
      int last = unchecked::month(m).days_in(is_l).count();
      for (int d = 1; d <= last; ++d)
      {
        unchecked::ymd_date dt;
        ycount+= unchecked::day(dt);
        ++count;
      }
    }
  }
  auto t1 = boost::chrono::high_resolution_clock::now();
  typedef boost::chrono::duration<float, boost::nano> sec;
  auto encode = t1 - t0;
  std::cout << "default unchecked calendar " << sec(encode).count() / count << " " << ycount << '\n';
}

void empty_checked_ymd_dcl()
{
  int count = 0;
  int ycount = 0;
  auto t0 = boost::chrono::high_resolution_clock::now();
  for (int y = Ymin; y <= Ymax; ++y)
  {
    bool is_l = year(y).is_leap();
    for (int m = 1; m <= 12; ++m)
    {
      int last = unchecked::month(m).days_in(is_l).count();
      for (int d = 1; d <= last; ++d)
      {
        ymd_date dt;
        ycount+= day(dt);
        ++count;
      }
    }
  }
  auto t1 = boost::chrono::high_resolution_clock::now();
  typedef boost::chrono::duration<float, boost::nano> sec;
  auto encode = t1 - t0;
  std::cout << "default checked calendar   " << sec(encode).count() / count << " " << ycount << '\n';
}
#endif
void unchecked_ymd_dcl()
{
  int count = 0;
  int ycount = 0;
  auto t0 = boost::chrono::high_resolution_clock::now();
  for (int y = Ymin; y <= Ymax; ++y)
  {
    bool is_l = year(y).is_leap();
    for (int m = 1; m <= 12; ++m)
    {
      int last = unchecked::month(m).days_in(is_l).count();
      for (int d = 1; d <= last; ++d)
      {
#if 1
        unchecked::ymd_date dt(
            (year(y)),
            unchecked::month(m),
            unchecked::day(d)
        );
        ycount+= unchecked::day(dt)+unchecked::month(dt)+year(dt);
#else
        //ymd_date dt((year(y)), month(m), day(d));
        //ymd_date dt((year(y)), month(m), day(d, no_check));
        //ymd_date dt((year(y)), month(m, no_check), day(d));
        //ymd_date dt((year(y)), month(m, no_check), day(d, no_check));
        ymd_date dt((year(y)), month(m, no_check), day(d, no_check), no_check);
        //ymd_date dt((year(y)), month_day(month(m, no_check), day(d, no_check), no_check));
        //ymd_date dt((year_month(year(y), month(m, no_check))), day(d, no_check));
        ycount+= day(dt)+month(dt)+year(dt);
#endif
        ++count;
      }
    }
  }
  auto t1 = boost::chrono::high_resolution_clock::now();
  typedef boost::chrono::duration<float, boost::nano> sec;
  auto encode = t1 - t0;
  std::cout << "unchecked calendar " << sec(encode).count() / count << " " << ycount << '\n';
}
#if 1

void checked_month_ymd_dcl()
{
  int count = 0;
  int ycount = 0;
  auto t0 = boost::chrono::high_resolution_clock::now();
  for (int y = Ymin; y <= Ymax; ++y)
  {
    bool is_l = year(y).is_leap();
    for (int m = 1; m <= 12; ++m)
    {
      int last = unchecked::month(m).days_in(is_l).count();
      for (int d = 1; d <= last; ++d)
      {
        ymd_date dt((year(y)), month(m), day(d));
        //ymd_date dt((year(y)), month(m), day(d, no_check));
        //ymd_date dt((year(y)), month(m, no_check), day(d));
        //ymd_date dt((year(y)), month(m, no_check), day(d, no_check));
        ycount+= day(dt);
        ++count;
      }
    }
  }
  auto t1 = boost::chrono::high_resolution_clock::now();
  typedef boost::chrono::duration<float, boost::nano> sec;
  auto encode = t1 - t0;
  std::cout << "checked month calendar   " << sec(encode).count() / count << " " << ycount << '\n';
}
void checked_ymd_dcl()
{
  int count = 0;
  int ycount = 0;
  auto t0 = boost::chrono::high_resolution_clock::now();
  for (int y = Ymin; y <= Ymax; ++y)
  {
    bool is_l = year(y).is_leap();
    for (int m = 1; m <= 12; ++m)
    {
      int last = unchecked::month(m).days_in(is_l).count();
      for (int d = 1; d <= last; ++d)
      {
        ymd_date dt((year(y)), month(m), day(d));
        ycount+= day(dt);
        ++count;
      }
    }
  }
  auto t1 = boost::chrono::high_resolution_clock::now();
  typedef boost::chrono::duration<float, boost::nano> sec;
  auto encode = t1 - t0;
  std::cout << "checked month/day calendar   " << sec(encode).count() / count << " " << ycount << '\n';
}
void checked_day_ymd_dcl()
{
  int count = 0;
  int ycount = 0;
  auto t0 = boost::chrono::high_resolution_clock::now();
  for (int y = Ymin; y <= Ymax; ++y)
  {
    bool is_l = year(y).is_leap();
    for (int m = 1; m <= 12; ++m)
    {
      int last = unchecked::month(m).days_in(is_l).count();
      //month pm(m, no_check);
      for (int d = 1; d <= last; ++d)
      {
        //ymd_date dt((year(y)), month(m, no_check), day(d));
        ymd_date dt((year(y)), month(m), day(d));
        //ymd_date dt((year(y)), pm, day(d));
        ycount+= day(dt);
        ++count;
      }
    }
  }
  auto t1 = boost::chrono::high_resolution_clock::now();
  typedef boost::chrono::duration<float, boost::nano> sec;
  auto encode = t1 - t0;
  std::cout << "checked day calendar   " << sec(encode).count() / count << " " << ycount << '\n';
}

void checked_unchecked_ymd_dcl()
{
  int count = 0;
  int ycount = 0;
  auto t0 = boost::chrono::high_resolution_clock::now();
  for (int y = Ymin; y <= Ymax; ++y)
  {
    bool is_l = year(y).is_leap();
    for (int m = 1; m <= 12; ++m)
    {
      int last = unchecked::month(m).days_in(is_l).count();
      for (int d = 1; d <= last; ++d)
      {
        ymd_date dt((year(y)), month(m), day(d));
        unchecked::ymd_date dt2 = dt;
        ycount+= unchecked::day(dt2);
        ++count;
      }
    }
  }
  auto t1 = boost::chrono::high_resolution_clock::now();
  typedef boost::chrono::duration<float, boost::nano> sec;
  auto encode = t1 - t0;
  std::cout << "calendar -> unchecked calendar " << sec(encode).count() / count << " " << ycount << '\n';
}

void unchecked_checked_ymd_dcl()
{
  int count = 0;
  int ycount = 0;
  auto t0 = boost::chrono::high_resolution_clock::now();
  for (int y = Ymin; y <= Ymax; ++y)
  {
    bool is_l = year(y).is_leap();
    for (int m = 1; m <= 12; ++m)
    {
      int last = unchecked::month(m).days_in(is_l).count();
      for (int d = 1; d <= last; ++d)
      {
        unchecked::ymd_date dt((year(y)), unchecked::month(m), unchecked::day(d));
        ymd_date dt2(dt);
        ycount+= day(dt2);
        ++count;
      }
    }
  }
  auto t1 = boost::chrono::high_resolution_clock::now();
  typedef boost::chrono::duration<float, boost::nano> sec;
  auto encode = t1 - t0;
  std::cout << "unchecked calendar -> calendar " << sec(encode).count() / count << " " << ycount << '\n';
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
        (void)ds;
        ++count;
      }
    }
  }
  auto t1 = boost::chrono::high_resolution_clock::now();
  typedef boost::chrono::duration<float, boost::nano> sec;
  auto encode = t1 - t0;
  std::cout << "calendar -> serial raw   " << sec(encode).count() / count << '\n';
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
        (void)ds;
        ++count;
      }
    }
  }
  auto t1 = boost::chrono::high_resolution_clock::now();
  typedef boost::chrono::duration<float, boost::nano> sec;
  auto encode = t1 - t0;
  std::cout << "calendar -> serial space " << sec(encode).count() / count << '\n';
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
        volatile days::rep ds = days_date(unchecked::ymd_date(year(y), unchecked::month(m), unchecked::day(d))).days_since_epoch().count();
        (void)ds;
        ++count;
      }
    }
  }
  auto t1 = boost::chrono::high_resolution_clock::now();
  typedef boost::chrono::duration<float, boost::nano> sec;
  auto encode = t1 - t0;
  std::cout << "calendar -> serial class " << sec(encode).count() / count << '\n';
}


void empty_decoding_perf()
{

  const int k0 = days_date(year(Ymin)/month(1)/day(1)).days_since_epoch().count();
  const int k1 = days_date(year(Ymax)/month(12)/day(31)).days_since_epoch().count();
  int count = 0;
  int ycount = 0;
  int y2count = 0;
  auto t0 = boost::chrono::high_resolution_clock::now();
  for (int k = k0; k <= k1; ++k)
  {
    days_date dt((days(k)));
    ycount+= dt.days_since_epoch().count();
    y2count+= k;
    ++count;

  }
  auto t1 = boost::chrono::high_resolution_clock::now();
  typedef boost::chrono::duration<float, boost::nano> sec;
  auto decode = t1 - t0;
  std::cout << "serial  empty            " << sec(decode).count() / count << " " << ycount <<" " << y2count << '\n';
}
void raw_decoding_perf()
{

  const int k0 = days_date(year(Ymin)/month(1)/day(1)).days_since_epoch().count();
  const int k1 = days_date(year(Ymax)/month(12)/day(31)).days_since_epoch().count();
  int count = 0;
  int ycount = 0;
  int y2count = 0;
  auto t0 = boost::chrono::high_resolution_clock::now();
  for (int k = k0; k <= k1; ++k)
  {
    days_date dt1((days(k)));
    to_ymd(const_cast<days_date&>(dt1).days_since_epoch().count(), const_cast<int&>(y),const_cast<int &>(m),const_cast<int&>(d));
    ycount+= dt1.days_since_epoch().count();
    y2count+= k;
    ++count;

  }
  auto t1 = boost::chrono::high_resolution_clock::now();
  typedef boost::chrono::duration<float, boost::nano> sec;
  auto decode = t1 - t0;
  std::cout << "serial -> calendar raw   " << sec(decode).count() / count << " " << ycount <<" " << y2count << '\n';
}

void raw_space_decoding_perf()
{

  const int k0 = days_date(year(Ymin)/month(1)/day(1)).days_since_epoch().count();
  const int k1 = days_date(year(Ymax)/month(12)/day(31)).days_since_epoch().count();
  int count = 0;
  int ycount = 0;
  int y2count = 0;
  auto t0 = boost::chrono::high_resolution_clock::now();
  for (int k = k0; k <= k1; ++k)
  {
    days_date dt1((days(k)));
    to_ymd(const_cast<days_date&>(dt1).days_since_epoch().count(), const_cast<boost::int_least32_t&>(y),const_cast<boost::int_least16_t &>(m16),const_cast<boost::int_least16_t&>(d16));
    ycount+= dt1.days_since_epoch().count();
    y2count+= k;
    ++count;

  }
  auto t1 = boost::chrono::high_resolution_clock::now();
  typedef boost::chrono::duration<float, boost::nano> sec;
  auto decode = t1 - t0;
  std::cout << "serial -> calendar space " << sec(decode).count() / count << " " << ycount <<" " << y2count << '\n';
}

void class_decoding_perf()
{

  const int k0 = days_date(year(Ymin)/month(1)/day(1)).days_since_epoch().count();
  const int k1 = days_date(year(Ymax)/month(12)/day(31)).days_since_epoch().count();
  int count = 0;
  int ycount = 0;
  int y2count = 0;
  auto t0 = boost::chrono::high_resolution_clock::now();
  for (int k = k0; k <= k1; ++k)
  {
    days_date dt1((days(k)));
    ymd_date dt2(const_cast<days_date&>(dt1));
    ycount+= dt1.days_since_epoch().count();
    y2count+= day(dt2);
    ++count;

  }
  auto t1 = boost::chrono::high_resolution_clock::now();
  typedef boost::chrono::duration<float, boost::nano> sec;
  auto decode = t1 - t0;
  std::cout << "serial ->           calendar           class " << sec(decode).count() / count << " " << ycount <<" " << y2count << '\n';
}

void class_decoding_encoding_perf()
{

  const int k0 = days_date(year(Ymin)/month(1)/day(1)).days_since_epoch().count();
  const int k1 = days_date(year(Ymax)/month(12)/day(31)).days_since_epoch().count();
  int count = 0;
  int ycount = 0;
  int y2count = 0;
  auto t0 = boost::chrono::high_resolution_clock::now();
  for (int k = k0; k <= k1; ++k)
  {
    days_date dt1((days(k)));
    ymd_date dt2(const_cast<days_date&>(dt1));
    days_date dt3(dt2);
    ycount+= dt1.days_since_epoch().count();
    y2count+= (dt1==dt3);
    ++count;

  }
  auto t1 = boost::chrono::high_resolution_clock::now();
  typedef boost::chrono::duration<float, boost::nano> sec;
  auto decode = t1 - t0;
  std::cout << "serial ->           calendar -> serial class " << sec(decode).count() / count << " " << ycount <<" " << count <<" " << y2count << '\n';
}

void unchecked_class_decoding_perf()
{

  const int k0 = days_date(year(Ymin)/month(1)/day(1)).days_since_epoch().count();
  const int k1 = days_date(year(Ymax)/month(12)/day(31)).days_since_epoch().count();
  int count = 0;
  int ycount = 0;
  int y2count = 0;
  auto t0 = boost::chrono::high_resolution_clock::now();
  for (int k = k0; k <= k1; ++k)
  {
    days_date dt1((days(k)));
    unchecked::ymd_date dt2(const_cast<days_date&>(dt1));
    ycount+= dt1.days_since_epoch().count();
    y2count+= unchecked::day(dt2);
    ++count;

  }
  auto t1 = boost::chrono::high_resolution_clock::now();
  typedef boost::chrono::duration<float, boost::nano> sec;
  auto decode = t1 - t0;
  std::cout << "serial -> unchecked calendar           class " << sec(decode).count() / count << " " << ycount <<" " << y2count << '\n';
}
void unchecked_class_decoding_encoding_perf()
{

  const int k0 = days_date(year(Ymin)/month(1)/day(1)).days_since_epoch().count();
  const int k1 = days_date(year(Ymax)/month(12)/day(31)).days_since_epoch().count();
  int count = 0;
  int ycount = 0;
  int y2count = 0;
  auto t0 = boost::chrono::high_resolution_clock::now();
  for (int k = k0; k <= k1; ++k)
  {
    days_date dt1((days(k)));
    unchecked::ymd_date dt2(const_cast<days_date&>(dt1));
    days_date dt3(dt2);
    ycount+= dt1.days_since_epoch().count();
    y2count+= (dt1==dt3);
    ++count;

  }
  auto t1 = boost::chrono::high_resolution_clock::now();
  typedef boost::chrono::duration<float, boost::nano> sec;
  auto decode = t1 - t0;
  std::cout << "serial -> unchecked calendar -> serial class " << sec(decode).count() / count << " " << ycount <<" " << count <<" " << y2count << '\n';
}

void class_encoding_decoding_perf()
{
  int count = 0;
  int ycount = 0;
  int y2count = 0;
  auto t0 = boost::chrono::high_resolution_clock::now();
  for (int y = Ymin; y <= Ymax; ++y)
  {
    bool is_l = year(y).is_leap();
    for (int m = 1; m <= 12; ++m)
    {
      int last = month(m).days_in(is_l).count();
      for (int d = 1; d <= last; ++d)
      {
        ymd_date dt1=ymd_date(year(y), month(m), day(d));
        days_date dt2(dt1);
        ymd_date dt3(dt2);
        ycount+= dt2.days_since_epoch().count();
        y2count+= (dt1==dt3);
        ++count;
      }
    }
  }
  auto t1 = boost::chrono::high_resolution_clock::now();
  typedef boost::chrono::duration<float, boost::nano> sec;
  auto encode = t1 - t0;
  std::cout << "          calendar -> serial ->           calendar " << sec(encode).count() / count << " " << ycount <<" " << count <<" " << y2count << '\n';
}
void unchecked_class_encoding_decoding_perf()
{
  int count = 0;
  int ycount = 0;
  int y2count = 0;
  auto t0 = boost::chrono::high_resolution_clock::now();
  for (int y = Ymin; y <= Ymax; ++y)
  {
    bool is_l = year(y).is_leap();
    for (int m = 1; m <= 12; ++m)
    {
      int last = month(m).days_in(is_l).count();
      for (int d = 1; d <= last; ++d)
      {
        unchecked::ymd_date dt1=unchecked::ymd_date(year(y), unchecked::month(m), unchecked::day(d));
        days_date dt2(dt1);
        unchecked::ymd_date dt3(dt2);
        ycount+= dt2.days_since_epoch().count();
        y2count+= (dt1==dt3);
        ++count;
      }
    }
  }
  auto t1 = boost::chrono::high_resolution_clock::now();
  typedef boost::chrono::duration<float, boost::nano> sec;
  auto encode = t1 - t0;
  std::cout << "unchecked calendar -> serial -> unchecked calendar " << sec(encode).count() / count << " " << ycount <<" " << count <<" " << y2count << '\n';
}
#endif

int main()
{
  empty_checked_ymd_dcl();
  empty_checked_ymd_dcl();
  empty_checked_ymd_dcl();
  empty_checked_ymd_dcl();
  empty_checked_ymd_dcl();
  empty_unchecked_ymd_dcl();
  empty_unchecked_ymd_dcl();
  empty_unchecked_ymd_dcl();
  empty_unchecked_ymd_dcl();
  empty_unchecked_ymd_dcl();
  checked_day_ymd_dcl();
  checked_day_ymd_dcl();
  checked_day_ymd_dcl();
  checked_day_ymd_dcl();
  checked_day_ymd_dcl();
  checked_ymd_dcl();
  checked_ymd_dcl();
  checked_ymd_dcl();
  checked_ymd_dcl();
  checked_ymd_dcl();
  checked_ymd_dcl();
  checked_ymd_dcl();
  checked_ymd_dcl();
  checked_ymd_dcl();
  checked_ymd_dcl();
  checked_day_ymd_dcl();
  checked_day_ymd_dcl();
  checked_day_ymd_dcl();
  checked_day_ymd_dcl();
  checked_day_ymd_dcl();
  checked_month_ymd_dcl();
  checked_month_ymd_dcl();
  checked_month_ymd_dcl();
  checked_month_ymd_dcl();
  checked_month_ymd_dcl();
  unchecked_ymd_dcl();
  unchecked_ymd_dcl();
  unchecked_ymd_dcl();
  unchecked_ymd_dcl();
  unchecked_ymd_dcl();
  unchecked_ymd_dcl();
  unchecked_ymd_dcl();
  unchecked_ymd_dcl();
  unchecked_ymd_dcl();
  unchecked_ymd_dcl();
  unchecked_ymd_dcl();
  unchecked_ymd_dcl();
  unchecked_ymd_dcl();
  unchecked_ymd_dcl();
  unchecked_ymd_dcl();
  unchecked_ymd_dcl();
  unchecked_ymd_dcl();
  unchecked_ymd_dcl();
  unchecked_ymd_dcl();
  unchecked_ymd_dcl();
  checked_unchecked_ymd_dcl();
  checked_unchecked_ymd_dcl();
  checked_unchecked_ymd_dcl();
  checked_unchecked_ymd_dcl();
  checked_unchecked_ymd_dcl();
  unchecked_checked_ymd_dcl();
  unchecked_checked_ymd_dcl();
  unchecked_checked_ymd_dcl();
  unchecked_checked_ymd_dcl();
  unchecked_checked_ymd_dcl();
  empty_checked_ymd_dcl();
  empty_unchecked_ymd_dcl();
  checked_ymd_dcl();
  unchecked_ymd_dcl();
  checked_unchecked_ymd_dcl();
  raw_encoding_perf();
  raw_space_encoding_perf();
  class_encoding_perf();
  empty_decoding_perf();
  raw_decoding_perf();
  raw_space_decoding_perf();
  class_decoding_perf();
  class_decoding_encoding_perf();
  unchecked_class_decoding_perf();
  unchecked_class_decoding_encoding_perf();
  class_decoding_perf();
  class_decoding_encoding_perf();

  empty_checked_ymd_dcl();
  empty_unchecked_ymd_dcl();
  checked_ymd_dcl();
  unchecked_ymd_dcl();
  checked_unchecked_ymd_dcl();
  empty_checked_ymd_dcl();
  empty_unchecked_ymd_dcl();
  checked_ymd_dcl();
  unchecked_ymd_dcl();
  checked_unchecked_ymd_dcl();
  raw_encoding_perf();
  raw_space_encoding_perf();
  class_encoding_perf();
  empty_decoding_perf();
  raw_decoding_perf();
  raw_space_decoding_perf();
  class_decoding_perf();
  class_decoding_encoding_perf();
  unchecked_class_decoding_perf();
  unchecked_class_decoding_encoding_perf();
  class_decoding_perf();
  class_decoding_encoding_perf();
  class_decoding_encoding_perf();
  class_decoding_encoding_perf();
  class_decoding_encoding_perf();
  class_decoding_encoding_perf();
  unchecked_class_decoding_encoding_perf();
  unchecked_class_decoding_encoding_perf();
  unchecked_class_decoding_encoding_perf();
  unchecked_class_decoding_encoding_perf();
  unchecked_class_decoding_encoding_perf();
  unchecked_class_decoding_encoding_perf();

  class_encoding_decoding_perf();
  class_encoding_decoding_perf();
  class_encoding_decoding_perf();
  class_encoding_decoding_perf();
  class_encoding_decoding_perf();
  unchecked_class_encoding_decoding_perf();
  unchecked_class_encoding_decoding_perf();
  unchecked_class_encoding_decoding_perf();
  unchecked_class_encoding_decoding_perf();
  unchecked_class_encoding_decoding_perf();
  return 1;
}

