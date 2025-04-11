#include<iostream>
#include<queue>

#include<unordered_set>
#include"GraphBase.h"
#include"Node.h"
using namespace std;

class BreadthFirstSearch {
public:
	void bfs(Node* node) {
		if (node == NULL) {
			return;
		}

		//ֱ��ʹ��ջ�϶������
		queue<Node*>* q = new queue<Node*>();
		unordered_set<Node*>* set = new unordered_set<Node*>();

		//��������Сʱ�������������滻��ϣ��
		q->push(node);
		set->insert(node);
		while (!q->empty()) {
			Node* cur = q->front();
			cout << cur->value;
			for (Node* next : *(cur->nexts)) {
				if (set->find(next)==set->end()) {
					q->push(next);
					set->insert(next);
				}
			}
		}
	}
};

#include<stack>

class DepthFirstSearch {
public:

	void dfs(Node* node) {
		if (node == NULL) {
			return;
		}

		//ֱ����ջ��Ԫ��
		stack<Node*> s;
		unordered_set<Node*> set;

		s.push(node);
		set.insert(node);
		cout << node->value;
		while (!s.empty()) {
			Node* cur = s.top();
			s.pop();
			for (Node* next : *(cur->nexts)) {
				if (set.find(next) == set.end()) {
					s.push(cur);
					s.push(next);
					set.insert(next);
					cout << next->value;
					break;
				}
			}
		}
	}
};

class TopologicalSorting {
public:

	vector<Node*> sortTopo(Graph* graph) {
		unordered_map<Node*, int> inMap;
		queue<Node*> zeroInQueue;

		for (auto& pair : *(graph->nodes)) {
			Node* node = pair.second;
			inMap.insert({ node, node->in });
			if (node->in == 0) {
				zeroInQueue.push(node);
			}
		}

		vector<Node*> result;
		while (!zeroInQueue.empty()) {
			Node* cur = zeroInQueue.front();
			zeroInQueue.pop();
			result.push_back(cur);
			for (Node* next : *(cur->nexts)) {
				inMap.insert({ next, inMap.find(next)->second - 1 });
				if (inMap.find(next)->second == 0) {
					zeroInQueue.push(next);
				}
			}
		}
		return result;
	}
};

#include "UnionFindSet.h"

struct compare {
	//������С��
	bool operator()(Edge* o1, Edge* o2) {
		return o1->weight > o2->weight;
	}
};

class algorithmKruskal {
public:

	unordered_set<Edge*> Kruskal(Graph* graph) {

		//��ȡ���е㣬�����ǳ�ʼ�����鼯
		vector<Node*>nodeValues;
		for (auto& pair : *(graph->nodes)) {
			nodeValues.push_back(pair.second);
		}
		UFS unionFind(nodeValues);

		//�����ߵ���С�ѣ�֮�����С�߿�ʼ���η���
		priority_queue<Edge*, vector<Edge*>, compare> pq;
		for (Edge* edge : *(graph->edges)) {
			pq.push(edge);
		}

		unordered_set<Edge*> result;
		while (!pq.empty()) {
			Edge* edge = pq.top();
			pq.pop();
			//������������ߣ��Ѿ����ӵĵ㲻��ɻ�
			if (!unionFind.isSameSet(edge->from, edge->to)) {
				result.insert(edge);
				unionFind.unionSet(edge->from, edge->to);
			}
		}
		return result;
	}

};

class algorithmPrim {
public:
	unordered_set<Edge*> primMST(Graph* graph) {
		//�Ѿ������ıߵ���С�ѣ�ע�⣬���еĵ��������ı߶���Ž�ȥ��
		priority_queue<Edge*, vector<Edge*>, compare> pq;
		//�Ѿ������ĵ�ļ���
		unordered_set<Node*> nodeSet;
		//��С����������ߵļ���
		unordered_set<Edge*> res;

		//������ܱ�֤���е���ͨ�������η���ÿ����
		for (auto& pair : *(graph->nodes)) {
			Node* node = pair.second;
			
			if (nodeSet.find(node) == nodeSet.end()) {
				nodeSet.insert(node);
				//����ʼ������б߷�����С��
				for (Edge* edge : *(node->edges)) {
					pq.push(edge);
				}

				while (!pq.empty()) {
					//ȡ����С��
					Edge* edge = pq.top();
					pq.pop();
					Node* toNode = edge->to;
					//�жϱ���to���Ƿ����Ѿ������ĵ㣬��δ��������֮�����Ѿ������ĵ㼯��
					if (nodeSet.find(toNode) == nodeSet.end()) {
						nodeSet.insert(toNode);
						res.insert(edge);
						for (Edge* nextEdge : *(toNode->edges)) {
							pq.push(nextEdge);
						}
					}
				}
			}
		}
		return res;
	}

};

class Dijikstra {
public:
	//��ʼ��һ����ϣ���洢��ԭ�㵽���е�ľ���
	unordered_map<Node*, int> dijkstra1(Node* head) {
		unordered_map<Node*, int> distanceMap;
		distanceMap.insert({ head, 0 });
		//�洢�Ѿ�ȷ������С���룬�����ٸı䡰��ͬʱΪ�����ġ���δȷ������С����ĵ㡱�ĺ����ṩ����
		unordered_set<Node*> selectedNodes;
		Node* minNode = getMinDistanceAndUnselectedNode(distanceMap, selectedNodes);
		//ԭ��������������꣬
		while (minNode != NULL) {
			//��ǰminNode�������꣬forѭ�����꣬ԭ�㵽minNode��С����ȷ��
			int distance = distanceMap.find(minNode)->second;
			for (Edge* edge : *(minNode->edges)) {
				Node* toNode = edge->to;
				//���ָ����Ƿ��м�¼��ʵ���Ͼ�����������
				if (distanceMap.find(toNode) == distanceMap.end()) {
					distanceMap.insert({ toNode, distance + edge->weight});
				}
				//�ж�ԭ�㵽to��ľ����Ƿ����������
				else {
					distanceMap.find(edge->to)->second = min(distanceMap.find(toNode)->second,
						                                     distance + edge->weight);
				}
			}
			//��minNode�����Ѿ�ȷ���ĵ�
			selectedNodes.insert(minNode);
			//����minNode
			minNode = getMinDistanceAndUnselectedNode(distanceMap, selectedNodes);
		}
		return distanceMap;
	}

	Node* getMinDistanceAndUnselectedNode(const unordered_map<Node*, int> &distanceMap, 
		                                  const unordered_set<Node*> &selectedNodes) 
	{
		Node* minNode = NULL;
		int minDistance = INT_MAX;
		for (pair<Node*, int> pairs : distanceMap) {
			Node* node = pairs.first;
			int distance = pairs.second;
			if (selectedNodes.find(node) == selectedNodes.end() && distance < minDistance) {
				minNode = node;
				minDistance = distance;
			}
		}
		return minNode;
	}
};