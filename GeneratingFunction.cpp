#include <bits/stdc++.h>

const int maxn = 1000;

/*
* 每个数构成表达式(1 + x ^ nums[i])，指数表示能够组合出来的数，系数表示权重，也就是方案数
* n个数组合即为(1 + x ^ nums[0]) * (1 + x ^ nums[1]) * ... * (1 + x ^ nums[n - 1])
*/

void generating_Function(vector<int>& nums) {
	int n = nums.size();
	// 数组范围为题目要求或者不可能通过累加得到的和
	vector<int> s(maxn, 0);
	vector<int> t(maxn, 0);
	// 初始化第一个表达式，也即(1 + x ^ nums[0])
	// 循环表示当前数可选多次，如果只能选一次只须初始化s[0]和s[nums[0]]
	for (int i = 0; i < maxn; i += nums[0]) {
		s[i] = 1;   // 对应每位的权重
	}
	// 遍历后面n - 1个表达式
	for (int i = 1; i < n; ++i) {
		// 每次将前面累乘的表达式与当前表达式相乘
		// 这里的相乘是对应指数系数的累加
		for (int j = 0; j < maxn; ++j) {
			for (int k = 0; j + k < maxn; k += nums[i]) {
				// 当前表达式每个指数对应的权重，可选多次
				t[j + k] += s[j];
			}
			// s保存累乘结果，t用于暂存
			s = t;
			fill(t.begin(), t.end(), 0);
		}
	}
}
