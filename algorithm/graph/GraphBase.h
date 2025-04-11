#pragma once
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "Edge.h"
#include "Node.h"

using namespace std;

class Graph {
public:
    // serial number & practical structure
    unordered_map<int, Node*>* nodes;
    unordered_set<Edge*>* edges;

    Graph() {
        nodes = new unordered_map<int, Node*>();
        edges = new unordered_set<Edge*>();
    }

    ~Graph() {
        delete nodes;
        delete edges;
    }
};
