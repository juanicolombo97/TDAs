#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/
bool pruebasvolumen(){
    pila_t* pila2 = pila_crear();
    int vector[1001];
    for(int i =0; i <= 1000;i++){
        vector[i] = i;
        pila_apilar(pila2, &vector[i]);
        if(pila_ver_tope(pila2) != &vector[i]){
            pila_destruir(pila2);
            return false;
        }
    }
    
    for(int x = 1000; x>=0; x--){
        if (pila_desapilar(pila2) != &vector[x]){
            pila_destruir(pila2);
            return false;
        }
    }
    pila_destruir(pila2);
    return true;
}

void pruebas_pila_alumno() {
    pila_t* ejemplo = NULL;

    print_test("Puntero inicializado a NULL", ejemplo == NULL);
   

   // Pruebas crear pila vacia
    printf("pila vacia\n");

    pila_t* pila0 = pila_crear();
    //inicio pruebas

    print_test("Crear pila vacia",pila0 != NULL);
    print_test("Cantidad de elementos igual a 0",pila_esta_vacia(pila0)==true);
    // prueba que no se puede desapilar o ver tope cuando se crea
    print_test("Se puede desapilar pila vacia", pila_desapilar(pila0) == NULL);
    print_test("El tope es NULL", pila_ver_tope(pila0)== NULL);
    //destruyo pila
    pila_destruir(pila0);
    print_test("la pila se destruyo",true);

    // Inicio pruebas con algunos elementos
    printf("INICIO PRUEBAS CON ELEMENTOS \n");
    pila_t* pila1 = pila_crear();
    int valor1=1, valor2=2, valor3=3, valor4=4;
    void* p1 = &valor1;
    void* p2 = &valor2;
    void* p3 = &valor3;
    void* p4 = &valor4;
    // Pruebo que pueda apilar
    print_test("Se puede apilar el valor1",pila_apilar(pila1,p1)== true);
    print_test("Se puede apilar el valor2",pila_apilar(pila1,p2)== true);
    print_test("Se puede apilar el valor3",pila_apilar(pila1,p3)== true);
    print_test("Se puede apilar el valor4",pila_apilar(pila1,p4)== true);
    // Prueba que desapila y el tope
    print_test("El tope es correcto",pila_ver_tope(pila1)==p4);
    print_test("Se puede desaplar el valor1",pila_desapilar(pila1)== p4);
    print_test("El tope es correcto",pila_ver_tope(pila1)==p3);
    print_test("Se puede desaplar el valor1",pila_desapilar(pila1)== p3);
    print_test("El tope es correcto",pila_ver_tope(pila1)==p2);
    print_test("Se puede desaplar el valor1",pila_desapilar(pila1)== p2);
    print_test("El tope es correcto",pila_ver_tope(pila1)==p1);
    print_test("Se puede desaplar el valor1",pila_desapilar(pila1)== p1);
    // veo si esta vacia la pila
    print_test("El tope es nulo",pila_ver_tope(pila1)==NULL);
    print_test("La pila esta vacia", pila_esta_vacia(pila1)== true);
    // dstruyo la pila
    pila_destruir(pila1);
    print_test("la pila se destruyo",true);

    
    print_test("Pruebas de volumen",pruebasvolumen());
  }