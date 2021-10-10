mkdir -p Build
cmake -B Build -S . -G "Unix Makefiles" -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++
cmake --build Build
mkdir -p Sandbox
cp "./Build/Core/Cmple" "./Sandbox/Cmple"
cp "./Build/Core/Cmple" "./Tests/Cmple"
cp "./Build/Tests/CmpleTest" "./Tests/CmpleTest"
