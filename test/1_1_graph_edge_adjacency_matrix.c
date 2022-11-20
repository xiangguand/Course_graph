#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "graph_adj_mat.h"

int test_result[5][5] = { {
                              0,
                              1,
                              3,
                              INFINITE_WEIGHT,
                              INFINITE_WEIGHT,
                          },
                          {
                              INFINITE_WEIGHT,
                              0,
                              INFINITE_WEIGHT,
                              INFINITE_WEIGHT,
                              7,
                          },
                          {
                              INFINITE_WEIGHT,
                              INFINITE_WEIGHT,
                              0,
                              2,
                              2,
                          },
                          {
                              INFINITE_WEIGHT,
                              INFINITE_WEIGHT,
                              INFINITE_WEIGHT,
                              0,
                              9,
                          },
                          {
                              INFINITE_WEIGHT,
                              INFINITE_WEIGHT,
                              INFINITE_WEIGHT,
                              9,
                              0,
                          } };

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

  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      assert(test_result[i][j] == graph->adjMatrix_[i][j].weight);
    }
  }

  return 0;
}
