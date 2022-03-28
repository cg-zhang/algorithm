#include <bits/stdc++.h>

using namespace std;

const int maxn = 100;

struct edge {
	int u, v, cost;
	edge() = default;
	edge(int from, int to, int c): u(from), v(to), cost(v) {};
};

// 顶点个数和边的个数
int n, m;
int father[maxn];

// 找根节点同时进行路径压缩
int find(int x) {
	return father[x] == x ? x : father[x] = find(father[x]);
}


void Kruskal() {
	// 存储m条边
	vector<edge> graph(m);
	// 将边按照cost大小排序
	sort(graph.begin(), graph.end(), [&](const auto& a, const auto& b) {
		return a.cost < b.cost;
		});
	// 初始化并查集
	for (int i = 1; i <= n; ++i) {
		father[i] = i;
	}
	// 遍历每条边，进行选择
	int ans = 0; // 路径长度
	for (int i = 0; i < m; ++i) {
		int x = find(graph[i].u);
		int y = find(graph[i].v);
		// 每次选最小的路径，不能与已选路径成环
		if (x != y) {
			father[x] = y;
			ans += graph[i].cost;
		}
	}
}

