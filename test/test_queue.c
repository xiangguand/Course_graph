#include <assert.h>
#include <stdio.h>
#include "queue.h"

int main(void)
{
  queue_t* queue = createQueue(sizeof(int), 100);

  for (int i = 0; i < 200; i++)
  {
    int ret = queue->offer(queue, &i);
    assert(false == queue->isEmpty(queue));
    if (i < 100)
    {
      assert(0 == ret);
      if(i != 99)
      {
        assert(false == queue->isFUll(queue));
      }
    }
    else
    {
      assert(true == queue->isFUll(queue));
      assert(-1 == ret);
    }
  }

  int data = 0;
  int ret;
  for (int i = 0; i < 200; i++)
  {
    ret = queue->poll(queue, &data);
    if (i < 100)
    {
      assert(data == i);
      assert(0 == ret);
    }
    else
    {
      assert(-1 == ret);
    }
  }

  for (int i = 0; i < 500; i++)
  {
    data = rand();
    int temp;
    ret = queue->offer(queue, &data);
    assert(0 == ret);
    ret = queue->poll(queue, &temp);
    assert(0 == ret);
    assert(temp == data);
  }

  int count = 0;
  int check = 0;

  for (int k = 0; k < 1000; k++)
  {
    for (int i = 0; i < 80; i++)
    {
      ret = queue->offer(queue, &count);
      assert(false == queue->isEmpty(queue));
      assert(0 == ret);
      count++;
    }

    for (int i = 0; i < 50; i++)
    {
      ret = queue->poll(queue, &data);
      assert(0 == ret);
      assert(data == check);
      check++;
    }

    for (int i = 0; i < 50; i++)
    {
      ret = queue->offer(queue, &count);
      assert(0 == ret);
      count++;
    }
    for (int i = 0; i < 80; i++)
    {
      ret = queue->poll(queue, &data);
      assert(0 == ret);
      assert(data == check);
      check++;
    }
  }

  assert(true == queue->isEmpty(queue));

  free(queue);
  printf("PASS\n");
  return 0;
}
