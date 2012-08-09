/**
* \file PrimitiveSite.cpp
* \brief Contains definition of PrimitiveSite class.
*/

#include <xdlrc/model/PrimitiveSite.hpp>

using namespace bil;


PrimitiveSite::PrimitiveSite():
  m_name(),
  m_bonded(false)
{

}


std::string& PrimitiveSite::name()
{
    return m_name;
}


const std::string& PrimitiveSite::name() const
{
    return m_name;
}


void PrimitiveSite::isBonded(bool flag)
{
    m_bonded = flag;
}


bool PrimitiveSite::isBonded() const
{
    return m_bonded;
}


void PrimitiveSite::clear()
{
    m_name.clear();
    m_bonded = false;
}