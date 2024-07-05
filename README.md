# Proyecto_Sudoku

# Descripción del Proyecto

El presente proyecto se centra en el desarrollo de un juego de Sudoku, implementado utilizando el lenguaje de programación C. A través de este proyecto, se busca recrear la experiencia juego, y también la puesta en práctica de conceptos fundamentales de programación y estructuras de datos. El desarrollo del juego en lenguaje C ofrece una oportunidad para profundizar en el manejo de arrays, funciones, y algoritmos eficientes para la generación y validación de tableros de Sudoku. Además, se considerarán aspectos de la interfaz de usuario y la experiencia del jugador para asegurar que el juego sea completo en todo sentido. 


# Descripción del Juego

El juego Sudoku tiene como objetivo rellenar todas las celdas de la cuadrícula 9x9 con números del 1 al 9.

# Reglas del Juego

1. Cada fila debe contener los números del 1 al 9 sin repetir ninguno.
2. Cada columna debe contener los números del 1 al 9 sin repetir ninguno.


# Desafío del Juego

El desafío del juego Sudoku es colocar los números de tal manera que se respeten las reglas mencionadas anteriores. Cada tablero viene con celdas previamente llenadas, esto sirve de guía al usuario para saber cómo debe de ser llenada y cuales números colocar estretégicamente. Estos números son importantes, ya que cada Sudoku tiene solo una única solución, por ende esos números ya establecidos juegan un papel importante a la hora de jugar.

# Dependencias e Instalación

Descargar una máquina virtual Linux, para poder correrlo desde la terminal.

# Pasos para Ejecución

1. Descargar los cuatro archivos de este repositorio y guardarlos todos en una misma carpeta.
2. Abrir la terminal y dirigirse a esa carpeta.
3. Descargar GTKWave, el cual es la interfaz del juego, mediante el comando:  sudo apt-get install libgtk-3-dev. (Solo se debe descargar una vez)
4. Ejecutar el programa con los comandos `make` y después `make run`. De esa manera se abrirá la interfaz para seleccionar la dificultad del Sudoku.
5. Una vez seleccionada la dificultad, se abrirá una nueva ventana de interfaz, donde aparecerá el Sudoku listo para jugarlo con la dificultad elegida.
6. Si se desea cambiar de dificultad, reiniciar o salir del juego, en la misma interfaz salen los botones correspondientes.
