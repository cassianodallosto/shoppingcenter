/*cassiano dallosto*/#include <stdio.h>//Cassiano dallosto 2410100707
/*cassiano dallosto*/#include <stdlib.h>//Cassiano dallosto 2410100707
/*cassiano dallosto*/#include <time.h>//Cassiano dallosto 2410100707
/*cassiano dallosto*/#include <stdbool.h>//Cassiano dallosto 2410100707

typedef struct cliente{ 
    int id; 
    int produtos;
    int tempo;
}cliente;

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
    cliente *clienteAtual;
    int tempoRestante;
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

 loja* criaLoja(){
    loja *l = (loja*)malloc(sizeof(loja));
    for(int i = 0; i < 5; i++){
        l->caixas[i].fila = criaFila();
        l->caixas[i].clienteAtual = NULL;
        l->caixas[i].tempoRestante = 0;
    }
    return l;
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
        return;
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

    bool verificaChegou(){ //ve se chegou um cliente com a chance de 10%

    int num = rand()%100;
    if(num<=60){
    
        return true;
    }   
    else {
        return false;
    }
}

int contadorFila(fila* f){ //conta a quantidade de clientes na fila e retorna um inteiro com a quantidade
    int i = 0;
    nodo *aux = f->inicio;
    while(aux != NULL){
        i++;
        aux = aux->prox;    
}
    return i;
}

int retornaMenorCaixa(loja* l){ //indica a caixa com a menor fila da loja no parametro
    int menor = 0;
    for(int i = 1; i < 5; i++){
        if(contadorFila(l->caixas[i].fila) < contadorFila(l->caixas[menor].fila)){
            menor = i;
        }
}
    return menor;

}

cliente* criarCliente(int id){ //cria o cleinte com produtos de 1 a 7 para satisfazer o tempo que deve ser entre 10 e 15 
    cliente *c = (cliente*)malloc(sizeof(cliente));
    c->id = id;
    c->produtos = rand()%7+ 1;
    c->tempo = 0;
    return c;
}
int defineTempo(cliente* c){ //definindo o tempo de atendimento baseado nos produtos
    c->tempo = c->produtos * 2;
    return c->tempo;
}


void chegada(loja* l, int *idContador){ //quando chega cliente, cria o cliente, define o tempo e insere na fila com menor caixa
    if (verificaChegou()){
        cliente *c = criarCliente(*idContador);
        (*idContador)++;
        printf("cliente %d chegou com %d produtos\n", c->id, c->produtos);
        defineTempo(c);
        int caixaMenor = retornaMenorCaixa(l);
        insereFila(l->caixas[caixaMenor].fila, c);
        printf("cliente %d na fila %d\n", c->id, caixaMenor);
    }
}

void atendimento(loja *l){

for (int i = 0; i < 5; i++){
    caixa *cx = &l->caixas[i];
    if(cx->clienteAtual == NULL){
        if(cx->fila->inicio != NULL){
            cx->clienteAtual = cx->fila->inicio->c;
            cx->tempoRestante = cx->clienteAtual->tempo;
            removeFila(cx->fila);
            printf("cliente %d sendoatendido na caixa %d\n", cx->clienteAtual->id, i);
        }
    }
    
    if(cx->clienteAtual != NULL){
            cx->tempoRestante--;
            if(cx->tempoRestante <= 0){
                printf("cliente %d terminou de ser atendido na caixa %d\n", cx->clienteAtual->id, i);
                free(cx->clienteAtual);
                cx->clienteAtual = NULL;
            }
      }
    }
}

void imprimeLoja(loja* l){
    for(int i = 0; i<5; i++){
        printf("caixa %d: ", i);
        if(l->caixas[i].clienteAtual != NULL){
            printf("atendendo: cliente %d /// tempo restante: %d | ", l->caixas[i].clienteAtual->id, l->caixas[i].tempoRestante);
        }
        printf("fila: ");
        imprimeFila(l->caixas[i].fila);
    }
}
int main() {
  srand(time(NULL));
  loja *loja = criaLoja();
  int idContador = 1;
  while(true){
  chegada(loja, &idContador);
  atendimento(loja);
  imprimeLoja(loja);  
  printf("pressiona enter para passar temmpo\n");

  getchar();
}

return 0;
}