"""
Map from names to format codes of system time command.
"""
from __future__ import print_function 

#mapping of name of measurement to format code for measurement 
#in --format argument to system time command.
TUPLE_NAME_CODES=\
    ( ('UserTime','%U')
    , ('SystemTime','%S')
    , ('ElapsedTime','%e')
    , ('MajorPageFaults', '%I')
    , ('MaxResidentSetSize', '%M')
    , ('Swaps', '%W')
    , ('ContextSwitches', '%w')
    )

DICT_NAME_CODE=dict(TUPLE_NAME_CODES)

def lst_names(): 
    """the names in TUPLE_NAME_CODES"""
    return map(lambda (name,code):name,TUPLE_NAME_CODES)

def fmtcode(name):
    """the format code for name"""
    return DICT_NAME_CODE[name]

if __name__ == '__main__':
    print(":DICT_NAME_CODE=",DICT_NAME_CODE)
    print(":names=",lst_names())
