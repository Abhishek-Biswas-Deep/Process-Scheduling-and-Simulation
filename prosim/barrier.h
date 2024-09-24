//
// Created by Abhishek Biswas Deep on 7/25/24.
//

#ifndef PROSIM_BARRIER_H
#define PROSIM_BARRIER_H

#include <pthread.h>

typedef struct barrier {
    pthread_mutex_t mutex;
    pthread_cond_t first_cond;
    pthread_cond_t all_threads_left;
    int max_threads;
    int cur_threads;
} barrier_t;

barrier_t * barrier_init(int n);
void barrier_wait(barrier_t *barrier);
void barrier_done(barrier_t *barrier);

#endif //PROSIM_BARRIER_H
