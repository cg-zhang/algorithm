#include <bits/stdc++.h>

using namespace std;

#define n 10000

vector<int> arr(n + 1);

/*
* 单点查询 + 单点修改
* 查询：原数组为arr，直接按照lowbit计算即可
* 修改：将对应位加上val
*/
int tree[n + 1];
// 构建树状数组
void init() {
	for (int i = 1; i <= n; ++i) {
		update(i, arr[i]);
	}
}
// 取出最低位的1
int lowbit(int x) {
	return x & -x;
}
// 单点更新
void update(int x, int val) {
	for (int i = x; i <= n; i += lowbit(i)) {
		tree[i] += val;
	}
}
// 单点查询
int getSum(int x) {
	int sum = 0;
	for (int i = x; i > 0; i -= lowbit(i)) {
		sum += tree[i];
	}
	return sum;
}

/*
* 单点查询 + 区间修改
* 查询：原数组为arr，设d[i] = a[i] - a[i - 1]，则求a[i]可通过d[i]的前缀和查询
* 修改：当修改区间[l, r]时，只需给d[l]加上delta，d[r + 1]减去delta即可（差分思想）
*/
int d[n + 1]; // 维护差分数组d

// 更新树状数组，val是变化量
void add(int idx, int val) {
	for (int i = idx; i <= n; i += lowbit(i)) {
		d[i] += val;
	}
}
// 区间修改
void range_Add(int l, int r, int delta) {
	// 差分思想
	add(l, delta);
	add(r + 1, -delta);
}
// 树状数组初始化
void init() {
	for (int i = 1; i <= n; ++i) {
		// i及其后加上差分
		add(i, arr[i] - arr[i - 1]);
	}
}
// 单点查询
int query(int x) {
	int ans = 0;
	// 计算d的前缀和即可
	while (x) {
		ans += d[x];
		x -= lowbit(x);
	}
	return ans;
}

/*
* 区间查询 + 区间修改
* 查询：S = arr[1] + arr[2] + ... + arr[n]
          = d[1] + (d[1] + d[2]) +...+(d[1] + d[2] + ... + d[n])
          = n * d[1] +(n - 1) * d[2] + ... +1 * d[n]
          = (n + 1) * (d[1] + d[2]+...+ d[n]) - (1 * d[1] + 2 * d[2] + ... + n * d[n])
		因此可用一个辅助数组c来维护c[i] = i * d[i]的值
* 修改：当修改区间[l, r]时，需给d[l]加上delta，d[r + 1]减去delta，c[l]加上idx * delta，c[r + 1]加上-idx * delta
*/

// 注意：区间求和数据较大，可能需要long long

int d[n + 1]; // 维护差分
int c[n + 1]; // 维护i * d[i]的树状数组

// 单点修改
void add(int idx, int delta) {
	for (int i = idx; i <= n; i += lowbit(i)) {
		d[i] += delta;
		c[i] += idx * delta;
	}
}
// 区间修改
void range_Add(int l, int r, int delta) {
	add(l, delta);
	add(r + 1, -delta);
}
// 单点查询
int query(int idx) {
	int ans = 0;
	for (int i = idx; i > 0; i -= lowbit(i)) {
		ans += (idx + 1) * d[i] - c[i];
	}
	return ans;
}
// 区间查询
int range_Query(int l, int r) {
	return query(r) - query(l - 1);
}
// 初始化
void init() {
	for (int i = 1; i <= n; ++i) {
		add(i, arr[i] - arr[i - 1]);
	}
}