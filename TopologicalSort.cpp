#include <bits/stdc++.h>

using namespace std;

const int maxn = 1000;
const int INF = 0x3fffff;

vector<int> in(maxn);   // ÿ��������
vector<vector<int>> graph(maxn, vector<int>(maxn));    // �ڽӾ���

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
		// ����ڵ���Ϣ
		for (int i = 1; i < maxn; ++i) {
			// ����t -> i ������
			if (graph[t][i] != INF && --in[i] == 0) {
				q.push(i);
			}
		}
	}
	return;
}