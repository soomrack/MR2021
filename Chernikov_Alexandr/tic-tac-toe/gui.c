#include <stdlib.h>
#include "game_logic.h"
#include "bot.h"
#include <gtk/gtk.h>

#define MENU_NUM_OF_ELEMS 3
#define BOT_ORDER_NUM_OF_ELEMS 3
#define INPUT_SIZE_NUM_OF_ELEMS 2
#define GAME_NUM_OF_ELEMS 3

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

typedef void (*GuiMove) (int*, int*, Field field);

GuiMove gui_player_move;
void gui_human_move(int *x, int *y, Field field){};

GuiMove gui_players_move[2] = {gui_human_move,
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
GtkWidget* grid_drawing_area;

GtkWidget *gui_menu_box;
GtkWidget *gui_bot_order_box;
GtkWidget *gui_input_size_box;
GtkWidget *gui_game_box;

// auxiliary enum for BotOrderData
enum BotOrderButton{
    BOT_ORDER_1,
    BOT_ORDER_2,
    BOT_ORDER_BACK
};

// auxiliary enum for InputSizeData
enum InputSizeButton{
    INPUT_SIZE_ENTER,
    INPUT_SIZE_BACK
};

// auxiliary enum for GameData
enum GameButton{
    GAME_DRAWING_AREA,
    GAME_RESTART,
    GAME_EXIT
};

/*
 * Data structures
 * for corresponding handlers
 */
typedef struct {
    GuiAppState state;
} MenuData;

typedef struct {
    enum BotOrderButton bot_order_button;
} BotOrderData;

typedef struct {
    enum InputSizeButton input_size_button;
    GtkWidget* widget;
} InputSizeData;

typedef struct {
    enum GameButton game_button;
    GtkWidget* widget;
} GameData;


// callback data for using in "button_press_callback"
typedef struct{
    GuiAppState prev_state;
    gpointer data;
} Callback;

typedef void (*worker) (gpointer data);
typedef GuiAppState (*handler) (void *data, GdkEventButton *event);
typedef void (*shower) (void *data);

GtkWidget* gui_menu_create(void);
GtkWidget* gui_bot_order_create(void);
GtkWidget* gui_input_size_create(void);
GtkWidget* gui_game_create(void);

void gui_menu_show(gpointer data);
void gui_bot_order_show(gpointer data);
void gui_input_size_show(gpointer data);
void gui_game_show(gpointer data);
void gui_exit_show(gpointer data);

GuiAppState gui_menu_handler(gpointer data, GdkEventButton *event);
GuiAppState gui_bot_order_handler(gpointer data, GdkEventButton *event);
GuiAppState gui_input_size_handler(gpointer data, GdkEventButton *event);
GuiAppState gui_game_handler(gpointer data, GdkEventButton *event);
GuiAppState gui_exit_handler(gpointer data, GdkEventButton *event);


shower gui_shower_table[] = {
        [GUI_MENU] = gui_menu_show,
        [GUI_BOT_ORDER] = gui_bot_order_show,
        [GUI_INPUT_SIZE] = gui_input_size_show,
        [GUI_GAME] = gui_game_show,
        [GUI_EXIT] = gui_exit_show,
};

handler gui_handler_table[] = {
        [GUI_MENU] = gui_menu_handler,
        [GUI_BOT_ORDER] = gui_bot_order_handler,
        [GUI_INPUT_SIZE] = gui_input_size_handler,
        [GUI_GAME] = gui_game_handler,
        [GUI_EXIT] = gui_exit_handler,
};

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

void draw_signs(cairo_t *cr, guint width, guint height, int field_size, CellState** cell_state_array){
    GdkRGBA color;
    gdk_rgba_parse(&color, "#000");
    gdk_cairo_set_source_rgba (cr, &color);

    guint rect_x, rect_y, rect_w, rect_h;
    for (int x = 0; x < field_size; x++){
        for (int y = 0; y < field_size; y++){
            rect_x = x * (width / field_size);
            rect_y = y * (height / field_size);
            rect_w = width / field_size;
            rect_h = height / field_size;
            switch (cell_state_array[x][y]){
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


void button_press_callback(GtkWidget *widget, GdkEventButton *event, gpointer data){

    Callback *callback_data = (Callback*) data;
    GuiAppState prev_state = callback_data->prev_state;

    GuiAppState next_state = gui_handler_table[prev_state](callback_data->data, event);
    if (prev_state != next_state){
        gui_shower_table[next_state](callback_data->data);
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
    draw_signs(cr, width, height, gui_field_size, gui_field.cell_state_array);

}


void gui_window_init(int argc, char **argv){

    // initialize object of window
    gtk_init (&argc, &argv);
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width(GTK_CONTAINER(window), 30);
    gtk_window_set_title (GTK_WINDOW (window), "Tic-tac-toe");
    g_signal_connect (G_OBJECT (window), "destroy", gtk_main_quit, NULL);

    // initialize all boxes
    gui_menu_box = gui_menu_create();
    gui_bot_order_box = gui_bot_order_create();
    gui_input_size_box = gui_input_size_create();
    gui_game_box = gui_game_create();

    // add boxes to a stack
    stack = gtk_stack_new();
    gtk_widget_set_size_request(stack, 200, 200);
    gtk_stack_add_named(GTK_STACK(stack), gui_menu_box, "Menu");
    gtk_stack_add_named(GTK_STACK(stack), gui_bot_order_box, "Bot order");
    gtk_stack_add_named(GTK_STACK(stack), gui_input_size_box, "Input size");
    gtk_stack_add_named(GTK_STACK(stack), gui_game_box, "Game");

    // set the first box visible and add the stack to the window
    gtk_stack_set_visible_child (GTK_STACK(stack), gui_menu_box);
    gtk_container_add(GTK_CONTAINER(window), stack);
}

GtkWidget* gui_menu_create(){

    // create elements of menu
    GtkWidget* button_start_human = gtk_button_new_with_label("Start human game");
    GtkWidget* button_start_bot = gtk_button_new_with_label("Start bot game");
    GtkWidget* button_exit = gtk_button_new_with_label("Exit");

    // pack elements into a box
    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(box), button_start_human, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(box), button_start_bot, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(box), button_exit, FALSE, FALSE, 10);

    // initialize data for corresponding handler
    static MenuData menu_data[MENU_NUM_OF_ELEMS];
    menu_data[0].state = GUI_INPUT_SIZE;
    menu_data[1].state = GUI_BOT_ORDER;
    menu_data[2].state = GUI_EXIT;

    // initialize data for callback
    static Callback menu_callback[MENU_NUM_OF_ELEMS];
    for (int i = 0; i < MENU_NUM_OF_ELEMS; i++){
        menu_callback[i].prev_state = GUI_MENU;
        menu_callback[i].data = &menu_data[i];
    }

    // connect signals to elements
    g_signal_connect(G_OBJECT(button_start_human),
                     "button_press_event",
                     G_CALLBACK(button_press_callback),
                     &menu_callback[0]);
    g_signal_connect(G_OBJECT(button_start_bot),
                     "button_press_event",
                     G_CALLBACK(button_press_callback),
                     &menu_callback[1]);
    g_signal_connect(G_OBJECT(button_exit),
                     "button_press_event",
                     G_CALLBACK(button_press_callback),
                     &menu_callback[2]);
    return box;
}

GtkWidget *gui_bot_order_create(){

    // create elements of bot_order box
    GtkWidget *button_bot_1 = gtk_button_new_with_label("Bot will be player 1");
    GtkWidget *button_bot_2 = gtk_button_new_with_label("Bot will be player 2");
    GtkWidget *button_back = gtk_button_new_with_label("Back to menu");

    // pack elements into a box
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_box_pack_start(GTK_BOX(box), button_bot_1, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(box), button_bot_2, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(box), button_back, FALSE, FALSE, 10);

    // initialize data for corresponding handler
    static BotOrderData bot_order_data[BOT_ORDER_NUM_OF_ELEMS];
    bot_order_data[0].bot_order_button = BOT_ORDER_1;
    bot_order_data[1].bot_order_button = BOT_ORDER_2;
    bot_order_data[2].bot_order_button = BOT_ORDER_BACK;

    // initialize data for callback
    static Callback bot_order_callback[BOT_ORDER_NUM_OF_ELEMS];
    for (int i = 0; i < MENU_NUM_OF_ELEMS; i++){
        bot_order_callback[i].prev_state = GUI_BOT_ORDER;
        bot_order_callback[i].data = &bot_order_data[i];
    }

    // connect signals to elements
    g_signal_connect(G_OBJECT(button_bot_1),
                     "button_press_event",
                     G_CALLBACK(button_press_callback),
                     &bot_order_callback[0]);
    g_signal_connect(G_OBJECT(button_bot_2),
                     "button_press_event",
                     G_CALLBACK(button_press_callback),
                     &bot_order_callback[1]);
    g_signal_connect(G_OBJECT(button_back),
                     "button_press_event",
                     G_CALLBACK(button_press_callback),
                     &bot_order_callback[2]);
    return box;
}

GtkWidget *gui_input_size_create(){

    // create elements of input_size box
    GtkWidget *label = gtk_label_new("Please, write the field size:");
    GtkWidget *entry = gtk_entry_new();
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
    gtk_entry_buffer_set_text(buffer, "3", 1);      // set default text in the entry
    GtkWidget *button_start_game = gtk_button_new_with_label("Start game");
    GtkWidget *button_back = gtk_button_new_with_label("Back to menu");

    // pack elements into a box
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(box), entry, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(box), button_start_game, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(box), button_back, FALSE, FALSE, 0);

    // initialize data for corresponding handler
    static InputSizeData input_size_data[INPUT_SIZE_NUM_OF_ELEMS];
    input_size_data[0].input_size_button = INPUT_SIZE_ENTER;
    input_size_data[0].widget = entry;
    input_size_data[1].input_size_button = INPUT_SIZE_BACK;
    input_size_data[1].widget = NULL;

    // initialize data for callback
    static Callback input_size_callback[INPUT_SIZE_NUM_OF_ELEMS];
    for (int i = 0; i < INPUT_SIZE_NUM_OF_ELEMS; i++){
        input_size_callback[i].prev_state = GUI_INPUT_SIZE;
        input_size_callback[i].data = &input_size_data[i];
    }

    // connect signals to elements
    g_signal_connect(G_OBJECT(button_start_game),
                     "button_press_event",
                     G_CALLBACK(button_press_callback),
                     &input_size_callback[0]);
    g_signal_connect(G_OBJECT(button_back),
                     "button_press_event",
                     G_CALLBACK(button_press_callback),
                     &input_size_callback[1]);
    return box;
}

GtkWidget *gui_game_create(){

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    char label_default_text[20];
    sprintf(label_default_text, "Player %d move", gui_field.current_player + 1);
    GtkWidget* label = gtk_label_new(label_default_text);

    grid_drawing_area = gtk_grid_new();
    drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, 200, 200);
    gtk_grid_attach(GTK_GRID(grid_drawing_area), drawing_area, 0, 0, 1, 1);

    gtk_widget_add_events(drawing_area, GDK_BUTTON_PRESS_MASK | GDK_EXPOSE);
    GtkWidget* button_restart = gtk_button_new_with_label("Restart");
    GtkWidget* button_exit = gtk_button_new_with_label("Exit");

    gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(box), grid_drawing_area, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), button_restart, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(box), button_exit, FALSE, FALSE, 10);

    // initialize data for corresponding handler
    static GameData game_data[GAME_NUM_OF_ELEMS];
    game_data[0].game_button = GAME_DRAWING_AREA;
    game_data[0].widget = label;
    game_data[1].game_button = GAME_RESTART;
    game_data[1].widget = label;
    game_data[2].game_button = GAME_EXIT;
    game_data[2].widget = NULL;

    // initialize data for callback
    static Callback game_callback[GAME_NUM_OF_ELEMS];
    for (int i = 0; i < GAME_NUM_OF_ELEMS; i++){
        game_callback[i].prev_state = GUI_GAME;
        game_callback[i].data = &game_data[i];
    }

    // connect signals to elements
    g_signal_connect(G_OBJECT(drawing_area),
                     "button_press_event",
                     G_CALLBACK(button_press_callback),
                     &game_callback[0]);
    g_signal_connect(G_OBJECT(drawing_area),
                     (gpointer)"draw",
                     G_CALLBACK(draw_callback),
                     &game_callback[0]);
    g_signal_connect(G_OBJECT(button_restart),
                     (gpointer)"button_press_event",
                     G_CALLBACK(button_press_callback),
                     &game_callback[1]);
    g_signal_connect(G_OBJECT(button_exit),
                     (gpointer)"button_press_event",
                     G_CALLBACK(button_press_callback),
                     &game_callback[2]);

    return box;
}

void gui_menu_show(gpointer data){
    gtk_stack_set_visible_child (GTK_STACK(stack), gui_menu_box);
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

GuiAppState gui_menu_handler(gpointer data, GdkEventButton *event){
    GuiAppState next_state = ((MenuData*) data)->state;
    return next_state;
}

GuiAppState gui_bot_order_handler(gpointer data, GdkEventButton *event){
    enum BotOrderButton button = ((BotOrderData*) data)->bot_order_button;
    switch (button) {
        case BOT_ORDER_1:
            gui_players_move[0] = bot_move;
            gui_players_move[1] = gui_human_move;
            break;
        case BOT_ORDER_2:
            gui_players_move[0] = gui_human_move;
            gui_players_move[1] = bot_move;
            break;
        case BOT_ORDER_BACK:
            return GUI_MENU;
        default:
            // strange case for error detection
            gui_players_move[0] = bot_move;
            gui_players_move[1] = bot_move;
    }
    return GUI_INPUT_SIZE;
}
GuiAppState gui_input_size_handler(gpointer data, GdkEventButton *event){
    InputSizeData* input_size_data = (InputSizeData*) data;

    // which button has pressed
    switch (input_size_data->input_size_button){
        case INPUT_SIZE_BACK:
            return GUI_MENU;
        case INPUT_SIZE_ENTER:
            break;
    }

    // get data from the entry
    GtkWidget* entry = input_size_data->widget;
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
    char *text = (char*) gtk_entry_buffer_get_text(buffer);
    gui_field_size = atoi(text);

    // consider that field size can not be less than 3
    if (gui_field_size < 3){
        return GUI_INPUT_SIZE;
    }
    init_field(&gui_field, gui_field_size);
    return GUI_GAME;
}
GuiAppState gui_game_handler(gpointer data, GdkEventButton *event){
    GameData* game_data = (GameData*) data;
    int x, y;
    int width = gtk_widget_get_allocated_width (
            gtk_grid_get_child_at(GTK_GRID(grid_drawing_area),
                                  0,
                                  0));
    int height = gtk_widget_get_allocated_height (
            gtk_grid_get_child_at(GTK_GRID(grid_drawing_area),
                                  0,
                                  0));

    switch(game_data->game_button){
        case GAME_RESTART:
            clear_field(&gui_field);
            break;

        case GAME_EXIT:
            return GUI_MENU;

        case GAME_DRAWING_AREA:
            // if drawing area was clicked then do moves
            if (gui_field.field_state == GAME_IS_IN_PROCESS){
                define_coords(&x, &y, (int)event->x, (int)event->y, width, height);
                gui_update_result = update_field(&gui_field, x, y);
            }

            while ((gui_players_move[gui_field.current_player] == bot_move) &&
                   (gui_field.field_state == GAME_IS_IN_PROCESS)) {
                bot_move(&x, &y, gui_field);
                gui_update_result = update_field(&gui_field, x, y);
            }
            break;
    }

    // drawing
    GdkWindow *game_window = gtk_widget_get_window(
            gtk_grid_get_child_at(GTK_GRID(grid_drawing_area),
                                  0,
                                  0));
    cairo_region_t *cairoRegion = cairo_region_create();
    GdkDrawingContext *drawingContext = gdk_window_begin_draw_frame(game_window, cairoRegion);
    {
        cairo_t *cr = gdk_drawing_context_get_cairo_context(drawingContext);
        {
            draw_white_rect(cr, width, height);
            draw_field(cr, width, height, gui_field_size);
            draw_signs(cr, width, height, gui_field_size, gui_field.cell_state_array);
        }
        gdk_window_end_draw_frame(game_window, drawingContext);
    }
    cairo_region_destroy(cairoRegion);

    // update label
    char label_new_text[30];
    switch (gui_field.field_state){
        case GAME_IS_IN_PROCESS:
            sprintf(label_new_text, "Player %d move", gui_field.current_player + 1);
            break;
        case WIN:
            sprintf(label_new_text, "Player %d win", gui_field.current_player + 1);
            break;
        case TIE:
            sprintf(label_new_text, "Tie");
    }
    gtk_label_set_label(GTK_LABEL(game_data->widget), label_new_text);

    return GUI_GAME;
}

GuiAppState gui_exit_handler(gpointer data, GdkEventButton *event){
    return GUI_EXIT;
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
