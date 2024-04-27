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

#include "fields/JSONFieldUInt.hpp"
#include "fields/JSONField.hpp"
#include "fields/JSONFieldInt.hpp"
#include "fields/JSONFieldFloat.hpp"
#include "fields/JSONFieldString.hpp"
#include "fields/JSONFieldTM.hpp"
#include "fields/JSONFieldDouble.hpp"
#include "fields/JSONFieldULong.hpp"
#include "fields/JSONFieldLong.hpp"
#include "fields/JSONFieldBool.hpp"

#include <jpl/utils/structure/list/LinkedList.hpp>
#include <jpl/exception/runtime/IndexOutOfBoundsException.hpp>
#include "exception/JSONKeyNotFoundException.hpp"

namespace jpl{
    namespace _parser{
        namespace _json{

            class JSONArray;

            class JSONObject{
                
                protected:
                    unsigned long intSize, uintSize, longSize, ulongSize, floatSize, doubleSize, boolSize, tmSize, stringSize;

                    unsigned long tabs; //Count how many tabs 
                    std::string name;

                    _utils::_collections::_list::LinkedList<JSONObject*> jsonObjects;   //Children json object
                    _utils::_collections::_list::LinkedList<JSONArray*> jsonArrays;      //Children json array
                    _utils::_collections::_list::LinkedList<JSONField*> fields;         //Children json field

                public:
                    JSONObject(std::string name, unsigned long tabs);
                    JSONObject(std::string name);
                    JSONObject();

                    /**
                     * @param name json object name
                     * @throw NotFoundExceptin if a so-called json object does not exist
                     * @return the object named as name
                    */
                    JSONObject* getJSONObject(std::string name) const;
                    /**
                     * @param index json object index
                     * @throw IndexOutOfBounds if a index is >= LL json object size
                     * @return the relative json object
                    */
                    JSONObject* getJSONObject(unsigned long index) const;

                    JSONArray* getJSONArray(std::string name) const;
                    JSONArray* getJSONArray(unsigned long index) const;

                    JSONField* getJSONField(std::string name) const;
                    JSONField* getJSONField(unsigned long index) const;

                    JSONFieldInt* getJSONFieldInt(std::string name) const;
                    JSONFieldInt* getJSONFieldInt(unsigned long index) const;
                    JSONFieldUInt* getJSONFieldUInt(std::string name) const;
                    JSONFieldUInt* getJSONFieldUInt(unsigned long index) const;
                    JSONFieldLong* getJSONFieldLong(std::string name) const;
                    JSONFieldLong* getJSONFieldLong(unsigned long index) const;
                    JSONFieldULong* getJSONFieldULong(std::string name) const;
                    JSONFieldULong* getJSONFieldULong(unsigned long index) const;
                    JSONFieldFloat* getJSONFieldFloat(std::string name) const;
                    JSONFieldFloat* getJSONFieldFloat(unsigned long index) const;
                    JSONFieldDouble* getJSONFieldDouble(std::string name) const;
                    JSONFieldDouble* getJSONFieldDouble(unsigned long index) const;
                    JSONFieldBool* getJSONFieldBool(std::string name) const;
                    JSONFieldBool* getJSONFieldBool(unsigned long index) const;
                    JSONFieldTM* getJSONFieldTM(std::string name) const;
                    JSONFieldTM* getJSONFieldTM(unsigned long index) const;
                    JSONFieldString* getJSONFieldString(std::string name) const;
                    JSONFieldString* getJSONFieldString(unsigned long index) const;

                    unsigned long getJSONObjectSize() const noexcept{return this->jsonObjects.getSize();}
                    unsigned long getJSONOArraySize() const noexcept{return this->jsonArrays.getSize();}
                    unsigned long getJSONFieldSize() const noexcept{return this->fields.getSize();}
                    unsigned long getJSONFieldIntSize() const noexcept{return this->intSize;}
                    unsigned long getJSONFieldUIntSize() const noexcept{return this->uintSize;}
                    unsigned long getJSONFieldLongSize() const noexcept{return this->longSize;}
                    unsigned long getJSONFieldULongSize() const noexcept{return this->ulongSize;}
                    unsigned long getJSONFieldFloatSize() const noexcept{return this->floatSize;}
                    unsigned long getJSONFieldboolSize() const noexcept{return this->boolSize;}
                    unsigned long getJSONFieldBoolSize() const noexcept{return this->boolSize;}
                    unsigned long getJSONFieldTMSize() const noexcept{return this->tmSize;}
                    unsigned long getJSONFieldStringSize() const noexcept {return this->stringSize;}

                    std::string getName() const noexcept{return this->name;}
                    unsigned long getTabs() const noexcept{return this->tabs;} 

                    void addJSONObject(JSONObject* jsonObject);
                    void addJSONArray(JSONArray* jsonObject);
                    void addJSONField(JSONField* jsonObject);

                    ~JSONObject();
            };
        }
    }
}

#include "JSONArray.hpp"

#endif