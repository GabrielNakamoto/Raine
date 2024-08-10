# Compiler
CC := gcc
CXX := g++

# Compiler flags
CFLAGS := -Wall -Wextra -g
CXXFLAGS := $(CFLAGS) -std=c++11

INCLUDES := -I. \
            -I../vendor/glad/include \
            -I../vendor/GLFW/include \
            -I../vendor/imgui/include \
			-I../vendor/stb_image/include \
			-I../vendor/tinyobjloader/include

LIBPATHS := -L../vendor/GLFW/lib 

LIBS := -lglfw.3 -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -framework CoreFoundation

SOURCES := $(wildcard *.cpp) \
           ../vendor/glad/src/glad.c \
           $(wildcard ../vendor/imgui/src/*.cpp)

OBJECTS := $(SOURCES:.cpp=.o)
OBJECTS := $(OBJECTS:.c=.o)

TARGET	:= app

all: clean $(TARGET) run

# Linking
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LIBPATHS) $(LIBS)

# Compilation
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	@echo "\nRunning program"
	./${TARGET}

.PHONY: all clean


