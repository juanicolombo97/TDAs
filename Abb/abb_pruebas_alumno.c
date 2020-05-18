#define _XOPEN_SOURCE 500
#include "abb.h"
#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const char* vector1, const char* vector2) {
	int pos_actual=0;
	int n1 = (int)strlen(vector1);
	int n2 = (int)strlen(vector2);
	while (pos_actual<n1 && pos_actual<n2) {
		if (vector2[pos_actual]<vector1[pos_actual]){
		    return -1;
    }
		if (vector1[pos_actual]<vector2[pos_actual]) {
		    return 1;
    }
		if (pos_actual==n2-1 && n1!=n2) {
		    return -1;
    }
			pos_actual++;
  }
	if (n2==n1) {
		return 0;
  }
	return 1;
}


void abb_vacio(){
	printf("\nPruebas abb vacio\n\n");
	abb_t* arbol = abb_crear(cmp,NULL);
	print_test("ABB recien creado esta vacio",abb_cantidad(arbol)==0);
	print_test("ABB recien creado no se puede borrar",abb_borrar(arbol,NULL)==false);
	print_test("abb pertenece es false en recien creado",abb_pertenece(arbol,NULL)==false);
	print_test("ABB obtener es false si recien esta creado",abb_obtener(arbol,NULL)==false);
	abb_destruir(arbol);
	print_test("Se destruyo el arbol correctamente",true);
}

void abb_insertar_raiz(){
	printf("Pruebas insertar raiz\n\n");
	abb_t* arbol0 = abb_crear(cmp,NULL);
	char* dato1 = strdup("1");

	print_test("Se inserta raiz",abb_guardar(arbol0,dato1,dato1)==true);
	print_test("La cantidad es 1",abb_cantidad(arbol0)==1);
	print_test("Se obtiene la raiz",abb_obtener(arbol0,dato1)==dato1);
	print_test("La raiz pertenece",abb_pertenece(arbol0,dato1)==true);
	abb_destruir(arbol0);
	print_test("El arbol se destruyo",true);
	free(dato1);
}

void abb_insertar(){
	printf("\nPRUEBAS INSERTAR\n\n");
	char* dato1 = strdup("1");
	char* dato2 = strdup("2");
	char* dato3 = strdup("3");
	abb_t* arbol2 = abb_crear(cmp,NULL);

	// Guardar dato 2
	print_test("Se guarda correctamente",abb_guardar(arbol2,dato2,dato2)==true);
	print_test("El dato2 se guardo y hora pertenece",abb_pertenece(arbol2,dato2)==true);
	print_test("El dato2 guardado se obtiene correctamente",abb_obtener(arbol2,dato2)==dato2);
	print_test("La cantidad es igual a 1",abb_cantidad(arbol2)==1);
	//Guardar dato 1
	print_test("Se guarda correctamente",abb_guardar(arbol2,dato1,dato1)==true);
	print_test("El dato1 se guardo y hora pertenece",abb_pertenece(arbol2,dato1)==true);
	print_test("El dato1 guardado se obtiene correctamente",abb_obtener(arbol2,dato1)==dato1);
	print_test("La cantidad es igual a 2",abb_cantidad(arbol2)==2);
	// Guardar dato 3
	print_test("Se guarda correctamente",abb_guardar(arbol2,dato3,dato3)==true);
	print_test("El dato3 se guardo y hora pertenece",abb_pertenece(arbol2,dato3)==true);
	print_test("El dato3 guardado se obtiene correctamente",abb_obtener(arbol2,dato3)==dato3);
	print_test("La cantidad es igual a 3",abb_cantidad(arbol2)==3);
	// destuyo el Arbol2
	abb_destruir(arbol2);
	free(dato1);
	free(dato2);
	free(dato3);
}

void abb_insertar_repetido(){
	printf("Pruebas insertar repetido\n\n");
	abb_t* arbol20 = abb_crear(cmp,NULL);
	char* dato1 = strdup("1");
	char* dato2 = strdup("2");
	print_test("Se guardo dato 1",abb_guardar(arbol20,dato1,dato1)==true);
	print_test("Se guardo dato 2",abb_guardar(arbol20,dato2,dato2)==true);
	print_test("Se guardo dato 1 en la clave 2 y se modifico",abb_guardar(arbol20,dato2,dato1)==true);
	abb_destruir(arbol20);
	print_test("Se destruyo",true);
	free(dato1);
	free(dato2);
}

void abb_borrar_raiz(){
	printf("\nPRUEBAS BORRAR \n\nBorrar raiz\n\n");
	abb_t* arbol3 = abb_crear(cmp,NULL);
	char* dato1 = strdup("1");
	abb_guardar(arbol3,dato1,dato1);
	print_test("Se borra correctamente la raiz",abb_borrar(arbol3,dato1)==dato1);
	print_test("La raiz ya no pertenece",abb_pertenece(arbol3,dato1)==false);
	print_test("La raiz no se obtiene",abb_obtener(arbol3,dato1)==NULL);
	print_test("La cantidad es igual a 0",abb_cantidad(arbol3)==0);
	print_test("EL arbol se destruyo correcamente",true);
	abb_destruir(arbol3);
	free(dato1);
}

void abb_borrar_hoja(){
	printf("\nPruebas abb borrar hoja\n\n");
	abb_t* arbol4 = abb_crear(cmp,NULL);
	char* dato1 = strdup("1");
	char* dato2 = strdup("2");
	char* dato3 = strdup("3");
	print_test("Se guarda correctamente 2",abb_guardar(arbol4,dato2,dato2)==true);
	print_test("Se guarda correctamente 1",abb_guardar(arbol4,dato1,dato1)==true);
	print_test("Se guarda correctamente 3",abb_guardar(arbol4,dato3,dato3)==true);
	print_test("La cantidad es igual a 3",abb_cantidad(arbol4)==3);
	print_test("Se borro la hoja 3",abb_borrar(arbol4,dato3) == dato3);
	print_test("La hoja 3 ya no pertenece",abb_pertenece(arbol4,dato3)== false);
	print_test("La cantidad es 2",abb_cantidad(arbol4)==2);
	print_test("No se puede obtener elem",abb_obtener(arbol4,dato3)==NULL);
	// La otra hoja ahora
	print_test("Borro la hoja 1",abb_borrar(arbol4,dato1)==dato1);
	print_test("La cantidad es 1",abb_cantidad(arbol4)==1);
	print_test("La clave 1 no pertence",abb_pertenece(arbol4,dato1)==false);
		print_test("No se puede obtener elem",abb_obtener(arbol4,dato1)==NULL);
	// Ultimo, seria raiz.
	print_test("Borro la raiz",abb_borrar(arbol4,dato2)== dato2);
	print_test("La cantidad es 0",abb_cantidad(arbol4)== 0);
	print_test("No pertenece la raiz",abb_pertenece(arbol4,dato2)==false);
	abb_destruir(arbol4);
	print_test("Se destruye correcamente",true);
	free(dato1);
	free(dato2);
	free(dato3);
}

void abb_borrar_hijo_der(){
	printf("\nBorrar nodo con hijo der \n");
	abb_t* arbol5 = abb_crear(cmp,NULL);
	char* dato2 = strdup("2");
	char* dato3 = strdup("3");
	char* dato4 = strdup("5");
	print_test("Se guarda correctamente 2",abb_guardar(arbol5,dato2,dato2)==true);
	print_test("Se guarda correctamente 3",abb_guardar(arbol5,dato3,dato3)==true);
	print_test("Se guarda correcamente 4",abb_guardar(arbol5,dato4,dato4)==true);
	print_test("La cantidad es igual a 3",abb_cantidad(arbol5)==3);

	print_test("Se borra nodo con hijo",abb_borrar(arbol5,dato3) == dato3);
	print_test("Ya no pertence",abb_pertenece(arbol5,dato3)==false);
	print_test("No se puede obtener", abb_obtener(arbol5,dato3)==NULL);
	print_test("La cantidad es 3",abb_cantidad(arbol5)==2);
	// BOrro los otros
	print_test("Se borra el dato 5",abb_borrar(arbol5,dato4)==dato4);
	print_test("Se borra el dato 2",abb_borrar(arbol5,dato2)==dato2);
	print_test("La cantidad es igual a 0",abb_cantidad(arbol5)==0);
	abb_destruir(arbol5);
	print_test("Se destruyo el abb correcamente",true);
	free(dato2);
	free(dato3);
	free(dato4);
}

void abb_borrar_hijo_izq(){
	printf("\nBorrar nodo con hijo izq\n");
	abb_t* arbol5 = abb_crear(cmp,NULL);
	char* dato2 = strdup("2");
	char* dato3 = strdup("3");
	char* dato4 = strdup("5");
	print_test("Se guarda correcamente 4",abb_guardar(arbol5,dato4,dato4)==true);
	print_test("Se guarda correctamente 3",abb_guardar(arbol5,dato3,dato3)==true);
	print_test("Se guarda correctamente 2",abb_guardar(arbol5,dato2,dato2)==true);
	print_test("La cantidad es igual a 3",abb_cantidad(arbol5)==3);

	print_test("Se borra nodo con hijo",abb_borrar(arbol5,dato3) == dato3);
	print_test("Ya no pertence",abb_pertenece(arbol5,dato3)==false);
	print_test("No se puede obtener", abb_obtener(arbol5,dato3)==NULL);
	print_test("La cantidad es 3",abb_cantidad(arbol5)==2);
	// BOrro los otros
	print_test("Se borra el dato 2",abb_borrar(arbol5,dato2)==dato2);
	print_test("Se borra el dato 5",abb_borrar(arbol5,dato4)==dato4);
	print_test("La cantidad es igual a 0",abb_cantidad(arbol5)==0);
	abb_destruir(arbol5);
	print_test("Se destruyo el abb correcamente",true);
	free(dato2);
	free(dato3);
	free(dato4);
}

void abb_borrar_raiz_un_hijo(){
	printf("\nBorrar raiz con hijo\n");
	abb_t* arbol5 = abb_crear(cmp,NULL);
	char* dato2 = strdup("2");
	char* dato3 = strdup("3");
	char* dato4 = strdup("5");
	print_test("Se guarda correcamente 4",abb_guardar(arbol5,dato4,dato4)==true);
	print_test("Se guarda correctamente 3",abb_guardar(arbol5,dato3,dato3)==true);
	print_test("Se guarda correctamente 2",abb_guardar(arbol5,dato2,dato2)==true);
	print_test("La cantidad es igual a 3",abb_cantidad(arbol5)==3);

	print_test("Se borra nodo con hijo",abb_borrar(arbol5,dato3) == dato3);
	print_test("Ya no pertence",abb_pertenece(arbol5,dato3)==false);
	print_test("No se puede obtener", abb_obtener(arbol5,dato3)==NULL);
	print_test("La cantidad es 3",abb_cantidad(arbol5)==2);
	// BOrro los otros
	print_test("Se borra el dato 5",abb_borrar(arbol5,dato4)==dato4);
	print_test("Se borra el dato 2",abb_borrar(arbol5,dato2)==dato2);
	print_test("La cantidad es igual a 0",abb_cantidad(arbol5)==0);
	abb_destruir(arbol5);
	print_test("Se destruyo el abb correcamente",true);
	free(dato2);
	free(dato3);
	free(dato4);

}

void abb_dos_hijos(){
	printf("\nBorrar nodo con dos hijos\n");
	abb_t* arbol6 = abb_crear(strcmp,NULL);
	char* dato1 = strdup("2");
	char* dato2 = strdup("4");
	char* dato3 = strdup("3");
	char* dato4 = strdup("5");
	abb_guardar(arbol6,dato1,dato1);
	abb_guardar(arbol6,dato2,dato2);
	abb_guardar(arbol6,dato3,dato3);
	abb_guardar(arbol6,dato4,dato4);
	print_test("La cantidad es 4",abb_cantidad(arbol6)==4);
	print_test("Borro con dos hijos",abb_borrar(arbol6,dato2)==dato2);
	print_test("No pertence",abb_pertenece(arbol6,dato2)==false);
	print_test("No se puede obtener",abb_obtener(arbol6,dato2)==NULL);
	print_test("La cantidad es 3",abb_cantidad(arbol6)==3);
	abb_borrar(arbol6,dato3);
	abb_destruir(arbol6);
	print_test("Se destruyo correctamente ",true);
	free(dato1);
	free(dato2);
	free(dato3);
	free(dato4);
}

void abb_raiz_dos_hijos(){
	printf("\nBorrar RAIZ con DOS HIJOS \n");
	abb_t* arbol5 = abb_crear(cmp,NULL);
	char* dato2 = strdup("2");
	char* dato3 = strdup("3");
	char* dato4 = strdup("5");
	print_test("Se guarda correctamente 3",abb_guardar(arbol5,dato3,dato3)==true);
	print_test("Se guarda correctamente 2",abb_guardar(arbol5,dato2,dato2)==true);
	print_test("Se guarda correcamente 4",abb_guardar(arbol5,dato4,dato4)==true);
	print_test("La cantidad es igual a 3",abb_cantidad(arbol5)==3);

	print_test("Se borra raiz con dos hijos",abb_borrar(arbol5,dato3) == dato3);
	print_test("Ya no pertence",abb_pertenece(arbol5,dato3)==false);
	print_test("No se puede obtener", abb_obtener(arbol5,dato3)==NULL);
	print_test("La cantidad es 3",abb_cantidad(arbol5)==2);
	// BOrro los otros
	print_test("Se borra el dato 5",abb_borrar(arbol5,dato4)==dato4);
	print_test("Se borra el dato 2",abb_borrar(arbol5,dato2)==dato2);
	print_test("La cantidad es igual a 0",abb_cantidad(arbol5)==0);
	abb_destruir(arbol5);
	print_test("Se destruyo el abb correcamente",true);
	free(dato2);
	free(dato3);
	free(dato4);
}

bool imprimir(const char* clave,void* dato, void* extra){
	printf("%s\n",clave);
	return true;
}

void iter_interno(){
	printf("\nIterador interno\n");
	abb_t* arbol6 = abb_crear(cmp,NULL);
	char* dato1 = strdup("2");
	char* dato2 = strdup("4");
	char* dato3 = strdup("3");
	char* dato4 = strdup("5");

	abb_guardar(arbol6,dato2,dato2);
	abb_guardar(arbol6,dato1,dato1);
	abb_guardar(arbol6,dato3,dato3);
	abb_guardar(arbol6,dato4,dato4);

	abb_in_order(arbol6,imprimir,NULL);

	abb_destruir(arbol6);

	free(dato1);
	free(dato2);
	free(dato3);
	free(dato4);
}

void abb_iterador_externo(){
	printf("\nIterador Externo\n");
	abb_t* arbol6 = abb_crear(cmp,NULL);
	char* dato1 = strdup("2");
	char* dato2 = strdup("4");
	char* dato3 = strdup("3");
	char* dato4 = strdup("5");

	abb_guardar(arbol6,dato2,dato2);
	abb_guardar(arbol6,dato1,dato1);
	abb_guardar(arbol6,dato3,dato3);
	abb_guardar(arbol6,dato4,dato4);

	abb_iter_t* iterador = abb_iter_in_crear(arbol6);
	const char* key = abb_iter_in_ver_actual(iterador);
	printf("La clave es%s\n", key);
	print_test("El iterador esta al principio",strcmp(abb_iter_in_ver_actual(iterador),dato4) == 0);
	while(!abb_iter_in_al_final(iterador)){
		const char* clave = abb_iter_in_ver_actual(iterador);
		printf("La clave es%s\n",clave );
		abb_iter_in_avanzar(iterador);
	}
	abb_iter_in_destruir(iterador);
	abb_destruir(arbol6);
	free(dato1);
	free(dato2);
	free(dato3);
	free(dato4);
}


void pruebas_abb_alumno(){
	abb_vacio();
	abb_insertar_raiz();
	abb_insertar();
	abb_insertar_repetido();
	abb_borrar_raiz();
	abb_borrar_hoja();
 	abb_borrar_hijo_der();
	abb_borrar_hijo_izq();
	abb_borrar_raiz_un_hijo();
	abb_raiz_dos_hijos();
  abb_dos_hijos();
	iter_interno();
	abb_iterador_externo();
}
