#include "logger.h"
#include "../drivers/pc_comm.h"
#include <string.h>

static void log_callback(char c) {}

static void format_message(char *message, char *buffer)
{
    strcpy(buffer, message);
    strcat(buffer, "\n");
}

void log_info(char *message)
{
    int lenght = strlen(message) + 2;
    char buffer[lenght];
    format_message(message, buffer);
    pc_comm_send_string_blocking(buffer);
}

void log_debug(char *message)
{
#ifdef DEBUG
    log_info(message);
#endif
}

void log_init()
{
    pc_comm_init(9600, log_callback);
}
