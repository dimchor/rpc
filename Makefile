CFLAGS=-Wall -I/usr/include/tirpc 
VECTOR_DIR=./src/vector/
RPC_DIR=./src/rpc/
TEST_SRC_DIR=./tests/
LIBS=-pthread -lcheck -pthread -lrt -lm -lsubunit -ltirpc

all: test_vector rpc

rpc: vector.o
	(cd $(RPC_DIR) && make -f Makefile.calc)

test_vector: check_vector.o vector.o
	gcc $(CFLAGS) $(VECTOR_DIR)check_vector.o $(VECTOR_DIR)vector.o -o $(VECTOR_DIR)test_vector $(LIBS)

check_vector.o: $(TEST_SRC_DIR)check_vector.c
	gcc $(CFLAGS) -c $(TEST_SRC_DIR)check_vector.c -o $(VECTOR_DIR)check_vector.o

vector.o: $(VECTOR_DIR)vector.c $(VECTOR_DIR)vector.h $(VECTOR_DIR)error.h
	gcc $(CFLAGS) -c $(VECTOR_DIR)vector.c -o $(VECTOR_DIR)vector.o

clean:
	rm $(VECTOR_DIR)*.o
