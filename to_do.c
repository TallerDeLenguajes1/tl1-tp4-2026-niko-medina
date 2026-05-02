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

Nodo* crearListaVacia();
Nodo * crearNodo(Tarea T);
void insertarNodo(Nodo ** inicio, Nodo *nodo);
void mostrarTareas(Nodo * Lista);
void cargarTareas(Nodo ** pendientes);
void liberarLista(Nodo *lista);

int main(){
    Nodo* pendientes;
    pendientes = crearListaVacia();
    cargarTareas(&pendientes);

    printf("Tareas pendientes:\n");
    mostrarTareas(pendientes);

    liberarLista(pendientes);
    pendientes = NULL;
    return 0;
}

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
        printf("Tarea numero: %d\n", Lista->T.TareaID);
        printf("Descripcion: ");
        puts(Lista->T.Descripcion);
        Lista = Lista->Siguiente;
    }
}

void cargarTareas(Nodo ** pendientes){
    int id = 1000;
    int continuar = 0;
    do{
        Tarea* nueva;
        nueva = (Tarea *) malloc(sizeof(Tarea));
        printf("Ingrese la descripcion de la tarea: ");
        nueva->Descripcion = malloc(50 * sizeof(char));
        fgets(nueva->Descripcion, 50, stdin);

        printf("Ingrese la duracion de la tarea (10 - 100): ");
        scanf("%d", &nueva->Duracion);
        getchar();

        nueva->TareaID = id;
        id++;

        Nodo * nuevoNodo = crearNodo(*nueva);
        insertarNodo(pendientes, nuevoNodo);
        printf("Agregar otra tarea?\n0. Si\n1. No\n");
        scanf("%d", &continuar);
        getchar();
    }while(!continuar);
}

void liberarLista(Nodo *lista){
    Nodo *aux;
    while(lista != NULL){
        aux = lista;
        lista = lista->Siguiente;
        free(aux->T.Descripcion);
        free(aux);
    }
}