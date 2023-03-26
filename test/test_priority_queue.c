#include <assert.h>
#include <stdio.h>
#include "priority_queue.h"

int cmp(void* a, void* b)
{
  int* a_p = (int*)a;
  int* b_p = (int*)b;

  return *a_p - *b_p;
}

int main(void)
{
  priorityQueue_t* queue = createPriorityQueue(sizeof(int), 100, cmp);

  int data;
  int temp;

  data = 100;
  queue->offer(queue, &data);
  data = 10;
  queue->offer(queue, &data);

  queue->poll(queue, &temp);
  printf("%d\n", temp);
  assert(10 == temp);

  data = 20;
  queue->offer(queue, &data);
  
  queue->poll(queue, &temp);
  printf("%d\n", temp);
  assert(20 == temp);

  data = 500;
  queue->offer(queue, &data);
  
  queue->poll(queue, &temp);
  printf("%d\n", temp);
  assert(100 == temp);

  data = 20;
  queue->offer(queue, &data);
  
  queue->poll(queue, &temp);
  printf("%d\n", temp);
  assert(20 == temp);

  queue->poll(queue, &temp);
  printf("%d\n", temp);
  assert(500 == temp);

  return 0;
}
