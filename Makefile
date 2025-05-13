CC = gcc
BASE_FLAGS = -Wall -Wextra -pedantic -O1 -g
SANITIZE_FLAGS = -fsanitize=address -fno-omit-frame-pointer
COVERAGE_FLAGS = --coverage
CFLAGS = $(BASE_FLAGS) $(SANITIZE_FLAGS) $(COVERAGE_FLAGS)
LDFLAGS = -lcunit

SRC = Memory/MemoryManagement.c Memory/Lista.c Logica/Auxiliares.c Interface/Comandos.c Logica/ComandosLogica.c Logica/ComandosLogicaA.c Interface/Tab.c
OBJ = $(SRC:.c=.o)
TEST_OBJ = Testes.o $(OBJ)
MAIN_OBJ = Main.o $(OBJ)

all: PuzzleMaster

PuzzleMaster: $(MAIN_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

Testes: $(TEST_OBJ)
	$(CC) $(CFLAGS) -DTESTING -o $@ $^ $(LDFLAGS)
	./Testes
	gcov -b -c Memory/Lista.c Logica/Auxiliares.c Logica/ComandosLogica.c Logica/ComandosLogicaA.c | grep -A 3 "File 'Memory/Lista.c'"
	gcov -b -c Memory/Lista.c Logica/Auxiliares.c Logica/ComandosLogica.c Logica/ComandosLogicaA.c | grep -A 3 "File 'Logica/Auxiliares.c'"
	gcov -b -c Memory/Lista.c Logica/Auxiliares.c Logica/ComandosLogica.c Logica/ComandosLogicaA.c | grep -A 3 "File 'Logica/ComandosLogica.c'"
	gcov -b -c Memory/Lista.c Logica/Auxiliares.c Logica/ComandosLogica.c Logica/ComandosLogicaA.c | grep -A 3 "File 'Logica/ComandosLogicaA.c'"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f Jogo Testes *.o *.gcov *.gcda *.gcno \
		              Logica/*.o Logica/*.gcov Logica/*.gcda Logica/*.gcno \
	                  Interface/*.o Interface/*.gcov Interface/*.gcda Interface/*.gcno \
					  Memory/*.o Memory/*.gcov Memory/*.gcda Memory/*.gcno \
					  TLogica/*.o Principais/*.gcov TLogica/*.gcda TLogica/*.gcno