/**
 * @file Stacktrace.hpp
 * 
 * This is an abstraction of a Stacktrace.<br>
 * Since it is a low-level implementation, there's an header-wrapper (StacktraceWrapper) in order to include the header file which is adapt to the running machine; that 
 * header file also has more information about everything you need to know about this feauter.
 * 
 * It is known that size var is 
 * 
 * @author Gabriele-P03
 * @date 2023-08-04
 * @copyright Copyright (c) 2023
 */

#ifndef STACKTRACE_JPL
#define STACKTRACE_JPL

    #include "Frame.hpp"
    #include <iostream>

    namespace jpl{
        namespace _utils{

            namespace _collections{
                namespace _list{
                    template<class T>
                    class LinkedList;
                }
            }

            namespace _debug{

                class Stacktrace{

                    
                    protected:

                        _collections::_list::LinkedList<jpl::_utils::_debug::Frame*>* frames;    //Later it will become an ArrayList

                        unsigned long skipped;
                        unsigned long maxSize;  //It will not be able to be retrieved since it is used only to get stacktrace
                        unsigned long size;     //It is the size of frames contained in frames, therefore the LL has the same size
                    public:

                        Stacktrace(unsigned long skipped, unsigned long maxSize);
                        Stacktrace(unsigned long skipped);
                        Stacktrace();

                        const _collections::_list::LinkedList<_debug::Frame*>* getFrames() const;
                        const unsigned long getSkippedFrames() const;
                        const _debug::Frame getFrameAt(unsigned long i) const;
                        const unsigned long getSize() const noexcept{
                            return this->size;
                        }

                        inline friend std::ostream& operator<<(std::ostream& os, const Stacktrace &s){
                            for(unsigned long i = 0; i < s.size; i++){
                                _debug::Frame frame = s.getFrameAt(i);
                                os<<"\t#"<<i<<" ";
                                if(frame.frame_valid){
                                    os<<frame.function_name<<" of "<<frame.file_name<<" at line "<<frame.line<<". Address "<<frame.address;
                                }else{
                                    os<<"Invalid Frame";
                                }
                                os<<std::endl;
                            }
                            return os;
                        }
                
                        ~Stacktrace();
                };

                Stacktrace* getStacktrace(unsigned long skipped, unsigned long maxFrame);
                std::string stktrc_str(const Stacktrace* stacktrace);
            }
        }
    }

    #include "wrapper/StacktraceWrapper.hpp"

#endif