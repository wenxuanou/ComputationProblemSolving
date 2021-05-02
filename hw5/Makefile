# compiler
#CC = icpc
CC = g++

# compiler flags
CFLAGS = -Wall

# compiler flag
#COMP =  -I"${MKLROOT}/include"
COMP = -I/usr/local/include -lcnpy -lz

# link
#LIB = -L${MKLROOT}/lib/intel64 -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread -lm -ldl
LIB = -L/usr/local/lib/

# build target
#TARGET = denseMatTransMKL 
TARGET = sparseMatTrans

all: $(TARGET)

$(TARGET):$(TARGET).cpp
	$(CC) -o $(TARGET) $(TARGET).cpp $(LIB) $(COMP) --std=c++11






clean:
	$(RM) *.o $(TARGET)
