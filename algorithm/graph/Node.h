#pragma once
#include <iostream>
#include <vector>
using namespace std;

// ǰ������ Edge ��
class Edge;

class Node {
public:
    int value;
    int in;  // in-degree
    int out; // out-degree
    vector<Node*>* nexts;
    vector<Edge*>* edges;

    Node() {

    }

    Node(int value) {
        this->value = value;
        in = 0;
        out = 0;
        nexts = new vector<Node*>();
        edges = new vector<Edge*>();
    }

    ~Node() {
        delete nexts;
        delete edges;
    }
};

