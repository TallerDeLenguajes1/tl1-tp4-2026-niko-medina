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
void mostrarUnaTarea(Tarea, char*);
void cargarTareas(Nodo ** pendientes);
void marcarRealizadas(Nodo ** pendientes, Nodo ** realizadas);
void moverTarea(Nodo **pendientes, Nodo **realizadas, int id);
void menuBuscar(Nodo *pendientes, Nodo * realizadas);
int buscarPorID(Nodo *tareas, int id, char * estado);
int buscarPorPalabra(Nodo *lista, char *clave, char *estado);
void liberarLista(Nodo * lista);

int main(){
    Nodo* pendientes;
    pendientes = crearListaVacia();
    cargarTareas(&pendientes);

    Nodo * realizadas;
    realizadas = crearListaVacia();
    marcarRealizadas(&pendientes, &realizadas);

    int opcion;
    do{
        printf("\n--- MENU ---\n");
        printf("1. Marcar tareas realizadas\n");
        printf("2. Ver pendientes\n");
        printf("3. Ver realizadas\n");
        printf("4. Buscar tareas\n");
        printf("0. Salir\n");
        scanf("%d", &opcion);

        switch(opcion){
            case 1:
                marcarRealizadas(&pendientes, &realizadas);
                break;
            case 2:
                printf("\nPendientes:\n");
                mostrarTareas(pendientes);
                break;
            case 3:
                printf("\nRealizadas:\n");
                mostrarTareas(realizadas);
                break;
            case 4:
                printf("\nBuscar por ID:\n");
                menuBuscar(pendientes, realizadas);
                break; 
        }

    }while(opcion != 0);

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

void mostrarUnaTarea(Tarea tarea, char * estado){
    printf("Tarea numero: %d\n", tarea.TareaID);
    printf("Descripcion: ");
    puts(tarea.Descripcion);
    printf("Duracion: %d horas\n", tarea.Duracion);
    printf("Estado: %s\n", estado);
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

void menuBuscar(Nodo *pendientes, Nodo * realizadas){
    int opcion;
    int encontradoPendientes;
    int encontradoRealizadas;
    do{
        printf("\n--- CONSULTAS ---\n");
        printf("1. Buscar por ID\n");
        printf("2. Buscar por palabra clave\n");
        printf("0. Volver\n");
        scanf("%d", &opcion);
        getchar();

        if(opcion == 1){
            int id;
            printf("Ingrese ID: ");
            scanf("%d", &id);

            encontradoPendientes = buscarPorID(pendientes, id, "Pendiente");
            encontradoRealizadas = buscarPorID(realizadas, id, "Realizada");
            if(!encontradoPendientes & !encontradoRealizadas){
                printf("No se encontro tarea con ID %d\n", id);    
            }
        }
        else if(opcion == 2){
            char clave[50];
            printf("Ingrese palabra clave: ");
            fgets(clave, 50, stdin);
            clave[strcspn(clave, "\n")] = 0;

            encontradoPendientes = buscarPorPalabra(pendientes, clave, "Pendiente");
            encontradoRealizadas = buscarPorPalabra(realizadas, clave, "Realizada");
            if(!encontradoPendientes & !encontradoRealizadas){
                printf("No se encontraron tareas con la palabra clave '%s'\n", clave);    
            }
            
        }

    }while(opcion != 0);
}

// busca coincidencia exacta
int buscarPorID(Nodo *tareas, int id, char * estado){
    Nodo *aux;
    int encontrado = 0;

    aux = tareas;
    while(aux != NULL & encontrado == 0){
        if(aux->T.TareaID == id){
            mostrarUnaTarea(aux->T, estado);
            encontrado = 1;
        }
        aux = aux->Siguiente;
    }

    return encontrado;
}

// busca todas las coincidencias parciales
int buscarPorPalabra(Nodo *lista, char *clave, char *estado){
    Nodo *aux;
    int encontrado = 0;

    aux = lista;
    while(aux != NULL){
        if(strstr(aux->T.Descripcion, clave) != NULL){
            mostrarUnaTarea(aux->T, estado);
            encontrado = 1;
        }
        aux = aux->Siguiente;
    }

    return encontrado;
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