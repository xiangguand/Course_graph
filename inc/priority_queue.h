#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct _priorityQueue_t priorityQueue_t;
typedef struct _priorityQueue_t
{
  int (*offer)(priorityQueue_t* priorityQueue, void* data);
  int (*poll)(priorityQueue_t* priorityQueue, void* data);
  int (*top)(priorityQueue_t* priorityQueue, void* data);
  uint32_t (*getLength)(priorityQueue_t* priorityQueue);
  bool (*isEmpty)(priorityQueue_t* priorityQueue);
  bool (*isFUll)(priorityQueue_t* priorityQueue);
  void* info;
} priorityQueue_t;

typedef int (*priofityQueueCmp_func)(const void* arg1, const void* arg2);

priorityQueue_t* createPriorityQueue(uint32_t data_bytes, uint32_t priorityQueue_length, priofityQueueCmp_func cmp);
void freePriorityQueue(priorityQueue_t* priorityQueue);

#endif /* PRIORITY_QUEUE_H_ */
