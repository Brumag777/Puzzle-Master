CC = gcc
BASE_FLAGS = -Wall -Wextra -pedantic -O1 -g
SANITIZE_FLAGS = -fsanitize=address -fno-omit-frame-pointer
COVERAGE_FLAGS = --coverage
CFLAGS = $(BASE_FLAGS) $(SANITIZE_FLAGS) $(COVERAGE_FLAGS)
LDFLAGS = -lcunit

SRC = MemoryManagement.c Lista.c Auxiliares.c Comandos.c ComandosLogica.c ComandosLogicaA.c
OBJ = $(SRC:.c=.o)
TEST_OBJ = Testes.o $(OBJ)
MAIN_OBJ = Main.o $(OBJ)

all: Jogo

Jogo: $(MAIN_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

Testes: $(TEST_OBJ)
	$(CC) $(CFLAGS) -DTESTING -o $@ $^ $(LDFLAGS)
	./Testes
	gcov -b -c Lista.c Auxiliares.c ComandosLogica.c ComandosLogicaA.c

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f Jogo Testes *.o *.gcov *.gcda *.gcno