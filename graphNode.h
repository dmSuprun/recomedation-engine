//
// Created by Dima on 16/08/2024.
//

#ifndef RECENG_GRAPHNODE_H
#define RECENG_GRAPHNODE_H

#include "user.h"
#include "film.h"
#include <variant>
#include <vector>


struct graphNode {
    int vertexId;
    std::variant<film *, user *> data;
    std::vector<graphNode *> adjacentNodes;

    graphNode(film *const filmInf);

    graphNode(user *const userInf);
};


#endif //RECENG_GRAPHNODE_H
