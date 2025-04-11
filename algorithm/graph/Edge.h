#pragma once
#include <iostream>
#include "Node.h"
#include <vector>
using namespace std;

class Edge {
public:
    int weight;
    Node* from;
    Node* to;

    Edge(int weight, Node* from, Node* to) {
        this->weight = weight;
        this->from = from;
        this->to = to;
    }
};
