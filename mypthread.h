//#include <sys/types.h>

typedef unsigned int size_t;
typedef int handle_t;
typedef handle_t pthread_t;

#define NULL    0
#define EINVAL          22               // Invalid argument
#define PRIORITY_NORMAL          8
#define PTHREAD_CREATE_JOINABLE       0
#define PTHREAD_EXPLICIT_SCHED        1
#define PTHREAD_SCOPE_SYSTEM          1

struct sched_param {
  int sched_priority;
};

/*
unsigned long param[4][4] = {
  {0xcb39de43, 0xcb39ce43, 0xfb38de03, 0xcb38de43},
  {0xcb39de43, 0xcb39ce43, 0xcb39ce83, 0xcb39ce83},
  {0xcb39de43, 0xcb39ce43, 0xcb39ce83, 0xcb39ce83},
  {0xbb39de43, 0xbb39ce43, 0xbb39ce83, 0xbb39ce83}
}; */

//
// Threads
//

struct pthread_attr {
	void *stackaddr;
	size_t stacksize;
	int detachstate;
	struct sched_param param;
	int inheritsched;
	int contentionscope;
};

typedef struct pthread_attr pthread_attr_t;

int pthread_attr_init(pthread_attr_t *attr);
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start)(void *), void *arg);

