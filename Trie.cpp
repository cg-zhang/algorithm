#include <bits/stdc++.h>

using namespace std;

struct trie {
	bool isEnd;
	vector<trie*> next;
	trie() : isEnd(false), next(26, nullptr) {};
};

void buildTree(trie* root, const string& str) {
	trie* node = root;
	// ������
	for (const auto& c : str) {
		int i = c - 'a';
		if (node->next[i] == nullptr) {
			node->next[i] = new trie();
		}
		node = node->next[i];
	}
	// �ַ���ĩβ�����
	node->isEnd = true;
	return;
}

trie* root;

int main() {
	string s;
	root = new trie();
	buildTree(root, s);
}