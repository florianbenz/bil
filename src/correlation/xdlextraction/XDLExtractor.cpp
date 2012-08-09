/**
* \file XDLExtractor.cpp
* \brief Contains definition of XDLExtractor class.
*/

#include <correlation/xdlextraction/XDLExtractor.hpp>
#include <xdl/model/Design.hpp>
#include <xdlrc/model/Device.hpp>

using namespace bil;


XDLExtractor::XDLExtractor(const Design& design, const Device& device):
  m_design(&design),
  m_device(&device)
{

}


void XDLExtractor::getTileTypeUnits(CorrelationUnits& units,
  TileIndices& tileIndices, size_t tileTypeIndex)
{
    // clear old data
    units.clear();
    tileIndices.clear();
    m_tileUnitMap.clear();

    // get PIP count of requested tile type
    const TileTypes& tileTypes = m_device->tileTypes();
    const TileType& tileType = tileTypes.at(tileTypeIndex);
    m_pipCount = (tileType.pips()).size();

    // cache some pointers
    const Nets& nets = m_design->nets();
    const Tiles& tiles = m_device->tiles();

    // loop over all nets in design
    size_t netCount = nets.size();
    for (size_t i = 0; i < netCount; ++i)
    {
        // loop over all active PIPs in current net
        const Net& net = nets[i];
        const PIPRefs& pips = net.pipRefs();
        size_t activePIPCount = pips.size();
        for (size_t j = 0; j < activePIPCount; ++j)
        {
            const PIPRef pip = pips[j];

            // lookup PIP's tile location and test, if its type is given one
            size_t tileIndex = pip.tileIndex();
            const Tile& tile = tiles.at(tileIndex);
            if (tile.typeIndex() != tileTypeIndex) continue;

            // if so, create/find map entry for that tile and set this PIP
            CorrelationUnit& unit = addCorrelationUnit(tileIndex);
            unit.setPIPBit(pip.pipIndex());
        }
    }

    // set result lists to match unit count
    size_t tileUnitCount = m_tileUnitMap.size();
    units.reserve(tileUnitCount);
    tileIndices.reserve(tileUnitCount);
    // copy from map to result lists
    tileUnitMap_t::const_iterator it = m_tileUnitMap.begin();
    tileUnitMap_t::const_iterator itEnd = m_tileUnitMap.end();
    for (; it != itEnd; ++it)
    {
        units.push_back(it->second);
        tileIndices.push_back(it->first);
    }

    // clear map
    m_tileUnitMap.clear();
}


CorrelationUnit& XDLExtractor::addCorrelationUnit(size_t tileIndex)
{
    // Check, if given tile index is already in map. If so, return its
    // associated correlation unit.
    tileUnitMap_t::iterator lb = m_tileUnitMap.lower_bound(tileIndex);
    if ((m_tileUnitMap.end() != lb) && (tileIndex == lb->first))
        return lb->second;

    // create a new entry in map
    tileUnitMap_t::iterator it =
        m_tileUnitMap.insert(lb, std::make_pair(tileIndex, CorrelationUnit()));
    // set its PIP count
    CorrelationUnit& unit = it->second;
    unit.pipBitSize(m_pipCount);

    // return it
    return unit;
}