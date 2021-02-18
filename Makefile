.DEFAULT_GOAL := all


SRC = $(wildcard src/*.cpp) \
		$(wildcard src/*/*.cpp) \
		$(wildcard src/*/*/*.cpp) \
		$(wildcard src/*/*/*/*.cpp)

OBJDIR = build

OBJ := $(SRC:%.cpp=$(OBJDIR)/%.o)

CC = g++

#TO FIT SEMESTRAL WORK REQUIREMENTS
SDL_COMPILER_FLAGS = -I/usr/include/SDL2 -D_REENTRANT
SDL_LINKER_FLAGS = -L/usr/lib -pthread -lSDL2 -lSDL2_ttf -lSDL2_image

#FOR REAL USAGE
#SDL_COMPILER_FLAGS = `sdl2-config --cflags`
#SDL_LINKER_FLAGS = `sdl2-config --libs` -lSDL2_ttf -lSDL2_image

COMPILER_FLAGS = -Wall -Wextra -pedantic -O2 -g $(SDL_COMPILER_FLAGS)

LINKER_FLAGS = $(SDL_LINKER_FLAGS)

OBJ_NAME = semestral-work

all: doc compile

$(OBJDIR)/%.o: %.cpp
	@mkdir -p '$(@D)'
	$(CC) $(COMPILER_FLAGS) -c $< -o $@

$(OBJ_NAME): $(OBJ)
	mkdir -p save
	$(CC) $(LINKER_FLAGS) -o $(OBJ_NAME) $(OBJ)

compile: $(OBJ_NAME)

run: $(OBJ_NAME)
	./$(OBJ_NAME)

clean:
	rm -rf build
	rm -rf save
	rm -rf doc
	rm -f $(OBJ_NAME)

doc: $(SRC)
	mkdir -p doc
	doxygen
