# compiler
CC = g++
# compiler flags
CFLAGS = -g -Wall
# build target
TARGET = multiplyLargeInt
# linker
LIBS = -lfftw3 -lm
# library path
LFLAGS = -L/usr/lib/x86_64-linux-gnu

all: $(TARGET)

$(TARGET):$(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp $(LFLAGS) $(LIBS)

clean:
	$(RM) *.o $(TARGET)	
