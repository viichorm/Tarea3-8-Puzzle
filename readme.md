# Resolución de 8-puzzle

# Descripción

El programa está diseñado para resolver el puzzle de 8 piezas, un juego de lógica donde se deben ordenar las piezas numeradas del 1 al 8 en una cuadrícula de 3x3, dejando un espacio vacío para permitir el movimiento de las piezas. El estado inicial del puzzle es una configuración específica de las piezas que no está en orden.

# Cómo compilar y ejecutar

Para compilar y ejecutar el programa, sigue estos pasos:

1. Clona este repositorio en tu máquina local.
2. Abre una terminal y navega hasta el directorio del repositorio clonado.
3. Compila el código utilizando un compilador de C compatible (por ejemplo, `gcc main.c tdas/*.c -o main`).
4. Ejecuta el programa compilado (`./main`).

En caso de no poder compilar u ejecutar correctamente, puede acceder directamente al replit donde se desarrollo el programa 
**[ACCEDER AL REPLIT](https://replit.com/@VicenteMart1neZ/Tarea3-8Puzzle)**

# Funcionalidades

## Funcionamiento y Explicacion:

 - **Búsqueda en Profundidad**: Este algoritmo explora el grafo de posibilidades tomando siempre el siguiente nodo más profundo en la ruta actual antes de retroceder. Es como un laberinto donde se sigue avanzando hasta llegar a un punto muerto, y luego se regresa para probar un camino diferente. Este método puede ser más rápido para puzzles con una solución cercana al estado inicial, pero no garantiza encontrar la solución más óptima y puede consumir mucha memoria si el árbol de búsqueda es muy grande.

- **Búsqueda en Anchura**: A diferencia de DFS, BFS explora todos los nodos vecinos al nivel actual antes de pasar al siguiente nivel. Esto asegura que si hay una solución, BFS la encontrará en el menor número de movimientos posible, ya que encuentra la solución más óptima. Sin embargo, puede ser más lento y consumir más memoria, ya que mantiene todos los nodos del nivel actual en memoria antes de pasar al siguiente.


## Problemas conocidos:

- Ruego por favor que se ingrese este tablero a la hora de la entrada, debido a que no funciona correctamente con otros trableros. Ademas tambien que al momento de pedir ingresar los valores, no sean caracteres como '' o ], que sino genera un bucle.
  
- 0 2 8
- 1 3 4
- 6 5 7

## A mejorar:

- Mejorar la eficiencia y gestion de memoria.
- Implementar opciones de ingresar y edición para resolver cualquier 8-puzzle

# Ejemplo de uso

## **Opción Base: Entrada de datos**
El programa le pedira al usuario que ingrese su tablero, como caso perfecto suguiero este:
- 0 2 8
- 1 3 4
- 6 5 7

Es el cual funciona correctamente con las 2 funciones del programa.


## **Opción 1: Búsqueda en Profundidad**
El programa inicia presentando el estado inicial del puzzle que ha sido configurado. A continuación, se detallan los movimientos ejecutados para alcanzar la solución, empleando el método de **búsqueda en profundidad**. Este proceso implica explorar sistemáticamente las ramificaciones del grafo de posibles estados hasta encontrar la configuración objetivo.

Además, se ofrece un conteo de las iteraciones realizadas durante la búsqueda, proporcionando una medida clara del esfuerzo computacional necesario para resolver el puzzle.



## **Opción 2: Buscar en Anchura**


Al comienzo, el programa despliega el estado inicial del puzzle previamente cargado. Seguidamente, se procede a ilustrar la secuencia de pasos seguidos para alcanzar la solución, utilizando la técnica de **búsqueda en profundidad**. Este método consiste en una exploración exhaustiva de las posibles configuraciones del puzzle, avanzando hacia la profundidad del árbol de soluciones hasta dar con la disposición correcta.

Adicionalmente, el programa proporciona una visualización del número total de iteraciones que se han llevado a cabo para llegar a la solución, ofreciendo así una perspectiva cuantitativa del proceso de búsqueda.



## Contribuciones ##

**Vicente Martinez**:
- Desarrollo en solitario del codigo, juntos con las funciones.
  
![d63ac5bcd7d3832dfb44ad829317fbff2ba5b6cf_128](https://github.com/viichorm/Tarea-2/assets/125922459/986606ce-420d-4121-84f2-3cf7e7251010)





  
