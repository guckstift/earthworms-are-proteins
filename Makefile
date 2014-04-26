.PHONY : all, rebuild, clean
all : build/sauerkirsche.exe
rebuild : clean all
clean :
	-rm build/*
build/sauerkirsche.exe : build/display.o build/sprite.o build/font.o build/image.o build/game.o build/sauerkirsche.o build/mixer.o build/sound.o build/mob.o build/camera.o build/utils.o
	i686-w64-mingw32-g++ -o build/sauerkirsche.exe -mwindows -L./windows/SDL2-2.0.3/i686-w64-mingw32/lib -L./windows/SDL2_image-2.0.0/i686-w64-mingw32/lib -L./windows/SDL2_mixer-2.0.0/i686-w64-mingw32/lib -L./windows/SDL2_ttf-2.0.12/i686-w64-mingw32/lib build/display.o build/sprite.o build/font.o build/image.o build/game.o build/sauerkirsche.o build/mixer.o build/sound.o build/mob.o build/camera.o build/utils.o -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
build/display.o : src/display.cpp src/display.h
	i686-w64-mingw32-g++ -o build/display.o -I./windows/SDL2-i686-w64-mingw32-merged-include -I./windows/SDL2-i686-w64-mingw32-merged-include/SDL2 -c src/display.cpp -Wno-write-strings
build/sprite.o : src/sprite.cpp src/sprite.h src/drawable.h src/image.h src/camera.h
	i686-w64-mingw32-g++ -o build/sprite.o -I./windows/SDL2-i686-w64-mingw32-merged-include -I./windows/SDL2-i686-w64-mingw32-merged-include/SDL2 -c src/sprite.cpp -Wno-write-strings
build/font.o : src/font.cpp src/font.h src/image.h src/display.h
	i686-w64-mingw32-g++ -o build/font.o -I./windows/SDL2-i686-w64-mingw32-merged-include -I./windows/SDL2-i686-w64-mingw32-merged-include/SDL2 -c src/font.cpp -Wno-write-strings
build/image.o : src/image.cpp src/image.h src/display.h
	i686-w64-mingw32-g++ -o build/image.o -I./windows/SDL2-i686-w64-mingw32-merged-include -I./windows/SDL2-i686-w64-mingw32-merged-include/SDL2 -c src/image.cpp -Wno-write-strings
build/game.o : src/game.cpp src/game.h src/display.h
	i686-w64-mingw32-g++ -o build/game.o -I./windows/SDL2-i686-w64-mingw32-merged-include -I./windows/SDL2-i686-w64-mingw32-merged-include/SDL2 -c src/game.cpp -Wno-write-strings
build/sauerkirsche.o : src/sauerkirsche.cpp src/sauerkirsche.h src/game.h src/display.h
	i686-w64-mingw32-g++ -o build/sauerkirsche.o -I./windows/SDL2-i686-w64-mingw32-merged-include -I./windows/SDL2-i686-w64-mingw32-merged-include/SDL2 -c src/sauerkirsche.cpp -Wno-write-strings
build/mixer.o : src/mixer.cpp src/mixer.h
	i686-w64-mingw32-g++ -o build/mixer.o -I./windows/SDL2-i686-w64-mingw32-merged-include -I./windows/SDL2-i686-w64-mingw32-merged-include/SDL2 -c src/mixer.cpp -Wno-write-strings
build/sound.o : src/sound.cpp src/sound.h
	i686-w64-mingw32-g++ -o build/sound.o -I./windows/SDL2-i686-w64-mingw32-merged-include -I./windows/SDL2-i686-w64-mingw32-merged-include/SDL2 -c src/sound.cpp -Wno-write-strings
build/mob.o : src/mob.cpp src/mob.h src/sprite.h src/drawable.h
	i686-w64-mingw32-g++ -o build/mob.o -I./windows/SDL2-i686-w64-mingw32-merged-include -I./windows/SDL2-i686-w64-mingw32-merged-include/SDL2 -c src/mob.cpp -Wno-write-strings
build/camera.o : src/camera.cpp src/camera.h
	i686-w64-mingw32-g++ -o build/camera.o -I./windows/SDL2-i686-w64-mingw32-merged-include -I./windows/SDL2-i686-w64-mingw32-merged-include/SDL2 -c src/camera.cpp -Wno-write-strings
build/utils.o : src/utils.cpp src/utils.h
	i686-w64-mingw32-g++ -o build/utils.o -I./windows/SDL2-i686-w64-mingw32-merged-include -I./windows/SDL2-i686-w64-mingw32-merged-include/SDL2 -c src/utils.cpp -Wno-write-strings
