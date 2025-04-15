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