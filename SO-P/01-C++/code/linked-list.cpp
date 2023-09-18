#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "linked-list.h"

namespace base {

   Node* destroy(Node* list)
   {
      return NULL;
   }

   Node* append(Node* list, uint32_t nmec, char *name)
   {
      Node* n = (struct Node*)malloc(sizeof(struct Node));
      n->reg.nmec = nmec;
      n->reg.name = strdup(name);
      n->next = NULL;

      if(list == NULL)
      {
         return n;
      } 
      
      Node* last = list;
      while (last->next != NULL) {
         last = last->next;
      }

      last->next = n;
      return list;
   }

   void print(Node* list)
   {
      while (list != NULL)
      {
         printf ("\n%d", list -> reg.nmec);
         printf ("\n%s\n", list -> reg.name);
         list = list -> next;
      } 
   }

   int exists(Node* list, uint32_t nmec)
   {
      Node* node = list;
      while (node != NULL)
      {
         if (node -> reg.nmec == nmec)
         {
            return 1;
         }
         node = node -> next;
      }
      return 0;
   }

   Node* remove(Node* list, uint32_t nmec)
   {
      Node* prev = NULL;
      Node* node = list;
      while (node != NULL) {
         if (node -> reg.nmec == nmec) {
            if (prev == NULL) {
               list = list -> next;
            } else {
               prev -> next = node -> next;
            }
            free(node -> reg.name);
            free(node);
            return list;
         }
         prev = node;
         node = node -> next;
      }
      return list;
   }

   const char *search(Node* list, uint32_t nmec)
   {
      Node* node = list;
      while (node != NULL) {
         if (node -> reg.nmec == nmec) {
            return node -> reg.name;
         }
         node = node -> next;
      }
      return NULL;
   }

   Node* sort_by_number(Node* list)
   {
      Node* sorted_list = NULL;

      while (list != NULL) {
         Node* current_node = list;
         list = list->next;

         Node* prev_node = NULL;
         Node* node = sorted_list;
         while (node != NULL && current_node->reg.nmec > node->reg.nmec) {
            prev_node = node;
            node = node->next;
         }
         
         if (prev_node == NULL) {
            sorted_list = current_node;
         } else {
            prev_node->next = current_node;
         }
         current_node->next = node;
      }
      return sorted_list;
   }
}