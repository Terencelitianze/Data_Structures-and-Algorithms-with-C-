//============================================================================
// Name         : lab3.cpp
// Author       : Tianze Li
// Version      : 1.0
// Date Created : 02/08/25
// Date Modified: 02/09/25
// Description  : Singly Linked-List implementation in C++
//============================================================================
//starter_code_begins
#include<iostream>
#include<string>
#include<fstream>
#include<exception>
#include<sstream>
using namespace std;
//====================================
class Node
{
	private:
		int elem; //data element 
		Node* next; //Link (pointer) to the next Node
		
	public:
		Node(int elem) : elem(elem), next(NULL)
		{}
		friend class MyLinkedList ;
};
//=====================================
class MyLinkedList
{
	private:
		Node* head; // pointer to the head of list
	public:
		MyLinkedList (); // empty list constructor
		~MyLinkedList (); // destructor to clean up all nodes
		bool empty() const; // is list empty?
		void addFront(int elem); // add a new Node at the front of the list
		void removeFront(); // remove front Node from the list
		void remove(int elem);	 // remove the first occurrence of an element of the list, if the element exists.
		unsigned int countElem(int elem) const; //count frequency of an element in the list
		int getIndexOf(int elem) const; //returns first index of an element in the list, -1 if the element is not present
		void display() const;
		void readData(string); //read a file and load it into the linked list
		void writeData(string) const; //write the linked list to a file
};
//=====================================
void listCommands()
{
	cout<<"List of available Commands:"<<endl
		<<"display            : Display the Linked List"<<endl
		<<"addFront <element> : Add <element> to the front of the Linked List"<<endl
		<<"removeFront        : Remove the front node of the Linked List"<<endl
		<<"remove        	  : Remove the first occurrence of an element of the list (if exists)"<<endl
		<<"count <element>    : count frequency of an element in the list"<<endl
		<<"indexOf <element>  : return first index of an element in the list (-1 of not present)"<<endl
		<<"read <file_name>   : Load the data from <file> and add it into the Linked List"<<endl
		<<"write <file_name>   : Dump the contents of the Linked list to <file>"<<endl
		<<"help               : Display the list of available commands"<<endl
		<<"exit               : Exit the Program"<<endl;
}
//=======================================
// main function
int main()
{
	MyLinkedList myList;

	listCommands();
	string user_input;
	string command;
	string parameter;

	do
	{
		cout<<">";
		getline(cin,user_input);
		
		// parse user input into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,parameter);
		
		if(command=="display") 				myList.display();
		else if(command=="addFront" or command=="af")				myList.addFront(stoi(parameter)),myList.display();
		else if(command=="removeFront" or command=="rf")			myList.removeFront(),myList.display();
		else if(command=="remove" or command=="r")         			myList.remove(stoi(parameter)),myList.display();
		else if(command=="count")			cout<<parameter<<" occurs "<<myList.countElem(stoi(parameter))<<" time(s) in the list"<<endl;
		else if(command=="indexOf")         cout<<"First index of "<<parameter<<" in the list is: "<<myList.getIndexOf(stoi(parameter))<<endl;
		else if(command=="read")			myList.readData(parameter),myList.display();
		else if(command == "write")			myList.writeData(parameter);
		else if(command == "help")			listCommands();
		else if(command == "exit")			break;
		else 								cout<<"Invalid Commad !!"<<endl;
	}while(command!="exit");

	return EXIT_SUCCESS;
}
//====================================
// constructor
MyLinkedList::MyLinkedList ()
{
	this->head = NULL;
}
//starter_code_ends
//====================================
// destructor to clean up all nodes
MyLinkedList::~MyLinkedList () 
{
	// loops through the linked list and sets the condition so while head does not equal NULL 
	// it will delete the nodes in the linked list using removeFront() function.
	while (head != NULL) {
        removeFront();
    }
}
//====================================
// Check if the list is empty or not
bool MyLinkedList::empty() const 
{
	//returns true if head points to NULL which means it returns true if the linked list is empty 
	return head == NULL;
}
//====================================
// add a node at the front of list
void MyLinkedList::addFront(int elem)
{
	// initalises a new node using pointer
	Node* newNode = new Node(elem);
	// first make the new node point to the node that the head is pointing to
	newNode->next = head;
	// then make the head point to the new node
	head = newNode;
}
//====================================
// remove the first node from the list
void MyLinkedList::removeFront()
{
	// validates to check that the list is not empty so you can delete using the empty function
	if (empty()){
		cout << "Error: List is empty. Cannot remove front node." << endl;
        return;
	}
	//intialises an temp node and make it point to what the head points to
	Node* temp = head;
	// then make the head point to the second node in the linked list
    head = head->next;
	// then delete the temp node which was the first node of the original linked list
    delete temp;
}
//=====================================
// remove the first occurrence of an element of the list, if the element exists
void MyLinkedList::remove(int elem)
{
	// validates to check that the list is not empty so you can delete using the empty function
	if (empty()) {
        cout << "Error: List is empty. Cannot remove element." << endl;
        return;
    }
	//intialises a node called current and make it point to what head points to
	Node* current = head;
	//intialises a node called previous and make it point to NULL
    Node* previous = NULL;

	// loop using a while loop while current is not at the end of the linked list
	// and the element that the current node stores is not the targeted element
    while (current != NULL && current->elem != elem) {
		//make the previous node point to what current node points to (so increment by one)
        previous = current;
		// and the current node points to the next node
        current = current->next;
    }

	//outputs a error message if the element that user want to delete is not found in the list
	//checks if current has reached the end of the linked list with current == NULL
    if (current == NULL) {
        cout << "Error: Element " << elem << " not found in the list." << endl;
        return;
    }

	//if the target to delete is at the head of the list then head will point to the second node
    if (previous == NULL) {
        head = current->next;
    } else { // if the target is in the middle of the list then the previous node will point 
			//to the next node of the current node, making sure the list is not broken when the 
			//current node is deleted
        previous->next = current->next;
    }

	// deletes the target node that the user wants to delete
    delete current;
	// outputs to the user saying that the target node has been successfully removed
    cout << "First occurrence of " << elem << " has been successfully deleted from the list." << endl;
}
//====================================
// count frequency of an element in the list
unsigned int MyLinkedList::countElem(int elem) const
{
	//intialises a variable call count and sets it to 0
	unsigned int count = 0;
	//intialises a node called current and make it point to what head points to
	Node* current = head;
	// while current node did not reach the end of the list
	while (current != NULL) {
		//if the element of the current node equals value of the target element then count
		// is incremented by one
        if (current->elem == elem) {
            count++;
        }
		// make the current node point to the next node in the linked list
        current = current->next;
    }
	// returns the value of the count variable
    return count;
}
//==============================================
// get first index of an element in the the list.
// returns -1 if the element is not present
int MyLinkedList::getIndexOf(int elem) const
{
	//intialises a variable called index and sets it to 0
	int index = 0;
	//intialises a node called current and make it point to what head points to
	Node* current = head;
	// while current node did not reach the end of the list
	while (current != NULL){
		//if the element of the current node equals value of the target element then index is returned
		if (current->elem == elem){
			return index;
		}
		// make the current node point to the next node in the linked list
		current = current->next;
		//index increments by one if the target node is not found yet
		index++;
	}
	//returns -1 is the target element is not found in the linked list
	return -1;
}
//==============================================
// display all nodes of the linked list
void MyLinkedList::display() const
{
	//intialises a node called current and make it point to what head points to
	Node* current = head;
	//outputs "head ->"
	cout<<"head->";
	// while current node did not reach the end of the list
	while (current != NULL) {
		//outputs the element of the current node
		cout<<current->elem<<"->";
		// make the current node point to the next node in the linked list
		current = current->next;
	}
	//outputs NULL 
	cout<<"NULL"<<endl;
}
//==============================================
//Load data from a file and add it to the Linked List
void MyLinkedList::readData(string path)
{
	//calls the ifstream which allows reading of the desired file
	ifstream file(path);
	//validates if the file can be opened, if not output a error message
	if (!file.is_open()){
		cout << "Error: Unable to open file " << path << endl;
        return;
	}
	//intialises a variable called elem
	int elem;
	//reads the file and stores any integer that it reads onto elem
	while (file>>elem){
		//uses the addFront() function to add the element that has been read from the file into
		// the linked list
		addFront(elem);
	}
	//closes the file 
	file.close();
}
//=============================================
//Dump/write the contents of the list to a file
void MyLinkedList::writeData(string path) const
{
	// uses the ofstream which allows writing of file
	ofstream file(path);
	//validates if the file can be opened, if not output a error message
	if (!file.is_open()) {
        cout << "Error: Unable to open file " << path << endl;
        return;
    }
	//intialises a node called current and make it point to what head points to
	Node* current = head;
	// while current node did not reach the end of the list
	while (current != NULL){
		//write the element of the current node onto the file and goes to the next line
		file<<current->elem<<endl;
		// make the current node point to the next node in the linked list
		current = current->next;
	}
	//closes the file
	file.close();
	//outputs a message fro user stating that the linked list has been written onto desired file
	cout << "Records have been exported to " << path << endl;
}
//==================================================

