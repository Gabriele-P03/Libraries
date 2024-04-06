/**
 * This is a wrapper header file which helps a collection either to print its elements or to generate a string which represents
 * its elements. 
 * Generally you can pass a collection to the std::cout. If T is a pointer, addresses will be printed, else the operator<< will
 * be used; therefore you oughta decleare that type of function, otherwise a compilation-error will occur  
 * 
 * @date 10/09/2023
 * @author Gabriele-P03
*/

#ifndef PRINTABLE_JPL
#define PRINTABLE_JPL

#include <iostream>
#include <sstream>

namespace jpl{

    namespace _utils{

        template <typename T>
        class Printable{

            public:
                static std::ostream& print(std::ostream& os, const T &value){
                    return os<<value<<" ";
                }
                static std::string to_string(const T value){
                    std::ostringstream ss;
                    ss << value;
                    return ss.str();
                }

        };

        template <typename P>
        class Printable<P *>{

            public:
                static std::ostream& print(std::ostream& os, const P * const value){
                    if(value == nullptr)
                        os<<"nullptr ";
                    else
                        os<<value<<" ";
                    return os;
                }

                static std::string to_string(const P* const value){
                    std::ostringstream ss;
                    ss << *value;
                    return ss.str();
                }
        };
    }
}

#endif