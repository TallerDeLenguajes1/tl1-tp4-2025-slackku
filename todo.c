#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tarea
{
    int TareaID;       // Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion;      // entre 10 – 100
} typedef Tarea;

struct Nodo
{
    Tarea T;
    struct Nodo *Siguiente;
} typedef Nodo;

Nodo *crearListaVacia();
Nodo *crearNodo(Tarea datoTarea);
void *insertarNodo(Nodo **lista, Nodo *nodo);
Tarea crearTarea(int iteracion);
void moverATerminadas(Nodo **listaPendientes, Nodo **listaTerminadas);
void mostrarLista(Nodo **lista);
Nodo *eliminarNodo(Nodo **lista);

int main()
{
    int iteracion = 1000;
    int buffCargaListas = 1;
    Nodo *tareasPendientes = crearListaVacia();
    Nodo *tareasTerminadas = crearListaVacia();
    printf("-- Carga de Tareas Pendientes --\n");
    while (buffCargaListas == 1)
    {
        Tarea nuevaTarea = crearTarea(iteracion);
        Nodo *nuevoNodo = crearNodo(nuevaTarea);
        insertarNodo(&tareasPendientes, nuevoNodo);

        iteracion++;
        printf("Ingrese 0 para finalizar la carga de tareas. Caso contrario ingresar 1: ");
        scanf("%d", &buffCargaListas);
        fflush(stdin);
    }
    printf("-- Ingreso de Tareas Terminada --\n");
    Nodo *auxPendientes = tareasPendientes;
    while (auxPendientes)
    {
        printf("Tarea ID: %d\n", auxPendientes->T.TareaID);
        printf("Descripcion: %s\n", auxPendientes->T.Descripcion);
        printf("Duracion: %d\n", auxPendientes->T.Duracion);
        printf("-.-.-.-.-.-.-.-.-.-.-\n");
        printf("Si la tarea ha sido finalizada ingrese 1. Caso contrario ingresar 0: ");
        scanf("%d", &buffCargaListas);
        if (buffCargaListas == 1)
        {
            moverATerminadas(&tareasPendientes, &tareasTerminadas);
            auxPendientes = tareasPendientes;
            buffCargaListas = 0;
        }
        else
        {
            auxPendientes = auxPendientes->Siguiente;
        }
    }
    printf("-- Listas Finales --\n");
    printf("Lista de Pendientes:\n");
    mostrarLista(&tareasPendientes);
    printf("Lista de Terminadas:\n");
    mostrarLista(&tareasTerminadas);
    return 0;
}

Nodo *crearListaVacia()
{
    return NULL;
}

void *insertarNodo(Nodo **lista, Nodo *nodo)
{
    nodo->Siguiente = *lista;
    *lista = nodo;
}

Tarea crearTarea(int iteracion)
{
    int duracion;
    char *buff = (char *)malloc(sizeof(char) * 50);
    Tarea nueva;
    nueva.TareaID = iteracion;
    printf("Ingrese la descripcion de la Tarea: ");
    gets(buff);
    nueva.Descripcion = (char *)malloc((sizeof(char) * strlen(buff)) + 1);
    strcpy(nueva.Descripcion, buff);
    fflush(stdin);
    printf("Ingrese la duracion de la Tarea[10-100]: ");
    scanf("%d", &duracion);
    if (duracion >= 10 && duracion <= 100)
    {
        nueva.Duracion = duracion;
    }
    else
    {
        printf("Datos de duracion ingresado invalido, usando el valor por defecto = 50\n");
        nueva.Duracion = 50;
    }
    fflush(stdin);
    free(buff);
    return nueva;
}

Nodo *crearNodo(Tarea datoTarea)
{
    Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));
    nodo->T = datoTarea;
    nodo->Siguiente = NULL;
    return nodo;
}

void moverATerminadas(Nodo **listaPendientes, Nodo **listaTerminadas)
{
    Nodo *pendienteAux = *listaPendientes;
    *listaPendientes = pendienteAux->Siguiente;
    pendienteAux->Siguiente = *listaTerminadas;
    *listaTerminadas = pendienteAux;
}

void mostrarLista(Nodo **lista)
{
    Nodo *aux = *lista;
    while (aux)
    {
        printf("Tarea ID: %d\n", aux->T.TareaID);
        printf("Descripcion: %s\n", aux->T.Descripcion);
        printf("Duracion: %d\n", aux->T.Duracion);
        printf("--------------------------------------\n");
        aux = aux->Siguiente;
    }
}