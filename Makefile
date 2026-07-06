CC := gcc
SRC := src
OBJ := objects

wordhist: $(OBJ)/wordhist.o $(OBJ)/histogram.o $(OBJ)/input.o $(OBJ)/StrArrayBuilder.o $(OBJ)/memory.o
	$(CC) -o wordhist $(OBJ)/wordhist.o $(OBJ)/histogram.o $(OBJ)/input.o $(OBJ)/StrArrayBuilder.o $(OBJ)/memory.o

$(OBJ)/wordhist.o: wordhist.c
	$(CC) -c -o $(OBJ)/wordhist.o wordhist.c

$(OBJ)/histogram.o: $(SRC)/histogram.c
	$(CC) -c -o $(OBJ)/histogram.o $(SRC)/histogram.c

$(OBJ)/input.o: $(SRC)/input.c
	$(CC) -c -o $(OBJ)/input.o $(SRC)/input.c

$(OBJ)/memory.o: $(SRC)/memory.c
	$(CC) -c -o $(OBJ)/memory.o $(SRC)/memory.c

$(OBJ)/StrArrayBuilder.o: $(SRC)/StrArrayBuilder.c
	$(CC) -c -o $(OBJ)/StrArrayBuilder.o $(SRC)/StrArrayBuilder.c
