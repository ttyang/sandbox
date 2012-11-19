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
import tuple_benchmark_filenames
import boost_root

def main(argv):
  """
  Inputs:
    argv[1] indicates how compiler performance will be measured.
    argv[2] is optional benchmark_suffix to the benchmark main program name.
    argv[3] is optional run name, used in forming output file name.
            This may be useful if several runs are made with same options
            and maybe some averaging will be done over different runs.
  Outputs:
    output file(name depends on argv, see below) contains performance
    measurements of the compilation of benchmark main program.
  """
  result = None
  #set defaults for argv[1..3]
  benchmark_suffix="mini"
  guage_name="guage_time"
  benchmark_run="_"
  #print("argv=",argv)
  iarg=1
  if len(argv)>=iarg:
    benchmark_suffix=argv[iarg]
  iarg+=1
  if len(argv)>=iarg:
    guage_name=argv[iarg]
  iarg+=1
  if len(argv)>=iarg:
    benchmark_run=argv[iarg]
  src_filename=tuple_benchmark_filenames.src_filename(benchmark_suffix)
  #print("src_filename=",src_filename)
  boost_root_path=boost_root.path()
  impl_map_inc={}#implementation key -> -I include flags to compiler
  if False:
    impl_map_inc["horizontal"]=\
        ""\
      #
  if False:
    impl_map_inc["vertical"]=\
        " -I"+boost_root_path\
      #
  if True:
    impl_map_inc["bcon12_horizontal"]=\
        ""\
      #
  if True:
    impl_map_inc["bcon12_vertical"]=\
        " -I"+boost_root_path\
      #
  if False:
    impl_map_inc["compstor"]=\
        " -I"+boost_root_path\
      + " -I"+boost_root_path+"/sandbox/rw/variadic_templates"\
      #
  if False:
    impl_map_inc["std"]=\
        ""\
      #
  tuple_min_size=10
  tuple_max_size=15
  tuple_del_size=5
  name_domain=[
      [ 'compiler', compilers(COMPILER_MAP.keys())]
    , [ 'TUPLE_IMPL', impls(impl_map_inc.keys())]
    , [ 'TUPLE_SIZE', sizes(range(tuple_min_size,tuple_max_size+1,tuple_del_size))]
    , [ 'TUPLE_UNROLL_MAX', unroll_max()]
    ]
  guage_map=\
    { 'guage_time':compiler_guage.guage_time()
    , 'guage_ftime':compiler_guage.guage_ftime()
    }
  if benchmark_suffix == "mini" :
    name_domain.append( [ 'LAST_LESS', last(4,tuple_del_size)])
  else:
    name_domain.append( [ 'TREE_DEPTH', tree_depth(2,4,1)])
  domains=product_dep(
    map(lambda t: t[1], name_domain)
    )
  guage_fun=guage_map[guage_name]
  run_fileobj=\
    open\
    ( tuple_benchmark_filenames.out_filename\
      ( 'run'
      , benchmark_suffix
      , guage_name
      , benchmark_run
      )
    , mode='w'
    )
  print(TAG_TUPLE.compilers+"[",file=run_fileobj)
  for compiler_name in COMPILER_MAP.keys():
    (compiler_exe,compiler_flags)=COMPILER_MAP[compiler_name]
    print("compiler_name:",compiler_name,file=run_fileobj)
    print(TAG_TUPLE.version+"[",file=run_fileobj)
    run_fileobj.flush()
    rc=subprocess.call(
        compiler_exe+" -v"
      , shell=True
      , stdout=run_fileobj
      , stderr=subprocess.STDOUT
      )
    if compiler_name == 'clangxx':
      print("compiler_exe:",compiler_exe,file=run_fileobj)
    print("]"+TAG_TUPLE.version,file=run_fileobj)
  print("]"+TAG_TUPLE.compilers,file=run_fileobj)
  domain_names=list(map(lambda t:t[0],name_domain))
  print(TAG_TUPLE.domain_names
    , domain_names,sep="", end=TAG_TUPLE.domain_names+"\n"
    , file=run_fileobj)
  macro_names=domain_names[1:]
  for element in domains():
      print(TAG_TUPLE.domain_values
        , element, sep="", end=TAG_TUPLE.domain_values+"\n"
        , file=run_fileobj)
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
        + src_filename\
        #
      print(TAG_TUPLE.range_out+"[",file=run_fileobj)
      run_fileobj.flush()
      run_rc=guage_fun.measure(compiler_exe, compiler_args, run_fileobj)
      print("]"+TAG_TUPLE.range_out,file=run_fileobj)
      if run_rc != 0:
        return run_rc
  return result

if __name__ == '__main__':
    ret = main(sys.argv)
    if ret is not None:
        sys.exit(ret)
