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
    MyLabelButton(const char *name = "Button");
    MyLabelButton(GtkButton *label_button);
    void set_label(const char *name);
    void set_signal(const char *event ,void (*signal)(void), gpointer data);
    void set_unactive();
    void set_active();
    gchar* get_label();
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
    void pack_start(MyWidget *widget,gboolean expand = TRUE, gboolean fill = FALSE, guint padding = 5);
    GtkWidget* get_widget();
private:
    GtkWidget *v_box;
};

///////////////////////////////////////////////////////MyHBox///////////////////////////////////////////////////////////
class MyHBox:public MyWidget {
public:
    MyHBox(gint spacing=10);
    void pack_start(MyWidget *widget,gboolean expand = TRUE, gboolean fill = FALSE, guint padding = 5);
    GtkWidget* get_widget();
private:
    GtkWidget *h_box;
};

///////////////////////////////////////////////////////MyDialog/////////////////////////////////////////////////////////
class MyDialog:public MyWidget {
public:
    MyDialog(char* name);
    void show();
private:
    GtkWidget *dialog;
    GtkWidget *label;
    GtkWidget *content_area;
};


#endif //!GTKLM
