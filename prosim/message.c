//
// Created by Abhishek Biswas Deep on 7/25/24.
//

#include <stdlib.h>
#include <pthread.h>
#include "message.h"
#include "stdio.h"

/* Initializing the message send/receive. */
message_t* message_init(int num_nodes) {
    message_t * message = calloc(1, sizeof(message_t));
    message->send = calloc(num_nodes, sizeof(int*));
    message->receive = calloc(num_nodes, sizeof(int*));
    pthread_mutex_init(&message->message_lock, NULL);

    return message;
}

/* This is initializing the nodes. */
void message_node_init(message_t * message, int node_id, int num_procs) {
    node_id = node_id - 1;
    message->send[node_id] = calloc(num_procs, sizeof(int));
    message->receive[node_id] = calloc(num_procs, sizeof(int));
}
/* If receiver is waiting then sender is done and receiver is done.
 * Or else the sender waits. */
void message_send(message_t * message, int sender_id, int receiver_id, int clock_tick) {
    pthread_mutex_lock(&message->message_lock);

    int sender_node = get_node_id(sender_id);
    int receiver_node = get_node_id(receiver_id);
    int process_sender_id = get_process_id(sender_id);
    int process_receiver_id = get_process_id(receiver_id);

    message->send[sender_node - 1][process_sender_id - 1] = receiver_id;

    if (message->receive[receiver_node - 1][process_receiver_id - 1] == sender_id) {
        message->send[sender_node - 1][process_sender_id - 1] = -clock_tick;
        message->receive[receiver_node - 1][process_receiver_id - 1] = -clock_tick;
    }

    pthread_mutex_unlock(&message->message_lock);

}

/* If sender is waiting then receiver is done and sender is done.
 * Or else the receiver is waiting. */
void message_receive(message_t * message, int sender_id, int receiver_id, int clock_tick) {
    pthread_mutex_lock(&message->message_lock);

    int sender_node = get_node_id(sender_id);
    int receiver_node = get_node_id(receiver_id);
    int process_sender_id = get_process_id(sender_id);
    int process_receiver_id = get_process_id(receiver_id);

    message->receive[receiver_node - 1][process_receiver_id - 1] = sender_id;

    if (message->send[sender_node - 1][process_sender_id - 1] == receiver_id) {
        message->receive[receiver_node - 1][process_receiver_id - 1] = -clock_tick;
        message->send[sender_node - 1][process_sender_id - 1] = -clock_tick;
    }

    pthread_mutex_unlock(&message->message_lock);

}

/* This is computing id for the nodes. */
int compute_id(int node_id, int process_id) {
    return node_id * 100 + process_id;
}

/* This is used to get the node id. */
int get_node_id(int id) {
    return id / 100;
}

/* This is used to get the process id. */
int get_process_id(int id) {
    return id % 100;
}

/* This is used to make the sender wait. */
int is_sender_waiting(message_t * message, int sender_id) {
    int sender_node = get_node_id(sender_id);
    int process_sender_id = get_process_id(sender_id);
    return message->send[sender_node - 1][process_sender_id - 1];
}

/* This is used to make the receiver wait. */
int is_receiver_waiting(message_t * message, int receiver_id) {
    int receiver_node = get_node_id(receiver_id);
    int process_receiver_id = get_process_id(receiver_id);
    return message->receive[receiver_node - 1][process_receiver_id - 1];
}


