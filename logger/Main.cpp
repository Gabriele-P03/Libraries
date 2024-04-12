#define USE_LOGGER_JPL
#define USE_STACKTRACE_W_EXCEPTION_JPL
#define AUTO_LOG_EXCEPTION_JPL

#include <jpl/logger/LoggerWrapper.hpp>

int main(){

    throw new jpl::_exception::FileNotFoundException("Op");

    return 0;
}