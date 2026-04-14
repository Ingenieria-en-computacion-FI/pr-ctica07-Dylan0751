#include "lista_simple.h"
#include <stdio.h>
//un main sencillo
void imprimirInt(void* dato){
    printf("%d ", *(int*)dato);
}

int main(){
    Lista* lista = crearLista();

    int a = 10, b = 20, c = 30;

    insertarFinal(lista, &a, sizeof(int));
    insertarFinal(lista, &b, sizeof(int));
    insertarFinal(lista, &c, sizeof(int));

    imprimirLista(lista, imprimirInt);

    borrarLista(lista);
    return 0;
}