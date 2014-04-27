.PHONY : all, rebuild, clean
all : build/earthworms
rebuild : clean all
clean :
	-rm build/*
build/earthworms : build/display.o build/sprite.o build/font.o build/image.o build/game.o build/cherry.o build/mixer.o build/leaf.o build/bird.o build/sound.o build/worm.o build/mob.o build/camera.o build/utils.o build/earthworms.o
	g++ -o build/earthworms build/display.o build/sprite.o build/font.o build/image.o build/game.o build/cherry.o build/mixer.o build/leaf.o build/bird.o build/sound.o build/worm.o build/mob.o build/camera.o build/utils.o build/earthworms.o -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
build/display.o : src/display.cpp src/display.h
	g++ -o build/display.o -c src/display.cpp -Wno-write-strings
build/sprite.o : src/sprite.cpp src/sprite.h src/drawable.h src/image.h src/camera.h
	g++ -o build/sprite.o -c src/sprite.cpp -Wno-write-strings
build/font.o : src/font.cpp src/font.h src/image.h src/display.h
	g++ -o build/font.o -c src/font.cpp -Wno-write-strings
build/image.o : src/image.cpp src/image.h src/display.h src/utils.h
	g++ -o build/image.o -c src/image.cpp -Wno-write-strings
build/game.o : src/game.cpp src/game.h src/display.h
	g++ -o build/game.o -c src/game.cpp -Wno-write-strings
build/cherry.o : src/cherry.cpp src/cherry.h src/mob.h src/sprite.h src/drawable.h
	g++ -o build/cherry.o -c src/cherry.cpp -Wno-write-strings
build/mixer.o : src/mixer.cpp src/mixer.h
	g++ -o build/mixer.o -c src/mixer.cpp -Wno-write-strings
build/leaf.o : src/leaf.cpp src/leaf.h src/mob.h src/sprite.h src/drawable.h
	g++ -o build/leaf.o -c src/leaf.cpp -Wno-write-strings
build/bird.o : src/bird.cpp src/bird.h src/mob.h src/sprite.h src/drawable.h
	g++ -o build/bird.o -c src/bird.cpp -Wno-write-strings
build/sound.o : src/sound.cpp src/sound.h
	g++ -o build/sound.o -c src/sound.cpp -Wno-write-strings
build/worm.o : src/worm.cpp src/earthworms.h src/game.h src/worm.h src/image.h src/cherry.h src/mob.h src/sprite.h src/drawable.h src/leaf.h src/mob.h src/sprite.h src/drawable.h
	g++ -o build/worm.o -c src/worm.cpp -Wno-write-strings
build/mob.o : src/mob.cpp src/mob.h src/sprite.h src/drawable.h
	g++ -o build/mob.o -c src/mob.cpp -Wno-write-strings
build/camera.o : src/camera.cpp src/camera.h
	g++ -o build/camera.o -c src/camera.cpp -Wno-write-strings
build/utils.o : src/utils.cpp src/utils.h
	g++ -o build/utils.o -c src/utils.cpp -Wno-write-strings
build/earthworms.o : src/earthworms.cpp src/earthworms.h src/game.h src/display.h src/image.h src/worm.h src/cherry.h src/mob.h src/sprite.h src/drawable.h src/leaf.h src/mob.h src/sprite.h src/drawable.h src/bird.h src/mob.h src/sprite.h src/drawable.h
	g++ -o build/earthworms.o -c src/earthworms.cpp -Wno-write-strings
