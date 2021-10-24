#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "game_logic.h"
#include "bot.h"

typedef enum{
    GUI_MENU,
    GUI_BOT_ORDER,
    GUI_INPUT_SIZE,
    GUI_GAME,
    GUI_EXIT
} GuiAppState;

int gui_field_size = 0;
Field gui_field;
int gui_update_result = 0;

typedef void (*Move) (int*, int*, Field field);

Move player_move;

void gui_human_move(int *x, int *y, Field field){};

Move gui_players_move[2] = {gui_human_move,
                            gui_human_move};

void define_coords(int *x, int *y,
                   int clicked_x, int clicked_y,
                   int width, int height){
    *x = clicked_x / (width / gui_field_size);
    *y = clicked_y / (height / gui_field_size);
}

GtkWidget *window;
GtkWidget *stack;
GtkWidget *drawing_area;

GtkWidget *gui_menu_box;
GtkWidget *gui_bot_order_box;
GtkWidget *gui_input_size_box;
GtkWidget *gui_game_box;

typedef struct{
    GuiAppState prev_state;
    GuiAppState next_state;
    gpointer data;
} Callback;

typedef void (*worker) (gpointer data);
typedef void (*handler) (void *data, GdkEventButton *event);
typedef void (*shower) (void *data);

GtkWidget *gui_menu_create(void);
GtkWidget *gui_bot_order_create(void);
GtkWidget *gui_input_size_create(void);
GtkWidget *gui_game_create(void);

void gui_menu_show(gpointer data);
void gui_bot_order_show(gpointer data);
void gui_input_size_show(gpointer data);
void gui_game_show(gpointer data);
void gui_exit_show(gpointer data);

void gui_menu_handler(gpointer data, GdkEventButton *event);
void gui_bot_order_handler(gpointer data, GdkEventButton *event);
void gui_input_size_handler(gpointer data, GdkEventButton *event);
void gui_game_handler(gpointer data, GdkEventButton *event);
void gui_exit_handler(gpointer data, GdkEventButton *event);

void gui_init_boxes();

shower gui_shower_table[5] = {
        [GUI_MENU] = gui_menu_show,
        [GUI_BOT_ORDER] = gui_bot_order_show,
        [GUI_INPUT_SIZE] = gui_input_size_show,
        [GUI_GAME] = gui_game_show,
        [GUI_EXIT] = gui_exit_show,
};

handler gui_handler_table[5] = {
        [GUI_MENU] = gui_menu_handler,
        [GUI_BOT_ORDER] = gui_bot_order_handler,
        [GUI_INPUT_SIZE] = gui_input_size_handler,
        [GUI_GAME] = gui_game_handler,
        [GUI_EXIT] = gui_exit_handler,
};


void button_press_callback(GtkWidget *widget, GdkEventButton *event, gpointer data){

    Callback *callback_data = (Callback*) data;
    GuiAppState prev_state = callback_data->prev_state;
    GuiAppState next_state = callback_data->next_state;

    gui_handler_table[prev_state](callback_data->data, event);
    if (prev_state != next_state){
        prev_state = next_state;
        gui_shower_table[next_state](callback_data->data);
    }
}

void draw_white_rect(cairo_t *cr, guint width, guint height){
    GdkRGBA color;
    gdk_rgba_parse(&color, "#fff");
    gdk_cairo_set_source_rgba (cr, &color);
    cairo_rectangle(cr, 0, 0, width, height);
    cairo_fill(cr);
}

void draw_field(cairo_t *cr, guint width, guint height, int field_size){
    GdkRGBA color;
    gdk_rgba_parse(&color, "#000");
    gdk_cairo_set_source_rgba (cr, &color);

    for (int i = 1; i < field_size; i++){
        cairo_move_to(cr, (double) width / field_size * i, 0);
        cairo_line_to(cr, (double) width / field_size * i, height);
    }

    for (int i = 1; i < field_size; i++){
        cairo_move_to(cr, 0, (double) height / field_size * i);
        cairo_line_to(cr, width, (double) height / field_size * i);
    }
    cairo_stroke(cr);
}
void draw_cross(cairo_t *cr, guint x, guint y, guint width, guint height){
    cairo_move_to(cr, x, y);
    cairo_line_to(cr, x + width, y + height);
    cairo_stroke (cr);

    cairo_move_to(cr, x + width, y);
    cairo_line_to(cr, x, y + height);
    cairo_stroke (cr);
}

void draw_zero(cairo_t *cr, guint x, guint y, guint width, guint height){
    cairo_arc (cr,
               x + width / 2.0, y + height / 2.0,
               MIN (width, height) / 2.0,
               0, 2 * G_PI);
    cairo_stroke (cr);
}

void draw_signs(cairo_t *cr, guint width, guint height, int field_size){
    GdkRGBA color;
    gdk_rgba_parse(&color, "#000");
    gdk_cairo_set_source_rgba (cr, &color);

    guint rect_x, rect_y, rect_w, rect_h;
    for (int x = 0; x < gui_field_size; x++){
        for (int y = 0; y < gui_field_size; y++){
            rect_x = x * (width / gui_field_size);
            rect_y = y * (height / gui_field_size);
            rect_w = width / gui_field_size;
            rect_h = width / gui_field_size;
            switch (gui_field.cell_state_array[x][y]){
                case ZERO:
                    draw_zero(cr, rect_x, rect_y, rect_w, rect_h);
                    break;
                case CROSS:
                    draw_cross(cr, rect_x, rect_y, rect_w, rect_h);
                    break;
                default:
                    break;
            }
        }
    }
}

void draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data){
    // g_print("Draw\n");

    guint width, height;
    GdkRGBA color;
    GtkStyleContext *context;

    context = gtk_widget_get_style_context (widget);

    width = gtk_widget_get_allocated_width (widget);
    height = gtk_widget_get_allocated_height (widget);

    gtk_render_background(context, cr, 0, 0, width, height);

    int x, y;
    while ((gui_players_move[gui_field.current_player] == bot_move) && (gui_field.field_state == GAME_IS_IN_PROCESS)){
        bot_move(&x, &y, gui_field);
        gui_update_result = update_field(&gui_field, x, y);
    }

    draw_white_rect(cr, width, height);
    draw_field(cr, width, height, gui_field_size);
    draw_signs(cr, width, height, gui_field_size);

    if (gui_field.field_state != GAME_IS_IN_PROCESS){
        clear_field(&gui_field);
    }
}


void gui_window_init(int argc, char **argv){
    gtk_init (&argc, &argv);
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_title (GTK_WINDOW (window), "Tic-tac-toe");
    g_signal_connect (G_OBJECT (window), "destroy", gtk_main_quit, NULL);

    gui_init_boxes();

    stack = gtk_stack_new();
    gtk_widget_set_size_request(stack, 200, 200);
    gtk_stack_add_named(GTK_STACK(stack), gui_menu_box, "Menu");
    gtk_stack_add_named(GTK_STACK(stack), gui_bot_order_box, "Bot order");
    gtk_stack_add_named(GTK_STACK(stack), gui_input_size_box, "Input size");
    gtk_stack_add_named(GTK_STACK(stack), gui_game_box, "Game");

    gtk_stack_set_visible_child (GTK_STACK(stack), gui_menu_box);
    gtk_container_add(GTK_CONTAINER(window), stack);
}

GtkWidget *gui_menu_create(){

    GtkWidget *button_start_human = gtk_button_new_with_label("Start human game");
    GtkWidget *button_start_bot = gtk_button_new_with_label("Start bot game");
    GtkWidget *button_exit = gtk_button_new_with_label("Exit");

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(box), button_start_human, TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(box), button_start_bot, TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(box), button_exit, TRUE, TRUE, 10);

    static Callback menu_data[3] = {
            {GUI_MENU, GUI_INPUT_SIZE, NULL},
            {GUI_MENU, GUI_BOT_ORDER, NULL},
            {GUI_MENU, GUI_EXIT, NULL},
    };
    g_signal_connect(G_OBJECT(button_start_human),
                     "button_press_event",
                     G_CALLBACK(button_press_callback),
                     &menu_data[0]);
    g_signal_connect(G_OBJECT(button_start_bot),
                     "button_press_event",
                     G_CALLBACK(button_press_callback),
                     &menu_data[1]);
    g_signal_connect(G_OBJECT(button_exit),
                     "button_press_event",
                     G_CALLBACK(button_press_callback),
                     &menu_data[2]);
    return box;
}

GtkWidget *gui_bot_order_create(){

    GtkWidget *button_bot_1 = gtk_button_new_with_label("Bot will be player 1");
    GtkWidget *button_bot_2 = gtk_button_new_with_label("Bot will be player 2");

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(box), button_bot_1, TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(box), button_bot_2, TRUE, TRUE, 10);

    static int bot_order_num[2] = {1, 2};

    static Callback bot_order_data[2] = {
            {GUI_BOT_ORDER, GUI_INPUT_SIZE, &bot_order_num[0]},
            {GUI_BOT_ORDER, GUI_INPUT_SIZE, &bot_order_num[1]},
    };
    g_signal_connect(G_OBJECT(button_bot_1),
                     "button_press_event",
                     G_CALLBACK(button_press_callback),
                     &bot_order_data[0]);
    g_signal_connect(G_OBJECT(button_bot_2),
                     "button_press_event",
                     G_CALLBACK(button_press_callback),
                     &bot_order_data[1]);
    return box;
}

GtkWidget *gui_input_size_create(){

    GtkWidget *label = gtk_label_new("Please, write the field size:");
    GtkWidget *entry = gtk_entry_new();
    GtkWidget *button_start_game = gtk_button_new_with_label("Start game");

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(box), entry, TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(box), button_start_game, TRUE, TRUE, 10);

    Callback *input_size_data = calloc(1, sizeof(Callback));
    input_size_data->prev_state = GUI_INPUT_SIZE;
    input_size_data->next_state = GUI_GAME;
    input_size_data->data = entry;

    g_signal_connect(G_OBJECT(button_start_game),
                     "button_press_event",
                     G_CALLBACK(button_press_callback),
                     &input_size_data[0]);
    return box;
}

GtkWidget *gui_game_create(){

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    drawing_area = gtk_drawing_area_new ();
    // gtk_widget_set_size_request (drawing_area, 200, 200);
    gtk_widget_add_events(drawing_area, GDK_BUTTON_PRESS_MASK | GDK_EXPOSE);

    Callback *game_data = calloc(2, sizeof(Callback));
    game_data[0].prev_state = GUI_GAME;
    game_data[0].next_state = GUI_GAME;
    game_data[0].data = NULL;

    game_data[1].prev_state = GUI_GAME;
    game_data[1].next_state = GUI_GAME;
    game_data[1].data = NULL;

    g_signal_connect(G_OBJECT(drawing_area),
                     "button_press_event",
                     G_CALLBACK(button_press_callback),
                     &game_data[0]);
    g_signal_connect(G_OBJECT(drawing_area),
                     (gpointer)"draw",
                     G_CALLBACK(draw_callback),
                     &game_data[1]);
    gtk_box_pack_start(GTK_BOX(box), drawing_area, TRUE, TRUE, 0);
    return box;
}

void gui_init_boxes(){
    gui_menu_box = gui_menu_create();
    gui_bot_order_box = gui_bot_order_create();
    gui_input_size_box = gui_input_size_create();
    gui_game_box = gui_game_create();
}

void gui_menu_show(gpointer data){
    gtk_stack_set_visible_child (GTK_STACK(stack), gui_bot_order_box);
}

void gui_bot_order_show(gpointer data){
    gtk_stack_set_visible_child (GTK_STACK(stack), gui_bot_order_box);
}

void gui_input_size_show(gpointer data){
    gtk_stack_set_visible_child(GTK_STACK(stack), gui_input_size_box);
}

void gui_game_show(gpointer data){
    gtk_stack_set_visible_child(GTK_STACK(stack), gui_game_box);
}

void gui_exit_show(gpointer data){
    gtk_main_quit();
}


void gui_menu_handler(gpointer data, GdkEventButton *event){
    ;
}
void gui_bot_order_handler(gpointer data, GdkEventButton *event){
    int *number = (int *) data;
    switch (*number) {
        case 1:
            gui_players_move[0] = bot_move;
            gui_players_move[1] = gui_human_move;
            break;
        case 2:
            gui_players_move[0] = gui_human_move;
            gui_players_move[1] = bot_move;
            break;
        default:
            gui_players_move[0] = bot_move;
            gui_players_move[1] = bot_move;
    }
}
void gui_input_size_handler(gpointer data, GdkEventButton *event){
    GtkWidget *entry = (GtkWidget*) data;
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
    char *text = (char*) gtk_entry_buffer_get_text(buffer);
    gui_field_size = atoi(text);
    init_field(&gui_field, gui_field_size);
}
void gui_game_handler(gpointer data, GdkEventButton *event){
    int x, y;
    int width = gtk_widget_get_allocated_width (gui_game_box);
    int height = gtk_widget_get_allocated_height (gui_game_box);

    if (gui_field.field_state == GAME_IS_IN_PROCESS){
        define_coords(&x, &y, (int)event->x, (int)event->y, width, height);
        gui_update_result = update_field(&gui_field, x, y);
    }
    else{
        clear_field(&gui_field);
    }

    while ((gui_players_move[gui_field.current_player] == bot_move) &&
           (gui_field.field_state == GAME_IS_IN_PROCESS)) {
        bot_move(&x, &y, gui_field);
        gui_update_result = update_field(&gui_field, x, y);
    }

    GdkWindow *game_window = gtk_widget_get_window(gui_game_box);
    cairo_region_t *cairoRegion = cairo_region_create();
    GdkDrawingContext *drawingContext = gdk_window_begin_draw_frame(game_window, cairoRegion);
    {
        cairo_t *cr = gdk_drawing_context_get_cairo_context(drawingContext);
        {
            draw_white_rect(cr, width, height);
            draw_field(cr, width, height, gui_field_size);
            draw_signs(cr, width, height, gui_field_size);
        }
        gdk_window_end_draw_frame(game_window, drawingContext);
    }
    cairo_region_destroy(cairoRegion);
}

void gui_exit_handler(gpointer data, GdkEventButton *event){
    ;
}


void gui_show_window(){
    gtk_widget_show_all(window);
    gtk_main();
}

int gui_main (int argc, char **argv) {

    gui_window_init(argc, argv);
    gui_show_window();

    return 0;
}