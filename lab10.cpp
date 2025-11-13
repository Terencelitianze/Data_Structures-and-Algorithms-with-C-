/*
 * @file 
 * @author : Tianze Li
 * @description Binary Heap Implementation in C++
 * @date : 10th april 2025
 */
//starter_code_begins (please do not remove this line)
#include<iostream>
#include<exception>
#include<math.h>
#include<ctime>
#include<vector>
#include<iomanip>
#include<sstream>
using namespace std;

class Heap
{
	private:
		vector<int> array;
	public:
		Heap();
		void insert(int key);
		int removeMin();
		int getMin();
		int parent(int k);
		int left(int k);
		int right(int k);
		void bubbleup(int k);
		void bubbledown(int k);
		void print();
		void sort();
};

void listCommands()
{
	cout<<"-----------------------------------------------------------------"<<endl;
	cout<<"display            :Display the Heap"<<endl
		<<"insert <key>       :Insert a new element in the Heap"<<endl
		<<"getMin             :Get the element with Min. Key in the Heap"<<endl
		<<"removeMin          :Remove the element with Min. Key from Heap"<<endl
		<<"sort               :Sort the Heap"<<endl
		<<"help               :Display the available commands"<<endl
		<<"exit/quit          :Exit the program"<<endl;
	cout<<"-----------------------------------------------------------------"<<endl;
}
//=============================================
void demo(Heap &myHeap)
{
	for (int i=1; i<=7; i++)
	{
		int n = rand()%25;
		myHeap.insert(n);
	}
	myHeap.print();
}
//=============================================
int main()
{

	Heap myHeap;
	string user_input;
	string command;
	string argument;

	listCommands();

	while(true)
	{
		try
		{
			cout<<">";
			getline(cin,user_input);
		
			// parse userinput into command and parameter(s)
			stringstream sstr(user_input);
			getline(sstr,command,' ');
			getline(sstr,argument);

			     if(command =="display" or command=="d")        myHeap.print();
			else if(command =="insert"  or command=="i")        { myHeap.insert(stoi(argument)); myHeap.print(); }
			else if(command =="getMin")        					{int min=myHeap.getMin();cout<<"Min Key = "<<min<<endl;}
			else if(command =="removeMin"  or command=="r")     { cout<<myHeap.removeMin()<<" has been removed..!"<<endl; myHeap.print(); }     
			else if(command =="sort")          					{ myHeap.sort(); myHeap.print(); }
			else if(command == "help")         					listCommands();
			else if(command == "demo")         					demo(myHeap);
			else if(command == "exit" or command == "quit") 	break;
			else cout<<"Invalid command !!!"<<endl;
		}
		catch (exception &e)
		{
			cout<<"Exception: "<<e.what()<<endl;
		}
	}
	return EXIT_SUCCESS;
}
//==================================================================
//This method prints a Heap in 2D format. 
void Heap::print()
{
	if(array.size()>1)
	{
		int levels = int(log2(array.size()));

		int *spaces = new int[levels+1];
		spaces[levels]=0;

		for(int j=levels-1; j>=0; j--)
		{
				spaces[j]=2*spaces[j+1]+1;
		}
		
		int level=0;
		for (int i=0; i<array.size()-1; i++)
		{
			if(i == (pow(2,level)-1))
			{
				cout<<endl<<endl;
			
				for(int k=0; k<spaces[level]; k++)
				cout<<"   ";
				level++;
			}
			cout<<std::left<<setw(3)<<array[i+1];
		
			if(level>1)
			{
				for(int k=0; k<spaces[level-2]; k++)
					cout<<"   ";
			}
			
		}
		cout<<endl;
		for(int i=0; i<spaces[0]*log2(array.size()/2)+4; i++)
			cout<<"__";
		
		cout<<endl;
		delete[] spaces;
	}

}

//Constructor
Heap::Heap()
{
	array.push_back(0); //add a dummy value to the first location of the array that will remain unused
}
//starter_code_ends (please do not remove this line)
//==================================================================
// Insert an element in Heap keeping the Heap property intact 
void Heap::insert(int key)
{
	//add the new key at the end of the array
	array.push_back(key);  
	//use bubbleup algorithm to get the key to the correct place        
	bubbleup(array.size() - 1);    
}
// Remove the minimum value from Heap keeping the Heap property intact
int Heap::removeMin()
{
	//checks if the array is empty 
	if(array.size() <= 1) {
		//outputs a error message if the array is empty
		throw runtime_error("Heap is empty");
	}
	//stores the value of the minimum value 
	int min = array[1];  
	//make the last element of the array to the root position
	array[1] = array.back();           
	//remove the last element of the array
	array.pop_back();   
	//if the array has size greater than 1, do the bubble down alogrithm to get the element to 
	//the right place               
	if(array.size() > 1) {
		bubbledown(1);                 
	}
	//return the minimum value
	return min;
}
// Return (but don't remove) the minimum value from the Heap
int Heap::getMin()
{
	//checks if the array is empty 
	if(array.size() <= 1) {
		//outputs a error message if the array is empty
		throw runtime_error("Heap is empty");
	}
	//return the root which is the minimum value
	return array[1];
}
// Returns the index of the parent of the node k
int Heap::parent(int k)
{
	//returns the floor function of the node's index divide by 2
	return k / 2;
}
//returns the index of the left child of the node k
int Heap::left(int k)
{
	//returns the node's index times by 2
	return 2 * k;
}
// Returns the index of the right child of the node k
int Heap::right(int k)
{
	//returns the node's index times by 2 + 1
	return 2 * k + 1;
}

void Heap::bubbleup(int k)
{
	//loop if the parent of the element is bigger than the element and is not at root yet
	while(k > 1 && array[k] < array[parent(k)]) {
		//swap with the parent if element is smaller
		swap(array[k], array[parent(k)]);  
		//make the element's index to the index of the parent 
		k = parent(k);                    
	}
}

void Heap::bubbledown(int k)
{
	//while node has a left child
	while(left(k) < array.size()) {        
		//assign the left child's index to Child
		int Child = left(k);        
		
		//check if right child exists and is smaller than left child
		if(right(k) < array.size() && array[right(k)] < array[left(k)]) {
			//make Child equal to the index of the right child
			Child = right(k);
		}
		
		//if node is larger than the smallest child of its children
		if(array[k] > array[Child]) {
			//swap with the parent if element is smaller
			swap(array[k], array[Child]);
			//make the index of the node the index of it's smaller child
			k = Child;  
		//else break the loop as the node is at it's right place           
		} else {
			break;                        
		}
	}
}
//=====================================
// This method will sort the internal array/vector 
// Hints: 
// 		Keep extracting the min value from the heap and store them into an auxiliary array.
// 		Copy the values from auxiliary array to the internal array/vector of heap
void Heap::sort()
{
	//intiallise an array called sortedArray
	vector<int> sortedArray;
	//initiallise it with a dummy element at index 0
	sortedArray.push_back(0);  
	
	//get the element of the heap one by one using the RemoveMin() function is array size is 
	//greater than 1
	while(array.size() > 1) {
		//add it from the back of the array for each element
		sortedArray.push_back(removeMin());
	}
	
	//replace the original array with the sorted array
	array = sortedArray;
}
//=============================================