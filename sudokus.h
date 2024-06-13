// Curso IE-0117
// Asignacion: Proyecto final.
// Archivo: sudokus.h
//Estudiantes: Bayron Guerrero Ruiz B73492, Mery Solano Mora B97584
// Juan Pablo Diaz Matamoros B82600, Anthonny Artavia Alpizar C10735


#ifndef SUDOKUS_H
#define SUDOKUS_H

// Este nos indica el tamaño del tablero del Sudoku, que es 9x9.
#define SIZE 9

// Esto nos ndica que las matrices están definidas en otro archivo 
extern int easySudoku[SIZE][SIZE];
extern int mediumSudoku[SIZE][SIZE];
extern int hardSudoku[SIZE][SIZE];

// Se segura que todo el contenido del archivo solo se incluya una vez por cada archivo de código fuente que lo incluye.
#endif
