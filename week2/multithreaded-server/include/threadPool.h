#include "headers.h"

class ThreadPool {
private:
    int n_threads;
    pthread_t * threads;
    // pthread_cond_t condition_var = PTHREAD_COND_INITIALIZER;

public:
    ThreadPool(int max_threads);
    ~ThreadPool();

    sem_t sem;
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    const int declare_runner(void * (*arg) (void *));
};