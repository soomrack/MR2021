#include "gui.h"
#include "cli.h"

enum InterfaceType{
    GUI,
    CLI
};

enum InterfaceType current_interface_type = GUI;

int main(int argc, char **argv) {
    switch(current_interface_type) {
        case GUI:
            gui_main(argc, argv);
            break;
        case CLI:
            cli_main(argc, argv);
        default:
            break;
    }
    return 0;
}
