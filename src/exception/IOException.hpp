/**
* \file IOException.hpp
* \brief Contains declaration of IOException class.
*/

#pragma once
#ifndef BIL_IOEXCEPTION_HPP
#define BIL_IOEXCEPTION_HPP

#include <exception/Exception.hpp>


namespace bil {

    /**
    * \brief Exception for I/O errors.
    *
    * Exception for indicating I/O errors.
    */
    class IOException: public Exception {
    public:

        /**
        * \brief Creates a new IOException instance.
        */
        IOException() throw();

        /**
        * \brief Creates a new IOException instance.
        * \param what_arg Description string.
        */
        explicit IOException(const std::string& what_arg) throw();

    };

}

#endif
