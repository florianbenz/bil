/**
* \file XDLExtractor.hpp
* \brief Contains declaration of XDLExtractor class.
*/

#pragma once
#ifndef BIL_XDLEXTRACTOR_HPP
#define BIL_XDLEXTRACTOR_HPP

#include <cstring>
#include <map>
#include <vector>
#include <correlation/CorrelationUnit.hpp>


namespace bil {

    class Design;
    class Device;


    /// A list with tile indices
    typedef std::vector<size_t> TileIndices;


    /**
    * \brief Extracts a list of correlation units from a XDL design.
    *
    * This class collects used tiles of a given type in a XDL Design, and fills
    * a list of correlation units with their data (active PIPs).
    *
    * Todo: Should also add the state of the primitive sites' configuration
    * options to the correlation units.
    */
    class XDLExtractor {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a XDLExtractor instance.
        * \param design The design from which to extract.
        * \param device The device the design is for.
        */
        XDLExtractor(const Design& design, const Device& device);


        /**********************************************************************/
        /* DATA EXTRACTION                                                    */
        /**********************************************************************/

        /**
        * \brief Extracts a list of correlation units.
        * \param units The correlation unit list to be filled.
        * \param tileIndices Tile indices of the correlation units.
        * \param tileTypeIndex Tile type index of tiles to collect.
        */
        void getTileTypeUnits(CorrelationUnits& units, TileIndices& tileIndices, size_t tileTypeIndex);


    private:

        CorrelationUnit& addCorrelationUnit(size_t tileIndex);

        const Design* m_design;
        const Device* m_device;

        size_t m_pipCount;
        typedef std::map<size_t, CorrelationUnit> tileUnitMap_t;
        tileUnitMap_t m_tileUnitMap;

    };

}

#endif
