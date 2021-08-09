#include "HashTable.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
using namespace std;	
//Hashtable is implemented using Seperate chaining collision technique


template <typename T, typename N, typename E>
HashTable<T, N, E>::HashTable()
{}

template <typename T, typename N, typename E>
int HashTable<T,N, E>::hashCode(T key){
	size_t key_hash = std::hash<T>()(key);
	return key_hash % SIZE;
}

template <typename T, typename N, typename E>
void HashTable<T,N, E>::insert(T data, N data2, E data3) {
	bool Notpresent = true;
	//get the hash code
	int hashIndex = hashCode(data);
	//if collision occures add a node (list)
	if(DataTable[hashIndex].filled)
	{
		node<T,N,E> *temp = new node<T,N,E>;
		temp->data = data;
		temp->data2 = data2; 
		temp->data3 = data3; 
		temp->next = NULL;
		if(DataTable[hashIndex].next == NULL)
			DataTable[hashIndex].next = temp;
		else{
			node<T,N,E> *temp1 = DataTable[hashIndex].next;
			while(temp1->next!=NULL)
				temp1 = temp1->next;
			temp1->next = temp;
		}
	} //If collision does not occur then just simply Save data in array element
	else{
	    DataTable[hashIndex].filled = true;
	    DataTable[hashIndex].data = data;
	    DataTable[hashIndex].data2 = data2;
	    DataTable[hashIndex].data3 = data3;
	    DataTable[hashIndex].key = hashIndex;
	}
}

template <typename T, typename N, typename E>
void HashTable<T,N,E>::display(){
	system("CLS");
	cout<<"\n\t\t================================\n\t\t\tLIST OF CONTACTS\n\t\t================================\n";
	int counter = 0;
	for(int i=0;i<SIZE; i++){
		if(DataTable[i].filled != false){
			cout<<"===========================================================\n\n";
			cout<<"Name  : "<<DataTable[i].data<<endl;
			cout<<"Phone : "<<DataTable[i].data2<<endl;
			cout<<"Email : "<<DataTable[i].data3<<endl;
			counter++;
		}
		if(DataTable[i].next != NULL){
				node<T,N,E> *tmp = DataTable[i].next;
				while(tmp!=NULL){
					cout<<"===========================================================\n\n";
					cout<<"Name  : "<<tmp->data<<endl;
					cout<<"Phone : "<<tmp->data2<<endl;
					cout<<"Email : "<<tmp->data3<<endl;
					tmp = tmp->next;
					counter++;
				}
			}
	}
	if(counter==0)
		cout<<"Contacts Directory is Empty!\n";
}

template <typename T, typename N, typename E>
bool HashTable<T,N,E>::Search(T data){
	//get the hash 
	system("CLS");
	cout<<"\n\t\t================================\n\t\t\tCONTACT INFO\n\t\t================================\n";
   int hashIndex = hashCode(data);
   bool Return_val = false;
	if(DataTable[hashIndex].filled ==false && DataTable[hashIndex].next != NULL)
	{
	   	node<T,N,E> *temp1 = DataTable[hashIndex].next;
	   	while(temp1!=NULL){
	   		if(temp1->data == data){
			if(temp1->data2[0] == '+'){
				cout<<"Name  : "<<temp1->data<<endl;
				cout<<"Phone : "<<temp1->data2<<endl;
			}
			else{
				cout<<"Phone : "<<temp1->data<<endl;
				cout<<"Name  : "<<temp1->data2<<endl;
			}
			cout<<"Email : "<<temp1->data3<<endl;
			}
	   		temp1 = temp1->next;
	   		Return_val = true;
		}
		return Return_val;
	}
	else if(DataTable[hashIndex].filled != false){
		if(DataTable[hashIndex].data2[0] == '+'){
				cout<<"Name  : "<<DataTable[hashIndex].data<<endl;
				cout<<"Phone : "<<DataTable[hashIndex].data2<<endl;
			}
			else{
				cout<<"Phone : "<<DataTable[hashIndex].data<<endl;
				cout<<"Name  : "<<DataTable[hashIndex].data2<<endl;
			}
			cout<<"Email : "<<DataTable[hashIndex].data3<<endl;
			Return_val = true;
	}
	
	return Return_val;
}

template <typename T, typename N, typename E>
N HashTable<T,N,E>::Delete(T data){
	N Return_Val;
	//get the hash code
   int hashIndex = hashCode(data);
   if(DataTable[hashIndex].data !=data && DataTable[hashIndex].next != NULL)
	{
	   	node<T,N,E> *temp1 = DataTable[hashIndex].next;
	   	node<T,N,E> *last = NULL;
	   	while(temp1->next!=NULL && temp1->data != data){
	   		last = temp1;
	   		temp1 = temp1->next;
		}
		if(temp1->data == data && last != NULL){
			last->next = temp1->next;
			Return_Val = temp1->data2;
			delete temp1;
			return Return_Val;
		}
		else if(temp1->data == data && last == NULL){
			 DataTable[hashIndex].next = temp1->next;
			 Return_Val = temp1->data2;
			delete temp1;
			return Return_Val;
		}
	}
	else if(DataTable[hashIndex].filled == false && DataTable[hashIndex].next != NULL){
		node<T,N,E> *temp1 = DataTable[hashIndex].next;
	   	node<T,N,E> *last = NULL;
	   	while(temp1->next!=NULL && temp1->data != data){
	   		last = temp1;
	   		temp1 = temp1->next;
		}
		if(temp1->data == data && last != NULL){
			last->next = temp1->next;
			Return_Val = temp1->data2;
			delete temp1;
			return Return_Val;
		}
		else if(temp1->data == data && last == NULL){
			 DataTable[hashIndex].next = temp1->next;
			 Return_Val = temp1->data2;
			delete temp1;
			return Return_Val;
		}
	}
	else if(DataTable[hashIndex].filled == true && DataTable[hashIndex].data == data){
		Return_Val = DataTable[hashIndex].data2;
   		DataTable[hashIndex].filled = false;
   		return Return_Val;
	}
	return "-1";
}

template <typename T, typename N, typename E>
N HashTable<T,N,E>::Edit(T data, T data1, N data2, E data3){
	N Return_Val;
	//get the hash code
   int hashIndex = hashCode(data);
   if(DataTable[hashIndex].data !=data && DataTable[hashIndex].next != NULL)
	{
	   	node<T,N,E> *temp1 = DataTable[hashIndex].next;
	   	while(temp1->next!=NULL && temp1->data != data){
	   		temp1 = temp1->next;
		}
		if(temp1->data == data){
			Return_Val = temp1->data2;
			if(data1 != "-1" && data1 != temp1->data){
				insert(data1, temp1->data2, temp1->data3);
				Delete(data);
			}else{
				(data1=="-1") ? temp1->data : temp1->data = data1;
				(data2=="-1") ? temp1->data2 : temp1->data2 = data2;
				(data3=="-1") ? temp1->data3 : temp1->data3 = data3;
			}
			return Return_Val;
		}
	}
	else if(DataTable[hashIndex].filled == true && DataTable[hashIndex].data == data){
		Return_Val = DataTable[hashIndex].data2;
		if(data1 != "-1" && data1 != DataTable[hashIndex].data){
			insert(data1, DataTable[hashIndex].data2, DataTable[hashIndex].data3);
			Delete(data);
		}else{
			(data1=="-1") ? DataTable[hashIndex].data  : DataTable[hashIndex].data = data2;
			(data2=="-1") ? DataTable[hashIndex].data2 : DataTable[hashIndex].data2 = data2;
			(data3=="-1") ? DataTable[hashIndex].data3 : DataTable[hashIndex].data3 = data3;
		}
   		return Return_Val;
	}
	else
		return "-1";
}

template <typename T, typename N, typename E>
void HashTable<T,N,E>::Save(string fn){
	ofstream outfile;
	outfile.open(fn.c_str(), ios::trunc);
	if (!outfile) { // If can't open
		abort(); // Exit
	}
	else {
		//Output Hash Table data into txt file
		for(int i=0;i<SIZE; i++){
		if(DataTable[i].filled != false){
			outfile << DataTable[i].data << "," << DataTable[i].data2 <<"," << DataTable[i].data3<<endl;
		}
		if(DataTable[i].next != NULL){
				node<T,N,E> *tmp = DataTable[i].next;
				while(tmp!=NULL){
					outfile << tmp->data << "," << tmp->data2 <<"," << tmp->data3<<endl;
					tmp = tmp->next;
				}
			}
		}
		outfile.close();
	}
}

template <typename T, typename N, typename E>
void HashTable<T,N,E>::Load(string fn){
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
				unsigned int i = str.find(",");
				d1 = str.substr(0 , i);
				str = str.substr(i + 1);
				
				i = str.find(",");
				d2 = str.substr(0 , i);
				d3 = str.substr(i + 1);
				insert(d1, d2, d3);
			}
	}
	catch (...) {
		fin.close();
		return;
	}
	fin.close();
	}
}

