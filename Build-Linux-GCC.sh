mkdir Build
cmake -B Build -S . -G "Unix Makefiles"
cmake --build Build
mkdir Sandbox
copy "./Build/Core/Cmple" "./Sandbox/Cmple"
