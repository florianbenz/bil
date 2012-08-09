/**
* \file BitFileData.hpp
* \brief Contains declaration of BitFileData class.
*/

#pragma once
#ifndef BIL_BITFILEDATA_HPP
#define BIL_BITFILEDATA_HPP

#include <cstring>
#include <string>
#include <vector>
#include <boost/cstdint.hpp>


namespace bil {

    /**
    * \brief Models the contents of a Xilinx bit file.
    *
    * It contains meta data (e.g. target device name, creation date, etc.), and
    * the raw bitstream. Note that it does not check the meta data and the raw
    * bitstream contents, it is only a container.
    */
    class BitFileData {
    public:

        /**********************************************************************/
        /* META DATA INTERFACE                                                */
        /**********************************************************************/

        /**
        * \brief Gets name of bitstream source file.
        * \return Reference to source file name string.
        */
        std::string& sourceFileName();

        /**
        * \brief Gets read only name of bitstream source file.
        * \return Reference to source file name string.
        */
        const std::string& sourceFileName() const;


        /**
        * \brief Gets name of bitstream target device.
        * \return Reference to target device name string.
        */
        std::string& targetDeviceName();

        /**
        * \brief Gets read only name of bitstream target device.
        * \return Reference to target device name string.
        */
        const std::string& targetDeviceName() const;


        /**
        * \brief Gets bitstream creation date.
        * \return Reference to creation date string.
        */
        std::string& creationDate();

        /**
        * \brief Gets read only bitstream creation date.
        * \return Reference to creation date string.
        */
        const std::string& creationDate() const;


        /**
        * \brief Gets bitstream creation time.
        * \return Reference to creation time string.
        */
        std::string& creationTime();

        /**
        * \brief Gets read only bitstream creation time.
        * \return Reference to creation time string.
        */
        const std::string& creationTime() const;


        /**********************************************************************/
        /* RAW BITSTREAM INTERFACE                                            */
        /**********************************************************************/

        /**
        * \brief Sets number of 32 bit words the raw bitstream contains.
        * \param count New count to set.
        */
        void bitstreamWordCount(size_t count);

        /**
        * \brief Gets number of 32 bit words the raw bitstream contains.
        * \return Number of words.
        */
        size_t bitstreamWordCount() const;

        /**
        * \brief Gets a pointer to the raw bitstream data.
        * \return Pointer to bitstream raw data, if bitstreamWordCount() > 0;
        *         otherwise 0.
        */
        boost::uint32_t* bitstreamWords();

        /**
        * \brief Gets a read only pointer to the raw bitstream data.
        * \return Pointer to bitstream raw data, if bitstreamWordCount() > 0;
        *         otherwise 0.
        */
        const boost::uint32_t* bitstreamWords() const;


        /**********************************************************************/
        /* MODIFIERS                                                          */
        /**********************************************************************/

        /**
        * \brief Clears all data.
        */
        void clear();


    private:

        std::string m_sourceFileName;
        std::string m_targetDeviceName;
        std::string m_creationDate;
        std::string m_creationTime;

        std::vector<boost::uint32_t> m_bitstream;

    };

}

#endif
