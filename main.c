// Se incluyen las bibliotecas y archivos a utilizar 
#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include "sudoku_boards.h"
#include "sudoku_solver.h"

// Se declaran las variables globales
GtkWidget *window;              // Ventana principal del juego 
GtkWidget *difficulty_window;   // Ventana para seleccionar la dificultad
GtkWidget *grid;                // Cuadricula del Sudoku
GtkWidget *entry_grid[9][9];    // Matriz con numeros de entrada para el Sudoku
int current_board[9][9];        // Matriz para el tablero actual del Sudoku
int solved_board[9][9];         // Matriz para el tablero con la solucion del Sudoku

// Se declaran las funciones
void start_game(GtkWidget *widget, gpointer data);     // Funcion para iniciar el juego con la difultad seleccionada
void verify_sudoku(GtkWidget *widget, gpointer data);  // Funcion para verificar las respuestas del Sudoku
void show_congratulations();                           // Funcion para mostrar el mensaje de felicitaciones
void show_difficulty_menu();                           // Funcion para mostrar el menu de dificultad   

