/**
 * @file lab4.cpp
 * @author : Tianze Li
 * @description Doubly LinkedList implementation in C++
 * @date modified 2025-02-16
 */
//startercode_begins
#include<iostream>
#include<string>
#include<sstream>
#include<iomanip>
using namespace std;


class Node
{
	private:
		string elem; //data element (type string in this case)
		Node* next; //Link (pointer) to the next Node
		Node* prev; //Link (pointer) to the previous Node
		friend class DoublyLinkedList;
		
	public:
		Node(): next(NULL), prev(NULL)
		{}
		Node(string elem) : elem(elem),next(NULL), prev(NULL)
		{}
};
//==============================================================
class DoublyLinkedList
{
	private:
		Node* head; 	// pointer to the head of List
		Node* tail; 	// pointer to the tail of List
	public:
		DoublyLinkedList (); // constructor to create dummy head and tail nodes
		~DoublyLinkedList (); // destructor to clean up all nodes
		bool isEmpty() const; // return true if the list is empty
		const string& front() const; // returns the const reference of the element from the first valid Node of list, throw an exception if the list is empty
		const string& back() const;  // returns the const reference of the element from last valid Node of the list, throw an exception if the list is empty
		void addFront(const string& elem); // add a new node to the front of list (after head)
		void addBack(const string & elem); //add a new node to the back of the list (before tail)
		void removeFront(); // remove front node from list, throw an exception if the list is empty
		void removeBack();  // remove last node from list, throw an exception if the list is empty
		void reverseList();	// reverse the list
		bool isPalindrome() const; //return true if the list is Palindrome, false otherwise
		void display() const;	// display all element of the list
};
//===================================
void listCommands()
{
	cout<<"List of available Commands:"<<endl
		<<"display            : Display the Doubly Linked List"<<endl
		<<"front              : Display the first element of the List"<<endl
		<<"back               : Display the last element of the List"<<endl
		<<"addFront <elem>    : Add a new Node at the beginning of the List"<<endl
		<<"addBack  <elem>    : Add a new Node at the end of the List"<<endl
		<<"removeFront        : Remove the first Node of the Linked List"<<endl
		<<"removeBack         : Remove the last Node of the Linked List"<<endl	
		<<"isEmpty            : Check if the List is empty?"<<endl
		<<"reverse            : Reverse the Linked List"<<endl
		<<"isPalindrome       : Check if the List is Palindrome or not?"<<endl
		<<"help               : Display the list of available commands"<<endl
		<<"exit               : Exit the Program"<<endl;
}
//===================================
int main()
{
	DoublyLinkedList myList;
	listCommands();
	string user_input;
	string command;
	string parameter;


	do
	{
		cout<<">";
		getline(cin,user_input);

		// parse user-input into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,parameter);

		try
		{
			if(command=="display" or command=="d") 				myList.display();
			else if(command=="front" or command=="f")			cout<<"Front = "<<myList.front()<<endl;
			else if(command=="back" or command=="b")			cout<<"Back = "<<myList.back()<<endl;
			else if(command=="addFront" or command=="af")		myList.addFront(parameter),myList.display();
			else if(command=="addBack"	or command=="ab")		myList.addBack(parameter),myList.display();
			else if(command=="removeFront" or command=="rf")	myList.removeFront(),myList.display();
			else if(command=="removeBack" or command=="rb")		myList.removeBack(),myList.display();
			else if(command=="isEmpty"	or command=="ise")		cout<<"List is "<<(myList.isEmpty()? "Empty":"Not Empty")<<endl;
			else if(command=="reverse"	or command=="r")		myList.reverseList(),myList.display();
			else if(command=="isPalindrome" or command=="isp")	cout<<"List is "<<(myList.isPalindrome()? "Palindrome":"Not Palindrome")<<endl;
			else if(command == "help" or command=="h")			listCommands();
			else if(command == "exit" or command=="e")			break;
			else 												cout<<"Invalid Commad !!"<<endl;
		}
		catch(exception &e)
		{
			cout<<"Exception: "<<e.what()<<endl;
		}

	}while(command!="exit" and command!="quit");

	return EXIT_SUCCESS;
}
//============================================================
#ifdef _WIN32
void DoublyLinkedList::display() const
{
	Node *curr=head;
	while(curr!=NULL)
	{
		cout<<"+------";
		curr=curr->next;
	}
	cout<<"+"<<endl<<"|";
	curr=head;
	while(curr!=NULL)
	{
		if (curr == head)		cout<<" Head |";
		else if(curr == tail)	cout<<" Tail |";
		else 					cout<<setw(5)<<curr->elem<<" |";
	
		curr=curr->next;
	}
	curr=head;
	cout<<endl;
	while(curr!=NULL)
	{
		cout<<"+------";
		curr=curr->next;
	}
	cout<<"+"<<endl;
}
//====================================================================
#else
void DoublyLinkedList::display() const
{
	Node *curr=head;
	while(curr!=NULL)
	{
		cout<<"╔══════╗    ";
		curr=curr->next;
	}
	cout<<endl<<"║";
	curr=head;
	while(curr!=NULL)
	{
		if (curr == head)		cout<<" Head ║<══>║";
		else if(curr == tail)	cout<<" Tail ║";
		else 					cout<<setw(6)<<curr->elem<<"║<══>║";
	
		curr=curr->next;
	}
	curr=head;
	cout<<endl;
	while(curr!=NULL)
	{
		cout<<"╚══════╝    ";
		curr=curr->next;
	}
	cout<<endl;
}
#endif
//startercode_ends
//===========================================================
//Constructor to create Sentinel (dummy) nodes
DoublyLinkedList::DoublyLinkedList ()
{
	//create dummy head node
	head = new Node();  
	//create dummy tail node
    tail = new Node();  
	//head points to tail
    head->next = tail;  
	//tail points back to head
    tail->prev = head;  
}
//============================================================
DoublyLinkedList::~DoublyLinkedList () 
{
	//loops through the list if it is not empty
	while (!isEmpty()) {
		//remove all nodes until the list is empty
        removeFront();  
    }
	//delete the dummy head node
    delete head;  
	//delete the dummy tail node
    delete tail;  

}
//============================================================
bool DoublyLinkedList::isEmpty() const 
{
	//list is empty if head points directly to tail
	return head->next == tail;  
}
//============================================================
const string& DoublyLinkedList::front() const 
{
	//validates to make sure list is not empty or else throws an error
	if (isEmpty()) {
        throw runtime_error("List is Empty");
    }
	//return the element of the first valid node
    return head->next->elem;  
}
//============================================================
const string& DoublyLinkedList::back() const 
{
	//validates to make sure list is not empty or else throws an error
	if (isEmpty()) {
        throw runtime_error("List is Empty");
    }
	//return the element of the last valid node
    return tail->prev->elem;  
}
//============================================================
void DoublyLinkedList::addFront(const string& elem) 
{
	//create a new node
	Node* newNode = new Node(elem);  
	//new node points to the current first node
    newNode->next = head->next;      
	//new node's previous is head
    newNode->prev = head;            
	//current first node's previous is new node
    head->next->prev = newNode;      
	//head points to the new node
    head->next = newNode;            
}
//============================================================
void DoublyLinkedList::addBack(const string& elem) 
{
	//create a new node
	Node* newNode = new Node(elem);  
	//new node's previous is the current last node
    newNode->prev = tail->prev;      
	//new node points to tail
    newNode->next = tail;            
	//current last node points to new node
    tail->prev->next = newNode;      
	//tail's previous is new node
    tail->prev = newNode;            
}
//============================================================
void DoublyLinkedList::removeFront() 
{
	//validates to make sure list is not empty or else throws an error
	if (isEmpty()) {
        throw runtime_error("List is Empty");
    }
	//node to be removed
    Node* oldNode = head->next;  
	//head points to the next node
    head->next = oldNode->next;  
	//next node's previous is head
    oldNode->next->prev = head;  
	//delete the old node
    delete oldNode;              
}
//============================================================
void DoublyLinkedList::removeBack() 
{
	//validates to make sure list is not empty or else throws an error
    if (isEmpty()) {
        throw runtime_error("List is Empty");
    }
	//node to be removed
    Node* oldNode = tail->prev;  
	//tail's previous is the previous node
    tail->prev = oldNode->prev;  
	//previous node's next is tail
    oldNode->prev->next = tail; 
	//delete the old node 
    delete oldNode;             
}
//============================================================
void DoublyLinkedList::reverseList() 
{
	//validates to make sure list is not empty or else throws an error
	if (isEmpty()) {
        throw runtime_error("List is Empty");
    }
    Node* current = head->next;
    Node* temp = nullptr;
	//loops through the whole list
    while (current != tail) {
		//swap next and prev pointers
		//temp stores the prev pointer
        temp = current->prev;   
		//make the prev pointer the next pointer       
        current->prev = current->next;
		//make the next pointer the prev pointer
        current->next = temp;
		//move to the next node as prev is next because we swapped before
        current = current->prev;       
    }
	//swap head and tail pointers
    temp = head->next;    
	//make the head next pointer become tails prev pointer            
    head->next = tail->prev;
	//make tail prev pointer become head next pointer
    tail->prev = temp;
	//update the new first node's previous
    head->next->prev = head;          
	//update the new last node's next
    tail->prev->next = tail;          
}
//============================================================
bool DoublyLinkedList::isPalindrome() const
{
	//validates to make sure list is not empty or else throws an error
	if (isEmpty()) {
        throw runtime_error("List is Empty");
    }
    Node* forward = head->next;
    Node* backward = tail->prev;
	//loops the forward pointer foward and the backward pointer backwards if the two pointers
	//don't past each other
    while (forward != backward && forward->prev != backward) {
        //checks if the elements foward and backward are the same
		if (forward->elem != backward->elem) {
			//not a palindrome if elements don't match
            return false;  
        }
        forward = forward->next;
        backward = backward->prev;
    }
	//list is a palindrome
    return true;  
}
