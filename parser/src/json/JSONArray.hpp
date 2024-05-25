/**
 * Json Array abstraction
 * 
 *
 * @file JSONObject.hpp
 * @author Gabriele-P03
 */

#ifndef JSON_ARRAY_JPL
#define JSON_ARRAY_JPL

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

#include "JSONElement.hpp"

namespace jpl{
    namespace _parser{
        namespace _json{

            class JSONObject;

            class JSONArray : public JSONElement{
                
                protected:
                    
                    unsigned long intSize, uintSize, longSize, ulongSize, floatSize, doubleSize, boolSize, tmSize, stringSize;

                    unsigned long tabs; //Count how many tabs. They will be used for indentation 
                    std::string name;

                    _utils::_collections::_list::LinkedList<JSONObject*> jsonObjects;   //Children json object
                    _utils::_collections::_list::LinkedList<JSONArray*> jsonArrays;      //Children json array
                    _utils::_collections::_list::LinkedList<JSONField*> fields;         //Children json field

                public:
                    JSONArray(std::string name, unsigned long tabs);
                    JSONArray(std::string name);
                    JSONArray();

                    /**
                     * @param index json object index
                     * @throw IndexOutOfBounds if a index is >= LL json object size
                     * @return the relative json object
                    */
                    JSONObject* getJSONObject(unsigned long index) const;
                    JSONArray* getJSONArray(unsigned long index) const;


                    JSONField* getJSONField(unsigned long index) const;

                    JSONFieldInt* getJSONFieldInt(unsigned long index) const;
                    JSONFieldUInt* getJSONFieldUInt(unsigned long index) const;
                    JSONFieldLong* getJSONFieldLong(unsigned long index) const;
                    JSONFieldULong* getJSONFieldULong(unsigned long index) const;
                    JSONFieldFloat* getJSONFieldFloat(unsigned long index) const;
                    JSONFieldDouble* getJSONFieldDouble(unsigned long index) const;
                    JSONFieldBool* getJSONFieldBool(unsigned long index) const;
                    JSONFieldTM* getJSONFieldTM(unsigned long index) const;
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
                    void setName(std::string name) noexcept{this->name = name;}
                    unsigned long getTabs() const noexcept{return this->tabs;} 

                    void addJSONObject(JSONObject* jsonObject);
                    void addJSONArray(JSONArray* jsonObject);
                    void addJSONField(JSONField* jsonObject);

                    std::string toString() const noexcept;

                    ~JSONArray();
            };
        }
    }
}

#include "JSONObject.hpp"

#endif