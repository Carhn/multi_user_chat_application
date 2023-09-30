// Debug
#define DBG

// Header files
#include "main.h"

// Initialize global variables
int run_client = true;              // Loop used by handlers to run indefinitely
pthread_mutex_t client_loop_lock;   // Lock for the handler's loop boolean

// Main
int main()
{
   // Initialize variables

      // Thread variables
      pthread_t sender_handler_thread, receiver_handler_thread;

      // Initialize global loop mutex lock
      pthread_mutex_init( &client_loop_lock, NULL );

      // Properties file variables
      char *properties_server_file = "server.properties";
      char *properties_client_file = "client.properties";
      Properties *server_properties;           
      Properties *client_properties;

         // Read in property file values and assign to property data structure
         server_properties = property_read_properties( properties_server_file );
         client_properties = property_read_properties( properties_client_file );

   // Create threads to handle sending and receiving

      // Create sender handler thread
      pthread_create( &sender_handler_thread, NULL, sender_handler, 
                                                     (void*)server_properties );

      // Create receiver handler thread
      pthread_create( &receiver_handler_thread, NULL, receiver_handler, 
                                                     (void*)client_properties );

      // Join threads - this will keep main from exiting while chat is running
      pthread_join( receiver_handler_thread, NULL );
}

// Functions ===================================================================
void check_for_shutdown_command( int message_type )
{
   // Check if message type is Shutdown
   if( ( message_type == SHUTDOWN) || ( message_type == SHUTDOWN_ALL) )
   {
      // Change bool value of run client variable
      run_client = false;
   }
   // Disengage mutex lock for loop boolean
   pthread_mutex_unlock( &client_loop_lock );
}