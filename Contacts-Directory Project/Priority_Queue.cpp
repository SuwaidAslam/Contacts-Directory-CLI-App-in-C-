#include "Priority_Queue.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
//Min Priority Queue is being used to just arrange data alphabetically

template <typename T, typename N, typename E>
void Priority_Queue<T,N,E>::Enqueue(T item, N item2, int priority, E item3)
{
    queue_node<T,N,E> *tmp, *q;
    tmp = new queue_node<T,N,E>;
    tmp->data1 = item;
    tmp->data2 = item2;
    tmp->priority = priority;
    tmp->data3 = item3;
    if (front == NULL || priority < front->priority)
    {
        tmp->next = front;
        front = tmp;
    }
    else
    {
        q = front;
        while (q->next != NULL && q->next->priority <= priority)
            q=q->next;
        tmp->next = q->next;
        q->next = tmp;
    }
}

template <typename T, typename N, typename E>
bool Priority_Queue<T,N,E>::Delete(T k)
{
    queue_node<T,N,E> *tmp = front;
    queue_node<T,N,E> *p = front;
    if(front == NULL)
        cout<<"Contacts Directory is Empty!!\n";
    
    if(front->data1 ==  k){
        front = front->next;
        delete tmp;
        return true;
	}
    else
    {
    	queue_node<T,N,E> *next;
        while(tmp!= NULL){
        	if(tmp->data1 == k){
        		next = tmp->next;
        		p->next = next;
        		delete tmp;
        		return true;
			}
			p = tmp;
			tmp = tmp->next;
		}
    }
    return false;
}

template <typename T, typename N, typename E>
void Priority_Queue<T,N,E>::display()
{
	system("CLS");
	cout<<"\n\t\t================================\n\t\t\tLIST OF CONTACTS\n\t\t================================\n";
    queue_node<T,N,E> *ptr;
    ptr = front;
    if (front == NULL)
        cout<<"Contacts Directory is Empty!\n";
    else
    {
        while(ptr != NULL)
        {
        	cout<<"===========================================================\n\n";
        	cout<<"Name  : "<<ptr->data1<<endl;
			cout<<"Phone : "<<ptr->data2<<endl;
			cout<<"Email : "<<ptr->data3<<endl;
            ptr = ptr->next;
        }
    }
}

template <typename T, typename N, typename E>
bool Priority_Queue<T,N,E>::Edit(T k, T data1, N data2, E data3)
{
    queue_node<T,N,E> *tmp = front;
    if(front == NULL)
        cout<<"Contacts Directory is Empty!\n";
    
    if(front->data1 ==  k){
        (data1=="-1") ? tmp->data1: tmp->data1 = data1;
		(data2=="-1") ? tmp->data2 : tmp->data2 = data2;
		(data3=="-1") ? tmp->data3 : tmp->data3 = data3;
		return true;
	}
    else
    {
        while(tmp!= NULL){
        	if(tmp->data1 == k){
        		(data1=="-1") ? tmp->data1: tmp->data1 = data1;
				(data2=="-1") ? tmp->data2 : tmp->data2 = data2;
				(data3=="-1") ? tmp->data3 : tmp->data3 = data3;
        		return true;
			}
			tmp = tmp->next;
		}
    }
    return false;
}

template <typename T, typename N, typename E>
bool Priority_Queue<T,N,E>::Search(string name, string num){
    queue_node<T,N,E> *ptr;
    ptr = front;
    if (front == NULL)
        return false;
    else
    {
        while(ptr != NULL)
        {
        	if(ptr->data1 == name){
        		return true;
			}
            ptr = ptr->next;
        }
        ptr = front;
        while(ptr != NULL)
        {
        	if(ptr->data2 == num){
        		return true;
			}
            ptr = ptr->next;
        }
    }
    return false;
}

template <typename T, typename N, typename E>
void Priority_Queue<T,N,E>::Save(string fn){
	ofstream outfile;
	outfile.open(fn.c_str(), ios::trunc);
	if (!outfile) { // If can't open
		abort(); // Exit
	}
	else {
		queue_node<T,N,E> *ptr;
		ptr = front;
		if (front == NULL)
		    return ;
		else
		{
		    while(ptr != NULL)
		    {
		    	outfile << ptr->data1 << "," << ptr->data2 <<"," <<ptr->priority<<"," <<ptr->data3<<endl;
		        ptr = ptr->next;
		    }
		}
		outfile.close();
	}
}

template <typename T, typename N, typename E>
void Priority_Queue<T,N,E>::Load(string fn){
	T d1; N d2; E d3;
	string str;
	ifstream fin(fn.c_str()); // Open and read file
	if (!fin) { // If can't open 
		ofstream wfile;
		wfile.open(fn.c_str(), ios::trunc);//Create new file
		wfile.close();
	}
	else{
		try {
			while(getline(fin, str)) {
				string p;
				unsigned int i = str.find(",");
				d1 = str.substr(0 , i).c_str();
				str = str.substr(i + 1);
				
				i = str.find(",");
				d2 = str.substr(0 , i).c_str();
				str = str.substr(i + 1);
				
				i = str.find(",");
				p = str.substr(0 , i).c_str();
				d3 = str.substr(i + 1).c_str();
				Enqueue(d1, d2, stoi(p),d3);
			}
	}
	catch (...) {
		fin.close();
		return;
	}
	fin.close();
	}
}
