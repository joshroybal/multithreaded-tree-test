CC = g++
CFLAGS = -O2
LFLAGS = -lpthread
BIN = bin/trees
OBJ = obj/main.o obj/bst.o obj/avl.o

$(BIN): $(OBJ)
	$(CC) $(LFLAGS) -o $@ $^

obj/main.o: src/main.cpp src/bst.hpp src/avl.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

obj/bst.o: src/bst.cpp src/bst.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

obj/avl.o: src/avl.cpp src/bst.hpp src/avl.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY : clean
clean:
	$(RM) $(BIN) $(OBJ)
