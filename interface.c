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