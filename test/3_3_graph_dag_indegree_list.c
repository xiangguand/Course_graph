#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "graph_adj_list.h"
#include "queue.h"

const int test_result[6] = { 0, 3, 1, 2, 5, 4 };

void calculate_indegree(graphAdjList_t* graph, int index, int* counts, bool* visited)
{
  if (visited[index])
  {
    return;
  }
  visited[index] = true;

  // find other neighbors
  adjListUnit_t* adj = graph->adjList_[index];
  while (adj != NULL)
  {
    int weight = adj->weight_;
    if (weight == INFINITE_WEIGHT)
    {
      continue;
    }
    counts[adj->dst_]++;
    calculate_indegree(graph, adj->dst_, counts, visited);
    adj = adj->next_;
  }
}

int* topological_sort_indegree(graphAdjList_t* graph, int index, int* returnSize)
{
  if ((NULL == graph) || (0 == graph->num_) || (NULL == returnSize))
  {
    return NULL;
  }
  int* result = malloc(graph->num_ * sizeof(int));
  memset(result, 0, graph->num_ * sizeof(int));
  bool* visited = malloc(graph->num_ * sizeof(bool));
  memset(visited, 0, graph->num_ * sizeof(bool));
  int i_result = 0;

  // step1: calculate indegree count
  int* indegree_counts = malloc(graph->num_ * sizeof(int));
  memset(indegree_counts, 0, graph->num_ * sizeof(int));

  for (int i = 0; i < graph->num_; i++)
  {
    calculate_indegree(graph, i, indegree_counts, visited);
  }
  for (int i = 0; i < graph->num_; i++)
  {
    printf("[%d]: %d\n", i, indegree_counts[i]);
  }

  memset(visited, 0, graph->num_ * sizeof(bool));
  // step2: find vertex with 0 indegree
  queue_t* queue = createQueue(sizeof(int), graph->num_);
  for (int i = 0; i < graph->num_; i++)
  {
    if (indegree_counts[i] == 0)
    {
      queue->offer(queue, &i);
    }
  }

  // step3: repeat 2 + update indegree count
  while (true)
  {
    if (queue->isEmpty(queue))
    {
      break;
    }
    int i_vertex;
    queue->poll(queue, &i_vertex);

    printf("=> %d\n", i_vertex);
    result[i_result++] = i_vertex;

    adjListUnit_t* adj = graph->adjList_[i_vertex];
    while (adj != NULL)
    {
      indegree_counts[adj->dst_]--;
      if(indegree_counts[adj->dst_] == 0)
      {
        queue->offer(queue, &adj->dst_);
      }

      adj = adj->next_;
    }
  }

  *returnSize = i_result;
  free(visited);
  free(queue);
  free(indegree_counts);

  return result;
}

int main()
{
  graphAdjList_t* graph = graphAdjListGen(6);

  assert(0 == graphAdjListSetEdge(graph, 0, 1, 1));
  assert(0 == graphAdjListSetEdge(graph, 0, 2, 1));
  assert(0 == graphAdjListSetEdge(graph, 1, 4, 1));
  assert(0 == graphAdjListSetEdge(graph, 3, 2, 1));
  assert(0 == graphAdjListSetEdge(graph, 3, 4, 1));
  assert(0 == graphAdjListSetEdge(graph, 3, 5, 1));
  assert(0 == graphAdjListSetEdge(graph, 5, 4, 1));

  graphAdjListPrintEdge(graph);
  /*
  0 -> [ 1,  1] -> [ 2,  1]
  1 -> [ 4,  1]
  2 ->
  3 -> [ 2,  1] -> [ 4,  1] -> [ 5,  1]
  4 ->
  5 -> [ 4,  1]
  */

  int return_sz = 0;
  int* result = topological_sort_indegree(graph, 0, &return_sz);
  assert(return_sz == 6);
  for (int i = 0; i < return_sz; i++)
  {
    printf("%d, ", result[i]);
    assert(result[i] == test_result[i]);
  }
  printf("\n");

  printf("PASS\n");

  return 0;
}
