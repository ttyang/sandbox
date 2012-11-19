"""
print list((list(domain),list(range)) to stdout.
"""
from __future__ import print_function 

def print_domain_range(domain_range):
  for domain_vals,range_vals in domain_range:
    print(":domain=",domain_vals)
    #The reason for not using print("...",range_vals) instead
    #of the following is that the float values printed have
    #many decimal places.  For some strange reason, printing
    #each with separate print function call avoids that.
    print(":range=[",end="")
    for i,val in enumerate(range_vals):
      if i > 0: print(", ",end="")
      print(val,end="")
    print("]")
