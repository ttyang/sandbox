//  Copyright (c) 2008 Oliver Kowalke. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TASK_DETAIL_SEMAPHORE_WINDOWS_H
#define BOOST_TASK_DETAIL_SEMAPHORE_WINDOWS_H

extern "C"
{
#include <Windows.h>
}

#include <boost/utility.hpp>

namespace boost { namespace task
{
namespace detail
{
class semaphore : private boost::noncopyable
{
private:
	HANDLE	handle_;

public:
	semaphore( int);

	~semaphore();

	void post();

	bool try_wait();
	void wait();

	int value();
};
}}}

#endif // BOOST_TASK_DETAIL_SEMAPHORE_WINDOWS_H
