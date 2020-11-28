#include "../include/listaencad.h"


typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula {
  int item;
  TipoApontador prox;
} TipoCelula;

typedef struct TipoLista{
  TipoApontador Primeiro, Ultimo;
} TipoLista;

TipoLista* CriaLista()
{
    TipoLista* Lista = malloc(sizeof(TipoLista));
    FLVazia(Lista);
    return Lista;
}

/* Faz a lista ficar vazia */
void FLVazia(TipoLista *Lista)
{
    Lista -> Primeiro = NULL;
    Lista -> Ultimo = NULL;
}

/*Verifica se a lista esta vazia*/
int Vazia(TipoLista* Lista){
    if(Lista->Primeiro != NULL)
        return 0;
    else
        return 1;
}

/* Insere x apos o ultimo elemento da lista */
void Insere(int x, TipoLista *Lista){
    if(Vazia(Lista)){
        Lista -> Primeiro = Lista -> Ultimo = (TipoApontador) malloc(sizeof(TipoCelula));
        Lista -> Primeiro->item = x;
        Lista -> Primeiro -> prox = NULL;
    } else{
        Lista -> Ultimo -> prox = (TipoApontador) malloc(sizeof(TipoCelula));
        Lista -> Ultimo = Lista -> Ultimo -> prox;
        Lista -> Ultimo->item = x;
        Lista -> Ultimo -> prox = NULL;
    }
}

/* Busca um produto pelo codigo - retornando a celula inteira*/
TipoApontador BuscaItem(int x, TipoLista *Lista){
    
    if(Vazia(Lista) == 0)
    {
        TipoApontador celula = Lista -> Primeiro;
        
        do
        {
            if(celula->item == x)
            {
                return celula;
            }
            celula = celula -> prox;
        } while(celula -> prox != NULL);
    }
    return NULL;
}

/* libera na memória uma celula */
void LiberaCelula(TipoCelula *celula){
    free(celula);
}

/* Retira uma celula da lista encadeada */
void RetiraCelula(TipoCelula *anterior, TipoCelula *retirar){
    anterior -> prox = retirar -> prox;
    LiberaCelula(retirar);
}

int RetiraPrimeiro(TipoLista* Lista){
    int valor = Lista->Primeiro->item;
    Retira(valor, Lista);
    return valor;
}

/*Retira um elemento da lista */
void Retira(int x, TipoLista *Lista){
    
    if(Vazia(Lista) == 0)
    {
        TipoApontador anterior = NULL;
        TipoApontador alvo = Lista -> Primeiro;

        while(alvo != NULL && alvo->item != x)
        {
            anterior = alvo;
            alvo = alvo -> prox;
        }

        if(alvo == NULL)    return;

        if(alvo == Lista -> Primeiro && alvo == Lista -> Ultimo)
        {
            Lista -> Primeiro = alvo -> prox;
            Lista -> Ultimo = NULL;
        }

        if(alvo == Lista -> Primeiro)
        {
            Lista -> Primeiro = alvo -> prox;          
        }
        
        if(alvo == Lista -> Ultimo)
        {
            Lista -> Ultimo = anterior;
            anterior -> prox = NULL;
        }
        else if(anterior != NULL)
        {
            anterior -> prox = alvo -> prox;
        }
        LiberaCelula(alvo);
    }
}


/*Imprime a lista */
void ImprimeLista(TipoLista* Lista){
    if(Vazia(Lista))
    {
        printf("LISTA VAZIA\n");
    } else{
        TipoApontador celula = Lista->Primeiro;
    
        while(celula != NULL)
        {
            printf("%d\n", celula->item);
            celula = celula -> prox;
        }
    }
}

/* Quantidade de elementos na lista */
int Quantidade(TipoLista Lista){
    if(Vazia(&Lista)) return 0;
    
    int cont = 1;
    TipoApontador referencia = Lista.Primeiro;
    
    while(referencia -> prox != NULL)
    {
        cont ++;
        referencia = referencia -> prox;
    }
    return cont;
}

/* Libera toda a lista encadeada */
void LiberaLista(TipoLista *Lista)
{

    TipoApontador AuxDestruidor = NULL;
    while(Vazia(Lista) == 0)
    {
        AuxDestruidor = Lista -> Primeiro;
        Lista -> Primeiro = Lista -> Primeiro -> prox;
        LiberaCelula(AuxDestruidor);
    }
}