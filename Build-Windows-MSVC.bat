mkdir Build
cmake -B Build -S . -G "Visual Studio 16 2019"
cmake --build Build
mkdir Sandbox
copy ".\Build\Core\Debug\Cmple.exe" ".\Sandbox\Cmple.exe"
