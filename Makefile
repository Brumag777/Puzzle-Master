# Flags do guião
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O1 -fsanitize=address -fno-omit-frame-pointer -g

# Nome dos ficheiros
GAME_SRC = Principais/main.c
TEST_SRC = Testes/testes.c Principais/main.c

EXEC = Jogo
TEST_EXEC = Testes/Testes

#Compilar o jogo
Jogo: $(GAME_SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(GAME_SRC)

#gcov
Testes: CFLAGS += -fprofile-arcs -ftest-coverage
Testes: LDFLAGS += -lgcov
Testes:
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TEST_EXEC) $(TEST_SRC)
	./$(TEST_EXEC)
	gcov Principais/main.c

#Limpa os ficheiros gerados
clean:
	rm -f *.o *.gcda *.gcno *.gcov \
	       Principais/*.o Principais/*.gcda Principais/*.gcno Principais/*.gcov \
	       Testes/*.o Testes/*.gcda Testes/*.gcno Testes/*.gcov \
	       $(EXEC) $(TEST_EXEC)