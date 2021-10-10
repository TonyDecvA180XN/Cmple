mkdir Build
cmake -B Build -S . -G "Visual Studio 16 2019"
cmake --build Build
mkdir Sandbox
copy ".\Build\Core\Debug\Cmple.exe" ".\Sandbox\Cmple.exe"
copy ".\Build\Core\Debug\Cmple.exe" ".\Tests\Cmple.exe"
copy ".\Build\Tests\Debug\CmpleTest.exe" ".\Tests\CmpleTest.exe"
