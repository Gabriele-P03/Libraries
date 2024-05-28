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
                    /**
                     * @param name of the json array
                     * @throw NotFoundException if a so-called json array does not exist
                     * @return the json array named as given param 
                    */
                    JSONArray* getJSONArray(std::string name) const;
                    /**
                     * @param index json array index
                     * @throw IndexOutOfBounds if a index is >= LL json array size
                     * @return the relative json array
                    */
                    JSONArray* getJSONArray(unsigned long index) const;

                    /**
                     * @param name of the json field
                     * @throw NotFoundException if a so-called json field does not exist
                     * @return the json field named as given param 
                    */
                    JSONField* getJSONField(std::string name) const;
                    /**
                     * @param index json field index
                     * @throw IndexOutOfBounds if a index is >= LL json field size
                     * @return the relative json field
                    */
                    JSONField* getJSONField(unsigned long index) const;

                    JSONFieldInt* getJSONFieldInt(std::string name) const;
                    JSONFieldUInt* getJSONFieldUInt(std::string name) const;
                    JSONFieldLong* getJSONFieldLong(std::string name) const;
                    JSONFieldULong* getJSONFieldULong(std::string name) const;
                    JSONFieldFloat* getJSONFieldFloat(std::string name) const;
                    JSONFieldDouble* getJSONFieldDouble(std::string name) const;
                    JSONFieldBool* getJSONFieldBool(std::string name) const;
                    JSONFieldTM* getJSONFieldTM(std::string name) const;
                    JSONFieldString* getJSONFieldString(std::string name) const;

                    unsigned long getJSONObjectSize() const noexcept{return this->jsonObjects.getSize();}
                    unsigned long getJSONOArraySize() const noexcept{return this->jsonArrays.getSize();}
                    unsigned long getJSONFieldSize() const noexcept{return this->fields.getSize();}

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