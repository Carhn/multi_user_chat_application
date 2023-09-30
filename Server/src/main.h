// Preprocessor Safety
#ifndef MAIN_H
#define MAIN_H

// Header Files
#include "client_handler.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <sys/ioctl.h>

// Preprocessor substitutions
#define PORT 45345

// Externs for global variables
extern pthread_mutex_t thread_lock;
extern pthread_mutex_t linked_list_lock;
extern pthread_mutex_t server_loop_lock;
extern Chat_Node *chat_list_head_ptr;
extern bool run_loop;

// Thread Data Struct
typedef struct thread_data
{

   // Accepted client socket
   int client_socket;

   // Client IP info struct
   struct sockaddr_in client_address;
   
} thread_data;

#endif