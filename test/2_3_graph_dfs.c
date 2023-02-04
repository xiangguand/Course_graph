#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "graph_adj_mat.h"
#include "queue.h"

const int test_result[5] = { 0, 1, 4, 3, 2 };

void traverse_dfs_help(graphAdjMatrix_t* graph, int index, int* result, int* i_result, bool* visited)
{
  if (visited[index])
  {
    return;
  }
  visited[index] = true;

  // main logic
  printf("%d, ", index);
  result[(*i_result)++] = index;

  // find other neighbors
  for (int ni = 0; ni < graph->num_; ni++)
  {
    int weight = graph->adjMatrix_[index][ni].weight;
    if (weight == INFINITE_WEIGHT)
    {
      continue;
    }
    traverse_dfs_help(graph, ni, result, i_result, visited);
  }
}

void traverse_dfs(graphAdjMatrix_t* graph, int index, int* result)
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
  graphAdjMatrix_t* graph = graphAdjMatrixGen(5);

  int edge_before;
  assert(0 == graphAdjMatrixGetEdge(graph, 0, 2, &edge_before));
  assert(INFINITE_WEIGHT == edge_before);

  assert(0 == graphAdjMatrixSetEdge(graph, 0, 0, 0));
  assert(0 == graphAdjMatrixSetEdge(graph, 0, 0, 0));
  assert(0 == graphAdjMatrixSetEdge(graph, 0, 1, 1));
  assert(0 == graphAdjMatrixSetEdge(graph, 0, 2, 3));

  assert(0 == graphAdjMatrixSetEdge(graph, 1, 1, 0));
  assert(0 == graphAdjMatrixSetEdge(graph, 1, 4, 7));

  assert(0 == graphAdjMatrixSetEdge(graph, 2, 2, 0));
  assert(0 == graphAdjMatrixSetEdge(graph, 2, 3, 2));
  assert(0 == graphAdjMatrixSetEdge(graph, 2, 4, 2));

  assert(0 == graphAdjMatrixSetEdge(graph, 3, 3, 0));
  assert(0 == graphAdjMatrixSetEdge(graph, 3, 4, 9));

  assert(0 == graphAdjMatrixSetEdge(graph, 4, 3, 9));
  assert(0 == graphAdjMatrixSetEdge(graph, 4, 4, 0));

  int edge_after;
  assert(0 == graphAdjMatrixGetEdge(graph, 0, 2, &edge_after));
  assert(3 == edge_after);

  graphAdjMatrixPrintEdge(graph);
  /*
   [   0][   1][   2][   3][   4]
[0]    0,    1,    3,  INFINITE_WEIGHT,  INFINITE_WEIGHT,
[1]  INFINITE_WEIGHT,    0,  INFINITE_WEIGHT,  INFINITE_WEIGHT,    7,
[2]  INFINITE_WEIGHT,  INFINITE_WEIGHT,    0,    2,    2,
[3]  INFINITE_WEIGHT,  INFINITE_WEIGHT,  INFINITE_WEIGHT,    0,    9,
[4]  INFINITE_WEIGHT,  INFINITE_WEIGHT,  INFINITE_WEIGHT,    9,    0,
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
