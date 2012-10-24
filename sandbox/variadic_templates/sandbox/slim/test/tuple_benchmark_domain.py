#Purpose:
#  Provide classes for defining the "domain"
#  of the tuple benchmark.  A domain is all
#  the various inputs to the benchmark.
#  For example:
#    1) the particular compilers used to compiler the benchmark.
#    2) the values of various macros used in the source code.
#
from product_dep import product_dep

class compilers(object):
  def __init__(self, names):
    self.names=names
  def __call__(self,xs):
    return self.names

class impls(object):
  "tuple implementations"
  def __init__(self, names):
    self.names=names
  def __call__(self,xs):
    return self.names

class sizes(object):
  "TUPLE_SIZE macro values"
  def __init__(self, tuple_sizes):
    self.sizes=tuple_sizes
  def __call__(self,xs):
    return self.sizes

class last(object):
  "LAST_LESS macro values"
  def __init__(self, size_start, size_step=1):
    self.start=size_start
    self.step=size_step
  def __call__(self,xs):
    return range(
        self.start
      , self.start+1#xs[2]+1 #xs[2] is current tuple_size
      , self.step
      )

class chunk(object):
  "TUPLE_CHUNK macro values(only used with vertical impl)"
  def __init__(self, size_start=2, size_step=4):
    self.start=size_start
    self.step=size_step
  def __call__(self,xs):
    if xs[1] == 'vertical':
      if False:
        return range(
            xs[2]#self.start
          , xs[2]+1+self.step #xs[2] is current tuple_size
          , self.step
          )
      else:
        return [10]
    return [-1]

if __name__ == '__main__':
  tuple_max_size=8
  tuple_min_size=4
  tuple_del_size=2
  domain=product_dep( 
    [ compilers(["compiler1","compiler2"])
    , impls(["impl1","vertical"])
    , sizes(range(tuple_min_size,tuple_max_size+1,tuple_del_size))
    , last(tuple_min_size,tuple_del_size)
    , chunk()
    ])
  for element in domain():
      print(element)
