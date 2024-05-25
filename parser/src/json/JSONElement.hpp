/**
 * A JSONElement is a merker class for JSON Elements (Object, Array and field) which is used as an abstraction 
 * for any function that needs to operate without knowning what type of element it is  
 * 
 * @date 2024-05-25
 * @author Gabriele-P03
*/
#ifndef JSON_ELEMENT_JPL
#define JSON_ELEMENT_JPL

namespace jpl{
    namespace _parser{
        namespace _json{
            class JSONElement{
                
                protected:
                    
                    virtual ~JSONElement() = default;
            };
        }
    }
}

#endif