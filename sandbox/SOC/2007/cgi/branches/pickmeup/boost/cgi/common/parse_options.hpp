
#ifndef BOOST_CGI_COMMON_PARSE_OPTIONS_HPP_INCLUDED_
#define BOOST_CGI_COMMON_PARSE_OPTIONS_HPP_INCLUDED_

namespace cgi {
 namespace common {

   // Parser options for loading requests. Note that you should *always*
   // parse the environment before using a request object. If you don't parse
   // anything you will have unspecified behaviour.
   enum parse_options
   {
       parse_none        = 0
     , parse_env         = 1
     , parse_get_only    = 2
     , parse_get         = parse_get_only | parse_env
     , parse_post_only   = 4
     , parse_post        = parse_post_only | parse_env
     , parse_form        = parse_env | parse_get | parse_post
     , parse_cookie_only = 8
     , parse_cookie      = parse_cookie_only | parse_env
     , parse_all         = parse_env | parse_form | parse_cookie
   };

 } // namespace common
} // namespace cgi

#endif // BOOST_CGI_COMMON_PARSE_OPTIONS_HPP_INCLUDED_

