#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "graph_adj_mat.h"
#include "priority_queue.h"

static char mappingToEnglish[6] = { 'A', 'B', 'C', 'D', 'E', 'F' };

static const int ANS_MINIMAL_FROM_A[6] = { 0, 3, 2, 8, 10, 14 };

typedef struct _path_t
{
  int start_;
  int end_;
  int distance_;
} path_t;

path_t* createPath(int i_st, int i_end, int distance)
{
  path_t* path = malloc(sizeof(path_t));
  path->start_ = i_st;
  path->end_ = i_end;
  path->distance_ = distance;

  return path;
}

int cmp(const void* a, const void* b)
{
  path_t* a_p = (path_t*)a;
  path_t* b_p = (path_t*)b;

  return a_p->distance_ - b_p->distance_;
}

void find_shortest_path_dijkstra(graphAdjMatrix_t* graph, int i_vertex_start)
{
  priorityQueue_t* queue = createPriorityQueue(sizeof(path_t), 20, cmp);
  bool* visited = malloc(sizeof(bool) * 6);
  memset(visited, 0, sizeof(bool) * 6);

  // memory that it save the previous vertex information
  int* shortest_distance = malloc(sizeof(int) * 6);
  int* shortest_vertex = malloc(sizeof(int) * 6);
  memset(shortest_vertex, 0, sizeof(int) * 6);
  for (int i = 0; i < 6; i++)
  {
    shortest_distance[i] = INT32_MAX;
  }

  // first path
  queue->offer(queue, createPath(-1, 0, 0));

  while (!queue->isEmpty(queue))
  {
    path_t path;
    queue->poll(queue, &path);

    // check whether it visited the vertex
    if (visited[path.end_])
    {
      continue;
    }
    visited[path.end_] = true;

    // main logic, update shortest path
    if (path.distance_ < shortest_distance[path.end_])
    {
      shortest_distance[path.end_] = path.distance_;
      shortest_vertex[path.end_] = path.start_;
    }

    // change perspective
    int i_vertex_from = path.end_;
    int distance_so_far = path.distance_;

    // explore neighbors
    for (int i = 0; i < 6; i++)
    {
      int dis = graph->adjMatrix_[i_vertex_from][i].weight;
      if (dis == INFINITE_WEIGHT)
      {
        continue;
      }

      int dis_to = distance_so_far + dis;
      queue->offer(queue, createPath(i_vertex_from, i, dis_to));
    }
  }

  printf("======\n");
  for (int i = 0; i < 6; i++)
  {
    printf("[%3c], ", mappingToEnglish[i]);
  }
  printf("\n");
  for (int i = 0; i < 6; i++)
  {
    if (shortest_vertex[i] >= 0)
    {
      printf("[%3c], ", mappingToEnglish[shortest_vertex[i]]);
    }
    else
    {
      printf("[%3c], ", '.');
    }
  }
  printf("\n======\n");
  for (int i = 0; i < 6; i++)
  {
    printf("[%3c], ", mappingToEnglish[i]);
  }
  printf("\n");
  for (int i = 0; i < 6; i++)
  {
    printf("[%3d], ", shortest_distance[i]);
  }
  printf("\n");

  for (int i = 0; i < 6; i++)
  {
    assert(ANS_MINIMAL_FROM_A[i] == shortest_distance[i]);
  }

  free(shortest_distance);
  free(shortest_vertex);
  free(visited);
  freePriorityQueue(queue);
}

int main()
{
  graphAdjMatrix_t* graph = graphAdjMatrixGen(6);

  int edge_before;
  assert(0 == graphAdjMatrixGetEdge(graph, 0, 2, &edge_before));
  assert(INFINITE_WEIGHT == edge_before);

  assert(0 == graphAdjMatrixSetEdge(graph, 0, 0, 0));
  assert(0 == graphAdjMatrixSetEdge(graph, 0, 1, 4));
  assert(0 == graphAdjMatrixSetEdge(graph, 0, 2, 2));

  assert(0 == graphAdjMatrixSetEdge(graph, 1, 1, 0));
  assert(0 == graphAdjMatrixSetEdge(graph, 1, 0, 4));
  assert(0 == graphAdjMatrixSetEdge(graph, 1, 2, 1));
  assert(0 == graphAdjMatrixSetEdge(graph, 1, 3, 5));

  assert(0 == graphAdjMatrixSetEdge(graph, 2, 2, 0));
  assert(0 == graphAdjMatrixSetEdge(graph, 2, 0, 2));
  assert(0 == graphAdjMatrixSetEdge(graph, 2, 1, 1));
  assert(0 == graphAdjMatrixSetEdge(graph, 2, 3, 8));
  assert(0 == graphAdjMatrixSetEdge(graph, 2, 4, 9));

  assert(0 == graphAdjMatrixSetEdge(graph, 3, 3, 0));
  assert(0 == graphAdjMatrixSetEdge(graph, 3, 1, 5));
  assert(0 == graphAdjMatrixSetEdge(graph, 3, 2, 8));
  assert(0 == graphAdjMatrixSetEdge(graph, 3, 4, 2));
  assert(0 == graphAdjMatrixSetEdge(graph, 3, 5, 6));

  assert(0 == graphAdjMatrixSetEdge(graph, 4, 4, 0));
  assert(0 == graphAdjMatrixSetEdge(graph, 4, 2, 9));
  assert(0 == graphAdjMatrixSetEdge(graph, 4, 3, 2));
  assert(0 == graphAdjMatrixSetEdge(graph, 4, 5, 5));

  assert(0 == graphAdjMatrixSetEdge(graph, 5, 5, 0));
  assert(0 == graphAdjMatrixSetEdge(graph, 5, 3, 6));
  assert(0 == graphAdjMatrixSetEdge(graph, 5, 4, 5));

  printf("0 = A\n");
  printf("1 = B\n");
  printf("2 = C\n");
  printf("3 = D\n");
  printf("4 = E\n");
  printf("5 = F\n");
  graphAdjMatrixPrintEdge(graph);
  /*
   [   0][   1][   2][   3][   4]
[0]    0,    1,    3,  INFINITE_WEIGHT,  INFINITE_WEIGHT,
[1]  INFINITE_WEIGHT,    0,  INFINITE_WEIGHT,  INFINITE_WEIGHT,    7,
[2]  INFINITE_WEIGHT,  INFINITE_WEIGHT,    0,    2,    2,
[3]  INFINITE_WEIGHT,  INFINITE_WEIGHT,  INFINITE_WEIGHT,    0,    9,
[4]  INFINITE_WEIGHT,  INFINITE_WEIGHT,  INFINITE_WEIGHT,    9,    0,
  */

  find_shortest_path_dijkstra(graph, 0);

  return 0;
}
