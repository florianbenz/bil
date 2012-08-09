/**
* \file DeviceCfgDbFiller.hpp
* \brief Contains declaration of DeviceCfgDbFiller class.
*/

#pragma once
#ifndef BIL_DEVICECFGDBFILLER_HPP
#define BIL_DEVICECFGDBFILLER_HPP

#include <map>
#include <mappingdb/DeviceCfgDb.hpp>


namespace bil {

    class Device;
    class TileType;


    /**
    * \brief Fills a DeviceCfgDb with initial data.
    *
    * This class fills a DeviceCfgDb with initial data gathered from a Device
    * instance. It can not fill all data, the information about configuration
    * bit positions is left empty.
    */
    class DeviceCfgDbFiller {
    public:

        /**********************************************************************/
        /* DATABASE FILLING                                                   */
        /**********************************************************************/

        /**
        * \brief Fills a complete database with initial data.
        * \param deviceDb The database to fill.
        * \param device The device to get data from.
        */
        void initDeviceDb(DeviceCfgDb& deviceDb, const Device& device);

        /**
        * \brief Fills a tile type database with initial data.
        * \param tileTypeDb The database to fill.
        * \param tileType The tile type to get data from.
        * \param tileTypeIndex The index of tile type (in Device).
        */
        void initTileTypeDb(TileTypeCfgDb& tileTypeDb, const TileType& tileType, size_t tileTypeIndex);


    private:

        PIPControlSet& addPIPControlSet(size_t endWireIndex);
        void collapsePIPControlSets();


        PIPControlSets* m_pipControlSets;
        typedef std::map<size_t, size_t> pipControlSetMap_t;
        pipControlSetMap_t m_pipControlSetMap;

    };

}

#endif
