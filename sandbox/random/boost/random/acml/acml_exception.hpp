// Copyright Fabian Bösch 2012
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/**
 *  @file 
 *  @brief This file contains an exception class used for the ACML random number engines.
 */

#ifndef BOOST_RANDOM_ACML_EXCEPTION_HPP
#define BOOST_RANDOM_ACML_EXCEPTION_HPP

#include <stdexcept>
#include <string>

namespace boost {
namespace random {
namespace acml {

const char errmsg[100] = "Input argument value is not valid.";

/// An exception class for AMD ACML error codes.
class acml_exception : public std::exception
{
    public:

    /** @brief Construct from error code.
     *  @param errcode ACML error code.
     */
    acml_exception(long errcode)
    {
        //msg_ptr = &msg_badargs;
    }

    /// Destruct exception.
    virtual ~acml_exception() throw() {}

    /** @brief Error description.
     *  @return Error message.
     */
    virtual const char* what() const throw()
    {
        //return msg_ptr->c_str();
		return errmsg;
    }

    private:

    //static const std::string msg_badargs;

    //const std::string* msg_ptr;
};

/** @brief Check for ACML errors.
 *  Throw an instance of @c acml_exception if error occurs.
 *  @param errcode ACML error code.
 */
inline void check_errcode(long errcode)
{
    if (errcode != 0 && errcode != 1) throw boost::random::acml::acml_exception(errcode);
}

} // acml
} // random
} // boost


#endif // BOOST_RANDOM_ACML_EXCEPTION_HPP

