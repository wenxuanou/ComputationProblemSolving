# compiler
CC = icpc

# compiler flags
CFLAGS = -Wall

# include path
INC = /usr/include/mkl

# library path
LIB = /usr/lib/x86_64-linux-gnu

# build target
TARGET = denseMatTransMKL


all: $(TARGET)

$(TARGET):$(TARGET).cpp
	$(CC) $(LIB) $(INC) -o $(TARGET) $(TARGET).cpp


clean:
	$(RM) *.o $(TARGET)
