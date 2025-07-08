[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/mi1WNrHU)
# Proyecto de C++ - DICE'S PALACE

## Equipo

- **Nombre del equipo:** Undefined

### Integrantes del equipo

1. **Nombre completo:** Susan Abigail Castillo Oliva
   **Carnet:** 00221125

2. **Nombre completo:** Daniel Alexander Espinal Echegoyen
   **Carnet:** 00100725

3. **Nombre completo:** Francisco Javier Guadrón Vásquez
   **Carnet:** 00077225

4. **Nombre completo:** Eduardo Josué Guerra Sagastizado
   **Carnet:** 00043625


## ➢ Descripción del Proyecto

Dice’s palace es un juego de laberinto, donde el jugador se verá atrapado en un castillo y su objetivo será buscar el camino para poder salir, para ello entrará a cuatro salas diferentes, la cuales serán laberintos y para pasar tendrá que encontrar el camino correcto que lo llevará al jefe y derrotarlo.

## ➢ Temática y ambientación
La historia se centra en la travesía de un ladrón moderno que roba un casino, sin embargo, al lograr su objetivo es teletransportado a un castillo, remontándose a la época medieval, sin pistas de donde esta y como llego ahí, en lo profundo del castillo él se dispone a encontrar la salida, cueste lo que cueste donde se encontrará con un sin fin de decisiones y posibles caminos que deberá tomar para poder salir con vida del castillo y regresar a su mundo actual.

## ➢ Mecánica principal
Juego de aventura y puzles en laberintos con ambientación medieval.

- **Aventura de Laberintos:** Núcleo del movimiento y exploración, ya que el jugador está atrapado en un castillo y debe buscar el camino para poder salir a través de cuatro salas diferentes, la cuales serán laberintos.
- **Puzles/Desafíos Variados:** La forma de derrotar al jefe en cada nivel no es el combate tradicional, sino la resolución de puzles:
  - Acertijos (Nivel 1)
  - Busca la diferencia (Nivel 2)
  - Ordenar números (Nivel 3)
  - Mini-juego de habilidad/reacción (Nivel 4)

## ➢ Idea general de la jugabilidad
El jugador comienza con estadísticas predefinidas (100 HP). La vida del jefe (100 HP) se mostrará durante la lucha. La vida del jefe bajará a medida complete correctamente el mini juego.

1) El jugador estará atrapado en un castillo y su objetivo principal es encontrar la salida, lo cual implica navegar por cuatro salas diferentes, cada una siendo un laberinto. El jugador podrá ver su posición y moverse entre los caminos, así como la posición del jefe al que debe llegar.
2)  Dificultad en cada nivel:
     - Al llegar al jefe el jugador podrá comenzar combatir con el jefe (Jugando los minijuegos de cada nivel).
     - Según el nivel, la dificultad para pasarlo y asi derrotar al jefe irá aumentando (Según la lógica de cada mini juego)

**¿Cómo derrotar al jefe?**
1.	**NIVEL 1: Acertijos**
      Para derrotar el jefe el jugador tendrá que resolver 4 acertijos que el jefe le irá dando, entre más responda correctamente la vida del jefe se irá bajando.
2.	**NIVEL 2: Busca la diferencia**
      Al jugador se le mostrarán dos strings casi iguales y tendrá que encontrar el carácter distinto para lograr derrotarlo.
3.	**NIVEL 3: Ordenar números**
      El jefe le presentará una serie de 4 números que estarán desordenados, el jugador tendrá que ordenar estos números en 15 segundos.
4.	**NIVEL 4: Mini juego de habilidad**
      El jefe le dirá al jugador que apriete una serie de teclas rápidamente.
      El jugador tendrá que ser hábil y teclear correctamente las teclas que se le presenten para poder derrotar al jefe.

## ➢ Aplicación de los temas vistos (uno por uno con ejemplos)

### **1) Variables y tipos de datos:**
  Para almacenar cualquier tipo de información en el programa, como la posición del jugador, la vida del jefe, la dificultad, las opciones de menú, etc. 
  - Un **ejemplo** más puntual es dentro de la función de playSpotDifference(en 2_spotDifference), aqui se crea una variable de tipo string, llamada “respuesta”, luego es utilizada para diferentes procesos.
  - **char option:** Variable de tipo carácter para almacenar la tecla que el usuario presiona en el menú principal.

### **2) Estructuras condicionales (if, else, switch)**
  Permiten que el programa tome decisiones y ejecute diferentes bloques de código basándose en si una condición es verdadera o falsa.
  - **Switch:**
      ````
      switch (option)
      {
      case 13: // Enter
      quitGame = Level1();
      break;
      case 104: // Key 'h'
      quitGame = showStory();
      break;
      case 27: // ESC
      quitGame = true;
      break;
      }
  - **If, else:**
      ````
      if (!file)
      {
      cout << "Error al abrir el archivo: \n" << filePath;
      return;
      }
      
      if (score >= scoreToWin) {
      // ...
      return true; // Ends game
      }

### **3) Ciclos (for, while, do while)**
  Permiten ejecutar un bloque de código repetidamente. usados para iterar listas de datos, dibujar elementos repetitivos en pantalla, mantener un bucle de juego continuo, o esperar por una condición.
  - **While:** El bucle principal del mini-juego "Key Smash" que se ejecuta mientras el jefe tenga vida
      ````
      while (bossHP > 0)
      {
      // ...
      }
  - **For:** `En loadMazeFromFile()`, bucle para escanear cada carácter en una línea del laberinto y encontrar la posición del jugador o el jefe.
      ````
      for (int col = 0; col < maze.cols; ++col)
      {
      // ...
      }

### **4) Funciones**
  Se utilizan para organizar y reutilizar fragmentos de código que se repiten o que realizan tareas específicas dentro del juego.
  - `void showMenu()` Muestra la interfaz del menú principal, incluyendo el título ASCII art y las opciones.
  - `bool playKeySmash(int posX, int posY)` Contiene toda la lógica del mini-juego "Key Smash".

### **5) Estructuras de datos** 
  Se utilizan para organizar y almacenar datos de manera eficiente para que puedan ser accedidos y manipulados fácilmente. Agrupando variables de diferentes tipos bajo un solo nombre.   
  - Encontrada en `maze.h`, agrupa todos los datos relacionados con un laberinto.  
    ``````
    // Structure that stores the maze content
    struct Maze
    {
    // Maze matrix
    char grid[MAX_ROWS][MAX_COLS];
    // Actual size of the loaded maze (from txt file)
    int rows, cols;
    // Player position (P)
    int playerX, playerY;
    // Boss position (B)
    int bossX, bossY;
    };
    
### **6) Manejo de archivos**
  Utilizado para cargar archivos .txt, ejem: `maze.cpp` Utilizado para cargar el diseño de los laberintos.
  - `#include <fstream>`: Incluye la biblioteca necesaria para operaciones de archivos (entrada/salida de flujo de archivos).
  - `ifstream file(filePath)`: Crea un objeto ifstream para abrir un archivo de texto en modo de lectura.
  - `getline(file, line)`: Lee una línea completa del archivo file y la almacena en la variable line.
  - `file.close()`: Cierra el archivo después de que se ha terminado de leer.  

### **7) Manejo de errores**
  Utilizado para asegurar que el juego no se comporte de forma inesperada cuando el jugador ingrese datos incorrectos o se produzca un fallo al leer archivos o realizar acciones aleatorias.
  -  Si una letra del mini-juego llega al final de la pantalla sin ser presionada, se considera un fallo del jugador, se reproduce un sonido de error `(playError())`, y la función `playKeySmash()` retorna false, indicando que la ronda no fue superada.
     ````
     if (keys[i].y > startY + HEIGHT)
     {
     playError();
     Sleep(2000);
     moveCursor(startX, startY + HEIGHT + 5);
     system("pause");
     delete[] keys;
     return false; // Ends game (indicando fallo)
     }

### **8) Interfaz por consola** 
  Se utiliza para mostrar texto, arte ASCII, manejar la posición del cursor, cambiar colores, y capturar la entrada del teclado del usuario, etc. Todo lo que interactua con el usuario.

## ➢ Consideraciones técnicas del desarrollo
  1) Para que Dice's Palace pueda correr (Compilar y crear ejecutable) sin ninguna dificultad es necesario seguir los siguientes pasos: 
     - https://www.notion.so/Compilaci-n-y-ejecutable-20dca0bc849e8098b398de0ed6dac96c?source=copy_link
  2) **Compilador:** MinGW.org GCC/G++ 6.3.0
  3) **Estándar del Lenguaje C++:** C++17
  4) **Sistema operativo para su correcta ejecución:** Windows 10/11 (Esto se debe a que el juego ocupa librerias nativas de windows `conio.h`, `windows.h`, `winmn`)
  5) **Herramientas de Desarrollo Específicas:** CMake _(Para el proceso de compilación)_, IDE recomendado (Visual Studio Code con extensiones C/C++, o Visual Studio completo).

## ➢ Mockups y flujogramas
   En el siguiente enlace se podrá visualizar los mockups y diagramas de flujo.
   - https://ucaedusv-my.sharepoint.com/:f:/g/personal/00221125_uca_edu_sv/Epx8NrvMaCRCr1AXvrdfIv0BUfpjvjyUgmqT_WGEr2xWeQ?e=dmKgkx
