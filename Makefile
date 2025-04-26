CC      = gcc
CFLAGS  = -Wall -Wextra -pedantic -O1 -fsanitize=address -fno-omit-frame-pointer -g

GAME_SRC    = Main.c Auxiliares.c Comandos.c ComandosLogica.c ComandosLogicaAuxiliares.c Stack.c

TESTAUX_SRC = TAuxiliares.c Auxiliares.c Comandos.c ComandosLogica.c ComandosLogicaAuxiliares.c Stack.c
TESTCLAUX_SRC = TComandosLogicaAuxiliares.c Auxiliares.c Comandos.c ComandosLogica.c ComandosLogicaAuxiliares.c Stack.c

EXEC = Jogo

.PHONY: all Jogo Testes TAuxiliares TComandosLogicaAuxiliares clean

all: Jogo

Jogo: $(GAME_SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(GAME_SRC)

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
	       $(EXEC) $(TEST_EXEC) TAuxiliares TComandosLogicaAuxiliares