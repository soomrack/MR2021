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

typedef void (*GuiMove) (int*, int*, void* data);

void gui_window_init(int argc, char** argv);
void gui_show_window();

GtkWidget* gui_menu_create(void);
GtkWidget* gui_bot_order_create(void);
GtkWidget* gui_input_size_create(void);
GtkWidget* gui_game_create(void);

void gui_menu_handler(GtkWidget *widget, GdkEventButton *event, gpointer data);
void gui_bot_order_handler(GtkWidget *widget, GdkEventButton *event, gpointer data);
void gui_input_size_handler(GtkWidget *widget, GdkEventButton *event, gpointer data);
void gui_game_handler(GtkWidget *widget, GdkEventButton *event, gpointer data);

void draw_handler(GtkWidget *widget, cairo_t *cr, gpointer data);

void gui_human_move(int *x, int *y, void* data);

void draw_white_rect(cairo_t *cr, guint width, guint height);
void draw_field(cairo_t *cr, guint width, guint height, int field_size);
void draw_cross(cairo_t *cr, guint x, guint y, guint width, guint height);
void draw_zero(cairo_t *cr, guint x, guint y, guint width, guint height);
void draw_signs(cairo_t *cr, guint width, guint height, int field_size, CellState** cell_state_array);

int gui_field_size = 0;
Field gui_field;

GuiMove gui_players_move[2] = {gui_human_move,
                               gui_human_move};

GtkWidget* window;
GtkWidget* stack;
GtkWidget* drawing_area;
GtkWidget* grid_drawing_area;

GtkWidget* gui_menu_box;
GtkWidget* gui_bot_order_box;
GtkWidget* gui_input_size_box;
GtkWidget* gui_game_box;


int gui_main (int argc, char **argv) {
    gui_window_init(argc, argv);
    gui_show_window();
    return 0;
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

void gui_show_window(){
    gtk_widget_show_all(window);
    gtk_main();
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

    // connect signals to elements
    g_signal_connect(G_OBJECT(button_start_human),
                     "button_press_event",
                     G_CALLBACK(gui_menu_handler),
                     &menu_data[0]);
    g_signal_connect(G_OBJECT(button_start_bot),
                     "button_press_event",
                     G_CALLBACK(gui_menu_handler),
                     &menu_data[1]);
    g_signal_connect(G_OBJECT(button_exit),
                     "button_press_event",
                     G_CALLBACK(gui_menu_handler),
                     &menu_data[2]);
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

    // connect signals to elements
    g_signal_connect(G_OBJECT(button_bot_1),
                     "button_press_event",
                     G_CALLBACK(gui_bot_order_handler),
                     &bot_order_data[0]);
    g_signal_connect(G_OBJECT(button_bot_2),
                     "button_press_event",
                     G_CALLBACK(gui_bot_order_handler),
                     &bot_order_data[1]);
    g_signal_connect(G_OBJECT(button_back),
                     "button_press_event",
                     G_CALLBACK(gui_bot_order_handler),
                     &bot_order_data[2]);
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

    // connect signals to elements
    g_signal_connect(G_OBJECT(button_start_game),
                     "button_press_event",
                     G_CALLBACK(gui_input_size_handler),
                     &input_size_data[0]);
    g_signal_connect(G_OBJECT(button_back),
                     "button_press_event",
                     G_CALLBACK(gui_input_size_handler),
                     &input_size_data[1]);
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

    // connect signals to elements
    g_signal_connect(G_OBJECT(drawing_area),
                     "button_press_event",
                     G_CALLBACK(gui_game_handler),
                     &game_data[0]);
    g_signal_connect(G_OBJECT(drawing_area),
                     (gpointer)"draw",
                     G_CALLBACK(draw_handler),
                     &game_data[0]);
    g_signal_connect(G_OBJECT(button_restart),
                     (gpointer)"button_press_event",
                     G_CALLBACK(gui_game_handler),
                     &game_data[1]);
    g_signal_connect(G_OBJECT(button_exit),
                     (gpointer)"button_press_event",
                     G_CALLBACK(gui_game_handler),
                     &game_data[2]);

    return box;
}


void draw_handler (GtkWidget *widget, cairo_t *cr, gpointer data){
    guint width, height;
    GdkRGBA color;
    GtkStyleContext *context;

    context = gtk_widget_get_style_context (widget);

    width = gtk_widget_get_allocated_width (widget);
    height = gtk_widget_get_allocated_height (widget);

    gtk_render_background(context, cr, 0, 0, width, height);

    int x, y;
    while ((gui_players_move[gui_field.current_player] == bot_move) &&
    (gui_field.field_state == GAME_IS_IN_PROCESS)){
        bot_move(&x, &y, &gui_field);
        update_field(&gui_field, x, y);
    }

    draw_white_rect(cr, width, height);
    draw_field(cr, width, height, gui_field_size);
    draw_signs(cr, width, height, gui_field_size, gui_field.cell_state_array);
}


void gui_menu_handler(GtkWidget *widget, GdkEventButton *event, gpointer data){
    GuiAppState next_state = ((MenuData*) data)->state;

    switch (next_state){
        case GUI_INPUT_SIZE:
            gui_players_move[0] = gui_human_move;
            gui_players_move[1] = gui_human_move;
            gtk_stack_set_visible_child(GTK_STACK(stack), gui_input_size_box);
            break;
        case GUI_BOT_ORDER:
            gtk_stack_set_visible_child(GTK_STACK(stack), gui_bot_order_box);
            break;
        case GUI_EXIT:
            gtk_main_quit();
            break;
        default:
            printf("Unexpected value has received");
            break;
    }
}

void gui_bot_order_handler(GtkWidget *widget, GdkEventButton *event, gpointer data){
    enum BotOrderButton button = ((BotOrderData*) data)->bot_order_button;
    switch (button) {
        case BOT_ORDER_1:
            gui_players_move[0] = bot_move;
            gui_players_move[1] = gui_human_move;
            gtk_stack_set_visible_child(GTK_STACK(stack), gui_input_size_box);
            break;
        case BOT_ORDER_2:
            gui_players_move[0] = gui_human_move;
            gui_players_move[1] = bot_move;
            gtk_stack_set_visible_child(GTK_STACK(stack), gui_input_size_box);
            break;
        case BOT_ORDER_BACK:
            gtk_stack_set_visible_child(GTK_STACK(stack), gui_menu_box);
            break;
        default:
            printf("Unexpected value has received");
            break;
    }
}

void gui_input_size_handler(GtkWidget *widget, GdkEventButton *event, gpointer data){
    InputSizeData* input_size_data = (InputSizeData*) data;

    // which button has pressed
    switch (input_size_data->input_size_button){
        case INPUT_SIZE_BACK:
            gtk_stack_set_visible_child(GTK_STACK(stack), gui_menu_box);
            return;
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
        gtk_stack_set_visible_child(GTK_STACK(stack), gui_input_size_box);
        return;
    }

    init_field(&gui_field, gui_field_size);
    gtk_stack_set_visible_child(GTK_STACK(stack), gui_game_box);
}

void gui_game_handler(GtkWidget *widget, GdkEventButton *event, gpointer data){
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
            while (gui_players_move[gui_field.current_player] == bot_move){
                bot_move(&x, &y, &gui_field);
                update_field(&gui_field, x, y);
            }
            break;

        case GAME_EXIT:
            gtk_stack_set_visible_child(GTK_STACK(stack), gui_menu_box);
            return;

        case GAME_DRAWING_AREA:
            // if drawing area was clicked then do moves
            if (gui_field.field_state == GAME_IS_IN_PROCESS){
                gui_human_move(&x, &y, event);
                update_field(&gui_field, x, y);
            }

            while ((gui_players_move[gui_field.current_player] == bot_move) &&
                   (gui_field.field_state == GAME_IS_IN_PROCESS)){
                bot_move(&x, &y, &gui_field);
                update_field(&gui_field, x, y);
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
}

void gui_human_move(int *x, int *y, void* data){
    GdkEventButton* event = (GdkEventButton*) data;
    int clicked_x = (int)event->x;
    int clicked_y = (int)event->y;

    int width = gtk_widget_get_allocated_width(gtk_grid_get_child_at(GTK_GRID(grid_drawing_area),
                                                                      0,
                                                                      0));
    int height = gtk_widget_get_allocated_height(gtk_grid_get_child_at(GTK_GRID(grid_drawing_area),
                                                                        0,
                                                                        0));
    *x = clicked_x / (width / gui_field_size);
    *y = clicked_y / (height / gui_field_size);
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
