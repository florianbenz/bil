/**
* \file Exception.cpp
* \brief Contains definition of Exception class.
*/

#include <exception/Exception.hpp>

using namespace bil;


Exception::Exception() throw():
  runtime_error(std::string())
{

}


Exception::Exception(const std::string& what_arg) throw():
  runtime_error(what_arg)
{

}