mkdir -p Build
cmake -B Build -S . -G "Unix Makefiles"
cmake --build Build
mkdir -p Sandbox
cp "./Build/Core/Cmple" "./Sandbox/Cmple"
