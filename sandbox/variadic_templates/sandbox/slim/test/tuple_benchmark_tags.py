"""
Tags (in sense of xml tags) delimiting the output of tuple_benchmark_run.py
"""
from collections import namedtuple
tag_names=\
  [ 'compilers'
  , 'version'
  , 'domain_names'
  , 'domain_values'
  , 'range_how'
  , 'range_out'
  ]
tag_tuple=namedtuple\
  ( 'tag_tuple'
  , tag_names
  )
TAG_TUPLE=tag_tuple._make(tag_names)

if __name__ == '__main__':
    print(TAG_TUPLE)
