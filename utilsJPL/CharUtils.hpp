/**
 * There are some static non-member function useful to check some prioprieties about a char of a string
 * 
 * @date 2023-02-11
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef CHAR_UTILS_CYPHER_JPL
#define CHAR_UTILS_CYPHER_JPL


namespace jpl{

    namespace _utils{

        inline bool isUppercaseLetter(char _s){
            return (_s >= ((unsigned int)('A')) && _s <= ((unsigned int)('Z')));
        }

        inline bool isLowercaseLetter(char _s){
            return (_s >= ((unsigned int)('a')) && _s <= ((unsigned int)('z')));
        }

        inline bool isLetter(char _s){
            return isUppercaseLetter(_s) || isLowercaseLetter(_s);
        }

        /**
         * Return the lowercase of the given letter. 
         * If it is not a valid char, returns the given one
         * If _s is already lowercase, returns the given one
         * 
         * @param _s 
         * @return char 
         */
        inline char toLower(char _s){

            if(isLetter(_s)){

                if(isLowercaseLetter(_s))
                    return _s;

                else
                    return _s  + ( (unsigned int)('z') - (unsigned int)('a') );
            }

            return _s;
        }

        /**
         * Return the uppercase of the given letter. 
         * If it is not a valid char, returns the given one
         * If _s is already uppercase, returns the given one
         * 
         * @param _s 
         * @return char 
         */
        inline char toUpper(char _s){

            if(isLetter(_s)){

                if(isUppercaseLetter(_s))
                    return _s;

                else
                    return _s - ( (unsigned int)('z') - (unsigned int)('a') );
            }

            return _s;
        }

    }
}

#endif