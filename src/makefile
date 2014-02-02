OBJ = minishell.o file.o path.o list.o exec.o parse.o
SRC = minishell.c list.c path.c file.c exec.c header.h list.h parse.c
CC = gcc
OPTION =  -Wall -g -CB

minishell : $(OBJ)
	@$(CC) -g -o minishell $(OBJ)

minishell.o : $(SRC)
	@$(CC) -g -c minishell.c list.c file.c path.c

parse.o : header.h list.c list.h parse.c
	@$(CC) -g -c list.c parse.c

file.o : list.c header.h file.c list.h
	@$(CC) -g -c list.c file.c

path.o : list.h path.c list.c header.h
	@$(CC) -g -c list.c path.c

list.o : list.c header.h
	@$(CC) -g -c list.c

exec.o : exec.c header.h
	@$(CC) -g -c exec.c

clean :
	@rm $(OBJ)
