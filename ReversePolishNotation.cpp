#include <bits/stdc++.h>

// 定义运算符优先级
unordered_map<char, int> d{ {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };   

string convertReversePolishNotation(string s) {
	stack<char> op;
	string ans;
	for (const auto& c : s) {
		if (c == '(') {
			op.push(c);  // 左括号进栈
		}
		else if (c == ')') {
			// 将括号之间的符号弹出
			while (op.top() != '(') {
				ans += op.top();
				op.pop();
			}
			// 弹出左括号
			op.pop();
		}
		else if (isdigit(c)) {
			ans += c;    // 数字直接输出
		}
		else {
			// 弹出栈顶优先级大于当前操作符的运算符
			while (!op.empty() && d[op.top()] >= d[c]) {
				ans += op.top();
				op.pop();
			}
			op.push(c);
		}
	}
	// 弹出剩余操作符
	while (!op.empty()) {
		ans += op.top();
		op.pop();
	}
	return ans;
}