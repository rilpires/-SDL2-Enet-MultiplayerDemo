
ENET_OBJECT_FILES   := $(wildcard ../Engine/enet-1.3.13/*.o)
INCLUDE_DIRS := ../Engine/enet-1.3.13/include
				
make: $(ENET_OBJECT_FILES) server.cpp
	g++ server.cpp $(ENET_OBJECT_FILES)  -I$(INCLUDE_DIRS) -o server
