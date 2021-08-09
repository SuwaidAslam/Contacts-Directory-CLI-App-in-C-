#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
using namespace std;

const int SIZE = 500;

//This node is used for List when collision occurs
template <typename T, typename N, typename E>
struct node
{
    T data;
    N data2;
    E data3;
    node<T,N,E> *next;
};

//This Element is used like an Array element
template <typename T, typename N, typename E>
struct DataElement{
	bool filled = false;
	T data;
	N data2;
	E data3;
	int key;
	node<T,N,E> *next = NULL;
};

template <typename T, typename N, typename E>
class HashTable
{
private:
	DataElement<T, N, E> DataTable[SIZE];
public:
    HashTable();
    int hashCode(T);
	void insert(T, N, E);
	void display();
	N Delete(T);
	bool Search(T);
	void Save(string);
	void Load(string);
	N Edit(T, T, N, E);
};

#endif
