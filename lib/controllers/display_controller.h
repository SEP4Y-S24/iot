typedef enum
{
    DISPLAY_STATE_TIME,
    DISPLAY_STATE_MESSAGE
} DISPLAY_CONTROLLER_STATE;

void display_controller_init();

void display_controller_switch_state();