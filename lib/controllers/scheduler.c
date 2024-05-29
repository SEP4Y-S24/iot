#include "scheduler.h"
#include "../utils/logger.h"
#include "../drivers/periodic_task.h"
#include <stdlib.h>

static uint64_t last_run_time;
static schedule_task_t schedule_task_array[100];
static int task_index;
void scheduler_run_all_tasks()
{
    last_run_time++;

    for (int i = 0; i < 100; i++)
    {
        if (schedule_task_array[i].task != NULL && last_run_time % schedule_task_array[i].interval == 0)
        {
            schedule_task_array[i].task();
        }
    }
}

void scheduler_init()
{
    task_index = 0;
    last_run_time = 0;
    log_info("Scheduler initialized");
    periodic_task_init_a(scheduler_run_all_tasks, 1000);
}

void scheduler_add_task(void (*task)(void), int interval)
{
    schedule_task_array[task_index].task = task;
    schedule_task_array[task_index].interval = interval;
    task_index++;
}