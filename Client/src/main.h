// Preprocessor Protection
#ifndef MAIN_H
#define MAIN_H

// Header Files
#include <stdio.h>
#include <stdlib.h>  
#include <unistd.h> 
#include <pthread.h>
#include "sender_handler.h"
#include "receiver_handler.h"
#include <stdatomic.h>
#include "properties.h"
#include "dbg.h"
#include "chat_node.h"
#include "message.h"
#include "constants.h"

// Extern for global variables
extern int run_client;
extern pthread_mutex_t client_loop_lock;

// Prototypes
void check_for_shutdown_command( int message_type );

#endif
