#Flags do guião
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O1 -fsanitize=address -fno-omit-frame-pointer -g -lm

#Nome dos ficheiros
SRC = main.c
TEST_SRC = Tmain.c

EXEC = Jogo
TEST_EXEC = Testes

#Compilar o jogo
Jogo: $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)

#gcov
Testes: CFLAGS += -fprofile-arcs -ftest-coverage
Testes: LDFLAGS += -lgcov
Testes:
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TEST_EXEC) $(TEST_SRC)
	./$(TEST_EXEC)
	gcov main.c

#Limpa os ficheiros gerados
clean:
	rm -f *.o *.gcda *.gcno *.gcov $(EXEC) $(TEST_EXEC)