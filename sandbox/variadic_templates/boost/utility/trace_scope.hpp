#ifndef UTILITY_TRACE_SCOPE_HPP
#define UTILITY_TRACE_SCOPE_HPP
#include <boost/utility/indent_scope.hpp>
namespace boost
{
  class
trace_scope
  //Purpose:
  //  Indicate on cout when a scope entered and exited.
  : indent_scope<>
  {
  public:
      template
      < typename ScopeName
      >
    trace_scope(ScopeName a_scopeName)
      : indent_scope<>
        ( std::string("===>Enter:{{")+a_scopeName+"\n"
        , std::string("===>Exit:}}")+a_scopeName+"\n"
        )
      {
      }
  };//end trace_scope class
}//exit boost namespace
#endif
