#!/usr/bin/env python
##Purpose:
##  Parse the range output in the file produced by
##  tuple_benchmark_run.py
##===============================================
from __future__ import print_function 
import sys, re, pickle
from tuple_benchmark_tags import TAG_TUPLE
from print_domain_range import print_domain_range

debug_print=0

import abc

class parse_range_abstract:
    """
    Abstract class for parsing output from compiler performance measurement.
    """
    __metaclass__=abc.ABCMeta

    @abc.abstractmethod
    def parse(range_str):
      """
      range_str is a string output from compiler performance measurement.
      This method turns that into a list or range values 
      which are then returned.
      """
      pass
  
class parse_range_time:
    """
    Concrete for parsing output from compiler performance measurement
    made with system time command.
    """

    def __init__(self):
        self.range_names=['user','system','elapsed']
        range_values_pat\
            ="^"\
            +self.range_names[0]\
            +":(.*) "\
            +self.range_names[1]\
            +":(.*) "\
            +self.range_names[2]\
            +":(.*)$"
        self.range_values_re=re.compile(range_values_pat)

    def names(self):
        return self.range_names

    def parse(self,range_values_str):
        found=self.range_values_re.search(range_values_str)
        range_values_lst=[]
        n=len(self.range_names)
        for i in range(1,1+n):
            range_val=float(found.group(i))
            range_values_lst.append(range_val)
        return range_values_lst

def main(argv):
  result = None
  if len(argv)>1:
    run_file_inp=open(argv[1],mode='r')
  else:
    print("***expected input filename as argv[1]")
    return 1
  line_count=0
  end_compilers=re.compile("^]"+TAG_TUPLE.compilers+"$")
  for line_str in run_file_inp:
    line_count+=1
    found=end_compilers.search(line_str)
    if debug_print:
      print(":line=",line_str,end="")
      print(":found=",found)
    if found:
      break
  line_str=run_file_inp.next()
  line_count+=1
  domain_names_re=re.compile("^"+TAG_TUPLE.domain_names+"(\[.*\])"+TAG_TUPLE.domain_names+"$")
  found=domain_names_re.search(line_str)
  domain_names_lst=eval(found.group(1))
  range_parser=parse_range_time()
  print(":domain_names_lst=",domain_names_lst)
  range_names_lst=range_parser.names()
  print(":range_names_lst=",range_names_lst)
  end_range=re.compile(".*]"+TAG_TUPLE.range_out+"$")
  domain_values_pat="^"+TAG_TUPLE.domain_values+"(\[.*\])"+TAG_TUPLE.domain_values
  domain_values_re=re.compile(domain_values_pat)
  domain_range_values=[]#list_of(tuple_of(list_of(domain_values),list_of(range_values)))
  for line_str in run_file_inp:#{
    #Body of this loop appends next tuple of(list_of(domain_values),list_of(range_values))
    line_count+=1
    if debug_print:
      print(":line[",line_count,"]=",line_str,end="")
    found=domain_values_re.search(line_str)
    if not found:
      print("*** on line",line_count,"expected '"+TAG_TUPLE.domain_values+"' but found:"+line_str)
      return 1
    domain_values_lst=eval(found.group(1))#list_of(domain_values)
    line_str=run_file_inp.next()#should be 'range_out['
    line_count+=1
    range_values_str=""#will be everthing between the TAG_TUPLE.range_out begin/end tags.
    for line_str in run_file_inp:#{
      line_count+=1
      if debug_print:
        print(":line("+TAG_TUPLE.range_out+")=",line_str,end="")
      found=end_range.search(line_str)
      if found:
        break
      range_values_str+=line_str
    #}for line_str in run_file_inp:
    range_values_lst=range_parser.parse(range_values_str)
    domain_range_values.append((domain_values_lst,range_values_lst))
    #^appends tuple_of(list_of(domain_values),list_of(range_values))
  #}for line_str in run_fle_inp:
  print_domain_range(domain_range_values)
  domain_range_out=open('domain_range.pkl','wb')
  pickle.dump((domain_names_lst,range_names_lst,domain_range_values),domain_range_out)
  domain_range_out.close()
  return result

if __name__ == '__main__':
    ret = main(sys.argv)
    if ret is not None:
        sys.exit(ret)
