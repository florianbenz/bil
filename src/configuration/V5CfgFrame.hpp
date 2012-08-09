/**
* \file V5CfgFrame.hpp
* \brief Contains declaration of V5CfgFrame class.
*/

#pragma once
#ifndef BIL_V5CFGFRAME_HPP
#define BIL_V5CFGFRAME_HPP

#include <cstring>
#include <boost/cstdint.hpp>


namespace bil {

    /**
    * \brief Holds a configuration frame of a Virtex-5 device.
    *
    * A frame is the smallest unit of configuration data that can be written to
    * configuration memory at once. Its destination is determined by the frame
    * address.
    */
    class V5CfgFrame {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new V5CfgFrame instance.
        */
        V5CfgFrame();


        /**********************************************************************/
        /* MODIFICATORS                                                       */
        /**********************************************************************/

        /**
        * \brief Zero out frame data.
        * \details This is default configuration for unused logic: A completely
        *          unused FPGA will have all frames zeroed out.
        */
        void reset();


        /**********************************************************************/
        /* DATA ACCESS                                                        */
        /**********************************************************************/

        /// Virtex-5 frames are 41 words big.
        static const size_t WORDCOUNT = 41;

        /**
        * \brief Index of the HCLK word in the frame.
        * \details A Virtex-5 frame consists of three parts: 20 lower words, 1
        *          HCLK word, and 20 upper words.
        */
        static const size_t HCLK_WORD_INDEX = 20;

        /**
        * \brief Gets a pointer to the frame data.
        * \return The data pointer.
        */
        boost::uint32_t* data();

        /**
        * \brief Gets a read only pointer to the frame data.
        * \return The data pointer.
        */
        const boost::uint32_t* data() const;


    private:

        boost::uint32_t m_data[WORDCOUNT];

    };

}

#endif
