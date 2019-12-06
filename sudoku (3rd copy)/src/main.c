#include <gtk/gtk.h>
#include "sudoku.h"

#define MAX_SIZE 9

int linha, coluna;
GtkWidget *g_btn;
GtkLabel *g_lbl;
GtkButton *g_btn_display[MAX_SIZE][MAX_SIZE];
GtkButton *g_btn_input[MAX_SIZE];
struct element jogo[MAX_SIZE][MAX_SIZE];

int main(int argc, char *argv[])
{
    int i, j;
    GtkBuilder      *builder;
    GtkWidget       *window;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file ("glade/window_main.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);

    // get pointers to the two labels
    g_lbl = GTK_LABEL(gtk_builder_get_object(builder, "lbl"));
    g_btn = GTK_WIDGET(gtk_builder_get_object(builder, "btn"));

    char btn_name[20];
    for(i=0;i<MAX_SIZE;i++){
      sprintf(btn_name, "btn_input_%d", i + 1);
      g_btn_input[i] = GTK_BUTTON(gtk_builder_get_object(builder, btn_name));
      for(j=0;j<MAX_SIZE;j++){
        sprintf(btn_name, "btn_display_%d%d", i, j);
        g_btn_display[i][j] = GTK_BUTTON(gtk_builder_get_object(builder, btn_name));
      }
    }


    g_object_unref(builder);


    gtk_widget_show(window);
    gtk_main();

    return 0;
}

// called when button is clicked
void on_btn_clicked()
{
  int i, j;
  start( jogo );
  char str[10];
  for(i=0;i<MAX_SIZE;i++){
    for(j=0;j<MAX_SIZE;j++){      
      if(jogo[i][j].value == 0)
        gtk_button_set_label(g_btn_display[i][j], " ");
      else{
        sprintf(str, "%d", jogo[i][j].value);
        gtk_button_set_label(g_btn_display[i][j], str);
      }
    }
  }
}

void on_btn_display_clicked( GtkButton *button, gpointer data ){
  int i, j;
  for(i=0; i<MAX_SIZE; i++){
    for(j=0; j<MAX_SIZE; j++){
      if(button == g_btn_display[i][j]){
        linha = i;
        coluna = j;
      }
    }
  }
}

void on_btn_input_clicked( GtkButton *button, gpointer data ){
  gtk_button_set_label(g_btn_display[linha][coluna], gtk_button_get_label(button));
}


// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}
