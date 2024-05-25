#include "JSONArray.hpp"

jpl::_parser::_json::JSONArray::JSONArray(std::string name, unsigned long tabs){
    this->name = name;
    this->tabs = tabs;
} 
jpl::_parser::_json::JSONArray::JSONArray(std::string name) : jpl::_parser::_json::JSONArray(name, 0){} 
jpl::_parser::_json::JSONArray::JSONArray() : jpl::_parser::_json::JSONArray(""){}

jpl::_parser::_json::JSONArray::~JSONArray(){
    this->fields.clear();
    this->jsonArrays.clear();
    this->jsonObjects.clear();
}

jpl::_parser::_json::JSONObject* jpl::_parser::_json::JSONArray::getJSONObject(unsigned long index) const{
    if(index >= this->jsonObjects.getSize())
        throw new jpl::_exception::IndexOutOfBoundsException(this->jsonObjects.getSize(), index);
    return this->jsonObjects.get(index);
}

jpl::_parser::_json::JSONArray* jpl::_parser::_json::JSONArray::getJSONArray(unsigned long index) const{
    if(index >= this->jsonArrays.getSize())
        throw new jpl::_exception::IndexOutOfBoundsException(this->jsonArrays.getSize(), index);
    return this->jsonArrays.get(index);
}

/**
 * --------------------------------------- JSON Fields ---------------------------------------
*/

jpl::_parser::_json::JSONField* jpl::_parser::_json::JSONArray::getJSONField(unsigned long index) const{
    if(index >= this->fields.getSize())
        throw new jpl::_exception::IndexOutOfBoundsException(this->fields.getSize(), index);
    return this->fields.get(index);
}

//  --------------------------------------- JSON Fields Int ---------------------------------------

jpl::_parser::_json::JSONFieldInt* jpl::_parser::_json::JSONArray::getJSONFieldInt(unsigned long index) const{
    if(index >= this->intSize)
        throw new jpl::_exception::IndexOutOfBoundsException(this->fields.getSize(), index);
    size_t c = 0;
    for(size_t i = 0; i < this->fields.getSize(); i++){
        jpl::_parser::_json::JSONField* cr = this->fields.get(i);
        if( typeid(cr) == typeid(jpl::_parser::_json::JSONFieldInt) ){
            if(c++ == index)
                return static_cast<jpl::_parser::_json::JSONFieldInt*>(cr);
        }
    }  
    throw new jpl::_exception::RuntimeException("Altough index is into the range, there's no valid json field. This is a JPL bug, please report...");
}

//  --------------------------------------- JSON Fields UInt ---------------------------------------

jpl::_parser::_json::JSONFieldUInt* jpl::_parser::_json::JSONArray::getJSONFieldUInt(unsigned long index) const{
    if(index >= this->uintSize)
        throw new jpl::_exception::IndexOutOfBoundsException(this->fields.getSize(), index);
    size_t c = 0;
    for(size_t i = 0; i < this->fields.getSize(); i++){
        jpl::_parser::_json::JSONField* cr = this->fields.get(i);
        if( typeid(cr) == typeid(jpl::_parser::_json::JSONFieldUInt) ){
            if(c++ == index)
                return static_cast<jpl::_parser::_json::JSONFieldUInt*>(cr);
        }
    }  
    throw new jpl::_exception::RuntimeException("Altough index is into the range, there's no valid json field. This is a JPL bug, please report...");
}

//  --------------------------------------- JSON Fields Long ---------------------------------------

jpl::_parser::_json::JSONFieldLong* jpl::_parser::_json::JSONArray::getJSONFieldLong(unsigned long index) const{
    if(index >= this->longSize)
        throw new jpl::_exception::IndexOutOfBoundsException(this->fields.getSize(), index);
    size_t c = 0;
    for(size_t i = 0; i < this->fields.getSize(); i++){
        jpl::_parser::_json::JSONField* cr = this->fields.get(i);
        if( typeid(cr) == typeid(jpl::_parser::_json::JSONFieldLong) ){
            if(c++ == index)
                return static_cast<jpl::_parser::_json::JSONFieldLong*>(cr);
        }
    }  
    throw new jpl::_exception::RuntimeException("Altough index is into the range, there's no valid json field. This is a JPL bug, please report...");
}

//  --------------------------------------- JSON Fields ULong ---------------------------------------

jpl::_parser::_json::JSONFieldULong* jpl::_parser::_json::JSONArray::getJSONFieldULong(unsigned long index) const{
    if(index >= this->ulongSize)
        throw new jpl::_exception::IndexOutOfBoundsException(this->fields.getSize(), index);
    size_t c = 0;
    for(size_t i = 0; i < this->fields.getSize(); i++){
        jpl::_parser::_json::JSONField* cr = this->fields.get(i);
        if( typeid(cr) == typeid(jpl::_parser::_json::JSONFieldULong) ){
            if(c++ == index)
                return static_cast<jpl::_parser::_json::JSONFieldULong*>(cr);
        }
    }  
    throw new jpl::_exception::RuntimeException("Altough index is into the range, there's no valid json field. This is a JPL bug, please report...");
}


//  --------------------------------------- JSON Fields Float ---------------------------------------

jpl::_parser::_json::JSONFieldFloat* jpl::_parser::_json::JSONArray::getJSONFieldFloat(unsigned long index) const{
    if(index >= this->floatSize)
        throw new jpl::_exception::IndexOutOfBoundsException(this->fields.getSize(), index);
    size_t c = 0;
    for(size_t i = 0; i < this->fields.getSize(); i++){
        jpl::_parser::_json::JSONField* cr = this->fields.get(i);
        if( typeid(cr) == typeid(jpl::_parser::_json::JSONFieldFloat) ){
            if(c++ == index)
                return static_cast<jpl::_parser::_json::JSONFieldFloat*>(cr);
        }
    }  
    throw new jpl::_exception::RuntimeException("Altough index is into the range, there's no valid json field. This is a JPL bug, please report...");
}


//  --------------------------------------- JSON Fields Double ---------------------------------------

jpl::_parser::_json::JSONFieldDouble* jpl::_parser::_json::JSONArray::getJSONFieldDouble(unsigned long index) const{
    if(index >= this->doubleSize)
        throw new jpl::_exception::IndexOutOfBoundsException(this->fields.getSize(), index);
    size_t c = 0;
    for(size_t i = 0; i < this->fields.getSize(); i++){
        jpl::_parser::_json::JSONField* cr = this->fields.get(i);
        if( typeid(cr) == typeid(jpl::_parser::_json::JSONFieldDouble) ){
            if(c++ == index)
                return static_cast<jpl::_parser::_json::JSONFieldDouble*>(cr);
        }
    }  
    throw new jpl::_exception::RuntimeException("Altough index is into the range, there's no valid json field. This is a JPL bug, please report...");
}


//  --------------------------------------- JSON Fields Bool ---------------------------------------

jpl::_parser::_json::JSONFieldBool* jpl::_parser::_json::JSONArray::getJSONFieldBool(unsigned long index) const{
    if(index >= this->boolSize)
        throw new jpl::_exception::IndexOutOfBoundsException(this->fields.getSize(), index);
    size_t c = 0;
    for(size_t i = 0; i < this->fields.getSize(); i++){
        jpl::_parser::_json::JSONField* cr = this->fields.get(i);
        if( typeid(cr) == typeid(jpl::_parser::_json::JSONFieldBool) ){
            if(c++ == index)
                return static_cast<jpl::_parser::_json::JSONFieldBool*>(cr);
        }
    }  
    throw new jpl::_exception::RuntimeException("Altough index is into the range, there's no valid json field. This is a JPL bug, please report...");
}


//  --------------------------------------- JSON Fields TM ---------------------------------------

jpl::_parser::_json::JSONFieldTM* jpl::_parser::_json::JSONArray::getJSONFieldTM(unsigned long index) const{
    if(index >= this->tmSize)
        throw new jpl::_exception::IndexOutOfBoundsException(this->fields.getSize(), index);
    size_t c = 0;
    for(size_t i = 0; i < this->fields.getSize(); i++){
        jpl::_parser::_json::JSONField* cr = this->fields.get(i);
        if( typeid(cr) == typeid(jpl::_parser::_json::JSONFieldTM) ){
            if(c++ == index)
                return static_cast<jpl::_parser::_json::JSONFieldTM*>(cr);
        }
    }  
    throw new jpl::_exception::RuntimeException("Altough index is into the range, there's no valid json field. This is a JPL bug, please report...");
}


//  --------------------------------------- JSON Fields String ---------------------------------------

jpl::_parser::_json::JSONFieldString* jpl::_parser::_json::JSONArray::getJSONFieldString(unsigned long index) const{
    if(index >= this->stringSize)
        throw new jpl::_exception::IndexOutOfBoundsException(this->fields.getSize(), index);
    size_t c = 0;
    for(size_t i = 0; i < this->fields.getSize(); i++){
        jpl::_parser::_json::JSONField* cr = this->fields.get(i);
        if( typeid(cr) == typeid(jpl::_parser::_json::JSONFieldString) ){
            if(c++ == index)
                return static_cast<jpl::_parser::_json::JSONFieldString*>(cr);
        }
    }  
    throw new jpl::_exception::RuntimeException("Altough index is into the range, there's no valid json field. This is a JPL bug, please report...");
}


void jpl::_parser::_json::JSONArray::addJSONObject(JSONObject* jsonObject){
    if(jsonObject == nullptr)
        throw new jpl::_exception::IllegalArgumentException("You cannot add null json object");
    this->jsonObjects.add(jsonObject);
}
void jpl::_parser::_json::JSONArray::addJSONArray(JSONArray* jsonArray){
    if(jsonArray == nullptr)
        throw new jpl::_exception::IllegalArgumentException("You cannot add null json array");
    this->jsonArrays.add(jsonArray);
}
void jpl::_parser::_json::JSONArray::addJSONField(JSONField* field){
    if(field == nullptr)
        throw new jpl::_exception::IllegalArgumentException("You cannot add null json field");
    this->fields.add(field);
}

std::string jpl::_parser::_json::JSONArray::toString() const noexcept{
    std::string buffer = std::string(this->tabs, '\t');
    if(!this->name.empty()){
        buffer += "\"" + this->name + "\":";
    }
    buffer += "{\n";
    size_t objSize = this->jsonObjects.getSize(), arrSize = this->jsonArrays.getSize(), fldSize = this->fields.getSize();
    for(size_t i = 0; i < objSize; i++){
        buffer += this->jsonObjects.get(i)->toString();
        buffer += (i < objSize-1 ? ",\n" : "\n");
    }
    for(size_t i = 0; i < arrSize; i++){
        buffer += this->jsonArrays.get(i)->toString();
        buffer += (i < arrSize-1 ? ",\n" : "\n");
    }
    for(size_t i = 0; i < fldSize; i++){
        buffer += this->fields.get(i)->toString();
        buffer += (i < fldSize-1 ? ",\n" : "\n");
    }
    buffer += std::string(this->tabs, '\t') + "}";
    return buffer;
}