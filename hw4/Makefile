# compiler
CC = g++
# compiler flags
CFLAGS = -g -Wall
# build target
TARGET1 = recursive
TARGET2 = bruteForce
# library flag
LIB = -fopenmp

all: $(TARGET1) $(TARGET2)

$(TARGET1):$(TARGET1).cpp
	$(CC) $(CFLAGS) -o $(TARGET1) $(LIB) $(TARGET1).cpp

$(TARGET2):$(TARGET2).cpp
	$(CC) $(CFLAGS) -o $(TARGET2) $(LIB) $(TARGET2).cpp

clean:
	$(RM) *.o $(TARGET1) $(TARGET2)
