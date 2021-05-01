# compiler
CC = icpc

# compiler flags
CFLAGS = -Wall

# compiler flag
COMP =  -I"${MKLROOT}/include"

# link
LIB = -L${MKLROOT}/lib/intel64 -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread -lm -ldl

# build target
TARGET = denseMatTransMKL


all: $(TARGET)

$(TARGET):$(TARGET).cpp
	$(CC) $(LIB) $(COMP) $(TARGET).cpp


clean:
	$(RM) *.o $(TARGET)
