// Copyright Fabian Bösch 2012
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/**
 *  @file 
 *  @brief This file contains an exception class used for the MKL random number engines.
 */

#ifndef BOOST_RANDOM_MKL_VSL_EXCEPTION_HPP
#define BOOST_RANDOM_MKL_VSL_EXCEPTION_HPP

#include <mkl_vsl.h>
#include <stdexcept>
#include <string>
#include <iostream>

namespace boost {
namespace random {
namespace mkl {

const char errmsg[31][500] = { 
	"Input argument value is not valid.",
	"CPU version is not supported.",
	"Feature invoked is not implemented.",
	"System cannot allocate memory.",
	"Input pointer argument is NULL.",
	"Unknown error.",
	"File format is unknown.",
	"Descriptive random stream format is unknown.",
	"The value in NBits field is bad.",
	"The value in NSeeds field is bad.",
	"The random stream is invalid.",
	"The value in StreamStateSize field is bad.",
	"Callback function for an abstract BRNG returns an invalid number of updated entries in a buffer, that is, < 0 or >nmax.",
	"The value in WordSize field is bad.",
	"BRNG is not supported by the function.",
	"Registration cannot be completed due to lack of free entries in the table of registered BRNGs.",
	"Two BRNGs are not compatible for the operation.",
	"Error in closing the file.",
	"Error in opening the file.",
	"Error in reading the file.",
	"Error in writing the file.",
	"The abstract random stream is invalid.",
	"BRNG index is not valid.",
	"BRNG does not support Leapfrog method.",
	"Callback function for an abstract BRNG returns zero as the number of updated entries in a buffer.",
	"Period of the generator is exceeded.",
	"BRNG does not support Skip-Ahead method.",
	"File format version is not supported.",
	"Non-deterministic random number generator is not supported on the CPU running the application.",
	"Number of retries to generate a random number using non-deterministic random number generator exceeds threshold.",
	"Something bad happened."
};

/// An exception class for Intel MKL VSL error codes.
class vsl_exception : public std::exception
{
    public:

    /** @brief Construct from error code.
     *  @param errcode VSL error code.
     */
    vsl_exception(int errcode)
    {
        switch (errcode)
        {
			case VSL_ERROR_BADARGS:
                msg_ptr = errmsg[0];
                break;
            case VSL_ERROR_CPU_NOT_SUPPORTED:
                msg_ptr = errmsg[1];
                break;
            case VSL_ERROR_FEATURE_NOT_IMPLEMENTED:
                msg_ptr = errmsg[2];
                break;
            case VSL_ERROR_MEM_FAILURE:
                msg_ptr = errmsg[3];
                break;
            case VSL_ERROR_NULL_PTR:
                msg_ptr = errmsg[4];
                break;
            case VSL_ERROR_UNKNOWN:
                msg_ptr = errmsg[5];
                break;
            case VSL_RNG_ERROR_BAD_FILE_FORMAT:
                msg_ptr = errmsg[6];
                break;
            case VSL_RNG_ERROR_BAD_MEM_FORMAT:
                msg_ptr = errmsg[7];
                break;
            case VSL_RNG_ERROR_BAD_NBITS:
                msg_ptr = errmsg[8];
                break;
            case VSL_RNG_ERROR_BAD_NSEEDS:
                msg_ptr = errmsg[9];
                break;
            case VSL_RNG_ERROR_BAD_STREAM:
                msg_ptr = errmsg[10];
                break;
            case VSL_RNG_ERROR_BAD_STREAM_STATE_SIZE:
                msg_ptr = errmsg[11];
                break;
            case VSL_RNG_ERROR_BAD_UPDATE:
                msg_ptr = errmsg[12];
                break;
            case VSL_RNG_ERROR_BAD_WORD_SIZE:
                msg_ptr = errmsg[13];
                break;
            case VSL_RNG_ERROR_BRNG_NOT_SUPPORTED:
                msg_ptr = errmsg[14];
                break;
            case VSL_RNG_ERROR_BRNG_TABLE_FULL:
                msg_ptr = errmsg[15];
                break;
            case VSL_RNG_ERROR_BRNGS_INCOMPATIBLE:
                msg_ptr = errmsg[16];
                break;
            case VSL_RNG_ERROR_FILE_CLOSE:
                msg_ptr = errmsg[17];
                break;
            case VSL_RNG_ERROR_FILE_OPEN:
                msg_ptr = errmsg[18];
                break;
            case VSL_RNG_ERROR_FILE_READ:
                msg_ptr = errmsg[19];
                break;
            case VSL_RNG_ERROR_FILE_WRITE:
                msg_ptr = errmsg[20];
                break;
            case VSL_RNG_ERROR_INVALID_ABSTRACT_STREAM:
                msg_ptr = errmsg[21];
                break;
            case VSL_RNG_ERROR_INVALID_BRNG_INDEX:
                msg_ptr = errmsg[22];
                break;
            case VSL_RNG_ERROR_LEAPFROG_UNSUPPORTED:
                msg_ptr = errmsg[23];
                break;
            case VSL_RNG_ERROR_NO_NUMBERS:
                msg_ptr = errmsg[24];
                break;
            case VSL_RNG_ERROR_QRNG_PERIOD_ELAPSED:
                msg_ptr = errmsg[25];
                break;
            case VSL_RNG_ERROR_SKIPAHEAD_UNSUPPORTED:
                msg_ptr = errmsg[26];
                break;
            case VSL_RNG_ERROR_UNSUPPORTED_FILE_VER:
                msg_ptr = errmsg[27];
                break;
            case VSL_RNG_ERROR_NONDETERM_NOT_SUPPORTED:
                msg_ptr = errmsg[28];
                break;
            case VSL_RNG_ERROR_NONDETERM_NRETRIES_EXCEEDED:
                msg_ptr = errmsg[29];
                break;
            default:
                msg_ptr = errmsg[30];
        }
    }

    /// Destruct exception.
    virtual ~vsl_exception() throw() {}

    /** @brief Error description.
     *  @return Error message.
     */
    virtual const char* what() const throw()
    {
		return msg_ptr;
    }

    private:

	const char* msg_ptr;
};

/** @brief Check for VSL errors.
 *  Throw an instance of @c vsl_exception if error occurs.
 *  @param errcode VSL error code.
 */
inline void check_errcode(int errcode)
{
    if (errcode != VSL_STATUS_OK && errcode != VSL_ERROR_OK) 
	{
		std::cout << "not ok!!!!!" << std::endl;
		throw boost::random::mkl::vsl_exception(errcode);
	}
}

} // mkl
} // random
} // boost

#endif // BOOST_RANDOM_MKL_VSL_EXCEPTION_HPP

