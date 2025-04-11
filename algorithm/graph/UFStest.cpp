#include<iostream>
#include"UnionFindSet.h"

using namespace std;

class P8654蓝桥杯2017国C合根植物 {
public:
	static const int MAX = 1000;
	int m, n;
	int pre[MAX];

	void init(int n) {
		for (int i = 1; i <= n; i++) {
			pre[i] = i;
		}
	}

	int find_pre(int key) {
		if (pre[key] == key) return key;
		return find_pre(pre[key]);
	}

	void unio(int n, int m) {
		int rootx = find_pre(m);
		int rooty = find_pre(n);
		if (rootx != rooty)pre[rootx] = rooty;
	}

	int main1() {
		int x, y, line;
		cin >> x >> y >> line;
		init(m * n);

		for (int i = 0; i < line; i++) {
			cin >> x >> y;
			unio(x, y);
		}

		int ans = 0, a[MAX] = { 0 };
		for (int i = 1; i <= m * n; i++) {
			a[find_pre(i)] = 1;
		}
		for (int i = 1; i <= m * n; i++) {
			if (a[i])ans++;
		}
		cout << ans << endl;

		return 0;
	}
};

int main() {
	P8654蓝桥杯2017国C合根植物 test;
	test.main1();
}