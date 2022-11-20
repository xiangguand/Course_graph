#ifndef GRAPH_ADH_MAT_H_
#define GRAPH_ADH_MAT_H_


#define INFINITE_WEIGHT  (-1)

typedef struct _adjMatrixUnit_t
{
  int weight;
} adjMatrixUnit_t;

typedef struct _graphAdjMatrix_t
{
  adjMatrixUnit_t **adjMatrix_; //! num X num
  int num_;
} graphAdjMatrix_t;


graphAdjMatrix_t *graphAdjMatrixGen(int num);
int graphAdjMatrixSetEdge(graphAdjMatrix_t *graph, int src, int dst, int weight);
int graphAdjMatrixGetEdge(graphAdjMatrix_t *graph, int src, int dst, int *weight);
int graphAdjMatrixPrintEdge(graphAdjMatrix_t *graph);






#endif /* GRAPH_ADH_MAT_H_ */
