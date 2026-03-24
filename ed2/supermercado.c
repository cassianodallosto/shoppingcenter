#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

//Cassiano dallosto 2410100707
typedef struct nodo {//estrutura de nó para a fila
    cliente *cliente;
    struct nodo *prox;
}nodo;

typedef struct fila { //estrutura da fila
    nodo *inicio;
    nodo *fim;
}fila;

typedef struct cliente{ 
    int id; 
    int produtos;
    int tempo;
}cliente;

typedef struct caixa{
    fila *fila;
    cliente *cliente_atual;
    int tempo_restante;
}caixa;

typedef struct loja{
    caixa *caixa1;
    caixa *caixa2;
    caixa *caixa3;
}loja;

fila* criaFila(){
    fila *f = (fila*)malloc(sizeof(fila));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

void insereFila(fila* f){
    nodo *novo = (nodo*)malloc(sizeof(nodo));
    novo->prox = NULL;

    if(f->fim == NULL){
        f->inicio = novo;
        f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }   
}

void removeFila(fila* f){
    if(f->inicio == NULL || f->fim == NULL){
        printf("fila vazia");
    }
    nodo *aux = f->inicio;
    f->inicio = f->inicio->prox;    
    free(aux);
}

void imprimeFila(fila* f){
    nodo *aux = f->inicio;
    while(aux != NULL){
        printf("%d ", aux->cliente->id);
        aux = aux->prox;
    }
    printf("\n");
}

bool chegada(){

    int num = rand()%100;
    if(num<=10){
        return true;
    }else {
        return false;
    }
}


cliente* criarCliente(int id){
    cliente *c = (cliente*)malloc(sizeof(cliente));
    c->id = id;
    c->produtos = rand()%7+ 1;
    c->tempo = 0;
    return c;
}
int defineTempo(cliente* c){
    c->tempo = c->produtos * 2;
    return c->tempo;
}
int main() {
    srand(time(NULL));
    
    
    return 0;
}