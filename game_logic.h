// Curso IE-0117
// Asignacion: Proyecto final.
// Archivo: game_logic.c
//Estudiantes: Bayron Guerrero Ruiz B73492, Mery Solano Mora B97584
// Juan Pablo Diaz Matamoros B82600, Anthonny Artavia Alpizar C10735

#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "sudokus.h"

// Se definen las variables que estan en otro archivo.
extern int (*selectedSudoku)[SIZE];
extern int userSudoku[SIZE][SIZE];

// Se utiliza para definir la dificultad del sudoku.
typedef enum {
    EASY,
    MEDIUM,
    HARD
} difficulty;

//Se declaran las funciones que estan en otro archivo de la fuente.
void selectSudoku(int difficulty);
void printSudoku();
int isValidMove(int row, int col, int num);
int isSudokuComplete();

#endif

