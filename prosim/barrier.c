//
// Created by Abhishek Biswas Deep on 7/25/24.
//

#include <stdlib.h>
#include "barrier.h"

/* This function initializes a barrier with given initial number of threads. */
barrier_t* barrier_init(int n) {
    barrier_t * barrier = calloc(1,sizeof(barrier_t));
    barrier->max_threads = n;
    barrier->cur_threads = 0;
    pthread_mutex_init(&barrier->mutex, NULL);
    pthread_cond_init(&barrier->first_cond, NULL);
    pthread_cond_init(&barrier->all_threads_left, NULL);
    return barrier;
}

/* This function performs barrier operation. */
void barrier_wait(barrier_t *barrier) {
    pthread_mutex_lock(&barrier->mutex);
    barrier->cur_threads++;

    if(barrier->cur_threads < barrier->max_threads) {
        pthread_cond_wait(&barrier->first_cond, &barrier->mutex);
    }

    barrier->cur_threads--;

    pthread_cond_signal(&barrier->first_cond);
    pthread_mutex_unlock(&barrier->mutex);
    if(barrier->cur_threads > 0) {
        pthread_cond_wait(&barrier->all_threads_left, &barrier->mutex);
    }
    pthread_cond_signal(&barrier->all_threads_left);
    pthread_mutex_unlock(&barrier->mutex);
}

/* This function is called by a thread once finished its simulation in order to decrement numbers of threads
needing to be synchronized. */
void barrier_done(barrier_t *barrier) {
    pthread_mutex_lock(&barrier->mutex);
    barrier->max_threads--;
    if(barrier->cur_threads == barrier->max_threads) {
        pthread_cond_signal(&barrier->first_cond);
    }
    pthread_mutex_unlock(&barrier->mutex);
}