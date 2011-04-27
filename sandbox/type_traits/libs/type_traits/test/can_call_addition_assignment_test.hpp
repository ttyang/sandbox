//  (C) Copyright Frederic Bron 2009-2011.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

namespace {

void run2() {
   // test with only one template parameter
   TEST_T(void, false);
   TEST_T(bool, true);
   TEST_T(char, true);
   TEST_T(signed char, true);
   TEST_T(short int, true);
   TEST_T(int, true);
   TEST_T(long int, true);
   TEST_T(unsigned char, true);
   TEST_T(unsigned short int, true);
   TEST_T(unsigned int, true);
   TEST_T(unsigned long int, true);
   TEST_T(wchar_t, true);
   TEST_T(float, true);
   TEST_T(double, true);
   TEST_T(long double, true);
   TEST_T(void, false);
#	undef CV
#	define CV(T) const T
   TEST_T(CV(bool), false);
   TEST_T(CV(int), false);
   TEST_T(CV(double), false);
#	undef CV
#	define CV(T) volatile T
   TEST_T(CV(bool), true);
   TEST_T(CV(int), true);
   TEST_T(CV(double), true);
#	undef CV
#	define CV(T) const volatile T
   TEST_T(CV(bool), false);
   TEST_T(CV(int), false);
   TEST_T(CV(double), false);
#	undef CV
#	define CV(T) const T&
   TEST_T(CV(bool), false);
   TEST_T(CV(int), false);
   TEST_T(CV(double), false);
#	undef CV
#	define CV(T) volatile T&
   TEST_T(CV(bool), true);
   TEST_T(CV(int), true);
   TEST_T(CV(double), true);
#	undef CV
#	define CV(T) const volatile T&
   TEST_T(CV(bool), false);
   TEST_T(CV(int), false);
   TEST_T(CV(double), false);

   // test with only two template parameters
   TEST_TT(void, int, false);
   TEST_TT(int, void, false);
   TEST_TT(void, void, false);
   TEST_TT(bool, bool, true);
   TEST_TT(bool, char, true);
   TEST_TT(bool, signed char, true);
   TEST_TT(bool, short int, true);
   TEST_TT(bool, int, true);
   TEST_TT(bool, long int, true);
   TEST_TT(bool, unsigned char, true);
   TEST_TT(bool, unsigned short int, true);
   TEST_TT(bool, unsigned int, true);
   TEST_TT(bool, unsigned long int, true);
   TEST_TT(bool, wchar_t, true);
   TEST_TT(bool, float, true);
   TEST_TT(bool, double, true);
   TEST_TT(bool, long double, true);
   TEST_TT(char, bool, true);
   TEST_TT(char, char, true);
   TEST_TT(char, signed char, true);
   TEST_TT(char, short int, true);
   TEST_TT(char, int, true);
   TEST_TT(char, long int, true);
   TEST_TT(char, unsigned char, true);
   TEST_TT(char, unsigned short int, true);
   TEST_TT(char, unsigned int, true);
   TEST_TT(char, unsigned long int, true);
   TEST_TT(char, wchar_t, true);
   TEST_TT(char, float, true);
   TEST_TT(char, double, true);
   TEST_TT(char, long double, true);
   TEST_TT(signed char, bool, true);
   TEST_TT(signed char, char, true);
   TEST_TT(signed char, signed char, true);
   TEST_TT(signed char, short int, true);
   TEST_TT(signed char, int, true);
   TEST_TT(signed char, long int, true);
   TEST_TT(signed char, unsigned char, true);
   TEST_TT(signed char, unsigned short int, true);
   TEST_TT(signed char, unsigned int, true);
   TEST_TT(signed char, unsigned long int, true);
   TEST_TT(signed char, wchar_t, true);
   TEST_TT(signed char, float, true);
   TEST_TT(signed char, double, true);
   TEST_TT(signed char, long double, true);
   TEST_TT(short int, bool, true);
   TEST_TT(short int, char, true);
   TEST_TT(short int, signed char, true);
   TEST_TT(short int, short int, true);
   TEST_TT(short int, int, true);
   TEST_TT(short int, long int, true);
   TEST_TT(short int, unsigned char, true);
   TEST_TT(short int, unsigned short int, true);
   TEST_TT(short int, unsigned int, true);
   TEST_TT(short int, unsigned long int, true);
   TEST_TT(short int, wchar_t, true);
   TEST_TT(short int, float, true);
   TEST_TT(short int, double, true);
   TEST_TT(short int, long double, true);
   TEST_TT(int, bool, true);
   TEST_TT(int, char, true);
   TEST_TT(int, signed char, true);
   TEST_TT(int, short int, true);
   TEST_TT(int, int, true);
   TEST_TT(int, long int, true);
   TEST_TT(int, unsigned char, true);
   TEST_TT(int, unsigned short int, true);
   TEST_TT(int, unsigned int, true);
   TEST_TT(int, unsigned long int, true);
   TEST_TT(int, wchar_t, true);
   TEST_TT(int, float, true);
   TEST_TT(int, double, true);
   TEST_TT(int, long double, true);
   TEST_TT(long int, bool, true);
   TEST_TT(long int, char, true);
   TEST_TT(long int, signed char, true);
   TEST_TT(long int, short int, true);
   TEST_TT(long int, int, true);
   TEST_TT(long int, long int, true);
   TEST_TT(long int, unsigned char, true);
   TEST_TT(long int, unsigned short int, true);
   TEST_TT(long int, unsigned int, true);
   TEST_TT(long int, unsigned long int, true);
   TEST_TT(long int, wchar_t, true);
   TEST_TT(long int, float, true);
   TEST_TT(long int, double, true);
   TEST_TT(long int, long double, true);
   TEST_TT(unsigned char, bool, true);
   TEST_TT(unsigned char, char, true);
   TEST_TT(unsigned char, signed char, true);
   TEST_TT(unsigned char, short int, true);
   TEST_TT(unsigned char, int, true);
   TEST_TT(unsigned char, long int, true);
   TEST_TT(unsigned char, unsigned char, true);
   TEST_TT(unsigned char, unsigned short int, true);
   TEST_TT(unsigned char, unsigned int, true);
   TEST_TT(unsigned char, unsigned long int, true);
   TEST_TT(unsigned char, wchar_t, true);
   TEST_TT(unsigned char, float, true);
   TEST_TT(unsigned char, double, true);
   TEST_TT(unsigned char, long double, true);
   TEST_TT(unsigned short int, bool, true);
   TEST_TT(unsigned short int, char, true);
   TEST_TT(unsigned short int, signed char, true);
   TEST_TT(unsigned short int, short int, true);
   TEST_TT(unsigned short int, int, true);
   TEST_TT(unsigned short int, long int, true);
   TEST_TT(unsigned short int, unsigned char, true);
   TEST_TT(unsigned short int, unsigned short int, true);
   TEST_TT(unsigned short int, unsigned int, true);
   TEST_TT(unsigned short int, unsigned long int, true);
   TEST_TT(unsigned short int, wchar_t, true);
   TEST_TT(unsigned short int, float, true);
   TEST_TT(unsigned short int, double, true);
   TEST_TT(unsigned short int, long double, true);
   TEST_TT(unsigned int, bool, true);
   TEST_TT(unsigned int, char, true);
   TEST_TT(unsigned int, signed char, true);
   TEST_TT(unsigned int, short int, true);
   TEST_TT(unsigned int, int, true);
   TEST_TT(unsigned int, long int, true);
   TEST_TT(unsigned int, unsigned char, true);
   TEST_TT(unsigned int, unsigned short int, true);
   TEST_TT(unsigned int, unsigned int, true);
   TEST_TT(unsigned int, unsigned long int, true);
   TEST_TT(unsigned int, wchar_t, true);
   TEST_TT(unsigned int, float, true);
   TEST_TT(unsigned int, double, true);
   TEST_TT(unsigned int, long double, true);
   TEST_TT(unsigned long int, bool, true);
   TEST_TT(unsigned long int, char, true);
   TEST_TT(unsigned long int, signed char, true);
   TEST_TT(unsigned long int, short int, true);
   TEST_TT(unsigned long int, int, true);
   TEST_TT(unsigned long int, long int, true);
   TEST_TT(unsigned long int, unsigned char, true);
   TEST_TT(unsigned long int, unsigned short int, true);
   TEST_TT(unsigned long int, unsigned int, true);
   TEST_TT(unsigned long int, unsigned long int, true);
   TEST_TT(unsigned long int, wchar_t, true);
   TEST_TT(unsigned long int, float, true);
   TEST_TT(unsigned long int, double, true);
   TEST_TT(unsigned long int, long double, true);
   TEST_TT(wchar_t, bool, true);
   TEST_TT(wchar_t, char, true);
   TEST_TT(wchar_t, signed char, true);
   TEST_TT(wchar_t, short int, true);
   TEST_TT(wchar_t, int, true);
   TEST_TT(wchar_t, long int, true);
   TEST_TT(wchar_t, unsigned char, true);
   TEST_TT(wchar_t, unsigned short int, true);
   TEST_TT(wchar_t, unsigned int, true);
   TEST_TT(wchar_t, unsigned long int, true);
   TEST_TT(wchar_t, wchar_t, true);
   TEST_TT(wchar_t, float, true);
   TEST_TT(wchar_t, double, true);
   TEST_TT(wchar_t, long double, true);
   TEST_TT(float, bool, true);
   TEST_TT(float, char, true);
   TEST_TT(float, signed char, true);
   TEST_TT(float, short int, true);
   TEST_TT(float, int, true);
   TEST_TT(float, long int, true);
   TEST_TT(float, unsigned char, true);
   TEST_TT(float, unsigned short int, true);
   TEST_TT(float, unsigned int, true);
   TEST_TT(float, unsigned long int, true);
   TEST_TT(float, wchar_t, true);
   TEST_TT(float, float, true);
   TEST_TT(float, double, true);
   TEST_TT(float, long double, true);
   TEST_TT(double, bool, true);
   TEST_TT(double, char, true);
   TEST_TT(double, signed char, true);
   TEST_TT(double, short int, true);
   TEST_TT(double, int, true);
   TEST_TT(double, long int, true);
   TEST_TT(double, unsigned char, true);
   TEST_TT(double, unsigned short int, true);
   TEST_TT(double, unsigned int, true);
   TEST_TT(double, unsigned long int, true);
   TEST_TT(double, wchar_t, true);
   TEST_TT(double, float, true);
   TEST_TT(double, double, true);
   TEST_TT(double, long double, true);
   TEST_TT(long double, bool, true);
   TEST_TT(long double, char, true);
   TEST_TT(long double, signed char, true);
   TEST_TT(long double, short int, true);
   TEST_TT(long double, int, true);
   TEST_TT(long double, long int, true);
   TEST_TT(long double, unsigned char, true);
   TEST_TT(long double, unsigned short int, true);
   TEST_TT(long double, unsigned int, true);
   TEST_TT(long double, unsigned long int, true);
   TEST_TT(long double, wchar_t, true);
   TEST_TT(long double, float, true);
   TEST_TT(long double, double, true);
   TEST_TT(long double, long double, true);
   TEST_TT(bool, void, false);
   TEST_TT(void, bool, false);
   TEST_TT(char, void, false);
   TEST_TT(void, char, false);
   TEST_TT(signed char, void, false);
   TEST_TT(void, signed char, false);
   TEST_TT(short int, void, false);
   TEST_TT(void, short int, false);
   TEST_TT(int, void, false);
   TEST_TT(void, int, false);
   TEST_TT(long int, void, false);
   TEST_TT(void, long int, false);
   TEST_TT(unsigned char, void, false);
   TEST_TT(void, unsigned char, false);
   TEST_TT(unsigned short int, void, false);
   TEST_TT(void, unsigned short int, false);
   TEST_TT(unsigned int, void, false);
   TEST_TT(void, unsigned int, false);
   TEST_TT(unsigned long int, void, false);
   TEST_TT(void, unsigned long int, false);
   TEST_TT(wchar_t, void, false);
   TEST_TT(void, wchar_t, false);
   TEST_TT(float, void, false);
   TEST_TT(void, float, false);
   TEST_TT(double, void, false);
   TEST_TT(void, double, false);
   TEST_TT(long double, void, false);
   TEST_TT(void, long double, false);

// test with three template parameters
   TEST_TTR(bool, bool, bool, true);
   TEST_TTR(bool, char, bool, true);
   TEST_TTR(bool, signed char, bool, true);
   TEST_TTR(bool, short int, bool, true);
   TEST_TTR(bool, int, bool, true);
   TEST_TTR(bool, long int, bool, true);
   TEST_TTR(bool, unsigned char, bool, true);
   TEST_TTR(bool, unsigned short int, bool, true);
   TEST_TTR(bool, unsigned int, bool, true);
   TEST_TTR(bool, unsigned long int, bool, true);
   TEST_TTR(bool, wchar_t, bool, true);
   TEST_TTR(bool, float, bool, true);
   TEST_TTR(bool, double, bool, true);
   TEST_TTR(bool, long double, bool, true);
   TEST_TTR(char, bool, bool, true);
   TEST_TTR(char, char, bool, true);
   TEST_TTR(char, signed char, bool, true);
   TEST_TTR(char, short int, bool, true);
   TEST_TTR(char, int, bool, true);
   TEST_TTR(char, long int, bool, true);
   TEST_TTR(char, unsigned char, bool, true);
   TEST_TTR(char, unsigned short int, bool, true);
   TEST_TTR(char, unsigned int, bool, true);
   TEST_TTR(char, unsigned long int, bool, true);
   TEST_TTR(char, wchar_t, bool, true);
   TEST_TTR(char, float, bool, true);
   TEST_TTR(char, double, bool, true);
   TEST_TTR(char, long double, bool, true);
   TEST_TTR(signed char, bool, bool, true);
   TEST_TTR(signed char, char, bool, true);
   TEST_TTR(signed char, signed char, bool, true);
   TEST_TTR(signed char, short int, bool, true);
   TEST_TTR(signed char, int, bool, true);
   TEST_TTR(signed char, long int, bool, true);
   TEST_TTR(signed char, unsigned char, bool, true);
   TEST_TTR(signed char, unsigned short int, bool, true);
   TEST_TTR(signed char, unsigned int, bool, true);
   TEST_TTR(signed char, unsigned long int, bool, true);
   TEST_TTR(signed char, wchar_t, bool, true);
   TEST_TTR(signed char, float, bool, true);
   TEST_TTR(signed char, double, bool, true);
   TEST_TTR(signed char, long double, bool, true);
   TEST_TTR(short int, bool, bool, true);
   TEST_TTR(short int, char, bool, true);
   TEST_TTR(short int, signed char, bool, true);
   TEST_TTR(short int, short int, bool, true);
   TEST_TTR(short int, int, bool, true);
   TEST_TTR(short int, long int, bool, true);
   TEST_TTR(short int, unsigned char, bool, true);
   TEST_TTR(short int, unsigned short int, bool, true);
   TEST_TTR(short int, unsigned int, bool, true);
   TEST_TTR(short int, unsigned long int, bool, true);
   TEST_TTR(short int, wchar_t, bool, true);
   TEST_TTR(short int, float, bool, true);
   TEST_TTR(short int, double, bool, true);
   TEST_TTR(short int, long double, bool, true);
   TEST_TTR(int, bool, bool, true);
   TEST_TTR(int, char, bool, true);
   TEST_TTR(int, signed char, bool, true);
   TEST_TTR(int, short int, bool, true);
   TEST_TTR(int, int, bool, true);
   TEST_TTR(int, long int, bool, true);
   TEST_TTR(int, unsigned char, bool, true);
   TEST_TTR(int, unsigned short int, bool, true);
   TEST_TTR(int, unsigned int, bool, true);
   TEST_TTR(int, unsigned long int, bool, true);
   TEST_TTR(int, wchar_t, bool, true);
   TEST_TTR(int, float, bool, true);
   TEST_TTR(int, double, bool, true);
   TEST_TTR(int, long double, bool, true);
   TEST_TTR(long int, bool, bool, true);
   TEST_TTR(long int, char, bool, true);
   TEST_TTR(long int, signed char, bool, true);
   TEST_TTR(long int, short int, bool, true);
   TEST_TTR(long int, int, bool, true);
   TEST_TTR(long int, long int, bool, true);
   TEST_TTR(long int, unsigned char, bool, true);
   TEST_TTR(long int, unsigned short int, bool, true);
   TEST_TTR(long int, unsigned int, bool, true);
   TEST_TTR(long int, unsigned long int, bool, true);
   TEST_TTR(long int, wchar_t, bool, true);
   TEST_TTR(long int, float, bool, true);
   TEST_TTR(long int, double, bool, true);
   TEST_TTR(long int, long double, bool, true);
   TEST_TTR(unsigned char, bool, bool, true);
   TEST_TTR(unsigned char, char, bool, true);
   TEST_TTR(unsigned char, signed char, bool, true);
   TEST_TTR(unsigned char, short int, bool, true);
   TEST_TTR(unsigned char, int, bool, true);
   TEST_TTR(unsigned char, long int, bool, true);
   TEST_TTR(unsigned char, unsigned char, bool, true);
   TEST_TTR(unsigned char, unsigned short int, bool, true);
   TEST_TTR(unsigned char, unsigned int, bool, true);
   TEST_TTR(unsigned char, unsigned long int, bool, true);
   TEST_TTR(unsigned char, wchar_t, bool, true);
   TEST_TTR(unsigned char, float, bool, true);
   TEST_TTR(unsigned char, double, bool, true);
   TEST_TTR(unsigned char, long double, bool, true);
   TEST_TTR(unsigned short int, bool, bool, true);
   TEST_TTR(unsigned short int, char, bool, true);
   TEST_TTR(unsigned short int, signed char, bool, true);
   TEST_TTR(unsigned short int, short int, bool, true);
   TEST_TTR(unsigned short int, int, bool, true);
   TEST_TTR(unsigned short int, long int, bool, true);
   TEST_TTR(unsigned short int, unsigned char, bool, true);
   TEST_TTR(unsigned short int, unsigned short int, bool, true);
   TEST_TTR(unsigned short int, unsigned int, bool, true);
   TEST_TTR(unsigned short int, unsigned long int, bool, true);
   TEST_TTR(unsigned short int, wchar_t, bool, true);
   TEST_TTR(unsigned short int, float, bool, true);
   TEST_TTR(unsigned short int, double, bool, true);
   TEST_TTR(unsigned short int, long double, bool, true);
   TEST_TTR(unsigned int, bool, bool, true);
   TEST_TTR(unsigned int, char, bool, true);
   TEST_TTR(unsigned int, signed char, bool, true);
   TEST_TTR(unsigned int, short int, bool, true);
   TEST_TTR(unsigned int, int, bool, true);
   TEST_TTR(unsigned int, long int, bool, true);
   TEST_TTR(unsigned int, unsigned char, bool, true);
   TEST_TTR(unsigned int, unsigned short int, bool, true);
   TEST_TTR(unsigned int, unsigned int, bool, true);
   TEST_TTR(unsigned int, unsigned long int, bool, true);
   TEST_TTR(unsigned int, wchar_t, bool, true);
   TEST_TTR(unsigned int, float, bool, true);
   TEST_TTR(unsigned int, double, bool, true);
   TEST_TTR(unsigned int, long double, bool, true);
   TEST_TTR(unsigned long int, bool, bool, true);
   TEST_TTR(unsigned long int, char, bool, true);
   TEST_TTR(unsigned long int, signed char, bool, true);
   TEST_TTR(unsigned long int, short int, bool, true);
   TEST_TTR(unsigned long int, int, bool, true);
   TEST_TTR(unsigned long int, long int, bool, true);
   TEST_TTR(unsigned long int, unsigned char, bool, true);
   TEST_TTR(unsigned long int, unsigned short int, bool, true);
   TEST_TTR(unsigned long int, unsigned int, bool, true);
   TEST_TTR(unsigned long int, unsigned long int, bool, true);
   TEST_TTR(unsigned long int, wchar_t, bool, true);
   TEST_TTR(unsigned long int, float, bool, true);
   TEST_TTR(unsigned long int, double, bool, true);
   TEST_TTR(unsigned long int, long double, bool, true);
   TEST_TTR(wchar_t, bool, bool, true);
   TEST_TTR(wchar_t, char, bool, true);
   TEST_TTR(wchar_t, signed char, bool, true);
   TEST_TTR(wchar_t, short int, bool, true);
   TEST_TTR(wchar_t, int, bool, true);
   TEST_TTR(wchar_t, long int, bool, true);
   TEST_TTR(wchar_t, unsigned char, bool, true);
   TEST_TTR(wchar_t, unsigned short int, bool, true);
   TEST_TTR(wchar_t, unsigned int, bool, true);
   TEST_TTR(wchar_t, unsigned long int, bool, true);
   TEST_TTR(wchar_t, wchar_t, bool, true);
   TEST_TTR(wchar_t, float, bool, true);
   TEST_TTR(wchar_t, double, bool, true);
   TEST_TTR(wchar_t, long double, bool, true);
   TEST_TTR(float, bool, bool, true);
   TEST_TTR(float, char, bool, true);
   TEST_TTR(float, signed char, bool, true);
   TEST_TTR(float, short int, bool, true);
   TEST_TTR(float, int, bool, true);
   TEST_TTR(float, long int, bool, true);
   TEST_TTR(float, unsigned char, bool, true);
   TEST_TTR(float, unsigned short int, bool, true);
   TEST_TTR(float, unsigned int, bool, true);
   TEST_TTR(float, unsigned long int, bool, true);
   TEST_TTR(float, wchar_t, bool, true);
   TEST_TTR(float, float, bool, true);
   TEST_TTR(float, double, bool, true);
   TEST_TTR(float, long double, bool, true);
   TEST_TTR(double, bool, bool, true);
   TEST_TTR(double, char, bool, true);
   TEST_TTR(double, signed char, bool, true);
   TEST_TTR(double, short int, bool, true);
   TEST_TTR(double, int, bool, true);
   TEST_TTR(double, long int, bool, true);
   TEST_TTR(double, unsigned char, bool, true);
   TEST_TTR(double, unsigned short int, bool, true);
   TEST_TTR(double, unsigned int, bool, true);
   TEST_TTR(double, unsigned long int, bool, true);
   TEST_TTR(double, wchar_t, bool, true);
   TEST_TTR(double, float, bool, true);
   TEST_TTR(double, double, bool, true);
   TEST_TTR(double, long double, bool, true);
   TEST_TTR(long double, bool, bool, true);
   TEST_TTR(long double, char, bool, true);
   TEST_TTR(long double, signed char, bool, true);
   TEST_TTR(long double, short int, bool, true);
   TEST_TTR(long double, int, bool, true);
   TEST_TTR(long double, long int, bool, true);
   TEST_TTR(long double, unsigned char, bool, true);
   TEST_TTR(long double, unsigned short int, bool, true);
   TEST_TTR(long double, unsigned int, bool, true);
   TEST_TTR(long double, unsigned long int, bool, true);
   TEST_TTR(long double, wchar_t, bool, true);
   TEST_TTR(long double, float, bool, true);
   TEST_TTR(long double, double, bool, true);
   TEST_TTR(long double, long double, bool, true);
   TEST_TTR(bool, bool, tag, false);
   TEST_TTR(bool, char, tag, false);
   TEST_TTR(bool, signed char, tag, false);
   TEST_TTR(bool, short int, tag, false);
   TEST_TTR(bool, int, tag, false);
   TEST_TTR(bool, long int, tag, false);
   TEST_TTR(bool, unsigned char, tag, false);
   TEST_TTR(bool, unsigned short int, tag, false);
   TEST_TTR(bool, unsigned int, tag, false);
   TEST_TTR(bool, unsigned long int, tag, false);
   TEST_TTR(bool, wchar_t, tag, false);
   TEST_TTR(bool, float, tag, false);
   TEST_TTR(bool, double, tag, false);
   TEST_TTR(bool, long double, tag, false);
   TEST_TTR(char, bool, tag, false);
   TEST_TTR(char, char, tag, false);
   TEST_TTR(char, signed char, tag, false);
   TEST_TTR(char, short int, tag, false);
   TEST_TTR(char, int, tag, false);
   TEST_TTR(char, long int, tag, false);
   TEST_TTR(char, unsigned char, tag, false);
   TEST_TTR(char, unsigned short int, tag, false);
   TEST_TTR(char, unsigned int, tag, false);
   TEST_TTR(char, unsigned long int, tag, false);
   TEST_TTR(char, wchar_t, tag, false);
   TEST_TTR(char, float, tag, false);
   TEST_TTR(char, double, tag, false);
   TEST_TTR(char, long double, tag, false);
   TEST_TTR(signed char, bool, tag, false);
   TEST_TTR(signed char, char, tag, false);
   TEST_TTR(signed char, signed char, tag, false);
   TEST_TTR(signed char, short int, tag, false);
   TEST_TTR(signed char, int, tag, false);
   TEST_TTR(signed char, long int, tag, false);
   TEST_TTR(signed char, unsigned char, tag, false);
   TEST_TTR(signed char, unsigned short int, tag, false);
   TEST_TTR(signed char, unsigned int, tag, false);
   TEST_TTR(signed char, unsigned long int, tag, false);
   TEST_TTR(signed char, wchar_t, tag, false);
   TEST_TTR(signed char, float, tag, false);
   TEST_TTR(signed char, double, tag, false);
   TEST_TTR(signed char, long double, tag, false);
   TEST_TTR(short int, bool, tag, false);
   TEST_TTR(short int, char, tag, false);
   TEST_TTR(short int, signed char, tag, false);
   TEST_TTR(short int, short int, tag, false);
   TEST_TTR(short int, int, tag, false);
   TEST_TTR(short int, long int, tag, false);
   TEST_TTR(short int, unsigned char, tag, false);
   TEST_TTR(short int, unsigned short int, tag, false);
   TEST_TTR(short int, unsigned int, tag, false);
   TEST_TTR(short int, unsigned long int, tag, false);
   TEST_TTR(short int, wchar_t, tag, false);
   TEST_TTR(short int, float, tag, false);
   TEST_TTR(short int, double, tag, false);
   TEST_TTR(short int, long double, tag, false);
   TEST_TTR(int, bool, tag, false);
   TEST_TTR(int, char, tag, false);
   TEST_TTR(int, signed char, tag, false);
   TEST_TTR(int, short int, tag, false);
   TEST_TTR(int, int, tag, false);
   TEST_TTR(int, long int, tag, false);
   TEST_TTR(int, unsigned char, tag, false);
   TEST_TTR(int, unsigned short int, tag, false);
   TEST_TTR(int, unsigned int, tag, false);
   TEST_TTR(int, unsigned long int, tag, false);
   TEST_TTR(int, wchar_t, tag, false);
   TEST_TTR(int, float, tag, false);
   TEST_TTR(int, double, tag, false);
   TEST_TTR(int, long double, tag, false);
   TEST_TTR(long int, bool, tag, false);
   TEST_TTR(long int, char, tag, false);
   TEST_TTR(long int, signed char, tag, false);
   TEST_TTR(long int, short int, tag, false);
   TEST_TTR(long int, int, tag, false);
   TEST_TTR(long int, long int, tag, false);
   TEST_TTR(long int, unsigned char, tag, false);
   TEST_TTR(long int, unsigned short int, tag, false);
   TEST_TTR(long int, unsigned int, tag, false);
   TEST_TTR(long int, unsigned long int, tag, false);
   TEST_TTR(long int, wchar_t, tag, false);
   TEST_TTR(long int, float, tag, false);
   TEST_TTR(long int, double, tag, false);
   TEST_TTR(long int, long double, tag, false);
   TEST_TTR(unsigned char, bool, tag, false);
   TEST_TTR(unsigned char, char, tag, false);
   TEST_TTR(unsigned char, signed char, tag, false);
   TEST_TTR(unsigned char, short int, tag, false);
   TEST_TTR(unsigned char, int, tag, false);
   TEST_TTR(unsigned char, long int, tag, false);
   TEST_TTR(unsigned char, unsigned char, tag, false);
   TEST_TTR(unsigned char, unsigned short int, tag, false);
   TEST_TTR(unsigned char, unsigned int, tag, false);
   TEST_TTR(unsigned char, unsigned long int, tag, false);
   TEST_TTR(unsigned char, wchar_t, tag, false);
   TEST_TTR(unsigned char, float, tag, false);
   TEST_TTR(unsigned char, double, tag, false);
   TEST_TTR(unsigned char, long double, tag, false);
   TEST_TTR(unsigned short int, bool, tag, false);
   TEST_TTR(unsigned short int, char, tag, false);
   TEST_TTR(unsigned short int, signed char, tag, false);
   TEST_TTR(unsigned short int, short int, tag, false);
   TEST_TTR(unsigned short int, int, tag, false);
   TEST_TTR(unsigned short int, long int, tag, false);
   TEST_TTR(unsigned short int, unsigned char, tag, false);
   TEST_TTR(unsigned short int, unsigned short int, tag, false);
   TEST_TTR(unsigned short int, unsigned int, tag, false);
   TEST_TTR(unsigned short int, unsigned long int, tag, false);
   TEST_TTR(unsigned short int, wchar_t, tag, false);
   TEST_TTR(unsigned short int, float, tag, false);
   TEST_TTR(unsigned short int, double, tag, false);
   TEST_TTR(unsigned short int, long double, tag, false);
   TEST_TTR(unsigned int, bool, tag, false);
   TEST_TTR(unsigned int, char, tag, false);
   TEST_TTR(unsigned int, signed char, tag, false);
   TEST_TTR(unsigned int, short int, tag, false);
   TEST_TTR(unsigned int, int, tag, false);
   TEST_TTR(unsigned int, long int, tag, false);
   TEST_TTR(unsigned int, unsigned char, tag, false);
   TEST_TTR(unsigned int, unsigned short int, tag, false);
   TEST_TTR(unsigned int, unsigned int, tag, false);
   TEST_TTR(unsigned int, unsigned long int, tag, false);
   TEST_TTR(unsigned int, wchar_t, tag, false);
   TEST_TTR(unsigned int, float, tag, false);
   TEST_TTR(unsigned int, double, tag, false);
   TEST_TTR(unsigned int, long double, tag, false);
   TEST_TTR(unsigned long int, bool, tag, false);
   TEST_TTR(unsigned long int, char, tag, false);
   TEST_TTR(unsigned long int, signed char, tag, false);
   TEST_TTR(unsigned long int, short int, tag, false);
   TEST_TTR(unsigned long int, int, tag, false);
   TEST_TTR(unsigned long int, long int, tag, false);
   TEST_TTR(unsigned long int, unsigned char, tag, false);
   TEST_TTR(unsigned long int, unsigned short int, tag, false);
   TEST_TTR(unsigned long int, unsigned int, tag, false);
   TEST_TTR(unsigned long int, unsigned long int, tag, false);
   TEST_TTR(unsigned long int, wchar_t, tag, false);
   TEST_TTR(unsigned long int, float, tag, false);
   TEST_TTR(unsigned long int, double, tag, false);
   TEST_TTR(unsigned long int, long double, tag, false);
   TEST_TTR(wchar_t, bool, tag, false);
   TEST_TTR(wchar_t, char, tag, false);
   TEST_TTR(wchar_t, signed char, tag, false);
   TEST_TTR(wchar_t, short int, tag, false);
   TEST_TTR(wchar_t, int, tag, false);
   TEST_TTR(wchar_t, long int, tag, false);
   TEST_TTR(wchar_t, unsigned char, tag, false);
   TEST_TTR(wchar_t, unsigned short int, tag, false);
   TEST_TTR(wchar_t, unsigned int, tag, false);
   TEST_TTR(wchar_t, unsigned long int, tag, false);
   TEST_TTR(wchar_t, wchar_t, tag, false);
   TEST_TTR(wchar_t, float, tag, false);
   TEST_TTR(wchar_t, double, tag, false);
   TEST_TTR(wchar_t, long double, tag, false);
   TEST_TTR(float, bool, tag, false);
   TEST_TTR(float, char, tag, false);
   TEST_TTR(float, signed char, tag, false);
   TEST_TTR(float, short int, tag, false);
   TEST_TTR(float, int, tag, false);
   TEST_TTR(float, long int, tag, false);
   TEST_TTR(float, unsigned char, tag, false);
   TEST_TTR(float, unsigned short int, tag, false);
   TEST_TTR(float, unsigned int, tag, false);
   TEST_TTR(float, unsigned long int, tag, false);
   TEST_TTR(float, wchar_t, tag, false);
   TEST_TTR(float, float, tag, false);
   TEST_TTR(float, double, tag, false);
   TEST_TTR(float, long double, tag, false);
   TEST_TTR(double, bool, tag, false);
   TEST_TTR(double, char, tag, false);
   TEST_TTR(double, signed char, tag, false);
   TEST_TTR(double, short int, tag, false);
   TEST_TTR(double, int, tag, false);
   TEST_TTR(double, long int, tag, false);
   TEST_TTR(double, unsigned char, tag, false);
   TEST_TTR(double, unsigned short int, tag, false);
   TEST_TTR(double, unsigned int, tag, false);
   TEST_TTR(double, unsigned long int, tag, false);
   TEST_TTR(double, wchar_t, tag, false);
   TEST_TTR(double, float, tag, false);
   TEST_TTR(double, double, tag, false);
   TEST_TTR(double, long double, tag, false);
   TEST_TTR(long double, bool, tag, false);
   TEST_TTR(long double, char, tag, false);
   TEST_TTR(long double, signed char, tag, false);
   TEST_TTR(long double, short int, tag, false);
   TEST_TTR(long double, int, tag, false);
   TEST_TTR(long double, long int, tag, false);
   TEST_TTR(long double, unsigned char, tag, false);
   TEST_TTR(long double, unsigned short int, tag, false);
   TEST_TTR(long double, unsigned int, tag, false);
   TEST_TTR(long double, unsigned long int, tag, false);
   TEST_TTR(long double, wchar_t, tag, false);
   TEST_TTR(long double, float, tag, false);
   TEST_TTR(long double, double, tag, false);
   TEST_TTR(long double, long double, tag, false);
#	undef CV1
#	define CV1(T) const T
#	undef CV2
#	define CV2(T) T
   // test with only two template parameters
   TEST_TT(CV1(bool), CV2(int), false);
   TEST_TT(CV1(bool), CV2(double), false);
   TEST_TT(CV1(int), CV2(bool), false);
   TEST_TT(CV1(int), CV2(double), false);
   TEST_TT(CV1(double), CV2(bool), false);
   TEST_TT(CV1(double), CV2(int), false);

   // test with three template parameters
   TEST_TTR(CV1(bool), CV2(int), bool, false);
   TEST_TTR(CV1(bool), CV2(double), bool, false);
   TEST_TTR(CV1(int), CV2(bool), bool, false);
   TEST_TTR(CV1(int), CV2(double), bool, false);
   TEST_TTR(CV1(double), CV2(bool), bool, false);
   TEST_TTR(CV1(double), CV2(int), bool, false);
   TEST_TTR(CV1(bool), CV2(int), tag, false);
   TEST_TTR(CV1(bool), CV2(double), tag, false);
   TEST_TTR(CV1(int), CV2(bool), tag, false);
   TEST_TTR(CV1(int), CV2(double), tag, false);
   TEST_TTR(CV1(double), CV2(bool), tag, false);
   TEST_TTR(CV1(double), CV2(int), tag, false);

#	undef CV1
#	define CV1(T) volatile T
#	undef CV2
#	define CV2(T) T
   // test with only two template parameters
   TEST_TT(CV1(bool), CV2(int), true);
   TEST_TT(CV1(bool), CV2(double), true);
   TEST_TT(CV1(int), CV2(bool), true);
   TEST_TT(CV1(int), CV2(double), true);
   TEST_TT(CV1(double), CV2(bool), true);
   TEST_TT(CV1(double), CV2(int), true);

   // test with three template parameters
   TEST_TTR(CV1(bool), CV2(int), bool, true);
   TEST_TTR(CV1(bool), CV2(double), bool, true);
   TEST_TTR(CV1(int), CV2(bool), bool, true);
   TEST_TTR(CV1(int), CV2(double), bool, true);
   TEST_TTR(CV1(double), CV2(bool), bool, true);
   TEST_TTR(CV1(double), CV2(int), bool, true);
   TEST_TTR(CV1(bool), CV2(int), tag, false);
   TEST_TTR(CV1(bool), CV2(double), tag, false);
   TEST_TTR(CV1(int), CV2(bool), tag, false);
   TEST_TTR(CV1(int), CV2(double), tag, false);
   TEST_TTR(CV1(double), CV2(bool), tag, false);
   TEST_TTR(CV1(double), CV2(int), tag, false);

#	undef CV1
#	define CV1(T) const volatile T
#	undef CV2
#	define CV2(T) T
   // test with only two template parameters
   TEST_TT(CV1(bool), CV2(int), false);
   TEST_TT(CV1(bool), CV2(double), false);
   TEST_TT(CV1(int), CV2(bool), false);
   TEST_TT(CV1(int), CV2(double), false);
   TEST_TT(CV1(double), CV2(bool), false);
   TEST_TT(CV1(double), CV2(int), false);

   // test with three template parameters
   TEST_TTR(CV1(bool), CV2(int), bool, false);
   TEST_TTR(CV1(bool), CV2(double), bool, false);
   TEST_TTR(CV1(int), CV2(bool), bool, false);
   TEST_TTR(CV1(int), CV2(double), bool, false);
   TEST_TTR(CV1(double), CV2(bool), bool, false);
   TEST_TTR(CV1(double), CV2(int), bool, false);
   TEST_TTR(CV1(bool), CV2(int), tag, false);
   TEST_TTR(CV1(bool), CV2(double), tag, false);
   TEST_TTR(CV1(int), CV2(bool), tag, false);
   TEST_TTR(CV1(int), CV2(double), tag, false);
   TEST_TTR(CV1(double), CV2(bool), tag, false);
   TEST_TTR(CV1(double), CV2(int), tag, false);

#	undef CV1
#	define CV1(T) const T&
#	undef CV2
#	define CV2(T) T
   // test with only two template parameters
   TEST_TT(CV1(bool), CV2(int), false);
   TEST_TT(CV1(bool), CV2(double), false);
   TEST_TT(CV1(int), CV2(bool), false);
   TEST_TT(CV1(int), CV2(double), false);
   TEST_TT(CV1(double), CV2(bool), false);
   TEST_TT(CV1(double), CV2(int), false);

   // test with three template parameters
   TEST_TTR(CV1(bool), CV2(int), bool, false);
   TEST_TTR(CV1(bool), CV2(double), bool, false);
   TEST_TTR(CV1(int), CV2(bool), bool, false);
   TEST_TTR(CV1(int), CV2(double), bool, false);
   TEST_TTR(CV1(double), CV2(bool), bool, false);
   TEST_TTR(CV1(double), CV2(int), bool, false);
   TEST_TTR(CV1(bool), CV2(int), tag, false);
   TEST_TTR(CV1(bool), CV2(double), tag, false);
   TEST_TTR(CV1(int), CV2(bool), tag, false);
   TEST_TTR(CV1(int), CV2(double), tag, false);
   TEST_TTR(CV1(double), CV2(bool), tag, false);
   TEST_TTR(CV1(double), CV2(int), tag, false);

#	undef CV1
#	define CV1(T) volatile T&
#	undef CV2
#	define CV2(T) T
   // test with only two template parameters
   TEST_TT(CV1(bool), CV2(int), true);
   TEST_TT(CV1(bool), CV2(double), true);
   TEST_TT(CV1(int), CV2(bool), true);
   TEST_TT(CV1(int), CV2(double), true);
   TEST_TT(CV1(double), CV2(bool), true);
   TEST_TT(CV1(double), CV2(int), true);

   // test with three template parameters
   TEST_TTR(CV1(bool), CV2(int), bool, true);
   TEST_TTR(CV1(bool), CV2(double), bool, true);
   TEST_TTR(CV1(int), CV2(bool), bool, true);
   TEST_TTR(CV1(int), CV2(double), bool, true);
   TEST_TTR(CV1(double), CV2(bool), bool, true);
   TEST_TTR(CV1(double), CV2(int), bool, true);
   TEST_TTR(CV1(bool), CV2(int), tag, false);
   TEST_TTR(CV1(bool), CV2(double), tag, false);
   TEST_TTR(CV1(int), CV2(bool), tag, false);
   TEST_TTR(CV1(int), CV2(double), tag, false);
   TEST_TTR(CV1(double), CV2(bool), tag, false);
   TEST_TTR(CV1(double), CV2(int), tag, false);

#	undef CV1
#	define CV1(T) const volatile T&
#	undef CV2
#	define CV2(T) T
   // test with only two template parameters
   TEST_TT(CV1(bool), CV2(int), false);
   TEST_TT(CV1(bool), CV2(double), false);
   TEST_TT(CV1(int), CV2(bool), false);
   TEST_TT(CV1(int), CV2(double), false);
   TEST_TT(CV1(double), CV2(bool), false);
   TEST_TT(CV1(double), CV2(int), false);

   // test with three template parameters
   TEST_TTR(CV1(bool), CV2(int), bool, false);
   TEST_TTR(CV1(bool), CV2(double), bool, false);
   TEST_TTR(CV1(int), CV2(bool), bool, false);
   TEST_TTR(CV1(int), CV2(double), bool, false);
   TEST_TTR(CV1(double), CV2(bool), bool, false);
   TEST_TTR(CV1(double), CV2(int), bool, false);
   TEST_TTR(CV1(bool), CV2(int), tag, false);
   TEST_TTR(CV1(bool), CV2(double), tag, false);
   TEST_TTR(CV1(int), CV2(bool), tag, false);
   TEST_TTR(CV1(int), CV2(double), tag, false);
   TEST_TTR(CV1(double), CV2(bool), tag, false);
   TEST_TTR(CV1(double), CV2(int), tag, false);

#	undef CV1
#	define CV1(T) T
#	undef CV2
#	define CV2(T) const T
   // test with only two template parameters
   TEST_TT(CV1(bool), CV2(int), true);
   TEST_TT(CV1(bool), CV2(double), true);
   TEST_TT(CV1(int), CV2(bool), true);
   TEST_TT(CV1(int), CV2(double), true);
   TEST_TT(CV1(double), CV2(bool), true);
   TEST_TT(CV1(double), CV2(int), true);

   // test with three template parameters
   TEST_TTR(CV1(bool), CV2(int), bool, true);
   TEST_TTR(CV1(bool), CV2(double), bool, true);
   TEST_TTR(CV1(int), CV2(bool), bool, true);
   TEST_TTR(CV1(int), CV2(double), bool, true);
   TEST_TTR(CV1(double), CV2(bool), bool, true);
   TEST_TTR(CV1(double), CV2(int), bool, true);
   TEST_TTR(CV1(bool), CV2(int), tag, false);
   TEST_TTR(CV1(bool), CV2(double), tag, false);
   TEST_TTR(CV1(int), CV2(bool), tag, false);
   TEST_TTR(CV1(int), CV2(double), tag, false);
   TEST_TTR(CV1(double), CV2(bool), tag, false);
   TEST_TTR(CV1(double), CV2(int), tag, false);

#	undef CV1
#	define CV1(T) T
#	undef CV2
#	define CV2(T) volatile T
   // test with only two template parameters
   TEST_TT(CV1(bool), CV2(int), true);
   TEST_TT(CV1(bool), CV2(double), true);
   TEST_TT(CV1(int), CV2(bool), true);
   TEST_TT(CV1(int), CV2(double), true);
   TEST_TT(CV1(double), CV2(bool), true);
   TEST_TT(CV1(double), CV2(int), true);

   // test with three template parameters
   TEST_TTR(CV1(bool), CV2(int), bool, true);
   TEST_TTR(CV1(bool), CV2(double), bool, true);
   TEST_TTR(CV1(int), CV2(bool), bool, true);
   TEST_TTR(CV1(int), CV2(double), bool, true);
   TEST_TTR(CV1(double), CV2(bool), bool, true);
   TEST_TTR(CV1(double), CV2(int), bool, true);
   TEST_TTR(CV1(bool), CV2(int), tag, false);
   TEST_TTR(CV1(bool), CV2(double), tag, false);
   TEST_TTR(CV1(int), CV2(bool), tag, false);
   TEST_TTR(CV1(int), CV2(double), tag, false);
   TEST_TTR(CV1(double), CV2(bool), tag, false);
   TEST_TTR(CV1(double), CV2(int), tag, false);

#	undef CV1
#	define CV1(T) T
#	undef CV2
#	define CV2(T) const volatile T
   // test with only two template parameters
   TEST_TT(CV1(bool), CV2(int), true);
   TEST_TT(CV1(bool), CV2(double), true);
   TEST_TT(CV1(int), CV2(bool), true);
   TEST_TT(CV1(int), CV2(double), true);
   TEST_TT(CV1(double), CV2(bool), true);
   TEST_TT(CV1(double), CV2(int), true);

   // test with three template parameters
   TEST_TTR(CV1(bool), CV2(int), bool, true);
   TEST_TTR(CV1(bool), CV2(double), bool, true);
   TEST_TTR(CV1(int), CV2(bool), bool, true);
   TEST_TTR(CV1(int), CV2(double), bool, true);
   TEST_TTR(CV1(double), CV2(bool), bool, true);
   TEST_TTR(CV1(double), CV2(int), bool, true);
   TEST_TTR(CV1(bool), CV2(int), tag, false);
   TEST_TTR(CV1(bool), CV2(double), tag, false);
   TEST_TTR(CV1(int), CV2(bool), tag, false);
   TEST_TTR(CV1(int), CV2(double), tag, false);
   TEST_TTR(CV1(double), CV2(bool), tag, false);
   TEST_TTR(CV1(double), CV2(int), tag, false);

#	undef CV1
#	define CV1(T) T
#	undef CV2
#	define CV2(T) const T&
   // test with only two template parameters
   TEST_TT(CV1(bool), CV2(int), true);
   TEST_TT(CV1(bool), CV2(double), true);
   TEST_TT(CV1(int), CV2(bool), true);
   TEST_TT(CV1(int), CV2(double), true);
   TEST_TT(CV1(double), CV2(bool), true);
   TEST_TT(CV1(double), CV2(int), true);

   // test with three template parameters
   TEST_TTR(CV1(bool), CV2(int), bool, true);
   TEST_TTR(CV1(bool), CV2(double), bool, true);
   TEST_TTR(CV1(int), CV2(bool), bool, true);
   TEST_TTR(CV1(int), CV2(double), bool, true);
   TEST_TTR(CV1(double), CV2(bool), bool, true);
   TEST_TTR(CV1(double), CV2(int), bool, true);
   TEST_TTR(CV1(bool), CV2(int), tag, false);
   TEST_TTR(CV1(bool), CV2(double), tag, false);
   TEST_TTR(CV1(int), CV2(bool), tag, false);
   TEST_TTR(CV1(int), CV2(double), tag, false);
   TEST_TTR(CV1(double), CV2(bool), tag, false);
   TEST_TTR(CV1(double), CV2(int), tag, false);

#	undef CV1
#	define CV1(T) T
#	undef CV2
#	define CV2(T) volatile T&
   // test with only two template parameters
   TEST_TT(CV1(bool), CV2(int), true);
   TEST_TT(CV1(bool), CV2(double), true);
   TEST_TT(CV1(int), CV2(bool), true);
   TEST_TT(CV1(int), CV2(double), true);
   TEST_TT(CV1(double), CV2(bool), true);
   TEST_TT(CV1(double), CV2(int), true);

   // test with three template parameters
   TEST_TTR(CV1(bool), CV2(int), bool, true);
   TEST_TTR(CV1(bool), CV2(double), bool, true);
   TEST_TTR(CV1(int), CV2(bool), bool, true);
   TEST_TTR(CV1(int), CV2(double), bool, true);
   TEST_TTR(CV1(double), CV2(bool), bool, true);
   TEST_TTR(CV1(double), CV2(int), bool, true);
   TEST_TTR(CV1(bool), CV2(int), tag, false);
   TEST_TTR(CV1(bool), CV2(double), tag, false);
   TEST_TTR(CV1(int), CV2(bool), tag, false);
   TEST_TTR(CV1(int), CV2(double), tag, false);
   TEST_TTR(CV1(double), CV2(bool), tag, false);
   TEST_TTR(CV1(double), CV2(int), tag, false);

#	undef CV1
#	define CV1(T) T
#	undef CV2
#	define CV2(T) const volatile T&
   // test with only two template parameters
   TEST_TT(CV1(bool), CV2(int), true);
   TEST_TT(CV1(bool), CV2(double), true);
   TEST_TT(CV1(int), CV2(bool), true);
   TEST_TT(CV1(int), CV2(double), true);
   TEST_TT(CV1(double), CV2(bool), true);
   TEST_TT(CV1(double), CV2(int), true);

   // test with three template parameters
   TEST_TTR(CV1(bool), CV2(int), bool, true);
   TEST_TTR(CV1(bool), CV2(double), bool, true);
   TEST_TTR(CV1(int), CV2(bool), bool, true);
   TEST_TTR(CV1(int), CV2(double), bool, true);
   TEST_TTR(CV1(double), CV2(bool), bool, true);
   TEST_TTR(CV1(double), CV2(int), bool, true);
   TEST_TTR(CV1(bool), CV2(int), tag, false);
   TEST_TTR(CV1(bool), CV2(double), tag, false);
   TEST_TTR(CV1(int), CV2(bool), tag, false);
   TEST_TTR(CV1(int), CV2(double), tag, false);
   TEST_TTR(CV1(double), CV2(bool), tag, false);
   TEST_TTR(CV1(double), CV2(int), tag, false);

#	undef CV1
#	define CV1(T) const T
#	undef CV2
#	define CV2(T) const T
   // test with only two template parameters
   TEST_TT(CV1(bool), CV2(int), false);
   TEST_TT(CV1(bool), CV2(double), false);
   TEST_TT(CV1(int), CV2(bool), false);
   TEST_TT(CV1(int), CV2(double), false);
   TEST_TT(CV1(double), CV2(bool), false);
   TEST_TT(CV1(double), CV2(int), false);

   // test with three template parameters
   TEST_TTR(CV1(bool), CV2(int), bool, false);
   TEST_TTR(CV1(bool), CV2(double), bool, false);
   TEST_TTR(CV1(int), CV2(bool), bool, false);
   TEST_TTR(CV1(int), CV2(double), bool, false);
   TEST_TTR(CV1(double), CV2(bool), bool, false);
   TEST_TTR(CV1(double), CV2(int), bool, false);
   TEST_TTR(CV1(bool), CV2(int), tag, false);
   TEST_TTR(CV1(bool), CV2(double), tag, false);
   TEST_TTR(CV1(int), CV2(bool), tag, false);
   TEST_TTR(CV1(int), CV2(double), tag, false);
   TEST_TTR(CV1(double), CV2(bool), tag, false);
   TEST_TTR(CV1(double), CV2(int), tag, false);

#	undef CV1
#	define CV1(T) const T&
#	undef CV2
#	define CV2(T) const T&
   // test with only two template parameters
   TEST_TT(CV1(bool), CV2(int), false);
   TEST_TT(CV1(bool), CV2(double), false);
   TEST_TT(CV1(int), CV2(bool), false);
   TEST_TT(CV1(int), CV2(double), false);
   TEST_TT(CV1(double), CV2(bool), false);
   TEST_TT(CV1(double), CV2(int), false);

   // test with three template parameters
   TEST_TTR(CV1(bool), CV2(int), bool, false);
   TEST_TTR(CV1(bool), CV2(double), bool, false);
   TEST_TTR(CV1(int), CV2(bool), bool, false);
   TEST_TTR(CV1(int), CV2(double), bool, false);
   TEST_TTR(CV1(double), CV2(bool), bool, false);
   TEST_TTR(CV1(double), CV2(int), bool, false);
   TEST_TTR(CV1(bool), CV2(int), tag, false);
   TEST_TTR(CV1(bool), CV2(double), tag, false);
   TEST_TTR(CV1(int), CV2(bool), tag, false);
   TEST_TTR(CV1(int), CV2(double), tag, false);
   TEST_TTR(CV1(double), CV2(bool), tag, false);
   TEST_TTR(CV1(double), CV2(int), tag, false);

#	undef CV1
#	define CV1(T) volatile T
#	undef CV2
#	define CV2(T) volatile T
   // test with only two template parameters
   TEST_TT(CV1(bool), CV2(int), true);
   TEST_TT(CV1(bool), CV2(double), true);
   TEST_TT(CV1(int), CV2(bool), true);
   TEST_TT(CV1(int), CV2(double), true);
   TEST_TT(CV1(double), CV2(bool), true);
   TEST_TT(CV1(double), CV2(int), true);

   // test with three template parameters
   TEST_TTR(CV1(bool), CV2(int), bool, true);
   TEST_TTR(CV1(bool), CV2(double), bool, true);
   TEST_TTR(CV1(int), CV2(bool), bool, true);
   TEST_TTR(CV1(int), CV2(double), bool, true);
   TEST_TTR(CV1(double), CV2(bool), bool, true);
   TEST_TTR(CV1(double), CV2(int), bool, true);
   TEST_TTR(CV1(bool), CV2(int), tag, false);
   TEST_TTR(CV1(bool), CV2(double), tag, false);
   TEST_TTR(CV1(int), CV2(bool), tag, false);
   TEST_TTR(CV1(int), CV2(double), tag, false);
   TEST_TTR(CV1(double), CV2(bool), tag, false);
   TEST_TTR(CV1(double), CV2(int), tag, false);

#	undef CV1
#	define CV1(T) volatile T&
#	undef CV2
#	define CV2(T) volatile T&
   // test with only two template parameters
   TEST_TT(CV1(bool), CV2(int), true);
   TEST_TT(CV1(bool), CV2(double), true);
   TEST_TT(CV1(int), CV2(bool), true);
   TEST_TT(CV1(int), CV2(double), true);
   TEST_TT(CV1(double), CV2(bool), true);
   TEST_TT(CV1(double), CV2(int), true);

   // test with three template parameters
   TEST_TTR(CV1(bool), CV2(int), bool, true);
   TEST_TTR(CV1(bool), CV2(double), bool, true);
   TEST_TTR(CV1(int), CV2(bool), bool, true);
   TEST_TTR(CV1(int), CV2(double), bool, true);
   TEST_TTR(CV1(double), CV2(bool), bool, true);
   TEST_TTR(CV1(double), CV2(int), bool, true);
   TEST_TTR(CV1(bool), CV2(int), tag, false);
   TEST_TTR(CV1(bool), CV2(double), tag, false);
   TEST_TTR(CV1(int), CV2(bool), tag, false);
   TEST_TTR(CV1(int), CV2(double), tag, false);
   TEST_TTR(CV1(double), CV2(bool), tag, false);
   TEST_TTR(CV1(double), CV2(int), tag, false);

#	undef CV1
#	define CV1(T) const volatile T
#	undef CV2
#	define CV2(T) const volatile T
   // test with only two template parameters
   TEST_TT(CV1(bool), CV2(int), false);
   TEST_TT(CV1(bool), CV2(double), false);
   TEST_TT(CV1(int), CV2(bool), false);
   TEST_TT(CV1(int), CV2(double), false);
   TEST_TT(CV1(double), CV2(bool), false);
   TEST_TT(CV1(double), CV2(int), false);

   // test with three template parameters
   TEST_TTR(CV1(bool), CV2(int), bool, false);
   TEST_TTR(CV1(bool), CV2(double), bool, false);
   TEST_TTR(CV1(int), CV2(bool), bool, false);
   TEST_TTR(CV1(int), CV2(double), bool, false);
   TEST_TTR(CV1(double), CV2(bool), bool, false);
   TEST_TTR(CV1(double), CV2(int), bool, false);
   TEST_TTR(CV1(bool), CV2(int), tag, false);
   TEST_TTR(CV1(bool), CV2(double), tag, false);
   TEST_TTR(CV1(int), CV2(bool), tag, false);
   TEST_TTR(CV1(int), CV2(double), tag, false);
   TEST_TTR(CV1(double), CV2(bool), tag, false);
   TEST_TTR(CV1(double), CV2(int), tag, false);

#	undef CV1
#	define CV1(T) const volatile T&
#	undef CV2
#	define CV2(T) const volatile T&
   // test with only two template parameters
   TEST_TT(CV1(bool), CV2(int), false);
   TEST_TT(CV1(bool), CV2(double), false);
   TEST_TT(CV1(int), CV2(bool), false);
   TEST_TT(CV1(int), CV2(double), false);
   TEST_TT(CV1(double), CV2(bool), false);
   TEST_TT(CV1(double), CV2(int), false);

   // test with three template parameters
   TEST_TTR(CV1(bool), CV2(int), bool, false);
   TEST_TTR(CV1(bool), CV2(double), bool, false);
   TEST_TTR(CV1(int), CV2(bool), bool, false);
   TEST_TTR(CV1(int), CV2(double), bool, false);
   TEST_TTR(CV1(double), CV2(bool), bool, false);
   TEST_TTR(CV1(double), CV2(int), bool, false);
   TEST_TTR(CV1(bool), CV2(int), tag, false);
   TEST_TTR(CV1(bool), CV2(double), tag, false);
   TEST_TTR(CV1(int), CV2(bool), tag, false);
   TEST_TTR(CV1(int), CV2(double), tag, false);
   TEST_TTR(CV1(double), CV2(bool), tag, false);
   TEST_TTR(CV1(double), CV2(int), tag, false);

   // pointers
   TEST_TT(void*, bool, false);
   TEST_TT(void*, int, false);
   TEST_TT(void*, double, false);
   TEST_TT(void*, A, false);
   TEST_TT(void*, B, false);
   TEST_TT(bool*, bool, true);
   TEST_TT(bool*, int, true);
   TEST_TT(bool*, double, false);
   TEST_TT(bool*, A, false);
   TEST_TT(bool*, B, false);
   TEST_TT(int*, bool, true);
   TEST_TT(int*, int, true);
   TEST_TT(int*, double, false);
   TEST_TT(int*, A, false);
   TEST_TT(int*, B, false);
   TEST_TT(double*, bool, true);
   TEST_TT(double*, int, true);
   TEST_TT(double*, double, false);
   TEST_TT(double*, A, false);
   TEST_TT(double*, B, false);
   TEST_TT(A*, bool, true);
   TEST_TT(A*, int, true);
   TEST_TT(A*, double, false);
   TEST_TT(A*, A, false);
   TEST_TT(A*, B, false);
   TEST_TT(B*, bool, true);
   TEST_TT(B*, int, true);
   TEST_TT(B*, double, false);
   TEST_TT(B*, A, false);
   TEST_TT(B*, B, false);
   TEST_TT(bool, void*, false);
   TEST_TT(bool, bool*, true);
   TEST_TT(bool, int*, true);
   TEST_TT(bool, double*, true);
   TEST_TT(bool, A*, true);
   TEST_TT(bool, B*, true);
   TEST_TT(int, void*, false);
   TEST_TT(int, bool*, false);
   TEST_TT(int, int*, false);
   TEST_TT(int, double*, false);
   TEST_TT(int, A*, false);
   TEST_TT(int, B*, false);
   TEST_TT(double, void*, false);
   TEST_TT(double, bool*, false);
   TEST_TT(double, int*, false);
   TEST_TT(double, double*, false);
   TEST_TT(double, A*, false);
   TEST_TT(double, B*, false);
   TEST_TT(A, void*, false);
   TEST_TT(A, bool*, false);
   TEST_TT(A, int*, false);
   TEST_TT(A, double*, false);
   TEST_TT(A, A*, false);
   TEST_TT(A, B*, false);
   TEST_TT(B, void*, false);
   TEST_TT(B, bool*, false);
   TEST_TT(B, int*, false);
   TEST_TT(B, double*, false);
   TEST_TT(B, A*, false);
   TEST_TT(B, B*, false);
   TEST_TT(void*, void*, false);
   TEST_TT(void*, bool*, false);
   TEST_TT(void*, int*, false);
   TEST_TT(void*, double*, false);
   TEST_TT(void*, A*, false);
   TEST_TT(void*, B*, false);
   TEST_TT(bool*, void*, false);
   TEST_TT(bool*, bool*, false);
   TEST_TT(bool*, int*, false);
   TEST_TT(bool*, double*, false);
   TEST_TT(bool*, A*, false);
   TEST_TT(bool*, B*, false);
   TEST_TT(int*, void*, false);
   TEST_TT(int*, bool*, false);
   TEST_TT(int*, int*, false);
   TEST_TT(int*, double*, false);
   TEST_TT(int*, A*, false);
   TEST_TT(int*, B*, false);
   TEST_TT(double*, void*, false);
   TEST_TT(double*, bool*, false);
   TEST_TT(double*, int*, false);
   TEST_TT(double*, double*, false);
   TEST_TT(double*, A*, false);
   TEST_TT(double*, B*, false);
   TEST_TT(A*, void*, false);
   TEST_TT(A*, bool*, false);
   TEST_TT(A*, int*, false);
   TEST_TT(A*, double*, false);
   TEST_TT(A*, A*, false);
   TEST_TT(A*, B*, false);
   TEST_TT(B*, void*, false);
   TEST_TT(B*, bool*, false);
   TEST_TT(B*, int*, false);
   TEST_TT(B*, double*, false);
   TEST_TT(B*, A*, false);
   TEST_TT(B*, B*, false);
   TEST_TT(C, void*, true);
   TEST_TT(D, void*, false);
   TEST_TT(void*, C, false);
   TEST_TT(void*, D, true);
   TEST_TT(C, D, true);
}
}