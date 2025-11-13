#ifndef MYVECTOR_H
#define MYVECTOR_H

//============================================================================
// Name         : myvector.h
// Author       : Khalid Mengal
// Version      : 1.0
// Date Created : 16-03-2019
// Date Modified: 09-02-2025 
// Copyright    : All rights are reserved
// Description  : Vector implementation in C++
//============================================================================

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <stdexcept>
#include <sstream>

using namespace std;

// Template class for a custom vector implementation
template <typename T>
class MyVector 
{
	private:
	    T *array;                // Pointer to dynamically allocated array to store elements
	    int v_size;             // Current number of elements in the vector
	    int v_capacity;         // Total capacity of the vector (size of the allocated array)

	public:
	    // Constructors and Destructor
	    MyVector();                     // Default constructor (initializes an empty vector)
	    MyVector(int cap);              // Constructor with initial capacity
	    ~MyVector();                    // Destructor (deallocates memory)

	    // Vector Operations
	    void push_back(T element);      // Adds an element to the end of the vector
	    void reserve(int n);            //increase the capacity of the vector so that it can hold at least n elements
        void insert(int index, T element); // Inserts an element at a specific index
	    void erase(int index);          // Removes an element at a specific index
	    T& operator[](int index);       // Overloaded [] operator to access elements by index
	    T& at(int index);               // Access element at a specific index with bounds checking
	    const T& front();               // Returns a reference to the first element
	    const T& back();                // Returns a reference to the last element
	    int size() const;               // Returns the current number of elements in the vector
	    int capacity() const;           // Returns the current capacity of the vector
	    bool empty() const;             // Checks if the vector is empty
	    void shrink_to_fit();           // Reduces the vector's capacity to fit its size
	};

//==================================================================//
//	Please implement the required vector of Vector class below	//

//implementing the default constructor by setting th size and capacity of the vector to 0 and
//point array to null
template <typename T>
MyVector<T>::MyVector() : array(nullptr), v_size(0), v_capacity(0) {}

//constructor of MyVector it intiallises the size to zero and capacity and dynamically creates 
//a new array
template <typename T>
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
//if the size of the vector is 0 than it is empty
bool MyVector<T>::empty() const {
    return v_size == 0;
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
//make the capacity of the vector to fit the size of the vector
void MyVector<T>::shrink_to_fit() {
	//checks if the capacity is equal to the size of the vector 
	if (v_size == 0) {
		//delete the old vector
        delete[] array;
		//set it to null
        array = nullptr;
		//set capacity to 0
        v_capacity = 0;
        return;
	}
	//checks if the capacity is greater than the size of the vector 
    if (v_size == v_capacity){
		//dynamically create a new array of size of the vector
		T* newArray = new T[v_size];
		//use a for loop and copy all the value of the vector into the new array
		for (int i = 0; i < v_size; i++) {
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
//overload the [] operator to output the value of the element at desired index
T& MyVector<T>::operator[](int index) {
	//returns the value at desired index of the vector
    return array[index];
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
//insert an element at a desired index in the vector
void MyVector<T>::insert(int index, T element) {
	//checks if the desired index is with in range, if not output an error
    if (index < 0 || index > v_size) {
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

template <typename T>
//returns the value at the front of the vector
const T& MyVector<T>::front() {
	//validates for if the vector is empty then throw an error
    if (empty()) {
        throw out_of_range("Vector is Empty");
    }
	//returns the value at index zero
    return array[0];
}

template <typename T>
//returns the value at the back of the vector
const T& MyVector<T>::back() {
	//validates for if the vector is empty then throw an error
    if (empty()) {
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
//==================================================================//
#endif