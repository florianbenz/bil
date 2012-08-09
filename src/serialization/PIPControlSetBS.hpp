/**
* \file PIPControlSetBS.hpp
* \brief Contains binary serialization functions for PIPControlSet class.
*/

#pragma once
#ifndef BIL_PIPCONTROLSETBS_HPP
#define BIL_PIPCONTROLSETBS_HPP

#include <istream>
#include <ostream>


namespace bil {

    class PIPControlSet;


    /**
    * \brief Writes data from a PIPControlSet into a binary stream.
    * \param data The PIPControlSet to write.
    * \param outputStream The stream to write into.
    * \throws .
    */
    void writeBinary(const PIPControlSet& data, std::ostream& outputStream);

    /**
    * \brief Reads data into a PIPControlSet from a binary stream.
    * \param data The PIPControlSet to read into.
    * \param inputStream The stream to read from.
    * \throws .
    */
    void readBinary(PIPControlSet& data, std::istream& inputStream);

}

#endif
