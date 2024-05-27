#include "utils.h"
#include <string.h>

int utils_find_char_index_in_string(char *string, char c)
{
    char *e = strchr(string, c);
    return (int)(e - string);
}

int utils_find_nth_char_index_in_string(char *string, char c, int n)
{
    int count = 0;
    for (int i = 0; i < strlen(string); i++)
    {
        if (string[i] == c)
        {
            count++;
            if (count == n)
            {
                return i;
            }
        }
    }
    return -1;
}

int utils_count_char_in_string(char *string, char c)
{
    int count = 0;
    for (int i = 0; i < strlen(string); i++)
    {
        if (string[i] == c)
        {
            count++;
        }
    }
    return count;
}