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
    // ��ʼ�� graph
    Graph* graph = new Graph();  // �����ﴴ��һ���µ� Graph ����

    for (int i = 0; i < matrix.size(); i++) {
        int weight = matrix[i][0];
        int from = matrix[i][1];
        int to = matrix[i][2];

        // ����ڵ㲻���ڣ��򴴽��µĽڵ�
        if (graph->nodes->find(from) == graph->nodes->end()) {
            graph->nodes->insert({ from, new Node(from) });
        }
        if (graph->nodes->find(to) == graph->nodes->end()) {
            graph->nodes->insert({ to, new Node(to) });
        }

        // ��ȡ�ӽڵ�͵��ڵ��ָ��
        Node* fromNode = graph->nodes->at(from);
        Node* toNode = graph->nodes->at(to);

        // �����µı߲����½ڵ������
        Edge* newEdge = new Edge(weight, fromNode, toNode);
        fromNode->nexts->push_back(toNode);
        fromNode->out++;
        toNode->in++;
        fromNode->edges->push_back(newEdge);
        graph->edges->insert(newEdge);
    }

    return graph;
}
