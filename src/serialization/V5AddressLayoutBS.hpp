/**
* \file V5AddressLayoutBS.hpp
* \brief Contains binary serialization functions for V5AddressLayout class.
*/

#pragma once
#ifndef BIL_V5ADDRESSLAYOUTBS_HPP
#define BIL_V5ADDRESSLAYOUTBS_HPP

#include <istream>
#include <ostream>


namespace bil {

    class V5AddressLayout;


    /**
    * \brief Writes data from a V5AddressLayout into a binary stream.
    * \param data The V5AddressLayout to write.
    * \param outputStream The stream to write into.
    * \throws .
    */
    void writeBinary(const V5AddressLayout& data, std::ostream& outputStream);

    /**
    * \brief Reads data into a V5AddressLayout from a binary stream.
    * \param data The V5AddressLayout to read into.
    * \param inputStream The stream to read from.
    * \throws .
    */
    void readBinary(V5AddressLayout& data, std::istream& inputStream);

}

#endif
