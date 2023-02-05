#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "graph_adj_list.h"
#include "queue.h"

const int test_result[5] = { 0, 1, 2, 4, 3 };

void traverse_bfs(graphAdjList_t* graph, int index, int* result)
{
  // using integer
  queue_t* queue = createQueue(sizeof(int), 20);

  // record you whether visited
  bool* visited = malloc(graph->num_ * sizeof(bool));
  memset(visited, 0, graph->num_ * sizeof(bool));

  int ret;
  ret = queue->offer(queue, &index);
  assert(0 == ret);

  int i_now = index;
  int i_result = 0;
  printf("\nBFS: ");
  while (true)
  {
    if (queue->isEmpty(queue))
      break;
    ret = queue->poll(queue, &i_now);
    assert(0 == ret);
    if (visited[i_now])
      continue;
    assert(i_now < graph->num_);
    visited[i_now] = true;

    //! main logic, BFS print out
    printf("%d, ", i_now);
    result[i_result++] = i_now;

    adjListUnit_t *adj = graph->adjList_[i_now];
    while(adj != NULL)
    {
      int weight = adj->weight_;
      if (weight == INFINITE_WEIGHT)
        continue;
      ret = queue->offer(queue, &adj->dst_);
      assert(0 == ret);
      adj = adj->next_;
    }
  }

  printf("\n");

  free(visited);
  free(queue);
}

int main()
{
  graphAdjList_t* graph = graphAdjListGen(5);

  int edge_before;
  assert(0 == graphAdjListGetEdge(graph, 0, 2, &edge_before));
  assert(INFINITE_WEIGHT == edge_before);

  assert(0 == graphAdjListSetEdge(graph, 0, 1, 1));
  assert((void*)0 != graph->adjList_[0]);
  assert(0 == graphAdjListSetEdge(graph, 0, 2, 3));
  assert(0 == graphAdjListSetEdge(graph, 1, 4, 7));
  assert(0 == graphAdjListSetEdge(graph, 2, 3, 2));
  assert(0 == graphAdjListSetEdge(graph, 2, 4, 2));
  assert(0 == graphAdjListSetEdge(graph, 3, 4, 9));
  assert(0 == graphAdjListSetEdge(graph, 4, 3, 9));

  int edge_after;
  assert(0 == graphAdjListGetEdge(graph, 0, 2, &edge_after));
  assert(3 == edge_after);

  graphAdjListPrintEdge(graph);
  /*
   0 -> [ 1,  1] -> [ 2,  3]
   1 -> [ 4,  7]
   2 -> [ 3,  2] -> [ 4,  2]
   3 -> [ 4,  9]
   4 -> [ 3,  9]
  */

  int* result = malloc(graph->num_ * sizeof(int));
  memset(result, 0, graph->num_ * sizeof(int));
  traverse_bfs(graph, 0, result);
  for (int i = 0; i < graph->num_; i++)
  {
    assert(result[i] == test_result[i]);
  }

  printf("PASS\n");

  return 0;
}
