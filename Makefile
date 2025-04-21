CC      = gcc
CFLAGS  = -Wall -Wextra -pedantic -O1 -fsanitize=address -fno-omit-frame-pointer -g

GAME_SRC    = Main.c Auxiliares.c Comandos.c ComandosLogica.c ComandosLogicaAuxiliares.c Stack.c
TEST_SRC    = Testes/testes.c \
              Principais/main.c \
              Principais/puzzle.c

EXEC        = Jogo
TEST_EXEC   = Testes/Testes

Jogo: $(GAME_SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(GAME_SRC)

Testes: CFLAGS += -fprofile-arcs -ftest-coverage
Testes: LDFLAGS += -lgcov
Testes:
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TEST_EXEC) $(TEST_SRC)
	./$(TEST_EXEC)
	gcov Principais/main.c
	gcov Principais/puzzle.c

clean:
	rm -f *.o *.gcda *.gcno *.gcov \
	       Principais/*.o Principais/*.gcda Principais/*.gcno Principais/*.gcov \
	       Testes/*.o Testes/*.gcda Testes/*.gcno Testes/*.gcov \
	       $(EXEC) $(TEST_EXEC)