// main.c
// Se incluye la biblioteca estandar y el archivo header.h
#include <stdio.h>
#include "game_logic.h"

// Se declara una función externa para ejecutar la interfaz gráfica
extern int run_interface(int argc, char **argv);

// Aca se muestra el menú principal para seleccionar la dificultad del Sudoku.
void show_main_menu() {
    int difficulty; // Esta variable almacena la dificultad seleccionada

    // Se imprimir el menú de selección de dificultad
    printf("Seleccione la dificultad del Sudoku:\n");
    printf("1. Sudoku fácil\n");
    printf("2. Sudoku medio\n");
    printf("3. Sudoku difícil\n");
    printf("Opción: ");
    scanf("%d", &difficulty); // Se lee la opción seleccionada por el usuario

    selectSudoku(difficulty); // Se encarga de llamar a la función para seleccionar el sudoku según la dificultad
    printSudoku();
}

// Función principal del programa.
int main(int argc, char **argv) {
    show_main_menu(); // Se muestra el menú principal para seleccionar la dificultad
    return run_interface(argc, argv); // Se ejecutar la interfaz gráfica y retorna su código de salida
}
