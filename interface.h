#ifndef INTERFACE_H
#define INTERFACE_H
#include <gtk/gtk.h>


void show_main_menu(GtkApplication *app);
void on_activate(GtkApplication *app, gpointer user_data);
void check_entry(GtkWidget *widget, gpointer data);
void reset_game(GtkWidget *widget, gpointer data);
void return_to_menu(GtkWidget *widget, gpointer data);
void show_menu(GtkWidget *widget, gpointer data);
void show_completion_message();
void show_game_window(int difficulty);
void difficulty_button_clicked(GtkButton *button, gpointer data);

#endif //INTERFACE_H