/**
 * This is a wrapper header file which helps a collection to print its element in a best-effort way.
 * 
 * How it print the element is via an implementation of helper class which
 * checks type of T - if it is a pointer or not - and then use the relative print() method
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