#include "lista.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>




bool pruebasvolumen(){
	lista_t* lista1 = lista_crear();
	int vector[1001];
	for(int x = 0;x<=1000;x++){
		vector[x]=x;
		lista_insertar_ultimo(lista1,&vector[x]);

	}
	
	for (int x = 0;x<= 1000;x++){
		if (lista_borrar_primero(lista1)!= &vector[x]){
			lista_destruir(lista1,NULL);
			return false;
		}
	}
	lista_destruir(lista1,NULL);
	return true;
}

bool pruebasvolumen_principio(){
	lista_t* lista2 = lista_crear();
	int vector[1001];
	for(int x = 0;x<=1000;x++){
		vector[x]=x;
		lista_insertar_primero(lista2,&vector[x]);

	}
	
	for(int x = 1000; x>=0; x--){
    	if (lista_borrar_primero(lista2) != &vector[x]){
        	lista_destruir(lista2,NULL);
        	return false;
        }
    }
	lista_destruir(lista2,NULL);
	return true;

}

void pruebas_lista_alumno(void){
	// Creo una lista y me fijo si esta vacia
	lista_t* lista = lista_crear();
	print_test("La lista recien creada esta vacia",lista_esta_vacia(lista)==true);
	//Pruebo que sacar elementos o ver de una lista recien creada no se puede
	print_test("La lista vacia no se puede sacar elementos",lista_borrar_primero(lista)== NULL);
	print_test("No se puede ver el primer elemento de una lista vacia",lista_ver_primero(lista)==NULL);
	print_test("No se puede ver ultimo elemento de una lista vacia",lista_ver_ultimo(lista)==NULL);
	print_test("Largo de una lista recien creada es 0",lista_largo(lista)==0);
	//Pruebas insertar elementos lista vacia
	int a = 3;
	void* b = &a;
	print_test("Se puede insertar al principio",lista_insertar_primero(lista,b)==true);
	print_test("El primer elemento se inserta correctamente",lista_ver_primero(lista)==b);
	print_test("EL primero elemento tambien es el ultimo", lista_ver_ultimo(lista)==b);
	print_test("EL largo de la lista es el correcto",lista_largo(lista)==1);
	// Pruebo que se pueda eliminar el elemento
	print_test("Se elimina correctamente el primer elemento",lista_borrar_primero(lista)==b);
	// ahora puedo insertar al final
	print_test("Se insert un elemento al final en una lista vacia correctamente",lista_insertar_ultimo(lista,b)==true);
	print_test("Se inserta correctamente alfinal",lista_ver_primero(lista)==b);
	print_test("La lista no esta vacia",lista_esta_vacia(lista)== false);
	print_test("Largo de la lista distinto de cero", lista_largo(lista)==1);
	print_test("Se elimina el elemento correctamente",lista_borrar_primero(lista)==b);
	print_test("La lista esta vacia",lista_esta_vacia(lista)==true);
	lista_destruir(lista,NULL);
	
	// Pruebas de volumen insertando al final
	print_test("Pruebas de volumen",pruebasvolumen() == true);
	// Pruebas de volumen insertando al principio
	print_test("Pruebas de volumen insertando al principio",pruebasvolumen_principio()== true);

	lista_t* lista3 = lista_crear();
	print_test("Se puede apilar NULL en lista recien creada al principio",lista_insertar_primero(lista3,NULL)==true);
	print_test("Se puede apilar NULL en lista recien creada al final",lista_insertar_ultimo(lista3,NULL)==true);
	lista_destruir(lista3,NULL);

	// Pruebas iterador externo
	lista_t* lista4 = lista_crear();
	lista_iter_t* iterador = lista_iter_crear(lista4);
	print_test("El iterador recien creado apunta a NULL",lista_iter_al_final(iterador)== true);
	print_test("El valor actual del iterador recien creado es NULL",lista_iter_ver_actual(iterador)==NULL);
	print_test("No se puede avanzar un iterador si la lista esta vacia",lista_iter_avanzar(iterador)==false);
	print_test("Se inserta un elemento",lista_iter_insertar(iterador,b)==true);
	print_test("Insertar elemento posicion iterador recien creado, es el primer elemento",lista_iter_ver_actual(iterador)==b);
	
	// Al eliminar cuando se crea el iterador cambia la primera posicion de la lista
	lista_iter_borrar(iterador);
	print_test("Se modifica el primer elemento de la lista",lista_ver_primero(lista4)==NULL);

	int c = 4;
	void* d =&c;
	lista_iter_insertar(iterador,d);
	print_test("SI el iterador esta en el primer elemento, inserta al principio",lista_ver_primero(lista4)==d);
	
	// Si el iterador esta al final, inserta al final
	int f = 4;
	void* g =&f;
	lista_iter_avanzar(iterador);
	lista_iter_avanzar(iterador);
	lista_iter_insertar(iterador,g);
	print_test("SI esta alfinal,inserta alfinal",lista_ver_ultimo(lista4)==g);
	print_test("Avanza bien",lista_iter_ver_actual(iterador)==g);

	// Remover en la ultima posicion cambia el ultimo de la lista
	lista_iter_borrar(iterador);
	print_test("Se modifica el ultimo de la lista",lista_ver_ultimo(lista4)==d);
	lista_iter_destruir(iterador);
	lista_destruir(lista4,NULL);
	

}