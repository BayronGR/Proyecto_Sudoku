// Se definen los encabezados
#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

// Se incluye la biblioteca para usar el tipo de dato tool
#include <stdbool.h>

// Se crea una funcion para verificar si es seguro colocar un numero en una posicion especifica del tablero
bool is_safe(int board[9][9], int row, int col, int num) {
    for (int x = 0; x < 9; x++) {   // Recorre cada celda de la fila y la columna
        // Verifica si el numero ya esta presente en la fila, columna o un subcuadro de 3x3
        if (board[row][x] == num || board[x][col] == num || 
            board[row - row % 3 + x / 3][col - col % 3 + x % 3] == num) {
            return false;  // Retorna FALSE si ya se encuentra el numero
        }
    }
    return true;  // Retorna TRUE si es seguro colocar el numero
}

// Se crea una funcion que resuelve el Sudoku usando el algoritmo de backtracking
bool solve_sudoku(int board[9][9]) {
    int row = -1, col = -1;    // Variables para almacenar la posicion de una celda vacia
    bool is_empty = true;      // Se indica si hay celdas vacias en el tablero 
    
    // Se encuentra una celda vacia en el tablero 
    for (int i = 0; i < 9 && is_empty; i++) {  // Recorre las filas 
        for (int j = 0; j < 9 && is_empty; j++) {  // Recorre las columnas
            if (board[i][j] == 0) {  // Si se encuentra una celda vacia 
                row = i;             // Almacena la fila de la celda vacia
                col = j;             // Almacena la columna de la celda vacia
                is_empty = false;    // Se cambia a FALSE
            }
        }
    }

    // Si no hay celdas vacias el Sudoku esta resuelto 
    if (is_empty) return true;

    // Se prueban los numeros del 1 al 9 
    for (int num = 1; num <= 9; num++) {   
        if (is_safe(board, row, col, num)) {   // Se verifica si es seguro colocar el numero
            board[row][col] = num;             // Coloca el numero en la celda 
            
            // Llama recursivamente para resolver el resto del tablero 
            if (solve_sudoku(board)) return true;
            board[row][col] = 0;  // Si falla, retrocede y elimina el numero
        }
    }

    return false;   // Retorna FALSE si no puede resolver el Sudoku
}

// Se crea una funcion para verificar si la solucion del usuario coincide con la solucion correcta 
bool verify_sudoku_solution(int user_board[9][9], int solved_board[9][9]) {
    for (int i = 0; i < 9; i++) {        // Recorre las filas del tablero 
        for (int j = 0; j < 9; j++) {    // Recorre las columnas del tablero 
        
            // Se verifica si el valor de la celda del usuario coincide con la solucion correcta
            if (user_board[i][j] != 0 && user_board[i][j] != solved_board[i][j]) {
                return false;  // Retorna FALSE si no hay coincidencia 
            }
        }
    }
    return true;  // Retorna TRUE si todas las celdas coinciden 
}

#endif // SUDOKU_SOLVER_H    // Termina la definicion del encabezado 
