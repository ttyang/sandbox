#ifndef UTILITY_INDENT_SCOPE_HPP
#define UTILITY_INDENT_SCOPE_HPP
#include <boost/iostreams/utility/indent_scoped_ostreambuf.hpp>
#include <string>
namespace boost
{
  template
  < typename Enter=std::string
  , typename Exit=Enter
  >
  class
indent_scope
  //Purpose:
  //  Indicate on cout when a scope entered and exited.
  {
  public:
    indent_scope
      ( Enter a_enter=""
      , Exit a_exit=""
      )
      : my_exit(a_exit)
      {
      ; std::cout<<a_enter
      ; std::cout<<indent_buf_in
      ;}
    ~indent_scope(void)
      {
      ; std::cout<<indent_buf_out
      ; std::cout<<my_exit
      ;}
  private:
      Exit
    my_exit
      ;
  };//end indent_scope class
}//exit boost namespace
#endif
