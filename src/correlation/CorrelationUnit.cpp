/**
* \file CorrelationUnit.cpp
* \brief Contains definition of CorrelationUnit class.
*/

#include <correlation/CorrelationUnit.hpp>
#include <exception/Exception.hpp>

using namespace bil;


void CorrelationUnit::pipBitSize(size_t size)
{
    m_pipBits.resize(size);
}


size_t CorrelationUnit::pipBitSize() const
{
    return m_pipBits.size();
}


void CorrelationUnit::setPIPBit(size_t index)
{
    m_pipBits.set(index);
}


void CorrelationUnit::resetPIPBit(size_t index)
{
    m_pipBits.reset(index);
}


void CorrelationUnit::setPIPBits()
{
    m_pipBits.set();
}


void CorrelationUnit::resetPIPBits()
{
    m_pipBits.reset();
}


bool CorrelationUnit::testPIPBit(size_t index) const
{
    return m_pipBits.test(index);
}


bool CorrelationUnit::isIsolated() const
{
    // search for first set bit
    size_t index = m_pipBits.find_first();
    if (INVALID_BIT_INDEX == index) return false;

    // search for second set bit
    index = m_pipBits.find_next(index);
    return (INVALID_BIT_INDEX == index);
}


void CorrelationUnit::cfgBitSize(size_t size)
{
    m_cfgBits.resize(size);
}


size_t CorrelationUnit::cfgBitSize() const
{
    return m_cfgBits.size();
}


void CorrelationUnit::setCfgBit(size_t index)
{
    m_cfgBits.set(index);
}


void CorrelationUnit::resetCfgBit(size_t index)
{
    m_cfgBits.reset(index);
}


void CorrelationUnit::setCfgBits()
{
    m_cfgBits.set();
}


void CorrelationUnit::resetCfgBits()
{
    m_cfgBits.reset();
}


bool CorrelationUnit::testCfgBit(size_t index) const
{
    return m_cfgBits.test(index);
}


size_t CorrelationUnit::firstCfgBit() const
{
    return m_cfgBits.find_first();
}


size_t CorrelationUnit::nextCfgBit(size_t index) const
{
    return m_cfgBits.find_next(index);
}


void CorrelationUnit::appendCfgBits(boost::uint32_t* data, size_t dataWordCount)
{
    m_cfgBits.append(data, data + dataWordCount);
}


void CorrelationUnit::intersect(const CorrelationUnit& with)
{
    // test if sizes match
    if (m_pipBits.size() != with.m_pipBits.size()) throw Exception();
    if (m_cfgBits.size() != with.m_cfgBits.size()) throw Exception();
    // do intersection
    m_pipBits &= with.m_pipBits;
    m_cfgBits &= with.m_cfgBits;
}


void CorrelationUnit::intersectInverted(const CorrelationUnit& with)
{
    // test if sizes match
    if (m_pipBits.size() != with.m_pipBits.size()) throw Exception();
    if (m_cfgBits.size() != with.m_cfgBits.size()) throw Exception();
    // do subtraction
    m_pipBits -= with.m_pipBits;
    m_cfgBits -= with.m_cfgBits;
}