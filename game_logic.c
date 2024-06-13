// game_logic.c
// Se incluye el archivo header.h del juego, la biblioteca estandar, y la biblioteca GTK para interfaces graficas 
#include "game_logic.h"
#include <stdio.h>
#include <gtk/gtk.h>

// Variables generales
int (*selectedSudoku)[SIZE]; // Puntero a una matriz del Sudoku seleccionado según la dificultad
int userSudoku[SIZE][SIZE]; // Matriz que representa el Sudoku que el usuario está resolviendo

// Nivel de dificultad del Sudoku (EASY, MEDIUM, HARD)

void selectSudoku(int difficulty) {
    switch (difficulty) {  // Acá se selecciona el Sudoku en función de la dificultad
        case EASY: 
            selectedSudoku = easySudoku; // Selecciona el Sudoku fácil
            break;
        case MEDIUM:
            selectedSudoku = mediumSudoku; // Selecciona el Sudoku medio
            break;
        case HARD:
            selectedSudoku = hardSudoku; // Selecciona el Sudoku difícil
            break;
    }

    // Se inicializa el sudoku con los valores seleccionados 
    for (int i = 0; i < SIZE; i++) { // Se itera sobre las filas del Sudoku
        for (int j = 0; j < SIZE; j++) { // Se itera sobre las columnas del Sudoku
            userSudoku[i][j] = selectedSudoku[i][j]; // Se copia el valor del Sudoku seleccionado a userSudoku
        }
    }
}

// Aca se imprime el Sudoku del usuario en la interfaz
void printSudoku() {
    for (int i = 0; i < SIZE; i++) { // Se itera sobre las filas del Sudoku
        for (int j = 0; j < SIZE; j++) { // Se itera sobre las columnas del Sudoku
            printf("%d ", userSudoku[i][j]); // Imprime el valor actual
        }
        printf("\n"); // Imprime una nueva línea al final de cada fila
    }
}
