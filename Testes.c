#include "Puzzle.h"
#include "FTestes/TLista.c"
#include "FTestes/TAuxiliares.c"
#include "FTestes/TComandosLogica.c"
#include "FTestes/TComandosLogicaA.c"
#include "FTestes/TComandosLogicaAA.c"
#include "FTestes/TComandosRestricoes.c"

// Função principal
int main () {

    CU_initialize_registry ();

    CU_pSuite suite = CU_add_suite ("Testes", NULL, NULL);

    testesLista (suite);
    testesAuxiliares (suite);
    testesComandosLogica (suite);
    testesComandosLogicaA (suite);
    testesComandosLogicaAA (suite);
    testesComandosRestricoes (suite);

    CU_basic_set_mode (CU_BRM_VERBOSE);
    CU_basic_run_tests ();
    CU_cleanup_registry ();

    return 0;
}