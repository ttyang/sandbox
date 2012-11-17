#!/usr/bin/env python
##Purpose:
##  Read pickle file containing performance data
##  apply filter to it, print filtered data.
##===============================================
from __future__ import print_function 
import sys, pickle
from collections import namedtuple
from print_domain_range import print_domain_range

def main(argv):
  result = None
  if len(argv)>1:
    pkl_file_inp=open(argv[1],mode='rb')
  else:
    print("***expected input pickle filename as argv[1]")
    return 1
  (domain_names_lst,range_names_lst,domain_range_values)=pickle.load(pkl_file_inp)
  print(":domain_names_lst=",domain_names_lst)
  print(":range_names_lst=",range_names_lst)
  #print(":domain_range_values=")
  #print_domain_range(domain_range_values)
  domain_names_type=namedtuple('domain_names_indices',domain_names_lst)
  d_ndx=domain_names_type._make(range(len(domain_names_lst)))
  #print("domain_indices=",d_ndx)
  filt_dr=filter\
    ( lambda (d_lst,r_lst)
      :   d_lst[d_ndx.compiler] == 'gcc4_8'
      and d_lst[d_ndx.TUPLE_SIZE] == 15
    , domain_range_values
    )
  print(":filt_dr=")
  print_domain_range(filt_dr)
  return result

if __name__ == '__main__':
    ret = main(sys.argv)
    if ret is not None:
        sys.exit(ret)
