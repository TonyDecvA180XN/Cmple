mkdir Build
cmake -B Build -S . -G "MinGW Makefiles"
cmake --build Build
mkdir Sandbox
copy ".\Build\Core\Cmple.exe" ".\Sandbox\Cmple.exe"
copy ".\Build\Core\Cmple.exe" ".\Tests\Cmple.exe"
copy ".\Build\Tests\CmpleTest.exe" ".\Tests\CmpleTest.exe"
