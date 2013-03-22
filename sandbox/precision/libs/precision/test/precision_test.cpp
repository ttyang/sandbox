/*!
  \file
 \brief
 extended (and reduced) precision specifications.
 \version 1

 \details
*/

// Copyright Paul A. Bristow 2013

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file is written to be included from a Quickbook .qbk document.
// It can be compiled by the C++ compiler, and run. Any output can
// also be added here as comment or included or pasted in elsewhere.
// Caution: this file contains Quickbook markup as well as code
// and comments: don't change any of the special comment markups!

// This file also includes Doxygen-style documentation about the function of the code.
// See http://www.doxygen.org for details.

//[precision_example_1
// This is a snippet of code that can be included into a Quickbook program.

// Include Standard Library input output, for example.
#include <iostream>
using std::cout;
using std::endl;

// Include precision header(s).
#include <boost/precision/precision.hpp>

// Probably need to add #include directories to the project as well.

/*!
*/

int main()
{
  using boost::precision::myclass;

  cout << "Hello World!" << endl;
  return 0;

} // int main()

//] [/precision_example_1] // This ends the 1st snippet.

//[precision_example_2

/*`This is to show math symbols using Unicode.

*/

//] [/precision_example_2] // This ends the 2nd snippet.

/*

//[precision_example_output
//`[* Output from running precision_example.cpp is:]

------ Rebuild All started: Project: precision_example, Configuration: Debug Win32 ------
  precision_example.cpp
  precision_example.vcxproj -> J:\Cpp\precision_example\Debug\precision_example.exe
  Hello World!
========== Rebuild All: 1 succeeded, 0 failed, 0 skipped ==========


//] [/precision_example_output] // End of output snippet.

*/

