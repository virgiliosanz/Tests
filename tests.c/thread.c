#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
/*
#include <gdsl.h>

typedef struct queue_s queue_s;
enum job_action_e {
	WORK,
	END
};
typedef enum job_action_e job_action_e;

typedef int (*job_cb)(void *context, void *data);
struct job_s {
	job_action_e action;
	char        *name;
	void        *context;
	void        *data;
	job_cb      *job;
};
typedef struct job_s job_s;

job_s  *job_alloc(const char *name);
void   *job_context(void *context);
void   *job_data(void *data);
job_cb *job_callback(job_cb *job);
job_s  *job_last();

struct worker_s {
	int          thread_id;
	gdsl_queue_t q;
	time_t       started;

};
typedef struct worker_s worker_s;

worker_s *worker_alloc(const char *name);
int       worker_start(worker_s *worker, const char *worker_name);
int       worker_enqueu(worker_s *worker, job_s *job);
*/

#define NUM_THREADS (50)

void *print_hello(void *threadid)
{
        long tid;
        tid = (long)threadid;
        printf("Hello World! It's me, thread #%ld!\n", tid);
        sleep(10);
        printf("Bye World! It's me, thread #%ld!\n", tid);

        pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
        pthread_t threads[NUM_THREADS];
        int rc;
        long t;
        for (t = 0; t < NUM_THREADS; t++) {
                printf("In main: creating thread %ld\n", t);
                rc = pthread_create(&threads[t], NULL, print_hello, (void *)t);
                if (rc) {
                        printf("ERROR; return code from pthread_create() is %d\n", rc);
                        exit(-1);
                }
        }

	/* Como esperar por los hilos? Como saber cuantos quedan ejecutando? */

        /* Last thing that main() should do */
        pthread_exit(NULL);
}

