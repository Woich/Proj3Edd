#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct lista{
    char nome[30];
    int *posicao, numAparece;
    struct lista *proximo,
                 *anterior;
}Lista;

typedef struct head{
    struct lista *primeiro,
                 *ultimo;
    long int qtdElementos;
}Header;

void geraArqIver(Header *baseLista){

    //ContTempo temFuncao;
    FILE *file=fopen("Historia.txt", "r");
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

                    //Caso tenha uma palavra igual já cadastrada;
                    if(retornoComp == 0){

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
                        comparador=comparador->proximo;
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
    }

    fclose(file);

}

void geraVetor(Lista **vetor, Header *baseLista){

    int i;
    //Esse é o elemento que será adicionado ná posição do vetor;
    Lista *eleAdicionado = baseLista->primeiro;

    //Esse for serve para arrumas todas as referencias de todos os pontos do vetor
    for(i=0 ; i<baseLista->qtdElementos ; i++){

        if(i == 0){

            //Aloca a memória
            vetor[i] = malloc(sizeof(Lista));
            //Adiciona a referência
            vetor[i] = eleAdicionado;
            //Muda elemento a er adicionado
            eleAdicionado = eleAdicionado->proximo;

        }
        else if(i == baseLista->qtdElementos-1){

            //Aloca a memória
            vetor[i] = malloc(sizeof(Lista));
            //Adiciona a referência
            vetor[i] = eleAdicionado;
            //Não altera por não ter próximo elemento

        }
        else{
            //Aloca a memória
            vetor[i] = malloc(sizeof(Lista));
            //Adiciona a referência
            vetor[i] = eleAdicionado;
            //Muda elemento a er adicionado
            eleAdicionado = eleAdicionado->proximo;
        }

    }
}

void quickSortLista(Header *lista, Lista **vetorPont, int iniComp, int fimComp){//Esse possui inicio e fim do vetor para limitadores
    int i;//'i' e 'j' são controladores de loops, enquanto o pivo é uma medida para a organização
    Lista *pontAux, *pivo;//Ponteiro Auxiliar
    int posPivo, delimit;

    //Se inicia caso seja possível com inicio e fim sendo diferentes e o inicio sendo menor
    if(iniComp < fimComp){

        posPivo = fimComp;
        pivo = vetorPont[posPivo];

        //Delimitador que será usado para fazer a secção para as próximas chamadas da função
        delimit = iniComp;

        //Roda o vetor
        for(i=iniComp; i<fimComp ; i++){

            //Caso a string seja menor que o pivo e o 'i' não seja delimit para evitar uma troca de elemento com ele mesmo
            if(strcmp(vetorPont[i]->nome, pivo->nome) <= 0 ){
                //Realizamos a troca
                pontAux = vetorPont[i];

                vetorPont[i] = vetorPont[delimit];

                vetorPont[delimit] = pontAux;

                //Para limpar o auxiliar;
                pontAux = 0;

                //Aumenta a posição do delimit
                delimit++;

            }
        }

        //Realiza a troca do pivo

        pontAux = vetorPont[fimComp];

        vetorPont[fimComp] = vetorPont[delimit];

        vetorPont[delimit] = pontAux;

        //Organiza as partes
        quickSortLista(lista, vetorPont, iniComp, delimit-1);
        quickSortLista(lista, vetorPont, delimit+1, fimComp);

    }
}

void imprimeArquivoIver(Lista **arquivoIver, Header *baseLista){
    int i, j;

    for(i=0; i<baseLista->qtdElementos; i++){

        printf("%d:%s - ", i+1, arquivoIver[i]->nome);

        for(j=0 ; j<arquivoIver[i]->numAparece ; j++){

            printf("%d,", arquivoIver[i]->posicao[j]);
        }

        printf("\n\n");

    }
}

int pesquisaBinaria(Lista **vetorArquivoInver, int tamArquivo){

    int posicao,//posição a ser avaliada
        inicio,//pisião inicial da lista ser avaliada
        fim,// posição final da lista a ser avaliada
        retorno;

    char palavra[30];

    printf("Digite a Palavra Buscada: ");
    scanf("%s", palavra);
    printf("\n");

    inicio=0;
    fim=tamArquivo;

    while(inicio <= fim){
        posicao = (fim + inicio)/2;

        retorno = strcmp(palavra, vetorArquivoInver[posicao]);

        //caso ache pare o loop
        if(retorno == 0){
            break;
        }

        if(retorno > 0){
            inicio = posicao+1;
        }
        else{
            fim = posicao-1;
        }
    }
    //Retorno utilizado para a parte da impressão
    if(inicio>fim){
        return -1;
    }
    else{
        return posicao;
    }

}

void imprimePalavraAchada(int posicaoAchada, Lista **vetorPalavras){
    if(posicaoAchada != -1){//Se foi encontrado a palavra no arquivo invertido
        printf("Palavar: %s | Numero de Aparicoes: %d\n\n", vetorPalavras[posicaoAchada]->nome, vetorPalavras[posicaoAchada]->numAparece);
    }
    else{
        printf("Palavra não encontrada!\n");
    }
}

void posicaoTexto(int posicaoAchada, Lista **vetorPalavras){

    FILE *file=fopen("Historia.txt", "r");
    char linInicial[600],*linTemp, *strPart;
    char delimit[]=" .,;:!?";
    Lista *registro, *comparador;
    int i=0,  proximo = 1, posicaoTxt, j, difTam, proxLin=0;
    long int numChar=1;

    fgets(linInicial, 600, file);

    //Posicao no texto da palavra
    posicaoTxt = vetorPalavras[posicaoAchada]->posicao[i];

    //Proximo é o controlador a ser usado para saber se é ou não para imprimir o a próxima aparição
    while(proximo != 0){

        //Caso não esteja na linha atual, mudamos ela para ser avaliado em um novo vetor
        if(posicaoTxt > strlen(linInicial)){
            fgets(linInicial, 600, file);
            posicaoTxt = posicaoTxt - strlen(linInicial);
            proxLin = 1;//Variavel que controla necessidade de aparecer o menu de próxima palavra
        }
        else{
            //Caso seja a primeira palavra da linha
            if(posicaoTxt == 1){
                //Mostra a aparição
                printf("Aparicao : %d | Posicao: %d\n\n", i+1, vetorPalavras[posicaoAchada]->posicao[i]);
                printf("(...)   ");

                //Para imprimir os 50 primeiros caracteres
                for(j=0 ; j<100 ; j++){
                    printf("%c", linInicial[j]);
                }
                printf("   (...)\n\n");
            }
            //Caso seja o ultimo elemento da lista;
            else if(posicaoTxt == strlen(linInicial)){

                printf("Aparicao : %d | Posicao: %d\n\n", i+1, vetorPalavras[posicaoAchada]->posicao[i]);
                printf("(...)   ");

                //Para imprimir os 50 primeiros caracteres
                for(j=posicaoTxt-100 ; j<posicaoTxt ; j++){
                    printf("%c", linInicial[j]);
                }
                printf("   (...)\n\n");
            }
            else{
                //Caso tenha menos de 50 caracteres para o fim da frase
                if(strlen(linInicial) - posicaoTxt < 50){

                    difTam = strlen(linInicial) - posicaoTxt;

                    printf("Aparicao : %d | Posicao: %d\n\n", i+1, vetorPalavras[posicaoAchada]->posicao[i]);
                    printf("(...)   ");

                    //Para imprimir os 50 primeiros caracteres.Equanto 'j' for menor que uma ditancia que permita imprimir o fianl da lista sem atingir memória inexistente
                    for(j= posicaoTxt-50-difTam ; j<posicaoTxt+difTam ; j++){
                        printf("%c", linInicial[j]);
                    }
                    printf("   (...)\n\n");

                }
                //Caso tenha menos de 50 carcteres até o inicio do texto
                else if(posicaoTxt < 50){
                    difTam = posicaoTxt;

                    printf("Aparicao : %d | Posicao: %d\n\n", i+1, vetorPalavras[posicaoAchada]->posicao[i]);
                    printf("(...)   ");

                    //Para imprimir os 100 caracteres a volta da palavra.Equanto 'j' for menor que uma ditancia que permita imprimir desde o inicio lista sem atingir memória inexistente
                    for(j= 0 ; j<posicaoTxt+difTam ; j++){
                        printf("%c", linInicial[j]);
                    }
                    printf("   (...)\n\n");
                }
                else{
                    printf("Aparicao : %d | Posicao: %d\n\n", i+1, vetorPalavras[posicaoAchada]->posicao[i]);
                    printf("(...)   ");

                    //Para imprimir os 100 caracteres a volta da palavra
                    for(j= posicaoTxt-50 ; j<posicaoTxt+50 ; j++){
                        printf("%c", linInicial[j]);
                    }
                    printf("   (...)\n\n");
                }

            }

            proxLin = 0;

        }

        if(proxLin != 1){
            printf("Deseja ver proxima aparicao?\n"
                   "(01)Sim\n"
                   "(00)Nao\n");
            scanf("%d", &proximo);
            i++;

            if(i == vetorPalavras[posicaoAchada]->numAparece){
                i=0;
            }

            if(proximo == 1){
                posicaoTxt = vetorPalavras[posicaoAchada]->posicao[i];
            }
            else{
                break;
            }
        }

    }

    fclose(file);

}

int main(){

    int opcAcao=0, cont, posicaoBusca;
    Lista **arquivoInvertido;
    Header arquivoTemp;

    while(opcAcao != -1){

        printf("+----------------------------+\n"
               "|    ESCOLHA SUA ACAO        |\n"
               "|   (01)Ler arquivo          |\n"
               "|   (02)Imprimir arquivo     |\n"
               "|   (03)Buscar Nova Palavra  |\n"
               "|   (-1)Sair                 |\n"
               "+----------------------------+\n");
        scanf("%d", &opcAcao);


        switch(opcAcao){

        case 1:geraArqIver(&arquivoTemp);
               //Essa opção serve para gerar um vetor de ponteiros que é uma ferramenta mais fácil de se trabalhar;
               arquivoInvertido = malloc(arquivoTemp.qtdElementos * sizeof(Lista));
               geraVetor(arquivoInvertido, &arquivoTemp);
               quickSortLista(&arquivoTemp, arquivoInvertido, 0, arquivoTemp.qtdElementos-1);
               break;

        case 2:printf("\e[H\e[2J");//Referência On-line de forma de apagar a tela em linux.
               imprimeArquivoIver(arquivoInvertido, &arquivoTemp);
               break;

        case 3:printf("\e[H\e[2J");//Referência On-line de forma de apagar a tela em linux.
               posicaoBusca = pesquisaBinaria(arquivoInvertido, arquivoTemp.qtdElementos-1);
               imprimePalavraAchada(posicaoBusca, arquivoInvertido);
               posicaoTexto(posicaoBusca, arquivoInvertido);
               printf("\e[H\e[2J");
               break;

        }
    }


}
