#pragma once
#include<iostream>
#include<vector>
#include<unordered_map>

#include"GraphBase.h"
#include"Node.h"
using namespace std;

class UFS {
public:
	unordered_map<Node*, vector<Node*>> setMap;
	UFS(vector<Node* >nodes) {
		for (Node* cur : nodes) {
			vector<Node*> set;
			set.push_back(cur);
			setMap.insert({ cur,set });
		}
	}

	bool isSameSet(Node* from, Node* to) {
		vector<Node*> fromSet = setMap.find(from)->second;
		vector<Node*> toSet = setMap.find(to)->second;
		//检查集合的内存地址是否相等，依此判断是否为同一个集合
		return fromSet == toSet;
	}

	void unionSet(Node* from, Node* to) {
		vector<Node*> fromSet = setMap.find(from)->second;
		vector<Node*> toSet = setMap.find(to)->second;

		/*for (Node* toNode : toSet) {
			fromSet.push_back(toNode);
			setMap.insert({ toNode, fromSet });
		}*/

		// 将 toSet 中的节点添加到 fromSet 中
		fromSet.insert(fromSet.end(), toSet.begin(), toSet.end());

		// 更新 setMap 中 toSet 所有元素的集合为 fromSet
		for (Node* toNode : toSet) {
			setMap[toNode] = fromSet;
		}
	}
};

class newUFS {
	//指定并查集能够包含的元素个数，由题意决定
	static const int N = 1000;

	unordered_map<Node*, Node*> preNode;
	unordered_map<Node*, int>nodeRanks;

	newUFS(vector<Node*> nodes) {
		for (Node* node : nodes) {
			preNode[node] = node;
			nodeRanks[node] = 1;
		}
	}

	Node* find(Node* node) {
		if (preNode[node] == node) return node;
		return find(preNode[node]);
	}

	bool isSame(Node* from, Node* to) {
		return find(from) == find(to);
	}

	bool join(Node* from, Node* to) {
		from = find(from);
		to = find(to);
		if (from == to) return false;
		if (nodeRanks[from] > nodeRanks[to]) {
			preNode[to] = from;
		}
		else {
			if (nodeRanks[from] == nodeRanks[to]) {
				nodeRanks[to]++;
			}
			preNode[from] = to;
		}
		return true;
	}
};

