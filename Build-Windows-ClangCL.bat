mkdir Build
cmake -B Build -S . -T ClangCL
cmake --build Build --verbose
