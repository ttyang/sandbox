
#ifndef DEMANGLE_HPP
#define DEMANGLE_HPP

#include <string>
#include <typeinfo>
#include <cxxabi.h>

std::string demangle(std::string const& name)
{
    return std::string(abi::__cxa_demangle(name.c_str(), 0, 0, 0));
}

#endif
