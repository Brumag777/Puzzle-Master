CC      = gcc
CFLAGS  = -Wall -Wextra -pedantic -O1 -fsanitize=address -fno-omit-frame-pointer -g
COV_CFLAGS = -Wall -Wextra -pedantic -O1 -fprofile-arcs -ftest-coverage -g

GAME_SRC    = Main.c Auxiliares.c Comandos.c ComandosLogica.c ComandosLogicaAuxiliares.c Stack.c

TESTAUX_SRC = TAuxiliares.c Auxiliares.c Comandos.c ComandosLogica.c ComandosLogicaAuxiliares.c Stack.c
TESTCLAUX_SRC = TComandosLogicaAuxiliares.c Auxiliares.c Comandos.c ComandosLogica.c ComandosLogicaAuxiliares.c Stack.c

EXEC = Jogo

.PHONY: all Jogo Testes TAuxiliares TComandosLogicaAuxiliares coverage clean

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

TAuxiliares-cov: LDFLAGS += -lcunit
TAuxiliares-cov: $(TESTAUX_SRC)
	$(CC) $(COV_CFLAGS) -o $@ $(TESTAUX_SRC) $(LDFLAGS)

TComandosLogicaAuxiliares-cov: LDFLAGS += -lcunit
TComandosLogicaAuxiliares-cov: $(TESTCLAUX_SRC)
	$(CC) $(COV_CFLAGS) -o $@ $(TESTCLAUX_SRC) $(LDFLAGS)

coverage: TAuxiliares-cov TComandosLogicaAuxiliares-cov
	./TAuxiliares-cov
	./TComandosLogicaAuxiliares-cov
	gcov -b Auxiliares.c ComandosLogicaAuxiliares.c

clean:
	rm -f *.o *.gcda *.gcno *.gcov \
	       $(EXEC) TAuxiliares TComandosLogicaAuxiliares \
	       TAuxiliares-cov TComandosLogicaAuxiliares-cov