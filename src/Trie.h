#ifndef TRIE_H
#define TRIE_H

#include "map.h"



using namespace std;

struct TrieNode {

    HashTable<TrieNode> childNode;
    bool endOfWord;
    TrieNode();
};

class Trie {

    TrieNode* root;

public:
    Trie();
    void insert(string word);
    bool search(string word);
    void recursiveDelete(TrieNode* root);
    ~Trie();
};

#endif
