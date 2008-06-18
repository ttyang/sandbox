//                    -- main.hpp --
//
//           Copyright (c) Darren Garvey 2007.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
////////////////////////////////////////////////////////////////
//
//[fcgi_echo
//
// This example simply echoes all variables back to the user. ie.
// the environment and the parsed GET, POST and cookie variables.
// Note that GET and cookie variables come from the environment
// variables QUERY_STRING and HTTP_COOKIE respectively.
//
///////////////////////////////////////////////////////////
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/program_options/environment_iterator.hpp>
///////////////////////////////////////////////////////////
#include "boost/cgi/fcgi.hpp"

using namespace std;
using namespace boost::fcgi;

// This is a file to put internal logging info into
#define LOG_FILE "/var/www/log/fcgi_echo.txt"

// The styling information for the page, just to make things look nicer.
static const char* gCSS_text =
"body { padding: 0; margin: 3%; border-color: #efe; }"
".var_map_title"
    "{ font-weight: bold; font-size: large; }"
".var_map"
    "{ border: 1px dotted; padding: 2px 3px 2px 3px; margin-bottom: 3%; }"
".var_pair"
    "{ border-top: 1px dotted; overflow: auto; padding: 0; margin: 0; }"
".var_name"
    "{ position: relative; float: left; width: 30%; font-weight: bold; }"
".var_value"
    "{ position: relative; float: left; width: 65%; left: 1%;"
     " border-left: 1px solid; padding: 0 5px 0 5px;"
     " overflow: auto; white-space: pre; }"
;

//
// This function writes the title and map contents to the ostream in an
// HTML-encoded format (to make them easier on the eye).
//
template<typename OStreamT, typename MapT>
void format_map(OStreamT& os, MapT& m, const std::string& title)
{
  os<< "<div class=\"var_map\">"
         "<div class=\"var_map_title\">"
    <<       title
    <<   "</div>";

  if (m.empty())
    os<< "<div class=\"var_pair\">EMPTY</div>";
  else
    for (typename MapT::const_iterator i = m.begin(); i != m.end(); ++i)
    {
      os<< "<div class=\"var_pair\">"
             "<div class=\"var_name\">"
        <<       i->first
        <<   "</div>"
             "<div class=\"var_value\">"
        <<       i->second
        <<   "</div>"
           "</div>";
    }
  os<< "</div>";
}

std::size_t process_id()
{
#if defined(BOOST_WINDOWS)
  return _getpid();
#else
  return getpid();
#endif
}


/// This function accepts and handles a single request.
template<typename Request>
int handle_request(Request& req)
{
  boost::system::error_code ec;
  
  //
  // Load in the request data so we can access it easily.
  //
  req.load(ec, true); // The 'true' means read and parse STDIN (ie. POST) data.

  //
  // Construct a `response` object (makes writing/sending responses easier).
  //
  response resp;

  //
  // Responses in CGI programs require at least a 'Content-type' header. The
  // library provides helpers for several common headers:
  //
  resp<< content_type("text/html");
  
  // You can also stream text to a response. 
  // All of this just prints out the form 
  resp<< "<html>"
         "<head>"
           "<title>FastCGI Echo Example</title>"
           "<style type=\"text/css\">"
      <<       gCSS_text <<
           "</style>"
         "<head>"
         "<body>"
           "Request ID = " << req.id() << "<br />"
           "Process ID = " << process_id() << "<br />"
           "<form method=POST enctype='multipart/form-data'>"
             "<input type=text name=name value='"
      <<         req[post]["name"] << "' />"
             "<br />"
             "<input type=text name=hello value='"
      <<         req[post]["hello"] << "' />"
             "<br />"
             "<input type=file name=user_file />"
             "<input type=hidden name=cmd value=multipart_test />"
             "<br />"
             "<input type=submit value=submit />"
           "</form><p />";

  //
  // Use the function defined above to show some of the request data.
  // (this function isn't part of the library)
  //
  format_map(resp, req[env], "Environment Variables");
  format_map(resp, req[get], "GET Variables");
  format_map(resp, req[post], "POST Variables");
  format_map(resp, req[cookies], "Cookie Variables");

  // Print the complete buffer containing the POST data and the FastCGI params.
  resp<< "<pre>";
  BOOST_FOREACH(char& ch, req.post_buffer())
  {
    resp<< ch;
  }
  //    << req.get_buffer()
  resp<< "</pre>";

  //
  // Response headers can be added at any time before send/flushing it:
  //
  resp<< "Response content-length == "
      << resp.content_length() // the content-length (returns std::size_t)
      << content_length(resp)  // a content-length header
      << ">";

  // This funky macro finishes up:
  return_(resp, req, 0);
  //
  // It is equivalent to the below, where the third argument is represented by
  // `program_status`:
  //
  // resp.send(req.client());
  // req.close(resp.status(), program_status);
  // return program_status;
  //
  // Note: in this case `program_status == 0`.
  //
}

int main()
{
try {

  // Make a `service` (more about this in other examples).
  service s;
  // Make an `acceptor` for accepting requests through.
  acceptor a(s);

  //
  // After the initial setup, we can enter a loop to handle one request at a
  // time until there's an error of some sort.
  //
  int ret(0);
  for (;;)
  {
    request req(s);
    //
    // Now we enter another loop that reuses the request's memory - makes
    // things more efficient). You should always do this for 
    // now; this requirement might be removed in future.
    //
    for (;;)
    {
      a.accept(req);
      ret = handle_request(req);
      if (ret)
        break;
      //
      // Clear the request's data, so information doesn't pass between
      // different users (this step isn't really necessary, because
      // the library will do this automatically.
      //
      req.clear();
    }
  }
  
  return ret;

}catch(boost::system::system_error& se){
  // This is the type of error thrown by the library.
  cerr<< "[fcgi] System error: " << se.what() << endl;
  return 1313;
}catch(exception* e){
  // Catch any other exceptions
  cerr<< "[fcgi] Exception: " << e->what() << endl;
  return 666;
}catch(...){
  cerr<< "[fcgi] Uncaught exception!" << endl;
  return 667;
}
}
//]
