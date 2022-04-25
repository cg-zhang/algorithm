#include <bits/stdc++.h>

using namespace std;

const int maxn = 1000;
const int inf = 0x3ffff; 

int graph[maxn][maxn];
// 顶点个数和边的个数
int n, m;

// 计算以s为起点到各顶点的最小生成树
void prim(int s) {
    // 离当前点的距离
    int dist[maxn];
    // 标记是否访问过
    bool vis[maxn];
    // 记录每个点的前驱节点，记录最小生成树路径
    vector<int> track;
    // 最小生成树路径长度
    int ans = 0;
    memset(dist, inf, sizeof(dist));
    dist[s] = 0;
    for (int i = 1; i <= n; ++i) {
        int idx, minD = inf;
        // 每一轮选出距离当前点集合最近的点
        for (int j = 1; j <= n; ++j) {
            if (!vis[j] && dist[j] < minD) {
                minD = dist[j];
                idx = j;
            }
        }
        // 标记访问
        vis[idx] = true;
        // 记录路径
        track.push_back(idx);
        ans += minD;
        // 根据当前点扩展未加入的点的距离，新距离为对应边长
        for (int j = 1; j <= n; ++j) {
            // graph[idx][j]为当前j距离已加入集合点的新距离，若更小则更新
            if (!vis[j] && graph[idx][j] < dist[j]) {
                dist[j] = graph[idx][j];
            }
        }
    }
}
