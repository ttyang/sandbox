# Find each subdirectory containing a CMakeLists.txt file, and include
# it. This avoids the need to manually list which libraries in Boost
# have CMakeLists.txt files.

# return a list of directories that we should add_subdirectory()
macro(BOOST_COLLECT_SUBPROJECT_DIRECTORY_NAMES varname filename)
  file(GLOB BOOST_LIBRARY_CMAKE_FILES 
    RELATIVE "${CMAKE_SOURCE_DIR}/libs" "*/${filename}")
  foreach(BOOST_LIB_CMAKE_FILE ${BOOST_LIBRARY_CMAKE_FILES})
    get_filename_component(BOOST_LIB_DIR ${BOOST_LIB_CMAKE_FILE} PATH)
    set(${varname} ${${varname}} ${BOOST_LIB_DIR})
  endforeach(BOOST_LIB_CMAKE_FILE ${BOOST_LIBRARY_CMAKE_FILES})
endmacro(BOOST_COLLECT_SUBPROJECT_DIRECTORY_NAMES varname)

macro(ADD_SUBDIRECTORIES prefix)
  foreach(subdir ${ARGN})
    MESSAGE(STATUS "${prefix}${subdir}")
    add_subdirectory(${subdir})
  endforeach(subdir ${ARGN})
endmacro(ADD_SUBDIRECTORIES prefix)

# Find all of the subdirectories with .cmake files in them. These are
# the libraries with dependencies.
boost_collect_subproject_directory_names(BOOST_MODULE_DIRS "module.cmake")
foreach(subdir ${BOOST_MODULE_DIRS})
  include("${CMAKE_SOURCE_DIR}/libs/${subdir}/module.cmake")
endforeach(subdir)

# Find all of the subdirectories with CMakeLists.txt files in
# them. This contains all of the Boost libraries.
boost_collect_subproject_directory_names(BOOST_SUBPROJECT_DIRS "CMakeLists.txt")

# Add all of the Boost projects in reverse topological order, so that
# a library's dependencies show up before the library itself.
set(CPACK_INSTALL_CMAKE_COMPONENTS_ALL)
list(SORT BOOST_SUBPROJECT_DIRS)
topological_sort(BOOST_SUBPROJECT_DIRS BOOST_ _DEPENDS)
add_subdirectories(" + " ${BOOST_SUBPROJECT_DIRS})

# Export the list of components to be installed
set(CPACK_COMPONENTS_BOOST_ALL ${CPACK_COMPONENTS_BOOST_ALL} PARENT_SCOPE)
set(CPACK_COMPONENT_GROUPS_BOOST_ALL ${CPACK_COMPONENT_GROUPS_BOOST_ALL} PARENT_SCOPE)

# Export all of the variables that have been marked as "to be exported"
foreach(MACRO ${BOOST_EXPORT_MACROS})
  set(${MACRO} ${${MACRO}} PARENT_SCOPE)
endforeach()
