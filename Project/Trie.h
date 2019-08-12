#ifndef __TRIE_H__
#define __TRIE_H__ 

#include <bits/stdc++.h> 
using namespace std;
#define ALPHABET_SIZE 30
class Trie{
private:
	Trie *children[ALPHABET_SIZE]; 
	bool visited; 
	int timestamp; 

public:
	Trie *getNode(void);
	void insert(Trie *root, string key, int timestamp);
	int search(Trie *root, string key, int timestamp);
	int getIndex(char V);
	bool isEmpty(Trie *root);
	Trie *remove(Trie *root, string key, int depth = 0);
	void createTrie(Trie *root, vector<string> &v, vector<int> &timestamp);
	void searchTrie(Trie *root, vector<string> &strings, vector<int> &timestamp, bool round);
	void deleteTrie(Trie *root, const vector<string> previous);
	

	enum output_type{
		MODIFIED = 1,
		DELETED = 2,
		ADDED = -1
	};
};

#endif