#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tdas/list.h"
#include "tdas/heap.h"
#include "tdas/queue.h"
#include "tdas/stack.h"


// Definición de la estructura para el estado del puzzle
typedef struct {
    int square[3][3]; // Matriz 3x3 que representa el tablero
    int x;    // Posición x del espacio vacío
    int y;    // Posición y del espacio vacío
    List* actions; //Secuencia de movimientos para llegar al estado
} State;

// Función para imprimir el estado del puzzle
void imprimirEstado(State *estado) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (estado->square[i][j] == 0) {
                printf("x ");
            } else {
                printf("%d ", estado->square[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Definición de la función CrearEstado.
// Esta función intenta asignar memoria para un nuevo estado y devuelve un puntero a él.
State* CrearEstado() {
    // Intenta asignar memoria para un estado.
    State* Estado = (State*)malloc(sizeof(State));

    // Verifica si la asignación de memoria fue exitosa.
    if (Estado == NULL) {
        // Si no se pudo asignar memoria, imprime un mensaje de error y termina el programa.
        printf("Error: No se pudo asignar memoria.\n");
        exit(1);
    }

    // Si la asignación fue exitosa, devuelve el puntero al nuevo estado.
    return Estado;
}


// Función LeerEntrada: Lee los valores ingresados por el usuario para el rompecabezas 8-puzzle.
State* LeerEntrada() {
    // Crea un nuevo estado para el rompecabezas.
    State* EstadoIngresar = CrearEstado();

    // Inicializa un arreglo para rastrear qué números han sido ingresados.
    bool numerosIngresados[9] = {false};

    // Solicita al usuario que ingrese los valores del rompecabezas.
    printf("Ingrese los valores del rompecabezas 8-puzzle (del 1 al 8, 0 para el espacio vacío):\n\n");

    // Declara variables para iterar y almacenar el valor ingresado.
    int i, j, valor;

    // Itera sobre cada casilla del rompecabezas.
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            // Repite la solicitud de ingreso hasta que se reciba un valor válido.
            while(true) {
                // Imprime el estado actual del rompecabezas para que el usuario vea qué casillas están llenas.
                for (int fila = 0; fila < 3; fila++) {
                    for (int columna = 0; columna < 3; columna++) {
                        // Marca la casilla actual como vacía para el ingreso del usuario.
                        if (fila == i && columna == j) {
                            printf("[_] ");
                        } else {
                            // Imprime el valor actual de la casilla.
                            printf("[%d] ", EstadoIngresar->square[fila][columna]);
                        }
                    }
                    printf("\n");
                }

                // Pide al usuario que ingrese el valor para la casilla vacía.
                printf("\nIngrese el valor para la casilla vacía (fila %d, columna %d): ", i + 1, j + 1);
                scanf("%d", &valor);

                // Verifica si el valor ingresado es válido y no ha sido ingresado previamente.
                if (valor >= 0 && valor <= 8 && !numerosIngresados[valor]) {
                    // Asigna el valor ingresado a la casilla correspondiente.
                    EstadoIngresar->square[i][j] = valor;
                    // Marca el número como ingresado.
                    numerosIngresados[valor] = true;

                    // Si el valor ingresado es 0, actualiza la posición del espacio vacío.
                    if (valor == 0) {
                        EstadoIngresar->x = i;
                        EstadoIngresar->y = j;
                    }
                    break; // Sale del bucle ya que se ingresó un valor válido.
                } else {
                    // Informa al usuario que el número es inválido o ya fue ingresado y solicita otro intento.
                    printf("Número inválido o ya ingresado. Por favor, intente de nuevo.\n");
                }
            }
        }
    }
    // Devuelve el puntero al estado con los valores ingresados.
    return EstadoIngresar;
}


// Función esFinal: Determina si el estado actual del rompecabezas 8-puzzle es el estado objetivo.
bool esFinal(State* estado) {
    // Define el estado objetivo del rompecabezas 8-puzzle con el espacio vacío en la esquina superior izquierda.
    int estadoObjetivo[3][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8}
    };

    // Itera a través de cada casilla del rompecabezas para comparar el estado actual con el estado objetivo.
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // Comprueba si la casilla actual del estado no coincide con la casilla correspondiente del estado objetivo.
            if (estado->square[i][j] != estadoObjetivo[i][j]) {
                // Si alguna casilla no coincide, el estado actual no es el estado objetivo.
                return false;
            }
        }
    }
    // Si todas las casillas coinciden, el estado actual es el estado objetivo y el rompecabezas está resuelto.
    return true;
}



// Función EsValido: Determina si una acción es válida en el estado actual del rompecabezas 8-puzzle.
bool EsValido(State* estado, int action) {
  // Las acciones posibles son: 1 = arriba, 2 = abajo, 3 = izquierda, 4 = derecha.
  // La función verifica si el movimiento del espacio vacío en la dirección dada es posible.
    switch (action) {
        case 1: // Arriba
            // Verifica si el espacio vacío puede moverse hacia arriba (no está en la primera fila).
            return (estado->y > 0);
        case 2: // Abajo
            // Verifica si el espacio vacío puede moverse hacia abajo (no está en la última fila).
            return (estado->y < 2);
        case 3: // Izquierda
            // Verifica si el espacio vacío puede moverse hacia la izquierda (no está en la primera columna).
            return (estado->x > 0);
        case 4: // Derecha
            // Verifica si el espacio vacío puede moverse hacia la derecha (no está en la última columna).
            return (estado->x < 2);
        default:
            // Si la acción no es ninguna de las anteriores, devuelve falso.
            return false;
    }
}




// Función copiarEstadoTotal: Crea una copia profunda de un estado del rompecabezas 8-puzzle.
State* copiarEstadoTotal(State* estadoOriginal) {
    // Verificar si el estado original es nulo para evitar errores de segmentación.
    if (estadoOriginal == NULL) {
        fprintf(stderr, "Error: El estado original proporcionado es nulo.\n");
        return NULL;
    }

    // Intentar crear una nueva instancia de State para la copia.
    State* nuevoEstado = (State*)malloc(sizeof(State));
    // Verificar si la asignación de memoria fue exitosa.
    if (nuevoEstado == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria para el nuevo estado.\n");
        return NULL;
    }

    // Copiar los valores de la matriz del rompecabezas del estado original al nuevo estado.
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            nuevoEstado->square[i][j] = estadoOriginal->square[i][j];
        }
    }
    // Copiar la posición del espacio vacío del estado original al nuevo estado.
    nuevoEstado->x = estadoOriginal->x;
    nuevoEstado->y = estadoOriginal->y;

    // Crear una nueva lista para almacenar las acciones que llevaron al estado actual.
    nuevoEstado->actions = list_create();
    // Verificar si la creación de la lista fue exitosa.
    if (nuevoEstado->actions == NULL) {
        fprintf(stderr, "Error: No se pudo crear la lista de acciones para el nuevo estado.\n");
        // Liberar la memoria asignada al nuevo estado si la lista no pudo ser creada.
        free(nuevoEstado);
        return NULL;
    }

    // Copiar la lista de acciones del estado original al nuevo estado.
    List * AuxiliarEstado = list_first(estadoOriginal->actions);
    while(AuxiliarEstado != NULL) {
        list_pushBack(nuevoEstado->actions, AuxiliarEstado);
        AuxiliarEstado = list_next(estadoOriginal->actions);
    }
    // Devolver el nuevo estado con la copia completa del estado original.
    return nuevoEstado;
}



// Función transicion: Realiza un movimiento en el rompecabezas 8-puzzle según la configuración dada.
State *transicion(State *Estado, int Direcc) {
    // Las direcciones posibles son: Arriba = 1; Abajo = 2; Izquierda = 3; Derecha = 4.

    // No es necesario buscar la casilla vacía ya que ya la tenemos:
    int x = Estado->x;   
    int y = Estado->y;

    // Se reserva memoria para el puntero Direcc_ptr que almacenará la acción realizada.
    int *Direcc_ptr = (int *)malloc(sizeof(int));
    if (Direcc_ptr == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria para Direcc.\n");
        return NULL;
    }
    *Direcc_ptr = Direcc;

    // Realiza la acción correspondiente a la configuración dada.
    switch (Direcc) {
        case 1: // OPCION ARRIBA
            // Verifica si el movimiento es válido antes de realizarlo.
            if(EsValido(Estado, Direcc)) {
                // Intercambia el valor de la casilla vacía con la casilla de arriba.
                int aux_arriba = Estado->square[x][y - 1];
                Estado->square[x][y - 1] = Estado->square[x][y];
                Estado->square[x][y] = aux_arriba;

                // Actualiza la posición de la casilla vacía.
                Estado->y = y - 1;

                // Añade la acción realizada a la lista de acciones del estado.
                list_pushBack(Estado->actions, Direcc_ptr);
                return Estado;
            }
            break;
        case 2: // OPCION ABAJO
            if(EsValido(Estado, Direcc)) {
                int aux_abajo = Estado->square[x][y + 1];
                Estado->square[x][y + 1] = Estado->square[x][y];
                Estado->square[x][y] = aux_abajo;

                Estado->y = y + 1;

                list_pushBack(Estado->actions, Direcc_ptr);
                return Estado;
            }
            break;
        case 3: // OPCION IZQUIERDA
            if(EsValido(Estado, Direcc)) {
                int aux_izquierda = Estado->square[x - 1][y];
                Estado->square[x - 1][y] = Estado->square[x][y];
                Estado->square[x][y] = aux_izquierda;

                Estado->x = x - 1;

                list_pushBack(Estado->actions, Direcc_ptr);
                return Estado;
            }
            break;
        case 4: // OPCION DERECHA
            if(EsValido(Estado, Direcc)) {
                int aux_derecha = Estado->square[x + 1][y];
                Estado->square[x + 1][y] = Estado->square[x][y];
                Estado->square[x][y] = aux_derecha;

                Estado->x = x + 1;

                list_pushBack(Estado->actions, Direcc_ptr);
                return Estado;
            }
            break;
        default:
            // Si la configuración no es válida, libera la memoria reservada y devuelve NULL.
            free(Direcc_ptr);
            return NULL;
    }
    // Si la acción no es válida, libera la memoria reservada y devuelve NULL.
    free(Direcc_ptr);
    return NULL;
}



// Función ObtenerNodosAdyacentes: Genera una lista de todos los estados adyacentes válidos a partir del estado actual.
List* ObtenerNodosAdyacentes(State *EstadoActual) {
    // Crea una nueva lista para almacenar los nodos adyacentes.
    List* NodosAdyacentes = list_create();
    // Verifica si la lista se creó correctamente.
    if (!NodosAdyacentes) {
        // Si no se pudo crear la lista, devuelve NULL.
        fprintf(stderr, "Error: No se pudo crear la lista de nodos adyacentes.\n");
        return NULL;
    }

    // Itera sobre los posibles movimientos: Arriba (1), Abajo (2), Izquierda (3), Derecha (4).
    for(int movimiento = 1; movimiento <= 4; ++movimiento) {
        // Crea una copia del estado actual para explorar el movimiento.
        State* EstadoCopiado = copiarEstadoTotal(EstadoActual);
        // Verifica si la copia se realizó correctamente.
        if (!EstadoCopiado) {
            // Si no se pudo duplicar el estado, limpia la lista y devuelve NULL.
            fprintf(stderr, "Error: No se pudo duplicar el estado para el movimiento %d.\n", movimiento);
            list_clean(NodosAdyacentes);
            return NULL;
        }

        // Verifica si el movimiento es válido en la copia del estado.
        if (EsValido(EstadoCopiado, movimiento)) {
            // Realiza la transición en la copia del estado.
            State *nuevo_estado = transicion(EstadoCopiado, movimiento);
            // Verifica si la transición fue exitosa.
            if (!nuevo_estado) {
                // Si la transición no es válida, libera la memoria de la copia y continúa con el siguiente movimiento.
                free(EstadoCopiado);
                continue;
            }
            // Añade el nuevo estado a la lista de nodos adyacentes.
            list_pushBack(NodosAdyacentes, nuevo_estado);
        } else {
            // Si el movimiento no es válido, libera la memoria de la copia.
            free(EstadoCopiado);
        }
    }

    // Devuelve la lista de nodos adyacentes.
    return NodosAdyacentes;
}



State* DFS(State* initial, int* cont) {
    Stack *stack = stack_create(NULL); // Crear la pila
    stack_push(stack, initial); // Insertar el estado inicial en la pila

    while (stack_top(stack) != NULL) {
        // Sacar el estado actual de la pila
        State *current = stack_top(stack);
        stack_pop(stack);

        // Verificar si se ha alcanzado el límite de movimientos
        if (list_size(current->actions) >= 13) {
            // Si se excede el límite de movimientos, pasar a la siguiente rama
            continue;
        }

        // Verificar si el estado actual es el estado final
        if (esFinal(current)) {
            // Si es el estado final, liberar la pila y retornar el estado
            free(stack);
            return current;
        }

        // Obtener los vecinos del estado actual
        List *neighbors = ObtenerNodosAdyacentes(current);
        State *neighbor = list_first(neighbors);

        // Insertar los vecinos en la pila
        while (neighbor != NULL) {
            stack_push(stack, neighbor);
            neighbor = list_next(neighbors);
        }

        // Liberar la memoria de la lista de vecinos
        list_clean(neighbors);
        free(neighbors);

        // Incrementar el contador de iteraciones
        (*cont)++;
    }

    // Liberar la memoria de la pila si no se encontró una solución
    free(stack);
    return NULL;
}


// Función BFS: Realiza una búsqueda en anchura (Breadth-First Search) para encontrar la solución al rompecabezas 8-puzzle.
State* BFS(State* initial, int* cont) {
    // Crea una cola para manejar los estados a explorar.
    Queue* cola = queue_create(NULL);
    // Verifica si la cola se creó correctamente.
    if (cola == NULL) {
        fprintf(stderr, "Error: No se pudo crear la cola.\n");
        return NULL;
    }

    // Inserta el estado inicial en la cola.
    queue_insert(cola, initial);
    // Continúa mientras haya estados en la cola.
    while (queue_front(cola) != NULL) {
        // Obtiene el estado al frente de la cola.
        State* aux_queue = queue_front(cola);
        // Elimina el estado al frente de la cola.
        queue_remove(cola);
        // Verifica si el estado actual es el estado objetivo.
        if (esFinal(aux_queue)) {
            // Si es el estado final, limpia la cola, libera la memoria y devuelve el estado solución.
            queue_clean(cola);
            free(cola);
            return aux_queue;
        }
        // Obtiene todos los nodos adyacentes válidos del estado actual.
        List* list_vecinos = ObtenerNodosAdyacentes(aux_queue);
        // Itera sobre cada nodo adyacente.
        for (State* list_index = list_first(list_vecinos); list_index != NULL; list_index = list_next(list_vecinos)) {
            // Inserta el nodo adyacente en la cola para explorarlo luego.
            queue_insert(cola, list_index);
        }
        // Destruye la lista de nodos adyacentes para liberar memoria.
        list_destroy(list_vecinos);
        // Incrementa el contador de estados explorados.
        (*cont)++;
    }
    // Si se vacía la cola sin encontrar el estado objetivo, limpia la cola, libera la memoria y devuelve NULL.
    queue_clean(cola);
    free(cola);
    return NULL;
}


//Se que es medio redundante, pero no quiero tocar nada del codigo ya, asi que es una funcion para el estado incial...
void imprimirEstadoInicial(State *ini) {
    printf("\nEstado Inicial :\n");
    imprimirEstado(ini);
}

// Función imprimirSecuenciaAcciones: Imprime la secuencia de acciones desde el estado inicial al estado final.
void imprimirSecuenciaAcciones(State *Inicial, State *Final) {
    // Imprime el estado inicial del rompecabezas.
    imprimirEstadoInicial(Inicial);

    // Obtiene la lista de acciones del estado final.
    List *list = Final->actions;
    // Crea una copia del estado inicial para aplicar las transiciones.
    State *trans_state = copiarEstadoTotal(Inicial);
    // Inicializa el contador de pasos.
    int Pasos = 1; // Comenzamos desde el paso 1

    // Obtiene el primer elemento de la lista de acciones.
    int *aux = list_first(list); // Puntero utilizado para almacenar el siguiente elemento de la lista de acciones.

    // Itera mientras haya acciones en la lista.
    while ((aux != NULL)) {
        // Aplica la acción al estado transitorio y obtiene el nuevo estado.
        trans_state = transicion(trans_state, *aux);
        // Imprime el número del paso y el estado actual del rompecabezas.
        printf("Estado n° %d del puzzle:\n", Pasos++);
        imprimirEstado(trans_state); // Imprimir el estado actual
        // Obtiene la siguiente acción de la lista.
        aux = list_next(list);
    }
}


// Función para limpiar la pantalla
void limpiarPantalla() { system("clear"); }

void presioneTeclaParaContinuar() {
  puts("Presione una tecla para continuar...");
  getchar(); // Consume el '\n' del buffer de entrada
  getchar(); // Espera a que el usuario presione una tecla
}


// Función principal del programa para resolver el rompecabezas 8-puzzle.

int main() {
    // Solicita al usuario que ingrese el estado inicial del rompecabezas, POR FAVOR seguir el readme en este caso
    
    State* EstadoEntrada = LeerEntrada();

    // Crea la lista de acciones para el estado inicial.
    EstadoEntrada->actions = list_create();

    // Limpia la pantalla para una mejor visualización.
    limpiarPantalla();

    // Imprime el estado inicial del rompecabezas.
    printf("\nEstado inicial del puzzle:\n");
    imprimirEstado(EstadoEntrada);

    // Variables para controlar la opción del menú y el contador de iteraciones.
    int opcion;
    int cont = 0;
    State* resultado = NULL;

    // Bucle para mostrar el menú de opciones y procesar la entrada del usuario.
    do {
        // Muestra el menú de opciones de búsqueda.
        puts("========================================");
        puts("     Escoge método de búsqueda");
        puts("========================================");
        puts("1) Búsqueda en Profundidad");
        puts("2) Buscar en Anchura");
        puts("3) Salir");
        printf("Ingrese su opción: ");
        scanf("%d", &opcion);

        // Procesa la opción seleccionada por el usuario.
        switch (opcion) {
            case 1:
                // Realiza la búsqueda en profundidad (DFS).
                resultado = DFS(EstadoEntrada, &cont);
                printf("Número de iteraciones de búsqueda: %d\n", cont);
                imprimirSecuenciaAcciones(EstadoEntrada, resultado);
                cont = 0;
                break;
            case 2:
                // Realiza la búsqueda en anchura (BFS).
                resultado = BFS(EstadoEntrada, &cont);
                printf("Número de iteraciones de búsqueda: %d\n", cont);
                imprimirSecuenciaAcciones(EstadoEntrada, resultado);
                cont = 0;
                break;
            case 3:
                // Opción para salir del programa.
                printf("Saliendo del programa...\n");
                break;
            default:
                // Manejo de opciones no válidas.
                printf("Opción no válida. Intente de nuevo.\n");
        }

        // Limpia la lista de acciones y la pantalla antes de volver a mostrar el menú.
        list_clean(EstadoEntrada->actions);
        presioneTeclaParaContinuar();
        limpiarPantalla();

    } while (opcion != 3); // Repite el menú hasta que el usuario elija salir.

    return 0; // Finaliza el programa.
}
