#include "lista_simple.h"

Nodo* crearNodo(void *dato, size_t size){
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    
    if(nuevo!=NULL){
        nuevo->siguiente = NULL;
        nuevo->dato = malloc(size); //tanto malloc y dato son de tipo void
        memcpy(nuevo->dato, dato, size);//destino, origen, tamaño
    }
    return nuevo;
}

void borrarNodo(Nodo *n){
    if(n != NULL){
        free(n->dato);
        free(n);
    }
}

bool modificarNodo(Nodo *n, void *d, size_t size){
    if(n != NULL){
        memcpy(n->dato, d, size);
        return true;
    }
    return false;
}
Lista* crearLista(){
    Lista *lista = (Lista *)malloc(sizeof(Lista));
    
    if(lista != NULL){
        lista->head = lista->tail = NULL;
    }
    return lista;
}
bool esVacia(Lista* lista){
    return lista->head == NULL;
}

void insertarInicio(Lista* lista, void* dato, size_t size){
    Nodo *nuevo = crearNodo(dato, size);
    
    if(esVacia(lista)){
        lista->head = lista->tail = nuevo;
    }else{
        nuevo->siguiente = lista->head;
        lista->head = nuevo;
    }
}

void insertarFinal(Lista* lista, void* dato, size_t size){
    Nodo *nuevo = crearNodo(dato, size);
    
    if(esVacia(lista)){
        lista->head = lista->tail = nuevo;
    }else{
        lista->tail->siguiente = nuevo;
        lista->tail = nuevo;
    }
}

void insertarPorPosicion(Lista* lista, void* dato, size_t size, int pos){
    if(esVacia(lista)){
        return;
    }
    
    int total = 0;
    
    for(Nodo *tmp = lista->head; tmp != NULL; tmp = tmp->siguiente){
        total++;
    }
    
    if(pos==0){
        insertarInicio(lista, dato, size);
    }else if(pos == total){
        insertarFinal(lista, dato, size);
    }else if(pos >= 1 && pos < total){
        Nodo *nuevo = crearNodo(dato, size);
        Nodo *tmp = lista->head;

        for(int i = 0; i < pos - 1; i++){
            tmp = tmp->siguiente;
        }

        nuevo->siguiente = tmp->siguiente;
        tmp->siguiente = nuevo;
    }else{
        printf("La posicion no es valida\n");
    }
}

void eliminarInicio(Lista *lista){
    if(esVacia(lista))return;

    Nodo *tmp = lista->head;

    if(lista->head == lista->tail){
        lista->head = lista->tail = NULL;
    }else{
        lista->head = lista->head->siguiente;
    }
    borrarNodo(tmp);
}

void eliminarFinal(Lista *lista){
    if(esVacia(lista))return;
    
    if(lista->head == lista->tail){
        borrarNodo(lista->head);
        lista->head = lista->tail = NULL;
        return;
    }

    Nodo *tmp = lista->head;

    while(tmp->siguiente != lista->tail){
        tmp = tmp->siguiente;
    }

    borrarNodo(lista->tail);
    lista->tail = tmp;
    lista->tail->siguiente = NULL;
}

void eliminarPorPosicion(Lista* lista, int pos){
    Nodo* actual = lista->head;
    Nodo* anterior = NULL;
    int i = 0;

    while(actual && i < pos){
        anterior = actual;
        actual = actual->siguiente;
        i++;
    }

    if(!actual) return; 

    if(actual == lista->tail){
        lista->tail = anterior;
    }

    anterior->siguiente = actual->siguiente;
    borrarNodo(actual);
}

void eliminarPorElemento(Lista* lista, void* dato, CompararFunc cmp){
    if(!lista || esVacia(lista)) return;

    Nodo *actual = lista->head;
    Nodo *anterior = NULL;

    while(actual){
        if(cmp(actual->dato, dato) == 0){
            if(anterior == NULL){
                lista->head = actual->siguiente;
                if(actual == lista->tail)
                    lista->tail = lista->head;
            }else{
                anterior->siguiente = actual->siguiente;
                if(actual == lista->tail)
                    lista->tail = anterior;
            }

            borrarNodo(actual);
            return; 
        }

        anterior = actual;
        actual = actual->siguiente;
    }
}
void eliminarElementosIguales(Lista *lista, void *dato, CompararFunc cmp){
     if(!lista || esVacia(lista)) return;

    Nodo* actual = lista->head;
    Nodo* anterior = NULL;

    while(actual){
        if(cmp(actual->dato, dato) == 0){
            Nodo* temp = actual;

            if(anterior == NULL){
                lista->head = actual->siguiente;
                actual = lista->head;
            }else{
                anterior->siguiente = actual->siguiente;
                actual = actual->siguiente;
            }

            if(temp == lista->tail)
                lista->tail = anterior;

            borrarNodo(temp);
        }else{
            anterior = actual;
            actual = actual->siguiente;
        }
    }
}

// Búsquedas
void* buscarPorPosicion(Lista* lista, int pos){
    if(!lista || pos < 0) return NULL;

    Nodo* actual = lista->head;
    int i = 0;

    while(actual){
        if(i == pos)
            return actual->dato;

        actual = actual->siguiente;
        i++;
    }

    return NULL;
}
int buscarPorElemento(Lista* lista, void* dato, CompararFunc cmp){
    if(!lista) return -1;

    Nodo* actual = lista->head;
    int i = 0;

    while(actual){
        if(cmp(actual->dato, dato) == 0)
            return i;

        actual = actual->siguiente;
        i++;
    }

    return -1;
}

// Navegación
Nodo* primero(Lista* lista){
    return lista ? lista->head : NULL;
}
Nodo* ultimo(Lista* lista){
    return lista ? lista->tail : NULL;
}
Nodo* siguiente(Nodo* actual){
    return actual ? actual->siguiente : NULL;
}

// Modificar
void modificar(Lista* lista, int pos, void* dato, size_t size){
     if(!lista || pos < 0) return;

    Nodo* actual = lista->head;
    int i = 0;

    while(actual){
        if(i == pos){
            free(actual->dato);
            actual->dato = malloc(size);
            memcpy(actual->dato, dato, size);
            return;
        }
        actual = actual->siguiente;
        i++;
    }
}

// Utilidad
void imprimirLista(Lista* lista, ImprimirFunc imprimir){
    if(!lista) return;

    Nodo* actual = lista->head;

    while(actual){
        imprimir(actual->dato);
        actual = actual->siguiente;
    }
}
void vaciarLista(Lista* lista){
     if(!lista) return;

    Nodo* actual = lista->head;

    while(actual){
        Nodo* temp = actual;
        actual = actual->siguiente;
        borrarNodo(temp);
    }

    lista->head = NULL;
    lista->tail = NULL;
}
void borrarLista(Lista* lista){
     if(!lista) return;

    vaciarLista(lista);
    free(lista);
}
