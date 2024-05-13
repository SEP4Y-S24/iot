#include <external_screen.h>

static char* message = "No message received :(";

void message_set_message(char *new_message){
    message = new_message;
}

char *message_get_message(){
    return message;
}