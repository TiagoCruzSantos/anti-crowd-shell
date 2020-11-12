OBJ      := obj
SRC      := src
INC      := include
CFLAGS   := -lm -g -O2 -Wall -pedantic -Wextra -Wwrite-strings
EXE 	 := acsh.out
PROJETO  := main

# Cria objetos de todos os arquivos de código-fonte para então linká-los no programa final
main: clean $(OBJ)/$(PROJETO).o
	gcc $(OBJ)/*.o -o $(EXE) $(CFLAGS)

$(OBJ)/$(PROJETO).o: $(PROJETO).c
	gcc -c $(CFLAGS) $(PROJETO).c -o "$(OBJ)/$(PROJETO).o"

# Limpa objetos e o executável do programa
clean:
	-rm $(OBJ)/*.o
	-rm $(EXE)