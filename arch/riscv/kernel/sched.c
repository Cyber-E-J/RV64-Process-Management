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
  if(next->pid == current->pid) return;
  else {
    struct task_struct* tmp = current;
    current = next;
    __switch_to(tmp, next);
  }
}

int task_init_done = 0;
// initialize tasks, set member variables
void task_init(void) {
  puts("task init...\n");

  // initialize task[0]
  // current 是 地址
  current = (struct task_struct*)Kernel_Page;
  // state 默认是TASK_RUNNING
  current->state = TASK_RUNNING;
  // counter运行剩余时间为0
  current->counter = 1;
  // 最低priority
  current->priority = 5;
  // 没有被block
  current->blocked = 0;
  // 进程编号为0
  current->pid = 0;
  task[0] = current;
  task[0]->thread.sp = (unsigned long long)task[0] + TASK_SIZE;
  task[0]->thread.ra = &__init_sepc;

  // set other 4 tasks
  // LAB_TEST_NUM 为4
  for (int i = 1; i <= LAB_TEST_NUM; ++i) {
    /* your code */
    // current 是 地址
    task[i] = (struct task_struct*)(Kernel_Page + i * TASK_SIZE);
    // state 默认是TASK_RUNNING
    task[i]->state = TASK_RUNNING;
    // counter运行剩余时间为0
    task[i]->counter = 0;
    // 最低priority--?
    task[i]->priority = 5;
    // 没有被block
    task[i]->blocked = 0;
    // 进程编号为0
    task[i]->pid = i;
    // task[i] = current;
    task[i]->thread.sp = (unsigned long long)task[i] + TASK_SIZE;
    task[i]->thread.ra = &__init_sepc;

    printf("[PID = %d] Process Create Successfully!\n", task[i]->pid);
  }
  task_init_done = 1;
  //current = task[4];
}


/* Shortest Job First */
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
  current->counter--;
  if(current->counter <= 0){
    schedule();
    //current->counter = 0;
  }
}

// Select the next task to run. If all tasks are done(counter=0), set task0's
// counter to 1 and it would assign new test case.
void schedule(void) {
  unsigned char next;
  /* your code */

  int i;
  int shortest_counter = 100+1;// initial as max
  int shortest_pid = 0;
  for(i=LAB_TEST_NUM;i>=1;i--){
    if(task[i]->counter > 0 && task[i]->counter < shortest_counter){
      shortest_pid = i;
      shortest_counter = task[i]->counter;
    }
  }

  //printf("%d,%d",shortest_pid,shortest_counter);

  if(shortest_pid == 0) {
    printf(" all is done. switch to task 0\n");
    next = 0;
  }
  else //next = task[shortest_pid];
    next = shortest_pid;
  
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
  current->counter--;
  if(current->counter <= 0){
    schedule();
  }
}

// Select the next task to run. If all tasks are done(counter=0), set task0's
// counter to 1 and it would assign new test case.
void schedule(void) {
  unsigned char next;
  /* your code */

  int i;
  int highest_priority = 6;
  int prior_pid = 0;
  for(i=LAB_TEST_NUM;i>=1;i--){
    if(task[i]->counter > 0 && task[i]->priority < highest_priority){
      prior_pid = i;
      highest_priority = task[i]->priority;
    }
  }

  //printf("%d,%d", prior_pid, highest_priority);

  if(prior_pid == 0) {
    printf(" all is done. switch to task 0\n");
    next = 0;
  }
  else next = prior_pid;

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
