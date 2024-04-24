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
#include "JSONField.hpp"
#include <jpl/utils/structure/list/LinkedList.hpp>

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
                    _utils::_collections::_list::LinkedList<JSONArray*> jsonArray;      //Children json array
                    _utils::_collections::_list::LinkedList<AbstractJSONField> fields;         //Children json field

                public:
                    JSONObject(std::string name, unsigned long tabs);
                    JSONObject(std::string name);
                    JSONObject();

                    JSONObject* getJsonObject(std::string name) const;
                    JSONObject* getJsonObject(unsigned long index) const;

                    JSONArray* getJsonArray(std::string name) const;
                    JSONArray* getJsonArray(unsigned long index) const;


                    virtual AbstractJSONField* getJsonField(std::string name) const;
                    virtual AbstractJSONField* getJsonField(unsigned long index) const;

                    virtual JSONField<int> getJSONFieldInt(std::string name) const;
                    virtual JSONField<int> getJSONFieldInt(unsigned long index) const;
                    virtual JSONField<unsigned int>getJSONFieldUInt(std::string name) const;
                    virtual JSONField<unsigned int>getJSONFieldUInt(unsigned long index) const;
                    virtual JSONField<long> getJSONFieldLong(std::string name) const;
                    virtual JSONField<long> getJSONFieldLong(unsigned long index) const;
                    virtual JSONField<unsigned long> getJSONFieldULong(std::string name) const;
                    virtual JSONField<unsigned long> getJSONFieldULong(unsigned long index) const;
                    virtual JSONField<float> getJSONFieldFloat(std::string name) const;
                    virtual JSONField<float> getJSONFieldFloat(unsigned long index) const;
                    virtual JSONField<double> getJSONFieldDouble(std::string name) const;
                    virtual JSONField<double> getJSONFieldDouble(unsigned long index) const;
                    virtual JSONField<bool> getJSONFieldBool(std::string name) const;
                    virtual JSONField<bool> getJSONFieldBool(unsigned long index) const;
                    virtual JSONField<std::tm> getJSONFieldTM(std::string name) const;
                    virtual JSONField<std::tm> getJSONFieldTM(unsigned long index) const;
                    virtual JSONField<std::string> getJSONFieldString(std::string name) const;
                    virtual JSONField<std::string> getJSONFieldString(unsigned long index) const;

                    virtual unsigned long getJSONObjectSize() const noexcept{return this->jsonObjects.getSize();}
                    virtual unsigned long getJSONOArraySize() const noexcept{return this->jsonArray.getSize();}
                    virtual unsigned long getJSONFieldSize() const noexcept{return this->fields.getSize();}
                    virtual unsigned long getJSONFieldIntSize() const noexcept{return this->intSize;}
                    virtual unsigned long getJSONFieldUIntSize() const noexcept{return this->uintSize;}
                    virtual unsigned long getJSONFieldLongSize() const noexcept{return this->longSize;}
                    virtual unsigned long getJSONFieldULongSize() const noexcept{return this->ulongSize;}
                    virtual unsigned long getJSONFieldFloatSize() const noexcept{return this->floatSize;}
                    virtual unsigned long getJSONFieldDoubleSize() const noexcept{return this->doubleSize;}
                    virtual unsigned long getJSONFieldBoolSize() const noexcept{return this->boolSize;}
                    virtual unsigned long getJSONFieldTMSize() const noexcept{return this->tmSize;}
                    virtual unsigned long getJSONFieldStringSize() const noexcept {return this->stringSize;}

                    ~JSONObject();
            };
        }
    }
}

#endif