//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <condition_variable>

// class condition_variable_any;

// condition_variable_any& operator=(const condition_variable_any&) = delete;

#include <condition_variable>
#include <cassert>

int main()
{
    std::condition_variable_any cv0;
    std::condition_variable_any cv1;
    cv1 = cv0;
}
