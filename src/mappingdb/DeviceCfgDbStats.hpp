/**
* \file DeviceCfgDbStats.hpp
* \brief Contains declaration of DeviceCfgDbStats class.
*/

#pragma once
#ifndef BIL_DEVICECFGDBSTATS_HPP
#define BIL_DEVICECFGDBSTATS_HPP

#include <ostream>
#include <mappingdb/DeviceCfgDb.hpp>
#include <xdlrc/model/Device.hpp>


namespace bil {

    /**
    * \brief Prints statistics of a DeviceCfgDb.
    */
    class DeviceCfgDbStats {
    public:

        /**
        * \brief Print out statistics of given data base.
        * \param db The data base.
        * \param device The device the data base is for.
        * \param outStream Stream to use for output.
        */
        void printStats(const DeviceCfgDb& db, const Device& device, std::ostream& outStream);


    private:

        void printTileType(const TileTypeCfgDb& db, const TileType& tileType);
        void printPIPControlSet(const PIPControlSet& cs, size_t csIndex, const Wires& wires, const PIPs& pips);
        void printPIPCounts(size_t indent, size_t total, size_t isolated, size_t zero, size_t notIsolated);

        std::ostream* m_outputStream;

        size_t m_devicePIPCount;
        size_t m_deviceIsolatedPIPCount;
        size_t m_deviceZeroPIPCount;
        size_t m_deviceNotIsolatedPIPCount;

        size_t m_tileTypePIPCount;
        size_t m_tileTypeIsolatedPIPCount;
        size_t m_tileTypeZeroPIPCount;
        size_t m_tileTypeNotIsolatedPIPCount;

    };

}

#endif
