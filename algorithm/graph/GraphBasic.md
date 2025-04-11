## 图算法基础

#### 一，图模板（有/无向图）（邻接表/邻接矩阵）

##### GraphBase.h

```c++
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

```



##### Node.h

```c++
#pragma once
#include <iostream>
#include <vector>
using namespace std;

// 前向声明 Edge 类
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


```

##### Edge.h

```c++
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

```

大面积使用指针的主要目的是为了**避免不必要的深拷贝**，提高性能和灵活性，**避免栈上对象的生命周期问题**，以及便于在图的节点和边之间进行**共享和相互引用**。尤其是在处理图这样的复杂数据结构时，指针提供了更大的灵活性来高效地管理内存和对象之间的关系。

[第十三章 DFS与BFS（保姆级教学！！超级详细的图示！！）_dfs bfs-CSDN博客](https://blog.csdn.net/weixin_72060925/article/details/128145585)

#### 二，宽度优先遍历（BFS）

√

#### 三，深度优先遍历（DFS）

√

#### 四，拓扑排序

√

找到入度为0的点输出，擦除其及其影响，在剩下的点中找入度为0的点。

#### 五，最小生成树K算法：要求无向图

##### Kurskal

从最小的边（最小堆）开始考虑，添加加边是否形成环。（如何判断成环？——集合查询结构）

{单点集合}判断from，to是否在一个集合中，合并from，to形成{两点集合}。。。如果from，to不在一个集合中，则不会形成环。

```c++
//稍后说明，并查集
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

```

在写上述算法时，所使用的简易并查集实现：

```c++
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
```

#### 5.5 并查集结构（功能实现）（并查集）

##### 1，功能实现：

想办法实现类java.values()获取所有值那样的效果，有两种方法，一种是在实际算法中用auto自动推导，将全部数据先放进pair中，再用pair.second依次获取所有值，一种是直接修改头文件添加自定义的getvalues成员函数。这两种方法实际上大同小异。

###### （1），添加成员函数：

```c++
vector<Node*> getValues(Graph* graph) {
    vector<Node*> nodeValues;
    for (auto& pair : *(graph->nodes)) {
        nodeValues.push_back(pair.second); // pair.second 是 Node* 值
    }
    return nodeValues;
}
```

###### （2），在实际算法中处理：

```c++
algorithmKruskal(Graph* graph) {
	vector<Node*>nodeValues;
	for (auto& pair : *(graph->nodes)) {
		nodeValues.push_back(pair.second);
	}
	UFS unionFind(nodeValues);
}
```

##### 2，并查集

theSerein大佬讲得并查集结构真是使人醍醐灌顶！通透[【算法与数据结构】—— 并查集-CSDN博客](https://blog.csdn.net/the_ZED/article/details/105126583?ops_request_misc=%7B%22request%5Fid%22%3A%220058a3a032a1f25b6e30182bd185e85f%22%2C%22scm%22%3A%2220140713.130102334..%22%7D&request_id=0058a3a032a1f25b6e30182bd185e85f&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-105126583-null-null.142^v102^pc_search_result_base6&utm_term=并查集&spm=1018.2226.3001.4187) 我将以此为蓝本重新规划应用于Node类型的并查集。

```c++
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
```

#### 六，最小生成树P算法

##### Prim

从一个点开始，将之视为已经解锁的点，它的边视为已经解锁的边，将已经解锁的点和已经解锁的边分别放入哈希表和最小堆中，每次分析最小的已经解锁边，边上的to点是否指向一个未解锁的点，如果是，则解锁该点，将当前最小边加入结果Edge哈希集合，将该点的所有边加入最小堆。

```c++
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
```

#### 七，单源最短路径Dijikstra算法

通过每次分析确定（锁）一条最短路径，更新其它最短路径。因此，该**算法可以有权值为负数的边，但是不能有累加和为负数的环。** 如果存在，那么每在该环上转一圈，最短路径都会减少一些，直到变成负无穷。破坏了已经确定的最短路径。

```c++
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
```



最小堆优化：

如果使用自带最小堆，将原本用选择法实现的函数 getMinDistanceAndUnselectedNode 改用最小堆（参数为距离）实现，则在入堆过程中可能更改某些距离，改变了最小堆中既有元素的值，所以需要重写堆。