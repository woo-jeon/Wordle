#include <iostream>
#include <list>
#include <string.h>

using namespace std;

struct TrieNode;

template <typename T>
struct HashTable // collision resolution : separate chaining // module 7
{
	static const int size = 35; // 80% of this is 28, our map will never reach a load factor above 80%
	list<pair<char,T*>> table[size];
	
	int count;
	float loadFactor;
	float maxLoadFactor;

	public:

	HashTable();
	T* at(char key);
	int hashFunction(char key);
	void insert(char key, T* node);
	bool overRide(int key, T* node);


    typename list<pair<char, T*>>::iterator find(char key)// find returns an iterator of the keys spot or end of table
	{
		int hashKey = hashFunction(key);// funny pun: hashKey -> huskey
		auto& pairCell = table[hashKey];// link list at array slot
		list<pair<char, TrieNode*>>::iterator temp = pairCell.end();
		for (auto i = pairCell.begin(); i != pairCell.end(); i++)
		{
			if (i->first == key)
			{
				temp = i;
				break;
			}
		}
		return temp;
	}

	typename list<pair<char, T*>>::iterator end(char key)// find returns an iterator of the keys spot or end of table
	{
		int hashKey = hashFunction(key);// funny pun: hashKey -> huskey
		auto& pairCell = table[hashKey];// link list at array slot
		list<pair<char, TrieNode*>>::iterator temp = pairCell.end();
		return temp;
	}
};


// =================== Hash Table functions =================== // 
template <typename T>
HashTable<T>::HashTable()
{
	count = 0;
	maxLoadFactor = 1.0f;
	loadFactor = count/maxLoadFactor;
}

template <typename T>
int HashTable<T>::hashFunction(char key)
{
	return (int)key % size; // return ascii code of a letter thens mod it by total size
}

template <typename T>
void HashTable<T>::insert(char key, T* node)
{
	int hashValue = hashFunction(key);
	
	if (overRide(hashValue, node) == false)// if no key is found, we create a new list in our array
	{
		auto& pairCell = table[hashValue];//notice the reference symbol
		pairCell.emplace_back(key, node);
		count++;
		loadFactor = count / maxLoadFactor;//if load goes over max, will never happen in this case cause of the alphabet being 26 letters long this hash would only be 26 letters long, we have space for 35

	}

}

template <typename T>
bool HashTable<T>::overRide(int key, T* node)//override exisiting key's values
{
	bool temp = false;
	auto& pairCell = table[key];// link list at array slot
	for (auto i = pairCell.begin(); i != pairCell.end(); i++)
	{
		if (i->first == key)
		{
			temp = true;
			i->second = node;
			break;
		}

	}
	return temp;

}

template <typename T>
T* HashTable<T>::at(char key)
{
	T* result = nullptr;
	int hashKey = hashFunction(key);
	auto& pairCell = table[hashKey];// link list at array slot
	auto tempItr = find(key);
	if (tempItr != pairCell.end())
	{
		for (auto i = pairCell.begin(); i != pairCell.end(); i++)
		{
			if (i == tempItr)
			{
				return i->second;
				break;
			}
		}
	}
	else {
		throw std::out_of_range("No Key Found");
	}

	return result;
}
