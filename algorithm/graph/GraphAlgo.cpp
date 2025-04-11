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

		//直接使用栈上对象亦可
		queue<Node*>* q = new queue<Node*>();
		unordered_set<Node*>* set = new unordered_set<Node*>();

		//在数据量小时，可以用数组替换哈希表
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

		//直接用栈上元素
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
	//定义最小堆
	bool operator()(Edge* o1, Edge* o2) {
		return o1->weight > o2->weight;
	}
};

class algorithmKruskal {
public:

	unordered_set<Edge*> Kruskal(Graph* graph) {

		//获取所有点，用他们初始化并查集
		vector<Node*>nodeValues;
		for (auto& pair : *(graph->nodes)) {
			nodeValues.push_back(pair.second);
		}
		UFS unionFind(nodeValues);

		//创建边的最小堆，之后从最小边开始依次分析
		priority_queue<Edge*, vector<Edge*>, compare> pq;
		for (Edge* edge : *(graph->edges)) {
			pq.push(edge);
		}

		unordered_set<Edge*> result;
		while (!pq.empty()) {
			Edge* edge = pq.top();
			pq.pop();
			//如果加入这条边，已经连接的点不会成环
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
		//已经解锁的边的最小堆，注意，所有的点所解锁的边都会放进去。
		priority_queue<Edge*, vector<Edge*>, compare> pq;
		//已经解锁的点的集合
		unordered_set<Node*> nodeSet;
		//最小生成树结果边的集合
		unordered_set<Edge*> res;

		//如果不能保证所有点连通，则依次分析每个点
		for (auto& pair : *(graph->nodes)) {
			Node* node = pair.second;
			
			if (nodeSet.find(node) == nodeSet.end()) {
				nodeSet.insert(node);
				//将初始点的所有边放入最小堆
				for (Edge* edge : *(node->edges)) {
					pq.push(edge);
				}

				while (!pq.empty()) {
					//取得最小边
					Edge* edge = pq.top();
					pq.pop();
					Node* toNode = edge->to;
					//判断边上to点是否是已经解锁的点，若未解锁，则将之纳入已经解锁的点集中
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
	//初始化一个哈希表，存储从原点到所有点的距离
	unordered_map<Node*, int> dijkstra1(Node* head) {
		unordered_map<Node*, int> distanceMap;
		distanceMap.insert({ head, 0 });
		//存储已经确定的最小距离，”不再改变“，同时为后续的“找未确定的最小距离的点”的函数提供参数
		unordered_set<Node*> selectedNodes;
		Node* minNode = getMinDistanceAndUnselectedNode(distanceMap, selectedNodes);
		//原点向各个方向延申，
		while (minNode != NULL) {
			//当前minNode进行延申，for循环跑完，原点到minNode最小距离确定
			int distance = distanceMap.find(minNode)->second;
			for (Edge* edge : *(minNode->edges)) {
				Node* toNode = edge->to;
				//检查指向点是否有记录，实际上就是在做更新
				if (distanceMap.find(toNode) == distanceMap.end()) {
					distanceMap.insert({ toNode, distance + edge->weight});
				}
				//判断原点到to点的距离是否可以做更新
				else {
					distanceMap.find(edge->to)->second = min(distanceMap.find(toNode)->second,
						                                     distance + edge->weight);
				}
			}
			//将minNode加入已经确定的点
			selectedNodes.insert(minNode);
			//更新minNode
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