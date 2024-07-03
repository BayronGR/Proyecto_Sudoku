// Se definen los encabezados
#ifndef SUDOKU_BOARDS_H
#define SUDOKU_BOARDS_H

// Se define el tablero facil de Sudoku, matriz 9x9
int easy_board[9][9] = {
    {2, 7, 6, 1, 9, 8, 4, 3, 5},
    {4, 8, 0, 0, 0, 0, 2, 1, 0},
    {5, 1, 3, 6, 4, 0, 9, 7, 8},
    {0, 0, 0, 0, 3, 5, 0, 6, 1},
    {0, 5, 7, 9, 0, 0, 0, 4, 2},
    {6, 3, 0, 0, 0, 0, 0, 8, 9},
    {8, 9, 0, 0, 7, 0, 0, 2, 3},
    {0, 0, 0, 0, 6, 0, 1, 5, 7},
    {7, 6, 1, 5, 0, 0, 8, 9, 4}
};

// Se define el tablero medio de Sudoku, matriz 9x9
int medium_board[9][9] = {
    {7, 0, 0, 0, 3, 0, 5, 4, 0},
    {0, 0, 4, 8, 6, 7, 2, 0, 3},
    {3, 0, 0, 0, 9, 5, 6, 0, 0},
    {9, 0, 1, 0, 5, 0, 7, 6, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 4, 5, 0, 2, 0, 1, 0, 8},
    {0, 0, 7, 9, 8, 0, 0, 0, 5},
    {8, 0, 9, 2, 4, 1, 3, 0, 0},
    {0, 2, 6, 0, 7, 0, 0, 0, 1}
};

// Se define el tablero dificil de Sudoku, matriz 9x9
int hard_board[9][9] = {
    {7, 0, 0, 0, 0, 0, 0, 6, 0},
    {0, 0, 0, 0, 3, 8, 0, 0, 0},
    {0, 2, 0, 5, 7, 0, 9, 0, 0},
    {0, 0, 0, 0, 1, 2, 5, 0, 0},
    {0, 0, 2, 8, 0, 0, 0, 0, 4},
    {9, 4, 0, 7, 5, 0, 0, 0, 0},
    {4, 0, 6, 0, 0, 0, 8, 0, 5},
    {0, 0, 0, 0, 0, 0, 6, 0, 0},
    {5, 0, 0, 0, 0, 0, 0, 7, 0}
};

#endif // SUDOKU_BOARDS_H