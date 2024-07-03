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

    for (int i = 0; i < 9; ++i) {                          // Recorre las filas del tablero
        for (int j = 0; j < 9; ++j) {                      // Recorre las columnas del tablero
            const char *text = gtk_entry_get_text(GTK_ENTRY(entry_grid[i][j])); // Se obtiene el texto del widget de entrada
            if (strlen(text) == 1 && text[0] >= '1' && text[0] <= '9') {  // Verifica que el texto tenga solo un caracter y que sea un numero del 1 al 9.
                user_board[i][j] = text[0] - '0';      // Convierte el texto a un numero
            } else if (strlen(text) == 0) {            // Verifica si la celda está vacia
                user_board[i][j] = 0;                  // Establece la celda vacia como 0
                complete = FALSE;                      // Se marca el Sudoku como incompleto
            } else {                                   // Si el texto no es válido
                valid_input = FALSE;                   // Se marca la entrada como invalida
                break;                                 // Se sale del bucle
            }
        }
        if (!valid_input) break;       // Si se encontro una entrada invalida, sale del bucle
    }

    // Si se encontro una entrada invalida
    if (!valid_input) {               
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_CLOSE,
                                                   "¡Solo se permiten números del 1 al 9 en las celdas!");                // Se crea un dialogo de error para entradas invalidas
        gtk_dialog_run(GTK_DIALOG(dialog));   // Se muestra el dialogo de error
        gtk_widget_destroy(dialog);           // Se destruye el dialogo de error
        return;                               // Se termina la funcion
    }

    if (!is_valid_sudoku(user_board)) { // Verifica que no haya duplicados en filas y columnas
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_CLOSE,
                                                   "¡Hay números duplicados en una fila o columna!");  // Se crea un dialogo de error para duplicados
        gtk_dialog_run(GTK_DIALOG(dialog));     // Se muestra el dialogo de error
        gtk_widget_destroy(dialog);             // Se destruye el dialogo de error
        return;                                 // Se termina la funcion
    }

    if (complete && verify_sudoku_solution(user_board, solved_board)) {  // Verifica si el Sudoku esta completo y correcto
        show_congratulations();                                          // Se muestra el mensaje de felicitaciones si es correcto
    } else if (!complete) {                                             // Si el Sudoku no esta completo
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_CLOSE,
                                                   "¡El Sudoku no está completo!"); // Se crea un dialogo de error para el Sudoku incompleto
        gtk_dialog_run(GTK_DIALOG(dialog));                                     // Se muestra el dialogo de error
        gtk_widget_destroy(dialog);                                             // Se destruye el dialogo de error
    } else {                                                                    // Si el Sudoku esta completo pero incorrecto
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_CLOSE,
                                                   "¡La solución no es correcta!"); // Se crea un dialogo de error para soluciones incorrectas
        gtk_dialog_run(GTK_DIALOG(dialog));                                     // Se muestra el dialogo de error
        gtk_widget_destroy(dialog);                                             // Se destruye el dialogo de error
    }
}

// Se crea una funcion para mostrar el mensaje de felicitaciones
void show_congratulations() {
    // Se crea una nueva ventana para las felicitaciones, se establece el titulo y el tamano predeterminado
    GtkWidget *congrats_window = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
    gtk_window_set_title(GTK_WINDOW(congrats_window), "Felicidades");
    gtk_window_set_default_size(GTK_WINDOW(congrats_window), 300, 200);

    // Se crea un contenedor vertical y se anade el contenedor a la ventana de felicitaciones 
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(congrats_window), box);

    GtkWidget *label = gtk_label_new("¡Felicidades! Has completado el Sudoku.");  // Se crea una etiqueta de felicitaciones 
    GtkWidget *menu_button = gtk_button_new_with_label("Volver al Menú Principal");  // Se crea un boton para volver al menu principal 
    GtkWidget *exit_button = gtk_button_new_with_label("Salir");  // Se crea un boton para salir del juego

    g_signal_connect(menu_button, "clicked", G_CALLBACK(show_difficulty_menu), NULL);  // Se conecta el boton con la funcion del menu de dificultad 
    g_signal_connect(exit_button, "clicked", G_CALLBACK(gtk_main_quit), NULL);  // Se conecta el boton con la funcion para salir de la aplicacion 

    // Se anade la etiqueta y los botones al contenedor vertical 
    gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), menu_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), exit_button, TRUE, TRUE, 0);

    // Se muestran todos los widgets de la ventana de felicitaciones
    gtk_widget_show_all(congrats_window);
}

int main(int argc, char *argv[]) {
     
    // Se inicializa la biblioteca GTK
    gtk_init(&argc, &argv);

    show_difficulty_menu();

    gtk_main(); // Se entra en el bucle principal de GTK

    return 0;
}
