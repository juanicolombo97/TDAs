#include "lista.h"
#include <stdlib.h>
#include <stdio.h>



// Definicion del struct lista

struct nodo{
	void** dato;
	struct nodo* siguiente;

};
typedef struct nodo nodo_t;


struct lista{
	nodo_t* primero;
	nodo_t* ultimo;
	size_t largo;

};

struct lista_iter{
	nodo_t* actual;
	nodo_t* anterior;
	lista_t* lista;
};

// Primitivas de la lista

lista_t *lista_crear(void){
	lista_t* lista = malloc(sizeof(lista_t));
	// pruebo si se reservo memoria
	if(!lista) return NULL;
	lista->primero=NULL;
	lista->largo = 0;
	return lista;
}

bool lista_esta_vacia(const lista_t *lista){
	return lista->primero == NULL;
}

bool lista_insertar_primero(lista_t *lista, void *dato){
	nodo_t* nodonuevo = malloc(sizeof(nodo_t));
	// Pruebo que se pudo reservar memoria, sino devuelvo false
	if(!nodonuevo) return false;
	nodonuevo->dato = dato;
	//Verifico si la lista esta vacia
	if(lista_esta_vacia(lista)){
	lista->primero = nodonuevo;
	lista->ultimo = nodonuevo;
	lista->ultimo->siguiente = NULL;
	lista->largo++;
	return true;
	}
	// Si la lista no esta vacia
	nodonuevo->siguiente = lista->primero;
	lista->primero= nodonuevo;
	lista->largo++;
	return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
	nodo_t* nodonuevo = malloc(sizeof(nodo_t));
	// verifico que se pudo guardar memoria
	if (!nodonuevo) return false;
	nodonuevo->dato = dato;
	// Veo si la lista esta vacia
	if(lista_esta_vacia(lista)){
		lista->primero = nodonuevo;
		lista->ultimo = nodonuevo;
		lista->ultimo->siguiente = NULL;
		lista->largo++;
		return true;
	}
	lista->ultimo->siguiente=nodonuevo;
	lista->ultimo= nodonuevo;
	lista->largo++;
	nodonuevo->siguiente = NULL;
	return true;
}

void *lista_borrar_primero(lista_t *lista){
	if(lista_esta_vacia(lista)) return NULL;
	void* dato = lista->primero->dato;
	nodo_t* auxiliar = lista->primero;
	lista->primero=lista->primero->siguiente;
	free(auxiliar);
	lista->largo--;
	return dato;
}


void *lista_ver_primero(const lista_t *lista){
	if (lista_esta_vacia(lista)) return NULL;
	return lista->primero->dato;
}

void *lista_ver_ultimo(const lista_t* lista){
	if (lista_esta_vacia(lista)) return NULL;
	return lista->ultimo->dato;
}

size_t lista_largo(const lista_t *lista){
	return lista->largo;
}

void lista_destruir(lista_t *lista, void destruir_dato(void *)){
	while(lista->primero){
		nodo_t* auxiliar = lista->primero;
		void* dato = lista->primero->dato;
		lista->primero=lista->primero->siguiente;
		if( destruir_dato != NULL){
			destruir_dato(dato);
		}
		free(auxiliar);
	}
	free(lista);
}

// Primitiva iterador interno

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
	// Creo un iterador
	nodo_t* nodo = lista->primero;
	bool iterar = true;
	while(nodo){
		void * dato = nodo->dato;
		iterar = visitar(dato,extra);
		if (!iterar) return;
		nodo = nodo->siguiente;
	}
}
// Primitivas iterador externo


lista_iter_t *lista_iter_crear(lista_t *lista){
	lista_iter_t* iterador = malloc(sizeof(lista_iter_t));
	if(!iterador) return NULL;
	iterador->actual = lista->primero;
	iterador->anterior = NULL;
	iterador->lista = lista;
	return iterador;
}

bool lista_iter_avanzar(lista_iter_t *iter){
	// Me fijo si esta
	if(lista_iter_al_final(iter)) return false;
	iter->anterior = iter->actual;
	iter->actual= iter->actual->siguiente;
	return true;

}



void *lista_iter_ver_actual(const lista_iter_t *iter){
	if(lista_iter_al_final(iter)) return NULL;
	return iter->actual->dato;
}
bool lista_iter_al_final(const lista_iter_t *iter){
	return iter->actual == NULL;
}
void lista_iter_destruir(lista_iter_t *iter){
	free(iter);
}
bool lista_iter_insertar(lista_iter_t *iter, void *dato){
	//Si el iterador esta en la primer posicion o vacio
	if( iter->actual == iter->lista->primero && iter->anterior == NULL){
		if(!lista_insertar_primero(iter->lista,dato)) return false;
	iter->anterior = NULL;
	iter->actual = iter->lista->primero;
	return true;
	}
	//Si esta al final
	if(lista_iter_al_final(iter)){
		if(!lista_insertar_ultimo(iter->lista,dato)) return false;
		iter->actual = iter->lista->ultimo;
		iter->anterior->siguiente = iter->actual;
		return true;
	}
	//Si esta en cualquier otra posicion
	nodo_t* nuevo_nodo = malloc(sizeof(nodo_t));
	if(!nuevo_nodo) return false;
	nuevo_nodo->dato = dato;
	nuevo_nodo->siguiente = iter->actual;
	iter->actual = nuevo_nodo;
	iter->anterior->siguiente= iter->actual;
	iter->lista->largo++;
	return true;





}
void *lista_iter_borrar(lista_iter_t *iter){
	if(lista_esta_vacia(iter->lista) || lista_iter_al_final(iter))return NULL;
	nodo_t* auxiliar= iter->actual;
	//Si esta al principio
	if(iter->actual== iter->lista->primero){
		void* dato = lista_borrar_primero(iter->lista);
		iter->actual=iter->lista->primero;
		iter->anterior= NULL;
		return dato;
	}
	//	En otros casos
	void* dato = iter->actual->dato;
	//Caso que este al final
	if(auxiliar == iter->lista->ultimo){
		iter->actual = NULL;
		iter->lista->ultimo = iter->anterior;
		iter->anterior->siguiente = iter->actual;
	}
	//Si no esta ni al final ni al principio
	else{
		iter->actual = iter->actual->siguiente;
		iter->anterior->siguiente = iter->actual;
	}
	free(auxiliar);
	iter->lista->largo--;
	return dato;
	}



