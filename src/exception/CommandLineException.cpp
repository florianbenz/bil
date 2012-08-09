/**
* \file CommandLineException.cpp
* \brief Contains definition of CommandLineException class.
*/

#include <exception/CommandLineException.hpp>

using namespace bil;


CommandLineException::CommandLineException() throw():
  Exception()
{

}


CommandLineException::CommandLineException(const std::string& what_arg) throw():
  Exception(what_arg)
{

}