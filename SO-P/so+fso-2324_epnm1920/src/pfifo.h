/*
 * @brief A priority FIFO (implemented with a circular array),
 *        whose elements are pairs of integers, one being an
 *        non-negative id and the other a positive priority value.
 * 
 * The following operations are defined:
 *    \li initializer
 *    \li check if is empty
 *    \li check if is full
 *    \li insertion of a value with a given priority
 *    \li retrieval of a value.
 **/


#ifndef PFIFO_H
#define PFIFO_H

#include <stdint.h>
#include  "settings.h"

// TODO point: uncomment the desired implementation
// * DONE
#include "thread.h"
//#include "process.h"

typedef struct
{
   struct
   {
      int id;         // element ID (works as an index in array all_patients)
      int priority;   // patient priority in FIFO
   } array[FIFO_MAXSIZE];
   int inp;  ///< point of insertion (queue tail)
   int out;  ///< point of retrieval (queue head)
   int cnt;  ///< number of items stored
   static pthread_cond_t not_full;
   static pthread_cond_t not_empty;
   static pthread_mutex_t access;

   // TODO point: if necessary, add synchronization declarations here
} PriorityFIFO;

void init_pfifo(PriorityFIFO* pfifo);
void term_pfifo(PriorityFIFO* pfifo);
void insert_pfifo(PriorityFIFO* pfifo, int id, int priority);
int retrieve_pfifo(PriorityFIFO* pfifo);
int full_fifo(PriorityFIFO* pfifo);
int empty_fifo(PriorityFIFO* pfifo);


#endif
