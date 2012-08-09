/**
* \file PinWireBS.hpp
* \brief Contains binary serialization functions for PinWire class.
*/

#pragma once
#ifndef BIL_PINWIREBS_HPP
#define BIL_PINWIREBS_HPP

#include <istream>
#include <ostream>


namespace bil {

    class PinWire;


    /**
    * \brief Writes data from a PinWire into a binary stream.
    * \param data The PinWire to write.
    * \param outputStream The stream to write into.
    * \throws .
    */
    void writeBinary(const PinWire& data, std::ostream& outputStream);

    /**
    * \brief Reads data into a PinWire from a binary stream.
    * \param data The PinWire to read into.
    * \param inputStream The stream to read from.
    * \throws .
    */
    void readBinary(PinWire& data, std::istream& inputStream);

}

#endif
