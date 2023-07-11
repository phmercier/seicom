/************************************************************************
  queue.h 
  Copyright (c)Meshnetics.

  Description:

  History:
    21/05/07 D. Ovechkin - Created
**************************************************************************/
#ifndef _QUEUE_H
#define _QUEUE_H

#include <types.h>

/***************************************************************************
  Declare a queue and reset to the default state
  Every queue should be declared with this macros!
  Any queue element passed as parameter to functions should have as first
  field pointer for adding to a queue. 
  
  Parameters: 
    queue - the name of object.
  Returns: 
    None
****************************************************************************/
#define DECLARE_QUEUE(queue) QueueDescriptor_t queue = {NULL, &queue.head}

// Type of queue element
typedef struct __QueueElement_t
{
  struct 
  {
    struct __QueueElement_t *next;
  } service;
} QueueElement_t;

// Queue descriptor
typedef struct 
{
  QueueElement_t *head;
  QueueElement_t **tailNext;
} QueueDescriptor_t;


void  resetQueue(QueueDescriptor_t *queue);
void  putQueueElem(QueueDescriptor_t *queue, void *element);
void *getQueueElem(QueueDescriptor_t *queue);
bool  deleteHeadQueueElem(QueueDescriptor_t *queue);
void  deleteQueueElem(QueueDescriptor_t *queue, void *element);
void *getNextQueueElem(void *currElem);

#endif
//eof queue.h
