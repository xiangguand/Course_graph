#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph_adj_list.h"

graphAdjList_t* graphAdjListGen(int num)
{
  graphAdjList_t* graph = malloc(sizeof(graphAdjList_t));
  graph->num_ = num;

  graph->adjList_ = malloc(num * sizeof(adjListUnit_t*) * num);
  memset(graph->adjList_, 0, sizeof(adjListUnit_t*) * num);

  return graph;
}

adjListUnit_t* graphAdjListUnitGen(int dst, int weight)
{
  adjListUnit_t* unit = malloc(sizeof(adjListUnit_t));
  unit->next_ = (void*)0;
  unit->dst_ = dst;
  unit->weight_ = weight;

  return unit;
}

int graphAdjListSetEdge(graphAdjList_t* graph, int src, int dst, int weight)
{
  int ret = 0;
  adjListUnit_t* unit = (void*)0;
  if (graph != (void*)0 && src < graph->num_)
  {
    unit = graph->adjList_[src];
    if (unit == (void*)0)
    {
      graph->adjList_[src] = graphAdjListUnitGen(dst, weight);
    }
    else
    {
      while (unit->next_ != (void*)0)
      {
        unit = unit->next_;
      }
      unit->next_ = graphAdjListUnitGen(dst, weight);
    }
  }
  else
  {
    ret = -1;
  }

  return ret;
}

int graphAdjListGetEdge(graphAdjList_t* graph, int src, int dst, int* weight)
{
  int ret = 0;
  adjListUnit_t* unit;
  if (graph != (void*)0 && src < graph->num_ && weight != (void*)0)
  {
    *weight = INFINITE_WEIGHT;
    unit = graph->adjList_[src];
    while (unit != (void*)0)
    {
      if (unit->dst_ == dst)
      {
        *weight = unit->weight_;
        break;
      }
      unit = unit->next_;
    }
  }
  else
  {
    ret = -1;
  }

  return ret;
}

int graphAdjListPrintEdge(graphAdjList_t* graph)
{
  int ret = 0;
  if (graph != (void*)0)
  {
    for (int i = 0; i < graph->num_; i++)
    {
      adjListUnit_t* unit = graph->adjList_[i];
      printf("%2d -> ", i);
      while (unit != (void*)0)
      {
        printf("[%2d, %2d] ", unit->dst_, unit->weight_);
        if (unit->next_ != (void*)0)
        {
          printf("-> ");
        }
        unit = unit->next_;
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
