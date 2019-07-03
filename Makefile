CC = g++ # compiler
CCFLAGS = -std=c++11 -Wall -g # compiler flags
LE = g++ # link editor
LEFLAGS =-lm -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lfreeimage -lassimp # link editor flags


ZIP = trab

LOCAL_LIB = lib
LOCAL_INCLUDE = include
LOCAL_SRC = src

SRC = main.cpp

EXEC = exec

SHADERS_PATH = shaders/

OBJECTS = $(LOCAL_LIB)/glad.o $(LOCAL_LIB)/SCL.o $(LOCAL_LIB)/loader.o $(LOCAL_LIB)/Mesh.o $(LOCAL_LIB)/$(addsuffix .o, $(basename $(SRC)))

all : $(OBJECTS)
	$(LE) $^ -o $(EXEC) -I $(LOCAL_INCLUDE) -L $(LOCAL_LIB)  $(LEFLAGS)


$(LOCAL_LIB)/%.o : $(LOCAL_SRC)/%.cpp
	$(CC) $(CCFLAGS) -c -o $@ $< -I$(LOCAL_INCLUDE)

$(LOCAL_LIB)/glad.o : $(LOCAL_SRC)/glad.c $(LOCAL_INCLUDE)/glad/glad.h
	$(CC) $(CCFLAGS) -c -o $@ $< -I$(LOCAL_INCLUDE)


run :
	./$(PROG)


clean :
	rm -f $(LOCAL_LIB)/*.o
	rm -f $(addsuffix .o ,$(basename $(SRC)))
	rm -f $(EXEC)

zip:
	rm -f $(ZIP) && zip -r $(ZIP) * -x "models/**/*" # o -x "models/"
