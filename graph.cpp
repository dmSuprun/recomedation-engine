#include "graph.h"

void graph::addNode(film *const filmInf) {
    graphNode *temp = new graphNode(filmInf);
    adjacentList.insert(std::make_pair(temp->vertexId, temp));

}

void graph::addNode(user *const userInf) {
    graphNode *temp = new graphNode(userInf);
    adjacentList.insert(std::make_pair(temp->vertexId, temp));
}
bool graph::checkExistenceInGraph(int vertexId) {
    auto t = adjacentList.find(vertexId);
    if (t != adjacentList.end()){
        return true;
    }
    return false;
}


bool graph::checkAdjacent(int FirstVertexId, int secondVertexId) {
    std::vector<graphNode*> AdjacentNodes;

    getAdjacentNodes(FirstVertexId, AdjacentNodes);
    for(auto a:AdjacentNodes){
        if(a->vertexId == secondVertexId){
            return true;
        }
    }
    return false;

}

void graph::addEdge(int graphFrom, int graphTo) {
    graphNode *graph1 = adjacentList.at(graphFrom);
    graphNode *graph2 = adjacentList.at(graphTo);
    graph1->adjacentNodes.push_back(graph2);
    graph2->adjacentNodes.push_back(graph1);
}

void graph::removeNode(int nodeId) {
    graphNode *graph = adjacentList.at(nodeId);
    for (auto i: graph->adjacentNodes) {
        std::vector<graphNode *>::iterator position = std::find(i->adjacentNodes.begin(), i->adjacentNodes.end(),
                                                                graph);
        if (position != i->adjacentNodes.end()) // == myVector.end() means the element was not found
            i->adjacentNodes.erase(position);
    }
    adjacentList.erase(adjacentList.find(graph->vertexId));
    delete graph;

}

void graph::removeEdge(int nodeFromId, int nodeToId) {
    graphNode *graphFrom = adjacentList.at(nodeFromId);
    graphNode *graphTo = adjacentList.at(nodeToId);


    std::vector<graphNode *>::iterator position = std::find(graphFrom->adjacentNodes.begin(),
                                                            graphFrom->adjacentNodes.end(),
                                                            graphTo);
    if (position != graphFrom->adjacentNodes.end()) // == myVector.end() means the element was not found
        graphFrom->adjacentNodes.erase(position);
    position = std::find(graphTo->adjacentNodes.begin(), graphTo->adjacentNodes.end(),
                         graphFrom);
    if (position != graphTo->adjacentNodes.end()) // == myVector.end() means the element was not found
        graphTo->adjacentNodes.erase(position);

}

void graph::getAdjacentNodes(int nodeId, std::vector<graphNode *> &vectorForResults) {
    graphNode *graph = adjacentList.at(nodeId);
    std::vector<graphNode *> res;
    for (auto i: graph->adjacentNodes) {
        res.push_back(i);
    }
    vectorForResults = res;
}

void graph::viewGraph() {
    for (auto i: adjacentList) {
        std::cout << i.first << " - ";
        for (int j = 0; j < i.second->adjacentNodes.size(); j++) {
            std::cout << (i.second->adjacentNodes[j]->vertexId);

        }
        std::cout << std::endl;
    }
}

void graph::destroy() {
    std::vector<int> keys;
    for (auto i: adjacentList) {
        keys.push_back((i.second->vertexId));
    }
    for (auto i: keys) {
        removeNode(i);

    }
}

graph::~graph() {
    destroy();
}


