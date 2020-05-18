#include "cola.h"
#include <stdlib.h>
#include <stdio.h>


//Definicion del struct cola

struct nodo{
	void** dato;
	struct nodo* sig;

};
typedef struct nodo nodo_t;

struct cola{
	nodo_t* primero;
	nodo_t* ultimo;
};

// Primitivas de la cola

cola_t* cola_crear(void){
	cola_t* cola = malloc(sizeof(cola_t));
	if (!cola) return NULL;
	cola->primero=NULL;
	return cola;

}

void cola_destruir(cola_t *cola, void destruir_dato(void*)){
	while(cola->primero){
		nodo_t* auxiliar = cola->primero;
		void* dato = auxiliar->dato;
		cola->primero= cola->primero->sig;
		// Veo si quiero destruir tambien los datos
		if( destruir_dato != NULL){
			destruir_dato(dato);
		}
		free(auxiliar);
	}
	free(cola);
}

bool cola_esta_vacia(const cola_t *cola){
	return cola->primero ==NULL;
}

bool cola_encolar(cola_t *cola, void* valor){
	// Creo un nuevo nodo donde guardo los datos a agregar
	nodo_t* nodo_nuevo = malloc(sizeof(nodo_t));
	if(nodo_nuevo == NULL) return false;
	nodo_nuevo->dato = valor;
	// me fijo si la cola esta vacia
	if(cola_esta_vacia(cola)){
		cola->primero = nodo_nuevo;
		cola->ultimo = nodo_nuevo;
		cola->ultimo->sig = NULL;
		return true;

	}
	// si ya tenia elementos
	cola->ultimo->sig = nodo_nuevo;
	cola->ultimo= nodo_nuevo;
	nodo_nuevo->sig = NULL;
	return true;
}


void* cola_ver_primero(const cola_t *cola){
	if(cola_esta_vacia(cola)) return NULL;
	return cola->primero->dato;
}


void* cola_desencolar(cola_t *cola){
	// Si la cola esta vacia, devuelvo NULL
	if(cola_esta_vacia(cola)) return NULL;
	void* dato = cola->primero->dato;
	nodo_t* auxiliar = cola->primero;
	cola->primero= cola->primero->sig;
	free(auxiliar);
	return dato;


}



