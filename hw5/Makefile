# compiler
CC1 = icpc
CC2 = g++

# compiler flags
CFLAGS = -O

# compiler flag
COMP1 =  -I"${MKLROOT}/include"
COMP2 = -I/usr/local/ -lcnpy -lz

# link
LIB1 = -L${MKLROOT}/lib/intel64 -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread -lm -ldl
LIB2 = -L/usr/local/

# build target
TARGET1 = denseMatTransMKL 
TARGET2 = sparseMatTrans

all: $(TARGET2)

$(TARGET1):$(TARGET1).cpp
	$(CC1) -o $(TARGET1) $(TARGET1).cpp $(LIB1) $(COMP1)


$(TARGET2):$(TARGET2).cpp
	$(CC1) $(CFLAGS) -o $(TARGET2) $(TARGET2).cpp $(LIB2) $(COMP2) --std=c++11






clean:
	$(RM) *.o $(TARGET1) $(TARGET2)
