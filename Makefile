ENGINE_CPP_FILES    := $(wildcard Engine/*.cpp)
ENGINE_OBJECT_FILES := $(patsubst %.cpp,%.o,$(ENGINE_CPP_FILES))

GAME_CPP_FILES    := $(wildcard src/*.cpp)
GAME_OBJECT_FILES := $(patsubst %.cpp,%.o,$(GAME_CPP_FILES))

ENET_OBJECT_FILES   := $(wildcard Engine/enet-1.3.13/*.o)

OBJECT_FILES := $(ENGINE_OBJECT_FILES) $(GAME_OBJECT_FILES)


INCLUDE_DIRS := src/  \
				Engine/ \
				Engine/enet-1.3.13/include \
				#INCLUDE SDL PATHS HERE: SDL2 , SDL2_image and SDL2_ttf

LIBS_LINKED  := -lSDL2 -lSDL2_image -lSDL2_ttf


main: $(OBJECT_FILES) $(ENET_OBJECT_FILES)
	@echo 
	@echo Linkando tudo em $@:
	@echo $(patsubst %.o,"\n-%.o",$(OBJECT_FILES) )
	@echo $(patsubst %.o,"\n-%.o",$(ENET_OBJECT_FILES) )
	@echo
	g++ \
	$(OBJECT_FILES) \
	$(ENET_OBJECT_FILES) \
	$(patsubst %,-I%,$(INCLUDE_DIRS)) \
	$(LIBS_LINKED) \
	-o main 

build: main

rebuild: clean main

clean:
	rm -f main $(OBJECT_FILES)

src/%.o: %.cpp $(ENGINE_OBJECT_FILES)
	g++ -std=c++11 -O2 $(patsubst %,-I%,$(INCLUDE_DIRS)) -c $< -o $@

Engine/enet-1.3.13/%.o:
	./configure
	make
	make install
%.o: %.cpp
	g++ -std=c++11 -O2 $(patsubst %,-I%,$(INCLUDE_DIRS)) -c $< -o $@

