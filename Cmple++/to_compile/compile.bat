gcc glad.c -c
g++ camera.cpp -c
g++ classes_implementation.cpp -c
g++ cmple_api.cpp -c
g++ cmple_engine.cpp -c
g++ main.cpp -c
g++ model.cpp -c
g++ shader.cpp -c
g++ sound.cpp -c
g++ sprite.cpp -c
g++ stb_image.cpp -c
g++ controll.cpp -c
g++ player.cpp -c
g++ glad.o camera.o classes_implementation.o cmple_api.o cmple_engine.o main.o model.o shader.o sound.o sprite.o stb_image.o controll.o player.o -lopengl32 -L./GL -lglfw3dll -L./audiere -laudiere -o program.exe