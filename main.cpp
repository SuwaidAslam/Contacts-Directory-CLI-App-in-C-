#include <iostream>
#include <conio.h>
#include "HashTable.h"
#include "HashTable.cpp"
#include "Priority_Queue.h"
#include "Priority_Queue.cpp"
#include <string>
#include <regex>
using namespace std;

class Contact_Directory{
	private:
		HashTable<string, string, 	string> Name; //For Hashing By name
		HashTable<string, string, string> Number; //For Hashing By number
		Priority_Queue<string, string, string> P_Queue; //To arrange Alphabetically
	public:
		Contact_Directory();
		~Contact_Directory();
		void Menu();
		void Add();
		void Display();
		void Search();
		void Delete();
		int Priority(string);
		void Edit();
		bool Name_pattern_checker(string); //For inputed Name
		bool Phone_pattern_checker(string); //For inputed Phone
		bool Email_pattern_checker(string); //For inputed Email

};


Contact_Directory::Contact_Directory(){
	//Loads all of the data when program executes for the first time
	Name.Load("Names.txt");
	Number.Load("Numbers.txt");
	P_Queue.Load("Aranged.txt");
}
Contact_Directory::~Contact_Directory(){
	//Saves all the data when we exit our program
	Name.Save("Names.txt");
	Number.Save("Numbers.txt");
	P_Queue.Save("Aranged.txt");
}

void Contact_Directory::Menu(){
	bool Runing = true;
	int option = 0;
	while(Runing)
	{
		system("CLS");
		cout<<"\t\t===================================\n\t\t\tCONTACTS DIRECTORY MENU\n\t\t===================================\n";
		cout << "\t\t\t1-Add Contact\n";
		cout << "\t\t\t2-Delete Contact\n";
		cout << "\t\t\t3-Display all Contacts\n";
		cout << "\t\t\t4-Search Contact\n";
		cout << "\t\t\t5-Edit Contact\n";
		cout << "\t\t\t6-Exit\n";
		cout << "Enter Option: ";
		cin >> option;
		switch(option) {
		case 1:{
			Add();
			break;
		}
		case 2:{
			Delete();
			getch();
			break;
		}
		case 3:{
			Display();
			getch();
			break;
		}
		case 4:{
			Search();
			break;
		}
		case 5:{
			Edit();
			getch();
			break;
		}
		case 6:{
			Runing = false;
			break;
		}
		default:{
			cerr << "Invalid Choice!";
			getch();
		}
		}
	}
}

void Contact_Directory::Add(){
	bool runing;
	string v, n, e;
	bool option =1;
	while(option==1){
		runing = true;
		while(runing){
			cout<<"Enter Name (First Middle Last | First Last): ";
			cin.ignore();
			getline(cin, v);
			if(Name_pattern_checker(v)){
				runing = false;
			}
			else{
				cout <<"Please enter Name in Specified format.\n";
				getch();
			}
		}
		runing = true;
		while(runing){
			cout<<"Enter Num (+92-xxx-xxxxxxx ): ";
			cin>>n;
			if(Phone_pattern_checker(n)){
				runing = false;
			}
			else{
				cout<<"Please enter Phone Number in Specified format.\n";
				getch();
			}
		}
		if(P_Queue.Search(v,n)){
			cout<<"\t!!Contact with this name or Number is Already Saved in the Directory!\n";
			getch();
			break;
		}
		runing = true;
		while(runing){
			cout<<"Enter Email ID (example@mail.com): ";
			cin>>e;
			if(Email_pattern_checker(e)){
				runing = false;
			}
			else{
				cout <<"Please Enter Email in Specified format.\n";
				getch();
			}
		}
		int p = Priority(v);
		Name.insert(v,n,e);
		Number.insert(n,v,e);
		P_Queue.Enqueue(v,n, p, e);
		cout<<"\n\n";
		cout<<"Want to add one more contact? (1/0):";
		cin>>option;
	}
}
void Contact_Directory::Display(){
	cout<<"1 => Display A to Z."<<endl;
	cout<<"2 => Normal Display."<<endl;
	cout<<"Enter Option: ";
	int choose; cin>>choose;
	switch(choose){
		case 1:{
			P_Queue.display();
			break;
		}
		case 2:{
			Name.display();
			break;
		}
		default:{
			cout<<"Invalid Choice!"<<endl;
			break;
		}
	}
}

void Contact_Directory::Search(){
	cout<<"1 => Search with Name."<<endl;
	cout<<"2 => Search with Phone Number."<<endl;
	cout<<"Enter Option: ";
	int choose; cin>>choose;
	switch(choose){
		case 1:{
			string a;
			while(true){
				cout<<"Enter Name (First Middle Last | First Last): ";
				cin.ignore();
				getline(cin, a);
				if(Name_pattern_checker(a))
					break;
				cout<<"Please Enter Name in Specified format."<<endl;
				getch();
			}
			bool present = Name.Search(a);
			if(!present){
				cout<<"This Contact is not in directory. Wanna Add it? (y/n): ";
				char ask;
				cin>>ask;
				if(ask=='y') 
					Add();
				else
					return;
			}
			break;
		}
		case 2:{
			string num;
			while(true){
				cout<<"Enter Num (+92-xxx-xxxxxxx ): ";
				cin>>num;
				if(Phone_pattern_checker(num))
					break;
				cout<<"Please enter Phone Number in Specified format."<<endl;
				getch();
			}
			bool present = Number.Search(num);
			if(!present){
				cout<<"This Contact is not in directory. Wanna Add it? (y/n): ";
				char ask;
				cin>>ask;
				if(ask=='y') 
					Add();
				else
					return;
			}
			break;
		}
		default:{
			cout<<"Invalid Choice!"<<endl;
			break;
		}
	}
	getch();
}

bool Contact_Directory::Name_pattern_checker(string str){
	regex name_patrn ("\\w+\\s\\w+|\\w+\\s\\w+\\s\\w+"); //Expression for Name pattern checking
	if(regex_match (str,name_patrn))
		return true;
	return false;
}

bool Contact_Directory::Phone_pattern_checker(string str){
	regex phone_patrn ("\\+\\d{2}-\\d{3}-\\d{7}"); // Expression for Phone Number pattern checking
	if(regex_match (str,phone_patrn))
		return true;
	return false;
}

bool Contact_Directory::Email_pattern_checker(string str){
	regex email_patrn ("(\\w+\\d*)(\\.|_)?(\\w*\\d*)@(\\w+)(\\.(\\w+))+"); // Expression for Email ID pattern checking
	if(regex_match (str,email_patrn))
		return true;
	return false;
}

void Contact_Directory::Delete(){
	cout<<"1 => Delete with Name."<<endl;
	cout<<"2 => Delete with Phone Number."<<endl;
	cout<<"Enter Option: ";
	int choose; cin>>choose;
	switch(choose){
		case 1:{
			string a;
			while(true){
				cout<<"Enter Name (First Middle Last | First Last): ";
				cin.ignore();
				getline(cin, a);
				if(Name_pattern_checker(a))
					break;
				cout<<"Please Enter Name in Specified format."<<endl;
				getch();
			}
			string pn = Name.Delete(a);
			string nam = Number.Delete(pn);
			bool check = P_Queue.Delete(nam);
			(check)? cout<<"\nContact has been deleted!\n" : cout<<"\nThis Contact Not in Conatacts Directory!\n";
			cout<<"Press any key to continue...";
			break;
		}
		case 2:{
			string num;
			while(true){
				cout<<"Enter Num (+92-xxx-xxxxxxx ): ";
				cin>>num;
				if(Phone_pattern_checker(num))
					break;
				cout<<"Please enter Phone Number in Specified format."<<endl;
				getch();
			}
			string nm = Number.Delete(num);
			Name.Delete(nm);
			bool check = P_Queue.Delete(nm);
			(check)? cout<<"\nContact has been deleted!\n" : cout<<"\nThis Contact Not in Conatacts Directory!\n";
			cout<<"Press any key to continue...";
			break;
		}
		default:{
			cout<<"Invalid Choice!"<<endl;
			break;
		}
	}
}

void Contact_Directory::Edit(){
	string a;
	while(true){
		cout<<"Enter Contact Name to Edit (First Middle Last | First Last): ";
		cin.ignore();
		getline(cin, a);
		if(Name_pattern_checker(a))
			break;
		cout<<"Please Enter Name in Specified format."<<endl;
		getch();
	}
	bool present = Name.Search(a);
	if(!present){
		cout<<"This Contact is not found in Directory!"<<endl;
		getch();
		return;
	}else{
		cout<<"\n\t1=> Edit Name"<<endl;
		cout<<"\t2=> Edit Phone"<<endl;
		cout<<"\t3=> Edit Email"<<endl;
		int c;
		cout<<"Enter Option: ";
		cin>>c;
		switch(c){
			case 1:{
				string v;
				while(true){
					cout<<"Enter Name (First Middle Last | First Last): ";
					cin.ignore();
					getline(cin, v);
					if(Name_pattern_checker(v))
						break;
					cout<<"Please enter Name in Specified format."<<endl;
					getch();
				}
				if(P_Queue.Search(v,"-1")){
				cerr<<"\t!!Contact already exist with this name!."<<endl;
				}
				else{
					string numb = Name.Edit(a,v,"-1","-1");
					Number.Edit(numb, "-1",v,"-1");
					bool check = P_Queue.Edit(a,v,"-1","-1");
					(check)? cout<<"\nContact has been edited Successfully!"<<endl : cout<<"\nThis Contact Not in Conatacts Directory!"<<endl;
				}
				getch();
				cout<<"Press any key to continue...";
				break;
			}
			case 2:{
				string n;
				while(true){
					cout<<"Enter Num (+92-xxx-xxxxxxx ): ";
					cin>>n;
					if(Phone_pattern_checker(n))
						break;
					cout<<"Please enter Phone Number in Specified format."<<endl;
					getch();
				}
				if(P_Queue.Search("-1",n)){
				cerr<<"\t!!Contact already exist with this Phone Number!."<<endl;
				}
				else{
					string numb = Name.Edit(a,"-1",n,"-1");
					Number.Edit(numb,n,"-1","-1");
					bool check = P_Queue.Edit(a,"-1",n,"-1");
					(check)? cout<<"\nContact has been edited Successfully!"<<endl : cout<<"\nThis Contact Not in Conatacts Directory!"<<endl;
				}
				getch();
				cout<<"Press any key to continue...";
				break;
			}
			case 3:{
				cin.ignore();
				string e;
				while(true){
					cout<<"Enter Email ID (example@mail.com): ";
					cin>>e;
					if(Email_pattern_checker(e))
						break;
					cout<<"Please Enter Email in Specified format."<<endl;
					getch();
				}
				string numb = Name.Edit(a,"-1","-1",e);
				Number.Edit(numb,"-1","-1",e);
				bool check = P_Queue.Edit(a,"-1","-1",e);
				(check)? cout<<"\nContact has been edited Successfully!"<<endl : cout<<"\nThis Contact Not in Contacts Directory!"<<endl;
				getch();
				cout<<"Press any key to continue...";
				break;
			}
			default:{
			cout<<"Invalid Choice!"<<endl;
			break;
			}
		}
	}
}

int Contact_Directory::Priority(string s){
	char p = toupper(s[0]);
	return int(p); //Converts the charachter to ascii Value
}

//Main Driver
int main() {
	Contact_Directory cd;
	cd.Menu(); 
	
   return 0;
}
