#include <gtk/gtk.h>
#include "game_logic.h"

GtkWidget *entries[SIZE][SIZE];

void on_activate(GtkApplication *app, gpointer user_data);
void check_entry(GtkWidget *widget, gpointer data);
void reset_game(GtkWidget *widget, gpointer data);
void return_to_menu(GtkWidget *widget, gpointer data);
void show_menu(GtkWidget *widget, gpointer data);
void show_completion_message();
void show_game_window(GtkWidget *widget, gpointer data);
void difficulty_button_clicked(GtkButton *button, gpointer data);

void show_game_window(GtkWidget *widget, gpointer data) {
    int difficulty = GPOINTER_TO_INT(data);

    // Lógica para seleccionar el nivel
    selectSudoku(difficulty);

    // Crear la ventana de juego
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *entry;
    GtkWidget *reset_button;
    GtkWidget *menu_button;
    GtkWidget *exit_button;
    char buffer[2];


        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Sudoku");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            entry = gtk_entry_new();
            entries[i][j] = entry;

            int sudoku_value = selectedSudoku[i][j];
            if (sudoku_value != 0) {
                sprintf(buffer, "%d", sudoku_value);
                gtk_entry_set_text(GTK_ENTRY(entry), buffer);
                gtk_editable_set_editable(GTK_EDITABLE(entry), FALSE);
            } else {
                g_signal_connect(entry, "changed", G_CALLBACK(check_entry), GINT_TO_POINTER(i * SIZE + j));
            }

            gtk_widget_set_size_request(entry, 30, 30); // Ajusta el tamaño según tus necesidades
            gtk_grid_attach(GTK_GRID(grid), entry, j, i, 1, 1);
        }
    }

    // Crear botones para reiniciar el juego y volver al menú principal
    reset_button = gtk_button_new_with_label("Reiniciar Juego");
    g_signal_connect(reset_button, "clicked", G_CALLBACK(reset_game), GINT_TO_POINTER(difficulty));
    gtk_grid_attach(GTK_GRID(grid), reset_button, 0, SIZE, SIZE / 3, 1);

    menu_button = gtk_button_new_with_label("Volver al Menú Principal");
    g_signal_connect(menu_button, "clicked", G_CALLBACK(return_to_menu), window);
    gtk_grid_attach(GTK_GRID(grid), menu_button, SIZE / 3, SIZE, SIZE / 3, 1);

    // Crear botón de salida
    exit_button = gtk_button_new_with_label("Salir");
    g_signal_connect(exit_button, "clicked", G_CALLBACK(gtk_window_close), window); // Cerrar la ventana en lugar de llamar a gtk_main_quit directamente
    gtk_grid_attach(GTK_GRID(grid), exit_button, 2 * (SIZE / 3), SIZE, SIZE / 3, 1);

    gtk_widget_show_all(window);
}