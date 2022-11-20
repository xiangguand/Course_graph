#ifndef GRAPH_ADH_LIST_H_
#define GRAPH_ADH_LIST_H_

#define INFINITE_WEIGHT (-1)

typedef struct _adjListUnit_t
{
  int dst_;
  int weight_;
  struct _adjListUnit_t* next_;
} adjListUnit_t;

typedef struct _graphAdjList_t
{
  adjListUnit_t** adjList_;
  int num_;
} graphAdjList_t;

graphAdjList_t* graphAdjListGen(int num);
adjListUnit_t* graphAdjListUnitGen(int dst, int weight);
int graphAdjListSetEdge(graphAdjList_t* graph, int src, int dst, int weight);
int graphAdjListGetEdge(graphAdjList_t* graph, int src, int dst, int* weight);
int graphAdjListPrintEdge(graphAdjList_t* graph);

#endif /* GRAPH_ADH_LIST_H_ */
