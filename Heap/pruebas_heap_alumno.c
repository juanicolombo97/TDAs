#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "testing.h"
#include "heap.h"

/***********************************************************************/

int comparador(const void* a,const void* b) {
	return *(int*)a - *(int*)b;
}

/////////////////////////////////////////////////////////////////////

void heap_vacio(){
  printf("\n------------------Pruebas heap vacio------------------------------\n");
  heap_t* heap = heap_crear(comparador);
  print_test("El heap esta vacio",heap_cantidad(heap)==0);
  print_test("El heap esta vacio",heap_esta_vacio(heap)== true);
  print_test("No se puede desencolar",heap_desencolar(heap)==false);
  heap_destruir(heap,NULL);
  print_test("Se destruyo el heap",true);
}

void heap_insertar(){
  printf("\n------------------Pruebas insertar------------------------\n");
  // datos
  int vector[] = {0, 1, 2, 3, 4, 5, 6};

  heap_t* heap2 = heap_crear(comparador);
  // Encolo primer dato
  print_test("Encolar dato 2",heap_encolar(heap2,&vector[2])== true);
  print_test("La cantidad de elementos es 1",heap_cantidad(heap2)==1);
  print_test("EL heap no esta vacio",heap_esta_vacio(heap2)==false);
  print_test("EL maximo es el 2",heap_ver_max(heap2)==&vector[2]);
  // Encolo el segundo
  print_test("Encolar dato 1",heap_encolar(heap2,&vector[1])== true);
  print_test("La cantidad de elementos es 2",heap_cantidad(heap2)==2);
  print_test("EL heap no esta vacio",heap_esta_vacio(heap2)==false);
  print_test("EL maximo es el 2",heap_ver_max(heap2)==&vector[2]);
  // Encolo el tercero
  print_test("Encolar dato 3",heap_encolar(heap2,&vector[3])== true);
  print_test("La cantidad de elementos es 3",heap_cantidad(heap2)==3);
  print_test("EL heap no esta vacio",heap_esta_vacio(heap2)==false);
  print_test("EL maximo es el 3",heap_ver_max(heap2)==&vector[3]);
  // Encolo el cuarto
  print_test("Encolar dato 5",heap_encolar(heap2,&vector[5])== true);
  print_test("La cantidad de elementos es 4",heap_cantidad(heap2)==4);
  print_test("EL heap no esta vacio",heap_esta_vacio(heap2)==false);
  // Encolo el quinto
  print_test("Encolar dato 4",heap_encolar(heap2,&vector[4])== true);
  print_test("La cantidad de elementos es 5",heap_cantidad(heap2)==5);
  print_test("EL heap no esta vacio",heap_esta_vacio(heap2)==false);
  // Encolo el sexto
  print_test("Encolar dato 6",heap_encolar(heap2,&vector[6])== true);
  print_test("La cantidad de elementos es 6",heap_cantidad(heap2)==6);
  print_test("EL heap no esta vacio",heap_esta_vacio(heap2)==false);
  print_test("EL maximo es el 6",heap_ver_max(heap2)==&vector[6]);
  heap_destruir(heap2,NULL);
  print_test("Se destruyo heap 2 correctamente",true);

}


/////////////////////////////////////////////////////////////////////////

void heap_eliminar(){
  printf("\n-----------------------Pruebas Desencolar-------------------------\n");
  // datos
  int vector[] = {0, 1, 2, 3, 4, 5, 6};

  heap_t* heap3 = heap_crear(comparador);
  heap_encolar(heap3,&vector[1]);
  heap_encolar(heap3,&vector[4]);
  heap_encolar(heap3,&vector[5]);
  heap_encolar(heap3,&vector[2]);
  heap_encolar(heap3,&vector[6]);
  heap_encolar(heap3,&vector[3]);

  printf("%d\n",*(int*) heap_ver_max(heap3));

  print_test("La cantidad es 6",heap_cantidad(heap3)==6);
  print_test("EL maximo es 6",heap_ver_max(heap3)==&vector[6]);
  // Pruebo Desencolar
  print_test("Se desencola correctamente el 6",heap_desencolar(heap3)==&vector[6]);
  print_test("La cantidad de elementos es 5",heap_cantidad(heap3)==5);
  print_test("El max es 5",heap_ver_max(heap3)==&vector[5]);
  //Desencolo 5
  print_test("Se desencola correctamente el 5",heap_desencolar(heap3)==&vector[5]);
  print_test("La cantidad de elementos es 4",heap_cantidad(heap3)==4);
  print_test("El max es 4",heap_ver_max(heap3)==&vector[4]);
  //Desencolo 4
  print_test("Se desencola correctamente el 4",heap_desencolar(heap3)==&vector[4]);
  print_test("La cantidad de elementos es 3",heap_cantidad(heap3)==3);
  print_test("El max es 3",heap_ver_max(heap3)==&vector[3]);
  // Desencolo el 3
  print_test("Se desencola correctamente el 3",heap_desencolar(heap3)==&vector[3]);
  print_test("La cantidad de elementos es 2",heap_cantidad(heap3)==2);
  print_test("El max es 2",heap_ver_max(heap3)==&vector[2]);
  //Desencolo el 2
  print_test("Se desencola correctamente el 2",heap_desencolar(heap3)==&vector[2]);
  print_test("La cantidad de elementos es 1",heap_cantidad(heap3)==1);
  print_test("El max es 1",heap_ver_max(heap3)==&vector[1]);
  //Desencolo el 1
  print_test("Se desencola correctamente el 1",heap_desencolar(heap3)==&vector[1]);
  print_test("La cantidad de elementos es 0",heap_cantidad(heap3)==0);
  print_test("EL heap esta vacio",heap_esta_vacio(heap3)==true);
  print_test("El max es NULL",heap_ver_max(heap3)==NULL);

  heap_destruir(heap3,NULL);
  print_test("Se destruyo heap 3 correctamente",true);

}
/////////////////////////////////////////////////////////////////////

void prueba_heapify() {
	int* vector = malloc(sizeof(int)*7);
	print_test("Se crea vector desordenado", vector);
	vector[0] = 50;
	vector[1] = 1;
	vector[2] = 2;
	vector[3] = 3;
	vector[4] = 30;
	vector[5] = 10;
	vector[6] = 80;
	void* v0 = &vector[0];
	void* v1 = &vector[1];
	void* v2 = &vector[2];
	void* v3 = &vector[3];
	void* v4 = &vector[4];
	void* v5 = &vector[5];
	void* v6 = &vector[6];
	void** puntero = malloc(sizeof(void*) * 7);
	puntero[0] = v0;
	puntero[1] = v1;
	puntero[2] = v2;
	puntero[3] = v3;
	puntero[4] = v4;
	puntero[5] = v5;
	puntero[6] = v6;

    heap_t* heap = heap_crear_arr(puntero,7,comparador);
    print_test("Llama a Heapify", heap);
    print_test("El maximo concuerda", heap_ver_max(heap) == v6);
    print_test("Cantidad es 7", heap_cantidad(heap) == 7);

    heap_destruir(heap,NULL);
	print_test("Se destruye el heap", true);
	free(vector);
	free(puntero);
}

/////////////////////////////////////////////////////////////////////

void prueba_heapsort() {
	int* vector = malloc(sizeof(int)*7);
	print_test("Se crea vector desordenado", vector);
	vector[0] = 50;
	vector[1] = 1;
	vector[2] = 2;
	vector[3] = 3;
	vector[4] = 30;
	vector[5] = 10;
	vector[6] = 80;
	void* v0 = &vector[0];
	void* v1 = &vector[1];
	void* v2 = &vector[2];
	void* v3 = &vector[3];
	void* v4 = &vector[4];
	void* v5 = &vector[5];
	void* v6 = &vector[6];
	void** puntero = malloc(sizeof(void*) * 7);
	puntero[0] = v0;
	puntero[1] = v1;
	puntero[2] = v2;
	puntero[3] = v3;
	puntero[4] = v4;
	puntero[5] = v5;
	puntero[6] = v6;

	heap_sort(puntero,7,comparador);

	bool ok = true;
	ok &= puntero[0] == v1;
	ok &= puntero[1] == v2;
	ok &= puntero[2] == v3;
	ok &= puntero[3] == v5;
	ok &= puntero[4] == v4;
	ok &= puntero[5] == v0;
	ok &= puntero[6] == v6;
	print_test("El arreglo está ordenado", ok);

	free(vector);
	free(puntero);
}

/////////////////////////////////////////////////////////////////////

void pruebas_heap_alumno() {
	printf("-----CREAR VACIO-----\n");
	heap_vacio();
	printf("-----ENCOLAR Y DESENCOLAR-----\n");
	heap_insertar();
	heap_eliminar();
	printf("-----HEAPIFY-----\n");
	prueba_heapify();
	printf("-----HEAPSORT-----\n");
	prueba_heapsort();
}
