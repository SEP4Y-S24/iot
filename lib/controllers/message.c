#include <external_screen.h>
#include <string.h>
#include "display_controller.h"
static char message[90];

void message_set_message(char *new_message){
    strcpy(message, new_message);
    display_controller_reset_offset();
}

char *message_get_message(){
    return message;
}