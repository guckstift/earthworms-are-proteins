.PHONY : all, rebuild, clean
all : build/sauerkirsche
rebuild : clean all
clean :
	-rm build/*
build/sauerkirsche : build/display.o build/sprite.o build/font.o build/image.o build/game.o build/sauerkirsche.o build/mob.o build/camera.o build/utils.o
	g++ -o build/sauerkirsche build/display.o build/sprite.o build/font.o build/image.o build/game.o build/sauerkirsche.o build/mob.o build/camera.o build/utils.o -lSDL2 -lSDL2_image -lSDL2_ttf
build/display.o : src/display.cpp src/display.h
	g++ -o build/display.o -c src/display.cpp -Wno-write-strings
build/sprite.o : src/sprite.cpp src/sprite.h src/drawable.h src/image.h src/camera.h
	g++ -o build/sprite.o -c src/sprite.cpp -Wno-write-strings
build/font.o : src/font.cpp src/font.h src/image.h src/display.h
	g++ -o build/font.o -c src/font.cpp -Wno-write-strings
build/image.o : src/image.cpp src/image.h src/display.h
	g++ -o build/image.o -c src/image.cpp -Wno-write-strings
build/game.o : src/game.cpp src/game.h src/display.h
	g++ -o build/game.o -c src/game.cpp -Wno-write-strings
build/sauerkirsche.o : src/sauerkirsche.cpp src/sauerkirsche.h src/game.h
	g++ -o build/sauerkirsche.o -c src/sauerkirsche.cpp -Wno-write-strings
build/mob.o : src/mob.cpp src/mob.h src/sprite.h src/drawable.h
	g++ -o build/mob.o -c src/mob.cpp -Wno-write-strings
build/camera.o : src/camera.cpp src/camera.h
	g++ -o build/camera.o -c src/camera.cpp -Wno-write-strings
build/utils.o : src/utils.cpp src/utils.h
	g++ -o build/utils.o -c src/utils.cpp -Wno-write-strings
