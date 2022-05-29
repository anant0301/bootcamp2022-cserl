#include "threadPool.h"

ThreadPool::ThreadPool(int max_threads) {
    this-> n_threads = max_threads;
    this-> threads = (pthread_t *)calloc(max_threads, sizeof(pthread_t));
    if (sem_init(&(this-> sem), 0, 0) == -1) {
        std::cout << "Error in semaphore creation" << std::endl;
        exit(1);
    }
}

ThreadPool::~ThreadPool() {
    for (int i = 0; i < this-> n_threads; ++i) {
        pthread_join(this-> threads[i], nullptr);
    }
    std::cout << "Threads Closed" << std::endl;
}

const int ThreadPool::declare_runner(void * (*runner_func) (void *)) {
    int i = 0;
    for (; i < this-> n_threads; ++i) {
        pthread_create(&(this-> threads[i]), NULL, runner_func, NULL);
    }
    return i;
}

// pthread_t * ThreadPool::get_thread() {
//     pthread_t * thread;
//     pthread_mutex_lock(&lock);
//     thread = this-> thread_pool.front();
//     this-> thread_pool.pop();
//     pthread_mutex_unlock(&lock);
//     return thread;
// }
