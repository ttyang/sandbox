/*



FIXME change the workflow & logger's definition - it doesn't need a filter
all gather classes - they need to typedef the param they take, so that I can create a virtual function.
no more process_msg class -> remove from docs!
gathering the message - gather class must hold "param" type!
gather namespace - rewrite docs

tell about logger_format_write <> -  in format_write<> as well


------> FIXME after showing scenarios, show customizing?







about process_msg
about macros - macros.hpp -> have specific page
about non_const_context

about formatting
about thread-safety


writer namespace , etc.
compilers


convert- also explain that you can convert from str x to y; for instance write_time can actually append the time (instead of prepending it - default)!

formatters - most of them don't need thread-safety, destinations usually need . Explain why/how/when




*/