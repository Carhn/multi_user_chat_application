// Header files
#include "main.h"

// Global variables
pthread_mutex_t thread_lock;           // Lock for client_handler threads
pthread_mutex_t linked_list_lock;      // Lock for interacting with linked list
pthread_mutex_t server_loop_lock;      // Lock for changing loop boolean
Chat_Node *chat_list_head_ptr = NULL;  // Head Pointer to chat linked list
bool run_loop = true;                  // Server loop boolean

// Main function
int main()
{
   // Initialize variables
   int server_socket;
   thread_data client_data;
   struct sockaddr_in server_adress;
   socklen_t client_address_size = sizeof( client_data.client_address );

   // Socket and Port Information

      // Create and assign socket
      server_socket = socket( AF_INET, SOCK_STREAM, 0 );

      // Assign address info

         // Define connection as IPV4
         server_adress.sin_family = AF_INET;

         // Accept any address
         server_adress.sin_addr.s_addr = htonl( INADDR_ANY );

         // Assign translated port address
         server_adress.sin_port = htons( PORT );

      // Bind socket
      bind( server_socket, ( struct sockaddr *) &server_adress, 
                                                 sizeof( struct sockaddr_in ) );

      // Set socket to listen for client connection
      listen( server_socket, 100 );

   // Server loop

      // Prime Mutex locks

         // Initialize mutex lock
         pthread_mutex_init( &thread_lock, NULL );
         pthread_mutex_init( &linked_list_lock, NULL );
         pthread_mutex_init( &server_loop_lock, NULL );

         // Engage lock
         pthread_mutex_lock( &thread_lock );

      // Loop conditional
      while( run_loop )
      {

         // Accept client connection and assign socket and client's IP address
         client_data.client_socket = accept( server_socket, 
                              ( struct sockaddr *)&client_data.client_address, 
                              &client_address_size );

            // Error check for accepting client socket
            if( client_data.client_socket == -1 )
            {
               printf("Error accepting client %d\n", errno );

            }

            // Initialize thread variable
            pthread_t server_thread;

            // Create client_handler thread
            pthread_create( &server_thread, NULL, client_handler, 
                                                        ( void *) &client_data);

            // Detach client_handler thread
            pthread_detach( server_thread );

            // Engage Mutex lock
            pthread_mutex_lock( &thread_lock );

            // Close client connection
            close( client_data.client_socket );

      // Close loop
      }

   // Exit Application
   pthread_exit( NULL );
}
