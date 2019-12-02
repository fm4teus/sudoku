#include <gtk/gtk.h>

#define MAX_SIZE 9

GtkWidget *g_btn;
GtkLabel *g_lbl;
GtkEntry *g_input[MAX_SIZE][MAX_SIZE];

int main(int argc, char *argv[])
{
    GtkBuilder      *builder;
    GtkWidget       *window;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file ("glade/window_main.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);

    // get pointers to the two labels
    g_lbl = GTK_LABEL(gtk_builder_get_object(builder, "lbl"));
    g_btn = GTK_WIDGET(gtk_builder_get_object(builder, "btn"));

    int i, j;
    char input_name[10];
    for(i=0;i<MAX_SIZE;i++){
      for(j=0;j<MAX_SIZE;j++){
        sprintf(input_name, "input_%d%d", i, j);
        g_input[i][j] = GTK_ENTRY(gtk_builder_get_object(builder, input_name));
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
  FILE *fr;
  fr = fopen("src/test.txt", "r");
  int i, j;

  char str[10];
  char c;
  for(i=0;i<MAX_SIZE;i++){
    for(j=0;j<MAX_SIZE;j++){
      fscanf(fr,"%c",&c);
      if(c == '0')
          gtk_entry_set_text(g_input[i][j], " ");
      else{
        sprintf(str, "%c", c);
        gtk_entry_set_text(g_input[i][j], str);
      }
    }
  }
  fclose(fr);

}

// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}
