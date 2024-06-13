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


void on_activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button_easy, *button_medium, *button_hard, *button_exit;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Sudoku");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    button_easy = gtk_button_new_with_label("Fácil");
    g_signal_connect(button_easy, "clicked", G_CALLBACK(show_game_window), GINT_TO_POINTER(EASY)); // EASY representa la dificultad fácil
    gtk_grid_attach(GTK_GRID(grid), button_easy, 0, 0, 1, 1);

    button_medium = gtk_button_new_with_label("Medio");
    g_signal_connect(button_medium, "clicked", G_CALLBACK(show_game_window), GINT_TO_POINTER(MEDIUM)); // MEDIUM representa la dificultad media
    gtk_grid_attach(GTK_GRID(grid), button_medium, 0, 1, 1, 1);

    button_hard = gtk_button_new_with_label("Difícil");
    g_signal_connect(button_hard, "clicked", G_CALLBACK(show_game_window), GINT_TO_POINTER(HARD)); // HARD representa la dificultad difícil
    gtk_grid_attach(GTK_GRID(grid), button_hard, 0, 2, 1, 1);

    button_exit = gtk_button_new_with_label("Salir");
    g_signal_connect(button_exit, "clicked", G_CALLBACK(gtk_window_close), window); // Cerrar la ventana en lugar de llamar a gtk_main_quit directamente
    gtk_grid_attach(GTK_GRID(grid), button_exit, 0, 3, 1, 1);

    gtk_widget_show_all(window);
}

void check_entry(GtkWidget *widget, gpointer data) {
    const gchar *entry_text;
    int num;
    int index = GPOINTER_TO_INT(data);
    int row = index / SIZE;
    int col = index % SIZE;

    entry_text = gtk_entry_get_text(GTK_ENTRY(widget));
    if (g_strcmp0(entry_text, "") != 0) {
        num = atoi(entry_text);
        if (isValidMove(row, col, num)) {
            userSudoku[row][col] = num;
            if (isSudokuComplete()) {
                show_completion_message();
            }
        } else {
            gtk_entry_set_text(GTK_ENTRY(widget), "");
        }
    } else {
        userSudoku[row][col] = 0;
    }
}

void reset_game(GtkWidget *widget, gpointer data) {
    int difficulty = GPOINTER_TO_INT(data);
    selectSudoku(difficulty);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (selectedSudoku[i][j] != 0) {
                char buffer[2];
                sprintf(buffer, "%d", selectedSudoku[i][j]);
                gtk_entry_set_text(GTK_ENTRY(entries[i][j]), buffer);
                gtk_editable_set_editable(GTK_EDITABLE(entries[i][j]), FALSE);
            } else {
                gtk_entry_set_text(GTK_ENTRY(entries[i][j]), "");
                gtk_editable_set_editable(GTK_EDITABLE(entries[i][j]), TRUE);
            }
        }
    }
}

void return_to_menu(GtkWidget *widget, gpointer data) {
    GtkWidget *window = GTK_WIDGET(data);
    gtk_widget_destroy(window);
}

void show_completion_message() {
    GtkWidget *dialog;
    GtkWidget *content_area;
    GtkWidget *label;
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;

    dialog = gtk_dialog_new_with_buttons("¡Felicidades!",
                                         NULL,
                                         flags,
                                         "Aceptar",
                                         GTK_RESPONSE_ACCEPT,
                                         NULL);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    label = gtk_label_new("¡Has completado el Sudoku!");
    gtk_container_add(GTK_CONTAINER(content_area), label);

    g_signal_connect_swapped(dialog, "response", G_CALLBACK(gtk_widget_destroy), dialog);

    gtk_widget_show_all(dialog);
}