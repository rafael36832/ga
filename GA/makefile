OBJ = ga.o values.o 
OBJ_NAME = model

CC=g++
CFLAGS=-g -std=c++11

#Verifica o sistema operacional
ifeq ($(OS), Windows_NT)
    RM = del
else
    RM = rm
endif


all: $(OBJ)
	$(CC)  $(OBJ) $(CFLAGS) -o $(OBJ_NAME)

main.o: ga.cpp values.h 
	$(CC) -c ga.cpp $(CFLAGS)

values.o: values.cpp values.h
	$(CC) -c values.cpp $(CFLAGS)

.PHONY: clean clobber
clean:
	$(RM) $(OBJ)

clobber:
	$(RM) $(OBJ_NAME)