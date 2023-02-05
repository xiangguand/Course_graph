#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "graph_adj_list.h"
#include "queue.h"

const int test_result[5] = { 0, 1, 4, 3, 2 };

void traverse_dfs_help(graphAdjList_t* graph, int index, int* result, int* i_result, bool* visited)
{
  if (visited[index])
  {
    return;
  }
  visited[index] = true;

  // main logic
  printf("%d, ", index);
  result[(*i_result)++] = index;

  adjListUnit_t  *adj = graph->adjList_[index]; 
  // find other neighbors
  while(adj != NULL)
  {
    int weight = adj->weight_;
    if (weight == INFINITE_WEIGHT)
    {
      continue;
    }
    traverse_dfs_help(graph, adj->dst_, result, i_result, visited);
    adj = adj->next_;
  }
}

void traverse_dfs(graphAdjList_t* graph, int index, int* result)
{
  printf("\nDFS: ");
  bool* visited = malloc(graph->num_ * sizeof(bool));
  int i_result = 0;
  traverse_dfs_help(graph, index, result, &i_result, visited);
  printf("\n");

  free(visited);
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
  traverse_dfs(graph, 0, result);
  for (int i = 0; i < graph->num_; i++)
  {
    assert(result[i] == test_result[i]);
  }

  printf("PASS\n");

  return 0;
}
