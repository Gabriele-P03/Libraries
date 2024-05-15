#include "Stacktrace.hpp"

jpl::_utils::_debug::Stacktrace::Stacktrace(unsigned long skipped, unsigned long maxSize){
    this->skipped = skipped;
    this->maxSize = maxSize;
    this->frames = queryStacktrace(skipped, maxSize);
    this->size = this->frames->getSize();
}
jpl::_utils::_debug::Stacktrace::Stacktrace(unsigned long skipped) : jpl::_utils::_debug::Stacktrace(skipped, MAX_STACKFRAMES_JPL){}
jpl::_utils::_debug::Stacktrace::Stacktrace() : jpl::_utils::_debug::Stacktrace(0){}

const jpl::_utils::_debug::Frame jpl::_utils::_debug::Stacktrace::getFrameAt(unsigned long i) const{
    if(i >= this->size)
        throw new jpl::_exception::IndexOutOfBoundsException(this->size, i);
    return *this->frames->get(i);
}

const jpl::_utils::_collections::_list::LinkedList<jpl::_utils::_debug::Frame*>* jpl::_utils::_debug::Stacktrace::getFrames() const {
     return this->frames; 
}

const unsigned long jpl::_utils::_debug::Stacktrace::getSkippedFrames() const{
    return this->skipped;
}


jpl::_utils::_debug::Stacktrace::~Stacktrace(){
    this->frames->clear();
    delete this->frames;
}