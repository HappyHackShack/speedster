# Compiler and flags
## gxxFLAGS0 = -Wall -Wextra -std=c++17 -Iinclude
gxxFLAGS = -std=c++23

# Libraries to link (Example: pthread and math libraries)
LIBS  = -lSDL3 -lSDL3_image -lSDL3_ttf

BUILD = build

# Target executable name
SPEED = speedster

# Source and object files
SRCS = $(wildcard */*.cpp) $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, $(BUILD)/%.o, $(SRCS))

# Default rule to build the program
all: $(TARGET)

# Rule to link object files into the final executable
speed: $(OBJS)
	g++ $(gxxFLAGS) -o speedster $(OBJS) $(LIBS)

# Rule to compile source files into object files
$(BUILD)/%.o: %.cpp
	@mkdir -p $(dir $@)
	g++ $(gxxFLAGS) -c $< -o $@

# Rule to clean up build files
clean:
	rm -f $(OBJS) $(SPEED)
