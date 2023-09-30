// Header files
#include "receiver_handler.h"

// Global variable
pthread_mutex_t recv_thread_lock; // Lock for receiver function

void *receiver_handler( void *properties )
{
   // Initiailize Variables

      // Properties variables
      Properties *client_properties = properties;
      char *port;
      char *port_key = "PORT";

         // Assign server property values to variables
         port = property_get_property( client_properties, port_key );

      // Network variables
      int listener_port, server_socket, receiving_socket;
      struct sockaddr_in address_info;

   // Socket and Port Information

      // Convert strings to integers
      listener_port = atoi( port );

      // Create and assign socket
      server_socket = socket( AF_INET, SOCK_STREAM, 0 );

      // Assign address into
      address_info.sin_family = AF_INET;
      address_info.sin_addr.s_addr = htonl( INADDR_ANY );
      address_info.sin_port = htons( listener_port );

      // Bind socket
      bind( server_socket, ( struct sockaddr * ) &address_info, 
                                                       sizeof( address_info ) );

      // Set socket to listen for client connection
      listen( server_socket, 100 );

   // Prime Mutex lock

      // Initialize Mutex lock for receiver threads
      pthread_mutex_init( &recv_thread_lock, NULL );

      // Engage lock for receiver threads
      pthread_mutex_lock( &recv_thread_lock );

   // Receiver Handler's server loop

      // Loop while bool is true
      while( run_client )
      {

         // Accept connection from chat server
         receiving_socket = accept( server_socket, NULL, NULL );

           // Check for acceptance error
           if( receiving_socket == -1 )
            {
               printf("Error accepting client %d\n", errno );
            }

         // Declare pthread variable
         pthread_t listener_thread;  

         // Create listener thread
         pthread_create( &listener_thread, NULL, recv_data, 
                                                  ( void *) &receiving_socket );

         // Detach listener thread
         pthread_detach( listener_thread );

         // Re-engage Mutex lock
         pthread_mutex_lock( &recv_thread_lock );

         // Close client connection
         close( receiving_socket );

      // Close loop
      }

      // Exit Function
      pthread_exit( NULL );
}

// Read in data, print data, and check if client needs to shutdown
void *recv_data( void *recv_socket )
{
   // Initialize variables
   int *socket_num = ( int *) recv_socket;
   int msg_socket = *socket_num;
   Message received_message;

   // Read data from the server
   read_complete( msg_socket, &received_message, sizeof( Message ) );

   // Print message
   printf( "%s", received_message.note );

   // Check for shutdown command
   check_for_shutdown_command( received_message.message_type );

   // Disengage mutex lock for receiver thread
   pthread_mutex_unlock( &recv_thread_lock );

   // Exit Function
   pthread_exit( NULL );
}
