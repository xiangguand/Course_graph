#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "graph_adj_list.h"

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

  assert(1 == graph->adjList_[0]->dst_);
  assert(1 == graph->adjList_[0]->weight_);
  assert(2 == graph->adjList_[0]->next_->dst_);
  assert(3 == graph->adjList_[0]->next_->weight_);
  
  assert(4 == graph->adjList_[1]->dst_);
  assert(7 == graph->adjList_[1]->weight_);
  
  assert(3 == graph->adjList_[2]->dst_);
  assert(2 == graph->adjList_[2]->weight_);
  assert(4 == graph->adjList_[2]->next_->dst_);
  assert(2 == graph->adjList_[2]->next_->weight_);
  
  assert(4 == graph->adjList_[3]->dst_);
  assert(9 == graph->adjList_[3]->weight_);
  
  assert(3 == graph->adjList_[4]->dst_);
  assert(9 == graph->adjList_[4]->weight_);

  return 0;
}
