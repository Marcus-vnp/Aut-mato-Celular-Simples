#include <stdio.h>
#include <stdlib.h>

#define TAM 10 // TAMANHO DO VETOR QUE ARMAZENARÁ AS CELULAS

typedef struct{
    // VARIAVEL QUE DEFINE O ESTADO ATUAL DA CELULA (VIVA OU MORTA) E O PRÓXIMO ESTADO QUE ELA ESTARÁ NA PRÓXIMA GERAÇÃO
    int estado, proximoEstado;
}celula; // ESTRUTURA DAS VARIAVEIS QUE REPRESENTAM AS CELULAS

void definir_vetor(celula vetor[TAM][TAM]){ // FUNÇÃO QUE PERMITE O JOGADOR DEFINIR O ESTADO INICIAL DE CADA CELULA
    int vetorExemplo[10][10] = {
    {1, 0, 1, 1, 0, 0, 1, 0, 1, 0},
    {0, 1, 0, 1, 1, 0, 0, 1, 0, 1},
    {1, 1, 0, 0, 1, 0, 1, 1, 0, 0},
    {0, 0, 1, 0, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 1, 1, 0, 0, 0, 1, 1},
    {0, 1, 1, 0, 0, 1, 1, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 0, 0, 1, 0},
    {0, 1, 0, 0, 1, 0, 1, 1, 0, 1},
    {1, 1, 0, 1, 0, 1, 0, 1, 1, 0},
    {0, 0, 1, 0, 1, 0, 1, 0, 0, 1}
};

    printf("-----BEM VINDO AO JOGO DA VIDA-----\n");
    printf("PARA COMECAR, VAMOS DEFINIR OS ESTADOS DE CADA CELULA DO JOGO\n");
    printf("\nSAO %i LINHAS E %i COLUNAS\n", TAM, TAM);
    printf("ESCREVA ABAIXO O ESTADO DA CELULA EM SUA RESPECTIVA LINHA E COLUNA\n");
    printf("0 -> MORTO\n1 -> VIVO");
    printf("\nEXEMPLO:\n\n");
    for (int i = 0; i < TAM; i++){
        printf("\t");
        for (int o = 0; o < TAM; o++){

            printf("%i ", vetor[i][o].estado);
        }
        printf("\n");
    }
    printf("\nDIGITE AQUI EM BAIXO:\n");

    for (int i = 0; i < TAM; i++){ // pede 10 valores (0 ou 1) 10 vezes, 0 para morto e 1 para vivo
        printf("\t");
        scanf("%i %i %i %i %i %i %i %i %i %i", &vetor[i][0].estado, &vetor[i][1].estado, &vetor[i][2].estado, &vetor[i][3].estado, &vetor[i][4].estado, &vetor[i][5].estado, &vetor[i][6].estado, &vetor[i][7].estado, &vetor[i][8].estado, &vetor[i][9].estado);
    }

    system("cls");
}

void mostrar_vetor(celula vetor[TAM][TAM]){ // imprime os valores atuais do vetor
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
            printf("%i ", vetor[i][o].estado);
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

void define_proximo_estado(int vm, int vv, int pos_i, int pos_o, celula vetor[TAM][TAM]){
    if(vetor[pos_i][pos_o].estado == 0){ // CASO ESTEJA MORTO
        if (vv == 3){ // SE TIVER 3 VIZINHOS VIVOS, SEU PROXIMO ESTADO SERÁ VIVA, DO CONTRÁRIO, CONTINUA MORTA
            vetor[pos_i][pos_o].proximoEstado = 1;
        }else{
            vetor[pos_i][pos_o].proximoEstado = 0;
        }
    }else{ // CASO ELA ESTEJA VIVA
        if (vv == 2 || vv == 3){ // SE TIVER 2 OU 3 VIZINHOS VIVOS, SEU PRÓXIMO ESTADO SERÁ VIVA, DO CONTRÁRIO, IRÁ MORRER
            vetor[pos_i][pos_o].proximoEstado = 1;
        }else{
            vetor[pos_i][pos_o].proximoEstado = 0;
        }
    }
}

void verificao(celula vetor[TAM][TAM]){
    // uma variavel para contar os vizinhos vivos da celula e outra para contar os mortos
    int viz_vivos, viz_mortos;


    for(int i = 0; i < TAM; i++){ // ESQUEÇA
        for(int o = 0; o < TAM; o++){ // ESQUEÇA
            viz_vivos = 0;
            viz_mortos = 0;
            if (i > 0 && i < (TAM - 1)){
                if (o > 0 && o < (TAM - 1)){ // VERIFICA AS CELULAS DO INTERIOR
                    if (vetor[i - 1][o - 1].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                    if(vetor[i - 1][o].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                    if(vetor[i - 1][o + 1].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                    if(vetor[i][o + 1].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                    if(vetor[i + 1][o + 1].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                    if(vetor[i + 1][o].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                    if(vetor[i + 1][o - 1].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                    if(vetor[i][o - 1].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                }else if (o == 0 || o == (TAM - 1)){ // VERIFICA AS CELULAS DA ARESTA ESQUERDA E DIREITA
                    if(vetor[i - 1][o].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                    if(vetor[i + 1][o].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                    if (o == 0){
                        if(vetor[i - 1][o + 1].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                        if(vetor[i][o + 1].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                        if(vetor[i + 1][o + 1].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                    }else{
                        if(vetor[i - 1][o - 1].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                        if(vetor[i][o - 1].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                        if(vetor[i + 1][o - 1].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                    }
                }
            }else if(i == o){ // VERIFICA A VERTICE SUPERIOR ESQUERDA E INFERIOR DIREITA
                if (i == 0){
                    if (vetor[i][o + 1].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                    if (vetor[i + 1][o + 1].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                    if (vetor[i + 1][o].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                }else{
                    if (vetor[i][o - 1].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                    if (vetor[i - 1][o - 1].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                    if (vetor[i - 1][o].estado == 0){
                        viz_mortos++;
                    }else{
                        viz_vivos++;
                    }
                }
            }else if (i != o){
                if (o > 0 && o < (TAM - 1)){ // VERIFICA A ARESTA SUPERIOR E INFERIOR
                    if(vetor[i][o - 1].estado == 0){
                        viz_mortos++;
                   }else{
                        viz_vivos++;
                   }
                   if(vetor[i][o + 1].estado == 0){
                        viz_mortos++;
                   }else{
                        viz_vivos++;
                   }
                   if (i == 0){
                        if(vetor[i + 1][o - 1].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                        if(vetor[i + 1][o].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                       if(vetor[i + 1][o + 1].estado == 0){
                            viz_mortos++;
                       }else{
                            viz_vivos++;
                       }
                   }else{
                        if(vetor[i - 1][o - 1].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                        if(vetor[i - 1][o].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                       if(vetor[i - 1][o + 1].estado == 0){
                            viz_mortos++;
                       }else{
                            viz_vivos++;
                       }
                   }
                }else{ // VERIFICA A VERTICE SUPERIOR DIREITA E INFERIOR ESQUERDA
                   if (i == 0){
                        if(vetor[i][o - 1].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                        if(vetor[i + 1][o - 1].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                        if(vetor[i + 1][o].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                   }else{
                        if(vetor[i][o + 1].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                        if(vetor[i - 1][o + 1].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                        if(vetor[i - 1][o].estado == 0){
                            viz_mortos++;
                        }else{
                            viz_vivos++;
                        }
                   }
                }
            }
            define_proximo_estado(viz_mortos, viz_vivos, i, o, vetor);
        }
        printf("\n");
    }
}

void passar_geracao(celula vetor[TAM][TAM]){
    for (int i = 0; i < TAM; i++){
        for (int o = 0; o < TAM; o++){
            vetor[i][o].estado = vetor[i][o].proximoEstado;
            vetor[i][o].proximoEstado = 0;
        }
    }
}

void main(){
    celula jogo[TAM][TAM] = {
    {1, 0, 1, 1, 0, 0, 1, 0, 1, 0},
    {0, 1, 0, 1, 1, 0, 0, 1, 0, 1},
    {1, 1, 0, 0, 1, 0, 1, 1, 0, 0},
    {0, 0, 1, 0, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 1, 1, 0, 0, 0, 1, 1},
    {0, 1, 1, 0, 0, 1, 1, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 0, 0, 1, 0},
    {0, 1, 0, 0, 1, 0, 1, 1, 0, 1},
    {1, 1, 0, 1, 0, 1, 0, 1, 1, 0},
    {0, 0, 1, 0, 1, 0, 1, 0, 0, 1}
}; //  vetor onde ocorre as verificacoes e passadas de geracoes

    int ligado = 0; // TEMPORARIAS

    definir_vetor(jogo);

    while(ligado == 0){
        mostrar_vetor(jogo);

        verificao(jogo);

        // função pra passar geração

        passar_geracao(jogo);

        _sleep(500);

        system("cls");
    }
}
