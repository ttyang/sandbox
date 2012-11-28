"""
Map from names to format codes of system time command.
"""
from __future__ import print_function 

#mapping of name of measurement to format code for measurement 
#in --format argument to system time command.
TUPLE_NAME_CODES=\
    ( ('UserTime', ('%U',float))
    , ('SystemTime', ('%S',float))
    , ('ElapsedTime', ('%e',float))
    , ('MajorPageFaults', ('%I',long))
    , ('MaxResidentSetSize', ('%M',long))
    , ('Swaps', ('%W',long))
    , ('ContextSwitches', ('%w',long))
    )

DICT_NAME_CODE=dict(TUPLE_NAME_CODES)

def lst_names(): 
    """the names in TUPLE_NAME_CODES"""
    return map(lambda (name,code):name,TUPLE_NAME_CODES)

def fmtcode(name):
    """the format code for name"""
    return DICT_NAME_CODE[name][0]

def convert_str(name,str):
    """Convert str into value appropriate for name"""
    return DICT_NAME_CODE[name][1](str)

if __name__ == '__main__':
    print(":DICT_NAME_CODE=",DICT_NAME_CODE)
    print(":names=",lst_names())
