OBJ      := obj
SRC      := src
INC      := include
CFLAGS   := -lm -g -O2 -Wall -pedantic -Wextra -Wwrite-strings
EXE 	 := acsh.out
PROJETO  := main

# Cria objetos de todos os arquivos de código-fonte para então linká-los no programa final
main: $(OBJ)/listaencad.o $(OBJ)/utils.o $(OBJ)/signalManipulation.o $(OBJ)/sysFuncs.o $(OBJ)/$(PROJETO).o
	gcc $(OBJ)/*.o -o $(EXE) $(CFLAGS)

$(OBJ)/signalManipulation.o: $(SRC)/signalManipulation.c $(INC)/signalManipulation.h
	gcc -c $(CFLAGS) "$(SRC)/signalManipulation.c" -o "$(OBJ)/signalManipulation.o"

$(OBJ)/sysFuncs.o: $(SRC)/sysFuncs.c $(INC)/sysFuncs.h
	gcc -c $(CFLAGS) "$(SRC)/sysFuncs.c" -o "$(OBJ)/sysFuncs.o"

$(OBJ)/listaencad.o: $(SRC)/listaencad.c $(INC)/listaencad.h
	gcc -c $(CFLAGS) "$(SRC)/listaencad.c" -o "$(OBJ)/listaencad.o"

$(OBJ)/utils.o: $(SRC)/utils.c $(INC)/utils.h
	gcc -c $(CFLAGS) "$(SRC)/utils.c" -o "$(OBJ)/utils.o"

$(OBJ)/$(PROJETO).o: $(PROJETO).c
	gcc -c $(CFLAGS) $(PROJETO).c -o "$(OBJ)/$(PROJETO).o"

# Limpa objetos e o executável do programa
clean:
	-rm $(OBJ)/*.o
	-rm $(EXE)