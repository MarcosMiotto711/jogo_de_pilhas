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
    int v, repetido;
    int valores[TAM-1];
    cout << "Valores: ";
    for(int i=0; i<TAM-1; i++){
        srand(time(NULL));
        do{
            v = rand() % 16;
            repetido = 0;
            for(int j=0; j<TAM-1; j++){
                if(valores[j]==v){
                    repetido = 1;
                    break;
                }
            }
        }while(repetido);
        valores[i] = v;
        cout << v << " ";
    }
    cout << endl;
    for(int i=1; i<TAM; i++){
        int indices[TAM-1] = {};
        cout << "indices: ";
        for(int j=0; j<TAM-1; j++){
            do{
                srand(time(NULL));
                v = rand() % TAM;
                repetido = 0;
                for(int k=0; k<TAM-1; k++){
                    if(indices[k]==v){
                        repetido = 1;
                        break;
                    }
                }
            }while(repetido);
            indices[j] = v;
            cout << v << " ";
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
    for(int i=0; i<TAM; i++){
        for(int j=0; j<TAM-1; j++){
            
        }        
    }
    return;
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