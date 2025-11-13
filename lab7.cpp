//============================================================================
// Name         : MyVector.cpp
// Author       : Tianze Li
// Version      : 1.0
// Date Created : 3/08/25
// Date Modified: 3/10/25
// Description  : Vector implmentation in C++
//============================================================================
//start_code_begins
#include<iostream>
#include<cstdlib>
#include<iomanip>
#include <stdexcept>
#include<sstream>

using namespace std;

template <typename T>
class MyVector
{
	private:
		T *array;						//pointer to an array to store elements
		int v_size;						//current size of vector (number of elements in vector)
		int v_capacity;					//capacity of vector
	public:
		MyVector(int cap=0);			//Constructor
		~MyVector();					//Destructor
		int size() const;				//Return current size of vector
		int capacity() const;			//Return capacity of vector
		void reserve(int n);			//increase the capacity of the vector so that it can hold at least n elements
		bool isEmpty() const; 			//Rturn true if the vector is empty, False otherwise
		const T& front();				//Returns reference of the first element in the vector
		const T& back();				//Returns reference of the Last element in the vector
		void push_back(T element);		//Add an element at the end of vector
		void insert(int index, T element); //Add an element at the index 
		void erase(int index);			//Removes an element from the index
		T& operator[](int index);			//Returns the reference of an element at given index
		T& at(int index); 				//return reference of the element at given index
		void shrink_to_fit();			//Reduce vector capacity to fit its size
		void display();
};

void listCommands()
{
	cout<<"List of available Commands:"<<endl
		<<"display                  : Display the Vector"<<endl
		<<"push_back <element>      : Add an element to the end of the vector"<<endl
		<<"insert <index element>   : Insert an element at location index"<<endl
		<<"erase <index>            : Remove the element from index"<<endl
		<<"[index]                  : Returns a reference to an element at a specified index"<<endl
		<<"at <index>               : Returns a reference to an element at a specified index"<<endl
		<<"front                    : Return the (reference of) front element"<<endl
		<<"back                     : Returns a reference to the last element of the vector"<<endl
		<<"size                     : Returns the number of elements in the vector"<<endl
		<<"capacity                 : Returns the capacity of vector"<<endl
		<<"isEmpty                  : Tests if the vector container is empty"<<endl
		<<"shrink                   : Reduce vector capacity to fit its size (shrink_to_fit)"<<endl
		<<"exit/quit                : Exit the Program"<<endl;
}
//=======================================
int main()
{

	MyVector<int> myVector;
	//unitTest();
	string user_input;
	string command;
	string parameter1;
	string parameter2;
	listCommands();

	do
	{
		cout<<">";
		getline(cin,user_input);

		// parse userinput into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,parameter1,' ');
		getline(sstr,parameter2);

		try
		{
			if(command=="display" or command=="d") 							myVector.display();
			else if(command=="push_back" or command=="p" )					myVector.push_back(stoi(parameter1)),myVector.display();
			else if(command=="insert" or command=="i")		    			myVector.insert(stoi(parameter1),stoi(parameter2)),myVector.display();
			else if(command=="erase" or command=="e")		    			myVector.erase(stoi(parameter1)),myVector.display();
			else if(command=="at" or command=="a")			    			cout<<myVector.at(stoi(parameter1))<<endl;
			else if(command[0]=='[' and command[command.length()-1]==']') 	cout<<myVector[stoi(command.substr(1,command.length()-2)+"")]<<endl;
			else if(command=="front" or command=="f")			            cout<<myVector.front()<<endl;
			else if(command=="back" or command=="b")			            cout<<myVector.back()<<endl;
			else if(command=="size" or command=="s")                        cout<<myVector.size()<<endl;
			else if(command=="capacity" or command=="c")                    cout<<myVector.capacity()<<endl;
			else if(command=="isEmpty" or command=="ie")			        cout<<boolalpha<<myVector.isEmpty()<<endl;
			else if(command=="shrink")          				            myVector.shrink_to_fit(),myVector.display();
			else if(command == "help" or command=="?")			            listCommands();
			else if(command == "exit" or command=="quit")			        break;
			else 								                            cout<<"Invalid Commad !!"<<endl;
		}
		catch(exception &e)
		{
			cout<<"Exception: "<<e.what()<<endl;
		}

	}while(command!="exit" and command!="quit");

	return EXIT_SUCCESS;
}
//======================================
#ifndef _WIN32
//======================================
template <typename T>
void MyVector<T>::display()
{
	cout<<"╔";
	
	for(int i=0; i<v_capacity; i++)
	{	
		cout<<"════";
		if(i!=v_capacity-1) cout<<"╦";
	}
	cout<<"╗ size = "<<v_size<<endl;
	
	for(int i=0; i<v_capacity; i++)
	{
		cout<<"║";
		if(i<v_size)
			cout<<setw(4)<<array[i];
		else
			cout<<setw(4)<<" ";		
	}
	if(v_capacity==0) cout<<"║";
	cout<<"║"<<endl<<"╚";
	for(int i=0; i<v_capacity; i++)
	{
		cout<<"════";
		if(i != v_capacity-1) cout<<"╩";
	}
	cout<<"╝ capacity = "<<v_capacity<<endl;	
}
//======================================
#else
template <typename T>
void MyVector<T>::display()
{
	cout<<"+";
	
	for(int i=0; i<v_capacity; i++)
	{	
		cout<<"----";
		if(i!=v_capacity-1) cout<<"+";
	}
	cout<<"+ size = "<<v_size<<endl;
	
	for(int i=0; i<v_capacity; i++)
	{
		cout<<"|";
		if(i<v_size)
			cout<<setw(4)<<data[i];
		else
			cout<<setw(4)<<" ";		
	}
	if(v_capacity==0) cout<<"|";
	cout<<"|"<<endl<<"+";
	for(int i=0; i<v_capacity; i++)
	{
		cout<<"----";
		if(i != v_capacity-1) cout<<"+";
	}
	cout<<"+ capacity = "<<v_capacity<<endl;	
}
#endif
//starter_code_ends
// Add your code below this line
//===========================================
template <typename T>
//constructor of MyVector it intiallises the size to zero and capacity and dynamically creates 
//a new array
MyVector<T>::MyVector(int cap) : v_size(0), v_capacity(cap){
	array = new T[cap];
}

template <typename T>
//the destructor deletes the array 
MyVector<T>::~MyVector(){
	delete[] array;
}

template <typename T>
//the size function returns the size value of the class
int MyVector<T>::size() const{
	return v_size;
}

template <typename T>
//the capacity function returns the capcity of the Vector
int MyVector<T>::capacity() const {
    return v_capacity;
}

template <typename T>
//reserve method of the class
void MyVector<T>::reserve(int n) {
	//checks if n is greater than the capacity of the vector 
    if (n > v_capacity) {
		//dynamically create a new array of size n
        T* newArray = new T[n];
		//use a for loop and copy all the value of the old vector into the new array
        for (int i = 0; i < v_size; ++i) {
            newArray[i] = array[i];
        }
		//delete the old vector
        delete[] array;
		//let the vector array be the new array
        array = newArray;
		//set the capacity of the vector to n
        v_capacity = n;
    }
}

template <typename T>
//if the size of the vector is 0 than it is empty
bool MyVector<T>::isEmpty() const {
    return v_size == 0;
}

template <typename T>
//returns the value at the front of the vector
const T& MyVector<T>::front() {
	//validates for if the vector is empty then throw an error
    if (isEmpty()) {
        throw out_of_range("Vector is Empty");
    }
	//returns the value at index zero
    return array[0];
}

template <typename T>
//returns the value at the back of the vector
const T& MyVector<T>::back() {
	//validates for if the vector is empty then throw an error
    if (isEmpty()) {
        throw out_of_range("Vector is Empty");
    }
	//the index of the last element is size -1 so return the element at that index
    return array[v_size - 1];
}

template <typename T>
//push an element into the back of the vector
void MyVector<T>::push_back(T element) {
	//checks if the size of the vector is at capacity
    if (v_size == v_capacity) {
		//if yes then call the reserve function to double the capacity
        reserve(v_capacity == 0 ? 1 : v_capacity * 2);
    }
	//adds the element to end of the vector and then increment the size of the vector
    array[v_size++] = element;
}

template <typename T>
//insert an element at a desired index in the vector
void MyVector<T>::insert(int index, T element) {
	//checks if th desired index is with in range, if not output an error
    if (index < 0 || index > v_size - 1) {
        throw out_of_range("Vector index out of range!");
    }
	//checks if the size of the vector is at capacity
    if (v_size == v_capacity) {
		//if yes then call the reserve function to double the capacity
        reserve(v_capacity == 0 ? 1 : v_capacity * 2);
    }
	//use a for loop to shuffle all of the element after the desired index one index to the right
	//starting with the last element of the vector
    for (int i = v_size; i > index; --i) {
        array[i] = array[i - 1];
    }
	//place the element at the desired index
    array[index] = element;
	//increment the size of the vector
    v_size++;
}

//remove the element at the desired index of the vector
template <typename T>
void MyVector<T>::erase(int index) {
	//checks if th desired index is with in range, if not output an error
    if (index < 0 || index >= v_size) {
        throw out_of_range("Vector index out of range!");
    }
	//use a for loop to shuffle all of the element after the desired index one index to the left
	//starting with the first element after the desired index of the vector
    for (int i = index; i < v_size - 1; ++i) {
        array[i] = array[i + 1];
    }
	//decrement th size of the vector
    v_size--;
}

template <typename T>
//overload the [] operator to output the value of the element at desired index
T& MyVector<T>::operator[](int index) {
	//returns the value at desired index of the vector
    return array[index];
}

template <typename T>
//output the value of the element at desired index
T& MyVector<T>::at(int index) {
	//checks if th desired index is with in range, if not output an error
    if (index < 0 || index >= v_size) {
        throw out_of_range("Vector index out of range!");
    }
	//returns the value at desired index of the vector
    return array[index];
}

template <typename T>
//make the capacity of the vector to fit the size of the vector
void MyVector<T>::shrink_to_fit() {
	//checks if the capacity is greater than the size of the vector 
    if (v_size < v_capacity) {
		//dynamically create a new array of size of the vector
        T* newArray = new T[v_size];
		//use a for loop and copy all the value of the vector into the new array
        for (int i = 0; i < v_size; ++i) {
            newArray[i] = array[i];
        }
		//delete the old vector
        delete[] array;
		//let the vector array be the new array
        array = newArray;
		//set the capacity of the vector to size of the vector
        v_capacity = v_size;
    }
}