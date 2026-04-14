#ifndef __LISTA_SIMPLE_H__
#define __LISTA_SIMPLE_H__

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Nodo {
    void* dato;
    struct Nodo* siguiente;
} Nodo;

typedef struct {
    Nodo* head;
    Nodo* tail;
} Lista;

// Callbacks
typedef int (*CompararFunc)(void*, void*);
typedef void (*ImprimirFunc)(void*);

//Funciones para nodo
Nodo* crearNodo(void *dato, size_t size);
void borrarNodo(Nodo *n);
bool modificarNodo(Nodo *n, void *d, size_t size);

// Crear / estado
Lista* crearLista();
bool esVacia(Lista* lista);

// Inserciones
void insertarInicio(Lista* lista, void* dato, size_t size);
void insertarFinal(Lista* lista, void* dato, size_t size);
void insertarPorPosicion(Lista* lista, void* dato, size_t size, int pos);

// Eliminaciones
void eliminarInicio(Lista *lista);
void eliminarFinal(Lista *lista);
void eliminarPorPosicion(Lista* lista, int pos);
void eliminarPorElemento(Lista* lista, void* dato, CompararFunc cmp);
void eliminarElementosIguales(Lista *lista, void *dato, CompararFunc cmp);

// Búsquedas
void* buscarPorPosicion(Lista* lista, int pos);
int buscarPorElemento(Lista* lista, void* dato, CompararFunc cmp);

// Navegación
Nodo* primero(Lista* lista);
Nodo* ultimo(Lista* lista);
Nodo* siguiente(Nodo* actual);

// Modificar
void modificar(Lista* lista, int pos, void* dato, size_t size);

// Utilidad
void imprimirLista(Lista* lista, ImprimirFunc imprimir);
void vaciarLista(Lista* lista);
void borrarLista(Lista* lista);

#endif
