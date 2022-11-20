#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph_adj_mat.h"

graphAdjMatrix_t* graphAdjMatrixGen(int num)
{
  graphAdjMatrix_t* graph = malloc(sizeof(graphAdjMatrix_t));
  graph->num_ = num;

  graph->adjMatrix_ = malloc(num * sizeof(adjMatrixUnit_t) * num);
  for (int i = 0; i < num; i++)
  {
    graph->adjMatrix_[i] = malloc(num * sizeof(adjMatrixUnit_t*) * num);
    memset(graph->adjMatrix_[i], 0, sizeof(adjMatrixUnit_t*) * num);
    for (int k = 0; k < num; k++)
    {
      graph->adjMatrix_[i][k].weight = INFINITE_WEIGHT;
    }
  }

  return graph;
}

int graphAdjMatrixSetEdge(graphAdjMatrix_t* graph, int src, int dst, int weight)
{
  int ret = 0;
  if (graph != (void*)0)
  {
    graph->adjMatrix_[src][dst].weight = weight;
  }
  else
  {
    ret = -1;
  }

  return ret;
}

int graphAdjMatrixGetEdge(graphAdjMatrix_t* graph, int src, int dst, int* weight)
{
  int ret = 0;
  if (graph != (void*)0 && weight != (void*)0)
  {
    *weight = graph->adjMatrix_[src][dst].weight;
  }
  else
  {
    ret = -1;
  }

  return ret;
}

int graphAdjMatrixPrintEdge(graphAdjMatrix_t* graph)
{
  int ret = 0;
  if (graph != (void*)0)
  {
    printf("   ");
    for (int i = 0; i < graph->num_; i++)
    {
      printf("[%4d]", i);
    }
    printf("\n");
    for (int i = 0; i < graph->num_; i++)
    {
      printf("[%d] ", i);
      for (int j = 0; j < graph->num_; j++)
      {
        if (INFINITE_WEIGHT == graph->adjMatrix_[i][j].weight)
        {
          printf(" INF, ");
        }
        else
        {
          printf("%4d, ", graph->adjMatrix_[i][j].weight);
        }
      }
      printf("\n");
    }
  }
  else
  {
    ret = -1;
  }

  return ret;
}
