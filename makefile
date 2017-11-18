CC = g++
CFLAGS = -std=c++11 -Iinclude -Llib

LIB_DIR = lib
BIN_DIR = bin

LIBS = -lgmpxx -lgmp

VPATH=src

.PHONY: all clean dirs

all: dirs bin/tests

clean:
	rm -rf $(LIB_DIR) $(BIN_DIR)

dirs:
	mkdir -p $(LIB_DIR) $(BIN_DIR)


%.o: %.cpp
	$(CC) $(CFLAGS) -c $^ -o $(LIB_DIR)/$@

%.a:
	ar rcs $(LIB_DIR)/$@ $(addprefix $(LIB_DIR)/, $^)

binary_field.o: binary_field.cpp
prime_field.o: prime_field.cpp
nist_curves.o: nist_curves.cpp
ecs.o: ecs.o
libecs.a: binary_field.o prime_field.o nist_curves.o ecs.o

bin/tests: src/tests.cpp libecs.a
	$(CC) $(CFLAGS) src/tests.cpp $(LIBS) -lecs  -o $@
