CC = g++
VPATH = src/
OBJ_DIR := build/
INCLUDE_PATHS = -I./include -I./src
LIB_PATHS = -L/usr/lib
LIBS = 

SRC_CPP     :=                      \
   $(wildcard src/*.cpp)         \

SRC_C := \
   $(wildcard src/*.c)         \

BASENAMES_CPP := $(notdir $(SRC_CPP))
BASENAMES_C := $(notdir $(SRC_C))
OBJECTS  := $(BASENAMES_C:%.c=%.o)  #Don't wrap BASENAMES with $()
OBJECTS  += $(BASENAMES_CPP:%.cpp=%.o)  #Don't wrap BASENAMES with $()


OBJECT_PATHS = $(addprefix $(OBJ_DIR),$(OBJECTS))
CPP_FLAGS = $(INCLUDE_PATHS) -std=c++11 -Wall

vpath %.cpp src
vpath %.c src
vpath %.o build

all: main

# Dep
deps := $(patsubst %.o, %.d, $(OBJECT_PATHS))
-include $(deps)
DEPFLAGS = -MMD -MF build/deps/$(@:.o=.d)

test:
	echo $(OBJECTS)
# Targets
main: $(OBJECTS)
	g++ $(OBJECT_PATHS) $(CPP_FLAGS) $(LIB_PATHS) -o build/main $(LIBS)

#Patterns
%.o: %.cpp
	$(CC) -c $< $(CPP_FLAGS) -o build/$@ $(DEPFLAGS)

%.o: %.c
	$(CC) -c $< $(CPP_FLAGS) -o build/$@ $(DEPFLAGS) 2>log.txt

.PHONY: clean, cleanwin
clean: 
	rm -f build/*.o
	rm -f build/deps/*.d

cleanwin:
	del /S build\*.o
	del /S build\deps\*.d

