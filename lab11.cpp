//============================================================================
// Name         : Lab 11.cpp
// Author       : Tianze Li
// Version      : 1.0
// Date Created : 22/April/2025
// Date Modified: 22/April/2025
// Description  : Hash Table implementation using C++
//============================================================================
//starter-code-begins
#include<iostream>
#include<fstream>
#include<sstream>
#include<math.h>
#include<iomanip>
#include<list>

using namespace std;
class Entry
{
	private:
		string key;
		string value;
		bool deleted; 	//If an entry has been deleted, then it should be marked as deleted so that the same bucket can be reused in the future
	public:
		Entry(string key, string value)
		{
			this->key = key;
			this->value = value;
			this->deleted = false;
		}
		friend class HashTable;
};

class HashTable
{
	private:
		Entry **buckets;		        			// Array of Pointers to Entries
		unsigned int capacity;				    	// Total Capacity of Hash Table
		unsigned int size;					   		// Current # of entries in the Hash Table
		unsigned int collisions; 					// Total Number of Collisions
	public:
		HashTable(int capacity);
		unsigned int getSize();
		unsigned int getCollisions();
		unsigned long hashCode(string key);
		void insert(string key, string value);
		void remove(string key); 
		string search(string key);
		~HashTable();
};
//======================================================
int main(void)
{
	string inputfile="zipcodes.csv";
	ifstream fin;
	fin.open(inputfile);
	if(!fin){
		cout<<"Can not open "<<inputfile<<" !"<<endl;
		exit(-1);
	}
	
	string line;
	HashTable myHashTable(28859);// Prime number 30% bigger than >25844 (19880*1.3);
	getline(fin,line);  //skip first line
	while(!fin.eof())
	{
		string key, value;
		getline(fin,key,',');
		getline(fin,value);
		std::cout.setstate(std::ios_base::failbit); //dont print any thing on terminal until the failbit is cleared again.
		myHashTable.insert(key,value);
		std::cout.clear();							//clear the failbit
	}
	fin.close();
	cout<<"==================================================="<<endl;
	cout<<"Hash Table size = "<<myHashTable.getSize()<<endl;
	cout<<"Total Number of Collisions = "<<myHashTable.getCollisions()<<endl;
	cout<<"Avg. # collisions/entry = "<<setprecision(2)<<float(myHashTable.getCollisions())/myHashTable.getSize()<<endl;	
	cout<<"==================================================="<<endl;

	string user_input, command, argument1, argument2;

	while(true)
	{
	
		cout<<">";
		getline(cin,user_input);

		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,argument1,',');
		getline(sstr,argument2);

		if(command == "find")      
		{
			string result = myHashTable.search(argument1);
			if      (result == "Record not found!")      cout<<result<<endl;
			else    cout<<"Zip code for "<<argument1<<" is: "<<result<<endl;
		}
		else if(command == "insert")   myHashTable.insert(argument1,argument2);
		else if(command == "remove")   myHashTable.remove(argument1);
		else if(command == "help")	   cout<<"Available Commands:\ninsert <key,value>\nremove <key>\nfind <key>"<<endl;
		else if(command == "exit")	   break;
		else cout<<"Invalid command !!!"<<endl;
	}
	return 0;
}
//===================================================
HashTable::HashTable(int capacity)
{
	buckets = new Entry*[capacity];		// Array of Pointers to Entries
	for(int i=0; i<capacity; i++)
		buckets[i] = nullptr;

	this->capacity = capacity;
	this->size = 0;
	this->collisions = 0;
}
//starter-code-ends
//======================================================
//Please add your implementaiton below this line.

unsigned int HashTable::getSize(){
	//return the current number of entries in the hash table
	return size;
}
unsigned int HashTable::getCollisions(){
	//return the total number of collisions in the hash table
	return collisions;
}
//use the polynomial hash function implementation to hash the key
unsigned long HashTable::hashCode(string key){
	//initialize the hash value to 0
	unsigned long hash = 0;
	//use a prime number for the hash function
	int prime = 31;
	//loop through each character in the key and update the hash value for each
	for(unsigned long i = 0; i < key.length(); i++) {
        hash = hash * prime + key[i];
    }
	//return the hash value modulo the capacity of the hash table
    return hash % capacity;
}
void HashTable::insert(string key, string value){
	//check if the size of the hash table is full or not 
	if(size == capacity) {
		//output error message if the table is full
        cout << "Hash table is full!" << endl;
        return;
    }
    
	//get the hash value of the key by using the hashCode function
    unsigned long index = hashCode(key);
	//store the original index of the key
    unsigned long originalIndex = index;
	//initialize the number of comparisons to 0
    int comparisons = 0;
	//initialize the flag to false
    bool found = false;
    
    //use linear probing to find the appropriate bucket
    while(buckets[index] != nullptr) {
		//increment the number of comparisons
        comparisons++;
		//check if the key is already in the table
        if(buckets[index]->key == key && !buckets[index]->deleted) {
            //update the value of the key
            buckets[index]->value = value;
			//set the flag to true
            found = true;
			//output the confirmation message
            cout << "Existing record has been updated." << endl;
			//break the loop
            break;
        }
        
        //if the bucket is marked as deleted, we can reuse it
        if(buckets[index]->deleted) {
            break;
        }
        
		//increment the index of the key
        index = (index + 1) % capacity;
        
        //if we've gone through all buckets and didn't find it
        if(index == originalIndex) {
			//output the confirmation message
            cout << "Hash table is full!" << endl;
			//return
            return;
        }
    }
    
    if(!found) {
		//if we found an empty spot or a deleted entry
        if(buckets[index] != nullptr) {
			//delete the old entry if it was marked as deleted
            delete buckets[index];
        }
        //create a new entry in the bucket
        buckets[index] = new Entry(key, value);
		//increment the size of the hash table		
        size++;
		//if there are comparisons increment the number of collisions
        if(comparisons > 0) {
            collisions += comparisons;
			//output the confirmation message
            cout << "New record has been added successfully with " << comparisons << " collisions." << endl;
        }
        else {
			//output the confirmation message
            cout << "New record has been added successfully." << endl;
        }
    }
}
void HashTable::remove(string key){
	//get the hash value of the key by using the hashCode function
	unsigned long index = hashCode(key);
	//store the original index of the key
    unsigned long originalIndex = index;
    
    //use linear probing to find the key
    while(buckets[index] != nullptr) {
		//check if the key is already in the table
        if(buckets[index]->key == key && !buckets[index]->deleted) {
			//mark the key as deleted instead of actually removing
            buckets[index]->deleted = true;
			//decrement the size of the hash table
            size--;
			//output the confirmation message
            cout << key << " has been successfully removed!" << endl;
			//break the loop
            return;
        }
        
		//increment the index of the key
        index = (index + 1) % capacity;
        
        //if we've gone through all buckets and didn't find it
        if(index == originalIndex) {
			//output record not found if the key is not found
            cout << "Record not found!" << endl;
            return;
        }
    }
    //output record not found if the key is not found
    cout << "Record not found!" << endl;
}
string HashTable::search(string key){
	//get the hash value of the key by using the hashCode function
	unsigned long index = hashCode(key);
	//store the original index of the key
    unsigned long originalIndex = index;
	//initialize the number of comparisons to 0
    int comparisons = 0;
    
    //use linear probing to find the key
    while(buckets[index] != nullptr) {
		//increment the number of comparisons
        comparisons++;
		//check if the key is already in the table
        if(buckets[index]->key == key && !buckets[index]->deleted) {
			//return the value of the key and the number of comparisons
            return buckets[index]->value + " (comparisons = " + to_string(comparisons) + ")";
        }
		//increment the index of the key		
        index = (index + 1) % capacity;
        
        //if we've gone through all buckets and didn't find it
        if(index == originalIndex) {
			//output record not found if the key is not found
            cout << "Record not found!" << endl;
            return "Record not found!";
        }
    }
	//output record not found if the key is not found
    return "Record not found!";
}
HashTable::~HashTable(){
	//loop through each bucket in the hash table
	for(unsigned int i = 0; i < capacity; i++) {
        //check if the current bucket contains an entry
        if(buckets[i] != nullptr) {
            //delete the Entry object stored in the current bucket
            delete buckets[i];
        }
    }
    //delete the array of bucket pointers itself
    delete[] buckets;
}