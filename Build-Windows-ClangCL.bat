mkdir Build
cmake -B Build -S . -T ClangCL
cmake --build Build
mkdir Sandbox
copy ".\Build\Core\Cmple.exe" ".\Sandbox\Cmple.exe"
