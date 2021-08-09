#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include <string>
using namespace std;

template <typename T, typename N, typename E>
struct queue_node
{
	int priority;
	T data1;
	N data2;
	E data3;
	queue_node<T,N,E> *next;
};

template <typename T, typename N, typename E>
class Priority_Queue
{
    private:
        queue_node<T,N,E> *front;
    public:
        Priority_Queue()
        {
            front = NULL;
        }
        void Enqueue(T,N,int,E);
        void display();
        bool Delete(T);
        void Save(string);
		void Load(string);
		bool Edit(T,T,N,E);
		bool Search(string,string);
};

#endif
