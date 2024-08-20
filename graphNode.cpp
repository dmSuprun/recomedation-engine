//
// Created by Dima on 16/08/2024.
//

#include "graphNode.h"

graphNode::graphNode(film *const filmInf) {
    data = filmInf;
    vertexId = filmInf->Id;
};

graphNode::graphNode(user *const userInf) {
    data = userInf;
    vertexId = userInf->Id;
};