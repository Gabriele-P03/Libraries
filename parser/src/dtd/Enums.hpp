/**
 * @file
 * 
 * DTD Enums Utils
 * 
 * @author Gabriele-P03 
 */

#ifndef ENUMS_DTD_JPL
#define ENUMS_DTD_JPL

namespace jpl{
    namespace _parser{
        namespace _dtd{

            constexpr const char* const PCDATA = "PCDATA";
            constexpr const char* const PCDATA_TAG = "#PCDATA";
            
            //Presence Operator (, or |)
            enum PRS_OP{
                SEQ,    //Sequence represented by comma
                CHS     //Choises represented by pipe
            };

            //Occurrence Operator (?,+,*)
            enum OCC_OP{
                SINGLE,     // ZERO OR ONE, represented by question mark 
                LEAST,      //AT LEAST ONE, represented by sum
                ANY,         //ZERO OR MORE, represented by asterisk
                MANDATORY   //Only one mandatory
            };

            constexpr const char* const ANY_TAG = "ANY";
            constexpr const char* const EMPTY_TAG = "EMPTY";
            enum TYPE_LIST{
                ANYTHING,        //The element can contain anything
                EMPTY,      //The element must be empty
                CHILDREN,   //The elemet has a defined list of available element in a certain order
                MIXED       //The element can contain text and children elements in any order
            };
            
            constexpr const char* const ID_TAG = "ID" ;

            enum ATTR_TYPE{
                CDATA,          //Text value 
                LIST_CHOICE,     //It is a list of element 
                ID              //Unique ID in the document
            };

            constexpr const char* const REQ_VALUE_ATTR_TAG = "#REQUIRED";
            constexpr const char* const IMP_VALUE_ATTR_TAG = "#IMPLIED";
            constexpr const char* const FIX_VALUE_ATTR_TAG = "#FIXED";
            enum ATTR_VALUE{
                DEFAULT,        //The attribute has a default value (to use in case of null), which can be even a LIST_CHOICE
                REQUIRED,       //The attribute is not null
                IMPLIED,        //The attribute is nullable
                FIXED           //The attribute has a certain fixed value
            };

            constexpr const char* const DOCTYPE = "DOCTYPE";
            constexpr const char* const DOCTYPE_TAG = "<!DOCTYPE ";
            constexpr const char* const ELEMENT = "ELEMENT";
            constexpr const char* const ELEMENT_TAG = "<!ELEMENT ";
            constexpr const char* const ATTLIST = "ATTLIST";
            constexpr const char* const ATTLIST_TAG = "<!ATTLIST ";
            constexpr const char* const ENTITY = "ENTITY";
            constexpr const char* const ENTITY_TAG = "<!ENTITY ";

            constexpr const char* const SYSTEM_TAG = "SYSTEM ";
        }
    }
}

#endif