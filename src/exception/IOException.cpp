/**
* \file IOException.cpp
* \brief Contains definition of IOException class.
*/

#include <exception/IOException.hpp>

using namespace bil;


IOException::IOException() throw():
  Exception()
{

}


IOException::IOException(const std::string& what_arg) throw():
  Exception(what_arg)
{

}