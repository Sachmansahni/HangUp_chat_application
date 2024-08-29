#include<gtk/gtk.h>
int main(int argc,char**argv){
gtk_init(&argc,&argv);

GtkWidget *window;
GtkWidget *box;

GtkWidget *button1;
GtkWidget *button2;

window=gtk_window_new(GTK_WINDOW_TOPLEVEL);

box=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);

button1=gtk_button_new_with_label("button1");
gtk_widget_set_size_request(GTK_WIDGET(button1),300,200);
button2=gtk_button_new_with_label("button2");

gtk_container_add(GTK_CONTAINER(window),box);

gtk_box_pack_end(GTK_BOX(box),button1,FALSE,FALSE,50);     //EXPAND,FILL,PADDING
gtk_box_pack_start(GTK_BOX(box),button2,FALSE,TRUE,50);

int isHomo=gtk_box_get_homogeneous(GTK_BOX(box));
printf("is Homogeneous????  %d\n",isHomo);

gtk_box_set_homogeneous(GTK_BOX(box),TRUE);

isHomo=gtk_box_get_homogeneous(GTK_BOX(box));
printf("is Homogeneous AFTER SETTER CALL????  %d\n",isHomo);

g_signal_connect (window,"destroy",G_CALLBACK(gtk_main_quit),NULL);    // the fourth parameter is an argument and since we are not passing any argument here, we have to pass NULL
gtk_widget_show_all(window);

gtk_main();
return 0;
}

