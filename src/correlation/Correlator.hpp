/**
* \file Correlator.hpp
* \brief Contains declaration of Correlator class.
*/

#pragma once
#ifndef BIL_CORRELATOR_HPP
#define BIL_CORRELATOR_HPP

#include <map>
#include <correlation/CorrelationUnit.hpp>
#include <correlation/cfgextraction/CfgExtractor.hpp>
#include <correlation/xdlextraction/XDLExtractor.hpp>
#include <mappingdb/DeviceCfgDb.hpp>
#include <xdl/model/Design.hpp>
#include <xdlrc/model/Device.hpp>


namespace bil {

    /**
    * \brief Correlates the data of a Design with its binary configuration data.
    *
    * This class does the main work for associating the Design data (activated
    * PIPs and set options) with the binary configuration data. The results of
    * this correlation process will be saved into a DeviceCfgDb data base.
    */
    class Correlator {
    public:

        /**
        * \brief Runs the correlation algorithm.
        * \param db The configuration data base to fill.
        * \param design The design to correlate.
        * \param device The device the design is for.
        * \param cfgExtractor Extractor for retrieving the configuration data.
        * \throws .
        */
        void run(DeviceCfgDb& db, const Design& design, const Device& device, CfgExtractor& cfgExtractor);


    private:

        void gatherCorrelationUnits(size_t tileTypeIndex, const Design& design, const Device& device, CfgExtractor& cfgExtractor);
        void buildPIPControlSetMap(const PIPControlSets& pipControlSets);
        void initPIPStates(size_t pipCount, size_t cfgBitCount);
        void isolatePIPs(CorrelationUnits& correlationUnits);
        void writePIPsToDb(TileTypeCfgDb& tileTypeDb);
        void getCfgBitPositions(BitPositions &bitPositions, const PIPBitValues& pipBitValues) const;
        void getCfgBitValues(PIPBitValues& pipBitValues, const BitPositions &bitPositions) const;

        CorrelationUnits m_tileUnits;
        CorrelationUnits m_pipStates;
        typedef std::map<size_t, const PIPControlSet*> pipControlSetMap_t;
        pipControlSetMap_t m_pipControlSetMap;

        TileIndices m_tileIndices;
        std::vector<boost::uint32_t> m_buffer;

    };

}

#endif
