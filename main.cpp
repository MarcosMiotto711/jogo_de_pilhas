#include <iostream>
#include <windows.h>
#include <time.h>
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
    for(int p=1; p<TAM; p++){
        do{
            num = rand() % (TAM-1);
        }while(freq[num]>=5);
        freq[num]++;
        push(T[p].pilha, num+1);
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
    for(int i=0; i<TAM; i++){
        for(int p=0; p<TAM; p++){
            if(isEmpty(T[p].pilha)){
                cout << p << " - ";
            }else{
                cout << p  << " - " << peek(T[p].pilha) << endl;
                pop(T[p].pilha);
            }
        }
    cout << endl;
    }
}

int validar(Tubo T[], int o, int d){
    return 0;
}

int validar_fim(Tubo T[]){
    return 0;
}

int jogada(Tubo T[]){
    int x;
    cout << "Quer jogar?: ";
    cin >> x;
    return x;
}

int main(){
    Tubo T[TAM];
    int repetir = 1, retorno;
    do{
        iniciar_vazias(T);
        distribuir(T);
        mostrar(T);
        do{
            retorno = jogada(T);
            mostrar(T);
            if(retorno == 0)break;
        }while(retorno);
        mostrar(T);
        cout << "\n P A R A B E N S ! ! ! ! ";
        cout << "\n Jogar Novamente? 1(sim) ou 0(nao): ";
        cin >> repetir;
    }while(repetir);
    return 0;
}