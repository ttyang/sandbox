#!/usr/bin/python
#
#  Copyright (c) 2008 Thomas Klimpel and Rutger ter Borg
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)
#

import re, os.path, copy
from types import StringType

# for debugging purposes
import pprint


global_type_map = { 
  'CHARACTER': 'char',
  'LOGICAL': 'logical_t', 
  'INTEGER': 'integer_t',
  'REAL': 'float', 
  'DOUBLE PRECISION': 'double' }
  
templates = {}




def value_type( fortran_type ):
  m_type_map = global_type_map
  m_type_map[ 'COMPLEX' ] = 'fcomplex_t'
  m_type_map[ 'COMPLEX*16' ] = 'dcomplex_t'
  m_type_map[ 'DOUBLE COMPLEX' ] = 'dcomplex_t'
  return m_type_map[ fortran_type ]
  
def c_type( name, properties ):
  m_type_map = global_type_map
  m_type_map[ 'COMPLEX' ] = 'fcomplex_t'
  m_type_map[ 'COMPLEX*16' ] = 'dcomplex_t'
  m_type_map[ 'DOUBLE COMPLEX' ] = 'dcomplex_t'

  result = m_type_map[ properties[ 'value_type' ] ];
  if properties[ 'io' ] == [ 'input' ]:
    result += ' const'
  result += '*'
  result += ' ' + name.lower()  # is this really needed?
  
  return result
  
  
def cpp_type( name, properties ):
  m_type_map = global_type_map
  m_type_map[ 'COMPLEX' ] = 'traits::complex_f'
  m_type_map[ 'COMPLEX*16' ] = 'traits::complex_d'
  m_type_map[ 'DOUBLE COMPLEX' ] = 'traits::complex_d'
  
  result = m_type_map[ properties[ 'value_type' ] ]
  
  if properties[ 'type' ] == 'scalar':
    if properties[ 'io' ] == [ 'input' ]:
      result += ' const'
    elif properties[ 'io' ] == [ 'external procedure' ]:
      result += '*'
    else:
      result += '&'
    
  if properties[ 'type' ] == 'vector' or properties[ 'type' ] == 'matrix':
    result += '*'
    
  result += ' ' + name.lower()
    
  return result
  
def call_c_type( name, properties ):
  result = ''
  if properties[ 'type' ] == 'vector' or properties[ 'type' ] == 'matrix':
    if properties[ 'value_type' ][ 0:7] == 'COMPLEX' or \
       properties[ 'value_type' ] == 'DOUBLE COMPLEX':
      result = 'traits::complex_ptr(' + name.lower() + ')'
    else:
      result = name.lower()
  elif properties[ 'type' ] == 'scalar':
    if properties[ 'value_type' ][ 0:7] == 'COMPLEX' or \
       properties[ 'value_type' ] == 'DOUBLE COMPLEX':
      result = 'traits::complex_ptr(&' + name.lower() + ')'
    else:
      result = '&' + name.lower()
  
  return result
  

def call_level0_type( name, properties, arg_map ):
  result = ''
  if properties[ 'type' ] == 'matrix':
    result = "traits::matrix_storage(" + name.lower() + ")"
  elif properties[ 'type' ] == 'vector':
    my_name = name.lower()
    if 'workspace' in properties[ 'io' ]:
      my_name = 'work.select(' + workspace_type( name, properties ) + '())'
    result = "traits::vector_storage(" + my_name + ")"
  elif properties.has_key( 'trait_type' ):
    if properties[ 'trait_type' ] == 'lda':
      result = "traits::leading_dimension(" + properties[ 'trait_of' ].lower() + ")"
    if properties[ 'trait_type' ] == 'num_columns':
      result = "traits::matrix_num_columns(" + properties[ 'trait_of' ].lower() + ")"
    if properties[ 'trait_type' ] == 'num_rows':
      result = "traits::matrix_num_rows(" + properties[ 'trait_of' ].lower() + ")"
    if properties[ 'trait_type' ] == 'size':
      my_name = properties[ 'trait_of' ].lower()
      referring_to_properties = arg_map[ properties[ 'trait_of' ] ]
      if 'workspace' in referring_to_properties[ 'io' ]:
        my_name = 'work.select(' + workspace_type( properties[ 'trait_of' ].lower(), referring_to_properties ) + \
                  '())'
      result = "traits::vector_size(" + my_name + ")"
    if properties[ 'trait_type' ] == 'uplo':
      result = "traits::matrix_uplo_tag(" + properties[ 'trait_of' ].lower() + ")"
    if properties[ 'trait_type' ] == 'stride':
      result = "traits::vector_stride(" + properties[ 'trait_of' ].lower() + ")"

  else:
    result = name.lower()
  return result


def level1_type( name, properties ):
  result = None
  if not properties.has_key( 'trait_of' ) and 'workspace' not in properties[ 'io' ]:
    if properties[ 'type' ] == 'matrix':
      result = "Matrix" + name + "& " + name.lower()
    elif properties[ 'type' ] == 'vector':
      result = "Vector" + name + "& " + name.lower()
    else:
      result = cpp_type( name, properties )
      if properties[ 'value_type' ] == 'REAL':
        result = result.replace( "float", "real_type" )
      if properties[ 'value_type' ] == 'DOUBLE PRECISION':
        result = result.replace( "double", "real_type" )
      if properties[ 'value_type' ][ 0:7] == 'COMPLEX' or \
        properties[ 'value_type' ] == 'DOUBLE COMPLEX':
         result = result.replace( "traits::complex_d", "value_type" )
         result = result.replace( "traits::complex_f", "value_type" )

  return result


def level2_type( name, properties ):
  result = level1_type( name, properties )
  if name == 'INFO' and 'output' in properties[ 'io' ]:
    result = None

  if result != None:
    if properties[ 'value_type' ] == 'REAL' or properties[ 'value_type' ] == 'DOUBLE PRECISION':
      result = result.replace( "real_type", "typename traits::$TYPEOF_FIRST_TYPENAME" + \
        "_traits< $FIRST_TYPENAME >::value_type" )
    if properties[ 'value_type' ][ 0:7] == 'COMPLEX' or \
      properties[ 'value_type' ] == 'DOUBLE COMPLEX':
      result = result.replace( "value_type", "typename traits::$TYPEOF_FIRST_TYPENAME" + \
        "_traits< $FIRST_TYPENAME >::value_type" )
  return result


def level1_typename( name, properties ):
  result = None
  if 'workspace' not in properties[ 'io' ]:
    if properties[ 'type' ] == 'matrix':
      result = "typename Matrix" + name
    if properties[ 'type' ] == 'vector':
      result = "typename Vector" + name
  return result


def level1_static_assert( name, properties ):
  result = None
  if 'workspace' not in properties[ 'io' ]:
    if properties[ 'type' ] == 'matrix':
      result = "typename traits::matrix_traits< " + level1_typename( name, properties ).replace( "typename ", "") + " >::value_type"
    elif properties[ 'type' ] == 'vector':
      result = "typename traits::vector_traits< " + level1_typename( name, properties ).replace( "typename ", "") + " >::value_type"
    elif properties[ 'type' ] == 'scalar':
      result = "TODO"
  return result


def nested_list_args( arg ):
  print "finding nested list arguments of", arg
  if arg == None:
    return None
  if type( arg ) == StringType:
    if re.compile( '^[A-Z]+$' ).match( arg ) == None:
      return [ None ]
    else:
      return [ arg.upper() ]
  
  # we are dealing with a list-type, e.g., 
  # [ '*', [ 'A', 'B' ] ]
  # [ 'A', 'B' ]
  result = []
  if re.compile( '^[A-Z]+$' ).match( arg[0] ) == None:
    for a in arg[1]:
      sub_result = nested_list_args( a )
      if sub_result != [ None ] and sub_result != None:
        for r in sub_result:
          if r not in result:
            result.append( r )

  else:
    for a in arg:
      result.append( a )

  print "returning ",result
  return result




def expand_nested_list( arg, arg_map, use_arg_map = True ):

  if arg == None:
    return '?None'
  print "Expanding nested list: ", arg, len(arg)
  if type( arg ) == StringType:
    print "Type is string"
    # .....
    if re.compile( '^[A-Z]+$' ).match( arg ) == None:
      return arg
    else:
      if use_arg_map:
        if not arg_map.has_key( arg ):
          return '?' + arg.upper()
        else:
          return arg_map[ arg ][ 'code' ][ 'call_level_0' ]
      else:
        return arg.lower()
    
  if arg[0] == '()':
    result = '(' + expand_nested_list( arg[1], arg_map, use_arg_map ) + ')'
    return result
    
  if arg[0] == 'max' or arg[0] == 'min':
    print "arg1: ", arg[1]
    result = 'std::' + arg[0] + '('
    i = 0
    for a in arg[1]:
      result += expand_nested_list( a, arg_map, use_arg_map )
      i += 1
      if i != len(arg[1]):
        result += ","
    result += ')'
    return result
  
  if arg[0] == '*' or arg[0] == '/' or arg[0] == '+' or arg[0] == '-':
    print "arg1: ", arg[1]
    arg_list = []
    for a in arg[1]:
      arg_list += [ expand_nested_list( a, arg_map, use_arg_map ) ]
    result = arg[0].join( arg_list )
    return result
  
  print "ERROR: Don't know what to do!!"
  return 'ERROR'

def level1_assert( name, properties, arg_map ):
  result = None
  
  if properties.has_key( 'assert_char' ):
    result = "assert( "
    result_array = []
    for char in properties[ 'assert_char' ]:
      result_array += [ call_level0_type( name, properties, arg_map ) + ' == \'' + char + '\'' ]
    result += " || ".join( result_array )
    result += " );"
    
  if properties.has_key( 'assert_ge' ) and not properties.has_key( 'workspace_query_for' ):
    result = "assert( " + call_level0_type( name, properties, arg_map ) + " >= " + expand_nested_list( properties[ 'assert_ge' ], arg_map ) + ' );'
      
  if 'workspace' in properties[ 'io' ]:
    min_workspace_call = min_workspace_call_type( name, properties, arg_map )
    if min_workspace_call == None:
      min_workspace_call = '$CALL_MIN_SIZE'
    result = 'assert( traits::vector_size(work.select(' + workspace_type( name, properties ) + '()) >= ' + \
             'min_size_' + name.lower() + '( ' + min_workspace_call + ' )));'

  # assert_size is vector-type specific
  elif properties.has_key( 'assert_size' ):
    result = "assert( traits::vector_size(" + call_level1_type( name, properties ) + ") >= " + \
      expand_nested_list( properties[ 'assert_size' ], arg_map ) + ' );'

  return result


def call_level1_type( name, properties ):
  result = None
  if level1_type( name, properties ) != None:
    result = name.lower()
  return result


def workspace_type( name, properties ):
  result = None
  if 'workspace' in properties[ 'io' ]:
    if properties[ 'value_type' ] == 'INTEGER':
      result = 'integer_t'
    elif properties[ 'value_type' ] == 'LOGICAL':
      result = 'bool'
    elif properties[ 'value_type' ] == 'REAL' or properties[ 'value_type' ] == 'DOUBLE PRECISION':
      result = 'real_type'
    else: 
      result = 'value_type'
  return result




def opt_workspace_pre_type( name, properties, arg_map ):
  result = None
  if 'workspace' in properties[ 'io' ]:
    if properties.has_key( 'workspace_query_by' ):
      result = workspace_type( name, properties ) + ' opt_size_' + name.lower() + ';'
    else:
      min_workspace_call = min_workspace_call_type( name, properties, arg_map )
      if min_workspace_call == None:
        min_workspace_call = '$CALL_MIN_SIZE'
      result = 'traits::detail::array< ' + workspace_type( name, properties ) + ' >' + \
               ' tmp_' + name.lower() + '( min_size_' + name.lower() + '( ' + min_workspace_call + ' ) );'
  return result


def opt_workspace_post_type( name, properties ):
  result = None
  if 'workspace' in properties[ 'io' ]:
    if properties.has_key( 'workspace_query_by' ):
      if properties['value_type'] == 'INTEGER':
        result = 'traits::detail::array< ' + workspace_type( name, properties ) + ' >' + \
               ' tmp_' + name.lower() + '( opt_size_' + name.lower() + ' );'
      else:
        result = 'traits::detail::array< ' + workspace_type( name, properties ) + ' >' + \
               ' tmp_' + name.lower() + '( traits::detail::to_int( opt_size_' + name.lower() + ' ) );'
  return result



def opt_workspace_query_type( name, properties, arg_map ):
  result = None
  if properties.has_key( 'workspace_query_for' ):
    result = '-1'
  elif 'workspace' in properties[ 'io' ]:
    if properties.has_key( 'workspace_query_by' ):
      result = '&opt_size_' + name.lower();
    else:
      result = 'traits::vector_storage(tmp_' + name.lower() + ')'
  else:
    result = call_level0_type( name, properties, arg_map )
  return result


def min_workspace_size_type( name, properties, arg_map ):
  result = None
  if 'workspace' in properties[ 'io' ] and properties.has_key( 'assert_size' ):
    result = expand_nested_list( properties[ 'assert_size' ], arg_map, False );
  return result


def min_workspace_arg_type( name, properties, arg_map ):
  result = None
  if 'workspace' in properties[ 'io' ] and properties.has_key( 'assert_size_args' ):
    code_result = []
    for arg in properties[ 'assert_size_args' ]:
      if arg_map.has_key( arg ):
        code_result += [ cpp_type( arg, arg_map[ arg ] ) ]
      else:
        if type( properties[ 'assert_size' ] ) == StringType:
          code_result += [ '?' + properties[ 'assert_size' ] ]
        else:
          code_result += [ '??' ]
    result = ", ".join( code_result )
  return result


def min_workspace_call_type( name, properties, arg_map ):
  result = None
  if 'workspace' in properties[ 'io' ] and properties.has_key( 'assert_size_args' ):
    code_result = []
    for arg in properties[ 'assert_size_args' ]:
      if arg_map.has_key( arg ):
        code_result += [ call_level0_type( arg, arg_map[ arg ], arg_map ) ]
      else:
        if arg != None:
          code_result += [ '?' + arg.upper() ]
        else:
          if type( properties[ 'assert_size' ] ) == StringType:
            code_result += [ '?' + properties[ 'assert_size' ] ]
          else:
            code_result += [ '??' ]
    result = ", ".join( code_result )
  return result


def user_defined_type( name, properties, arg_map ):
  result = None
  if properties.has_key( 'user_defined' ):
    result = properties[ 'user_defined' ]
  return result



#
#
#
#
def match_formulae( text_field ):
  find_start = re.compile( '([A-Z]+)\s?(>=|is\sat\sleast)\s?(.*)the\scode\swill', re.M | re.S ).findall( text_field )
  for element in find_start:
    print element



#
# Split string using a list of delimiters
# Delimiters may be substrings of length 1 or 2 (may be increased if necessary)
#
def split_delim( s, delim = [','] ):
  result = []
  parentheses = 0
  cur_pos = 0
  prev_pos = 0
  for index in range( 0, len(s) ):
    if s[ index ] == '(': 
      parentheses += 1
    elif s[ index ] == ')':
      parentheses -= 1
    for length in range( 1, 3 ):
      if index >= (length-1) and parentheses == 0:
        c = s[ index-(length-1): index+1 ]
        if c in delim:
          result += [ s[ prev_pos:(index-(length-1)) ] ]
          prev_pos = index+1
          
  result += [ s[ prev_pos:len(s) ] ]
  return result



#
# Look for implicit products, like 5N, and replace with 5*N
#
def replace_implicit_products( text_field ):
  result = re.sub( '([0-9])+([A-Z]+)', '\\1*\\2', text_field )
  return result




def decompose_formula( text_field ):
  text_field = text_field.strip()
  print "Decompose: ", text_field
  
  if text_field[0] == '(' and text_field[-1] == ')':
    result = text_field[ 1:-1 ]
    return [ '()', decompose_formula( result ) ]
  
  if len( split_delim( text_field, [ ',' ] ) ) > 1:
    print "ERROR! (in LAPACK?)"
    return [ 'ERROR' ]
  
  #
  # Detect leaf: if text_field equals a argument (like N), or a number
  #  
  if re.compile( '^([a-zA-Z]+|[0-9]+)$' ).match( text_field ):
    print "decompose: at leaf: '" + text_field + "'"
    return text_field.upper()
  
  
  if len( split_delim( text_field, [ '**' ] ) ) > 1:
    print 'decompose: inserting pow'
    arguments = split_delim( text_field, [ '**' ] )
    print arguments
    result = []
    for arg in arguments:
      result.append( decompose_formula( arg ) )
    return [ 'pow', result ]
  
  for operator in [ '*', '/', '+', '-' ]:
    if len( split_delim( text_field, [ operator ] ) ) > 1:
      print 'decompose: inserting ' + operator
      arguments = split_delim( text_field, operator )
      print arguments
      result = []
      for arg in arguments:
        result.append( decompose_formula( arg ) )
      return [ operator, result ]
    
  
  if (text_field[ 0:4 ] == 'max(' or text_field[ 0:4 ] == 'MAX(') and \
    text_field[ -1 ] == ')':
    print "decompose: inserting max"
    arguments = split_delim( text_field[ 4:-1 ] )
    print arguments, len(arguments)
    # keep max a binary function ... :-)
    if len( arguments ) > 2:
      return [ 'max', [ decompose_formula( arguments[0] ), decompose_formula( 'max(' + ",".join( arguments[1:] ) + ')' ) ] ]
    else:  
      result = []
      for arg in arguments:
        result.append( decompose_formula( arg ) )
      #result = [ decompose_formula( arguments[0] ), decompose_formula( arguments[1] ) ]
      return [ 'max', result ]
  

  if (text_field[ 0:4 ] == 'min(' or text_field[ 0:4 ] == 'MIN(') and \
    text_field[ -1 ] == ')':
    print "decompose: inserting min"
    arguments = split_delim( text_field[ 4:-1 ] )
    print arguments, len(arguments)
    # keep max a binary function ... :-)
    if len( arguments ) > 2:
      return [ 'min', [ decompose_formula( arguments[0] ), decompose_formula( 'min(' + ",".join( arguments[1:] ) + ')' ) ] ]
    else:  
      result = []
      for arg in arguments:
        result.append( decompose_formula( arg ) )
      #result = [ decompose_formula( arguments[0] ), decompose_formula( arguments[1] ) ]
      return [ 'min', result ]
  

#
#
def match_assert_ge( argument_map, text_field ):
  #print "Match assert GE..."
  match_it = re.compile( ' +[A-Z]+[ ]{0,3}(>=|must be at least)[ ]{0,3}([0-9]|(min|max|MIN|MAX|[\(\)\,0-9A-Z\+\*\-])+)' ).findall( text_field )
  if len( match_it ) == 1:
    print "Match assert GE:", match_it
    #print match_it
    #if len( match_it[ 0 ][ 2 ] ) > 0:
    return decompose_formula( match_it[ 0 ][ 1 ] )
  else:
    print "nr of matches: ", len( match_it )
    return None
  




# try different keys, return the one that exists, if any

def my_has_key( key_name, template_map ):
  # try, e.g., gelsd.all.
  m_all_key = key_name.replace( ".complex", ".all" ).replace( ".real", ".all" )
  if template_map.has_key( key_name ):
    print "using key ", key_name
    return key_name
  if template_map.has_key( m_all_key ):
    print "using key ", m_all_key
    return m_all_key
  print "tried keys ", key_name, "and", m_all_key,", no results"
  return None



#
# Default user-defined arg is of type scalar INTEGER
#
def add_user_defined_args( arg, argument_map, template_map, base_name ):
  print "Trying to add user-defined argument definitions for", arg

  argument_map[ arg ] = {}

  base_key = base_name.lower() + '.' + arg
  print "base_key",base_key

  if my_has_key( base_key + '.value_type', template_map ) != None:
    argument_map[ arg ][ 'value_type' ] = template_map[ my_has_key( base_key + '.value_type', template_map ) ].strip()
  else:
    argument_map[ arg ][ 'value_type' ] = 'INTEGER'

  if my_has_key( base_key + '.type', template_map ) != None:
    argument_map[ arg ][ 'type' ] = template_map[ my_has_key( base_key + '.type', template_map ) ].strip()
  else:
    argument_map[ arg ][ 'type' ] = 'scalar'

  if my_has_key( base_key + '.init', template_map ) != None:
    argument_map[ arg ][ 'user_defined' ] = template_map[ my_has_key( base_key + '.init', template_map ) ].strip()
  else:
    argument_map[ arg ][ 'user_defined' ] = 'UNDEFINED'

  argument_map[ arg ][ 'io' ] = [ 'input' ]

  return







#
# Parse a LAPACK file
# input: filename
# output: a pair of ( function name, map )
#         the map contains: 
#         'arguments': an array of arguments
#         'argument_map': a map of ( argument_name, property ), 
#                     in which property can be
#            'type': Fortran type
#            'cpptype': C++ type
#            'io': the (input/output) part from the comment section
#
def parse_file( filename, template_map ):

  # for nice printing
  pp = pprint.PrettyPrinter( indent = 2 )

  # read the entire fortran source file
  source = open( filename ).read()

  # parse and split the code 
  # * merge multilines to one line (using the $ and + characters)
  # * split comments-blocks and code blocks
  # * remove '*' from comments
  # input:  full source code
  # output: an array of lines of code
  #         an array of lines of comments
  code = []
  comments = []
  for i in source.splitlines():

    # Special case: in e.g. CHEEVR comments are lead by many stars instead of 1
    # replace those (more than 1) with spaces so that it becomes a regular comment
    # block.
    leading_stars = re.compile( '^[ ]*\*(\*+)' ).match( i )
    if leading_stars != None:
      spaces = i[ leading_stars.start(1):leading_stars.end(1) ].replace( '*', ' ' )
      i = i[0:leading_stars.start(1)] + spaces + \
        i[leading_stars.end(1):len(i)]

    # Continue for the regular case
    match_comment = re.compile( '^[ ]*\*(.*)' ).search( i )
    if match_comment == None:
      match_multi = re.compile( '^[ ]*[\$\+][ ]*(.*)$' ).search( i )
      if match_multi == None:
        code += [ i ]
      else:
        code[-1 ] += match_multi.expand( "\\1" )
    else:
      comments += [ match_comment.expand( "\\1" ) ]

  # Acquire important information
  # * the subroutine name
  # * the arguments of the subroutine
  subroutine_found = False
  subroutine_name = ''
  subroutine_arguments = []
  subroutine_return_type = None

  code_line_nr = 0
  while code_line_nr < len(code) and not subroutine_found:
    match_subroutine_name = re.compile( '(DOUBLE COMPLEX FUNCTION|COMPLEX FUNCTION|DOUBLE PRECISION FUNCTION|REAL FUNCTION|SUBROUTINE)[ ]+([A-Z0-9]+)\(([^\)]+)' ).search( code[ code_line_nr ] )
    if match_subroutine_name != None:
      subroutine_found = True
      subroutine_name = match_subroutine_name.group( 2 )
      subroutine_arguments = match_subroutine_name.group( 3 ).replace( ' ', '' ).split( "," )
      if match_subroutine_name.group(1) != 'SUBROUTINE':
        subroutine_return_type = " ".join( match_subroutine_name.group(1).split(" ")[0:-1] )

    code_line_nr += 1

  # If we could not find a subroutine, we quit at our earliest convenience
  if code_line_nr == len(code):
    print "Could not find function/subroutine statement, bailing out."
    return None, None

  # IF there are no arguments, bail out
  if subroutine_arguments == ['']:
    print "Function without arguments not supported."
    return None, None

  #
  # Do some further analysis as to what kind of routine this is
  #
  subroutine_group_name = subroutine_name[ 1: ]
  subroutine_value_type = None
  if subroutine_name[0] == 'C' or subroutine_name[0] == 'Z':
    subroutine_value_type = 'complex'
  if subroutine_name[0] == 'S' or subroutine_name[0] == 'D':
    subroutine_value_type = 'real'

  print "Subroutine: ", subroutine_name
  print "Arguments:  ", len(subroutine_arguments),":",subroutine_arguments
  print "Group name: ", subroutine_group_name
  print "Variant:    ", subroutine_value_type
  print "Return:     ", subroutine_return_type

  # Now we have the names of the arguments. The code following the subroutine statement are
  # the argument declarations. Parse those right now, splitting these examples
  #      INTEGER            INFO, LDA, LDVS, LWORK, N, SDIM
  #      COMPLEX            A( LDA, * ), VS( LDVS, * ), W( * ), WORK( * )
  # into a map containing
  #      INFO: value_type=INTEGER, type=scalar
  #      WORK: value_type=COMPLEX, type=vector
  #         A: value_type=COMPLEX, type=matrix, leading_dimension=LDA
  # etc.
  arguments_found = False
  argument_map = {}
  while code_line_nr < len(code) and len( argument_map ) < len( subroutine_arguments ):
    match_argument_declaration = re.compile( '^[ ]*(EXTERNAL|LOGICAL|CHARACTER|REAL|INTEGER' + \
      '|DOUBLE PRECISION|DOUBLE COMPLEX|COMPLEX\*16|COMPLEX)[ ]+(.*)$' ).search( code[ code_line_nr] )
    if match_argument_declaration != None:
      for argument_match in re.findall( '([A-Z0-9]+(\([^\)]+\))?)[, ]?', match_argument_declaration.group( 2 ) ):
        argument_description = argument_match[0].strip().split( "(" )
        argument_name = argument_description[0]
        argument_map[ argument_name ] = {}
        argument_map[ argument_name ][ 'value_type' ] = match_argument_declaration.group( 1 )
        if len(argument_description) == 1:
          argument_map[ argument_name ][ 'type' ] = 'scalar'
        else:
          if argument_description[1].find( "," ) == -1:
            argument_map[ argument_name ][ 'type' ] = 'vector'
          else:
            argument_map[ argument_name ][ 'type' ] = 'matrix'
            # check if there is a leading dimension
            argument_map[ argument_name ][ 'leading_dimension' ] = argument_description[1].split( "," )[0].strip()
    code_line_nr += 1

  # See if we are hard-forcing argument renaming aliases
  # This is needed for BLAS. It has argument names that are tied to the 
  # value_type variant of the routine. E.g., daxpy has dx and dy, caxpy has
  # cx and cy. This is confusing for the generator, so we replace it with 
  # x and y, if the command for that is issued in its template.
  argument_replace_map = {}
  argument_value_type_prepend_key = subroutine_group_name.lower() + '.' + subroutine_value_type + '.remove_argument_value_type_prepend'
  if my_has_key( argument_value_type_prepend_key, template_map ):
    arguments_to_do = template_map[ my_has_key( argument_value_type_prepend_key, template_map ) ].strip().split(",")
    for argument_new_name in arguments_to_do:
      argument_new_name = argument_new_name.strip()
      # try to find the original argument with value type
      # it's either from a complex or double variant, 
      # not as cleanly applied as we might say
      if subroutine_value_type == 'complex':
        prefixes = [ 'C', 'Z' ]
      else:
        prefixes = [ 'S', 'D' ]
      # determine the original name
      argument_with_value_type = None
      for prefix in prefixes:
        try_name = prefix + argument_new_name
        if try_name in subroutine_arguments:
          argument_with_value_type = try_name
      # only if we could find something, do something
      if argument_with_value_type != None:
        loc = subroutine_arguments.index( argument_with_value_type )
        # replace in the overall subroutine arguments list
        subroutine_arguments[ loc ] = argument_new_name
        # rename the key in the argument map
        # create a copy, delete the old
        argument_replace_map[ argument_with_value_type ] = argument_new_name
        argument_map[ argument_new_name ] = argument_map[ argument_with_value_type ]
        del argument_map[ argument_with_value_type ]

  # Create convenience lookups by value_type and types of arguments
  # e.g., grouped_arguments[ 'by_value_type' ][ 'INTEGER' ] will give an array of all integer types
  #       grouped_arguments[ 'by_type' ][ 'matrix' ] will give an array of all matrices
  grouped_arguments = {}
  key_array = [ 'type', 'value_type' ]
  for s in key_array:
    grouped_arguments[ 'by_' + s ] = {}
  # make sure the order of argument names is the same as those in the subroutine argument order
  for argument_name in subroutine_arguments:
    argument_properties = argument_map[ argument_name ]
    for s in key_array:
      if not grouped_arguments[ 'by_' + s ].has_key( argument_properties[ s ] ):
        grouped_arguments[ 'by_' + s ][ argument_properties[ s ] ] = []
      grouped_arguments[ 'by_' + s ][ argument_properties[ s ] ] += [ argument_name ]

  # The next bulk load of information can be acquired from the comment fields, 
  # this is between "Purpose" and "Arguments". Locate those headers, and init with
  # -1 so that we can check if they where found.
  comment_line_nr = 0
  purpose_line_nr = -1
  arguments_line_nr = -1
  while comment_line_nr < len(comments) and purpose_line_nr == -1:
    if re.compile( '^[ ]+Purpose[ ]*$' ).search( comments[ comment_line_nr ] ) != None:
      purpose_line_nr = comment_line_nr
    comment_line_nr += 1

  while comment_line_nr < len(comments) and arguments_line_nr == -1:
    if re.compile( '^[ ]+Arguments[ ]*$' ).search( comments[ comment_line_nr ] ) != None:
      arguments_line_nr = comment_line_nr
    comment_line_nr += 1

  # Gather the actual subroutine purpose. This is always following the Purpose title (obvious :-))
  # and stopping before the "Arguments" block.
  subroutine_purpose = ''
  if purpose_line_nr > 0 and arguments_line_nr > 0:
    subroutine_purpose = "//" + "\n//".join( comments[ purpose_line_nr+3:arguments_line_nr-1 ] )

  # try to see if we are overriding the arguments piece
  arguments_key = subroutine_group_name.lower() + '.' + subroutine_value_type + '.arguments'
  if my_has_key( arguments_key, template_map ):
    print arguments_line_nr, comment_line_nr
    arguments_line_nr = len(comments)
    comments += template_map[ my_has_key( arguments_key, template_map ) ].splitlines()
    comments += [ '' ]

  # Break up the comments
  # Now, for each argument, locate its associated comment field
  #
  # In this case, for M, we store the range [45, 48>
  no_commented_arguments = 0
  if arguments_line_nr > 0:
    preceding_argument = ''
    finished_the_last = False
    detected_lapack_style = False
    detected_blas_style = False
    while comment_line_nr < len(comments) and not finished_the_last:
      # Example for LAPACK-style matching. 
      # 45 M       (input) INTEGER
      # 46         The number of rows of the matrix A. M >= 0.
      # 47
      # 48 N       (input) INTEGER
      match_lapack_style = re.compile( '^[\s]*([A-Z]+[12]?)[\s]+\(([a-z/ ]+)\)' ).search( comments[ comment_line_nr ] )
      if not detected_blas_style and match_lapack_style != None:
        detected_lapack_style = True
        argument_name = match_lapack_style.group(1)
        # If we're replacing arguments, we should do so here as well.
        if argument_replace_map.has_key( argument_name ):
          argument_name = argument_replace_map[ argument_name ]
        # Check if the argument is in the argument_map, don't crash if it isn't
        if argument_map.has_key( argument_name ):
          argument_map[ argument_name ][ 'comment_lines' ] = [ comment_line_nr ]
          split_regex = re.compile( '\/| or ' )
          argument_map[ argument_name ][ 'io' ] = split_regex.split( match_lapack_style.group(2) )
          if preceding_argument != '':
            argument_map[ preceding_argument ][ 'comment_lines' ] += [ comment_line_nr ]
          preceding_argument = argument_name
          no_commented_arguments += 1
        else:
          print "WARNING: Skipping argument comment of", argument_name,", not in function argument list"

      # Example for BLAS, which doesn't mention input/output on the same line
      # 37 N      - INTEGER.
      # 38          On entry, N specifies the order of the matrix A.
      # 39          N must be at least zero.
      # 40          Unchanged on exit.
      match_blas_style = re.compile( '^[\s]*([A-Z]+[2]?)[\s]+\- [A-Z]+' ).search( comments[comment_line_nr] )
      if not detected_lapack_style and match_blas_style != None:
        detected_blas_style = True
        argument_name = match_blas_style.group(1)
        argument_map[ argument_name ][ 'comment_lines' ] = [ comment_line_nr ]
        # default input/output with blas to output, this will be overwritten if "unchanged on exit" is
        # found
        argument_map[ argument_name ][ 'io' ] = [ 'output' ]
        if preceding_argument != '':
          argument_map[ preceding_argument ][ 'comment_lines' ] += [ comment_line_nr ]
        preceding_argument = argument_name
        no_commented_arguments += 1

      # Detection for BLAS' "input" statement
      match_unchanged_on_exit = re.compile( '^[\s]*[uU]nchanged on exit' ).search( comments[comment_line_nr] )
      if detected_blas_style and match_unchanged_on_exit != None:
        argument_map[ preceding_argument ][ 'io' ] = [ 'input' ]

      # INFO comes last, so detect an empty line for this case
      if no_commented_arguments == len( subroutine_arguments ) and \
         len( argument_map[ preceding_argument ][ 'comment_lines' ] ) < 2:
        match_empty_line = re.compile( '^[ ]*$' ).search( comments[ comment_line_nr ] )
        if match_empty_line != None:
          argument_map[ preceding_argument ][ 'comment_lines' ] += [ comment_line_nr + 1 ]
          finished_the_last = True

      comment_line_nr += 1

    # Inform the debug.log / user which comment style we employed
    if ( detected_lapack_style ):
      print "Argument comment style: LAPACK"
    elif ( detected_blas_style ):
      print "Argument comment style: BLAS"

  #
  # TODO
  # TODO
  # TODO
  #
  if no_commented_arguments != len( subroutine_arguments ):
    print str(no_commented_arguments) + " out of " + str(len(subroutine_arguments)) + \
      " arguments are commented, bailing out"
    return subroutine_name, None

  #
  # Make a back-reference to those arguments that are defined as leading dimension in the code
  #
  for argument_name, argument_properties in argument_map.iteritems():
    if argument_properties.has_key( 'leading_dimension' ):
      referring_argument_name = argument_properties[ 'leading_dimension' ]
      if argument_map.has_key( referring_argument_name ):
        argument_map[ referring_argument_name ][ 'trait_type' ] = 'lda'
        argument_map[ referring_argument_name ][ 'trait_of' ] = argument_name

  # Extend convenience lookups by io, recently acquired when processing the comment
  # fields. We have to be sure arguments are processed in the right order.
  grouped_arguments[ 'by_io' ] = {}
  for argument_name in subroutine_arguments:
    argument_properties = argument_map[ argument_name ]
    for io_type in argument_properties[ 'io' ]:
      if not grouped_arguments[ 'by_io' ].has_key( io_type ):
        grouped_arguments[ 'by_io' ][ io_type ] = []
      grouped_arguments[ 'by_io' ][ io_type ] += [ argument_name ]

  #
  # Parse the comment fields
  #
  print "PARSING COMMENTS:"
  user_defined_arg_map = {}
  for argument_name, argument_properties in argument_map.iteritems():

    print "\n\n**********"
    print argument_name
    comment_block = "\n".join( comments[ argument_properties[ 'comment_lines' ][0] : argument_properties[ 'comment_lines' ][1] ] )
    print comment_block
    match_formulae( comment_block )

    #
    # Handle scalar INTEGER comment blocks. Look for type traits stuff.
    #
    if argument_properties[ 'type' ] == 'scalar' and \
       argument_properties[ 'value_type' ] == 'INTEGER':
      #
      # Fetch matrix traits such as "the number of columns of A"
      #
      match_matrix_traits = re.compile( '(rows|columns|order)(in|of|the|input|\s)+(matrix|matrices|\s)+' + \
        '([A-Z]+\s+and\s+[A-Z]+|[A-Z]+)', re.M | re.S ).findall( comment_block )
      if len( match_matrix_traits ) == 1:
        if match_matrix_traits[0][0] == 'order':
          #
          # see if the traits are overruled through the template system
          # logically, these come first
          traits_key = subroutine_group_name.lower() + '.' + subroutine_value_type + '.' + argument_name + '.trait_of'
          if my_has_key( traits_key, template_map ):
            argument_properties[ 'trait_type' ] = 'num_columns'
            argument_properties[ 'trait_of' ] = template_map[ my_has_key( traits_key, template_map ) ].strip()
          # PANIC: return none
          # e.g., in tridiagonal case, there is no matrix, but a number of 
          # vectors (the diagonals)
          elif not grouped_arguments[ 'by_type' ].has_key( 'matrix' ):
            print "PANIC: returning none"
            # TODO
            # TODO
            return subroutine_name, None
            # TODO
            # TODO
          elif match_matrix_traits[0][3] in grouped_arguments[ 'by_type' ][ 'matrix' ]:
            # because it is both #rows and #columns, we have to choose one
            argument_properties[ 'trait_type' ] = 'num_columns'
            argument_properties[ 'trait_of' ] = match_matrix_traits[0][3].strip()


        else:
          references = match_matrix_traits[0][3].split( 'and' )
          for matrix_name in references:
            if matrix_name.strip() in grouped_arguments[ 'by_type' ][ 'matrix' ]:
              argument_properties[ 'trait_type' ] = 'num_' + match_matrix_traits[0][0]
              argument_properties[ 'trait_of' ] = matrix_name.strip()

      #
      # Fetch array traits, such as "the length of the array WORK"
      #
      match_array_traits = re.compile( '(The length|The dimension)(of|the|\s)+(array|\s)+([A-Z]+)', re.M | re.S ).findall( comment_block )
      if len( match_array_traits ) > 0 and match_array_traits[ 0 ][ 3 ] in grouped_arguments[ 'by_type' ][ 'vector' ]:
        argument_properties[ 'trait_type' ] = 'size'
        argument_properties[ 'trait_of' ] = match_array_traits[ 0 ][ 3 ]


      match_stride_traits = re.compile( '([Tt]he increment)(\s|for|the|elements|of)+([A-Z]+)', re.M | re.S ).findall( comment_block )
      print match_stride_traits
      if len( match_stride_traits ) > 0 and match_stride_traits[ 0 ][ 2 ] in grouped_arguments[ 'by_type' ][ 'vector' ]:
        argument_properties[ 'trait_type' ] = 'stride'
        argument_properties[ 'trait_of' ] = match_stride_traits[ 0 ][ 2 ]

      # Fetch greater-than-or-equal-to integer asserts, such as 
      # M >= 0.
      # N >= max(...)
      match_greater_equal = match_assert_ge( argument_map, comment_block )
      if match_greater_equal != None:
        argument_properties[ 'assert_ge' ] = match_greater_equal

      # Are we dealing with a workspace-length integer?
      # If so, try to detect the workspace-query text.
      # And, try to detect for which work arrays the query will run.
      # Keep the same order of workspace names as used in the grouped arguments map
      if 'WORK' in argument_name:
        match_query = re.compile( 'If ' + argument_name + ' \= \-1(\,|then|a|workspace|\s)+query', re.M ).search( comment_block )
        if match_query != None:
          work_query_block = comment_block[ match_query.start(0): ]
          any_workspace = "(" + "|".join( grouped_arguments[ 'by_io' ][ 'workspace' ] ) + ")"
          match_workspace = re.compile( '[^A-Z]' + any_workspace, re.M | re.S ).findall( work_query_block )
          if len( match_workspace ) > 0:
            argument_properties[ 'workspace_query_for' ] = []
          for name in grouped_arguments[ 'by_io' ][ 'workspace' ]:
            if name in match_workspace:
              argument_properties[ 'workspace_query_for' ] += [ name ]

    #
    # Handle CHARACTER comment blocks.
    # Try to get which variables are valid, to put this in asserts.
    #
    elif argument_properties[ 'value_type' ] == 'CHARACTER':
      match_statements = re.compile( '=(\s|or|\'[0-9A-Z]\')+[:,]', re.M ).finditer( comment_block )
      for statement in match_statements:
        print "Statement:",statement.group(0)
        match_letters = re.compile( '\'([0-9A-Z])\'' ).findall( statement.group(0) )
        for letter in match_letters:
          print "Letter",letter
          if not argument_properties.has_key( 'assert_char' ):
            argument_properties[ 'assert_char' ] = []
          if not letter in argument_properties[ 'assert_char' ]:
            argument_properties[ 'assert_char' ] += [ letter ]

      if argument_name == 'UPLO':
        # see if the traits are overruled through the template system
        traits_key = subroutine_group_name.lower() + '.' + subroutine_value_type + '.' + argument_name + '.trait_of'
        if my_has_key( traits_key, template_map ):
          argument_properties[ 'trait_type' ] = 'uplo'
          argument_properties[ 'trait_of' ] = template_map[ my_has_key( traits_key, template_map ) ].strip()
        
        else:
          match_uplo = re.compile( '([Uu]pper|[Ll]ower)(or|triangular|triangle|triangles|part|of|the|band|hermitian|symmetric|input|matrix|\s)+([A-Z]+)', re.M ).findall( comment_block )
          print "UPLO:", match_uplo
          uplo_trait_of = None
          if len( match_uplo ) > 0:
            uplo_trait_of = match_uplo[ 0 ][ 2 ]
          for match in match_uplo:
            if uplo_trait_of != None and match[2] != uplo_trait_of:
              uplo_trait_of = None
          if uplo_trait_of != None:
            print "adding uplo trait"
            argument_properties[ 'trait_type' ] = 'uplo'
            argument_properties[ 'trait_of' ] = uplo_trait_of

    #
    # Minimal workspace dimension recognition
    #
    elif argument_properties[ 'type' ] == 'vector':
      # usually this text is
      # 1) dimension (...)           without spaces in the formula
      # 2) dimension at least ...    (e.g., RWORK IN CLALSA)
      match_dim = re.compile( 'dimension \((.+)\)' ).findall( comment_block )
      print "Matches on dimension(): ", len( match_dim )
      for d in match_dim:
        d = d.replace( ' ', '' )
        #
        # TODO
        # make some sensible rules here
        #
        match_unwanted_text = re.compile( '\s([Ii]f|[Ww]hen)\s' ).findall( comment_block )
        print match_unwanted_text
        if len( match_unwanted_text ) == 0:
          argument_properties[ 'assert_size' ] = decompose_formula( replace_implicit_products( d ) )
          argument_properties[ 'assert_size_args' ] = nested_list_args( argument_properties[ 'assert_size' ] )

      # assert_size_args determines the arguments of min_size function for this
      # workspace array. But, this gets overruled by user-defined templates.
      if 'workspace' in argument_properties[ 'io' ]:
        args_string = None
        template_key = subroutine_group_name.lower() + '.' + subroutine_value_type + '.min_size_' + argument_name.lower() + '.args'
        if my_has_key( template_key, template_map ) != None:
          args_string = template_map[ my_has_key( template_key, template_map ) ]
          tmp_result = []
          for arg in args_string.split( "," ):
            tmp_result.append( arg.strip().upper() )
          if tmp_result == ['']:
            tmp_result = []

          for arg in tmp_result:
            if arg not in argument_map.keys():
              # variable not found, try user-defined variable definitions
              add_user_defined_args( arg, user_defined_arg_map, template_map, subroutine_group_name + '.' + subroutine_value_type )

          argument_properties[ 'assert_size_args' ] = tmp_result
          print "Using user-defined assert_size_args: ", tmp_result

      #
      # Try to detect packed strorage stuff. Typically these are vectors in Fortran, but 
      # matrices in our bindings. E.g. as used in spsv. 
      #
      packed_keywords = re.compile( '(/s|packed|matrix)+', re.M ).findall( comment_block )
      if 'matrix' in packed_keywords and 'packed' in packed_keywords:
        #
        # Overrule my type :-)
        #
        argument_properties[ 'type' ] = 'matrix'

  #
  # Add user-defined arguments to the argument_map
  #
  argument_map.update( user_defined_arg_map )


  print "Argument map: "  
  pp.pprint( argument_map )


  #
  # Make a back-reference for workspace queries
  #
  for argument_name, argument_properties in argument_map.iteritems():
    if argument_properties.has_key( 'workspace_query_for' ):
      for referring_argument_name in argument_properties[ 'workspace_query_for' ]:
        if argument_map.has_key( referring_argument_name ):
          if not argument_map[ referring_argument_name ].has_key( 'workspace_query_by' ):
            argument_map[ referring_argument_name ][ 'workspace_query_by' ] = []
          argument_map[ referring_argument_name ][ 'workspace_query_by' ] += [ argument_name ]


  #
  # Generate the actual C++ code statements, based on information acquired so far.
  #
  # pass 1
  for argument_name, argument_properties in argument_map.iteritems():
    argument_properties[ 'code' ] = {}
    argument_properties[ 'code' ][ 'lapack_h' ] = c_type( argument_name, argument_properties )
    argument_properties[ 'code' ][ 'call_c_header' ] = call_c_type( argument_name, argument_properties )
    argument_properties[ 'code' ][ 'level_0' ] = cpp_type( argument_name, argument_properties )
    argument_properties[ 'code' ][ 'call_level_0' ] = call_level0_type( argument_name, argument_properties, argument_map )
    argument_properties[ 'code' ][ 'level_1' ] = level1_type( argument_name, argument_properties )
    argument_properties[ 'code' ][ 'level_1_type' ] = level1_typename( argument_name, argument_properties )
    argument_properties[ 'code' ][ 'call_level_1' ] = call_level1_type( argument_name, argument_properties )
    argument_properties[ 'code' ][ 'level_2' ] = level2_type( argument_name, argument_properties )
    argument_properties[ 'code' ][ 'workspace_type' ] = workspace_type( argument_name, argument_properties )
    
  # Pass 2
  # A second pass is needed, because the asserts may cross-reference other 
  # variables which have been assigned their code in pass 1.
  for argument_name, argument_properties in argument_map.iteritems():
    argument_properties[ 'code' ][ 'level_1_assert' ] = level1_assert( argument_name, argument_properties, argument_map )
    argument_properties[ 'code' ][ 'level_1_static_assert' ] = level1_static_assert( argument_name, argument_properties )
    argument_properties[ 'code' ][ 'opt_workspace_query' ] = opt_workspace_query_type( argument_name, argument_properties, argument_map )
    argument_properties[ 'code' ][ 'opt_workspace_pre' ] = opt_workspace_pre_type( argument_name, argument_properties, argument_map )
    argument_properties[ 'code' ][ 'opt_workspace_post' ] = opt_workspace_post_type( argument_name, argument_properties )
    argument_properties[ 'code' ][ 'min_workspace' ] = min_workspace_size_type( argument_name, argument_properties, argument_map )
    argument_properties[ 'code' ][ 'min_workspace_args' ] = min_workspace_arg_type( argument_name, argument_properties, argument_map )
    argument_properties[ 'code' ][ 'min_workspace_call' ] = min_workspace_call_type( argument_name, argument_properties, argument_map )
    argument_properties[ 'code' ][ 'user_defined_init' ] = user_defined_type( argument_name, argument_properties, argument_map )

  print "Argument map: "  
  pp.pprint( argument_map )

  print "Grouped arguments: "
  pp.pprint( grouped_arguments )

  #
  # create a dict object
  #
  info_map = {}
  info_map[ 'arguments' ] = subroutine_arguments
  info_map[ 'purpose' ] = subroutine_purpose
  info_map[ 'return_type' ] = subroutine_return_type
  info_map[ 'argument_map' ] = argument_map
  info_map[ 'grouped_arguments' ] = grouped_arguments
  if subroutine_return_type != None:
    info_map[ 'return_value_type' ] = value_type( subroutine_return_type )
    info_map[ 'level1_return_type' ] = 'value_type'
    info_map[ 'return_statement' ] = 'return '
  else:
    info_map[ 'return_value_type' ] = 'void'
    info_map[ 'level1_return_type' ] = 'void'
    info_map[ 'return_statement' ] = ''

  #
  # Pass / check user-defined stuff right here.
  #
  user_def_key = subroutine_group_name.lower() + '.' + subroutine_value_type + '.extra_variables'
  if my_has_key( user_def_key, template_map ) != None:
    user_vars = template_map[ my_has_key( user_def_key, template_map ) ].split( "," )
    tmp_result = []
    for v in user_vars:
      tmp_result.append( v.strip().upper() )
    info_map[ 'user_defined_variables' ] = tmp_result
  else:
    info_map[ 'user_defined_variables' ] = None
    
  #
  # Pass / check user-defined stuff right here.
  # OPTIMAL CASE (may contain fewer variables)
  #
  user_def_key = subroutine_group_name.lower() + '.' + subroutine_value_type + '.extra_opt_variables'
  if my_has_key( user_def_key, template_map ) != None:
    user_vars = template_map[ my_has_key( user_def_key, template_map ) ].split( "," )
    tmp_result = []
    for v in user_vars:
      tmp_result.append( v.strip().upper() )
    info_map[ 'user_defined_opt_variables' ] = tmp_result
  else:
    info_map[ 'user_defined_opt_variables' ] = None
  
  
  #subroutine_description.replace( subroutine_name, subroutine_name[ 1: ] )
  #info_map[ 'description' ] = subroutine_description
  
  return subroutine_name, info_map


