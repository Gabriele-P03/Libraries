rm -r build/*
cmake -S . -B build/ -DUSE_STACKTRACE_W_EXCEPTION_JPL=true -DAUTO_LOG_EXCEPTION_JPL=true -DPROFILER_JPL=true -DSTRING_UTILS_CPP=true
cd build/
make