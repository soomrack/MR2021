#ifndef GTKLM_H
#define GTKLM_H
#include <gtk/gtk.h>
#define CLICKED ("clicked")

class MyWidget {
public:
    virtual GtkWidget* get_widget();
private:
};

////////////////////////////////////MyWindow///////////////////////////////////////////////////////////////////////////

class MyWindow:public MyWidget{
public:
    MyWindow();
    MyWindow(char *name);
    void add_child (MyWidget *child);
    void name_window(char *name);
    void set_border_width(int width);
    void show_window();
    GtkWidget* get_widget();
private:
    GtkWidget *window;
};
///////////////////////////////////////MyLabelButton////////////////////////////////////////////////////////////////////

class MyLabelButton:public MyWidget {
public:
    MyLabelButton(char *name = "Button");
    void set_signal(char *event ,void (*signal)(void), gpointer data);
    GtkWidget* get_widget();

private:
    GtkWidget *label_button;
};

//////////////////////////////////////////MyStack///////////////////////////////////////////////////////////////////////
class MyStack:public MyWidget {
public:
    MyStack();
    void add_child (MyWidget *child, const gchar* name);
    void set_child (const gchar *name);

    GtkWidget* get_widget();
private:
    GtkWidget *stack;
};


///////////////////////////////////////////////////////MyVBox///////////////////////////////////////////////////////////
class MyVBox:public MyWidget {
public:
    MyVBox(gint spacing=10);
    void pack_start(MyWidget *widget,gboolean expand, gboolean fill, guint padding);
    GtkWidget* get_widget();
private:
    GtkWidget *v_box;
};

///////////////////////////////////////////////////////MyHBox///////////////////////////////////////////////////////////
class MyHBox:public MyWidget {
public:
    MyHBox(gint spacing=10);
    void pack_start(MyWidget *widget,gboolean expand, gboolean fill, guint padding);
    GtkWidget* get_widget();
private:
    GtkWidget *h_box;
};

#endif //!GTKLM
