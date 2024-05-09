#include <external_screen.h>

static char* message = "No message received :(";

void message_display_message(){
    external_screen_string(message);
}

void message_set_message(char *new_message){
    message = new_message;
}