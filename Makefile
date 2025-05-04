CC      = gcc
CFLAGS  = -Wall -Wextra -pedantic -O1 -fsanitize=address -fno-omit-frame-pointer -g
COV_CFLAGS = -Wall -Wextra -pedantic -O1 -fprofile-arcs -ftest-coverage -g

GAME_SRC    = Main.c MemoryManagement.c Lista.c Auxiliares.c Comandos.c ComandosLogica.c ComandosLogicaAuxiliares.c

TESTAUX_SRC       = TAuxiliares.c Auxiliares.c Comandos.c ComandosLogica.c ComandosLogicaAuxiliares.c Lista.c MemoryManagement.c
TESTCLAUX_SRC     = TComandosLogicaAuxiliares.c Auxiliares.c Comandos.c ComandosLogica.c ComandosLogicaAuxiliares.c Lista.c MemoryManagement.c
TESTLOGICA_SRC    = TComandosLogica.c Auxiliares.c Comandos.c ComandosLogica.c ComandosLogicaAuxiliares.c Lista.c MemoryManagement.c
TESTLISTA_SRC     = TLista.c Auxiliares.c Comandos.c ComandosLogica.c ComandosLogicaAuxiliares.c Lista.c MemoryManagement.c

EXEC            = PuzzleMaster

.PHONY: all Jogo Testes TAuxiliares TComandosLogicaAuxiliares TComandosLogica coverage clean

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

TComandosLogica: LDFLAGS += -lcunit
TComandosLogica: $(TESTLOGICA_SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(TESTLOGICA_SRC)
	./$@

TLista: LDFLAGS += -lcunit
TLista: $(TESTLISTA_SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(TESTLISTA_SRC)
	./$@

clean:
	rm -f *.o *.gcda *.gcno *.gcov \
	       $(EXEC) TAuxiliares TComandosLogicaAuxiliares TComandosLogica TLista