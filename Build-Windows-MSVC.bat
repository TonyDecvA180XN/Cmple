mkdir Build
cmake -B Build -S . -G "Visual Studio 16 2019"
cmake --build Build --verbose
