/**
 * Json Object abstraction
 * 
 *
 * @file JSONObject.hpp
 * @author Gabriele-P03
 */

#ifndef JSON_OBJECT_JPL
#define JSON_OBJECT_JPL

#include <string>
#include <variant>

#include "fields/JSONFieldUInt.hpp"
#include "fields/JSONField.hpp"
#include "fields/JSONFieldInt.hpp"
#include "fields/JSONFieldFloat.hpp"
#include "fields/JSONFieldString.hpp"
#include "fields/JSONFieldTM.hpp"
#include "fields/JSONFieldbool.hpp"
#include "fields/JSONFieldULong.hpp"
#include "fields/JSONFieldLong.hpp"
#include "fields/JSONFieldBool.hpp"

#include <jpl/utils/structure/list/LinkedList.hpp>

namespace jpl{
    namespace _parser{
        namespace _json{

            class JSONArray;

            class JSONObject{
                
                protected:
                    unsigned long intSize, uintSize, longSize, ulongSize, floatSize, boolSize, boolSize, tmSize, stringSize;

                    unsigned long tabs; //Count how many tabs 
                    std::string name;

                    _utils::_collections::_list::LinkedList<JSONObject*> jsonObjects;   //Children json object
                    _utils::_collections::_list::LinkedList<JSONArray*> jsonArray;      //Children json array
                    _utils::_collections::_list::LinkedList<JSONField*> fields;         //Children json field

                public:
                    JSONObject(std::string name, unsigned long tabs);
                    JSONObject(std::string name);
                    JSONObject();

                    JSONObject* getJsonObject(std::string name) const;
                    JSONObject* getJsonObject(unsigned long index) const;

                    JSONArray* getJsonArray(std::string name) const;
                    JSONArray* getJsonArray(unsigned long index) const;


                    virtual JSONField* getJsonField(std::string name) const;
                    virtual JSONField* getJsonField(unsigned long index) const;

                    virtual JSONFieldInt* getJSONFieldInt(std::string name) const;
                    virtual JSONFieldInt* getJSONFieldInt(unsigned long index) const;
                    virtual JSONFieldUInt* getJSONFieldUInt(std::string name) const;
                    virtual JSONFieldUInt* getJSONFieldUInt(unsigned long index) const;
                    virtual JSONFieldLong* getJSONFieldLong(std::string name) const;
                    virtual JSONFieldLong* getJSONFieldLong(unsigned long index) const;
                    virtual JSONFieldULong* getJSONFieldULong(std::string name) const;
                    virtual JSONFieldULong* getJSONFieldULong(unsigned long index) const;
                    virtual JSONFieldFloat* getJSONFieldFloat(std::string name) const;
                    virtual JSONFieldFloat* getJSONFieldFloat(unsigned long index) const;
                    virtual JSONFieldbool* getJSONFieldbool(std::string name) const;
                    virtual JSONFieldbool* getJSONFieldbool(unsigned long index) const;
                    virtual JSONFieldBool* getJSONFieldBool(std::string name) const;
                    virtual JSONFieldBool* getJSONFieldBool(unsigned long index) const;
                    virtual JSONFieldTM* getJSONFieldTM(std::string name) const;
                    virtual JSONFieldTM* getJSONFieldTM(unsigned long index) const;
                    virtual JSONFieldString* getJSONFieldString(std::string name) const;
                    virtual JSONFieldString* getJSONFieldString(unsigned long index) const;

                    virtual unsigned long getJSONObjectSize() const noexcept{return this->jsonObjects.getSize();}
                    virtual unsigned long getJSONOArraySize() const noexcept{return this->jsonArray.getSize();}
                    virtual unsigned long getJSONFieldSize() const noexcept{return this->fields.getSize();}
                    virtual unsigned long getJSONFieldIntSize() const noexcept{return this->intSize;}
                    virtual unsigned long getJSONFieldUIntSize() const noexcept{return this->uintSize;}
                    virtual unsigned long getJSONFieldLongSize() const noexcept{return this->longSize;}
                    virtual unsigned long getJSONFieldULongSize() const noexcept{return this->ulongSize;}
                    virtual unsigned long getJSONFieldFloatSize() const noexcept{return this->floatSize;}
                    virtual unsigned long getJSONFieldboolSize() const noexcept{return this->boolSize;}
                    virtual unsigned long getJSONFieldBoolSize() const noexcept{return this->boolSize;}
                    virtual unsigned long getJSONFieldTMSize() const noexcept{return this->tmSize;}
                    virtual unsigned long getJSONFieldStringSize() const noexcept {return this->stringSize;}

                    ~JSONObject();
            };
        }
    }
}

#endif