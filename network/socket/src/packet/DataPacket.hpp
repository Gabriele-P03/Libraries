/**
 * A data packet is made up after two called to the recv function.
 * The first call reads 4 bytes which will be converted into an unsigned integer, it will be the size of the packet incoming.
 * 
 * The size returned by the first call counts also the eventual flags; the size_data field does not count them, then it will be set as
 * size_returned_by_first_call - OFFSET_FLAG_SIZE_JPL. But when you converts you object into a const char*, it will be long as counting flags, too.
 * 
 * 
 * ABOUT STANDARD FLAGS:
 * 
 * This data packet already has a standard byte of flag:
 *      1) root: if the client is sending a request as a root user (its permission will be checked)
 *      2) echo: ping packet to server (a response packet is supplied by the client)
 *      3) join: user is trying to join the server. If it is allowed, a packet with its stuff will be sent, otherwise an error-message
 *      4) quit: user is leaving the server. All client's stuff will be saved into disk
 * 
 * A normal data packet has all bits equals 0.
 * 
 * There are some rules checked about a packet:
 *      1) quit flag and join one cannot be true both at the same time
 *      2) echo flag must be alone
 * 
 * Since a boolean occupied a byte in memory and we already have 4 flags - in future I may need some others - it is needed to 
 * organize them into a single char, since it occupies only a byte.  
 * 
 * Data are copied through memcpy, then you will be able to free memory after have called any constructors.  
 * 
 * @date 2023-01-29
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */


#ifndef DATAPACKET_JPL
#define DATAPACKET_JPL

#define USE_PACKET_FLAGS_JPL
//You have chosen to use standard flags
#ifdef USE_PACKET_FLAGS_JPL

    namespace jpl{

        namespace _network{
            namespace _packet{
                #define FLAG_SIZE 1

                #define ROOT_FLAG 0b00000001
                #define ECHO_FLAG 0b00000010
                #define JOIN_FLAG 0b00000100
                #define QUIT_FLAG 0b00001000

                //Internal header macro
                #define PARSE_FLAGS_PACKET_JPL
            }
        }
    }

    #else
        #define FLAG_SIZE 0
    #endif

    namespace jpl{
        namespace _network{
            namespace _packet{
                //Max bytes available for the data packet
                #define DATA_PACKET_MAX_SIZE_JPL 4096  
            }
        }
    }

    #include <jpl/utils/ConversionUtils.hpp>

    #include <cstdlib>//For std::size_t

    namespace jpl{

        namespace _network{
            
            namespace _packet{

                class DataPacket{
                    
                    protected:

                        //Lentghof bytes contained in the data packet (flags are not included)
                        std::size_t size_data;

                        const char* data;

                        /**
                         * @brief extarct data from the const char* and parse them
                         * 
                         * @param data including flags' byte
                         */
                        inline virtual void extract(const char* data){

                            //Store flags
                            #ifdef USE_PACKET_FLAGS_JPL
                                memcpy(&this->flags, &data[0], FLAG_SIZE);
                            #endif

                            this->data = new char[this->size_data];
                            memcpy( (void*)this->data, &data[FLAG_SIZE], this->size_data);
                        }

                        //Defining flags
                        #ifdef USE_PACKET_FLAGS_JPL
                            char flags;

                            virtual bool checkFlags();
                        #endif

                    public:

                        /**
                         * @brief Construct a new Data Packet object. It is called once recv call is done
                         * 
                         * @param buffer of data to decompose 
                         * @param size of the data incoming (including flags)
                         */
                        DataPacket(const char* buffer, std::size_t size);

                        /**
                         * @brief Construct a new Data Packet object.
                         * 
                         * @param flags give any value if you did not define USE_PACKET_FLAGS_JPL
                         * @param data 
                         * @param size 
                         */
                        DataPacket(const char flags, const char* data, std::size_t size);

                        /**
                         * @brief Construct a new Data Packet object.
                         * Create an empty data packet with size_data as 0 and data not initialized. If you have defined USE_PACKET_FLAGS_JPL,
                         * an echo packet is created (always with empty data)
                         * 
                         */
                        DataPacket();

                        const char* getData();

                        std::size_t getLength();

                        #ifdef USE_PACKET_FLAGS_JPL
                            const char getFlags();
                            bool isRoot();
                            bool isEcho();
                            bool isJoin();
                            bool isQuit();
                        #endif

                };

                /**
                 * Serialize data contained into packet into the given buffer. Size of the buffer will be stored into size
                 * 
                 * @param packet 
                 * @param buffer 
                 * @param size of the buffer (counting eventually flags)
                 */
                extern void to_cstr(DataPacket* packet, const char* &buffer, std::size_t &size);
            }
        }
    }

#endif