#pragma once

#include "PetriNet.h"

const int Num = 15;
struct TrieNode{
    bool IsWord; //判断是否是单词
	//int marking_number_;
	TrieNode* next[Num];
	VectorXi marking_;
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
				location->next[marking(i)] = new TrieNode();
			}
			location = location->next[marking(i)];
		}
		//location->IsWord = true;
	}

	TrieNode* insert(VectorXi marking, int marking_number) {
		TrieNode* location = root;
		for (int i = 0; i < marking.size(); i++) {
			if (location->next[marking(i)] == nullptr) {
				TrieNode* temp = new TrieNode();
				location->next[marking(i)] = temp;
			}
			location = location->next[marking(i)];
		}
		//location->IsWord = true;
		//location->marking_number_ = marking_number;
		location->marking_ = marking;
		return location;
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

	TrieNode* search(VectorXi marking, int a = 0) {
		TrieNode* location = root;
		for (int i = 0; i < marking.size(); i++) {
			if (location->next[marking(i)] == nullptr) {
				return nullptr;  // 如果路径不存在，直接返回 false
			}
			location = location->next[marking(i)];
		}
		return location;
	}

};