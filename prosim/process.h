//
// Created by Alex Brodsky on 2023-05-07.
//

#ifndef PROSIM_PROCESS_H
#define PROSIM_PROCESS_H
#include "prio_q.h"
#include "context.h"
#include "barrier.h"
#include "message.h"


typedef struct processor {
    prio_q_t *blocked;       /* queue for blocked processes on node */
    prio_q_t *ready;         /* queue for blocked processes on node */
    int clock_time;          /* local node time */
    int next_proc_id;        /* local node process counter */
    prio_q_t *block_send;    /* queue for blocked send processes */
    prio_q_t *block_recv;    /* queue for blocked receive processes */
    message_t * message;     /* message passing functionality */
    int num_procs;           /* number of processes */
} processor_t;

/* Initialize the simulation
 * @params:
 *   quantum: the CPU quantum to use in the situation
 * @returns:
 *   returns 1
 */
extern void process_init(int cpu_quantum);

/* Create a new node context
 * @params:
 *   None
 * @returns:
 *   pointer to new node context.
 */
extern processor_t *process_new(message_t * message);

/* Admit a process into the simulation
 * @params:
 *   proc: pointer to the program context of the process to be admitted
 *   cpu : node context
 * @returns:
 *   returns 1
 */
extern int process_admit(processor_t *cpu, context *proc);

/* Perform the simulation
 * @params:
 *   cpu : node context
 * @returns:
 *   returns 1
 */
extern int process_simulate(processor_t *cpu, barrier_t *barrier);

/* Output process summary post execution
 * @params:
 *   fout : output file
 * @returns:
 *   none
 */
extern void process_summary(FILE *fout);

#endif //PROSIM_PROCESS_H
