#include "Puzzle.h"
#include "FTestes/TLista.c"
#include "FTestes/TAuxiliares.c"
#include "FTestes/TComandosLogica.c"
#include "FTestes/TComandosLogicaA.c"

// Função principal
int main () {

    CU_initialize_registry ();

    CU_pSuite suite = CU_add_suite ("Testes", NULL, NULL);

    CU_add_test (suite, "logicaGravar", teste_logicaGravar);
    CU_add_test (suite, "logicaLer", teste_logicaLer);
    CU_add_test (suite, "logicaSair", teste_logicaSair);
    CU_add_test (suite, "logicaPintarCasa", teste_logicaPintarCasa);
    CU_add_test (suite, "logicaRiscarCasa", teste_logicaRiscarCasa);
    CU_add_test (suite, "logicaDesfazerJogada", teste_logicaDesfazerJogada);
    CU_add_test (suite, "logicaVisualizarHistorico", teste_logicaVisualizarHistorico);
    CU_add_test (suite, "logicaVerifica", teste_logicaVerifica);
    CU_add_test (suite, "logicaAjuda", teste_logicaAjuda);
    CU_add_test (suite, "logicaAjudaRep", teste_logicaAjudaRep);
    CU_add_test (suite, "logicaResolveJogo", teste_logicaResolveJogo);
    CU_add_test (suite, "logicaApagaHistorico", teste_logicaApagaHistorico);
    CU_add_test (suite, "logicaImprimePont", teste_logicaImprimePont);
    CU_add_test (suite, "logicaListarInfo", teste_logicaListarInfo);
    CU_add_test (suite, "logicaInfoComandos", teste_logicaInfoComandos);
    CU_add_test (suite, "logicaEliminarJogo", teste_logicaEliminarJogo);
    CU_add_test (suite, "logicaCriarJogo", teste_logicaCriarJogo);

    CU_add_test (suite, "guardaInfo", teste_guardaInfo);
    CU_add_test (suite, "guardaJogadas", teste_guardaJogadas);
    CU_add_test (suite, "leFicheiro", teste_leFicheiro);
    CU_add_test (suite, "leLinhaJogadas", teste_leLinhasJogadas);
    CU_add_test (suite, "verificaInfracoes", teste_verificaInfracoes);
    CU_add_test (suite, "verificaCaminhoOrtogonal", teste_verificaCaminhoOrtogonal);
    CU_add_test (suite, "ajudaUmaVez", teste_ajudaUmaVez);
    CU_add_test (suite, "resolve", teste_resolve);
    CU_add_test (suite, "preencheTabInfracoes", teste_preencheTabInfracoes);

    CU_add_test (suite, "addJogada", teste_addJogada);
    CU_add_test (suite, "remJogada", teste_remJogada);
    CU_add_test (suite, "inverteHistorico", teste_inverteHistorico);

    CU_add_test (suite, "visualizaUltimosTabuleiros", teste_visualizaUltimosTabuleiros);
    CU_add_test (suite, "realizaAlteracoesJogada", teste_realizaAlteracoesJogada);
    CU_add_test (suite, "formaJogada", teste_formaJogada);
    CU_add_test (suite, "eMaiuscula", teste_eMaiuscula);
    CU_add_test (suite, "eMinuscula", teste_eMinuscula);
    CU_add_test (suite, "coordenadaValida", teste_coordenadaValida);
    CU_add_test (suite, "tabuleiroValido", teste_tabuleiroValido);
    CU_add_test (suite, "jogadasValidas", teste_jogadasValidas);
    CU_add_test (suite, "verificaLinhas", teste_verificaLinhas);
    CU_add_test (suite, "verificaColunas", teste_verificaColunas);
    CU_add_test (suite, "verificaCasaVazia", teste_verificaCasaVazia);
    CU_add_test (suite, "contaLetrasLigadas", teste_contaLetrasLigadas);
    CU_add_test (suite, "testeJogo", teste_testeJogo);
    CU_add_test (suite, "adicionaJogada", teste_adicionaJogada);
    CU_add_test (suite, "riscaCasasAux", teste_riscaCasasAux);
    CU_add_test (suite, "riscaCasas", teste_riscaCasas);
    CU_add_test (suite, "percorreLinha", teste_percorreLinha);
    CU_add_test (suite, "percorreColuna", teste_percorreColuna);
    CU_add_test (suite, "pintaCasasAux", teste_pintaCasasAux);
    CU_add_test (suite, "pintaCasas", teste_pintaCasas);
    CU_add_test (suite, "testaPossibilidadesCasaAux", teste_testaPossibilidadesCasaAux);
    CU_add_test (suite, "testaPossibilidadesCasa", teste_testaPossibilidadesCasa);
    CU_add_test (suite, "procuraInfracoesL", teste_procuraInfracoesL);
    CU_add_test (suite, "procuraInfracoesC", teste_procuraInfracoesC);
    CU_add_test (suite, "procuraInfracoesV", teste_procuraInfracoesV);
    CU_add_test (suite, "formaNomeFicheiro", teste_formaNomeFicheiro);
    CU_add_test (suite, "valorPont", teste_valorPont);

    CU_basic_set_mode (CU_BRM_VERBOSE);
    CU_basic_run_tests ();
    CU_cleanup_registry ();

    return 0;
}