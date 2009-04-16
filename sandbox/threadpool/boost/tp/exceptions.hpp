//  Copyright (c) 2008 Oliver Kowalke. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TP_EXCEPTIONS_H
#define BOOST_TP_EXCEPTIONS_H

#include <stdexcept>
#include <string>

namespace boost { namespace tp
{
class invalid_poolsize : public std::invalid_argument
{
public:
    invalid_poolsize()
	: std::invalid_argument("core poolsize must be greater than zero")
	{}
};

class invalid_scanns : public std::invalid_argument
{
public:
    invalid_scanns()
	: std::invalid_argument("scanns must be greater than or equal to zero")
	{}
};

class invalid_timeduration : public std::invalid_argument
{
public:
    invalid_timeduration()
	: std::invalid_argument("argument asleep is not valid")
	{}
};

class invalid_watermark : public std::invalid_argument
{
public:
    invalid_watermark( std::string const& msg)
	: std::invalid_argument( msg)
	{}
};

class task_already_executed : public std::logic_error
{
public:
    task_already_executed()
	: std::logic_error("task already executed")
	{}
};

struct task_interrupted
{};

class task_rejected : public std::runtime_error
{
public:
    task_rejected( std::string const& msg)
	: std::runtime_error( msg)
	{}
};
} }

#endif // BOOST_TP_EXCEPTIONS_H
