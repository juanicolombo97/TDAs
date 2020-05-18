#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>


// Definicion de los tipos de datos
struct lista;
typedef struct lista lista_t;
struct lista_iter;
typedef struct lista_iter lista_iter_t;
// Primitiva de la lista


//Crea una lista
// Post: Devuelve una lista vacia
lista_t *lista_crear(void);

//Devuelve true si la lista esta vacia, y false en el caso contrario
//Pre: La lista fue creada
bool lista_esta_vacia(const lista_t *lista);

// Inserta un elemento al principio de la lista y devuelve true, en el caso de no poder devuelve false
//Pre: La lista se creo
//Post:Se agrego un elemento a la lista,este se encuentra al principio
bool lista_insertar_primero(lista_t *lista, void *dato);

//Inserta un elemento al final de la lista y devuelve true, en caso de no poder devuelve false
//Pre:La lista fue creada
//Post: Se agrego un elemento al final de la lista y devuelve true, en caso contrario false
bool lista_insertar_ultimo(lista_t *lista, void *dato);

//Se elimina el primer elemento de la lista, salvo q esta este vacia
//en tal caso se devuelve NULL
//Pre: La lista fue creada
//Post: Se devuelve el primer elemento de la lista, y se lo elimina, si esta no estaba vacia
void *lista_borrar_primero(lista_t *lista);

//Se devuelve el primer elemento de la lista si esta no estaba vacia
//Pre: La lista fue creada
//Post: Se devuelve el primer elemento de la lista si esta no estaba vacia, sino devuelve NULL
void *lista_ver_primero(const lista_t *lista);

//Se devuelve el ultimo elemento de la lista en el caso que esta no este vacia
//Pre: Se creo la lista
//POst: Devuelve el ultimo elemento de la lista, en el caso que no este vacia, sino devuelve NULL
void *lista_ver_ultimo(const lista_t* lista);

//Devuelve el largo de la lista
//Pre: La lista fue creada
//Post: Se devolvio el largo de la lista
size_t lista_largo(const lista_t *lista);

//La lista se destruye, En el caso de recibir destruir_dato(), tambien elimina el dato
//Pre: La lista fue creada.Destruir_dato() , es una funcion capas de destruir los datos
// o NULL en caso que no se use
//Post: Se eliminaron todos los elementos de la lista
void lista_destruir(lista_t *lista, void destruir_dato(void *));


// Primitiva del iterador interno


// la funcion visitar devuelve true si se debe seguir iterando, y false en caso contrario
//Pre; La lista fue creada
//Post: se itero la lista
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);


// Primitivas del iterador externo

lista_iter_t *lista_iter_crear(lista_t *lista);
bool lista_iter_avanzar(lista_iter_t *iter);
void *lista_iter_ver_actual(const lista_iter_t *iter);
bool lista_iter_al_final(const lista_iter_t *iter);
void lista_iter_destruir(lista_iter_t *iter);
bool lista_iter_insertar(lista_iter_t *iter, void *dato);
void *lista_iter_borrar(lista_iter_t *iter);



// Pruebas del alumno

//Realiza las pruebas echas por el alumno
void pruebas_lista_alumno(void);

#endif // LISTA_H