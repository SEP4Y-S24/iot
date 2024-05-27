#include <external_screen.h>
#include <string.h>
static char message[90];

void message_set_message(char *new_message){
    strcpy(message, new_message);
}

char *message_get_message(){
    return message;
}