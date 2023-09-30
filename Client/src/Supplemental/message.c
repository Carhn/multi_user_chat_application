#include "message.h"

// Constants
const char JOIN_ERROR[] = "Error: You are already a member of this chat\n";
const char LEAVE_ERROR[] = "Error: You are not current a member of this chat\n";
const char BLANK_NOTE[] = "0";

void acknowledge_exit( Chat_Node *head_ptr, Message the_message )
{

   // Initialize variables
   Chat_Node *working_ptr = head_ptr;

   // Check that linked list is not null
   if( head_ptr != NULL )
   {
      // Iterate through the linked list

         // Loop while the current node's next node isn't NULL
         while( working_ptr != NULL )
         {

            // Make sure that current node is not originator of the message
            if( strcmp( working_ptr->client_name, 
                     the_message.connection_data.client_name ) == CLIENT_FOUND )
            {
               // Send message to client of working/current pointer
               send_message( working_ptr->client_info, the_message );
            }

            // Advance working pointer
            working_ptr = working_ptr->nextNode;

         // Close loop
         }
   }
}

// Determines type and info of received message
void parse_message( char *input, Message *message, bool *in_chat )
{
   // Determine if input type (command or note)
   if( strcmp( input, "JOIN\n" ) == 0 )
   {
      // Check flag to see if currently in the chat
      if( *in_chat )
      {
         // Display error message
         printf( JOIN_ERROR );
      }
      else
      {
         // Set message type
         message->message_type = JOIN;

         // Set joined chat flag to true
         *in_chat = true;
      }

   }
   else if( strcmp( input, "LEAVE\n" ) == 0 )
   {
      // Check flag to see if currently in chat
      if( !*in_chat )
      {
         // Display error message
         printf( LEAVE_ERROR );

      }
      else
      {
         // Set message type
         message->message_type = LEAVE;

         // Set joined chat flag to false
         *in_chat = false;
      }
   }
   else if( strcmp( input, "SHUTDOWN\n" ) == 0 )
   {
      // Check flag to see if currently in chat
      if( !*in_chat )
      {
         // Display error message
         printf( LEAVE_ERROR );

      }
      else
      {
         // Set message type
         message->message_type = SHUTDOWN;

         // Set joined chat flag to false
         *in_chat = false;
      }

   }
   else if( strcmp( input, "SHUTDOWN ALL\n" ) == 0 )
   {
      // Check flag to see if currently in chat
      if( !*in_chat )
      {
         // Display error message
         printf( LEAVE_ERROR );

      }
      else
      {
         // Set message type
         message->message_type = SHUTDOWN_ALL;

         // Set joined chat flag to false
         *in_chat = false;
      }

   }
   // Otherwise, assume it's a message
   else
   {
      // Check flag to see if currently in the chat
      if( !*in_chat )
      {
         // Display error message
         printf( JOIN_ERROR );
      }
      else
      {
         // Set message type
         message->message_type = NOTE;

         // Set user message
         strcpy( message->note, input );
      }
   }
}

// Assigns data to a Message Data Type variable and transmits it to the server
void send_message( struct sockaddr_in address, Message message )
{

   // Initialize and Declare Variables
   int connection_socket = socket( AF_INET, SOCK_STREAM, 0 );
   int connection_error;

   // Connect to Server
   connection_error = connect( connection_socket, ( struct sockaddr *) &address, 
                                                             sizeof( address ));

         // Error Message for failed connection
         if( connection_error == -1)
         {
            printf("Socket acceptance error number: %d\n", errno );
         }

   // Write message to server
   write( connection_socket, &message, sizeof( Message ) );

   // Close Connection
   close(connection_socket);
}

void send_message_all( Chat_Node *head_ptr, Message the_message )
{

   // Initialize variables
   Chat_Node *working_ptr = head_ptr;

   // Check that linked list is not null
   if( head_ptr != NULL )
   {

      // Iterate through the linked list

         // Loop while the current node's next node isn't NULL
         while( working_ptr != NULL )
         {
            // Send message to client of working/current pointer
            send_message( working_ptr->client_info, the_message );

            // Advance working pointer
            working_ptr = working_ptr->nextNode;

         // Close loop
         }
   }
}

void send_message_all_others( Chat_Node *head_ptr, Message the_message )
{

   // Initialize variables
   Chat_Node *working_ptr = head_ptr;

   // Check that linked list is not null
   if( head_ptr != NULL )
   {

      // Iterate through the linked list

         // Loop while the current node's next node isn't NULL
         while( working_ptr != NULL )
         {

            // Make sure that current node is not originator of the message
            if( strcmp( working_ptr->client_name, 
                     the_message.connection_data.client_name ) != CLIENT_FOUND )
            {
               // Send message to client of working/current pointer
               send_message( working_ptr->client_info, the_message );
            }

            // Advance working pointer
            working_ptr = working_ptr->nextNode;

         // Close loop
         }
   }
}
