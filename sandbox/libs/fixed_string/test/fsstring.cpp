// (C) Copyright 2004: Reece H. Dunn
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// test the string.h and stdio.h C-style string functions (fixed_string variants)

#include <boost/fixed_string/fsstring.hpp>
#include <boost/fixed_string/fsstdio.hpp>
#include <boost/test/minimal.hpp>

int main()
{
   const char *                        teststr = "C-style strings!";
   const int                           testlen = strlen( teststr );

   boost::fixed_string< 25 >           str1;
   boost::fixed_string< 20 >           str2;
   boost::fixed_string< 30 >           str3;

   // test strcpy and use it to test strcmp and strlen

   strcpy( str1, teststr );
   BOOST_TEST( strcmp( str1, teststr ) == 0 );
   BOOST_TEST( strcmp( str1, teststr ) == strcmp( teststr, str1 ));
   BOOST_TEST( strlen( str1 ) == testlen );

   // copy a different string and validate

   strcpy( str2, "12345" );
   BOOST_TEST( strcmp( str2, teststr ) != 0 );
   BOOST_TEST( strcmp( str2, "12345" ) == 0 );
   BOOST_TEST( strlen( str2 ) == 5 );

   // use the copied string to test strcat

   strcat( str2, "67890" );
   BOOST_TEST( strcmp( str2, "1234567890" ) == 0 );
   BOOST_TEST( strlen( str2 ) == 10 );

   // test sprintf

   BOOST_TEST( sprintf( str3, "1234%d7890", 56 ) == 10 );
   BOOST_TEST( strcmp( str3, "1234567890" ) == 0 );
   BOOST_TEST( strcmp( str2, str3 ) == 0 );
   BOOST_TEST( strlen( str3 ) == 10 );

   // test strcpy with a fixed_string as the 2nd argument

   strcpy( str3, str1 );
   BOOST_TEST( strcmp( str3, teststr ) == 0 );
   BOOST_TEST( strlen( str3 ) == testlen );

   return( 0 );
}
