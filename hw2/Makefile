# compiler
CC = g++
# compiler flags
CFLAGS = -g -Wall
# build target
TARGET = matrixTrans
# library flag
LIB = -fopenmp

all: $(TARGET)

$(TARGET):$(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(LIB) $(TARGET).cpp

clean:
	$(RM) *.o $(TARGET)
