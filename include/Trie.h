#pragma once

#include "PetriNet.h"

const int Num = 15;
struct TrieNode{
    bool IsWord; //判断是否是单词
	TrieNode* next[Num];
	vector<TrieNode*> chileNodes;
	TrieNode() : IsWord(false), next{} {}
};

class Trie {
private:
	TrieNode* root;
public:
	Trie() {
		this->root = new TrieNode();
	}
	bool isexist = true;

	void insert(VectorXi marking) {
		TrieNode* location = root;
		for (int i = 0; i < marking.size(); i++) {
			if (location->next[marking(i)] == nullptr) {
				this->isexist = false;
				TrieNode* temp = new TrieNode();
				location->next[marking(i)] = temp;
			}
			location = location->next[marking(i)];
		}
		//location->IsWord = true;
	}

	bool search(VectorXi marking) {
		TrieNode* location = root;
		for (int i = 0; i < marking.size(); i++) {
			if (location->next[marking(i)] == nullptr) {
				return false;  // 如果路径不存在，直接返回 false
			}
			location = location->next[marking(i)];
		}
		return location != nullptr && location->IsWord;
	}

};