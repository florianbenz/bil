/**
* \file CommandLineException.hpp
* \brief Contains declaration of CommandLineException class.
*/

#pragma once
#ifndef BIL_COMMANDLINEEXCEPTION_HPP
#define BIL_COMMANDLINEEXCEPTION_HPP

#include <exception/Exception.hpp>


namespace bil {

    /**
    * \brief Exception for command line errors.
    *
    * All programs in bil use this class to indicate errors in command line.
    */
    class CommandLineException: public Exception {
    public:

        /**
        * \brief Creates a new CommandLineException instance.
        */
        CommandLineException() throw();

        /**
        * \brief Creates a new CommandLineException instance.
        * \param what_arg Description string.
        */
        explicit CommandLineException(const std::string& what_arg) throw();

    };

}

#endif
