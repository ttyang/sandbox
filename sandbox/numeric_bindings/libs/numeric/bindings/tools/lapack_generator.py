#!/usr/bin/python
#
#  Copyright (c) 2008 Thomas Klimpel and Rutger ter Borg
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)
#

import netlib
import bindings

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


  
def c_type( name, properties ):
  m_type_map = global_type_map
  m_type_map[ 'COMPLEX' ] = 'fcomplex_t'
  m_type_map[ 'COMPLEX*16' ] = 'dcomplex_t'

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
    if properties[ 'value_type' ][ 0:7] == 'COMPLEX':
      result = 'traits::complex_ptr(' + name.lower() + ')'
    else:
      result = name.lower()
  elif properties[ 'type' ] == 'scalar':
    if properties[ 'value_type' ][ 0:7] == 'COMPLEX':
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
      result = "traits::matrix_size2(" + properties[ 'trait_of' ].lower() + ")"
    if properties[ 'trait_type' ] == 'num_rows':
      result = "traits::matrix_size1(" + properties[ 'trait_of' ].lower() + ")"
    if properties[ 'trait_type' ] == 'size':
      my_name = properties[ 'trait_of' ].lower()
      referring_to_properties = arg_map[ properties[ 'trait_of' ] ]
      if 'workspace' in referring_to_properties[ 'io' ]:
        my_name = 'work.select(' + workspace_type( properties[ 'trait_of' ].lower(), referring_to_properties ) + \
                  '())'
      result = "traits::vector_size(" + my_name + ")"
    if properties[ 'trait_type' ] == 'uplo':
      result = "traits::matrix_uplo_tag(" + properties[ 'trait_of' ].lower() + ")"
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
  return result


def level2_type( name, properties ):
  result = level1_type( name, properties )
  if name == 'INFO' and 'output' in properties[ 'io' ]:
    result = None

  if result != None:
    if properties[ 'value_type' ] == 'REAL' or properties[ 'value_type' ] == 'DOUBLE PRECISION':
      result = result.replace( "real_type", "typename traits::$TYPEOF_FIRST_TYPENAME" + \
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



def nested_list_args( arg ):
  print "finding nested list arguments of", arg
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
      if sub_result != [ None ]:
        for r in sub_result:
          if r not in result:
            result.append( r )

  else:
    for a in arg:
      result.append( a )

  print "returning ",result
  return result




def expand_nested_list( arg, arg_map, use_arg_map = True ):

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
  
  elif properties.has_key( 'assert_size' ):
    result = "assert( traits::vector_size(" + call_level0_type( name, properties, arg_map ) + ") >= " + \
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
        code_result += [ '?' + arg.upper() ]
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
        code_result += [ '?' + arg.upper() ]
      
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
# Desired order of routines in C++ code: float, double, single complex, double complex
#
def routine_cmp( a, b ):
  letter_a = a[0]
  letter_b = b[0]
  value_map = { 'S': 0, 'D': 1, 'C': 2, 'Z': 3 }
  result = 0
  if value_map[ a[0] ] < value_map[ b[ 0] ]:
    result = -1
  if value_map[ a[0] ] > value_map[ b[ 0] ]:
    result = 1
  return result
    

#
# Group subroutines on their name, with the first character removed. This will 
# group them in the same .hpp file as well. Sort these subroutines based on 
# routine_cmp above.
#
def group_by_value_type( global_info_map ):
  group_map = {}
  for i in global_info_map.keys():
    short_name = i[ 1: ]
    if not group_map.has_key( short_name ):
      group_map[ short_name ] = []
    group_map[ short_name ] += [ i ]
  for value in group_map.values():
    value.sort( routine_cmp )
  return group_map
  


  
def indent_lines( source_text, indent_size = 8 ):
  indent_string = '\n'
  for i in range(indent_size):
    indent_string += ' '
  return indent_string.join( source_text.splitlines() )
  

  
#
# Write the (many) driver routine file(s).
#
def write_functions( info_map, group, template_map, base_dir ):
  #
  # group.keys() is a vector of different grouped function names
  # like gees, dgesv, etc.
  #
  for group_name, subroutines in group.iteritems():
    
    filename = group_name.lower() + '.hpp'
    includes = [ '#include <cassert>',
      '#include <boost/numeric/bindings/traits/traits.hpp>',
      '#include <boost/numeric/bindings/traits/type_traits.hpp>', 
      '#include <boost/numeric/bindings/lapack/lapack.h>' ]
      
    if template_map.has_key( group_name.lower() + '.includes' ):
      includes += template_map[ group_name.lower() + '.includes' ].splitlines()

    #
    # LEVEL 0 HANDLING
    #  
    overloads = ''
    for subroutine in subroutines:
      sub_template = template_map[ 'lapack_overloads' ]
      # add the argument list here
      arg_list = []
      lapack_arg_list = []
      for arg in info_map[ subroutine ][ 'arguments' ]:
        arg_list += [ info_map[ subroutine ][ 'argument_map' ][ arg ][ 'code' ][ 'level_0' ] ]
        lapack_arg_list += [ info_map[ subroutine ][ 'argument_map' ][ arg ][ 'code' ][ 'call_c_header' ] ]
      sub_template = sub_template.replace( "$LEVEL0", ", ".join( arg_list ) )
      sub_template = sub_template.replace( "$CALL_C_HEADER", ", ".join( lapack_arg_list ) )
      sub_template = sub_template.replace( "$SUBROUTINE", subroutine )
      sub_template = sub_template.replace( '$groupname', group_name.lower() )
      
      overloads += bindings.proper_indent( sub_template )
  
    cases = {}
    # first, see what kind of functions we have
    # needed for argument check etc.
    for subroutine in subroutines:
      if subroutine[0] == 'S' or subroutine[0] == 'D':
        if not cases.has_key( 'real' ):
          cases[ 'real' ] = {}
          cases[ 'real' ][ 'subroutines' ] = []
        cases[ 'real' ][ 'subroutines' ] += [ subroutine ]
      if subroutine[0] == 'C' or subroutine[0] == 'Z':
        if not cases.has_key( 'complex' ):
          cases[ 'complex' ] = {}
          cases[ 'complex' ][ 'subroutines' ] = []
        cases[ 'complex' ][ 'subroutines' ] += [ subroutine ]
    
    #
    # LEVEL 1 and 2 HANDLING
    #
    level1_map = {}
    level2_map = {}
    for value_type, case_map in cases.iteritems():
      
      level1_template = ''
      level2_template = ''
      if info_map[ subroutine ][ 'grouped_arguments' ][ 'by_io' ].has_key( 'workspace' ):
        level1_template = template_map[ 'level1_workspace' ]
        level2_template = template_map[ 'level2_workspace' ]
      else:
        level1_template = template_map[ 'level1_noworkspace' ]
        level2_template = template_map[ 'level2_noworkspace' ]
      
      level1_template = level1_template.replace( '$groupname', group_name.lower() )
      level1_template = level1_template.replace( "$SPECIALIZATION", value_type )
    
      # take this subroutine for arguments etc.
      subroutine = case_map[ 'subroutines' ][ 0 ]
      print "taking",subroutine
      
      level0_arg_list = []
      level1_arg_list = []
      level2_arg_list = []
      level1_type_arg_list = []
      level1_assert_list = []
      call_level1_arg_list = []
      workspace_query_arg_list = []
      user_defined_arg_list = []
      user_defined_opt_arg_list = []
      for arg in info_map[ subroutine ][ 'arguments' ]:
        level0_arg_list += [ info_map[ subroutine ][ 'argument_map' ][ arg ][ 'code' ][ 'call_level_0' ] ]
        if info_map[ subroutine ][ 'argument_map' ][ arg ][ 'code' ][ 'level_1' ] != None:
          level1_arg_list += [ info_map[ subroutine ][ 'argument_map' ][ arg ][ 'code' ][ 'level_1' ] ]
        if info_map[ subroutine ][ 'argument_map' ][ arg ][ 'code' ][ 'level_2' ] != None:
          level2_arg_list += [ info_map[ subroutine ][ 'argument_map' ][ arg ][ 'code' ][ 'level_2' ] ]
        if info_map[ subroutine ][ 'argument_map' ][ arg ][ 'code' ][ 'level_1_type' ] != None and \
          info_map[ subroutine ][ 'argument_map' ][ arg ][ 'code' ][ 'level_1_type' ] not in level1_type_arg_list:
          level1_type_arg_list += [ info_map[ subroutine ][ 'argument_map' ][ arg ][ 'code' ][ 'level_1_type' ] ]
        if info_map[ subroutine ][ 'argument_map' ][ arg ][ 'code' ][ 'level_1_assert' ] != None:
          level1_assert_list += [ info_map[ subroutine ][ 'argument_map' ][ arg ][ 'code' ][ 'level_1_assert' ] ]
        if info_map[ subroutine ][ 'argument_map' ][ arg ][ 'code' ][ 'call_level_1' ] != None:
          call_level1_arg_list += [ info_map[ subroutine ][ 'argument_map' ][ arg ][ 'code' ][ 'call_level_1' ] ]
        if info_map[ subroutine ][ 'argument_map' ][ arg ][ 'code' ][ 'opt_workspace_query' ] != None:
          workspace_query_arg_list += [ info_map[ subroutine ][ 'argument_map' ][ arg ][ 'code' ][ 'opt_workspace_query' ] ]
          
      if info_map[ subroutine ][ 'user_defined_variables' ] != None:
        for arg in info_map[ subroutine ][ 'user_defined_variables' ]:
          print arg
          if info_map[ subroutine ][ 'argument_map' ][ arg ][ 'code' ][ 'user_defined_init' ] != None:
            user_defined_arg_list += [ info_map[ subroutine ][ 'argument_map' ][ arg ][ 'code' ][ 'user_defined_init' ] ]
      
      if info_map[ subroutine ][ 'user_defined_opt_variables' ] != None:
        for arg in info_map[ subroutine ][ 'user_defined_opt_variables' ]:
          print arg
          if info_map[ subroutine ][ 'argument_map' ][ arg ][ 'code' ][ 'user_defined_init' ] != None:
            user_defined_opt_arg_list += [ info_map[ subroutine ][ 'argument_map' ][ arg ][ 'code' ][ 'user_defined_init' ] ]
      
      # Level 1 replacements
      level1_template = level1_template.replace( "$CALL_LEVEL0", ", ".join( level0_arg_list ) )
      level1_template = level1_template.replace( "$CALL_LEVEL1", ", ".join( call_level1_arg_list ) )
      level1_template = level1_template.replace( "$LEVEL1", ", ".join( level1_arg_list ) )
      level1_template = level1_template.replace( "$TYPES", ", ".join( level1_type_arg_list ) )
      level1_template = level1_template.replace( "$ASSERTS", "\n        ".join( level1_assert_list ) )
      
      if len( user_defined_arg_list ) > 0:
        level1_template = level1_template.replace( "$INIT_USER_DEFINED_VARIABLES", indent_lines( "\n".join(user_defined_arg_list), 8 ) )
      else:
        level1_template = level1_template.replace( "\n        $INIT_USER_DEFINED_VARIABLES", "" )

      # Level 2 replacements
      # some special stuff is done here, such as replacing real_type with a 
      # type-traits deduction, etc..
      level2_template = level2_template.replace( "$LEVEL2", ", ".join( level2_arg_list ) )
      first_typename = level1_type_arg_list[0].split(" ")[-1]
      first_typename_datatype = first_typename[0:6].lower() # 'matrix' or 'vector'
      level2_template = level2_template.replace( "$FIRST_TYPENAME", first_typename )
      level2_template = level2_template.replace( "$TYPEOF_FIRST_TYPENAME", first_typename_datatype )
      level2_template = level2_template.replace( "$CALL_LEVEL1", ", ".join( call_level1_arg_list ) )
      level2_template = level2_template.replace( "$TYPES", ", ".join( level1_type_arg_list ) )

      #
      # Workspace stuff
      #
      if info_map[ subroutine ][ 'grouped_arguments' ][ 'by_io' ].has_key( 'workspace' ):
        # Add an include for the workspace stuff
        includes += [ '#include <boost/numeric/bindings/lapack/workspace.hpp>' ]
        includes += [ '#include <boost/numeric/bindings/traits/detail/array.hpp>' ]

        # Continue
        workspace_size = len( info_map[ subroutine ][ 'grouped_arguments' ][ 'by_io' ][ 'workspace' ] )
        workspace_args = info_map[ subroutine ][ 'grouped_arguments' ][ 'by_io' ][ 'workspace' ]
        level1_template = level1_template.replace( "$WORKSPACE_SIZE", str(workspace_size) )
        level1_template = level1_template.replace( "$WORKSPACE_TYPENAMES", "typename " + ", typename ".join( workspace_args ) )
        level1_template = level1_template.replace( "$WORKSPACE_TYPES", ", ".join( workspace_args ) )

        # $TMP_WORKARRAYS is something like "tmp_work, tmp_rwork"
        tmp_workspace_args = []
        for name in info_map[ subroutine ][ 'grouped_arguments' ][ 'by_io' ][ 'workspace' ]:
          tmp_workspace_args += [ 'tmp_' + name.lower() ]
        level1_template = level1_template.replace( "$TMP_WORKARRAYS", ", ".join( tmp_workspace_args ) )
        
        # $SETUP_WORKARRAYS looks like 
        #    traits::detail::array< value_type > $TMP_NAME .... 
        setup_min_workarrays = ''
        setup_opt_workarrays_pre = []
        setup_opt_workarrays_post = []
        for name in info_map[ subroutine ][ 'grouped_arguments' ][ 'by_io' ][ 'workspace' ]:
          # minimal case
          sub_min_template = template_map[ 'setup_min_workspace' ]
          sub_min_template = sub_min_template.replace( '$NAME', name.lower() )
          sub_min_template = sub_min_template.replace( '$WORKSPACE_TYPE', info_map[ subroutine ][ 'argument_map' ][ name ][ 'code' ][ 'workspace_type' ] )
          if info_map[ subroutine ][ 'argument_map' ][ name ][ 'code' ][ 'min_workspace_call' ] != None:
            sub_min_template = sub_min_template.replace( "$CALL_MIN_SIZE", info_map[ subroutine ][ 'argument_map' ][ name ][ 'code' ][ 'min_workspace_call' ] )
          
          setup_min_workarrays += sub_min_template

          # optimal case
          if info_map[ subroutine ][ 'argument_map' ][ name ][ 'code' ][ 'opt_workspace_pre' ] != None:
            setup_opt_workarrays_pre += [ info_map[ subroutine ][ 'argument_map' ][ name ][ 'code' ][ 'opt_workspace_pre' ] ]
          if info_map[ subroutine ][ 'argument_map' ][ name ][ 'code' ][ 'opt_workspace_post' ] != None:
            setup_opt_workarrays_post += [ info_map[ subroutine ][ 'argument_map' ][ name ][ 'code' ][ 'opt_workspace_post' ] ]
          
          
        # if the length of setup_opt_workarrays_post equals 0, it's equal to the minimal_case
        opt_workspace_template = ''
        if len( setup_opt_workarrays_post ) == 0:
          print "EQUAL to MINIMAL CASE!"
          opt_workspace_template = template_map[ 'level1_opt_workspace_is_min' ]
        else:
          includes += [ '#include <boost/numeric/bindings/traits/detail/utils.hpp>' ]
          opt_workspace_template = template_map[ 'level1_opt_workspace' ]
          
        opt_workspace_template = opt_workspace_template.replace( "$WORKSPACE_QUERY", ", ".join( workspace_query_arg_list ) )
        opt_workspace_template = opt_workspace_template.replace( "$SETUP_OPT_WORKARRAYS_POST", "\n        ".join( setup_opt_workarrays_post ) )
        opt_workspace_template = opt_workspace_template.replace( "$SETUP_OPT_WORKARRAYS_PRE", "\n        ".join( setup_opt_workarrays_pre ) )
        opt_workspace_template = opt_workspace_template.replace( "$CALL_LEVEL1", ", ".join( call_level1_arg_list ) )
        opt_workspace_template = opt_workspace_template.replace( "$TMP_WORKARRAYS", ", ".join( tmp_workspace_args ) )
        
      
        if len( user_defined_opt_arg_list ) > 0:
          opt_workspace_template = opt_workspace_template.replace( "$INIT_USER_DEFINED_OPT_VARIABLES", indent_lines( "\n".join(user_defined_arg_list), 8 ) )
        else:
          print "removing $INIT_USER_DEFINED_OPT_VARIABLES"
          opt_workspace_template = opt_workspace_template.replace( "        $INIT_USER_DEFINED_OPT_VARIABLES\n", "" )
        
        
        level1_template = level1_template.replace( "$OPT_WORKSPACE_FUNC", opt_workspace_template.rstrip() )
        level1_template = level1_template.replace( "$SETUP_MIN_WORKARRAYS_POST", setup_min_workarrays.rstrip() )
        
        
        #
        # INSERT THE MINIMAL WORKSPACE FUNCTIONS
        #
        min_size_funcs = ''
        for name in info_map[ subroutine ][ 'grouped_arguments' ][ 'by_io' ][ 'workspace' ]:
          sub_template = template_map[ 'min_size_func' ]
          sub_template = sub_template.replace( "$NAME", name.lower() )
          
          # first: user-defined stuff (overrules any auto-detected stuff)
          my_key = group_name.lower() + '.' + value_type + '.min_size_' + name.lower()
          my_key_all = group_name.lower() + '.all.min_size_' + name.lower()
          print my_key
          if template_map.has_key( my_key ):
            sub_template = sub_template.replace( "$MIN_SIZE", indent_lines( template_map[ my_key ].rstrip(), 8 ) )
            
          # if that fails, try the more generic key "all"
          elif template_map.has_key( my_key_all ):
            sub_template = sub_template.replace( "$MIN_SIZE", indent_lines( template_map[ my_key_all ].rstrip(), 8 ) )
          
          elif info_map[ subroutine ][ 'argument_map' ][ name ][ 'code' ][ 'min_workspace' ] != None:
            resulting_code = 'return ' + info_map[ subroutine ][ 'argument_map' ][ name ][ 'code' ][ 'min_workspace' ] + ';'
            sub_template = sub_template.replace( "$MIN_SIZE", resulting_code.rstrip() )
            
          # Do about the same for the argument stuff.  
          if info_map[ subroutine ][ 'argument_map' ][ name ][ 'code' ][ 'min_workspace_args' ] != None:
            sub_template = sub_template.replace( "$ARGUMENTS", info_map[ subroutine ][ 'argument_map' ][ name ][ 'code' ][ 'min_workspace_args' ] )

            #sub_template += 'FOUND'
          min_size_funcs += sub_template

        min_size_funcs = min_size_funcs.rstrip()
        level1_template = level1_template.replace( "$MIN_SIZE_FUNCS", min_size_funcs )

      level1_map[ value_type ] = bindings.proper_indent( level1_template )
      level2_map[ value_type ] = bindings.proper_indent( level2_template )

    #
    # LEVEL 1 and 2 FINALIZATION
    #
    for mapping in [ level1_map, level2_map ]:
      if len(mapping) > 1:
        # compare real and complex cases
        all_keys = mapping.keys()
        if mapping[ all_keys[0] ] == mapping[ all_keys[1] ]:
          print "literally everything is the same!!, falling back to 1 case"
          del mapping[ all_keys[ 1 ] ]

    level1 = ''
    if len( level1_map ) > 1:
      level1 = template_map[ 'level1_pre_header' ]
      includes += [ '#include <boost/utility/enable_if.hpp>' ]
      includes += [ '#include <boost/numeric/bindings/traits/is_real.hpp>' ]
      includes += [ '#include <boost/numeric/bindings/traits/is_complex.hpp>' ]

    for value_type in level1_map.keys():
      if len( level1_map ) == 1:
        header = template_map[ 'level1_header1' ]
      else:
        header = template_map[ 'level1_header2' ]

      level1 += header.replace( "$SPECIALIZATION", value_type )
      level1 += level1_map[ value_type ]

    level2 = ''
    for value_type in level2_map.keys():
      level2 += level2_map[ value_type ]

    #
    # handle addition of includes
    #
    includes_code = ''
    unique_includes = []
    for include in includes:
      if include not in unique_includes:
        unique_includes += [ include ]
    sorted_includes = sorted( unique_includes, lambda x, y: cmp( x.lower(), y.lower() ) )
    if len( sorted_includes ) > 0:
      includes_code = "\n".join( sorted_includes )

    result = template_map[ 'lapack.hpp' ]
    result = result.replace( '$INCLUDES', includes_code )
    result = result.replace( '$OVERLOADS', overloads )
    result = result.replace( '$LEVEL1', level1 )
    result = result.replace( '$LEVEL2', level2 )
    result = result.replace( '$GROUPNAME', group_name )
    result = result.replace( '$groupname', group_name.lower() )

    # replace the global variables as last (this is convenient)
    #result = result.replace( '$INDENT', '    ' )
    #result = result.replace( '$groupname', group_name.lower() )
    #result = result.replace( '$DESCRIPTION', info_map[ group[g][0] ][ 'description' ] )

    open( os.path.join( base_dir, filename ), 'wb' ).write( result )

#
# Write the (many) driver routine test cases to cpp files.
#
def write_test_case( info_map, group, template_map, base_dir, level_name ):

  for group_name, subroutines in group.iteritems():

    filename = group_name.lower() + '.cpp'
    result = template_map[ 'test_case.cpp' ]
    result = result.replace( '$groupname', group_name.lower() )
    result = result.replace( '$levelname', level_name.lower() )

    open( os.path.join( base_dir, filename ), 'wb' ).write( result )

def write_cmakefile( level_properties, template_map, base_dir ):
  
  entries = '' 
  for problem_type, problem_properties in level_properties.iteritems():
    if problem_properties.has_key( 'routines_by_value_type' ):
      group = problem_properties[ 'routines_by_value_type' ]
      for group_name, subroutines in group.iteritems():
        sub_result = template_map[ 'CMakeLists.entry' ]
        sub_result = sub_result.replace( '$groupname', group_name.lower() )
        entries += sub_result

  filename = 'CMakeLists.txt'
  result = template_map[ 'CMakeLists.txt' ]
  result = result.replace( '$ENTRIES', entries )
  open( os.path.join( base_dir, filename ), 'wb' ).write( result )


def read_templates( template_file ):
  file_contents = open( template_file ).read()
  split_regex = re.compile( '^\$TEMPLATE\[([^\]]+)\]\s', re.M | re.S )
  split_templates = split_regex.split( file_contents )[ 1:-1 ]
  result = {}
  for index in range(len(split_templates)/2):
    print "Adding template", split_templates[ index*2 ]
    result[ split_templates[ index*2 ] ] = split_templates[ index*2 + 1 ]
  return result

lapack_src_path = './lapack-3.1.1/SRC'
template_src_path = './templates'
bindings_target_path = '../../../../boost/numeric/bindings/lapack/'
test_target_path = '../test/lapack/'

templates = {}
templates[ 'PARSERMODE' ] = 'LAPACK'
for root, dirs, files in os.walk( template_src_path ):
  right_file = re.compile( '^.+\.(cpp|h|hpp|txt)$' )
  for template_file in files:
    if right_file.match( template_file ) != None:
      path_to_template_file = os.path.join( root, template_file )
      print "Reading template file", path_to_template_file
      templates.update( read_templates( path_to_template_file ) )

function_info_map = {}
for lapack_file in os.listdir( lapack_src_path ):
  right_file = re.compile( '^[cdsz].+\.f$' )
  if right_file.match( lapack_file ) != None:
    print "Parsing", lapack_file, "..."
    key, value = netlib.parse_file( os.path.join( lapack_src_path, lapack_file ), templates )
    if key != None and value != None:
      print "Adding LAPACK subroutine", key
      function_info_map[ key ] = value

print "Grouping subroutines..."

value_type_groups = {}
value_type_groups = group_by_value_type( function_info_map )

routines = {}
routines[ 'driver' ] = {}
routines[ 'driver' ][ 'linear_equations' ] = {}
routines[ 'driver' ][ 'linear_equations' ][ 'endings' ] = [ 'SV', 'SVX' ]

routines[ 'driver' ][ 'least_squares' ] = {}
routines[ 'driver' ][ 'least_squares' ][ 'endings' ] = [ 'LS', 'LSY', 'LSS', 'LSD' ]

routines[ 'driver' ][ 'general_least_squares' ] = {}
routines[ 'driver' ][ 'general_least_squares' ][ 'endings' ] = [ 'LSE', 'GLM' ]

# based on LAPACK Users' Guide, table 2.5
routines[ 'driver' ][ 'eigen' ] = {}
routines[ 'driver' ][ 'eigen' ][ 'endings' ] = [ 'YEV', 'EEV', 'YEVX', 'EEVX', 'YEVD', 'EEVD', 'YEVR', 'EEVR', 'EES', 'PEV', 'PEVD', 'PEVX', 'BEV', 'BEVD', 'BEVX', 'EESX', 'ESVD', 'ESDD', 'TEV', 'TEVD', 'TEVX', 'TEVR' ]

# based on LAPACK Users' Guide, table 2.6
routines[ 'driver' ][ 'general_eigen' ] = {}
routines[ 'driver' ][ 'general_eigen' ][ 'endings' ] = [ 'GV', 'GVD', 'GVX', 'GES', 'GESX', 'GEV', 'GEVX', 'GSVD' ]


routines[ 'computational' ] = {}

# based on LAPACK Users' Guide, table 2.7
routines[ 'computational' ][ 'linear_equations' ] = {}
routines[ 'computational' ][ 'linear_equations' ][ 'endings' ] = [ 'TRF', 'TRS', 'CON', 'RFS', 'TRI', 'EQU' ]

# based on LAPACK Users' Guide, table 2.9 
routines[ 'computational' ][ 'least_squares' ] = {}
routines[ 'computational' ][ 'least_squares' ][ 'endings' ] = [ 'QP3', 'EQRF', 'GQR', 'MQR', 'LQF', 'GLQ', 'MLQ', 'QLF', 'GQL', 'MQL', 'ERQF', 'GRQ', 'MRQ', 'RZF', 'RZ' ]

routines[ 'computational' ][ 'general_least_squares' ] = {}
routines[ 'computational' ][ 'general_least_squares' ][ 'endings' ] = [ 'GQRF', 'GRQF' ]

# based on LAPACK Users' Guide, table 2.10
routines[ 'computational' ][ 'symmetric_eigen' ] = {}
routines[ 'computational' ][ 'symmetric_eigen' ][ 'endings' ] = [ 'TRD', 'MTR', 'GTR', 'TEQR', 'ERF', 'EDC', 'EGR', 'EBZ', 'TEIN' ]

# based on LAPACK Users' Guide, table 2.11
routines[ 'computational' ][ 'nonsymmetric_eigen' ] = {}
routines[ 'computational' ][ 'nonsymmetric_eigen' ][ 'endings' ] = [ 'EHRD', 'EBAL', 'EBAK', 'GHR', 'MHR', 'SEQR', 'SEIN', 'REVC', 'REXC', 'RSYL', 'RSNA', 'RSEN' ]

# based on LAPACK Users' Guide, table 2.12
routines[ 'computational' ][ 'svd' ] = {}
routines[ 'computational' ][ 'svd' ][ 'endings' ] = [ 'BRD', 'GBR', 'MBR', 'SQR', 'SDC' ]

# based on LAPACK Users' Guide, table 2.14
routines[ 'computational' ][ 'general_eigen' ] = {}
routines[ 'computational' ][ 'general_eigen' ][ 'endings' ] = [ 'GST', 'STF' ]

# based on LAPACK Users' Guide, table 2.15
routines[ 'computational' ][ 'general_nonsymmetric_eigen' ] = {}
routines[ 'computational' ][ 'general_nonsymmetric_eigen' ][ 'endings' ] = [ 'GHRD', 'GBAL', 'GBAK', 'EQZ', 'GEVC', 'GEXC', 'GSYL', 'GSNA', 'GSEN' ]

# based on LAPACK Users' Guide, table 2.16
routines[ 'computational' ][ 'general_nonsymmetric_svd' ] = {}
routines[ 'computational' ][ 'general_nonsymmetric_svd' ][ 'endings' ] = [ 'SVP', 'SJA' ]

for name in value_type_groups.keys():
  found = False
  for level, level_properties in routines.iteritems():
    for problem_type, problem_properties in level_properties.iteritems():
      if name[ -2: ] in problem_properties[ 'endings' ] or \
         name[ -3: ] in problem_properties[ 'endings' ] or \
         name[ -4: ] in problem_properties[ 'endings' ]:
        print name, "is in {"+level+", "+  problem_type + "}"
        if not problem_properties.has_key( 'routines_by_value_type' ):
          problem_properties[ 'routines_by_value_type' ] = {}
        problem_properties[ 'routines_by_value_type' ][ name ] = value_type_groups[ name ]
        found = True
  if found == False:
    print name, "is in {??}"

print routines 


bindings.write_names_header( function_info_map, value_type_groups, templates, bindings_target_path + 'lapack_names.h' )
bindings.write_header( function_info_map, value_type_groups, templates, bindings_target_path + 'lapack.h' )

for level, level_properties in routines.iteritems():
  target_path = bindings_target_path + level
  if not os.path.exists( target_path ):
    os.mkdir( target_path )
  if not os.path.exists( test_target_path + level ):
    os.mkdir( test_target_path + level )

  for problem_type, problem_properties in level_properties.iteritems():
    if problem_properties.has_key( 'routines_by_value_type' ):
      write_functions( function_info_map, problem_properties[ 'routines_by_value_type' ], templates, target_path )

      write_test_case( function_info_map, problem_properties[ 'routines_by_value_type' ], templates, test_target_path + level, level )

  write_cmakefile( level_properties, templates, test_target_path + level )


