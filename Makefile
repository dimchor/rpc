CFLAGS=-Wall
VECTOR_SRC_DIR=./src/vector/
TEST_SRC_DIR=./tests/
BIN_DIR=./bin/
OBJ_DIR=./obj/
LIBS=-pthread -lcheck -pthread -lrt -lm -lsubunit

$(shell mkdir -p $(BIN_DIR) $(OBJ_DIR))

all: test_vector

test_vector: check_vector.o vector.o
	gcc $(CFLAGS) $(OBJ_DIR)check_vector.o $(OBJ_DIR)vector.o -o $(BIN_DIR)test_vector $(LIBS)

check_vector.o: $(TEST_SRC_DIR)check_vector.c
	gcc $(CFLAGS) -c $(TEST_SRC_DIR)check_vector.c -o $(OBJ_DIR)check_vector.o

vector.o: $(VECTOR_SRC_DIR)vector.c $(VECTOR_SRC_DIR)vector.h $(VECTOR_SRC_DIR)error.h
	gcc $(CFLAGS) -c $(VECTOR_SRC_DIR)vector.c -o $(OBJ_DIR)vector.o

clean:
	rm $(OBJ_DIR)*
	rm $(BIN_DIR)*
