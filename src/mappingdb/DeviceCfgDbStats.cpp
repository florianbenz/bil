/**
* \file DeviceCfgDbStats.cpp
* \brief Contains definition of DeviceCfgDbStats class.
*/

#include <iomanip>
#include <mappingdb/DeviceCfgDbStats.hpp>
#include <util/HexPrint.hpp>

using namespace bil;


const char* const STATMSG_TILETYPE = "Tile type: ";
const char* const STATMSG_CSCOUNT = "\n\tNumber of PIP control sets: ";
const char* const STATMSG_CSHEADER = "\tPIP control set ";
const char* const STATMSG_BITOFFSETS = ":\n\t\tBit offsets: ";
const char* const STATMSG_BITVALUES = "\n\t\tBit values:\n";
const char* const STATMSG_NOTISOLATED = "NOT ISOLATED";
const char* const STATMSG_ZEROED = "ZEROED";
const char* const STATMSG_OUTOF = " out of ";
const char* const STATMSG_PIPSISOLATED = "PIPs isolated: ";
const char* const STATMSG_PIPSZEROED = "PIPs zeroed: ";
const char* const STATMSG_PIPSNOTISOLATED = "PIPs not isolated: ";
const char* const STATMSG_PERCENTBEGIN = " (";
const char* const STATMSG_PERCENTEND = "%)";
const char* const STATMSG_PIPINDENT = "\t\t\t";
const char* const STATMSG_ENDP = "\n\n";
const char* const STATMSG_COMMA = ", ";
const char* const STATMSG_COLON = ": ";
const char STATMSG_SPACE = ' ';
const char STATMSG_INDENTCHAR = '\t';
const char STATMSG_ENDLN = '\n';


void DeviceCfgDbStats::printStats(const DeviceCfgDb& db,
  const Device& device, std::ostream& outStream)
{
    // save output stream pointer
    m_outputStream = &outStream;

    // reset stats
    m_devicePIPCount = 0;
    m_deviceIsolatedPIPCount = 0;
    m_deviceZeroPIPCount = 0;
    m_deviceNotIsolatedPIPCount = 0;

    // save data base pointers
    const TileTypeCfgDbs& tileTypeDbs = db.tileTypeDbs();
    const TileTypes& tileTypes = device.tileTypes();

    // loop over all tile types and their data bases and print their stats
    size_t tileTypeDbCount = tileTypeDbs.size();
    for (size_t i = 0; i < tileTypeDbCount; ++i)
    {
        const TileTypeCfgDb& tileTypeDb = tileTypeDbs[i];
        const TileType& tileType = tileTypes.at(tileTypeDb.typeIndex());
        printTileType(tileTypeDb, tileType);
    }

    // print global stats
    printPIPCounts(0, m_devicePIPCount, m_deviceIsolatedPIPCount,
                   m_deviceZeroPIPCount, m_deviceNotIsolatedPIPCount);
}


void DeviceCfgDbStats::printTileType(const TileTypeCfgDb& db,
  const TileType& tileType)
{
    // get PIP control sets, wires, and PIPs of this tile type
    const PIPControlSets& pipControlSets = db.pipControlSets();
    size_t pipControlSetCount = pipControlSets.size();
    const Wires& wires = tileType.wires();
    const PIPs& pips = tileType.pips();

    // reset tile type stats
    m_tileTypePIPCount = 0;
    m_tileTypeIsolatedPIPCount = 0;
    m_tileTypeZeroPIPCount = 0;
    m_tileTypeNotIsolatedPIPCount = 0;

    // print header for this tile type
    (*m_outputStream) << STATMSG_TILETYPE << tileType.name();
    (*m_outputStream) << STATMSG_CSCOUNT << pipControlSetCount << STATMSG_ENDP;

    // loop over all control sets and print them
    for (size_t i = 0; i < pipControlSetCount; ++i)
    {
        const PIPControlSet& pipControlSet = pipControlSets[i];
        printPIPControlSet(pipControlSet, i, wires, pips);
    }

    // print tile type stats
    printPIPCounts(1, m_tileTypePIPCount, m_tileTypeIsolatedPIPCount,
                   m_tileTypeZeroPIPCount, m_tileTypeNotIsolatedPIPCount);

    // increment global stats by this tile type stats
    m_devicePIPCount += m_tileTypePIPCount;
    m_deviceIsolatedPIPCount += m_tileTypeIsolatedPIPCount;
    m_deviceZeroPIPCount += m_tileTypeZeroPIPCount;
    m_deviceNotIsolatedPIPCount += m_tileTypeNotIsolatedPIPCount;
}


void DeviceCfgDbStats::printPIPControlSet(const PIPControlSet& cs,
  size_t csIndex, const Wires& wires, const PIPs& pips)
{
    // reset control set stats
    size_t isolatedPIPCount = 0;
    size_t zeroPIPCount = 0;
    size_t notIsolatedPIPCount = 0;

    // print control set header
    (*m_outputStream) << STATMSG_CSHEADER << csIndex;

    // print bit offsets
    (*m_outputStream) << STATMSG_BITOFFSETS;
    const BitPositions& bitPositions = cs.bitPositions();
    size_t bitPositionCount = bitPositions.size();
    for (size_t i = 0; i < bitPositionCount; ++i)
    {
        if (i != 0) (*m_outputStream) << STATMSG_COMMA;
        (*m_outputStream) << bitPositions[i];
    }

    // print pip bit values
    (*m_outputStream) << STATMSG_BITVALUES;
    const PIPBitValues& pipBitValues = cs.pipBitValues();
    size_t pipCount = pipBitValues.size();
    for (size_t i = 0; i < pipCount; ++i)
    {
        // get PIP bit value
        const PIPBitValue& pipBitValue = pipBitValues[i];

        // get PIP and print it
        const PIP& pip = pips.at(pipBitValue.pipIndex());
        const Wire& startWire = wires.at(pip.startWireIndex());
        const Wire& endWire = wires.at(pip.endWireIndex());
        (*m_outputStream) << STATMSG_PIPINDENT << startWire.name() << STATMSG_SPACE;
        (*m_outputStream) << PIPDirection::toString(pip.direction()) << STATMSG_SPACE;
        (*m_outputStream) << endWire.name() << STATMSG_COLON;

        // print PIP bit value
        boost::uint32_t value = pipBitValue.bitValue();
        if (0 != (value & PIPBitValue::VALUE_UNUSED))
        {
            (*m_outputStream) << STATMSG_NOTISOLATED;
            ++notIsolatedPIPCount;
        }
        else if (0 == value)
        {
            (*m_outputStream) << STATMSG_ZEROED;
            ++zeroPIPCount;
        }
        else
        {
            (*m_outputStream) << hexString(value);
            ++isolatedPIPCount;
        }
        (*m_outputStream) << STATMSG_ENDLN;
    }
    (*m_outputStream) << STATMSG_ENDLN;

    // increment tile type stats by control set stats
    m_tileTypePIPCount += pipCount;
    m_tileTypeIsolatedPIPCount += isolatedPIPCount;
    m_tileTypeZeroPIPCount += zeroPIPCount;
    m_tileTypeNotIsolatedPIPCount += notIsolatedPIPCount;
}


void DeviceCfgDbStats::printPIPCounts(size_t indent, size_t total,
  size_t isolated, size_t zero, size_t notIsolated)
{
    // set up indentation
    std::string indentStr(indent, STATMSG_INDENTCHAR);
    // set up percentage output
    float fTotal = ((total != 0) ? (100.0f / total) : 0);
    (*m_outputStream) << std::fixed << std::setprecision(1);

    // print stats for isolated PIPs
    (*m_outputStream) << indentStr << STATMSG_PIPSISOLATED << isolated;
    (*m_outputStream) << STATMSG_OUTOF << total;
    if (0 != total) (*m_outputStream) << STATMSG_PERCENTBEGIN << (isolated*fTotal) << STATMSG_PERCENTEND;
    (*m_outputStream) << STATMSG_ENDLN;

    // print stats for zeroed PIPs
    (*m_outputStream) << indentStr << STATMSG_PIPSZEROED << zero;
    (*m_outputStream) << STATMSG_OUTOF << total;
    if (0 != total) (*m_outputStream) << STATMSG_PERCENTBEGIN << (zero*fTotal) << STATMSG_PERCENTEND;
    (*m_outputStream) << STATMSG_ENDLN;

    // print stats for not isolated PIPs
    (*m_outputStream) << indentStr << STATMSG_PIPSNOTISOLATED << notIsolated;
    (*m_outputStream) << STATMSG_OUTOF << total;
    if (0 != total) (*m_outputStream) << STATMSG_PERCENTBEGIN << (notIsolated*fTotal) << STATMSG_PERCENTEND;
    (*m_outputStream) << STATMSG_ENDP;
}