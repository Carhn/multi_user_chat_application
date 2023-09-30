// Prepocessor protection
#ifndef RECEIVER_HANDLER_H
#define RECEIVER_HANDLER_H

// Header files
#include <stdbool.h>       // Handles boolean logic
#include <stdlib.h>        // General library functions
#include <sys/socket.h>    // Creating socket, socket structs, etc...
#include <netinet/in.h>    // IP definitions
#include <pthread.h>       // Handle threading
#include "properties.h"    // Properties file capability
#include <stdio.h>         // String handling
#include <errno.h>         // Error checking on socket and connection calls
#include "main.h"
#include "message.h"
#include "misc.h"

// Function prototypes
void *receiver_handler( void *properties );
void *recv_data( void *recv_socket );

#endif
