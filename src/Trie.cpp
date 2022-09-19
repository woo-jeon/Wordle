#include "Trie.h"
#include <string>

Trie::Trie() {
    root = new TrieNode();
}

TrieNode::TrieNode() {
    endOfWord = false;
}

//Inserts word into the trie data structure
void Trie::insert(string word) {
    TrieNode* current = root;
    for (int i = 0; i < (int)word.size(); ++i) {
        //if key does not exists, create TrieNode for that key
        if (current->childNode.find(word.at(i)) == current->childNode.end(word.at(i))) {
            TrieNode* temp = new TrieNode();
            current->childNode.insert(word.at(i), temp);
        }
        current = current->childNode.at(word.at(i));
    }
    current->endOfWord = true;
}

//Returns true if word exists in the trie
bool Trie::search(string word) {
    TrieNode* current = root;
    for (int i = 0; i < (int)word.size(); ++i) {
        if (current->childNode.find(word.at(i)) == current->childNode.end(word.at(i)))
            return false;
        else
            current = current->childNode.at(word.at(i));
    }
    //This checks that the last character is the end of a word
    if (current->endOfWord == true)
        return true;
    else
        return false;
}

void Trie::recursiveDelete(TrieNode *root) {
    for (auto it = root->childNode.table->begin(); it != root->childNode.table->end(); it++) {
        recursiveDelete(it->second);
        delete it->second;
    }
}

//Trie destructor
Trie::~Trie() {
    recursiveDelete(root);
}
