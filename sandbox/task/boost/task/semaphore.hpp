
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TASK_SEMAPHORE_H
#define BOOST_TASK_SEMAPHORE_H

#include <boost/task/detail/config.hpp>

extern "C"
{
# if defined(BOOST_WINDOWS_API)
#include <Windows.h>
# elif defined(BOOST_POSIX_API)
#include <semaphore.h>
# endif
}

#include <boost/utility.hpp>

#include <boost/task/detail/config.hpp>

#include <boost/config/abi_prefix.hpp>

# if defined(BOOST_MSVC)
# pragma warning(push)
# pragma warning(disable:4251 4275)
# endif

namespace boost {
namespace task {

class BOOST_TASK_DECL semaphore : private boost::noncopyable
{
private:
# if defined(BOOST_WINDOWS_API)
	HANDLE	handle_;
# elif defined(BOOST_POSIX_API)
	sem_t	handle_;;
# endif
public:
	semaphore( int);

	~semaphore();

	void post();

	void wait();
	bool try_wait();

	int value();
};

}}

# if defined(BOOST_MSVC)
# pragma warning(pop)
# endif


#include <boost/config/abi_suffix.hpp>

#endif // BOOST_TASK_SEMAPHORE_H
