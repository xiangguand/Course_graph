#include <string.h>
#include <stdlib.h>
#include "priority_queue.h"

typedef struct _priorityQueueInfo_t
{
  uint32_t data_size;
  uint8_t* buf;
  uint32_t count;
  uint32_t max_length;
  int* priority;
  priofityQueueCmp_func cmp;
} priorityQueueInfo_t;

static inline int priorityQueueOffer(priorityQueue_t* priorityQueue, void* data_p)
{
  if ((NULL == priorityQueue) || (NULL == data_p))
  {
    return -5;
  }
  priorityQueueInfo_t* info = (priorityQueueInfo_t*)priorityQueue->info;
  if (info->count >= info->max_length)
  {
    return -1;
  }
  memcpy(info->buf + info->count * info->data_size, data_p, info->data_size);
  info->count++;
  qsort(info->buf, info->count, info->data_size, info->cmp);

  return 0;
}

static inline int priorityQueuePoll(priorityQueue_t* priorityQueue, void* data_p)
{
  if ((NULL == priorityQueue) || (NULL == data_p))
  {
    return -5;
  }
  priorityQueueInfo_t* info = (priorityQueueInfo_t*)priorityQueue->info;
  if (info->count <= 0)
  {
    return -1;
  }
  memcpy(data_p, info->buf, info->data_size);

  // shift
  for (int i = 0; i < info->count-1; i++)
  {
    memcpy(info->buf + (i * info->data_size), info->buf + ((i + 1) * info->data_size), info->data_size);
  }
  info->count--;

  return 0;
}

static inline int priorityQueueTop(priorityQueue_t* priorityQueue, void* data_p)
{
  if ((NULL == priorityQueue) || (NULL == data_p))
  {
    return -5;
  }
  priorityQueueInfo_t* info = (priorityQueueInfo_t*)priorityQueue->info;
  memcpy(data_p, info->buf, info->data_size);
  return 0;
}

static inline uint32_t priorityQueueGetLength(priorityQueue_t* priorityQueue)
{
  if ((NULL == priorityQueue))
  {
    return -5;
  }
  priorityQueueInfo_t* info = (priorityQueueInfo_t*)priorityQueue->info;
  return info->count;
}

static inline bool priorityQueueIsEmpty(priorityQueue_t* priorityQueue)
{
  if ((NULL == priorityQueue))
  {
    return -5;
  }
  priorityQueueInfo_t* info = (priorityQueueInfo_t*)priorityQueue->info;
  return info->count > 0 ? false : true;
}

static inline bool priorityQueueIsFUll(priorityQueue_t* priorityQueue)
{
  if ((NULL == priorityQueue))
  {
    return -5;
  }
  priorityQueueInfo_t* info = (priorityQueueInfo_t*)priorityQueue->info;
  return info->count >= info->max_length ? true : false;
}

priorityQueue_t* createPriorityQueue(uint32_t data_bytes, uint32_t priorityQueue_length, priofityQueueCmp_func cmp)
{
  priorityQueue_t* priorityQueue = malloc(sizeof(priorityQueue_t));
  memset(priorityQueue, 0, sizeof(priorityQueue_t));
  priorityQueueInfo_t* info = malloc(sizeof(priorityQueueInfo_t));
  memset(info, 0, sizeof(priorityQueueInfo_t));
  priorityQueue->info = info;
  info->buf = malloc(data_bytes * sizeof(uint8_t) * priorityQueue_length);
  memset(info->buf, 0, data_bytes * sizeof(uint8_t) * priorityQueue_length);
  info->data_size = data_bytes;
  info->max_length = priorityQueue_length;
  info->priority = malloc(sizeof(int) * priorityQueue_length);
  info->cmp = cmp;
  priorityQueue->offer = priorityQueueOffer;
  priorityQueue->poll = priorityQueuePoll;
  priorityQueue->top = priorityQueueTop;
  priorityQueue->getLength = priorityQueueGetLength;
  priorityQueue->isEmpty = priorityQueueIsEmpty;
  priorityQueue->isFUll = priorityQueueIsFUll;

  return priorityQueue;
}

void freePriorityQueue(priorityQueue_t* priorityQueue)
{
  if ((NULL == priorityQueue) || (NULL == priorityQueue->info))
  {
    return;
  }
  priorityQueueInfo_t* info = (priorityQueueInfo_t*)priorityQueue->info;
  free(info->buf);
  free(priorityQueue->info);
  free(priorityQueue);
}
