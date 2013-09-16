
#include "mypthread.h"
//#include <sched.h>
//#include <sys/atomics.h>
//#include <string.h>


//
// Threads
//
int pthread_attr_init(pthread_attr_t *attr) {
	if (!attr) return EINVAL;
	attr->stackaddr = NULL;
	attr->stacksize = 0;
	attr->detachstate = PTHREAD_CREATE_JOINABLE;
	attr->param.sched_priority = PRIORITY_NORMAL;
	attr->inheritsched = PTHREAD_EXPLICIT_SCHED;
	attr->contentionscope = PTHREAD_SCOPE_SYSTEM;
	return 0;
}
/*
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start)(void *), void *arg) {
	
	unsigned int stacksize = 0;
	int priority = PRIORITY_NORMAL;
	int detach = 0;
	struct tib *tib;
	handle_t hthread;

	if (!thread) return EINVAL;

	if (attr) {
		stacksize = attr->stacksize;
		if (attr->detachstate == PTHREAD_CREATE_DETACHED) detach = 1;
		priority = attr->param.sched_priority;
	}

	hthread = beginthread((void (__stdcall *)(void *)) start, stacksize, arg, CREATE_POSIX | CREATE_SUSPENDED, NULL, &tib);
	if (hthread < 0) return errno;

	if (priority != PRIORITY_NORMAL) setprio(hthread, priority);
	if (detach) {
		*thread = tib->hndl;
		resume(hthread);
		close(hthread);
	} else {
		*thread = hthread;
		resume(hthread);
	}

	return 0;
}
*/

