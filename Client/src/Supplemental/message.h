
// Preprocessor Protection
#ifndef MESSAGE_H
#define MESSAGE_H

// Header Files
#include "constants.h"
#include "chat_node.h"
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>  
#include <unistd.h> 
#include <stdbool.h>
#include <pthread.h>
#include <errno.h>

// Message Data Structure
typedef struct Message
{

  int message_type;
  Chat_Node connection_data;
  char note[ MAX_NOTE_LEN ];

} Message;

// Function Prototypes
void acknowledge_exit( Chat_Node *head_ptr, Message the_message );
void parse_message( char *input, Message *message, bool *in_chat );
void send_message( struct sockaddr_in address, Message message );
void send_message_all( Chat_Node *head_ptr, Message the_message );
void send_message_all_others( Chat_Node *head_ptr, Message the_message );


#endif