#include "hash.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define  capacidadinicial 97 // debe ser un num primo

// Definicion de los structs

struct nodo_hash{
	void** dato;
  char* clave;
  int estado;// 0= vacio,1=ocupado,-1=borrado
};
typedef struct nodo_hash nodo_t;

struct hash {
  size_t cantidad; // cantidad elementos en la tabla
  size_t capacidad; // capacidad de la tabla
  nodo_t *tabla; // arreglo de nodos
  hash_destruir_dato_t destruir;

};

struct hash_iter{
  size_t pos_actual;
  const hash_t* hash;
};

//Funcion de hashing, que devuelve una posicion del arreglo
size_t hashing(size_t capacidad,const char* clave){
	unsigned int num1=378551,num2=63689,clave_numerica = 0;
	size_t tam = capacidad;
	for(int i =0; *clave;clave++,i++){
		clave_numerica = clave_numerica * num2 + (unsigned int)(*clave);
		num2= num2 * num1;
	}
	return (clave_numerica%tam);
}
//Funciones auxiliares
char *strdup (const char *s) {
    char *d = malloc (strlen (s) + 1);
    if (d == NULL) return NULL;
    strcpy (d,s);
    return d;
}

nodo_t* crear_tabla(size_t capacidad){
	nodo_t* tabla = malloc(capacidad * sizeof(nodo_t));
	if(!tabla){
		return NULL;
	}
	// Inicializo la tabla
	for(int x=0;x<capacidad;x++){
		tabla[x].clave = NULL;
		tabla[x].dato = NULL;
		tabla[x].estado = 0;
	}
	return tabla;
}

size_t buscar_pos(nodo_t* tabla,const char* clave,size_t capacidad){
	size_t pos= hashing(capacidad,clave);
	// Me fijo si la posicion encontrada esta vacia o tienen misma clave
	if(tabla[pos].estado == 0 || (tabla[pos].estado ==1 && strcmp(tabla[pos].clave,clave)==0)){
		return pos;
	}
	// Si la posicion es invalida llegamos a una colision que tenemos que arreglar
	for(int x=1;x<=capacidad;x++){
		// Utilizo quadratic probing
		pos = (pos + (x*x)) % capacidad;
		if(tabla[pos].estado == 0 || (tabla[pos].estado ==1 && strcmp(tabla[pos].clave,clave)==0)){
			return pos;
		}
	}
	//SI llego aca es que no encontro una posicion entonces devolvemos el doble de capacidad
	return capacidad;
}

bool copiar_datos(nodo_t* tabla_nueva,size_t capacidad_anterior,hash_t* hash,size_t capacidad){
	for(int x=0;x<capacidad_anterior;x++){
		// Salteo lugares vacios.
		if(hash->tabla[x].estado == 0){
			continue;
		}
		size_t pos = buscar_pos(tabla_nueva,hash->tabla[x].clave,capacidad);
		if(pos== capacidad){
			free(tabla_nueva);
			return false;
		}
		tabla_nueva[pos].clave = hash->tabla[x].clave;
		tabla_nueva[pos].dato = hash->tabla[x].dato;
		tabla_nueva[pos].estado = 1;
	}
	return true;
}

bool redimensionar(hash_t* hash,size_t capacidad){

	nodo_t* tabla_nueva = crear_tabla(capacidad);
	nodo_t* tabla_vieja = hash->tabla;
	if(!tabla_nueva) {
		free(tabla_nueva);
		return false;
	}
	size_t capacidad_anterior = hash->capacidad;
	copiar_datos(tabla_nueva,capacidad_anterior,hash,capacidad);
	free(tabla_vieja);
	hash->tabla = tabla_nueva;
	hash->capacidad = capacidad;
	return true;
}

// PRIMITIVAS DE HASH

hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
	//Se pide memoria para el hash
	hash_t* hash = malloc(sizeof(hash_t));
	//Compruebo que se obtubo correctamente sino devuevlo NULL
	if(!hash){
		return NULL;
	}
	// Ahora pedimos memoria para la tabla hash
	hash->capacidad= capacidadinicial;
	hash->tabla = crear_tabla(hash->capacidad);
	//Veo si se creo correctamente, sino libero la memoria pedida para hash
	if(!hash->tabla){
		free(hash);
		return NULL;
	}
	hash->cantidad = 0;
	hash->destruir = destruir_dato;
	return hash;
}

size_t hash_cantidad(const hash_t *hash){
	if(!hash){
		return 0; // devuelve 0 si el hash es nulo
	}
	return hash->cantidad;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato){
	if(!hash){
		return false;
	}
	// Verifico si hay que redimensionar
	if(hash->cantidad >= (hash->capacidad / 2)){
		redimensionar(hash,hash->capacidad *2);
	}
	size_t pos = buscar_pos(hash->tabla,clave,hash->capacidad);
	if(hash->capacidad == pos){
		return false;
	}
	//Si tienen la misma clave
	if(hash->tabla[pos].estado == 1){
		// Me fijo si hay que destruir el destruir dato
		if(hash->destruir){
			hash->destruir(hash->tabla[pos].dato);
		}
		hash->tabla[pos].dato = dato;
		return true;
	}
	// Si el lugar esta vacio

	if(hash->tabla[pos].estado == 0){
		char* clave_aux = strdup(clave);
		if(!clave_aux){
			free(clave_aux);
			return false;
		}
		hash->tabla[pos].clave = clave_aux;
		hash->tabla[pos].dato = dato;
		hash->cantidad++;
		hash->tabla[pos].estado = 1;
	}

	return true;
}

bool hash_pertenece(const hash_t *hash, const char *clave){
	if(!hash){
		return false;
	}
	if(hash->cantidad == 0){
		return false;
	}
	size_t pos = buscar_pos(hash->tabla,clave,hash->capacidad);
	if(hash->capacidad == pos || hash->tabla[pos].estado != 1){
		return false;
	}
	return (strcmp(hash->tabla[pos].clave,clave)==0);
}

void *hash_obtener(const hash_t *hash, const char *clave){
	if(!hash){
		return NULL;
	}
	if(hash->cantidad == 0){
		return NULL;
	}
	size_t pos = buscar_pos(hash->tabla,clave,hash->capacidad);
	if(hash->capacidad == pos || hash->tabla[pos].estado != 1){
		return NULL;
	}
	return hash->tabla[pos].dato;
}

void *hash_borrar(hash_t *hash, const char *clave){
	if(!hash){
		return NULL;
	}

	size_t pos = buscar_pos(hash->tabla,clave,hash->capacidad);
	if(hash->capacidad == pos || hash->tabla[pos].estado == -1){
		return NULL;
	}
	if(hash->tabla[pos].estado == 1){
	hash->cantidad--;
	hash->tabla[pos].estado = -1;
}
	free(hash->tabla[pos].clave);
	hash->tabla[pos].clave = NULL;
	return hash->tabla[pos].dato;
}

void hash_destruir(hash_t *hash){
	if(!hash){
		return;
	}
	for(int x=0;x< hash->capacidad;x++){
		if(hash->tabla[x].estado == 1){
			if(hash->destruir){
				hash->destruir(hash->tabla[x].dato);

			}
			free(hash->tabla[x].clave);
		}
	}
	free(hash->tabla);
	free(hash);
}


hash_iter_t *hash_iter_crear(const hash_t *hash){
  hash_iter_t* iter = malloc(sizeof(hash_iter_t));
  if(!iter) return NULL;
  iter->hash = hash;
  size_t pos = 0;
	while(pos < hash->capacidad && hash->tabla[pos].estado != 1){
		pos++;
	}
	if(pos < hash->capacidad && hash->tabla[pos].estado != 1){
		iter->pos_actual = hash->capacidad;
		return iter;
	}
	iter->pos_actual = pos;
  return iter;
}

bool hash_iter_avanzar(hash_iter_t *iter){
  if(iter->pos_actual == iter->hash->capacidad) return false;
	if(iter->hash->cantidad == 1){
		iter->pos_actual = iter->hash->capacidad;
		return false;
	}
	size_t pos = iter->pos_actual+1;
	while(pos < iter->hash->capacidad && iter->hash->tabla[pos].estado != 1){
		pos++;
	}
	iter->pos_actual = pos;
  return true;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter){
	if(iter->hash->cantidad == 0 || iter->pos_actual == iter->hash->capacidad) return NULL;
	return iter->hash->tabla[iter->pos_actual].clave;
}

bool hash_iter_al_final(const hash_iter_t *iter){
	if(iter->hash->cantidad == 0 || iter->pos_actual == iter->hash->capacidad) return true;
	return iter->pos_actual == iter->hash->capacidad;
}

void hash_iter_destruir(hash_iter_t* iter){
  free(iter);
}
