/**
 * @file Stacktrace.hpp
 * 
 * This is an abstraction of a Stacktrace.<br>
 * Since it is a low-level implementation, there's an header-wrapper (StacktraceWrapper) in order to include the header file which is adapt to the running machine; that 
 * header file also has more information about everything you need to know about this feauter.
 * 
 * @author Gabriele-P03
 * @date 2023-08-04
 * @copyright Copyright (c) 2023
 */

#ifndef STACKTRACE_JPL
#define STACKTRACE_JPL

    #include "wrapper/StacktraceWrapper.hpp"
    #include <iostream>

    namespace jpl{
        namespace _utils{
            namespace _debug{

                class Stacktrace{

                    
                    protected:

                        std::vector<Frame>* frames;    //Later it will become an ArrayList

                        unsigned long skipped;
                        unsigned long maxSize;  //It will not be able to be retrieved since it is used only to get stacktrace

                    public:

                        Stacktrace(unsigned long skipped, unsigned long maxSize){
                            this->skipped = skipped;
                            this->size = 0;
                            this->maxSize = maxSize;

                            this->frames = queryStacktrace(skipped, maxSize);
                        }
                        Stacktrace(unsigned long skipped) : Stacktrace(skipped, MAX_STACKFRAMES_JPL){}
                        Stacktrace() : Stacktrace(DEFAULT_SKIP_STACKFRAMES_JPL+2){} //Plus 2 due to the two constructor called 

                        const std::vector<Frame>* getFrames() const { return this->frames; }
                        const unsigned long getSkippedFrames() const{return this->skipped;}

                        inline friend std::ostream& operator<<(std::ostream& os, const Stacktrace &stacktrace){
                            std::vector<Frame>* stackFrames = stacktrace.frames;
                            for(unsigned long i = 0; i < stackFrames->size(); i++){
                                Frame frame = stackFrames->at(i);
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
                
                        ~Stacktrace(){
                            this->frames->clear();
                            delete this->frames;
                        }
                };
            }
        }
    }


#endif