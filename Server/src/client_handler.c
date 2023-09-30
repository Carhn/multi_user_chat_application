
// Header files
#include "client_handler.h"

// Read in message from client, determine message type, and call helper function
void *client_handler( void *recv_client_data )
{

   // Initialize variables
   thread_data *client_data = ( thread_data *)recv_client_data;
   Message received_message;

   // Read data from socket
   read_complete( client_data->client_socket, &received_message, 
                                                            sizeof( Message ) );
   // Assign client IP to message node
   received_message.connection_data.client_info.sin_addr.s_addr = 
                                    client_data->client_address.sin_addr.s_addr;

   // Determine message type

      // Message type ( command or chat note )s
      switch ( received_message.message_type )
      {
         case JOIN:

            // Call Join function to add client and alert chat members
            join( &chat_list_head_ptr, received_message );

            break;

         case LEAVE:

            // Call leave function to remove client and alert chat members
            leave( &chat_list_head_ptr, received_message );

            break;

         case SHUTDOWN:

            // Call shutdown function to remove client and alert chat members
            shutdown_client( &chat_list_head_ptr, received_message );

            break;

         case SHUTDOWN_ALL:

            // Call shutodwn all function.  Remove all members and exit server
            shutdown_all( &chat_list_head_ptr, received_message );

            break;

         default:

            // Everything else is a NOTE, forward message to all other members
            note( &chat_list_head_ptr, received_message );

            break;
      }

   // Disengage Mutex lock
   pthread_mutex_unlock( &thread_lock );

   // Exit thread
   pthread_exit( NULL );
}


/*
Calls add_client function to add client to chat linked list and then calls 
the send_message_all_others function to send message to all other chat members
*/
void join( Chat_Node **head_ptr, Message new_client)
{
   // Initialize variables
   Message outgoing;

      // Assign message type
      outgoing.message_type = NOTE;

      // Assign note to other clients acknowledging new members
      strcpy( outgoing.note, new_client.connection_data.client_name );
      strcat( outgoing.note, " has joined the chat.\n" );
      strcpy( outgoing.connection_data.client_name, 
                                        new_client.connection_data.client_name);

   // Engage link list mutex lock
   pthread_mutex_lock( &linked_list_lock );

   // Call add_client function
   add_client( head_ptr, new_client.connection_data );

   // Send message to all other members that someone has joined
   send_message_all_others( *head_ptr, outgoing );

   // Disengage link list mutex lock
   pthread_mutex_unlock( &linked_list_lock );
}

/*
 Calls remove_single_client function to remove client from linked list of chat
 members and then calls send_message_all_others function to alert other chat
 members that user has exited the chat.
*/
void leave( Chat_Node **head_ptr, Message target_client )
{ 
   // Initialize variables
   Message outgoing;

   // Assign message type
      outgoing.message_type = NOTE;
      strcpy( outgoing.note, target_client.connection_data.client_name );
      strcat( outgoing.note, " has left the chat.\n" );
      strcpy( outgoing.connection_data.client_name, 
                                    target_client.connection_data.client_name );

   // Engage link list mutex lock
   pthread_mutex_lock( &linked_list_lock );

   // Call remove single client function to remove a client
   remove_single_client( head_ptr, target_client.connection_data.client_name );

   //Send message to other clients that user has left the chat
   send_message_all( *head_ptr, outgoing );

   // Disengage link list mutex lock
   pthread_mutex_unlock( &linked_list_lock );
}

/* 
Calls send_message_all_others function and forwards received message to all
other chat clients
*/
void note( Chat_Node **head_ptr, Message sender_message )
{

   // Initialize variables
   Message outgoing;

   // Assign message type and data
   outgoing.message_type = NOTE;
   strcpy( outgoing.note, sender_message.connection_data.client_name );
   strcat( outgoing.note, ": " );
   strcat( outgoing.note, sender_message.note );
   strcpy( outgoing.connection_data.client_name, 
                                    sender_message.connection_data.client_name);

   // Engage link list mutex lock
   pthread_mutex_lock( &linked_list_lock );

   // Send the message to all other chat members
   send_message_all_others( *head_ptr, outgoing );

   // Disengage link list mutex lock
   pthread_mutex_unlock( &linked_list_lock );
}

/*
Calls acknowledge_exit function to send acknolowedgement to client that issued
the comment, and then leave function to remove the client from the linked list
and alert other chat members that user has exited the chat.
*/
void shutdown_client( Chat_Node **head_ptr, Message target_client )
{
   // Initialize variables

      // Assign message type
      Message outgoing;
      target_client.message_type = SHUTDOWN;

      // Assign exit message and data
      outgoing.message_type = SHUTDOWN;
      strcpy( outgoing.note, target_client.connection_data.client_name );
      strcat( outgoing.note, " has exited the chat." );
      strcpy( target_client.note, "Application Exited.  Goodbye.\n");
      strcpy( outgoing.connection_data.client_name, 
                                    target_client.connection_data.client_name);

   // Send Acknowledgement of received shutdown command back to client
   acknowledge_exit( *head_ptr, target_client );

   // Call Leave to message other chat members and remove client from list
   leave( head_ptr, outgoing );
}

/*
Calls send_message_all function to send message to all clients that a shutdown
command has been received.
*/
void shutdown_all( Chat_Node **head_ptr, Message issuing_client )
{
   // Initialize Variables
   Message outgoing;

      // Assign message type
      outgoing.message_type = SHUTDOWN_ALL;

      // Assign server shutdown message
      strcpy( outgoing.note, issuing_client.connection_data.client_name );
      strcat( outgoing.note, 
                  " has issued a SHUTDOWN ALL command.  Goodbye.\n" );
      strcpy( outgoing.connection_data.client_name, 
                                   issuing_client.connection_data.client_name );

   // Engage linked list mutex lock
   pthread_mutex_lock( &linked_list_lock );

   // Send Acknowledgement of received shutdown command back to client
   acknowledge_exit( *head_ptr, issuing_client );

   // Send shutdown all notification to all other chat members
   send_message_all_others( *head_ptr, outgoing );

   // Send Acknowledgement of received shutdown command back to client
   acknowledge_exit( *head_ptr, issuing_client );

   // Empty linked list
   purge_linked_list( head_ptr );

   // Disengage linked list mutex lock
   pthread_mutex_unlock( &linked_list_lock );

   // Shutdown server by setting server loop variable to false

      // Engage mutex lock
      pthread_mutex_lock( &server_loop_lock );

      // Set boolean to false
      run_loop = false;

      // Disengage mutex lock
      pthread_mutex_unlock( &server_loop_lock );
}


