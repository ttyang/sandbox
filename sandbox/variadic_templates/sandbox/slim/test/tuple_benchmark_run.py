#!/usr/bin/env python
"""
Run compilers on programs while recording resources usage.
"""
from __future__ import print_function 
from compiler_map import COMPILER_MAP
from tuple_benchmark_tags import TAG_TUPLE
import sys
from datetime import datetime
import subprocess

from tuple_benchmark_domain import *
import compiler_guage
import benchmark_prefix_name

def main(argv):
  """
  Inputs:
    argv[1] is optional benchmark_suffix to the benchmark main program name.
    argv[2] is optional run name, used in forming output file name.
  Outputs:
    output file(name depends on argv, see below) contains performance
    measurements of the compilation of benchmakr main program.
  """
  result = None
  default_suffix="mini"
  default_run="_"
  #print("argv=",argv)
  if len(argv)>1:
    benchmark_suffix=argv[1]
    if len(argv)>2:
      benchmark_run=argv[2]
    else:
      benchmark_run=default_run
  else:
    benchmark_suffix=default_suffix
    benchmark_run=default_run
  benchmark_presuffix=benchmark_prefix_name.name()+"."+benchmark_suffix
  benchmark_basename=benchmark_presuffix+".cpp"
  #print("benchmark_basename=",benchmark_basename)
  boost_root="/home/evansl/prog_dev/boost-svn/ro/boost_1_49_0"
  impl_map_inc={}#implementation key -> -I include flags to compiler
  if False:
    impl_map_inc["horizontal"]=\
        ""\
      #
  if False:
    impl_map_inc["vertical"]=\
        " -I"+boost_root\
      #
  if True:
    impl_map_inc["bcon12_horizontal"]=\
        ""\
      #
  if True:
    impl_map_inc["bcon12_vertical"]=\
        " -I"+boost_root\
      #
  if False:
    impl_map_inc["compstor"]=\
        " -I"+boost_root\
      + " -I"+boost_root+"/sandbox/rw/variadic_templates"\
      #
  if False:
    impl_map_inc["std"]=\
        ""\
      #
  tuple_min_size=5
  tuple_max_size=5
  tuple_del_size=5
  name_domain=[
      [ 'compiler', compilers(COMPILER_MAP.keys())]
    , [ 'TUPLE_IMPL', impls(impl_map_inc.keys())]
    , [ 'TUPLE_SIZE', sizes(range(tuple_min_size,tuple_max_size+1,tuple_del_size))]
    , [ 'TUPLE_UNROLL_MAX', unroll_max()]
    ]
  if benchmark_suffix == "mini" :
    name_domain.append( [ 'LAST_LESS', last(4,tuple_del_size)])
  else:
    name_domain.append( [ 'TREE_DEPTH', tree_depth(2,2,1)])
  domains=product_dep(
    map(lambda t: t[1], name_domain)
    )
  guage=compiler_guage.guage_time()
  measure_key=guage.__class__.__name__
  measure_out=open(benchmark_presuffix+"."+measure_key+"@"+benchmark_run+".txt",mode='w')
  print(TAG_TUPLE.compilers+"[",file=measure_out)
  for compiler_name in COMPILER_MAP.keys():
    (compiler_exe,compiler_flags)=COMPILER_MAP[compiler_name]
    print("compiler_name:",compiler_name,file=measure_out)
    print(TAG_TUPLE.version+"[",file=measure_out)
    measure_out.flush()
    rc=subprocess.call(
        compiler_exe+" -v"
      , shell=True
      , stdout=measure_out
      , stderr=subprocess.STDOUT
      )
    if compiler_name == 'clangxx':
      print("compiler_exe:",compiler_exe,file=measure_out)
    print("]"+TAG_TUPLE.version,file=measure_out)
  print("]"+TAG_TUPLE.compilers,file=measure_out)
  domain_names=list(map(lambda t:t[0],name_domain))
  print(TAG_TUPLE.domain_names,domain_names,sep="",end=TAG_TUPLE.domain_names+"\n",file=measure_out)
  macro_names=domain_names[1:]
  for element in domains():
      print(TAG_TUPLE.domain_values,element,sep="",end=TAG_TUPLE.domain_values+"\n",file=measure_out)
      compiler_name, macro_vals=element[0], element[1:]
      #print(":compiler_name=",compiler_name,":macro_vals=",macro_vals)
      compiler_macros=""
      for name,value in zip(macro_names,macro_vals):
        compiler_macros+=" -D"+name+"="+str(value)
      #print(":compiler_macros=",compiler_macros)
      (compiler_exe,compiler_flags)=COMPILER_MAP[compiler_name]
      #print(":compiler_exe=",compiler_exe,":compiler_flags=",compiler_flags)
      compiler_args=\
        " -c "\
        + compiler_flags+" "\
        + compiler_macros+" "\
        + impl_map_inc[macro_vals[0]]+" "\
        + benchmark_basename\
        #
      print(TAG_TUPLE.range_out+"[",file=measure_out)
      measure_out.flush()
      measure_rc=guage.measure(compiler_exe, compiler_args, measure_out)
      print("]"+TAG_TUPLE.range_out,file=measure_out)
      if measure_rc != 0:
        return measure_rc
  return result

if __name__ == '__main__':
    ret = main(sys.argv)
    if ret is not None:
        sys.exit(ret)
