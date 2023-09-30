// Preprocessor Safety
#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

// Header files
#include "chat_node.h"
#include "message.h"
#include "main.h"
#include "constants.h"
#include "misc.h"

// Function prototypes
void *client_handler( void *recv_client_data );
void join( Chat_Node **head_ptr, Message new_client );
void leave( Chat_Node **head_ptr, Message target_client );
void note( Chat_Node **head_ptr, Message sender_message );
void shutdown_client( Chat_Node **head_ptr, Message target_client );
void shutdown_all( Chat_Node **head_ptr, Message issuing_client );

#endif