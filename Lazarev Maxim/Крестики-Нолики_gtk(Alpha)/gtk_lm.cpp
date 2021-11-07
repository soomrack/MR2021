#include "gtk_lm.h"
#include <iostream>


GtkWidget *MyWidget::get_widget() {
}

////////////////////////////////////////////////MyWindow////////////////////////////////////////////////////////////////

MyWindow::MyWindow() {
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(window),"destroy", G_CALLBACK(gtk_main_quit), NULL);
}

MyWindow::MyWindow(char *name):MyWindow() {
    gtk_window_set_title(GTK_WINDOW(window),name);
}

void MyWindow::add_child(MyWidget *child) {
    gtk_container_add(GTK_CONTAINER(window), child->get_widget());
}

void MyWindow::name_window(char *name) {
    gtk_window_set_title(GTK_WINDOW(window),name);
}

void MyWindow::set_border_width(int width) {
    gtk_container_set_border_width(GTK_CONTAINER(window),width);
}

void MyWindow::show_window() {
    gtk_widget_show_all (window);
}

GtkWidget *MyWindow::get_widget() {
    return window;
}


//////////////////////////////////////////////MyLabelButton////////////////////////////////////////////////////////////



MyLabelButton::MyLabelButton(char *name) {
    label_button = gtk_button_new_with_label(name);
}

void MyLabelButton::set_signal(char *event ,void (*signal)(void), gpointer data) {
    g_signal_connect(GTK_BUTTON(label_button),event, signal, data);
}

GtkWidget* MyLabelButton::get_widget() {
    return label_button;
}

/////////////////////////////////////////////////MyStack////////////////////////////////////////////////////////////////

MyStack::MyStack() {
    stack = gtk_stack_new();
    gtk_stack_set_transition_type (GTK_STACK (stack), GTK_STACK_TRANSITION_TYPE_SLIDE_UP);
}

void MyStack::add_child(MyWidget *child, const gchar* name) {
    gtk_stack_add_named(GTK_STACK(stack), child->get_widget(), name);
}

void MyStack::set_child (const gchar *name){
    gtk_stack_set_visible_child_name(GTK_STACK(stack),name);
}

GtkWidget* MyStack::get_widget(){
    return stack;
}
/////////////////////////////////////////////////MyVBox/////////////////////////////////////////////////////////////////

MyVBox::MyVBox(gint spacing) {
    v_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, spacing);
}

void MyVBox::pack_start(MyWidget *widget,gboolean expand, gboolean fill, guint padding){
    gtk_box_pack_start(GTK_BOX(v_box),widget->get_widget(), expand, fill, padding);
}

GtkWidget *MyVBox::get_widget() {
    return v_box;
}

/////////////////////////////////////////////////MyHBox/////////////////////////////////////////////////////////////////

MyHBox::MyHBox(gint spacing) {
    h_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, spacing);
}

void MyHBox::pack_start(MyWidget *widget,gboolean expand, gboolean fill, guint padding){
    gtk_box_pack_start(GTK_BOX(h_box),widget->get_widget(), expand, fill, padding);
}

GtkWidget *MyHBox::get_widget() {
    return h_box;
}
