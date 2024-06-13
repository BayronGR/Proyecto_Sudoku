// Curso IE-0117
// Asignacion: Proyecto final.
// Archivo: sudokus.c
//Estudiantes: Bayron Guerrero Ruiz B73492, Mery Solano Mora B97584
// Juan Pablo Diaz Matamoros B82600, Anthonny Artavia Alpizar C10735
#include "sudokus.h"

// Esta es la logica de la matriz con dificultad sencilla.
int easySudoku[SIZE][SIZE] = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}
};

// Esta es la logica de la matriz con dificultad media.
int mediumSudoku[SIZE][SIZE] = {
    {0, 2, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 6, 0, 0, 0, 0, 3},
    {0, 7, 4, 0, 8, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 3, 0, 0, 2},
    {0, 8, 0, 0, 4, 0, 0, 1, 0},
    {6, 0, 0, 5, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 7, 8, 0},
    {5, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0}
};

// Esta es la logica de la matriz con dificultad sencilla.
int hardSudoku[SIZE][SIZE] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 6, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0}
};
