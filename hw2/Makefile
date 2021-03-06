# compiler
CC = g++
# compiler flags
CFLAGS = -g -Wall
# build target
TARGET = matrixTrans

all: $(TARGET)

$(TARGET):$(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp

clean:
	$(RM) *.o $(TARGET)
