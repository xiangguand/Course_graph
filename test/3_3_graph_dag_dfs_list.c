#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "graph_adj_list.h"
#include "queue.h"

const int test_result[6] = { 3, 5, 0, 2, 1, 4 };

void topological_sort_dfs_rec(graphAdjList_t* graph, int index, int* result, int* i_result, bool* visited)
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
    topological_sort_dfs_rec(graph, adj->dst_, result, i_result, visited);
    adj = adj->next_;
  }

  // main logic
  result[(*i_result)++] = index;
}

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

void reverseIntegerArray(int *array, int num)
{
  int i_left = 0;
  int i_right = num - 1;
  while (i_left < i_right)
  {
    swap(&array[i_left], &array[i_right]);
    i_left++;
    i_right--;
  }
}

int* topological_sort_dfs(graphAdjList_t* graph, int index, int* returnSize)
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
  for (int i = 0; i < graph->num_; i++)
  {
    topological_sort_dfs_rec(graph, i, result, &i_result, visited);
  }
  reverseIntegerArray(result, i_result);
  *returnSize = i_result;

  free(visited);

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
  int* result = topological_sort_dfs(graph, 0, &return_sz);
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
