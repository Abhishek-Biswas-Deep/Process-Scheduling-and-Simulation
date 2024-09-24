//
// Created by Abhishek Biswas Deep on 7/25/24.
//

#ifndef PROSIM_MESSAGE_H
#define PROSIM_MESSAGE_H

typedef struct message {
    int ** send;
    int ** receive;
    pthread_mutex_t message_lock;
} message_t;

/* Initializing the message send/receive.
 * @params:
 *   num_nodes: the number of nodes
 * @returns:
 *   the message pointer. */
message_t* message_init(int num_nodes);

/* This is initializing the nodes.
 * @params:
 *   message pointer
 *   the node id
 *   the number of processes
 * @returns:
 *   the message node initialization. */
void message_node_init(message_t * message, int node_id, int num_procs);

/* If receiver is waiting then sender is done and receiver is done.
 * Or else the sender waits.
 * @params:
 *   message pointer
 *   the sender id
 *   the receiver id
 *   the clock ticks
 * @returns:
 *   the message send. */
void message_send(message_t * message, int sender_id, int receiver_id, int clock_tick);

/* If sender is waiting then receiver is done and sender is done.
 * Or else the receiver is waiting.
 * @params:
 *   message pointer
 *   the sender id
 *   the receiver id
 *   the clock ticks
 * @returns:
 *   the message receive. */
void message_receive(message_t * message, int sender_id, int receiver_id, int clock_tick);

/* This is computing id for the nodes.
 * @params:
 *   node id
 *   process id
 * @returns:
 *   the id computed. */
int compute_id(int node_id, int process_id);

/* This is used to get the node id.
 * @params:
 *   id
 * @returns:
 *   the node id. */
int get_node_id(int id);

/* This is used to get the process id.
 * @params:
 *   id
 * @returns:
 *   the process id. */
int get_process_id(int id);

/* This is used to make the sender wait.
 * @params:
 *   message pointer
 *   sender id
 * @returns:
 *   an int. */
int is_sender_waiting(message_t * message, int sender_id);

/* This is used to make the receiver wait.
 * @params:
 *   message pointer
 *   receiver id
 * @returns:
 *   an int. */
int is_receiver_waiting(message_t * message, int receiver_id);

#endif //PROSIM_MESSAGE_H
