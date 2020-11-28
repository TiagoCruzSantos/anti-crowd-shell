#ifndef LISTAENCAD_H_
#define LISTAENCAD_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct TipoLista TipoLista;
typedef struct TipoCelula TipoCelula;
typedef struct TipoCelula *TipoApontador;

/* Cria uma nova lista */
TipoLista* CriaLista();

/* Faz a lista ficar vazia */
void FLVazia(TipoLista *Lista);

/* Retira o Primeiro elemento */
int RetiraPrimeiro(TipoLista* Lista);

/*Verifica se a lista esta vazia*/
int Vazia(TipoLista* Lista);

/* Insere x apos o ultimo elemento da lista */
void Insere(int x, TipoLista *Lista);

/* Busca um produto pelo codigo - retornando a celula inteira*/
TipoApontador BuscaItem(int codigo, TipoLista *Lista);

/* libera na memória uma celula */
void LiberaCelula(TipoCelula *celula);

/* Retira uma celula da lista encadeada */
void RetiraCelula(TipoCelula *anterior, TipoCelula *retirar);

/* Retira um elemento da lista */
void Retira(int x, TipoLista *Lista);


/* Imprime a lista */
void ImprimeLista(TipoLista *Lista);

/* Quantidade de elementos na lista */
int Quantidade(TipoLista Lista);

/* Libera toda a lista encadeada */
void LiberaLista(TipoLista *Lista);


#endif /* LISTAENCAD_H_ */