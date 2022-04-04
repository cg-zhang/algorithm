#include <bits/stdc++.h>

using namespace std;

const int maxn = 1000;
const int inf = 0x3ffff;

// 边信息
struct edge {
	int from, to, cost;
	edge(int u, int v, int c): from(u), to(v), cost(v) {};
};

// 优先队列中信息
struct HeapNode {
	// 当前到达u点的距离
	int d, u;
	HeapNode(int _d, int _u) : d(_d), u(_u) {};
	// 按照距离从小到大排
	bool operator < (const HeapNode& rhs) const {
		return d > rhs.d;
	}
};

// 顶点个数和边的个数
int n, m;
// 给每个边编号，存储对应边信息
vector<edge> edges;
// 邻接表存储每个节点的边信息，存储的是边的编号，方便直接映射
vector<vector<int>> G(maxn);
// 当前各顶点距离
int dist[maxn];
// 记录当前节点最短边
int pre[maxn];
// 是否访问过
bool vis[maxn];

// 添加新边
void addEdge(int from, int to, int dist) {
	edges.push_back(edge(from, to, dist));
	m = edges.size();
	// from节点连接的边编号
	G[from].push_back(m - 1);
}

// 从源点s出发
void Dijkstra(int s) {
	priority_queue<HeapNode> q;
	// 初始化距离
	for (int i = 0; i <= n; ++i) {
		dist[i] = inf;
	}
	dist[s] = 0;
	memset(vis, false, sizeof(vis));
	q.push(HeapNode(0, s));
	// 每次选择当前已到达节点中最短的那条路径
	while (!q.empty()) {
		auto x = q.top();
		q.pop();
		int u = x.u;
		// 如果已经更新过最短路径，跳过
		if (vis[u]) {
			continue;
		}
		vis[u] = true;
		// 遍历当前点可扩展的边
		for (int i = 0; i < G[u].size(); ++i) {
			// 获取边信息
			edge& e = edges[G[u][i]];
			if (dist[u] + e.cost < dist[e.to]) {
				dist[e.to] = dist[u] + e.cost;
				// 更新前驱节点
				pre[e.to] = G[u][i];
				// 只要更新就加入队列
				q.push(HeapNode(dist[e.to], e.to));
			}
		}
	}
}