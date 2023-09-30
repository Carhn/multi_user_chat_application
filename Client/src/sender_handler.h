// Preprocessor Protection
#ifndef SENDER_HANDLER_H
#define SENDER_HANDLER_H

// Header files
#include <stdbool.h>       // Handles boolean logic
#include <stdlib.h>        // General library functions
#include <sys/socket.h>    // Creating socket, socket structs, etc...
#include <netinet/in.h>    // IP definitionsr
#include <pthread.h>       // Handle threading
#include "properties.h"    // Properties file capability
#include <stdio.h>         // String handling
#include "main.h"
#include "message.h"

// Function prototypes
void *sender_handler(void *server_data);
void add_return_address( Message *message_data );

#endif