#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <alloca.h>

#include "linked-list.h"

using namespace base;

static Node* list = NULL;

/* ******************************************** */

static void printMenu(void)
{
   printf("\n"
         "+===============================================+\n"
         "|            Manipulation functions             |\n"
         "+===============================================+\n"
         "| 0 --- quit                                    |\n"
         "| 1 --- append new student                      |\n"
         "| 2 --- print list                              |\n"
         "| 3 --- remove student, through number          |\n"
         "| 4 --- get student's name, given the number    |\n"
         "| 5 --- sort list by name                       |\n"
         "| 6 --- sort list by number                     |\n"
         "+===============================================+\n");
}

/* ******************************************** */
/* menu handling functions */
/* ******************************************** */

void menuChoiceAppend()
{
   uint32_t nmec;
   char name[100];
   printf("nmec: ");
   scanf("%d", &nmec);
   printf("name: ");
   scanf("%s", name);

   list = append(list, nmec, name);
}

/* ******************************************** */

void menuChoicePrint()
{
   print(list);
}

/* ******************************************** */

void menuChoiceRemove()
{
   uint32_t nmec = 0;
   printf("nmec: ");
   scanf("%d", &nmec);

   list = remove(list, nmec);
}

/* ******************************************** */

void menuChoiceSearch()
{
   uint32_t nmec = 0;
   printf("nmec: ");
   scanf("%d", &nmec);

   const char *name = search(list, nmec);
   if (name != NULL)
   {
      printf("name: %s\n", name);
   }
   else
   {
      printf("student not found\n");
   }
}

/* ******************************************** */

void menuChoiceSortByName()
{
   list = sort_by_name(list);
}

/* ******************************************** */

void menuChoiceSortByNumber()
{
   list = sort_by_number(list);
}

/* ******************************************** */

/* The main function */
int main()
{
   int terminate = 0;
   while (!terminate)
   {
      printMenu();
      printf("Your command: ");
      int cmd;
      int res = scanf("%d", &cmd);
      if (res != 1)
      {
         fprintf(stderr, "Wrong input format (unsigned integer number required)\n");
         scanf("%*s"); // consume and ignore standard input
      }
      else
      {
         printf("\n");
         switch(cmd) 
         {
            case 0:
               terminate = 1;
               break;
            case 1:
               menuChoiceAppend();
               break;
            case 2:
               menuChoicePrint();
               break;
            case 3:
               menuChoiceRemove();
               break;
            case 4:
               menuChoiceSearch();
               break;
            case 5:
               menuChoiceSortByName();
               break;
            case 6:
               menuChoiceSortByNumber();
               break;
            default:
               fprintf(stderr, "Wrong action required (%d)\n", cmd);
         }
      }
   }

   return 0;
}     /* end of main */

