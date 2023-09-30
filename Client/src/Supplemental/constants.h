// Preprocessor Protection
#ifndef CONSTANTS_H
#define CONSTANTS_H

// Preprocessor Substitutions

   // String Lengths
   #define MAX_NOTE_LEN 64
   #define MAX_NAME_LEN 13
   #define NULL_CHARACTER '\0'
   
   // Error Code
   #define ERROR -1
   #define CLIENT_FOUND 0

   // Client Instructions
   #define NONE         0  // No message type assigned, blank message
   #define JOIN         1  // Join the chat command
   #define LEAVE        2  // Leave the chat command
   #define SHUTDOWN     3  // Leave the chat and exit client command
   #define SHUTDOWN_ALL 4  // Leave the chat, exit all chat clients and server
   #define NOTE         5  // Send a message to other chat clients

// Global Constants


#endif