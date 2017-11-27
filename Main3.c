#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct lista{
    char nome[30];
    int *posicao, numAparece;
    struct encad *proximo,
                 *anterior;
}Lista;

typedef struct head{
    struct lista *primeiro,
                 *ultimo;
    long int qtdElementos;
}Header;

void geraArqIver(Header *baseLista){

    //ContTempo temFuncao;
    FILE *file=fopen("Historia.txt", "r");;
    char linInicial[600],*linTemp, *strPart;
    char delimit[]=" .,;:!?";
    Lista *registro, *comparador;
    int i, retornoComp, retornoVazio, retornoTrave, visao, visao2;
    long int numChar=1;

    fgets(linInicial, 600, file);
    baseLista->qtdElementos = 0;



    while(linInicial[0] != '\0'){

        //Pega a palavra a ser avaliada;
        linTemp = linInicial;
        strPart = strsep(&linTemp, delimit);

        while(strPart[0] != '\n'){



            if(numChar == 1){
                //Aloca Memoria
                registro = malloc(sizeof(Lista));
                //Copia as informações da palavra
                strcpy(registro->nome, strPart);

                //Arruma vezes que apareceu e posição
                registro->posicao = (int*)malloc(10*sizeof(int));
                registro->numAparece=0;
                registro->posicao[registro->numAparece] = numChar;
                registro->numAparece = registro->numAparece+1;

                //Corrige referencias
                registro->anterior = 0;
                registro->proximo = 0;

                //Corrige Refencias do arquivo Base
                baseLista->primeiro = registro;
                baseLista->ultimo = registro;
                baseLista->qtdElementos = 1;

                //Adiciona o número de posições usadas.
                numChar = 1+strlen(strPart);
            }

            else{
                comparador = baseLista->primeiro;
                //Loop para verificar se palavra ainda não foi cadastrada;
                for(i=0 ; i<baseLista->qtdElementos ;i++){
                    retornoComp = strcmp(strPart, comparador->nome);
                    comparador=comparador->proximo;
                    visao = baseLista->qtdElementos;

                    //Caso tenha uma palavra igual já cadastrada;
                    if(retornoComp == 0){

                        visao2 = comparador->numAparece;

                        //Caso já tenha o tamanho do vetor base da struct
                        if(comparador->numAparece >= 10){
                            //Realoca a memoria para poder adicionar novo elemento;
                            comparador->posicao = (int*)realloc(comparador->posicao, (comparador->numAparece+1) * sizeof(int));
                            //Guarda nova posicao;
                            comparador->posicao[comparador->numAparece] = numChar;
                            //Adiciona um novo contador
                            comparador->numAparece = comparador->numAparece+1;
                        }

                        else{
                            //Guarda nova posicao;
                            comparador->posicao[comparador->numAparece] = numChar;
                            //Adiciona um novo contador
                            comparador->numAparece = comparador->numAparece+1;

                        }

                        break;


                    }
                    else{
                         continue;
                    }

                }

                //Cadastro que será feito caso nada seja achado uma palavra igual cadastrada;
                if(i==baseLista->qtdElementos && retornoComp != 0){

                    retornoTrave = strcmp(strPart, "-");
                    retornoVazio = strcmp(strPart, "");

                    if(retornoVazio == 0){
                        strPart = strsep(&linTemp, delimit);
                        continue;
                    }

                    else if(retornoTrave == 0){
                        strPart = strsep(&linTemp, delimit);
                        numChar++;
                        continue;
                    }

                    else{
                        //Aloca Memoria
                        registro = malloc(sizeof(Lista));
                        //Copia as informações da palavra
                        strcpy(registro->nome, strPart);

                        //Arruma vezes que apareceu e posição
                        registro->posicao = (int*)malloc(10*sizeof(int));
                        registro->numAparece=0;
                        registro->posicao[registro->numAparece] = numChar;
                        registro->numAparece = registro->numAparece+1;

                        //Corrige referencias
                        registro->anterior = baseLista->ultimo;
                        baseLista->ultimo->proximo = registro;
                        registro->proximo = 0;

                        //Corrige Refencias do arquivo Base
                        baseLista->ultimo = registro;
                        baseLista->qtdElementos = baseLista->qtdElementos + 1;
                    }

                }

                //O mais 1 vem da contagem da existencia de um espaço a mais
                numChar = numChar+1+strlen(strPart);

            }

            strPart = strsep(&linTemp, delimit);
        }

        linInicial[0] = '\0';
        fgets(linInicial, 600, file);
        printf(".");
    }

}

int main(){

    int opcAcao=0, cont;
    char palavra[]="Nulo";
    Lista **arquivoInvertido;
    Header arquivoTemp;

    while(opcAcao != -1){

        printf("Esolha Sua Ação\n");
        printf("(1)Ler arquivo\n");
        printf("(-1)Sair\n");
        scanf("%d", &opcAcao);


        switch(opcAcao){

        case 1:geraArqIver(&arquivoTemp);break;

        }
    }


}
