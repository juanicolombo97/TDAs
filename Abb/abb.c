#define _POSIX_C_SOURCE 200809L
#include "abb.h"
#include "pila.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//***************************************************************************
//------------ Estructuras y funciones auxiliares ---------------------------
//***************************************************************************
typedef struct nodo_abb {
  struct nodo_abb* izq;
  struct nodo_abb* der;
  struct nodo_abb* padre;
  char* clave;
  void* dato;
} nodo_abb_t;

struct abb{
  nodo_abb_t* raiz;
  size_t cantidad;
  abb_destruir_dato_t destruir_dato;
  abb_comparar_clave_t comparar_clave;
};

nodo_abb_t* crear_nodo_abb(char* clave, void* valor){
  nodo_abb_t* nodo = malloc(sizeof(nodo_abb_t));
  if (!nodo) return false;
  nodo->clave = clave;
  nodo->dato = valor;
  nodo->izq = NULL;
  nodo->der = NULL;
  return nodo;
}

nodo_abb_t* buscar_nodo(const abb_t* abb, const char* clave, nodo_abb_t* nodo_act) {
  //Busca un nodo en el arbol que tenga la clave pasada por parámetro.
  //Devuelve el nodo si lo encuentra o NULL en caso de que no este en el arbol.
	if (nodo_act == NULL) return NULL;
	if (abb->comparar_clave(nodo_act->clave, clave) == 0) {
		return nodo_act;
	}
	if (abb->comparar_clave(nodo_act->clave, clave) > 0) {
		return buscar_nodo(abb, clave, nodo_act->der);
	}
  return buscar_nodo(abb, clave, nodo_act->izq);
}

nodo_abb_t* buscar_padre(const abb_t* arbol, const char* clave, nodo_abb_t* posible_padre, nodo_abb_t* padre){
  if(!arbol || !arbol->raiz) return NULL;
  int comparar;
  if(!padre){
    comparar = arbol->comparar_clave(arbol->raiz->clave, clave);
    if(comparar == 0) return NULL;
    if(comparar < 0) return buscar_padre(arbol, clave, arbol->raiz->izq, arbol->raiz);
    return buscar_padre(arbol, clave, arbol->raiz->der, arbol->raiz);
  }
  if(!posible_padre) return padre;
  comparar = arbol->comparar_clave(posible_padre->clave, clave);
  if(comparar == 0) return padre;
  if(comparar < 0) return buscar_padre(arbol,clave, posible_padre->izq, posible_padre);
  return buscar_padre(arbol, clave, posible_padre->der, posible_padre);
}

void borrar_nodo(abb_t* arbol, nodo_abb_t* nodo){
  if(!nodo) return;
  if(arbol->destruir_dato != NULL) arbol->destruir_dato(nodo->dato);
  free(nodo->clave);
  free(nodo);
}

void borrar_hoja(abb_t* arbol,nodo_abb_t* nodo_a_borrar,nodo_abb_t* padre){
  if(!nodo_a_borrar) return;
  if(!padre){
    //Estamos borrando raiz.
    arbol->raiz = NULL;
  } else {
    int comparar;
    comparar = arbol->comparar_clave(padre->clave,nodo_a_borrar->clave);
    if(comparar < 0) padre->izq = NULL;
    if(comparar > 0) padre->der = NULL;
  }
  arbol->cantidad--;
  borrar_nodo(arbol,nodo_a_borrar);
  return;
}

void borrar_raiz_un_hijo(abb_t* arbol, nodo_abb_t* nodo_a_borrar,nodo_abb_t* padre,bool* hijo_der){
  if(*hijo_der) arbol->raiz = nodo_a_borrar->der;
  if(!*hijo_der) arbol->raiz = nodo_a_borrar->izq;
  borrar_nodo(arbol,nodo_a_borrar);
  return;
}

void* buscar_reemplazo(nodo_abb_t* nodo_act){
  //Si el nodo no tiene hijo izquierdo lo devolvemos.
  if(!nodo_act->izq) return nodo_act;
  return buscar_reemplazo(nodo_act->izq);
}

char* strdup(const char* entrada){
  char* copia = malloc(sizeof(char)*(strlen(entrada)+1));
  if(copia == NULL) return NULL;
  strcpy(copia, entrada);
  return copia;
}

//*********************************************************************
//----------------- PRIMITIVAS ABB -----------------------------------
//*********************************************************************
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){

  //Pido memoria para el abb
  abb_t* abb = malloc(sizeof(abb_t));
  //Si no se obtuvo correctamente devuelvo NULL
  if(!abb) return NULL;

  //Inicializo los miembros del abb vacío.
  abb->raiz = NULL;
  abb->cantidad = 0;
  abb->destruir_dato = destruir_dato;
  abb->comparar_clave = cmp;
  return abb;
}

void* abb_obtener(const abb_t *arbol, const char *clave){
  if(!arbol) return NULL;
  nodo_abb_t* nodo_act = buscar_nodo(arbol, clave, arbol->raiz);
  if(!nodo_act) return NULL;
  return nodo_act->dato;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
  if(!arbol || arbol->cantidad == 0) return false;
  nodo_abb_t* nodo_act = buscar_nodo(arbol, clave, arbol->raiz);

  return nodo_act != NULL;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){

  //Si ya esta la clave en el abb, reemplazo el dato.
   nodo_abb_t* nodo_act = buscar_nodo(arbol, clave, arbol->raiz);
   if(nodo_act != NULL) {
     if(arbol->destruir_dato != NULL) arbol->destruir_dato(nodo_act->dato);
     nodo_act->dato = dato;
     return true;
   }

  //Si la clave no esta guardada en el abb, copio la clave y creo el nodo a guardar
  char* key = strdup(clave);
	nodo_abb_t* nodo_nuevo = crear_nodo_abb(key, dato);
  nodo_abb_t* padre = buscar_padre(arbol,nodo_nuevo->clave,arbol->raiz,NULL);
	if (!nodo_nuevo) return false;

  if(!arbol->cantidad){
    //Si el abb esta vacio.
    arbol->raiz = nodo_nuevo;
  } else {
    int comparacion = arbol->comparar_clave(padre->clave,clave);
    if(comparacion < 0) padre->izq = nodo_nuevo;
    if(comparacion > 0) padre->der = nodo_nuevo;
  }
  arbol->cantidad++;
  return true;

}

size_t abb_cantidad(abb_t *arbol){
   return arbol->cantidad;
 }

void *abb_borrar(abb_t *arbol, const char *clave){
  // Si no existe el arbol, la cantidad de elementos es 0,
  // o la clave no pertenece se devuelve NULL.
  if(!arbol || !arbol->raiz || !abb_pertenece(arbol, clave)) return NULL;

  nodo_abb_t* nodo_a_borrar = buscar_nodo(arbol, clave, arbol->raiz);
  nodo_abb_t* padre = buscar_padre(arbol, clave, arbol->raiz, NULL);
  void* dato = nodo_a_borrar->dato;
  // Borro una HOJA.
  if(!nodo_a_borrar->der && !nodo_a_borrar->izq){
    borrar_hoja(arbol, nodo_a_borrar, padre);
    return dato;
  }

  //Borro con un hijo
  bool hijo_der = true; // Borro con hijo derecho
  if((nodo_a_borrar->der && !nodo_a_borrar->izq) || (!nodo_a_borrar->der && nodo_a_borrar->izq)) {
    if(!nodo_a_borrar->der && nodo_a_borrar->izq) hijo_der = false; //Borro con hijo izquierdo.
    if(arbol->comparar_clave(nodo_a_borrar->clave, arbol->raiz->clave) == 0){
      borrar_raiz_un_hijo(arbol, nodo_a_borrar, padre, &hijo_der);
      arbol->cantidad--;
      return dato;
    }
    if(arbol->comparar_clave(padre->clave, nodo_a_borrar->clave) < 0){
      if(hijo_der) padre->izq = nodo_a_borrar->der;
      if(!hijo_der) padre->izq = nodo_a_borrar->izq;
    } else {
      if(hijo_der) padre->der = nodo_a_borrar->der;
      if(!hijo_der) padre->der = nodo_a_borrar->izq;
    }
    arbol->cantidad--;
    borrar_nodo(arbol, nodo_a_borrar);
    return dato;
  }
  // Borrar nodo con dos hijos.
  nodo_abb_t* reemplazo = buscar_reemplazo(nodo_a_borrar->der);
  char* clave_reemplazo = strdup(reemplazo->clave);
  void* dato_reemplazo = abb_borrar(arbol, reemplazo->clave);
  free(nodo_a_borrar->clave);
  nodo_a_borrar->clave = clave_reemplazo;
  nodo_a_borrar->dato = dato_reemplazo;
  return dato;
}

//Funcion auxiliar para destruir nodos arbol.
void destruir_nodos(abb_t* arbol, nodo_abb_t* nodo){
	if (nodo == NULL) return;
	destruir_nodos(arbol, nodo->izq);
	destruir_nodos(arbol, nodo->der);
	if(arbol->destruir_dato != NULL) arbol->destruir_dato(nodo->dato);
  free(nodo->clave);
  free(nodo);
}

void abb_destruir(abb_t* arbol){
  if(!arbol) return;
  destruir_nodos(arbol, arbol->raiz);
  free(arbol);
  return;
}

//**************************************************************************
//------------------- ITERADORES ABB --------------------------------------
//***************************************************************************

// _________________________ Iterador interno __________________________

void _abb_in_order(nodo_abb_t* nodo, bool visitar(const char* clave, void *dato, void *extra), void* extra, bool* visitar_fin) {
    if(nodo == NULL) return;
    _abb_in_order(nodo->der, visitar, extra, visitar_fin);
    if(! *visitar_fin) return;
    *visitar_fin = visitar(nodo->clave, nodo->dato, extra);
    if(! *visitar_fin) return;
    _abb_in_order(nodo->izq, visitar, extra, visitar_fin);
}

void abb_in_order(abb_t *arbol, bool visitar(const char *clave, void *dato, void *extra), void *extra){
  if(!arbol) return;
  bool visitar_fin = true;
  _abb_in_order(arbol->raiz, visitar, extra, &visitar_fin);
  return;
}

// _________________________ Iterador externo __________________________

struct abb_iter{
  const abb_t* arbol;
  pila_t* pila;
};

void apilar_hijos_izquierdos(nodo_abb_t* nodo, pila_t* pila){
	if (nodo == NULL) return;
	if (!nodo->der) return;

	pila_apilar(pila, nodo->der);
	apilar_hijos_izquierdos(nodo->der, pila);
}

abb_iter_t* abb_iter_in_crear(const abb_t *arbol){
  abb_iter_t* iter_abb = malloc(sizeof(abb_iter_t));
  if(!iter_abb) return NULL;
  iter_abb->pila = pila_crear();
  if(!iter_abb->pila){
    free(iter_abb);
    return NULL;
  }
  if(arbol->raiz){
    pila_apilar(iter_abb->pila, arbol->raiz);
    apilar_hijos_izquierdos(arbol->raiz, iter_abb->pila);
  }
  iter_abb->arbol = arbol;
  return iter_abb;
}

bool abb_iter_in_avanzar(abb_iter_t *iter){
  if(abb_iter_in_al_final(iter)) return false;
  nodo_abb_t* aux = pila_desapilar(iter->pila);
  if (aux->izq != NULL){
		pila_apilar(iter->pila, aux->izq);
		apilar_hijos_izquierdos(aux->izq, iter->pila);
	}
	return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
  if(pila_esta_vacia(iter->pila)) return NULL;
  nodo_abb_t* aux = pila_ver_tope(iter->pila);
  return aux->clave;
}

bool abb_iter_in_al_final(const abb_iter_t *iter){
  return pila_esta_vacia(iter->pila);
}

void abb_iter_in_destruir(abb_iter_t* iter){
  pila_destruir(iter->pila);
  free(iter);
}
