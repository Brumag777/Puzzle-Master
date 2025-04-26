CC      = gcc
CFLAGS  = -Wall -Wextra -pedantic -O1 -fsanitize=address -fno-omit-frame-pointer -g

GAME_SRC    = Main.c Auxiliares.c Comandos.c ComandosLogica.c ComandosLogicaAuxiliares.c Stack.c
TEST_SRC    = Testes/testes.c \
              Principais/main.c \
              Principais/puzzle.c

TESTAUX_SRC = TAuxiliares.c Auxiliares.c Comandos.c ComandosLogica.c ComandosLogicaAuxiliares.c Stack.c
TESTCLAUX_SRC = TComandosLogicaAuxiliares.c Auxiliares.c Comandos.c ComandosLogica.c ComandosLogicaAuxiliares.c Stack.c

EXEC        = Jogo
TEST_EXEC   = Testes/Testes

.PHONY: all Jogo Testes TAuxiliares TComandosLogicaAuxiliares clean

all: Jogo

Jogo: $(GAME_SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(GAME_SRC)

Testes: CFLAGS += -fprofile-arcs -ftest-coverage
Testes: LDFLAGS += -lgcov
Testes:
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TEST_EXEC) $(TEST_SRC)
	./$(TEST_EXEC)
	gcov Principais/main.c
	gcov Principais/puzzle.c

TAuxiliares: LDFLAGS += -lcunit
TAuxiliares: $(TESTAUX_SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(TESTAUX_SRC)
	./$@

TComandosLogicaAuxiliares: LDFLAGS += -lcunit
TComandosLogicaAuxiliares: $(TESTCLAUX_SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(TESTCLAUX_SRC)
	./$@

clean:
	rm -f *.o *.gcda *.gcno *.gcov \
	       Principais/*.o Principais/*.gcda Principais/*.gcno Principais/*.gcov \
	       Testes/*.o Testes/*.gcda Testes/*.gcno Testes/*.gcov \
	       $(EXEC) $(TEST_EXEC) TAuxiliares TComandosLogicaAuxiliares