// Header Files
#include "chat_node.h"

// Constants
const char DEFAULT_NAME[] = "NONE";

// Adds a new client to the linked list of chat members
void add_client( Chat_Node **head_ptr, Chat_Node new_client_data )
{

   // Create working pointer and point to head node
   Chat_Node *working_ptr = *head_ptr;

   // Declare new node
   Chat_Node *new_node;

   // Allocate memory to new node
   new_node = ( Chat_Node *)malloc( sizeof( Chat_Node ) );

   // Assign data to new node
   copy_client_data( new_node, new_client_data );

   // Set node's next node to NULL
   new_node->nextNode = NULL;

   // Check if head pointer is NULL
   if( *head_ptr == NULL )
   {
      // Set head pointer to new node
      *head_ptr = new_node;
   }

   //Otherwise, add node to end of list
   else
   {
      // Loop until the next pointer is NULL
      while( working_ptr->nextNode != NULL )
      {
         // Advance working pointer to the next node
         working_ptr = working_ptr->nextNode;
      }

      // Set the current pointer's next pointer to the new node
      working_ptr->nextNode = new_node;
   }
}

// Copy client data to a new node
void copy_client_data( Chat_Node *new_node, Chat_Node client_data )
{
   // Assign chat node data from Message struct to chat node variable
   
      // Client IP address
      new_node->client_info.sin_addr.s_addr = 
                                        client_data.client_info.sin_addr.s_addr;
      
      // Client internet protocol version (IPv4)
      new_node->client_info.sin_family = client_data.client_info.sin_family;

      // Client port number
      new_node->client_info.sin_port = client_data.client_info.sin_port;

      // Logical Name of Client
      strcpy( new_node->client_name, client_data.client_name );

      // Next Node Pointer
      new_node->nextNode = NULL;
}

// Empty linked list of all nodes and free memory
void purge_linked_list( Chat_Node **head_ptr )
{
   // Initialize variables
   Chat_Node *working_ptr = *head_ptr;
   Chat_Node *previous_ptr = NULL;

   // Check that linked list is not null
   if( head_ptr != NULL )
   {

      // Iterate through the linked list

         // Loop while the current node's next node isn't NULL
         while( working_ptr != NULL )
         {

            // Set previous pointer to the working pointer
            previous_ptr = working_ptr;

            // Advance working pointer
            working_ptr = working_ptr->nextNode;

            // Free previous pointer
            free( previous_ptr );

         // Close loop
         }
   }
}

// Remove a specific client from the linked list of chat members
void remove_single_client( Chat_Node **head_ptr, char *target_name )
{

   // Declare and Initialize Variables
   Chat_Node *working_ptr = *head_ptr;
   Chat_Node *previous_ptr = NULL;

   // Check if list is empty
   if( *head_ptr == NULL )
   {

      // Check if head node is target node name
      if( strcmp( working_ptr->client_name, target_name ) == CLIENT_FOUND )
      {
         // Set head node to head's next node
         *head_ptr = ( *head_ptr )->nextNode;

         // Free working node
         free( working_ptr );

      // Close check
      }

      // Otherwise, head node is not the target node
      else
      {
         // Loop through list, checking for NULL
         while( working_ptr != NULL )
         {
            // First set PREVIOUS pointer to working
            previous_ptr = working_ptr;

            // check if working node's next node ip is target ip
            if( strcmp( working_ptr->client_name, target_name ) 
                                                               == CLIENT_FOUND )
            {

               // Set previous pointer's next node to the working's next node
               previous_ptr->nextNode = working_ptr->nextNode;

               // free working pointer
               free ( working_ptr );

               // Return to exit function
               return;

            // Close check
            }

            // Advance the working pointer to the next node
            working_ptr = working_ptr->nextNode;

         }
      }
   }
}