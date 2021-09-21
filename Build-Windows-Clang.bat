mkdir Build
cmake -B Build -S . -G "MinGW Makefiles" -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++
cmake --build Build --verbose
