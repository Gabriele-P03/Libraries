/**
 * @file CSVParser.hpp
 * 
 * CSV Parser
 * 
 * @author Gabriele-P03
 * @date 27-09-2024
 */

#ifndef CSV_PARSER_JPL
#define CSV_PARSER_JPL

namespace jpl{

    namespace _parser{

        namespace _csv{

            class CSVParser{

                protected:
                    char separator;

                public:

                    /**
                     * Instance a CSVParser with semi-colon as default separator
                     */
                    CSVParser();

                    /**
                     * Instance a CSVParser
                     * 
                     * @param separator - char separator
                     */
                    CSVParser(char separator);


                    
            };
        }
    }
}

#endif