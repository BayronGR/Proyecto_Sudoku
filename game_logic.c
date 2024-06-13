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

//Verifica si un movimiento es válido en el Sudoku.
int isValidMove(int row, int col, int num) {
    // Se comprueba la fila
    for (int i = 0; i < SIZE; i++) { // Se itera sobre las columnas de la fila dada
        if (userSudoku[row][i] == num) { // Revisa si el número ya está en la fila
            return 0; // Movimiento inválido
        }
    }

    // Se comprueba la columna
    for (int i = 0; i < SIZE; i++) { // Se itera sobre las filas de la columna dada
        if (userSudoku[i][col] == num) { // Revisa si el número ya está en la columna
            return 0; // Movimiento inválido
        }
    }
        // Se comprueba el bloque 3x3
    int startRow = (row / 3) * 3; // Se calcula la fila inicial del bloque 3x3
    int startCol = (col / 3) * 3; // Se calcula la columna inicial del bloque 3x3
    for (int i = startRow; i < startRow + 3; i++) { // Se itera sobre las filas del bloque 3x3
        for (int j = startCol; j < startCol + 3; j++) { // Se itera sobre las columnas del bloque 3x3
            if (userSudoku[i][j] == num) { // Revisa si el número ya está en el bloque 3x3
                return 0; // Movimiento inválido
            }
        }
    }

    return 1; // Movimiento válido
}

// Verifica si el Sudoku está completo
int isSudokuComplete() {
    for (int i = 0; i < SIZE; i++) { // Se itera sobre las filas del Sudoku
        for (int j = 0; j < SIZE; j++) { // Se itera sobre las columnas del Sudoku
            if (userSudoku[i][j] == 0) { // Revisa si hay una celda vacía (con valor 0)
                return 0; // Retorna el sudoku incompleto
            }
        }
    }
    return 1; // Retorna el sudoku completo
}
