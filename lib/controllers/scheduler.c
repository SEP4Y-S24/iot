#include "scheduler.h"
#include "logger.h"
#include "periodic_task.h"
#include <stdlib.h>

static uint64_t last_run_time = 0;
static schedule_task_t schedule_task_array[100];

static void scheduler_run_all_tasks()
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
    log_info("Scheduler initialized");
    periodic_task_init_a(scheduler_run_all_tasks, 1000);
}

void scheduler_add_task(void (*task)(void), int interval)
{
    for (int i = 0; i < 100; i++)
    {
        if (schedule_task_array[i].task == NULL)
        {
            schedule_task_array[i].task = task;
            schedule_task_array[i].interval = interval;
            break;
        }
    }
}