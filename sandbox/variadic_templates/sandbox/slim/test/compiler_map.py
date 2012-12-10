#!/usr/bin/env python3.1
"""
  Provide map from compiler short name to
  a tuple of:
    1) compiler location in file system
    2) compiler options
"""

COMPILER_MAP={}

COMPILER_MAP["gcc4_8"]=(
       "/home/evansl/download/gcc/4.8-20121028/install/bin/g++"
     , "-std=gnu++11"
     )
COMPILER_MAP["clangxx"]=(
       "/home/evansl/download/llvm/svn/build/Release/bin/clang"
     , "-std=c++11 -cxx-isystem /home/evansl/download/llvm/svn/llvm/projects/libcxx/include"
     )
COMPILER_MAP["clangxx_prof"]=(
       "/home/evansl/download/llvm/svn/build/Release+Profile/bin/clang"
     , "-std=c++11 -cxx-isystem /home/evansl/download/llvm/svn/llvm/projects/libcxx/include"
     )
COMPILER_MAP["clangxx_debass"]=(
       "/home/evansl/download/llvm/svn/build/Debug+Asserts/bin/clang"
     , "-std=c++11 -cxx-isystem /home/evansl/download/llvm/svn/llvm/projects/libcxx/include"
     )

import sys

if __name__ == '__main__':
    if len(sys.argv) == 1 :
      if False:  
        print(COMPILER_MAP)
      else:
        clang_prof=COMPILER_MAP["clangxx_prof"][0]
        print("clang_prof=",clang_prof)
    else:
      print(sys.argv[1],":",COMPILER_MAP[sys.argv[1]])

