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

// Se crea una funcion para mostrar el menu de dificultad 
void show_difficulty_menu() {
    // Se destruyen las ventanas anteriores si existen 
    if (window) gtk_widget_destroy(window);
    if (difficulty_window) gtk_widget_destroy(difficulty_window);
    
    // Se crea una nueva ventana para seleccionar la dificultad con titulo y tamano predeterminado
    difficulty_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(difficulty_window), "Selecciona la dificultad");
    gtk_window_set_default_size(GTK_WINDOW(difficulty_window), 300, 200);
    
    // Se crea un contenedor vertical y se anade a la ventana de dificultad
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5); // Se acomodan los widgets uno debajo del otro verticalmente con un espacio de 5 pixeles entre cada uno 
    gtk_container_add(GTK_CONTAINER(difficulty_window), box);

    // Se crea un boton para cada dificultad: facil, medio y dificil
    GtkWidget *easy_button = gtk_button_new_with_label("Fácil");
    GtkWidget *medium_button = gtk_button_new_with_label("Medio");
    GtkWidget *hard_button = gtk_button_new_with_label("Difícil");

    // Se conecta cada boton de dificultad con la funcion de inicio del juego, pasando al tablero correspondiente
    g_signal_connect(easy_button, "clicked", G_CALLBACK(start_game), easy_board);
    g_signal_connect(medium_button, "clicked", G_CALLBACK(start_game), medium_board);
    g_signal_connect(hard_button, "clicked", G_CALLBACK(start_game), hard_board);

    // Se anaden los botones al contenedor vertical 
    gtk_box_pack_start(GTK_BOX(box), easy_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), medium_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), hard_button, TRUE, TRUE, 0);

    // Se muestran todos los widgets de la ventana de dificultad
    gtk_widget_show_all(difficulty_window);
}
<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes
// Se crea una funcion para iniciar el juego con la dificultad seleccionada
void start_game(GtkWidget *widget, gpointer data) {
    // Se copia el tablero seleccionado al tablero actual y al tablero resuelto
    int (*selected_board)[9] = (int (*)[9])data;
    memcpy(current_board, selected_board, sizeof(current_board));
    memcpy(solved_board, selected_board, sizeof(solved_board));
    
    // Resuelve el Sudoku y almacena la solucion en solved_board
    solve_sudoku(solved_board);

    // Se destruye la ventana de dificultad si existe 
    if (difficulty_window) gtk_widget_destroy(difficulty_window);

    // Se crea una nueva ventana para el juego con titulo y un tamano predeterminado 
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Sudoku");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

    // Se crea un nuevo contenedor de cuadricula y se anade a la ventana del juego
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);