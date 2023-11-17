#include <iostream>
#include <windows.h>
#include <time.h>
#include <stdio.h>
#define TAM 6

using namespace std;

typedef int stack_element;

#include "stack.h"

typedef struct{
    int numero_elementos;
    Stack pilha;
}Tubo;

void iniciar_vazias(Tubo T[]){
    for(int i=0; i<TAM; i++){
        initStack(T[i].pilha);
        T[i].numero_elementos=0;
    }
}

void distribuir(Tubo T[]){
    int freq[TAM-1] = {0}, num;
    srand(time(0));
    for(int i=0; i<TAM-1; i++){
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

void printa_cor(int I){
    mudacor(I);
    cout << 'O';
    mudacor(15);
}

void mostrar(Tubo T[]){
    int valor;
    Tubo aux[TAM];
    iniciar_vazias(aux);
    // essa parte passa de linha por linha, pega os valores, imprime e passa pra auxililiar
    // for que passa por cada linha
    for(int l=(TAM-1); l>0; l--){
        // for que passa por cada pilha
        for(int p=0; p<TAM; p++){
            cout << " | ";
            // verifica se o tubo tem a quantidade de elemntos da linha
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
    // essa parte devolve os valores da auxiliar pra principal
    // for que passa por cada linha
    for(int l=TAM-1; l>0; l--){
        // for que passa por cada pilha
        for(int p=0; p<TAM; p++){
            if((aux[p].numero_elementos)==l){
                // tira o valor da auxiliar e guarda em valor
                valor = pop(aux[p].pilha);
                aux[p].numero_elementos--;
                // passa o valor para a pilha principal
                push(T[p].pilha, valor);
                T[p].numero_elementos++;
            }
        }
    }
}

int validar(Tubo T[], int o, int d){
    cout << endl;
    if(o==d){
        cout << "O VALOR DE ORIGEM E IGUAL AO DE DESTINO!\n";
        return 1;
    }
    if(o>TAM || o<0){
        cout << "O VALOR DE ORIGEM NAO E VALIDO!\n";
        return 1;
    }
    if(d>TAM || d<0){
        cout << "O VALOR DE DESTINO NAO E VALIDO!\n";
        return 1;
    }
    if(isEmpty(T[o-1].pilha)){
        cout << "O TUBO DE ORIGEM ESTA VAZIO!\n";
        return 1;
    }
    if((T[d-1].numero_elementos)>=TAM-1){
        cout << "O TUBO DE DESTINO ESTA CHEIO!\n";
        return 1;
    };
    return 0;
}

int validar_fim(Tubo T[]){
    int valor;
    Tubo aux[TAM];
    iniciar_vazias(aux);
    // executa os processos pra cada pilha
    for(int i=0; i<TAM; i++){
        // verifica se a pilha tem menos de 5 elementos (desconsiderando a pilha vazia)
        if(T[i].numero_elementos<(TAM-1) && !isEmpty(T[i].pilha))return 0;
        // executa os processos dentro das pilhas não vazias
        if(!isEmpty(T[i].pilha)){
            // vetor com valores dentro de cada pilha
            int valores[TAM-1] = {0};
            // for que percorre cada valor de uma pilha
            for(int j=0; j<TAM-1; j++){
                // tira da pilha original e guarda o valor na variavel
                valor = pop(T[i].pilha);
                // passa o valor da variavel pra pilha auxiliar;
                push(aux[i].pilha, valor);
                // adiciona o valor da variavel no array
                valores[j] = valor;
            }
            // preenche a pilha original com os valores da pilha auxiliar
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
    return 1;
}

int jogada(Tubo T[]){
    int origem, destino, valor;
    if(validar_fim(T)){
        return 0;
    };
    do{
        cout << "ORIGEM <1 A 6 (0 para sair)>: ";
        cin >> origem;
        if(!origem)return origem;
        cout << "DESTINO <1 A 6 (0 para sair)>: ";
        cin >> destino;
        if(!destino)return destino;
    }while(validar(T, origem, destino));
    valor = pop(T[origem-1].pilha);
    T[origem-1].numero_elementos--;
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
            cout << "P A R A B E N S ! ! ! !\n";
        }
        cout << "Jogar Novamente? 1(sim) ou 0(nao): ";
        cin >> repetir;
    }while(repetir);
    return 0;
}
