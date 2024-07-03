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

      // Se llena la cuadricula con entradas para cada celda del Sudoku
    for (int i = 0; i < 9; ++i) {                        // Recorre las filas del tablero
        for (int j = 0; j < 9; ++j) {                    // Recorre las columna del tablero
            entry_grid[i][j] = gtk_entry_new();          // Se crea un nuevo widget de entrada
            gtk_entry_set_max_length(GTK_ENTRY(entry_grid[i][j]), 1);  // Se establece la longitud maxima de la entrada a un caracter
            if (current_board[i][j] != 0) {              // Si la celda del tablero actual no esta vacia 
                char str[2];                             // Se crea un arreglo de caracteres para el numero
                sprintf(str, "%d", current_board[i][j]); // Se convierte el numero a una cadena 
                gtk_entry_set_text(GTK_ENTRY(entry_grid[i][j]), str);  // Se establece el texto del widget de entrada 
                gtk_editable_set_editable(GTK_EDITABLE(entry_grid[i][j]), FALSE);  // Hace que el widget de entrada no sea editable 
            }
            gtk_grid_attach(GTK_GRID(grid), entry_grid[i][j], j, i, 1, 1);  // Se anade el widget de entrada a la cuadricula 
        }
    }
      // Se crean botones para verificar, volver al menu principal y salir 
    GtkWidget *verify_button = gtk_button_new_with_label("Verificar");  // Se crea un boton para verificar el Sudoku 
    g_signal_connect(verify_button, "clicked", G_CALLBACK(verify_sudoku), NULL);  // Se conecta el boton con la funcion de verificacion 

    GtkWidget *main_menu_button = gtk_button_new_with_label("Menú Principal");  // Se crea un boton para volver al menu principal 
    g_signal_connect(main_menu_button, "clicked", G_CALLBACK(show_difficulty_menu), NULL); // Se conecta el boton con la funcion del menu de dificultad 

    GtkWidget *exit_button = gtk_button_new_with_label("Salir"); // Se crea un boton para salir del juego
    g_signal_connect(exit_button, "clicked", G_CALLBACK(gtk_main_quit), NULL);  // Se conecta el boton con la funcion para salir de la aplicacion

    // Se anade los botones a la cuadricula 
    gtk_grid_attach(GTK_GRID(grid), verify_button, 0, 9, 3, 1);
    gtk_grid_attach(GTK_GRID(grid), main_menu_button, 3, 9, 3, 1);
    gtk_grid_attach(GTK_GRID(grid), exit_button, 6, 9, 3, 1);

    // Se muestran todos los widgets en la ventana del juego 
    gtk_widget_show_all(window);
}

// Se crea una funcion para verificar las respuestas del Sudoku
void verify_sudoku(GtkWidget *widget, gpointer data) {
    int user_board[9][9];               // Matriz para el tablero del usuario
    gboolean valid_input = TRUE;        // Se verifica la validez de las entradas
    gboolean complete = TRUE;           // Se verifica si el Sudoku esta completo

    // Se crea una funcion para verificar que no haya numeros duplicados en una fila o columna.
    gboolean is_valid_sudoku(int board[9][9]) {
        for (int i = 0; i < 9; ++i) {               // Recorre las filas del tablero
            gboolean row_seen[10] = { FALSE };      // Arreglo que verifica los duplicados en la fila 
            gboolean col_seen[10] = { FALSE };      // Arreglo que verifica los duplicados en la columna 
            for (int j = 0; j < 9; ++j) {           // Recorre las columnas del tablero
                if (board[i][j] != 0) {             // Verifica si el valor en la fila no es 0
                    if (row_seen[board[i][j]]) return FALSE;  // Si ya se vio este numero en la fila, retorna FALSE
                    row_seen[board[i][j]] = TRUE;   // Se marca el numero como visto en la fila
                }
                if (board[j][i] != 0) {            // Verifica si el valor en la columna no es 0 
                    if (col_seen[board[j][i]]) return FALSE;  // Si ya se vio este numero en la columna, retorna FALSE
                    col_seen[board[j][i]] = TRUE;  // Se marca el numero como visto en la columna
                }
            }
        }
        return TRUE;   // Se retorna TRUE si no se encontraron numeros duplicados
    }