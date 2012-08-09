/**
* \file CfgDecoder.hpp
* \brief Contains declaration of CfgDecoder class.
*/

#pragma once
#ifndef BIL_CFGDECODER_HPP
#define BIL_CFGDECODER_HPP

#include <correlation/cfgextraction/CfgExtractor.hpp>
#include <mappingdb/DeviceCfgDb.hpp>
#include <xdl/model/PIPRef.hpp>
#include <xdlrc/model/Device.hpp>


namespace bil {

    /**
    * \brief Decodes configuration data by using a configuration data base.
    *
    * This class will decode binary configuration data to lists of active PIPs
    * and configurated primitive sites. For this task it needs a configuration
    * data base for the device the data is for, and a description of the device.
    */
    class CfgDecoder {
    public:

        /**********************************************************************/
        /* DECODING                                                           */
        /**********************************************************************/

        /**
        * \brief Decodes configuration data.
        * \param extractor The extractor object to get configuration data.
        * \param db The configuration data base.
        * \param device The device the configuration is for.
        * \throw .
        */
        void decode(CfgExtractor& extractor, const DeviceCfgDb& db, const Device& device);


        /**********************************************************************/
        /* DECODING RESULT LISTS                                              */
        /**********************************************************************/

        /**
        * \brief Gets PIP result list.
        * \return The PIP list.
        */
        const PIPRefs& pipRefs() const;

        /**
        * \todo Result lits with configurated primitive sites.
        */

    private:

        void decodeTileType(CfgExtractor& extractor, const TileTypeCfgDb& tileTypeDb, const Tiles& tiles);
        void decodeTilePIPs(const PIPControlSets& pipControlSets, size_t tileIndex);

        PIPRefs m_pipRefs;
        std::vector<boost::uint32_t> m_buffer;

    };

}

#endif
