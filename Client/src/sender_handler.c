
// Header files
#include "sender_handler.h"

void *sender_handler(void *server_data)
{
   // Initialize variables

      // Constants
      const char BAD_ENTRY[] = 
                            "Error: Input not recognized.  Please try again.\n";

      // Client variable
      char user_input[ MAX_NOTE_LEN ];
      bool joined_chat = false;

      // Properties file variables
      char *server_address, *server_port_num;
      Properties *server_properties = server_data; 
      char *addr_key                = "ADDRESS";
      char *port_key                = "PORT";

         // Assign server property values to variables
         server_address  = property_get_property( server_properties, addr_key );
         server_port_num = property_get_property( server_properties, port_key );

      // Network Variables
      int server_port;
      struct sockaddr_in server_info;

         // Convert strings to integers
         server_port = atoi( server_port_num );

         // Assign properties values to network data structure      
         server_info.sin_family      = AF_INET;
         server_info.sin_addr.s_addr = inet_addr(server_address);
         server_info.sin_port        = htons(server_port);

      // Display Menu
      printf( "\nWelcome to the CS460 Chat Client\n" );
      printf( "Available Commands are:\n" );
      printf( "JOIN, LEAVE, SHUTDOWN, SHUTDOWN_ALL\n\n");
      printf( "Enter a chat message or a pre-defined command:\n");

      // Sender Loop
      while( run_client )
      {

         // Initialize variables
         Message client_data;

         // Add return address info to message
         add_return_address( &client_data );

         // Get User Input
         //scanf( "%s", user_input );
         fgets( user_input, MAX_NOTE_LEN, stdin );

         // Process Data

            // Determine if input type (command or note)
            parse_message( user_input, &client_data, &joined_chat );

         // Output Data

            // Check that message has a type
            if( client_data.message_type == NONE )
            {
               // Display error message
               printf( BAD_ENTRY );
            }

            // Otherwise, message contains proper info
            else
            {

               // Send data to the server
               send_message( server_info, client_data );

               // Engage mutex lock for loop boolean
               pthread_mutex_lock( &client_loop_lock );

               // Change bool value of run client variable
               check_for_shutdown_command( client_data.message_type ); 
            }                     
      }
      
   // Exit function
   return EXIT_SUCCESS;
}


// FUNCTIONS====================================================================
void add_return_address( Message *message_data )
{
   // Initialize variables
   char *client_name, *client_port;  
   char *properties_file_name =            "client.properties";
   char *name_key             =            "NAME";
   char *port_key             =            "PORT";
   Properties *properties;

   // Read in property file values and assign to property data structure
   properties  = property_read_properties( properties_file_name );

   // Read in and assign server property values to variables
   client_name     = property_get_property( properties, name_key );
   client_port     = property_get_property( properties, port_key );

   // Assign properties values to network data structure      
   message_data->connection_data.client_info.sin_family = AF_INET;
   message_data->connection_data.client_info.sin_port =
                                                     htons(atoi( client_port ));

   // Assign user name
   strcpy( message_data->connection_data.client_name, client_name );

}