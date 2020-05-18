#define TAM_INICIAL_HEAP 10000
#define FACTOR_REDIMENSION 2
#include "heap.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

//---------------- ESTRUCTURA HEAP ---------------------------------------------

struct heap {
    void ** datos;
    size_t cant;
    size_t tam;
    cmp_func_t cmp;
};

//******************************************************************************
//------------------ Funciones auxiliares --------------------------------------
//******************************************************************************

bool redimensionar_heap(heap_t* heap, size_t nuevo_tam){
	void** tabla_nueva = realloc(heap->datos, nuevo_tam * sizeof(void*));
	if (!tabla_nueva) return false;
	heap->datos = tabla_nueva;
	heap->tam = nuevo_tam;
	return true;
}


size_t pos_hijo_izquierdo(size_t pos_padre){
  return ((pos_padre*2)+ 1);
}

size_t pos_hijo_derecho(size_t pos_padre){
  return ((pos_padre*2)+ 2);
}

size_t pos_padre(size_t pos_dato){
  return (pos_dato-1)/2;
}

bool cumple_propiedad_heap(heap_t* heap, size_t padre, size_t hijo){
  if(heap->cmp(heap->datos[padre], heap->datos[hijo]) > 0) return true;
  return false;
}

void swap_padre_hijo(void** arr, size_t padre, size_t hijo){
  void* aux = arr[padre];
  arr[padre] = arr[hijo];
  arr[hijo] = aux;
  return;
}

void up_heap(void** arr, size_t hijo, cmp_func_t cmp){
  size_t padre = pos_padre(hijo);
  if(cmp(arr[padre], arr[hijo]) > 0) return;
  swap_padre_hijo(arr, padre, hijo);
  if(padre == 0) return; // si el padre es el primer elemento del heap termina.
  up_heap(arr, padre, cmp); //se fija si el nuevo padre sigue cumpliendo propiedad de heap.
}

void down_heap(void** arr, size_t cantidad, size_t pos_padre, cmp_func_t cmp){
  if(pos_padre >= cantidad) return;

  size_t max = pos_padre;

  size_t hijo_der = pos_hijo_derecho(pos_padre);
  size_t hijo_izq = pos_hijo_izquierdo(pos_padre);

  if(hijo_izq < cantidad && cmp(arr[max], arr[hijo_izq]) < 0){
    max = hijo_izq;
  }
  if(hijo_der < cantidad && cmp(arr[max], arr[hijo_der]) < 0){
    max = hijo_der;
  }
  if(max != pos_padre){
    swap_padre_hijo(arr, pos_padre, max);
    down_heap(arr, cantidad, max, cmp);
  }
}

//******************************************************************************
//-------------------- PRIMITIVAS HEAP -----------------------------------------
//******************************************************************************

heap_t *heap_crear(cmp_func_t cmp){
  heap_t* heap = malloc(sizeof(heap_t));
  if(!heap) return NULL;
  heap->datos = malloc(sizeof(void*)*TAM_INICIAL_HEAP);
  if(!heap->datos){
    free(heap);
    return NULL;
  }
  heap->tam = TAM_INICIAL_HEAP;
  heap->cant = 0;
  heap->cmp = cmp;
  return heap;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
  for(size_t i=0; i<heap->cant; i++){
    if(destruir_elemento != NULL) destruir_elemento(heap->datos[i]);
  }
  free(heap->datos);
  free(heap);
  return;
}

size_t heap_cantidad(const heap_t *heap){
  return heap->cant;
}

bool heap_esta_vacio(const heap_t *heap){
  if(heap->cant == 0) return true;
  return false;
}

bool heap_encolar(heap_t *heap, void *elem){
  if(elem == NULL || heap == NULL) return false;
  if(heap->tam == heap->cant){
    redimensionar_heap(heap,heap->tam * 2);
  }
  heap->datos[heap->cant] = elem;
  if(heap->cant != 0) up_heap(heap->datos, heap->cant, heap->cmp);
  heap->cant++;
  return true;
}

void *heap_ver_max(const heap_t *heap){
  if(!heap || heap->cant == 0) return NULL;
  return heap->datos[0];
}


void *heap_desencolar(heap_t *heap){
  if(!heap || heap->cant == 0) return NULL;
  if(heap->tam <= heap->cant / 4){
    redimensionar_heap(heap,heap->tam /2);
  }
  heap->cant--;
  swap_padre_hijo(heap->datos, 0, heap->cant);
  void* desencolado = heap->datos[heap->cant];
  size_t pos_padre = 0;
  down_heap(heap->datos, heap->cant, pos_padre, heap->cmp);
  return desencolado;
}

//******************************************************************************
//------------------ HEAP SORT -------------------------------------------------
//******************************************************************************

void heapify(void* elementos[], size_t n, cmp_func_t cmp){
  for(size_t i = (n/2); i > 0; i--){
    down_heap(elementos, n, i-1, cmp);
  }
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
  heap_t* heap = heap_crear(cmp);
  if(!heap) return NULL;

  for(size_t i= 0; i < n; i++){
    heap->datos[heap->cant] = arreglo[i];
    heap->cant++;
  }
  heapify(heap->datos, n, cmp);
  return heap;
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
  if(cant <= 1) return;

  heapify(elementos, cant, cmp);

  for(size_t i = cant-1; i > 0; i--){
    swap_padre_hijo(elementos, 0, i);
    down_heap(elementos, i, 0, cmp);
  }
}
