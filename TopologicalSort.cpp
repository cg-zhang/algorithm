#include <bits/stdc++.h>

using namespace std;

const int maxn = 1000;
const int INF = 0x3fffff;

vector<int> in(maxn);   // 每个点的入度
vector<vector<int>> graph(maxn, vector<int>(maxn));    // 邻接矩阵

void TopologicalSort() {
	queue<int> q;
	for (int i = 1; i < maxn; ++i) {
		if (in[i] == 0) {
			q.push(i);
		}
	}
	while (!q.empty()) {
		int t = q.front();
		q.pop();
		// 输出节点信息
		for (int i = 1; i < maxn; ++i) {
			// 存在t -> i 这条边
			if (graph[t][i] != INF && --in[i] == 0) {
				q.push(i);
			}
		}
	}
	return;
}