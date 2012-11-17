"""
Print to stdout a prefix of the name of the c++ source code
benchmark.
"""
from __future__ import print_function 
from sys import argv

def src_prefix():
    return "tuple.benchmark"

def src_basename(src_suffix):
    return src_prefix()+"."+src_suffix

def out_basename(src_suffix,guage,run):
    return src_basename(src_suffix)+"."+guage+"@"+run

if __name__ == '__main__':
    out_name=src_basename(argv[1])
    if len(argv)>2:
      out_name=out_basename(argv[1],argv[2],argv[3])
    print(out_name)
