#!/usr/bin/env python
##Purpose:
##  Read pickle file containing performance data
##  apply filter to it, print filtered data.
##===============================================
from __future__ import print_function 
import sys, pickle
from collections import namedtuple
from enums import enumeration
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
  d_ndx=enumeration(domain_names_lst).enumerators()
  print("domain_indices=",d_ndx)
  filt_fun=lambda (d_lst,r_lst)\
    : True
  filt_dr=filter\
    ( filt_fun
    , domain_range_values
    )
  if False:
    print(":filt_dr=")
    print_domain_range(filt_dr)
  sort_fun=lambda (d_lst,r_lst)\
    : ( d_lst[d_ndx.TUPLE_SIZE]
      , d_lst[d_ndx.TREE_DEPTH]
      , d_lst[d_ndx.TUPLE_TEMPLATED_CTOR]
      , d_lst[d_ndx.iter]
      , d_lst[d_ndx.TUPLE_IMPL]
      , d_lst[d_ndx.compiler]
      )  
  sort_dr=sorted\
    ( filt_dr
    , key=sort_fun
    )
  if True:
    print(":sort_dr=")
    print_domain_range(sort_dr)
  return result

if __name__ == '__main__':
    ret = main(sys.argv)
    if ret is not None:
        sys.exit(ret)
