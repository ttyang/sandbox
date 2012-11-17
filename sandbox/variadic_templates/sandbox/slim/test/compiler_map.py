"""
  Provide map from compiler short name to
  a tuple of:
    1) compiler location in file system
    2) compiler options
"""

COMPILER_MAP={}

if True:
  COMPILER_MAP["gcc4_8"]=(
         "/home/evansl/download/gcc/4.8-20121028/install/bin/g++"
       , "-std=gnu++11"
       )
if True:
  COMPILER_MAP["clangxx"]=(
         "/home/evansl/download/llvm/svn/build/Release/bin/clang"
       , "-std=c++11 -cxx-isystem /home/evansl/download/llvm/svn/llvm/projects/libcxx/include"
       )
