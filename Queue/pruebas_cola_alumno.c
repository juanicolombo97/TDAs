#include "cola.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>

// Pruebas cola

bool pruebasvolumen(){
	cola_t* cola1 = cola_crear();
	int vector[1001];
	for(int x = 0;x<=1000;x++){
		vector[x]=x;
		cola_encolar(cola1,&vector[x]);

	}
	
	for (int x = 0;x<= 1000;x++){
		if (cola_desencolar(cola1)!= &vector[x]){
			cola_destruir(cola1,NULL);
			return false;
		}
	}
	cola_destruir(cola1,NULL);
	return true;
}






void pruebas_cola_alumno(){
	//Se fija q la cola creada este vacia
	cola_t* cola = cola_crear();

	print_test("La cola creada esta vacia",cola_esta_vacia(cola) == true);
	// Prueba encolar un elemento
	int a = 3;
	void* b = &a;
	print_test("Se puede encolar", cola_encolar(cola,b) == true);
	print_test("No esta vacia la cola",cola_esta_vacia(cola)== false);
	print_test("El primer elemento es correcto",cola_ver_primero(cola) ==b );
	// pruebo que se pueda desencolar un elemento
	print_test("Se puede desencolar",cola_desencolar(cola)== b);
	print_test("La cola esta vacia",cola_esta_vacia(cola)== true);
	cola_destruir(cola,NULL);
	print_test("La cola se destruyo",true);
	//prueba volumen
	print_test("Pruebas de volumen",pruebasvolumen() == true);
	// se puede encolar el elemento NULL
	cola_t* cola2 = cola_crear();
	print_test("Se puede encolar el elemento NULL",cola_encolar(cola2,NULL)== true);
	cola_destruir(cola2,NULL);
	// pruebo que no se puede desapilar o ver tope en una cola recien creada
	cola_t* cola3 = cola_crear();
	print_test("No se puede desencolar una cola recien creada",cola_desencolar(cola3)== false);
	print_test("No se puede ver primero de cola recien creada",cola_ver_primero(cola3)==NULL);
	cola_destruir(cola3,NULL);
	}


