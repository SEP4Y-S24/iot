#pragma once

typedef struct schedule_task
{
    void (*task)(void);
    int interval;
} schedule_task_t;

void scheduler_init();
void scheduler_add_task(void (*task)(void), int interval);
void scheduler_run_all_tasks();