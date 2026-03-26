#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct cliente{ 
    int id; 
    int produtos;
    int tempo;
}cliente;
//Cassiano dallosto 2410100707
typedef struct nodo {//estrutura de nó para a fila
    cliente *c;
    struct nodo *prox;
}nodo;

typedef struct fila { //estrutura da fila
    nodo *inicio;
    nodo *fim;
}fila;

typedef struct caixa{
    fila *fila;
    cliente *cliente_atual;
    int tempo_restante;
}caixa;

typedef struct loja{
    caixa caixas[5];
}loja;

fila* criaFila(){
    fila *f = (fila*)malloc(sizeof(fila));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

void insereFila(fila* f, cliente* c){
    nodo *novo = (nodo*)malloc(sizeof(nodo));
    novo->c = c;
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
        printf("%d ", aux->c->id);
        aux = aux->prox;
    }
    printf("\n");
}

    bool verificaChegou(){

    int num = rand()%100;
    if(num<=10){
        return true;
    }   
    else {
        return false;
    }
}

int contadorFila(fila* f){
    int i = 0;
    nodo *aux = f->inicio;
    while(aux != NULL){
        i++;
        aux = aux->prox;    
}
    return i;
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


void chegada(loja* l){
    if (verificaChegou()){
        cliente *c = criarCliente(rand()%9999);
        printf("cliente %d chegou com %d produtos\n", c->id, c->produtos);
        defineTempo(c);
    }

}
int main() {
  srand(time(NULL));
    
    //printf("bool: %d\n", chegou());
    return 0;
}