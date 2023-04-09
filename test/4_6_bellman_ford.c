#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "graph_adj_list.h"

static const int TEST_GRAPH_0_SHORTEST[] = { 0, INT32_MAX, INT32_MAX, -3, -5 };

static const int TEST_GRAPH_0_PREV[] = { -1, -1, -1, 4, 0 };

static const int TEST_GRAPH_1_SHORTEST[] = { 5, 0, 2, 2, 0 };

static const int TEST_GRAPH_1_PREV[] = { 1, -1, 1, 4, 0 };

void ASSERT_INT_ARRAY(int* exp, int* real, int size)
{
  for (int i = 0; i < size; i++)
  {
    assert(exp[i] == real[i]);
  }
}

typedef struct _path_t
{
  int start_;
  int end_;
  int distance_;
} path_t;

typedef struct _result_t
{
  int* shortestPath_;
  int* shortestPathPrevVertex_;
  int num;
} result_t;

int collectAllEdges(graphAdjList_t* graph, path_t** edges)
{
  int edges_num = 0;
  for (int i = 0; i < graph->num_; i++)
  {
    adjListUnit_t* unit = graph->adjList_[i];
    while (unit != (void*)0)
    {
      ++edges_num;
      unit = unit->next_;
    }
  }

  path_t* edges_all = malloc(sizeof(path_t) * edges_num);
  int i_path = 0;
  for (int i = 0; i < graph->num_; i++)
  {
    adjListUnit_t* unit = graph->adjList_[i];
    while (unit != (void*)0)
    {
      edges_all[i_path].start_ = i;
      edges_all[i_path].end_ = unit->dst_;
      edges_all[i_path].distance_ = unit->weight_;
      i_path++;
      unit = unit->next_;
    }
  }

  *edges = edges_all;

  return edges_num;
}

result_t* find_shortest_path_bellmanford(graphAdjList_t* graph, int i_vertex_start)
{
  int N = graph->num_;
  int* shortest_path = malloc(N * sizeof(int));
  for (int i = 0; i < N; i++)
  {
    shortest_path[i] = INT32_MAX;
  }
  shortest_path[i_vertex_start] = 0;

  int* shortest_path_prev_vertex = malloc(N * sizeof(int));
  for (int i = 0; i < N; i++)
  {
    shortest_path_prev_vertex[i] = -1;
  }

  // collect all edge
  path_t* edges_all;
  int edges_num = collectAllEdges(graph, &edges_all);

  // main logic
  for (int round = 0; round < N - 1; round++)
  {
    for (int i = 0; i < edges_num; i++)
    {
      path_t edge = edges_all[i];
      if (shortest_path[edge.start_] == INT32_MAX)
      {
        continue;
      }

      int weight_min = shortest_path[edge.end_];
      int weight_now = shortest_path[edge.start_] + edge.distance_;
      if (weight_now < weight_min)
      {
        shortest_path[edge.end_] = weight_now;
        shortest_path_prev_vertex[edge.end_] = edge.start_;
      }
    }
  }

  // check negative cycle
  bool is_negative_cycle_detected = false;
  for (int i = 0; i < edges_num; i++)
  {
    path_t edge = edges_all[i];
    if (shortest_path[edge.start_] == INT32_MAX)
    {
      continue;
    }

    int weight_min = shortest_path[edge.end_];
    int weight_now = shortest_path[edge.start_] + edge.distance_;
    if (weight_now < weight_min)
    {
      // negative cycle will let this algorithm change every time
      // after above for-loop, it should enter steady state
      is_negative_cycle_detected = true;
    }
  }

  if(is_negative_cycle_detected)
  {
    return NULL;
  }

  result_t* result = malloc(sizeof(result_t));
  result->shortestPath_ = shortest_path;
  result->shortestPathPrevVertex_ = shortest_path_prev_vertex;
  result->num = graph->num_;

  printf("================\n");
  for (int i = 0; i < N; i++)
  {
    printf("%d, ", shortest_path[i]);
  }
  printf("\n================\n");
  printf("================\n");
  for (int i = 0; i < N; i++)
  {
    printf("%d, ", shortest_path_prev_vertex[i]);
  }
  printf("\n================\n");

  return result;
}

int main()
{
  graphAdjList_t* graph = graphAdjListGen(5);

  assert(0 == graphAdjListSetEdge(graph, 0, 0, 0));
  assert(0 == graphAdjListSetEdge(graph, 0, 4, -5));

  assert(0 == graphAdjListSetEdge(graph, 1, 1, 0));
  assert(0 == graphAdjListSetEdge(graph, 1, 0, 5));
  assert(0 == graphAdjListSetEdge(graph, 1, 2, 2));
  assert(0 == graphAdjListSetEdge(graph, 1, 2, 3));
  assert(0 == graphAdjListSetEdge(graph, 1, 3, 9));

  assert(0 == graphAdjListSetEdge(graph, 2, 2, 0));
  assert(0 == graphAdjListSetEdge(graph, 2, 3, 1));

  assert(0 == graphAdjListSetEdge(graph, 3, 3, 0));

  assert(0 == graphAdjListSetEdge(graph, 4, 4, 0));
  assert(0 == graphAdjListSetEdge(graph, 4, 3, 2));
  graphAdjListPrintEdge(graph);

  /*
    0 -> [ 0,  0] -> [ 4, -5]
    1 -> [ 1,  0] -> [ 0,  5] -> [ 2,  2] -> [ 2,  3] -> [ 3,  9]
    2 -> [ 2,  0] -> [ 3,  1]
    3 -> [ 3,  0]
    4 -> [ 4,  0] -> [ 3,  2]
  */

  graphAdjList_t* graph_with_neg_cycle = graphAdjListGen(6);

  assert(0 == graphAdjListSetEdge(graph_with_neg_cycle, 0, 0, 0));
  assert(0 == graphAdjListSetEdge(graph_with_neg_cycle, 0, 4, -5));

  assert(0 == graphAdjListSetEdge(graph_with_neg_cycle, 1, 1, 0));
  assert(0 == graphAdjListSetEdge(graph_with_neg_cycle, 1, 0, 5));
  assert(0 == graphAdjListSetEdge(graph_with_neg_cycle, 1, 2, 2));
  assert(0 == graphAdjListSetEdge(graph_with_neg_cycle, 1, 2, 3));
  assert(0 == graphAdjListSetEdge(graph_with_neg_cycle, 1, 3, 9));

  assert(0 == graphAdjListSetEdge(graph_with_neg_cycle, 2, 2, 0));
  assert(0 == graphAdjListSetEdge(graph_with_neg_cycle, 2, 3, 1));

  assert(0 == graphAdjListSetEdge(graph_with_neg_cycle, 3, 3, 0));

  assert(0 == graphAdjListSetEdge(graph_with_neg_cycle, 4, 4, 0));
  assert(0 == graphAdjListSetEdge(graph_with_neg_cycle, 4, 3, 2));
  assert(0 == graphAdjListSetEdge(graph_with_neg_cycle, 4, 5, 1));

  assert(0 == graphAdjListSetEdge(graph_with_neg_cycle, 5, 5, 0));
  assert(0 == graphAdjListSetEdge(graph_with_neg_cycle, 5, 4, -2));
  graphAdjListPrintEdge(graph_with_neg_cycle);

  /*
    0 -> [ 0,  0] -> [ 4, -5]
    1 -> [ 1,  0] -> [ 0,  5] -> [ 2,  2] -> [ 2,  3] -> [ 3,  9]
    2 -> [ 2,  0] -> [ 3,  1]
    3 -> [ 3,  0]
    4 -> [ 4,  0] -> [ 3,  2] -> [ 5,  1]
    5 -> [ 5,  0] -> [ 4, -2]
  */

  result_t* result;
  result = find_shortest_path_bellmanford(graph, 0);
  ASSERT_INT_ARRAY(TEST_GRAPH_0_SHORTEST, result->shortestPath_, result->num);
  ASSERT_INT_ARRAY(TEST_GRAPH_0_PREV, result->shortestPathPrevVertex_, result->num);

  result = find_shortest_path_bellmanford(graph, 1);
  ASSERT_INT_ARRAY(TEST_GRAPH_1_SHORTEST, result->shortestPath_, result->num);
  ASSERT_INT_ARRAY(TEST_GRAPH_1_PREV, result->shortestPathPrevVertex_, result->num);

  result = find_shortest_path_bellmanford(graph_with_neg_cycle, 0);
  assert(result == NULL);

  printf("\nComplete\n");
}
