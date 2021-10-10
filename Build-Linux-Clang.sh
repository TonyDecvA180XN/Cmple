mkdir Build
cmake -B Build -S . -G "Unix Makefiles" -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++
cmake --build Build
mkdir Sandbox
copy "./Build/Core/Cmple" "./Sandbox/Cmple"
