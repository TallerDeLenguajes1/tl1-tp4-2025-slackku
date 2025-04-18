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
void marcarTareaTerminada(Nodo **listaPendientes, Nodo **listaTerminadas, int *buffEntrada);
void mostrarLista(Nodo **lista);
Nodo *eliminarNodo(Nodo **lista);
void mostrarEspecifo(Nodo **listaTerminadas, Nodo **listaPendientes); // Por id o palabra clave
void mostrarPorId(Nodo **lista, int id);
void mostrarPorPalabraClave(Nodo **lista, char *palabraClave);

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
    printf("-- Ingreso de Tareas Terminadas --\n");

    marcarTareaTerminada(&tareasPendientes, &tareasTerminadas, &buffCargaListas);

    printf("#####     Listas Finales     ####\n");
    printf("---- | Lista de Pendientes | ----\n");
    mostrarLista(&tareasPendientes);
    printf("---- | Lista de Terminadas | ----\n");
    mostrarLista(&tareasTerminadas);

    mostrarEspecifo(&tareasTerminadas, &tareasPendientes);

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

void marcarTareaTerminada(Nodo **listaPendientes, Nodo **listaTerminadas, int *buffEntrada)
{
    Nodo *head = *listaPendientes;
    Nodo *nodoAnterior = NULL;

    while (head)
    {
        printf("Tarea ID: %d\n", head->T.TareaID);
        printf("Descripcion: %s\n", head->T.Descripcion);
        printf("Duracion: %d\n", head->T.Duracion);
        printf("-.-.-.-.-.-.-.-.-.-.-\n");
        printf("Si la tarea ha sido finalizada ingrese 1. Caso contrario ingresar 0: ");
        scanf("%d", buffEntrada);

        if (*buffEntrada == 1)
        {
            Nodo *tareaTerminada = head;
            head = head->Siguiente;

            if (!nodoAnterior)
            {
                *listaPendientes = head;
            }
            else
            {
                nodoAnterior->Siguiente = head;
            }
            tareaTerminada->Siguiente = NULL;
            insertarNodo(listaTerminadas, tareaTerminada);
        }
        else
        {
            nodoAnterior = head;
            head = head->Siguiente;
        }
    }
}

void mostrarLista(Nodo **lista)
{
    Nodo *aux = *lista;
    while (aux)
    {
        printf("Tarea ID: %d\n", aux->T.TareaID);
        printf("Descripcion: %s\n", aux->T.Descripcion);
        printf("Duracion: %d\n", aux->T.Duracion);
        printf("-------------------------\n");
        aux = aux->Siguiente;
    }
}

void mostrarEspecifo(Nodo **listaTerminadas, Nodo **listaPendientes)
{
    int aux, idDato;
    char *buff = (char *)malloc(sizeof(char) * 50);

    printf("---- Ingresar segun lo deseado ----\n");
    printf("Buscar por id = [1] | Buscar por palabra clave = [2]\n");
    scanf("%d", &aux);
    fflush(stdin);
    switch (aux)
    {
    case 1:
        printf("Ingrese el id deseado: ");
        scanf("%d", &idDato);
        fflush(stdin);

        printf("Buscando en lista Pendientes: \n");
        mostrarPorId(listaPendientes, idDato);
        printf("Buscando en lista Terminadas: \n");
        mostrarPorId(listaTerminadas, idDato);

        break;
    case 2:
        printf("Ingrese la palabra clave: ");
        gets(buff);
        printf("Buscando en lista Pendientes: \n");
        mostrarPorPalabraClave(listaPendientes, buff);
        printf("Buscando en lista Terminadas: \n");
        mostrarPorPalabraClave(listaTerminadas, buff);

        break;
    }
}

void mostrarPorId(Nodo **lista, int id)
{
    Nodo *listaAux = *lista;

    while (listaAux != NULL && id != listaAux->T.TareaID)
    {
        listaAux = listaAux->Siguiente;
    }

    if (listaAux != NULL)
    {
        printf("###############\n");
        printf("# Tarea Encontrada - Datos encontrados\n");
        printf("# La tarea de id %d, es:\n", id);
        printf("# Descripcion: %s\n", listaAux->T.Descripcion);
        printf("# Duracion: %d\n", listaAux->T.Duracion);
        printf("###############\n");
    }
    else
    {
        printf("No ha sido encontrada ninguna tarea de id: %d en la lista.\n", id);
    }
}

void mostrarPorPalabraClave(Nodo **lista, char *palabraClave)
{
    Nodo *listaAux = *lista;
    char *coincidencia;
    while (listaAux)
    {
        coincidencia = strstr(listaAux->T.Descripcion, palabraClave);
        if (coincidencia != NULL && strlen(palabraClave) != 0)
        {
            printf("Tarea Encontrada - Datos encontrados\n");
            printf("La tarea de id %d, es:\n", listaAux->T.TareaID);
            printf("Descripcion: %s\n", listaAux->T.Descripcion);
            printf("Duracion: %d\n", listaAux->T.Duracion);
        }
        listaAux = listaAux->Siguiente;
    }
    if (coincidencia == NULL || strlen(palabraClave) == 0)
    {
        printf("No ha sido encontrada ninguna con la palabra clave %s en la lista.\n", palabraClave);
    }
}