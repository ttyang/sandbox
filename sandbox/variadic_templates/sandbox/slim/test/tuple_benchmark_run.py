#!/usr/bin/env python3.1
"""
Run compilers on programs while recording resources usage.
"""
#from __future__ import print_function 
import sys
import subprocess
import collections
import functools

from tuple_benchmark_domain import *
from compiler_map import COMPILER_MAP
from tuple_benchmark_tags import TAG_TUPLE
import command_guage
import tuple_benchmark_filenames
import boost_root

BOOST_ROOT_PATH=boost_root.path()

IMPL_MAP_INC={}#implementation key -> -I include flags to compiler
IMPL_MAP_INC["horizontal"]=\
    ""\
  #
IMPL_MAP_INC["vertical"]=\
    " -I"+BOOST_ROOT_PATH\
  #
IMPL_MAP_INC["bcon12_horizontal"]=\
    " -I"+BOOST_ROOT_PATH\
  #
IMPL_MAP_INC["bcon12_vertical"]=\
    " -I"+BOOST_ROOT_PATH\
  #
IMPL_MAP_INC["compstor"]=\
    " -I"+BOOST_ROOT_PATH\
  + " -I"+BOOST_ROOT_PATH+"/sandbox/rw/variadic_templates"\
  #
IMPL_MAP_INC["std"]=\
    ""\
  #

def domain_defs(benchmark_suffix):
  """defines domains used in benchmark"""
  compiler_domain=['clangxx']
  niter=1#number of iterations to run with same values for other domains.
  impl_domain=\
    [ 'bcon12_horizontal'
    #, 'bcon12_vertical'
    ]
  tuple_size_domain_del=5
  tuple_sizes_domain=range(10,11,tuple_size_domain_del)
  name_domain=collections.OrderedDict\
    ( ( ('iter', lambda ignore:range(niter))
      , ('compiler', compilers(compiler_domain))
      , ('TUPLE_IMPL', impls(impl_domain))
      , ('TUPLE_SIZE', sizes(tuple_sizes_domain))
      , ('TUPLE_UNROLL_MAX', unroll_maxs())
      )
    )
  if benchmark_suffix == "mini" :
    name_domain['LAST_LESS']=lasts(4,tuple_size_domain_del)
  else:
    name_domain['TREE_DEPTH']=tree_depths(2,4,1)
    name_domain['TUPLE_TEMPLATED_CTOR']=templated_ctor_flags(1,2)
  domain_names=name_domain.keys()
  indices_type=collections.namedtuple('domain_indices',domain_names)
  domain_enumerators.indices=indices_type._make(range(len(domain_names)))
  return name_domain

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
  benchmark_run="_"
  #print("argv=",argv)
  iarg=1
  if len(argv)>=iarg:
    benchmark_suffix=argv[iarg]
  iarg+=1
  if len(argv)>=iarg:
    benchmark_run=argv[iarg]
  iarg+=1
  if len(argv)>=iarg:
    guage_spec=argv[iarg:]
  src_filename=tuple_benchmark_filenames.src_filename(benchmark_suffix)
  #print("src_filename=",src_filename)
  name_domain=domain_defs(benchmark_suffix)
  domain_names=list(name_domain.keys())
  domain_values=product_dep(name_domain.values())
  guage_class='command_guage.'+guage_spec[0]
  guage_args=functools.reduce(lambda args,arg:args+", "+arg, guage_spec[1:], "")
  guage_args='('+guage_args[1:]+')'
  guage_code=guage_class+guage_args
  guage_obj=eval(guage_code)
  guage_how=[guage_spec[0]]+guage_obj.names()
  run_fileobj=\
    open\
    ( tuple_benchmark_filenames.out_filename\
      ( 'run'
      , benchmark_suffix
      , guage_spec[0]
      , benchmark_run
      )
    , mode='w'
    )
  print(TAG_TUPLE.compilers+"[",file=run_fileobj)
  compiler_domain=name_domain['compiler']
  for compiler_name in compiler_domain.names:
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
  print(TAG_TUPLE.domain_names
    , domain_names,sep="", end=TAG_TUPLE.domain_names+"\n"
    , file=run_fileobj)
  print(TAG_TUPLE.range_how,guage_how,TAG_TUPLE.range_how,sep="",file=run_fileobj)
  macros_index=2
  macro_names=domain_names[macros_index:]
  for element in domain_values():
      print(TAG_TUPLE.domain_values
        , element, sep="", end=TAG_TUPLE.domain_values+"\n"
        , file=run_fileobj)
      print(TAG_TUPLE.domain_values
        , element, sep="", end=TAG_TUPLE.domain_values+"\n"
        )
      compiler_name, macro_vals=element[macros_index-1], element[macros_index:]
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
        + IMPL_MAP_INC[macro_vals[0]]+" "\
        + src_filename\
        #
      print(TAG_TUPLE.range_out+"[",file=run_fileobj)
      run_fileobj.flush()
      run_rc=guage_obj.measure(compiler_exe, compiler_args, run_fileobj)
      print("]"+TAG_TUPLE.range_out,file=run_fileobj)
      if run_rc != 0:
        return run_rc
  return result

if __name__ == '__main__':
    ret = main(sys.argv)
    if ret is not None:
        sys.exit(ret)
