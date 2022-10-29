#include "sched.h"

#include "stdio.h"

#define Kernel_Page 0x80210000
#define LOW_MEMORY 0x80211000
#define PAGE_SIZE 4096UL

struct task_struct* current;
struct task_struct* task[NR_TASKS];

extern task_test_done;
extern void __init_sepc(void);

// If next==current,do nothing; else update current and call __switch_to.
void switch_to(struct task_struct* next) {
  // your code
}

int task_init_done = 0;
// initialize tasks, set member variables
void task_init(void) {
  puts("task init...\n");

  // initialize task[0]
  current = (struct task_struct*)Kernel_Page;
  current->state = TASK_RUNNING;
  current->counter = 0;
  current->priority = 5;
  current->blocked = 0;
  current->pid = 0;
  task[0] = current;
  task[0]->thread.sp = (unsigned long long)task[0] + TASK_SIZE;

  // set other 4 tasks
  for (int i = 1; i <= LAB_TEST_NUM; ++i) {
    /* your code */

    printf("[PID = %d] Process Create Successfully!\n", task[i]->pid);
  }
  task_init_done = 1;
}

#ifdef SJF
// simulate the cpu timeslice, which measn a short time frame that gets assigned
// to process for CPU execution
void do_timer(void) {
  if (!task_init_done) return;
  if (task_test_done) return;
  printf("[*PID = %d] Context Calculation: counter = %d,priority = %d\n",
         current->pid, current->counter, current->priority);
  // current process's counter -1, judge whether to schedule or go on.
  /* your code */
}

// Select the next task to run. If all tasks are done(counter=0), set task0's
// counter to 1 and it would assign new test case.
void schedule(void) {
  unsigned char next;
  /* your code */

  if (current->pid != task[next]->pid) {
    printf(
        "[ %d -> %d ] Switch from task %d[%lx] to task %d[%lx], prio: %d, "
        "counter: %d\n",
        current->pid, task[next]->pid, current->pid,
        (unsigned long)current->thread.sp, task[next]->pid,
        (unsigned long)task[next], task[next]->priority, task[next]->counter);
  }
  switch_to(task[next]);
}

#endif

#ifdef PRIORITY

// simulate the cpu timeslice, which measn a short time frame that gets assigned
// to process for CPU execution
void do_timer(void) {
  if (!task_init_done) return;
  if (task_test_done) return;
  printf("[*PID = %d] Context Calculation: counter = %d,priority = %d\n",
         current->pid, current->counter, current->priority);
  // current process's counter -1, judge whether to schedule or go on.
  /* your code */
}

// Select the next task to run. If all tasks are done(counter=0), set task0's
// counter to 1 and it would assign new test case.
void schedule(void) {
  unsigned char next;
  /* your code */

  if (current->pid != task[next]->pid) {
    printf(
        "[ %d -> %d ] Switch from task %d[%lx] to task %d[%lx], prio: %d, "
        "counter: %d\n",
        current->pid, task[next]->pid, current->pid,
        (unsigned long)current->thread.sp, task[next]->pid,
        (unsigned long)task[next], task[next]->priority, task[next]->counter);
  }
  switch_to(task[next]);
}

#endif
