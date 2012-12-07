#Purpose:
#  Provide classes for defining the "domain"
#  of the tuple benchmark.  A domain is all
#  the various inputs to the benchmark.
#  For example:
#    1) the particular compilers used to compile the benchmark.
#    2) the values of various macros used in the source code.
#
from __future__ import print_function 
from product_dep import product_dep

class domain_enumerators:
  indices=None
  #Above will be named indices to the domains.(set elsewhere).

class compilers(object):
  """compiler abbreviations"""
  def __init__(self, names):
    self.names=names
  def __call__(self,xs):
    return self.names

class impls(object):
  """TUPLE_IMPL macro values(which are tuple implementation abbreviations)."""
  def __init__(self, names):
    self.names=names
  def __call__(self,xs):
    return self.names

class sizes(object):
  """TUPLE_SIZE macro values."""
  def __init__(self, tuple_sizes):
    self.sizes=tuple_sizes
  def __call__(self,xs):
    return self.sizes

class lasts(object):
  """LAST_LESS macro values(Only used in mini benchmark)."""
  def __init__(self, size_start, size_step=1):
    self.start=size_start
    self.step=size_step
  def __call__(self,xs):
    return range(
        self.start
      , self.start+1
      , self.step
      )

class unroll_maxs(object):
  """TUPLE_UNROLL_MAX macro values(only used with vertical impl)"""
  def __init__(self, size_start=2, size_step=4,):
    self.start=size_start
    self.step=size_step
  def __call__(self,xs):
    impl_ndx=domain_enumerators.indices.TUPLE_IMPL
    if ((xs[impl_ndx] == 'vertical') or (xs[impl_ndx] == 'bcon12_vertical')):
      if False:
        size_ndx=domain_enumerators.indices.TUPLE_SIZE
        return range(
            xs[size_ndx]
          , xs[size_ndx]+1+self.step
          , self.step
          )
      else:
        return [10]
    return [-1]

class tree_depths(object):
  """TREE_DEPTH macro values(only used in tree_builder benchmark)"""
  def __init__(self, depth_start=2, depth_finish_plus_1=4, depth_step=1):
    self.start=depth_start
    self.finish_plus_1=depth_finish_plus_1
    self.step=depth_step
  def __call__(self,xs):
    if True:
      ndx=domain_enumerators.indices
      result = range(self.start, self.finish_plus_1, self.step)
      if (   xs[ndx.compiler  ] == 'clangxx'
         and xs[ndx.TUPLE_IMPL] == 'bcon12_vertical'
         and xs[ndx.TUPLE_SIZE] > 10
         ):#Otherwise, clangxx takes way too long.
        result = range(self.start-1, self.finish_plus_1-1, self.step)
      return result
    else:
      return [2]

class templated_ctor_flags(object):
  """TUPLE_TEMPLATED_CTOR macro values(only used in tree_builder benchmark)"""
  def __init__(self, start=0, finish_plus_1=2):
    self.start=max(0,start)
    self.finish_plus_1=min(finish_plus_1,2)
  def __call__(self,xs):
    if True:
      return range(
          self.start
        , self.finish_plus_1
        , 1
        )
    else:
      return [0,1]

if __name__ == '__main__':
  tuple_max_size=8
  tuple_min_size=4
  tuple_del_size=2
  domain=product_dep( 
    [ compilers(["compiler1","compiler2"])
    , impls(["impl1","vertical"])
    , sizes(range(tuple_min_size,tuple_max_size+1,tuple_del_size))
    , lasts(tuple_min_size,tuple_del_size)
    , unroll_maxs()
    , templated_ctor_flags()
    ])
  for element in domain():
      print(element)
