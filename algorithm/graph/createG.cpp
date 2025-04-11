#include "graphBase.h"
#include<iostream>

using namespace std;
//weight from to
vector<vector<int>> matrix = {
    {5,0,1},
    {3,1,2},
    {7,0,2},
};

Graph* createGraph(vector<vector<int>> matrix) {
    // 初始化 graph
    Graph* graph = new Graph();  // 在这里创建一个新的 Graph 对象

    for (int i = 0; i < matrix.size(); i++) {
        int weight = matrix[i][0];
        int from = matrix[i][1];
        int to = matrix[i][2];

        // 如果节点不存在，则创建新的节点
        if (graph->nodes->find(from) == graph->nodes->end()) {
            graph->nodes->insert({ from, new Node(from) });
        }
        if (graph->nodes->find(to) == graph->nodes->end()) {
            graph->nodes->insert({ to, new Node(to) });
        }

        // 获取从节点和到节点的指针
        Node* fromNode = graph->nodes->at(from);
        Node* toNode = graph->nodes->at(to);

        // 创建新的边并更新节点的属性
        Edge* newEdge = new Edge(weight, fromNode, toNode);
        fromNode->nexts->push_back(toNode);
        fromNode->out++;
        toNode->in++;
        fromNode->edges->push_back(newEdge);
        graph->edges->insert(newEdge);
    }

    return graph;
}
