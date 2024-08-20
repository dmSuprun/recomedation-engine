#ifndef RECENG_GRAPH_H
#define RECENG_GRAPH_H
#include "graphNode.h"
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>





struct graph {
    std::map<int, graphNode *> adjacentList;

    bool checkExistenceInGraph(int vertexId);
    bool checkAdjacent(int FirstVertexId, int secondVertexId);
    void addNode(film *const filmInf) ;

    void addNode(user *const userInf);

    void addEdge(int graphFrom, int graphTo);

    void removeNode(int nodeId);

    void removeEdge(int nodeFromId, int nodeToId);

    void getAdjacentNodes(int nodeId, std::vector<graphNode*>&vectorForResults);

    void viewGraph() ;

    void destroy();

    ~graph();
};


#endif //RECENG_GRAPH_H
