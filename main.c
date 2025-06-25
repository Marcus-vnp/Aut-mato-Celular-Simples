#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // para usar a função USLEEP
#include <errno.h> // para usar o tipo FILE e a função ACCESS 
#include <conio.h> // para fazer a verificação se uma tecla foi apertada (no final do código)

#define TAM 10 // TAMANHO DO VETOR QUE ARMAZENARÁ AS CELULAS

typedef struct{
    // VARIAVEL QUE DEFINE O ESTADO ATUAL DA CELULA (VIVA OU MORTA) E O PRÓXIMO ESTADO QUE ELA ESTARÁ NA PRÓXIMA GERAÇÃO
    int estado, proximoEstado;
}celula; // ESTRUTURA DAS VARIAVEIS QUE REPRESENTAM AS CELULAS

void criar_placar(){ // FUNÇÃO QUE CRIA O PLACAR
    const char *arq_nome = "placar.txt";
    FILE *arq_placar;

    if (access(arq_nome, F_OK) == 0){
        printf("");
    }else{
        arq_placar = fopen("placar.txt", "w");
        if (access(arq_nome, F_OK) == 0){
            fclose(arq_placar);
        }else{
            printf("HOUVE UM PROBLEMA E O PLACAR NÃO FOI CRIADO\n\n");
        }
    }
}
void inserir_jogador(char nome[], int gen){ // FUNÇÃO QUE INSERE O NOME DO JOGADOR E SUA GERAÇÃO MAXIMA ALCANÇADA NO PLACAR
    FILE *arq_placar;

    arq_placar = fopen("placar.txt", "a");

    if (arq_placar == NULL){
        printf("ERRO AO EDITAR PLACAR\n\n");
    }else{
        fprintf(arq_placar, "%s%i\n", nome, gen);
        fclose(arq_placar);
    }
}
void mostrar_placar(){ // FUNÇÃO QUE IMPRIME O PLACAR DO JOGO
    FILE *arq_placar;
    char linha[70];
    char linha1[70];
    char linha2[70];
    int contador_linhas = 0;

    arq_placar = fopen("placar.txt", "r");

    while (fgets(linha, sizeof(linha), arq_placar) != NULL) {
        contador_linhas++;
    }

    fclose(arq_placar);

    arq_placar = fopen("placar.txt", "r");

    if (arq_placar == NULL){
        printf("NAO FOI POSSIVEL MOSTRAR O PLACAR");
    }else{
        for(int i = 0; i < contador_linhas; i++){
            if (fgets(linha1, sizeof(linha1), arq_placar) == NULL) {
                linha1[0] = '\0';
            }
            if (fgets(linha2, sizeof(linha2), arq_placar) == NULL) {
                linha2[0] = '\0';
            }

            linha1[strcspn(linha1, "\n")] = '\0';
            linha2[strcspn(linha2, "\n")] = '\0';

            printf("%s\t:\t%s\n", linha1, linha2);
        }

    }
}

void menu_do_jogo(celula matriz[TAM][TAM], char nome[]){ // FUNÇÃO QUE PERMITE O JOGADOR DEFINIR O ESTADO INICIAL DE CADA CELULA
    int matrizExemplo[10][10] = {
    {1, 0, 1, 0, 1, 1, 0, 0, 1, 0},
    {0, 1, 0, 1, 0, 0, 1, 1, 0, 1},
    {1, 1, 0, 0, 1, 0, 1, 0, 1, 0},
    {0, 0, 1, 0, 1, 1, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 1, 1, 1, 0, 0},
    {0, 1, 1, 0, 0, 0, 1, 0, 1, 1},
    {1, 1, 0, 1, 0, 1, 0, 0, 1, 0},
    {0, 0, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 1, 0, 1, 0, 1, 0, 0},
    {0, 1, 0, 0, 1, 0, 1, 0, 1, 1}
};
    char opcao = '\0'; // variavel que armazena as decisoes do jogador no menu

    criar_placar();

    printf("-----BEM VINDO AO JOGO DA VIDA-----\n");

    printf("\n\nDigite seu nome para comecar: ");
    fgets(nome, 50, stdin);

    system("cls");

    printf("       BEM VINDO %s", nome);
    printf("Voce deseja jogar ou olhar o placar?\n");
    printf("Digite 'j' para jogar ou 'p' para ir para o placar!");
    while(opcao != 'j'){
        printf("\ndigite aqui: ");

        while ((opcao = getchar()) == '\n');
        if(opcao != 'j' && (opcao != 'j' && opcao != 'p')){
            printf("incorreto, tente novamente");
        }

        system("cls");

        if (opcao == 'p'){ // MOSTRA O PLACAR PARA O JOGADOR
            while(opcao != 's'){
            printf("NOME\t:\tGeracaoMaxima\n\n");

            mostrar_placar();

            printf("\n\nCaso queira voltar ao menu, digite 's'");
            while(opcao != 's'){

                printf("\ndigite: ");
                while ((opcao = getchar()) == '\n');
                if(opcao != 's'){
                    printf("\nincorreto, tente novamente");
                }
            }

            system("cls");

            printf("       BEM VINDO %s", nome);
            printf("Voce deseja jogar ou olhar o placar?\n");
            printf("Digite 'j' para jogar ou 'p' para ir para o placar!");
        }
        }
    }

    system("cls");

    printf("-----BEM VINDO AO JOGO DA VIDA-----");
    printf("\n\nPARA COMECAR, VAMOS DEFINIR OS ESTADOS DE CADA CELULA DO JOGO\n");
    printf("\nSAO %i LINHAS E %i COLUNAS\n", TAM, TAM);
    printf("0 -> MORTO\n1 -> VIVO");
    printf("\nEXEMPLO:\n\n");
    for (int i = 0; i < TAM; i++){
        printf("\t");
        for (int o = 0; o < TAM; o++){
            printf("%i ", matrizExemplo[i][o]);
        }
        printf("\n");
    }

    printf("\nVOCE DESEJA USAR A MATRIZ DE EXEMPLO OU DEFINIR OS ESTADOS MANUALMENTE?\n");
    printf("digite 'm' para definir manualmente\ndigite 'n' para usar a matriz de exemplo\n");
    while(opcao != 'm' && opcao != 'n'){
        printf("digite: ");
        while ((opcao = getchar()) == '\n');
        if(opcao != 'm' && (opcao != 'm' && opcao != 'n')){
            printf("incorreto, tente novamente\n");
        }
    }
    if (opcao == 'm'){
        printf("\nDIGITE AQUI EM BAIXO:\n");

        for (int i = 0; i < TAM; i++){ // pede 10 valores (0 ou 1) 10 vezes, 0 para morto e 1 para vivo
            printf("\t");
            scanf("%i %i %i %i %i %i %i %i %i %i", &matriz[i][0].estado, &matriz[i][1].estado, &matriz[i][2].estado, &matriz[i][3].estado, &matriz[i][4].estado, &matriz[i][5].estado, &matriz[i][6].estado, &matriz[i][7].estado, &matriz[i][8].estado, &matriz[i][9].estado);
        }

        system("cls");
    }else{
        for (int i = 0; i < TAM; i++){
            for (int o = 0; o < TAM; o++){
                matriz[i][o].estado = matrizExemplo[i][o];
            }
        }
        system("cls");
    }


}

void mostrar_matriz(celula matriz[TAM][TAM]){ // MOSTRA A MATRIZ
    for (int i = 0; i < 35; i++){
        printf("-");
    }
    printf("\n");
    for (int i = 0; i < 4; i++){
        printf("|\t\t\t\t  |\n");
    }
    for (int i = 0; i < TAM; i++){
        printf("|\t");
        for (int o = 0; o < TAM; o++){
            printf("%i ", matriz[i][o].estado);
        }
        printf("\t   \b|\n");
    }
    for (int i = 0; i < 4; i++){
        printf("|\t\t\t\t  |\n");
    }
    for (int i = 0; i < 35; i++){
        printf("-");
    }
}

void define_proximo_estado(int vm, int vv, int pos_i, int pos_o, celula matriz[TAM][TAM]){ // FUNÇÃO QUE DEFINE O PROXIMO ESTADO DA GERAÇÃO
    if(matriz[pos_i][pos_o].estado == 0){ // CASO ESTEJA MORTO
        if (vv == 3){ // SE TIVER 3 VIZINHOS VIVOS, SEU PROXIMO ESTADO SERÁ VIVA, DO CONTRÁRIO, CONTINUA MORTA
            matriz[pos_i][pos_o].proximoEstado = 1;
        }else{
            matriz[pos_i][pos_o].proximoEstado = 0;
        }
    }else{ // CASO ELA ESTEJA VIVA
        if (vv == 2 || vv == 3){ // SE TIVER 2 OU 3 VIZINHOS VIVOS, SEU PRÓXIMO ESTADO SERÁ VIVA, DO CONTRÁRIO, IRÁ MORRER
            matriz[pos_i][pos_o].proximoEstado = 1;
        }else{
            matriz[pos_i][pos_o].proximoEstado = 0;
        }
    }
}

void verificao(celula matriz[TAM][TAM]){ // FUNÇÃO QUE VERIFICA AS CELULAS E SEUS REQUISITOS PARA PROXIMA GERAÇÃO
    // uma variavel para contar os vizinhos vivos da celula e outra para contar os mortos
    int viz_vivos, viz_mortos;


    for(int i = 0; i < TAM; i++){ // ESQUEÇA
        for(int o = 0; o < TAM; o++){ // ESQUEÇA
            viz_vivos = 0;
            viz_mortos = 0;
            if (i > 0 && i < (TAM - 1)){
                if (o > 0 && o < (TAM - 1)){ // VERIFICA AS CELULAS DO INTERIOR
                    if (matriz[i - 1][o - 1].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                    if(matriz[i - 1][o].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                    if(matriz[i - 1][o + 1].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                    if(matriz[i][o + 1].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                    if(matriz[i + 1][o + 1].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                    if(matriz[i + 1][o].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                    if(matriz[i + 1][o - 1].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                    if(matriz[i][o - 1].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                }else if (o == 0 || o == (TAM - 1)){ // VERIFICA AS CELULAS DA ARESTA ESQUERDA E DIREITA
                    if(matriz[i - 1][o].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                    if(matriz[i + 1][o].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                    if (o == 0){
                        if(matriz[i - 1][o + 1].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                        if(matriz[i][o + 1].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                        if(matriz[i + 1][o + 1].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                    }else{
                        if(matriz[i - 1][o - 1].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                        if(matriz[i][o - 1].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                        if(matriz[i + 1][o - 1].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                    }
                }
            }else if(i == o){ // VERIFICA A VERTICE SUPERIOR ESQUERDA E INFERIOR DIREITA
                if (i == 0){
                    if (matriz[i][o + 1].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                    if (matriz[i + 1][o + 1].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                    if (matriz[i + 1][o].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                }else{
                    if (matriz[i][o - 1].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                    if (matriz[i - 1][o - 1].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                    if (matriz[i - 1][o].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                }
            }else if (i != o){
                if (o > 0 && o < (TAM - 1)){ // VERIFICA A ARESTA SUPERIOR E INFERIOR
                    if(matriz[i][o - 1].estado == 0){
                        viz_mortos++;
                   }else{
                        viz_vivos++;
                   }
                   if(matriz[i][o + 1].estado == 0){
                        viz_mortos++;
                   }else{
                        viz_vivos++;
                   }
                   if (i == 0){
                        if(matriz[i + 1][o - 1].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                        if(matriz[i + 1][o].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                       if(matriz[i + 1][o + 1].estado == 0){
                            viz_mortos++;
                       }else{
                            viz_vivos++;
                       }
                   }else{
                        if(matriz[i - 1][o - 1].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                        if(matriz[i - 1][o].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                       if(matriz[i - 1][o + 1].estado == 0){
                            viz_mortos++;
                       }else{
                            viz_vivos++;
                       }
                   }
                }else{ // VERIFICA A VERTICE SUPERIOR DIREITA E INFERIOR ESQUERDA
                   if (i == 0){
                        if(matriz[i][o - 1].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                        if(matriz[i + 1][o - 1].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                        if(matriz[i + 1][o].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                   }else{
                        if(matriz[i][o + 1].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                        if(matriz[i - 1][o + 1].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                        if(matriz[i - 1][o].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                   }
                }
            }
            define_proximo_estado(viz_mortos, viz_vivos, i, o, matriz);
        }
        printf("\n");
    }
}

void passar_geracao(celula matriz[TAM][TAM], int *gen){ // FUNÇÃO QUE SUBSTITUI O ESTADO ATUAL DAS CELULAS, PELOS SEUS ESTADOS FUTUROS
    for (int i = 0; i < TAM; i++){                      // E DEFINE COMO MORTO O PROXIMO ESTADO
        for (int o = 0; o < TAM; o++){                  // ISSO E INTERPRETADO COMO PASSAR UMA GERACAO
            matriz[i][o].estado = matriz[i][o].proximoEstado;  // TAMBÉM FAZ A CONTAGEM DAS GERAÇÕES
            matriz[i][o].proximoEstado = 0;

        }
    }
    *gen += 1;
}

void main(){
    celula jogo[TAM][TAM]; //  matriz onde ocorre as verificacoes e passadas de geracoes
    int geracao = 0; // armazena a contagem de geracoes que o jogo passa
    char nome[50]; // armazena o nome do jogador;
    menu_do_jogo(jogo, nome);

    while(1){ // LOOP INFINITO QUE MOSTRA O JOGO ATÉ O USUÁRIO FECHA-LO
        mostrar_matriz(jogo);

        printf("\n\nCONTAGEM DE GERACAO: %i", geracao);

        printf("\n\nO JOGO CONTINUA ATE FECHAR A JANELA OU APERTAR UMA TECLA DO TECLADO!");

        verificao(jogo);

        passar_geracao(jogo, &geracao);

        if (_kbhit()) { // VERIFICA SE ALGUMA TECLA FOI APERTADA
            char tecla = _getch();
            printf("ENCERRADO", tecla);
            break;
        }

        usleep(500000);

        system("cls");
    }

    inserir_jogador(nome, geracao);
}
