// Preprocessor Protection
#ifndef CHAT_NODE_H
#define CHAT_NODE_H

// Header Files
#include "constants.h"
#include <string.h>
#include <stdio.h>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <stdlib.h>


// Chat Node Data Structure
typedef struct Chat_Node {

  struct sockaddr_in client_info;   // Socket information
  char client_name[ MAX_NAME_LEN ]; // Client's logical name
  struct Chat_Node *nextNode;       // Next node in linked list

} Chat_Node;

// Function Prototypes
void add_client( Chat_Node **head_ptr, Chat_Node new_client_data );
void copy_client_data( Chat_Node *new_node, Chat_Node client_data );
void purge_linked_list( Chat_Node **head_ptr );
void remove_single_client( Chat_Node **head_ptr, char *target_name );

#endif
