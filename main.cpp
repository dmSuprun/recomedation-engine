#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <variant>

using namespace std;

struct film {
    int Id;
    string filmName;
    string genre;
};

struct user {
    int Id;
    string Name;

};

struct graphNode {
    int vertexId;
    variant< film *, user *> data;
    vector<graphNode *> adjacentNodes;
//    void operator=(graphNode& gr){
//        this->vertexId = gr.vertexId;
//        this->userData = gr.userData;
//        this->filmData = gr.filmData;
//        this->adjacentNodes = gr.adjacentNodes;
//
//    }


    graphNode(film *const filmInf) {
        data = filmInf;
        vertexId = filmInf->Id;
    }

    graphNode(user *const userInf) {
        data = userInf;
        vertexId = userInf->Id;
    }
};

struct graph {
    map<int, graphNode *> adjacentList;


    void addNode(film *const filmInf) {
        graphNode *temp = new graphNode(filmInf);
        adjacentList.insert(make_pair(temp->vertexId, temp));

    }

    void addNode(user *const userInf) {
        graphNode *temp = new graphNode(userInf);
        adjacentList.insert(make_pair(temp->vertexId, temp));
    }

    void addEdge(int graphFrom, int graphTo) {
        graphNode *graph1 = adjacentList.at(graphFrom);
        graphNode *graph2 = adjacentList.at(graphTo);
        graph1->adjacentNodes.push_back(graph2);
        graph2->adjacentNodes.push_back(graph1);
    }

    void removeNode(int nodeId) {
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

    void removeEdge(int nodeFromId, int nodeToId){
        graphNode *graphFrom = adjacentList.at(nodeFromId);
        graphNode *graphTo = adjacentList.at(nodeToId);


        std::vector<graphNode *>::iterator position = std::find(graphFrom->adjacentNodes.begin(), graphFrom->adjacentNodes.end(),
                                                                    graphTo);
        if (position != graphFrom->adjacentNodes.end()) // == myVector.end() means the element was not found
            graphFrom->adjacentNodes.erase(position);
        position = std::find(graphTo->adjacentNodes.begin(), graphTo->adjacentNodes.end(),
                                                                graphFrom);
        if (position != graphTo->adjacentNodes.end()) // == myVector.end() means the element was not found
            graphTo->adjacentNodes.erase(position);

    }

    void getAdjacentNodes(int nodeId, vector<graphNode*>&vectorForResults){
        graphNode* graph = adjacentList.at(nodeId);
        vector<graphNode*> res;
        for(auto i: graph->adjacentNodes){
            res.push_back(i);
        }
        vectorForResults = res;
    }

    void viewGraph() {
        for (auto i: adjacentList) {
            cout << i.first << " - ";
            for (int j = 0; j < i.second->adjacentNodes.size(); j++) {
                cout << (i.second->adjacentNodes[j]->vertexId);

            }
            cout << endl;
        }
    }

    void destroy() {
        vector<int> keys;
        for (auto i: adjacentList) {
            keys.push_back((i.second->vertexId));
        }
        for (auto i: keys) {
            removeNode(i);

        }
    }

    ~graph() {
        destroy();
    }
};


int main() {



    vector<graphNode*>m;

    graph g;
    user u = {1, "dmytro"};
    user u2 = {2, "petro"};

    g.addNode(&u);
    g.addNode(&u2);

    g.addEdge(u.Id, u2.Id);

    g.getAdjacentNodes(1, m);
    for(auto i:m){
        cout<<i->vertexId;
    }


    return 0;
}
