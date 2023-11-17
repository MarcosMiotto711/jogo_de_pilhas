// 23004163 - Tiago Morais Neto
// 23004827 - Marcos do Amaral Miotto
// 23009817 - Gabriel de Araujo Rosa
// 23004610 - Gabriel Philippe de Oliveira Ferrari
#include <iostream>
#include <windows.h>
#include <time.h>
// O programa foi testado e está funcionando com varios tamanhos
#define TAM 6

using namespace std;

typedef int stack_element;

// O programa foi testado e está funcionando com ambas as bibliotecas "stack.h" e "stack_id.h"
#include "stack.h"

typedef struct{
    int numero_elementos;
    Stack pilha;
}Tubo;

// Função para declarar todas as pilhas de um array vazias
void iniciar_vazias(Tubo T[]){
    for(int i=0; i<TAM; i++){
        initStack(T[i].pilha);
        T[i].numero_elementos=0;
    }
}

// Função para distribuir os valores aleatoriamente entre as pilhas
void distribuir(Tubo T[]){
    int num, freq[TAM-1] = {0};
    srand(time(0));
    // for para gerar os numeros aleatórios até preencher todas as linhas
    for(int i=0; i<TAM-1; i++){
        // for para gerar os numeros aleatórios e adicionar em cada linha
        for(int p=1; p<TAM; p++){
            do{
                num = rand() % (TAM-1);
            }while(freq[num]>=(TAM-1));
            freq[num]++;
            push(T[p].pilha, num+1);
            T[p].numero_elementos++;
        }
    }
}

// Função para mudar a cor do terminal para imprimir as bolinhas de varias cores diferentes
void mudacor(int cor){
/*
0 = Preto       8 = Cinza
1 = Azul        9 = Azul Claro
2 = Verde       A = Verde Claro
3 = Verde-Agua  B = Verde-Agua Claro
4 = Vermelho    C = Vermelho Claro
5 = Roxo        D = Lilas
6 = Amarelo     E = Amarelo Claro
7 = Branco      F = Branco Brilhante
*/
    HANDLE Saida;
    Saida = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(Saida, cor);
    return;
}

// Função que chama a função mudacor e imprime as bolinhas segundo as cores especificadas
void printa_cor(int I){
    mudacor(I);
    cout << 'O';
    mudacor(15);
}

// Função que imprime as pilhas de forma organizada 
void mostrar(Tubo T[]){
    stack_element valor;
    Tubo aux[TAM];
    iniciar_vazias(aux);
    // Parte que passa de linha por linha, pega os valores, imprime e passa para as pilhas auxililiar
    // for que passa por cada linha
    for(int l=(TAM-1); l>0; l--){
        // for que passa por cada pilha
        for(int p=0; p<TAM; p++){
            cout << " | ";
            // Verifica se o tubo tem a quantidade de elemntos da linha (por exemplo, se tem 5 elementos ele
            // imprime na quinta linha)
            if((T[p].numero_elementos)==l){
                // Tira o valor do tubo correspondente a linha
                valor = pop(T[p].pilha);
                T[p].numero_elementos--;
                // Coloca esse valor na pilha auxiliar de indice igual
                push(aux[p].pilha, valor);
                aux[p].numero_elementos++;
                // Imprime a bolinha da cor correspondente
                printa_cor(valor);
                cout << " | ";
            // Caso não tenha elementos suficiente para imprimir na linha imprime o tubo vazio
            }else{
                cout << "  | ";
            }
        }
        cout << endl;
    }
    for(int i=0; i<TAM; i++){
        cout << " ----- ";
    }
    cout << endl;
    for(int i=0; i<TAM; i++){
        cout << "   "<< i+1 << "   ";
    }
    cout << endl << endl;
    // Parte que devolve os valores das pilhas auxiliares para as pilhas principais
    // for que passa por cada linha
    for(int l=TAM-1; l>0; l--){
        // for que passa por cada pilha
        for(int p=0; p<TAM; p++){
            if((aux[p].numero_elementos)==l){
                // tira o valor da auxiliar e guarda na variavel valor
                valor = pop(aux[p].pilha);
                aux[p].numero_elementos--;
                // passa o valor para a pilha principal
                push(T[p].pilha, valor);
                T[p].numero_elementos++;
            }
        }
    }
}

// Função que verifica se os indices de origem e destino são válidos para executar a jogada
int validar(Tubo T[], int o, int d){
    cout << endl;
    // Valida se o usuário colocou o mesmo destino e origem
    if(o==d){
        cout << "O VALOR DE ORIGEM E IGUAL AO DE DESTINO!\n";
        return 1;
    }
    // Valida se o usuário colocou um número que não representa uma das alternativas de origem
    if(o>TAM || o<0){
        cout << "O VALOR DE ORIGEM NAO E VALIDO!\n";
        return 1;
    }
    // Valida se o usuário colocou um número que não representa uma das alternativas de destino
    if(d>TAM || d<0){
        cout << "O VALOR DE DESTINO NAO E VALIDO!\n";
        return 1;
    }
    // Valida se o usuário escolheu um tubo de origem que não possui nenhum conteudo
    if(isEmpty(T[o-1].pilha)){
        cout << "O TUBO DE ORIGEM ESTA VAZIO!\n";
        return 1;
    }
    // Valida se o usuário escolheu um tubo de destino que já está cheio
    if((T[d-1].numero_elementos)>=TAM-1){
        cout << "O TUBO DE DESTINO ESTA CHEIO!\n";
        return 1;
    };
    // Caso não atenda nenhum dos requisitos a jogada pode ser executada
    return 0;
}

// Função que verifica se o a posição das bolinhas já está completa e se o jogo já está ganho
int validar_fim(Tubo T[]){
    stack_element valor;
    Tubo aux[TAM];
    iniciar_vazias(aux);
    // Executa os processos pra cada pilha
    for(int i=0; i<TAM; i++){
        // Verifica se a pilha tem menos de TAM-1 elementos (desconsiderando a pilha vazia), se não tiver não
        // é necessário verificar se são todos iguais
        if(T[i].numero_elementos<(TAM-1) && !isEmpty(T[i].pilha))return 0;
        // Executa o processo de verificação dentro das pilhas não vazias
        if(!isEmpty(T[i].pilha)){
            // Vetor que recebe os valores de cada pilha
            stack_element valores[TAM-1] = {0};
            // for que percorre cada valor de uma pilha
            for(int j=0; j<TAM-1; j++){
                // Tira da pilha original e guarda o valor na variavel "valor"
                valor = pop(T[i].pilha);
                // Passa o valor da variavel para a pilha auxiliar;
                push(aux[i].pilha, valor);
                // Adiciona o valor da variavel no array
                valores[j] = valor;
            }
            // Preenche a pilha original com os valores da pilha auxiliar
            for(int j=0; j<TAM-1;j++){
                valor = pop(aux[i].pilha);
                push(T[i].pilha, valor);
            }
            // verifica se os valores dentro do array são iguais entre si
            for(int j=0; j<TAM-1; j++){
                if(j){
                    if(valores[j]!=valores[0])return 0;
                }
            }
        }
    }
    // Se todas as condições estiverem correstas quer dizer que o jogo está ganho
    return 1;
}

// Função que chamas as funções de validação e executa a jogada
int jogada(Tubo T[]){
    int origem, destino;
    stack_element valor;
    // Chama a função que valida se o jogo está ganho sempre antes de fazer a jogada
    if(validar_fim(T))return 0;
    // do/while que executa o pedido de inserção de origem e destino até que sejam valores válidos
    do{
        cout << "ORIGEM <1 A 6 (0 para sair)>: ";
        cin >> origem;
        // Se o valor for 0 ele retorna para a main
        if(!origem)return origem;
        cout << "DESTINO <1 A 6 (0 para sair)>: ";
        cin >> destino;
        // Se o valor for 0 ele retorna para a main
        if(!destino)return destino;
    }while(validar(T, origem, destino));
    // Execução da jogada
    // Tira o valor do topo da pilha de origem e coloca em "valor"
    valor = pop(T[origem-1].pilha);
    T[origem-1].numero_elementos--;
    // Coloca o "valor" na pilha de destino
    push(T[destino-1].pilha, valor);
    T[destino-1].numero_elementos++;
    return 1;
}

int main(){
    Tubo T[TAM];
    int repetir = 1, retorno;
    do{
        iniciar_vazias(T);
        distribuir(T);
        do{
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            mostrar(T);
            retorno = jogada(T);
            if(retorno == 0)break;
        }while(retorno);
        if(validar_fim(T)){
            cout << "P A R A B E N S ! ! ! !\n\n";
        }
        cout << "Jogar Novamente? 1(sim) ou 0(nao): ";
        cin >> repetir;
    }while(repetir);
    return 0;
}
