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

finite_fields.o: finite_fields.cpp
libecc.a: finite_fields.o

bin/tests: src/tests.cpp libecc.a
	$(CC) $(CFLAGS) src/tests.cpp $(LIBS) -lecc  -o $@




