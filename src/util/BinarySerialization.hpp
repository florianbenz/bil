/**
* \file BinarySerialization.hpp
* \brief Contains functions for binary stream reading and writing.
*/

#pragma once
#ifndef BIL_BINARYSERIALIZATION_HPP
#define BIL_BINARYSERIALIZATION_HPP

#include <istream>
#include <ostream>
#include <map>
#include <string>
#include <vector>
#include <boost/type_traits/is_pod.hpp>
#include <boost/utility/enable_if.hpp>
#include <exception/IOException.hpp>


namespace bil {

    /**
    * \brief Writes POD data into a binary stream.
    * \tparam T Type of the data.
    * \param data The data to write.
    * \param outputStream The stream to write into.
    * \throws .
    */
    template <typename T> inline
    typename boost::enable_if<boost::is_pod<T>, void>::type
    writeBinary(const T& data, std::ostream& outputStream)
    {
        // write data as one block
        outputStream.write(reinterpret_cast<const char*>(&data), sizeof(T));
        if (!outputStream) throw IOException();
    }

    /**
    * \brief Writes POD data from a std::vector into a binary stream.
    * \tparam T Type of the data inside vector.
    * \param data The vector to write.
    * \param outputStream The stream to write into.
    * \throws .
    */
    template <typename T> inline
    typename boost::enable_if<boost::is_pod<T>, void>::type
    writeBinary(const std::vector<T>& data, std::ostream& outputStream)
    {
        // write vector length
        size_t length = data.size();
        outputStream.write(reinterpret_cast<const char*>(&length), sizeof(length));
        if (!outputStream) throw IOException();
        // write vector data as one block
        if (0 < length)
        {
            outputStream.write(reinterpret_cast<const char*>(&(data[0])), sizeof(T) * length);
            if (!outputStream) throw IOException();
        }
    }

    /**
    * \brief Writes non-POD data from a std::vector into a binary stream.
    * \tparam T Type of the data inside vector.
    * \param data The vector to write.
    * \param outputStream The stream to write into.
    * \throws .
    */
    template <typename T> inline
    typename boost::disable_if<boost::is_pod<T>, void>::type
    writeBinary(const std::vector<T>& data, std::ostream& outputStream)
    {
        // write vector length
        size_t length = data.size();
        outputStream.write(reinterpret_cast<const char*>(&length), sizeof(length));
        if (!outputStream) throw IOException();
        // write vector data one by one
        for (size_t i = 0; i < length; ++i)
            writeBinary(data[i], outputStream);
    }

    /**
    * \brief Writes data from a std::map into a binary stream.
    * \tparam K Type of map keys.
    * \tparam V Type of map values.
    * \param data The map to write.
    * \param outputStream The stream to write into.
    * \throws .
    */
    template <typename K, typename V, typename C, typename A> inline
    void writeBinary(const std::map<K, V, C, A>& data, std::ostream& outputStream)
    {
        // write map entry count
        size_t length = data.size();
        outputStream.write(reinterpret_cast<const char*>(&length), sizeof(length));
        if (!outputStream) throw IOException();
        // write map data one by one
        std::map<K, V, C, A>::const_iterator it = data.begin();
        std::map<K, V, C, A>::const_iterator itEnd = data.end();
        for (; it != itEnd; ++it)
        {
            writeBinary(it->first, outputStream);
            writeBinary(it->second, outputStream);
        }
    }

    /**
    * \brief Writes data from a std::string into a binary stream.
    * \details Strings longer than 255 chars are truncated to that length.
    * \param data The string to write.
    * \param outputStream The stream to write into.
    * \throws .
    */
    void writeBinary(const std::string& data, std::ostream& outputStream);


    /**
    * \brief Reads POD data from a binary stream.
    * \tparam T Type of the data.
    * \param data The data to read into.
    * \param inputStream The stream to read from.
    * \throws .
    */
    template <typename T> inline
    typename boost::enable_if<boost::is_pod<T>, void>::type
    readBinary(T& data, std::istream& inputStream)
    {
        // read data as one block
        inputStream.read(reinterpret_cast<char*>(&data), sizeof(T));
        if (!inputStream) throw IOException();
    }

    /**
    * \brief Reads POD data into a std::vector from a binary stream.
    * \tparam T Type of the data inside vector.
    * \param data The vector to read into.
    * \param inputStream The stream to read from.
    * \throws .
    */
    template <typename T> inline
    typename boost::enable_if<boost::is_pod<T>, void>::type
    readBinary(std::vector<T>& data, std::istream& inputStream)
    {
        // read vector length
        size_t length;
        inputStream.read(reinterpret_cast<char*>(&length), sizeof(length));
        if (!inputStream) throw IOException();
        // read vector data as one block
        data.resize(length);
        if (0 < length)
        {
            inputStream.read(reinterpret_cast<char*>(&(data[0])), sizeof(T) * length);
            if (!inputStream) throw IOException();
        }
    }

    /**
    * \brief Reads non-POD data into a std::vector from a binary stream.
    * \tparam T Type of the data inside vector.
    * \param data The vector to read into.
    * \param inputStream The stream to read from.
    * \throws .
    */
    template <typename T> inline
    typename boost::disable_if<boost::is_pod<T>, void>::type
    readBinary(std::vector<T>& data, std::istream& inputStream)
    {
        // read vector length
        size_t length;
        inputStream.read(reinterpret_cast<char*>(&length), sizeof(length));
        if (!inputStream) throw IOException();
        // write vector data one by one
        data.resize(length);
        for (size_t i = 0; i < length; ++i)
            readBinary(data[i], inputStream);
    }

    /**
    * \brief Reads data into a std::map from a binary stream.
    * \tparam K Type of map keys.
    * \tparam V Type of map values.
    * \param data The map to read into.
    * \param inputStream The stream to read from.
    * \throws .
    */
    template <typename K, typename V, typename C, typename A> inline
    void readBinary(std::map<K, V, C, A>& data, std::istream& inputStream)
    {
        // read map entry count
        size_t length = data.size();
        inputStream.read(reinterpret_cast<char*>(&length), sizeof(length));
        if (!inputStream) throw IOException();
        // read map entries one by one
        data.clear();
        for (size_t i = 0; i < length; ++i)
        {
            // read key
            K key;
            readBinary(key, inputStream);
            // add it to map
            std::pair<std::map<K, V>::iterator, bool> ret =
                data.insert(std::make_pair(key, V()));
            V& value = (ret.first)->second;
            // read value
            readBinary(value, inputStream);
        }
    }

    /**
    * \brief Reads data into a std::string from a binary stream.
    * \param data The string to read into.
    * \param inputStream The stream to read from.
    * \throws .
    */
    void readBinary(std::string& data, std::istream& inputStream);

}

#endif
