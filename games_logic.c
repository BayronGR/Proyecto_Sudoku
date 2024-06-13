// Curso IE-0117
// Asignacion: Proyecto final.
// Archivo: games_logic.c
//Estudiantes: Bayron Guerrero Ruiz B73492, Mery Solano Mora B97584
// Juan Pablo Diaz Matamoros B82600, Anthonny Artavia Alpizar C10735

#include "game_logic.h"
#include <stdio.h>
#include <gtk/gtk.h>

// Variables globales
int (*selectedSudoku)[SIZE];
int userSudoku[SIZE][SIZE];

void selectSudoku(int difficulty) {
    switch (difficulty) {
        case EASY:
            selectedSudoku = easySudoku;
            break;
        case MEDIUM:
            selectedSudoku = mediumSudoku;
            break;
        case HARD:
            selectedSudoku = hardSudoku;
            break;
    }

    // Se inicializa el userSudoku con los valores del selectedSudoku
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            userSudoku[i][j] = selectedSudoku[i][j];
        }
    }
}

void printSudoku() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", userSudoku[i][j]);
        }
        printf("\n");
    }
}

int isValidMove(int row, int col, int num) {
    // Se comprueba la fila
    for (int i = 0; i < SIZE; i++) {
        if (userSudoku[row][i] == num) {
            return 0;
        }
    }

    // Se comprueba la columna
    for (int i = 0; i < SIZE; i++) {
        if (userSudoku[i][col] == num) {
            return 0;
        }
    }

    // Se comprueba el bloque 3x3
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
            if (userSudoku[i][j] == num) {
                return 0;
            }
        }
    }

    return 1;
}

int isSudokuComplete() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (userSudoku[i][j] == 0) {
                return 0;
            }
        }
    }
    return 1;
}