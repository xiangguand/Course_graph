#include <string.h>
#include <stdlib.h>
#include "queue.h"

typedef struct _queueInfo_t
{
  uint32_t data_size;
  uint32_t i_head;
  uint32_t i_tail;
  uint8_t* buf;
  uint32_t count;
  uint32_t max_length;
} queueInfo_t;

static inline int queueOffer(queue_t* queue, void* data_p)
{
  if ((NULL == queue) || (NULL == data_p))
  {
    return -5;
  }
  queueInfo_t* info = (queueInfo_t*)queue->info;
  if (info->count >= info->max_length)
  {
    return -1;
  }
  memcpy(info->buf + info->i_head * info->data_size, data_p, info->data_size);
  info->i_head++;
  info->i_head = info->i_head == info->max_length ? 0 : info->i_head;
  info->count++;

  return 0;
}

static inline int queuePoll(queue_t* queue, void* data_p)
{
  if ((NULL == queue) || (NULL == data_p))
  {
    return -5;
  }
  queueInfo_t* info = (queueInfo_t*)queue->info;
  if (info->count <= 0)
  {
    return -1;
  }
  memcpy(data_p, info->buf + info->i_tail * info->data_size, info->data_size);
  info->i_tail++;
  info->i_tail = info->i_tail == info->max_length ? 0 : info->i_tail;
  info->count--;

  return 0;
}

static inline int queueTop(queue_t* queue, void* data_p)
{
  if ((NULL == queue) || (NULL == data_p))
  {
    return -5;
  }
  queueInfo_t* info = (queueInfo_t*)queue->info;
  memcpy(data_p, info->buf + info->i_tail * info->data_size, info->data_size);
  return 0;
}

static inline uint32_t queueGetLength(queue_t* queue)
{
  if ((NULL == queue))
  {
    return -5;
  }
  queueInfo_t* info = (queueInfo_t*)queue->info;
  return info->count;
}

static inline bool queueIsEmpty(queue_t* queue)
{
  if ((NULL == queue))
  {
    return -5;
  }
  queueInfo_t* info = (queueInfo_t*)queue->info;
  return info->count > 0 ? false : true;
}

static inline bool queueIsFUll(queue_t* queue)
{
  if ((NULL == queue))
  {
    return -5;
  }
  queueInfo_t* info = (queueInfo_t*)queue->info;
  return info->count >= info->max_length ? true : false;
}

queue_t* createQueue(uint32_t data_bytes, uint32_t queue_length)
{
  queue_t* queue = malloc(sizeof(queue_t));
  memset(queue, 0, sizeof(queue_t));
  queueInfo_t* info = malloc(sizeof(queueInfo_t));
  memset(info, 0, sizeof(queueInfo_t));
  queue->info = info;
  info->buf = malloc(data_bytes * sizeof(uint8_t) * queue_length);
  memset(info->buf, 0, data_bytes * sizeof(uint8_t) * queue_length);
  info->data_size = data_bytes;
  info->max_length = queue_length;
  queue->offer = queueOffer;
  queue->poll = queuePoll;
  queue->top = queueTop;
  queue->getLength = queueGetLength;
  queue->isEmpty = queueIsEmpty;
  queue->isFUll = queueIsFUll;

  return queue;
}

void freeQueue(queue_t* queue)
{
  if ((NULL == queue) || (NULL == queue->info))
  {
    return;
  }
  queueInfo_t* info = (queueInfo_t*)queue->info;
  free(info->buf);
  free(queue->info);
  free(queue);
}
