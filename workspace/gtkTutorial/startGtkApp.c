#include<gtk/gtk.h>

static void activate(GtkApplication*app,gpointer user_data){
	//gtk code comes here

	GtkWidget *window;

	window=gtk_application_window_new(app);

	gtk_widget_show_all(window);

}

int main(int argc,char ** argv){
	GtkApplication *app;
	int ret;
	app=gtk_application_new("in.aducators",G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app,"activate",G_CALLBACK(activate),NULL);        //callback which happen on a particular action
	ret=g_application_run(G_CALLBACK(app),argc,argv);
	
	g_object_unref(app);
	
	return 0;
}
// gcc `pkg-config --cflags gtk+-3.0` -o startGtkApp startGtkApp.c `pkg-config --libs gtk+-3.0`
