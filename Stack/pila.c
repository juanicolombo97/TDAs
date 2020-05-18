#include "pila.h"
#include <stdlib.h>

#define  CAPACIDAD_MINIMA 10

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// ...
pila_t* pila_crear(void){
	// pido memoria para la pila
	pila_t* pila = malloc(sizeof(pila_t));
	if (pila == NULL) return NULL;
	// ahora pido memoria para los datos de la pila
	pila->datos = malloc(CAPACIDAD_MINIMA * sizeof(void*));

	if (pila->datos == NULL){
		free(pila);
		return NULL;
	}
	pila-> cantidad = 0;
	pila-> capacidad = CAPACIDAD_MINIMA;
	return pila;
}


void pila_destruir(pila_t *pila){
	if (pila){
		free(pila->datos);
		free(pila);
	}
}

bool pila_esta_vacia(const pila_t *pila){
	if(pila->cantidad ==0)return true;
	return false;
}




bool pila_apilar(pila_t *pila, void* valor){
	if (!pila) return false;

	if (pila->cantidad == pila->capacidad){
		void** datosauxiliar = realloc(pila->datos,pila->capacidad *2 *sizeof(void*));
		if (datosauxiliar == NULL){
			return false;
		}
		pila->datos = datosauxiliar;
		pila->capacidad *=2;
	}
	pila->datos[pila->cantidad] = valor;
	pila->cantidad++;
	return true;
	}


void* pila_ver_tope(const pila_t *pila){
	if (pila->cantidad == 0){
		return NULL;
	}
	return pila->datos[pila->cantidad-1];

}


void* pila_desapilar(pila_t *pila){
	if(pila->cantidad ==0){
		return NULL;
	}

	pila->cantidad--;
	void* dato = pila->datos[pila->cantidad];
	if (pila->capacidad > CAPACIDAD_MINIMA && pila->cantidad<= pila->capacidad / 4){
		void** datosauxiliar = realloc(pila->datos,(pila->capacidad /2) *sizeof(void*));
		if (datosauxiliar == NULL){
			return NULL;		
		}
		pila->datos = datosauxiliar;
		pila->capacidad /=2;
	}
	return dato;


}



