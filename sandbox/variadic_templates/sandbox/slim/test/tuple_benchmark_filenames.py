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

def src_ext():
    return "cpp"

def src_filename(src_suffix):
    return src_basename(src_suffix)+"."+src_ext()

def out_suffix(guage,run_id):
    return guage+"."+run_id

def run_basename(src_suffix,guage,run_id):
    return src_basename(src_suffix)+"."+out_suffix(guage,run_id)

def run_ext():
    return "run.txt"

def pkl_ext():
    return "pkl.txt"

def filt_ext():
    return "filt.txt"

def out_filename(out_ext,src_suffix,guage,run_id):
    return run_basename(src_suffix,guage,run_id)+"."+eval(out_ext+"_ext()")

if __name__ == '__main__':
    print(apply(eval(argv[1]),argv[2:]),end="")
