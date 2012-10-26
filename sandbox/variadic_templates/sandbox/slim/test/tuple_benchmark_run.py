#!/usr/bin/python3.1
from tuple_benchmark_domain import *
import subprocess
import collections

def measure_time(compiler_exe, compiler_args, measure_out):
  compile_cmd=compiler_exe+compiler_args
  time_format='"user:%U system:%S elapsed:%e"'
  measure_cmd='time --format '+time_format+' '+compile_cmd
  print(":measure_cmd=",measure_cmd)
  rc=subprocess.call(
      measure_cmd
    , shell=True
    , stdout=measure_out
    , stderr=subprocess.STDOUT
    )
  print(":rc=",rc)

def measure_ftime(compiler_exe, compiler_args, measure_out):
  measure_cmd=compiler_exe+" -ftime-report "+compiler_args
  print(":measure_cmd=",measure_cmd)
  rc=subprocess.call(
      measure_cmd
    , shell=True
    , stdout=measure_out
    , stderr=subprocess.STDOUT
    )
  print(":rc=",rc)

if __name__ == '__main__':
  tuple_min_size=10
  tuple_max_size=40
  tuple_del_size=10
  boost_root="/home/evansl/prog_dev/boost-svn/ro/boost_1_49_0"
  compiler_map={}
  if False:
    compiler_map["gcc4_8"]=(
           "/home/evansl/download/gcc/4.8-20120923/install/bin/g++"
         , "-std=gnu++11"
         )
  if True:
    compiler_map["clangxx"]=(
           "/home/evansl/download/llvm/svn/build/Release/bin/clang"
         , "-std=c++11 -cxx-isystem /home/evansl/download/llvm/svn/llvm/projects/libcxx/include"
         )
  impl_map_hpp={}#implementation key -> implementation include .hpp file.
  impl_map_hpp["horizontal"]="tuple_impl_horizontal.hpp"
  impl_map_hpp["vertical"  ]="tuple_impl_vertical.hpp"
  impl_map_hpp["bcon12_horizontal"]="tuple_impl_bcon12_horizontal.hpp"
  impl_map_hpp["bcon12_vertical"  ]="tuple_impl_bcon12_vertical.hpp"
  #impl_map_hpp["std"       ]="tuple_impl_std.hpp"
  #impl_map_hpp["compstor"  ]="tuple_impl_compstor.hpp"
  impl_map_inc=collections.defaultdict(lambda:"")#implementation key -> -I include flags to compiler
  impl_map_inc["vertical"  ]=\
      " -I"+boost_root\
    #
  impl_map_inc["bcon12_vertical"  ]=\
      " -I"+boost_root\
    #
  impl_map_inc["compstor"  ]=\
      " -I"+boost_root\
    + " -I"+boost_root+"/sandbox/rw/variadic_templates"\
    #
  name_domain=[
      [ 'compiler', compilers(compiler_map.keys())]
    , [ 'TUPLE_IMPL', impls(impl_map_hpp.keys())]
    , [ 'TUPLE_SIZE', sizes(range(tuple_min_size,tuple_max_size+1,tuple_del_size))]
    , [ 'LAST_LESS', last(4,tuple_del_size)]
    , [ 'TUPLE_CHUNK', chunk()]
    ]
  domain=product_dep(
    map(lambda t: t[1], name_domain)
    )
  measures={
      'time'  : measure_time
    , 'ftime' : measure_ftime
    }
  measure_key='time'
  benchmark="tuple.benchmark.mini"
  measure_out=open(benchmark+"."+measure_key+".txt",mode='w')
  for compiler_name in compiler_map.keys():
    (compiler_exe,compiler_flags)=compiler_map[compiler_name]
    print("compiler=",compiler_name,file=measure_out)
    print("version={",file=measure_out)
    measure_out.flush()
    rc=subprocess.call(
        compiler_exe+" -v"
      , shell=True
      , stdout=measure_out
      , stderr=subprocess.STDOUT
      )
    if compiler_name == 'clangxx':
      print("compiler_exe=",compiler_exe,file=measure_out)
    print("}",file=measure_out)
  print(list(map(lambda t: t[0], name_domain)),file=measure_out)
  for element in domain():
      print(element,file=measure_out)
      (compiler_name, impl_name, size, last, chk)=element
      #print(":compiler_name=",compiler_name,":impl_name=",impl_name,":size=",size,":last=",last)
      compiler_macros=\
          " -DTUPLE_IMPL="+impl_map_hpp[impl_name]\
        + " -DTUPLE_SIZE="+str(size)\
        + " -DLAST_LESS="+str(last)\
        + " -DTUPLE_CHUNK="+str(chk)
      #print(":compiler_macros=",compiler_macros)
      (compiler_exe,compiler_flags)=compiler_map[compiler_name]
      #print(":compiler_exe=",compiler_exe,":compiler_flags=",compiler_flags)
      compiler_args=\
        " -c "\
        + compiler_flags+" "\
        + compiler_macros+" "\
        + impl_map_inc[impl_name]+" "\
        + benchmark+".cpp"\
        #
      print("{",file=measure_out)
      measure_out.flush()
      measures[measure_key](compiler_exe, compiler_args, measure_out)
      print("}",file=measure_out)



