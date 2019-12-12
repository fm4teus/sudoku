#include <gtk/gtk.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "sudoku.h"

#define MAX_SIZE 9

int linha = 0, coluna = 0, penalty, level = EASY;
time_t game_start, game_end;
GtkWidget *g_btn;
GtkLabel *g_lbl;
GtkButton *g_btn_display[MAX_SIZE][MAX_SIZE];
GtkButton *g_btn_input[MAX_SIZE];
//GtkButton *g_btn_test[MAX_SIZE];
GtkWidget *g_btn_easy;
GtkWidget *g_btn_medium;
GtkWidget *g_btn_hard;
GtkWidget *g_img;
GtkWidget *g_img_btn_display[MAX_SIZE*MAX_SIZE];
GtkWidget *g_img_blue_input[MAX_SIZE];
GtkEntry *g_entry_name;
element jogo[MAX_SIZE][MAX_SIZE];



void hide_btn_input(){
  for(int i=0; i<MAX_SIZE; i++){
    g_object_set(g_btn_input[i], "visible", false, NULL);
  }
}

void show_btn_input(){
  for(int i=0; i<MAX_SIZE; i++){
    g_object_set(g_btn_input[i], "visible", true, NULL);
  }
}

int main(int argc, char *argv[])
{
    int i, j;
    GtkBuilder      *builder;
    GtkWidget       *window;
    

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("glade/window_main.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);

    // get pointers to the two labels
    g_lbl = GTK_LABEL(gtk_builder_get_object(builder, "lbl"));
    g_btn = GTK_WIDGET(gtk_builder_get_object(builder, "btn"));
    g_btn_easy = GTK_WIDGET(gtk_builder_get_object(builder, "btn_easy"));
    g_btn_medium = GTK_WIDGET(gtk_builder_get_object(builder, "btn_medium"));
    g_btn_hard = GTK_WIDGET(gtk_builder_get_object(builder, "btn_hard"));
    g_img = GTK_WIDGET(gtk_builder_get_object(builder, "img"));
    g_entry_name = GTK_ENTRY(gtk_builder_get_object(builder, "entry_name"));
    
    g_object_set(g_btn_easy,"visible",false,NULL);
    g_object_set(g_btn_medium,"visible",false,NULL);
    g_object_set(g_btn_hard,"visible",false,NULL);



    // get pointers to the buttons
    char btn_name[20];
    for(i=0;i<MAX_SIZE;i++){
      sprintf(btn_name, "btn_input%d", i+1 );
      g_btn_input[i] = GTK_BUTTON(gtk_builder_get_object(builder, btn_name));
      g_object_set(g_btn_input[i],"visible",false,NULL);

      sprintf(btn_name, "img_blue_input%d", i+1 );
      g_img_blue_input[i] = GTK_WIDGET(gtk_builder_get_object(builder, btn_name));
      g_object_set(g_img_blue_input[i],"visible",false,NULL);
      
      for(j=0;j<MAX_SIZE;j++){
        sprintf(btn_name, "img_blue%d", MAX_SIZE*i + j );
        g_img_btn_display[MAX_SIZE*i + j] = GTK_WIDGET(gtk_builder_get_object(builder, btn_name));
        g_object_set(g_img_btn_display[MAX_SIZE*i + j], "visible", false, NULL);

        sprintf(btn_name, "btn_display_%d%d", i, j);
        g_btn_display[i][j] = GTK_BUTTON(gtk_builder_get_object(builder, btn_name));
        g_object_set(g_btn_display[i][j], "visible", false, NULL);
      }
    }
    g_object_set(g_img, "visible", false, NULL);

    g_object_unref(builder);

    gtk_widget_show(window);
    gtk_main();

    return 0;
}


// called when button is clicked

void on_btn_clicked(){
  g_object_set(g_btn_easy, "visible", true, NULL);
  g_object_set(g_btn_medium, "visible", true, NULL);
  g_object_set(g_btn_hard, "visible", true, NULL);
  for(int i=0; i<MAX_SIZE*MAX_SIZE; i++)
    g_object_set(g_img_btn_display[i], "visible", false, NULL);
}

void on_btn_easy_clicked()
{
  level = EASY;
  g_object_set(g_btn_easy,"visible",false,NULL);
  g_object_set(g_btn_medium,"visible",false,NULL);
  g_object_set(g_btn_hard,"visible",false,NULL);
  g_object_set(g_img, "visible", true, NULL);
  time(&game_start);
  penalty = 0;
  int i, j;
  start( jogo , level );
  char str[10];
  for(i=0;i<MAX_SIZE;i++){
    g_object_set(g_btn_input[i], "visible", true, NULL);
    for(j=0;j<MAX_SIZE;j++){ 
      g_object_set(g_btn_display[i][j], "visible", true, NULL);
      if( jogo[i][j].fixed )
        g_object_set(g_img_btn_display[MAX_SIZE*i + j], "visible", true, NULL);
      if(jogo[i][j].value == 0)
        gtk_button_set_label(g_btn_display[i][j], " ");
      else{
        sprintf(str, "%d", jogo[i][j].value);
        gtk_button_set_label(g_btn_display[i][j], str);
      }
    }
  }
}

void on_btn_medium_clicked()
{
  level = MEDIUM;
  g_object_set(g_btn_easy,"visible",false,NULL);
  g_object_set(g_btn_medium,"visible",false,NULL);
  g_object_set(g_btn_hard,"visible",false,NULL);
  g_object_set(g_img, "visible", true, NULL);
  time(&game_start);
  penalty = 0;
  int i, j;
  start( jogo , level );
  char str[10];
  for(i=0;i<MAX_SIZE;i++){
    g_object_set(g_btn_input[i], "visible", true, NULL);
    for(j=0;j<MAX_SIZE;j++){ 
      g_object_set(g_btn_display[i][j], "visible", true, NULL);
      if( jogo[i][j].fixed )
        g_object_set(g_img_btn_display[MAX_SIZE*i + j], "visible", true, NULL);
      if(jogo[i][j].value == 0)
        gtk_button_set_label(g_btn_display[i][j], " ");
      else{
        sprintf(str, "%d", jogo[i][j].value);
        gtk_button_set_label(g_btn_display[i][j], str);
      }
    }
  }
}

void on_btn_hard_clicked()
{
  level = HARD;
  g_object_set(g_btn_easy,"visible",false,NULL);
    g_object_set(g_btn_medium,"visible",false,NULL);
    g_object_set(g_btn_hard,"visible",false,NULL);
  g_object_set(g_img, "visible", true, NULL);
  time(&game_start);
  penalty = 0;
  int i, j;
  start( jogo , level);
  char str[10];
  for(i=0;i<MAX_SIZE;i++){
    g_object_set(g_btn_input[i], "visible", true, NULL);
    for(j=0;j<MAX_SIZE;j++){ 
      g_object_set(g_btn_display[i][j], "visible", true, NULL);
      if( jogo[i][j].fixed )
        g_object_set(g_img_btn_display[MAX_SIZE*i + j], "visible", true, NULL);
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
  g_object_set(g_lbl,"visible",false,NULL);
  show_btn_input();
  for(int i=0; i<MAX_SIZE; i++){
    g_object_set(g_img_blue_input[i],"visible",false,NULL);
  }
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

void on_btn_help_clicked(){
  int i;
  penalty += 15;
  show_btn_input();
  bool solved = check( jogo );
  if( !solved ){
    for(i=0; i<MAX_SIZE; i++){
      if( !jogo[linha][i].row && !jogo[coluna][i].column && !jogo[box_number(linha, coluna)][i].box )
        g_object_set(g_img_blue_input[i],"visible",true,NULL);
    }
  }
}

void on_btn_input_clicked( GtkButton *button, gpointer data ){
  for(int i=0; i<MAX_SIZE; i++){
    g_object_set(g_img_blue_input[i],"visible",false,NULL);
  }
  if( !jogo[linha][coluna].fixed ){
    gtk_button_set_label(g_btn_display[linha][coluna], gtk_button_get_label(button));
    update( jogo, linha, coluna, atoll(gtk_button_get_label(button)));
  }
}

void on_btn_check_clicked(){
  int i;
  g_object_set(g_lbl,"visible",true,NULL);
  hide_btn_input();
  bool solved = check( jogo );
  if(solved == true){
    char name[MAX_NAME], hs[15*MAX_NAME], msg[21*MAX_NAME];
    
    strcpy(name, gtk_entry_get_text(g_entry_name));
  
    //remove possível caractere de espaço na entrada do usuario terminando ali a entrada
    for(i=0; *(name + i)!='\0'; i++ ){
        if( *(name + i)==' ')
            *(name + i) = '\0';
    }
    
    time(&game_end);
    int tempo = penalty + (int)difftime(game_end, game_start);
    get_highscore( hs, name, tempo, level );
    
    
    sprintf(msg, "PARABENS %s\nSUDOKU RESOLVIDO EM %d segundos\n\nHIGHSCORES:\n%s", name , tempo , hs);
    gtk_label_set_text(g_lbl, msg);
  }
  else{
    gtk_label_set_text(g_lbl, "SUDOKU AINDA NAO RESOLVIDO");
  }
}




// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}
