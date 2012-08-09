/**
* \file V5BitstreamXMLWriter.hpp
* \brief Contains declaration of V5BitstreamXMLWriter class.
*/

#pragma once
#ifndef BIL_V5BITSTREAMXMLWRITER_HPP
#define BIL_V5BITSTREAMXMLWRITER_HPP

#include <bitstream/V5BitstreamSyntaxChecker.hpp>


namespace bil {

    class Bitstream;
    class XMLWriter;


    /**
    * \brief Writes a Virtex-5 bitstream into XML.
    *
    * Being based on the V5BitstreamSyntaxChecker, V5BitstreamXMLWriter syntax
    * checks the packet sequence and writes every visited packet out to XML
    * using a given XMLWriter.
    */
    class V5BitstreamXMLWriter: public V5BitstreamSyntaxChecker {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Creates a new V5BitstreamXMLWriter instance.
        * \param xmlWriter The XMLWriter instance to be used for writing.
        */
        explicit V5BitstreamXMLWriter(XMLWriter& xmlWriter);


        /**********************************************************************/
        /* VISITING METHODS                                                   */
        /**********************************************************************/

        /**
        * \brief Visits a BuswidthPattern packet.
        * \param buswidthPattern BuswidthPattern instance to be visited.
        * \throws .
        */
        virtual void visit(const BuswidthPattern& buswidthPattern);

        /**
        * \brief Visits a DummyWord packet.
        * \param dummyWord DummyWord instance to be visited.
        * \throws .
        */
        virtual void visit(const DummyWord& dummyWord);

        /**
        * \brief Visits a SyncWord packet.
        * \param syncWord SyncWord instance to be visited.
        * \throws .
        */
        virtual void visit(const SyncWord& syncWord);

        /**
        * \brief Visits a Type1Packet packet.
        * \param type1Packet Type1Packet instance to be visited.
        * \throws .
        */
        virtual void visit(const Type1Packet& type1Packet);

        /**
        * \brief Visits a Type2Packet packet.
        * \param type2Packet Type2Packet instance to be visited.
        * \throws .
        */
        virtual void visit(const Type2Packet& type2Packet);


    protected:

        /**********************************************************************/
        /* XML WRITING                                                        */
        /**********************************************************************/

        /**
        * \brief Writes a BuswidthPattern packet into XML.
        * \param buswidthPattern BuswidthPattern instance to be written.
        * \throws .
        */
        void writePacketTag(const BuswidthPattern& buswidthPattern);

        /**
        * \brief Writes a DummyWord packet into XML.
        * \param dummyWord DummyWord instance to be written.
        * \throws .
        */
        void writePacketTag(const DummyWord& dummyWord);

        /**
        * \brief Writes a SyncWord packet into XML.
        * \param syncWord SyncWord instance to be written.
        * \throws .
        */
        void writePacketTag(const SyncWord& syncWord);

        /**
        * \brief Writes a Type2Packet packet (and its descendants) into XML.
        * \param tagName XML tag to use.
        * \param type2Packet Type2Packet instance to be written.
        * \throws .
        */
        void writePacketTag(const std::string& tagName, const Type2Packet& type2Packet);

        /**
        * \brief Writes packet payload data into XML.
        * \param words Pointer to data words to write.
        * \param wordCount Number of data words to write.
        * \throws .
        */
        void writeData(const boost::uint32_t* words, size_t wordCount);


    private:

        V5BitstreamXMLWriter(const V5BitstreamXMLWriter&);
        V5BitstreamXMLWriter& operator=(const V5BitstreamXMLWriter&);

        XMLWriter& m_xmlWriter;

    };


    /**
    * \brief Writes a Virtex-5 bitstream into XML.
    * \details Convenience functions for using V5BitstreamXMLWriter.
    * \param xmlWriter The XMLWriter instance to be used for writing.
    * \param bs Bitstream to be written.
    * \throws .
    */
    void writeV5BitstreamXML(XMLWriter& xmlWriter, const Bitstream& bs);

}

#endif
