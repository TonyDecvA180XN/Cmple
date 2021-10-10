mkdir Build
cmake -B Build -S . -G "MinGW Makefiles" -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++
cmake --build Build
mkdir Sandbox
copy ".\Build\Core\Cmple.exe" ".\Sandbox\Cmple.exe"
copy ".\Build\Core\Cmple.exe" ".\Tests\Cmple.exe"
copy ".\Build\Tests\CmpleTest.exe" ".\Tests\CmpleTest.exe"
