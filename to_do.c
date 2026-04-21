#include <stdio.h>
#include <stdlib.h>

typedef struct Tarea{
    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
} Tarea;

typedef struct Nodo{
    Tarea T;
    struct Nodo *Siguiente;
} Nodo;

Nodo* crearListaVacia(){
    return NULL;
}

Nodo * crearNodo(Tarea T){
    Nodo* nuevo = (Nodo *)malloc(sizeof(Nodo));
    nuevo->T = T;
    nuevo->Siguiente = NULL;
    return nuevo;
}

void insertarNodo(Nodo ** inicio, Nodo *nodo){
    nodo->Siguiente = *inicio;
    *inicio = nodo;
}

void mostrarTareas(Nodo * Lista){
    while(Lista != NULL){
        printf("\nTarea numero: %d", Lista->T.TareaID);
        puts(Lista->T.Descripcion);
        Lista = Lista->Siguiente;
    }
}

int main(){
    Nodo* pendientes;
    pendientes = crearListaVacia();

    int id = 1000;
    int continuar = 1;
    while(!continuar){
        Tarea* nueva;
        nueva = (Tarea *) malloc(sizeof(Tarea));
        printf("Ingrese la descripcion de la tarea:");
        fflush(stdin);
        nueva->Descripcion = malloc(50 * sizeof(char));
        gets(nueva->Descripcion);

        int duracion;
        printf("Ingrese la duracion de la tarea (10 - 100)");
        scanf("%d", &nueva->Duracion);
        
        nueva->TareaID = id;
        id++;

        Nodo * nuevoNodo = crearNodo(*nueva);
        insertarNodo(&pendientes, nuevoNodo);
        printf("Agregar otra tarea?\n0. Si\n1. No\n");
        scanf("%d", &continuar);
    }

    printf("Tareas pendientes:\n");
    mostrarTareas(pendientes);
    return 0;
}
