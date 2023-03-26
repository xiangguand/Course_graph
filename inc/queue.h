#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct _queue_t queue_t;
typedef struct _queue_t
{
  int (*offer)(queue_t *queue, void *data);
  int (*poll)(queue_t *queue, void *data);
  int (*top)(queue_t *queue, void *data);
  uint32_t(*getLength)(queue_t *queue);
  bool (*isEmpty)(queue_t *queue);
  bool (*isFUll)(queue_t *queue);
  void *info;
} queue_t;

queue_t *createQueue(uint32_t data_bytes, uint32_t queue_length);
void freeQueue(queue_t* queue);

#endif /* QUEUE_H_ */
