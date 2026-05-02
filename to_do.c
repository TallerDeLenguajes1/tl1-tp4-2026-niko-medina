#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void marcarRealizadas(Nodo ** pendientes, Nodo ** realizadas);
void moverTarea(Nodo **pendientes, Nodo **realizadas, int id);
void liberarLista(Nodo * lista);

int main(){
    Nodo* pendientes;
    pendientes = crearListaVacia();
    cargarTareas(&pendientes);

    Nodo * realizadas;
    realizadas = crearListaVacia();
    marcarRealizadas(&pendientes, &realizadas);

    printf("Tareas pendientes:\n");
    mostrarTareas(pendientes);
    printf("Tareas realizadas:\n");
    mostrarTareas(realizadas);

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
        printf("Duracion: %d horas\n", Lista->T.Duracion);
        Lista = Lista->Siguiente;
    }
}

void cargarTareas(Nodo ** pendientes){
    int id = 1000;
    int continuar = 0;
    char * Buff;
    do{
        Tarea* nueva;
        nueva = (Tarea *) malloc(sizeof(Tarea));

        printf("Ingrese la descripcion de la tarea: ");
        Buff = (char *) malloc(100*sizeof(char));
        fgets(Buff, 100, stdin);
        Buff[strcspn(Buff, "\n")] = '\0';
        nueva->Descripcion = (char *) malloc((strlen(Buff)+1) * sizeof(char));
        strcpy(nueva->Descripcion, Buff);

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
    free(Buff);
}

void marcarRealizadas(Nodo ** pendientes, Nodo ** realizadas){
    int continuar = 0;
    int id;
    do{
        printf("Ingrese el ID de la tarea realizada: ");
        scanf("%d", &id);
        getchar();

        moverTarea(pendientes, realizadas, id);
        printf("Marcar otra tarea realizada?\n0. Si\n1. No\n");
        scanf("%d", &continuar);
        getchar();
    }while(!continuar);    
}

void moverTarea(Nodo **pendientes, Nodo **realizadas, int id){
    Nodo *actual = *pendientes;
    Nodo *anterior = NULL;

    while(actual != NULL && actual->T.TareaID != id){
        anterior = actual;
        actual = actual->Siguiente;
    }

    if(actual == NULL){
        printf("No se encontro la tarea con ID %d\n", id);
        return;
    }

    if(anterior == NULL){
        *pendientes = actual->Siguiente;
    } else {
        anterior->Siguiente = actual->Siguiente;
    }

    actual->Siguiente = *realizadas;
    *realizadas = actual;

    printf("Tarea %d movida a realizadas\n", id);
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