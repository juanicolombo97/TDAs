#include "pila.h"
#include <stdlib.h>
#include <stdio.h>
#define CAPACIDAD_INICIAL 30
#define COEFICIENTE_DE_AUMENTO 2
#define COEFICIENTE_DE_REDUCCION 4

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

pila_t* pila_crear(){
  pila_t* pila = malloc(sizeof(pila_t));
  if (pila == NULL) return NULL;
  pila->cantidad = 0;
  pila->capacidad = CAPACIDAD_INICIAL;
  pila->datos = malloc(sizeof(void*)*pila->capacidad);
  if (pila->datos == NULL){
    free(pila);
    return NULL;
  }
  return pila;
}

void pila_destruir(pila_t *pila){
  free(pila->datos);
  free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
  if (pila->cantidad == 0) return true;
  return false;
}

bool redimensionar_pila(pila_t* pila, size_t n) {
  void** datos_nuevos;
  bool condicion1 = pila->cantidad == pila->capacidad;
  bool condicion2 = (pila->cantidad)*COEFICIENTE_DE_REDUCCION == pila->capacidad && (pila->capacidad)*COEFICIENTE_DE_AUMENTO >= CAPACIDAD_INICIAL;
  if (!condicion1 && !condicion2) return true;
  datos_nuevos = realloc(pila->datos,(pila->capacidad*n)*sizeof(void*));
  if (datos_nuevos == NULL) return false;
  pila->capacidad = n;
  pila->datos = datos_nuevos;
  return true;
}

bool pila_apilar(pila_t *pila, void* valor){
  size_t n = (pila->capacidad)*COEFICIENTE_DE_AUMENTO;
  if (!redimensionar_pila(pila, n)) return false;
  pila->datos[pila->cantidad] = valor;
  pila->cantidad++;
  return true;
}

void* pila_ver_tope(const pila_t *pila){
  if(pila_esta_vacia(pila)) return NULL;
  void* tope = pila->datos[pila->cantidad - 1];
  return tope;
}

void* pila_desapilar(pila_t *pila){
  size_t n = (pila->capacidad)/COEFICIENTE_DE_AUMENTO;
  if (!redimensionar_pila(pila, n)) return false;
  if(pila_esta_vacia(pila)) return NULL;
  void* ultimo = pila->datos[pila->cantidad - 1];
  pila->cantidad--;
  return ultimo;
}

int largo_pila(pila_t* pila){
  if(pila_esta_vacia(pila)) return 0;
  void* elemento = pila_desapilar(pila);
  return largo_pila(pila)+1 && pila_apilar(pila, elemento);
}
