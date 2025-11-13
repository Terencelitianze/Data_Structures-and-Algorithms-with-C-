/**
 * @file lab6.cpp
 * @author 
 * @description Traffic Junction Simulation using Circular Queue in C++
 * @date 
 */
//starter-code-begins
#include<iostream>
#include<iomanip> //for setw() manipulator
#include<exception>
#include<sstream>
#include<string>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>	 
using namespace std;

#define QUEUE_SIZE 7   //Default Queue Size
#define MAX_CARS 200   //Max number of cars after which simulation will stop
enum {TOP, LEFT, BOTTOM, RIGHT}; // TOP=0, LEFT=1, BOTTOM=2, RIGHT=3
int current_signal;				 // current signal which can be either TOP, LEFT, RIGHT or BOTTOM
int SPEED=2; 					 //speed of simulation, 1=slowest 

//ANSI Colors 
string colors[]={
					"\033[33m", 	//Yellow
					"\033[34m", 	//Blue
					"\033[35m", 	//Magenta
					"\033[36m", 	//Cyan
					"\033[37m", 	//White
				};
//=================================================
//=========== Queue Class =========================
template <typename T>
class Queue
{
	private:
		T *array;
		int capacity;	//Max Capacity of the Queue
		int size;		//current number of elements in the Queue
		int front;		//front of the Queue
		int rear;		//index where a new element will be added
	public:
		Queue();
		~Queue();
		void enqueue(T); 
		T dequeue();
		bool isEmpty();
		bool isFull();
		friend void display();
};
//===============================================
//============= Car Class =======================
class Car
{
	private:
		time_t arrival_time;
		string color;
	public:
		Car()
		{
			this->arrival_time = time(NULL);
			this-> color = colors[rand()%5];
		}
		time_t get_arrival_time()
		{
			return arrival_time;
		}
		string getColor()
		{
			return color;
		}
};
//===============================================
void display(); //declaration of display method
//===============================================
// Create 4 Queues representing each road of the junction
Queue<Car> road[4];		
//===============================================
int main()
{

	int total_cars=0;		//variable to accumulate number of cars leaving the junction
	int accumulated_waiting_time=0;	//variable to accumulate total waiting time of all cars
	
	srand(time(NULL));	//use system time as a seed for rand()
	current_signal = rand()%4;	//pick a random signal at the start of the program
	time_t signal_timer = time(NULL); //start a timer
	
	while(total_cars<MAX_CARS)
	{
		try
		{	
			int choice=rand()%4;	//choose a random road
			if (!road[choice].isFull() and current_signal!=choice) 	//if road is not already full and the signal is not green for it
				road[choice].enqueue(Car());	

				///create and ad a car in it
			
			if(time(NULL)-signal_timer>= 5/SPEED) //change the signal after every 2 second (if simulation speed is normal i.e. 1)
			{
				current_signal = (current_signal + 1)%4;
				signal_timer = time(NULL);	//reset the timer
			}
			
			if(!road[current_signal].isEmpty() )	//if there are still some cars in the queue for which the signal is green
			{ 
				//take a car out and add its waiting time to the waiting_time
				accumulated_waiting_time+= (time(NULL)-road[current_signal].dequeue().get_arrival_time());
				total_cars++;	//number of cars leaving the junction
			}
			
			system("clear");	//clear the screen
			display();				//re-draw the junction

			cout<<"Total cars passed through the junction:"<<total_cars<<endl;
			cout<<"Avg. waiting time for a car: "<<setprecision(3)<<(float(accumulated_waiting_time)/total_cars)*SPEED<<" seconds"<<endl;	
			
			//Wait for some time
			usleep(1000000/SPEED);

		}
		catch (exception &ex) 	//if Queue is full or empty 
		{}						//Catch the exception but do nothing i.e. skip an iteration of the loop
	}

	return EXIT_SUCCESS;
}
//============================================================
void display()
{
	string spaces; 
	for(int j=0; j<=QUEUE_SIZE; j++)
		spaces+="     ";
	cout<<spaces<<"╔════╗"<<endl;
	for(int i=QUEUE_SIZE-1; i>=0; i--)
	{
	  	cout<<spaces<<"║";
		if(i<road[TOP].size)	cout<<road[TOP].array[(i+road[TOP].front)%road[TOP].capacity].getColor()<<setw(4)<<" ▒▒ "<<"\033[0m";  	
	  	else					cout<<"    ";
	  	cout<<"║"<<endl<<spaces<<"╠════╣"<<endl;;
	}

	cout<<spaces<<"║";
	if(current_signal==TOP)		cout<<"\033[1;32m"<<" ▄▄ "<<"\033[0m";
	else 						cout<<"\033[1;31m"<<" ▄▄ "<<"\033[0m";

	cout<<"║"<<endl<<"╔════";
	
	for(int i=0; i<QUEUE_SIZE; i++)
		cout<<"╦════";
	
	cout<<"╝    ╚";
	
	for(int i=0; i<QUEUE_SIZE; i++)
		cout<<"════╦";

	cout<<"════╗"<<endl;

	for(int i=QUEUE_SIZE-1; i>=0; i--)
	{
		cout<<"║";
		if(i<road[LEFT].size) 	cout<<road[LEFT].array[(i+road[LEFT].front)%road[LEFT].capacity].getColor()<<setw(4)<<" ▒▒ "<<"\033[0m";
		else					cout<<"    ";
	}
	cout<<"║";

	if(current_signal==LEFT)	cout<<"\033[1;32m"<<" █ "<<"\033[0m";
	else 						cout<<"\033[1;31m"<<" █ "<<"\033[0m";
	cout<<"      ";

	if(current_signal==RIGHT)	cout<<"\033[1;32m"<<"   █ "<<"\033[0m";
	else 						cout<<"\033[1;31m"<<"   █ "<<"\033[0m";

	for(int i=0; i<QUEUE_SIZE; i++)
	{
		cout<<"║";
		if(i<road[RIGHT].size)	cout<<road[RIGHT].array[(i+road[RIGHT].front)%road[RIGHT].capacity].getColor()<<setw(4)<<" ▒▒ "<<"\033[0m";
		else					cout<<"    ";
	}
	cout<<"║"<<endl<<"╚════";
	
	for(int i=0; i<QUEUE_SIZE; i++)
		cout<<"╩════";
	
	cout<<"╗    ╔";
	
	for(int i=0; i<QUEUE_SIZE; i++)
		cout<<"════╩";
	
	cout<<"════╝"<<endl<<spaces<<"║";

	if(current_signal==BOTTOM)	cout<<"\033[1;32m"<<" ▄▄ "<<"\033[0m";
	else 						cout<<"\033[1;31m"<<" ▄▄ "<<"\033[0m";
	
	cout<<"║"<<endl;

	for(int i=0; i<QUEUE_SIZE; i++)
	{
	  	cout<<spaces<<"╠════╣"<<endl<<spaces<<"║";
		if(i<road[BOTTOM].size) cout<<road[BOTTOM].array[(i+road[BOTTOM].front)%road[BOTTOM].capacity].getColor()<<setw(4)<<" ▒▒ "<<"\033[0m"<<"║"<<endl;
		else					cout<<"    ║"<<endl;
	}
	cout<<spaces<<"╚════╝"<<endl<<endl;
}
//starter-code-ends
//===========================================================================================
//Define QueueEmpty and QueueFull exception classes
//===========================================
template<typename T> Queue<T>::Queue()
{
	//set capicity of the queue as the default capacity
	capacity = QUEUE_SIZE;
	//dynamically create an array of size capacity
    array = new T[capacity];
	//intiallise the front to be 0, rear to be -1 and size to be 0 
    front = 0;
    rear = -1;
    size = 0;
}
//===========================================
template<typename T> Queue<T>::~Queue()
{
	//delete the array
	delete[] array;
}
//===========================================
template<typename T> void Queue<T>::enqueue(T element)
{
	//checks if the queue is full or not if full throw an exception
	if (isFull()) {
        throw overflow_error("queue is full");
    }
	//increment the rear and uses mod so it cycles back to the front of the queue if the back
	//of the queue is reached
    rear = (rear + 1) % capacity;
	//set the value at the rear of the array to be element
    array[rear] = element;
	//increment the size by 1
    size++;
}
//===========================================
template<typename T> T Queue<T>::dequeue()
{
	//checks if the queue is empty, if true then throws an exception
	if (isEmpty()) {
        throw underflow_error("queue is empty");
    }
	//intiallise an element to be the value at the front of the queue
    T element = array[front];
	//increment the front and uses mod so it cycles back to the front of the queue if the back
	//of the queue is reached
    front = (front + 1) % capacity;
	//decrements the size of the queue by 1
    size--;
	//return the value of the element
    return element;
}
//===========================================
template<typename T> bool Queue<T>::isEmpty()
{
	//if the size of the queue is 0 then it is empty
	return size == 0;
}
//===========================================
template<typename T> bool Queue<T>::isFull()
{
	//if the size of the queue is at capacity then it is full
	return size == capacity;
}
//=============================================