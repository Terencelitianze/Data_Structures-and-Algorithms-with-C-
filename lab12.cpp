/**
 * @file lab12.cpp
 * @author Tianze Li
 * @description AVL Tree implementation in C++
 * @date 04/05/25
 */
//starter-code-begins
#include<iostream>
#include<cstdlib>
#include<sstream>
#include<iomanip>
#include<math.h>
#include<queue>
#include<vector>

using namespace std;

class Node
{
	private:
		int key;
		string value;
		Node* left;
		Node* right;
		Node* parent;
	public:
		Node(int key,string value): key(key),value(value),left(nullptr),right(nullptr), parent(nullptr) {}
		int getKey() { return this->key;}
		string getValue() {return this->value;}
		friend class BST;
};
//=============================================================================
class BST
{
	private:
		Node *root;
	public:
		void clear(Node* ptr);
		BST();									//constructor
		~BST();									//destructor
		Node* getRoot();						//returns the root of the Tree
		void insert(Node* ptr,int key,string value);			//Insert key into tree/subtree with root ptr
		int height(Node *ptr);				    //Find the height of a tree/subtree with root ptr
		Node* find(Node *ptr,int key);		//Find and returns the node with key
		Node* findMin(Node *ptr);				//Find and return the Node with minimum key value from a tree/subtree with root ptr
		Node* findMax(Node *ptr);				//Find and return the Node with Max key value from a tree/subtree with root ptr		
		void remove(Node *ptr,int key);			//Remove a node with key from the tree/subtree with root
		void printInorder(Node* ptr);			//Traverse (inroder) and print the key of a tree/subtree with root ptr
		void printTree();						//Print 2D Tree
        int balanceFactor(Node *ptr);
        void rotateRight(Node *z);
        void rotateLeft(Node *z);
        void rebalance(Node *ptr);
};

//==========================================================
void listCommands()
{
			
	cout<<"________________________________________________________"<<endl;
	cout<<"display            :Display the BST Tree"<<endl
		<<"height             :Find the height of the Tree"<<endl
		<<"min                :Find the node with minimum key in BST"<<endl
		<<"max                :Find the node with maximum key in BST"<<endl
		<<"find <key>         :Find a node with a given key value in BST"<<endl
		<<"insert <key,value> :Insert a new node in BST"<<endl
		<<"remove <key>       :Remove the node from BST "<<endl
		<<"inorder            :Print the BST in Inorder"<<endl
		<<"help               :Display the available commands"<<endl
		<<"exit               :Exit the program"<<endl;
}
//==========================================================
void demo( BST &myBST)
{
	myBST.insert(myBST.getRoot(),10,"v10");
	myBST.insert(myBST.getRoot(),5,"v5");
	myBST.insert(myBST.getRoot(),4,"v4");
	myBST.insert(myBST.getRoot(),7,"v7");
	myBST.insert(myBST.getRoot(),13,"v13");
	myBST.insert(myBST.getRoot(),15,"v15");
	myBST.insert(myBST.getRoot(),12,"v12");
	myBST.printTree();
}
//==========================================================
int main(void)
{
	BST myBST;
	listCommands();


	while(true)
	{
		string user_input="";
		string command="";
		string key="";
		string value="";
		try
		{
			cout<<">";
			getline(cin,user_input);

			// parse user input into command and parameter(s)
			stringstream sstr(user_input);
			getline(sstr,command,' ');
			getline(sstr,key,',');
			getline(sstr,value);
			
			Node* root = myBST.getRoot();	//get the root of the tree
			if( user_input =="display")	myBST.printTree();
			else if( command =="height")	cout<<"Height = "<<myBST.height(root)<<endl;
			else if( command =="min")	
			{
				Node* min = myBST.findMin(root);
				cout<<"Min. key = "<<((min!=nullptr)? to_string(min->getKey()):" does not exist")<<endl;
			}
			else if( command =="max")	
			{
				Node* max = myBST.findMax(root);
				cout<<"Max. key = "<<((max!=nullptr)? to_string(max->getKey()):" does not exist")<<endl;
			}
			else if( command =="find" or command =="f")	
			{
				Node *node = myBST.find(root,stoi(key));
				if(node==nullptr)
					cout<<key<<" not found"<<endl;
				else
					cout<<"("<<key<<","<<node->getValue()<<")"<<endl;
			}
			else if( command =="insert" or command=="i")	{ myBST.insert(root, stoi(key),value); myBST.printTree();} 
			else if( command =="remove" or command=="r")	{ myBST.remove(root,stoi(key)); myBST.printTree();}
			else if( command =="inorder")	{myBST.printInorder(root); cout<<endl;}
			else if( command == "demo") demo(myBST); 
			else if( command == "help") listCommands();
			else if( command =="exit" or command =="quit" or command =="q") break;
			else cout<<"Invalid command !!!"<<endl;
		}
		catch(exception &ex)
		{
			cout<<ex.what()<<endl;
		}

	}
	return 0;
}
//===============================================================
//Print a 2D Tree
void BST::printTree()
{
	cout<<"Tree:"<<endl;

	int levels = height(this->root);
	int max_nodes = pow(2,levels+1)-1;	
	queue<Node*> myQueue;
	vector<Node*> myVector;
	myQueue.push(this->root);

	//Travers the tree in Breadth First Order and store each node into myVector
	for(int i=0; i<max_nodes; i++)		
	{
		Node* cur = myQueue.front();
		myQueue.pop();
		myVector.push_back(cur);
		if(cur != nullptr)
		{
			myQueue.push(cur->left);
			myQueue.push(cur->right);
		}
		else //For Empty nodes push nullptr(placeholder) in Queue 
		{
			myQueue.push(nullptr);		
			myQueue.push(nullptr);
		}	
	}

	if(max_nodes >0)			//if a non-empty tree
	{
		int *spaces = new int[levels+1];
		spaces[levels]=0;
		int level=0;

		for(int j=levels-1; j>=0; j--)
			spaces[j]=2*spaces[j+1]+1;
		
		for (int i=0; i<max_nodes; i++)
		{
			if(i == (pow(2,level)-1))	// if first node of a level
			{
				cout<<endl<<endl;		// go to next line		
				for(int k=0; k<spaces[level]; k++)	//print sufficient spaces before printing the first node of a level
				    cout<<"   ";
				
				level++;
			}
			if(myVector[i]!=nullptr)     cout<<std::left<<setw(3)<<myVector[i]->getKey();
			else                         cout<<std::left<<setw(3)<<" ";	
			if(level>1)
				for(int k=0; k<spaces[level-2]; k++)	// print spaces between two nodes on same level
					cout<<"   ";
		}

		cout<<endl;
		for(int i=0; i<pow(levels,2.5); i++)	//Add last line with ----
			cout<<"___";
		
		cout<<endl;
		delete[] spaces;
	}
}
//starter-code-ends
//helper function used for the by the destructor to delete all the nodes of the tree
void BST::clear(Node* ptr) 
{
	//deletes all the nodes of the tree recursively using post order traversal 
	//set the base case to if the ptr is not a leaf node
    if (ptr != nullptr) {
		//call the function first to delete the left subtree
        clear(ptr->left);
		//then call the function to delete the right subtree
        clear(ptr->right);
		//delete the nodes itself
        delete ptr;
    }
}
//=====================================================================
BST::BST()
{
	//intialises the binary tree by making the root of the tree equal to null
	root = nullptr;
}
//=====================================================================
BST::~BST()
{
	//uses the helper clear function to delete all nodes
	clear(root);
}
//=====================================================================
// Return the root of the tree
Node* BST::getRoot()
{
	return root;
}
//=====================================================================
//Insert recursively the key in the tree/subtree rooted at ptr
void BST::insert(Node *ptr, int key,string value)
{
	//checks if the tree is empty, if yes then just make the inserted node the root of the tree
    if (root == nullptr) {
        root = new Node(key, value);
        return;
    }
	//if the input key is less than the key that ptr points to
    if (key < ptr->key) {
		//checks if the left child of ptr is null or not 
        if (ptr->left == nullptr) {
			//if yes then the left child of that ptr is where to insert the new node
            ptr->left = new Node(key, value);
			//fixing the connection so that the new inserted node points back to the parent 
            ptr->left->parent = ptr;
            //rebalance after insertion
            rebalance(ptr);  
        } else {
			//continue this recursively to reach the desired place
            insert(ptr->left, key, value);
        }
	//if the input key is greater than the key that ptr points to
    } else if (key > ptr->key) {
		//checks if the right child of ptr is null or not 
        if (ptr->right == nullptr) {
			//if yes then the right child of that ptr is where to insert the new node
            ptr->right = new Node(key, value);
			//fixing the connection so that the new inserted node points back to the parent 
            ptr->right->parent = ptr;
            //rebalance after insertion
            rebalance(ptr); 
        } else {
			//continue this recursively to reach the desired place
            insert(ptr->right, key, value);
        }
    }
    //if the input key is equal to the key that ptr points to (no duplicates allowed)
	else if (key == ptr->key) { 
		cout << "Duplicates are not allowed !!" << endl;
		return;
	}
}
//=====================================================================
//Find the Height of the tree/subtree rooted at ptr
int BST::height(Node* ptr)
{
	//the base case of if ptr equals null then return -1
	if (ptr == nullptr) {
		// as empty tree has height -1, single node has height 0
        return -1;
    }
	//calls the height recursively for the right and left side of each ptr in tree
    int leftHeight = height(ptr->left);
    int rightHeight = height(ptr->right);
	//returns the max height between the right and left ptr
    return 1 + max(leftHeight, rightHeight);
}
//=====================================================================
// Find recursively (or iteratively ) the key with minimum in the tree/subtree rooted at ptr
Node* BST::findMin(Node *ptr)
{
	//check is ptr is null, if yes then return null as the tree is empty
	if (ptr == nullptr) return nullptr;
	//loop all the way on the left side while the left child is not null
    while (ptr->left != nullptr) {
		//increment the ptr to the left child
        ptr = ptr->left;
    }
	//return the most left child as ptr
    return ptr;
}
//=====================================================================
// Find recursively (or iteratively ) the key with Maximum in the tree/subtree rooted at ptr
Node* BST::findMax(Node *ptr)
{
	//check is ptr is null, if yes then return null as the tree is empty
	if (ptr == nullptr) return nullptr;
	//loop all the way on the right side while the right child is not null
    while (ptr->right != nullptr) {
		//increment the ptr to the right child
        ptr = ptr->right;
    }
	//return the most right child as ptr
    return ptr;
}
//=====================================================================
// Find recursively the node with key value in the tree/subtree rooted at ptr
Node* BST::find(Node *ptr,int key)
{
	//find the desired ptr recursively
	//set base case as if ptr is null
	if (ptr == nullptr) return nullptr;
	//checks if the input key is equal to the ptr's key
    if (key == ptr->key) {
		//is yes then the ptr is found so return that ptr
        return ptr;
	//if input key is less than the ptr's key 
    } else if (key < ptr->key) {
		//call find recursively on the left child of the current ptr
        return find(ptr->left, key);
	//if input key is greater than the ptr's key 
    } else {
		//call find recursively on the right child of the current ptr
        return find(ptr->right, key);
    }				
}
//=========================================================
//Remove recursively the node with key value from the tree/subtree rooted at ptr
void BST::remove(Node *ptr,int key)
{
	//key is not found if ptr equals null
	if (ptr == nullptr) return;  
	//if input key is less than the ptr's key 
    if (key < ptr->key) {
		//call remove function recursively on the left child of the current ptr
        remove(ptr->left, key);
	//if input key is greater than the ptr's key 
    } else if (key > ptr->key) {
		//call remove function recursively on the right child of the current ptr
        remove(ptr->right, key);
    } else {
        //intiallise parent as the ptr's parent
        Node* parent = ptr->parent;
        //case 1: node has no children
		//when the left child and right child of the ptr are both null
        if (ptr->left == nullptr && ptr->right == nullptr) {
			//checks if the ptr is the root node
            if (ptr == root) {
				//if yes then just let root equal null
                root = nullptr;
			//if ptr is the left child of its parent 
            } else if (ptr->parent->left == ptr) {
				//then make it's parents left child equal to null
                ptr->parent->left = nullptr;
			//else make it's parents right child equal to null
            } else {
                ptr->parent->right = nullptr;
            }
			//delet ptr its self
            delete ptr;
            //rebalance after deletion
            rebalance(parent); 
        }
        //case 2: node has one child
		//if the left child of ptr is null
        else if (ptr->left == nullptr) {
			//intiallise a temp ptr that points to the right child
            Node* temp = ptr->right;
			//if ptr is the root
            if (ptr == root) {
				//then let root become the right child
                root = temp;
			//if ptr is the left child of its parent 
            } else if (ptr->parent->left == ptr) {
				//let the left child of ptr's parent be the temp ptr
                ptr->parent->left = temp;
			//else let the right child of ptr's parent be the temp ptr
            } else {
                ptr->parent->right = temp;
            }
			//fixing the connections to make the ptr's parent the parent of the temp ptr
            temp->parent = ptr->parent;
			//delete the desired ptr
            delete ptr;
            //rebalance after deletion
            rebalance(parent);
		//if the left child of ptr is null
        } else if (ptr->right == nullptr) {
			//intiallise a temp ptr that points to the left child
            Node* temp = ptr->left;
			//if ptr is the root
            if (ptr == root) {
				//then let root become the left child
                root = temp;
			//if ptr is the left child of its parent 
            } else if (ptr->parent->left == ptr) {
				//let the left child of ptr's parent be the temp ptr
                ptr->parent->left = temp;
			//else let the right child of ptr's parent be the temp ptr
            } else {
                ptr->parent->right = temp;
            }
			//fixing the connections to make the ptr's parent the parent of the temp ptr
            temp->parent = ptr->parent;
			//delete the desired ptr
            delete ptr;
            //rebalance after deletion
            rebalance(parent);
        }
        //case 3: node has two children
        else {
			//intiallise a node by finding the smallest node on the right side of ptr recursively
            Node* Node = findMin(ptr->right);
			//set the ptr's key to node's key
            ptr->key = Node->key;
			//set the ptr's value to node's value
            ptr->value = Node->value;
			//remove the smallest node on the right side of ptr recursively
            remove(ptr->right, Node->key);
        }
    }
}
//===============================================================
//Print recursively the tree/subtree rooted at ptr Inorder fromat
void BST::printInorder(Node *ptr)
{
	//print the inorder of ptr recursively
	//set base case as if ptr is null
	if (ptr == nullptr) return;
	//calls the left child recursively first
    printInorder(ptr->left);
	//prints out the key and value of the ptr itself
    cout << "(" << ptr->key << "," << ptr->value << ") ";
	//then calls the right child recursively
    printInorder(ptr->right);
}

//checks if the node is balanced or not
int BST::balanceFactor(Node *ptr){
    //if it is a empty tree then return 0
    if (ptr == nullptr) return 0;
    //return the difference height of left tree to the height of right tree to get the balance
    //factor
    return height(ptr->left) - height(ptr->right);
}

//perform right rotation to the node
void BST::rotateRight(Node *z){
    //set y equal to the left child of node z 
    Node* y = z->left;
    //cannot rotate right if no left child
    if (y == nullptr) return; 
    
    //make y's right subtree become z's left subtree
    z->left = y->right;
    //check if the right child of y exist, if yes then update the parent pointer
    if (y->right != nullptr) {
        y->right->parent = z;
    }
    
    //make z's parent y's parent
    y->parent = z->parent;
    
    //update parent's child pointer
    if (z->parent == nullptr) {
        //if the parent of z is null then make y the root of the tree
        root = y;
    //else if z is a left child of its parent 
    } else if (z == z->parent->left) {
        //then make y the left child of z's parent
        z->parent->left = y;
    } else {
        //else make y the right child of z's parent
        z->parent->right = y;
    }
    
    //make z the right child of y
    y->right = z;
    //make y the parent of z
    z->parent = y;
}

void BST::rotateLeft(Node *z){
    //set y equal to the left child of node z
    Node* y = z->right;
    //cannot rotate left if no right child
    if (y == nullptr) return;  
    
    //make y's left subtree become z's right subtree
    z->right = y->left;
    //check if the left child of y exist, if yes then update the parent pointer
    if (y->left != nullptr) {
        y->left->parent = z;
    }
    
    //make z's parent y's parent
    y->parent = z->parent;
    
     //update parent's child pointer
    if (z->parent == nullptr) {
        //if the parent of z is null then make y the root of the tree
        root = y;
    //else if z is a left child of its parent 
    } else if (z == z->parent->left) {
        //then make y the left child of z's parent
        z->parent->left = y;
    } else {
        //else make y the right child of z's parent
        z->parent->right = y;
    }
    
    //make z the left child of y
    y->left = z;
    //make y the parent of z
    z->parent = y;
}

void BST::rebalance(Node *ptr){
    //traverse up the tree from ptr to root
    while (ptr != nullptr) {
        //intialise the balance factor using the balanceFactor function
        int bf = balanceFactor(ptr);
        
        //if it is left heavy
        if (bf > 1) {
            //if it is the left-right case
            if (balanceFactor(ptr->left) < 0) {
                //do rotate left for the left child of the node to make it left left case
                rotateLeft(ptr->left);
            }
            //then do the left-left case rotation, by rotating right calling the rotateRight function
            rotateRight(ptr);
        }
        //if it is right heavy
        else if (bf < -1) {
            //if it is the right-left case
            if (balanceFactor(ptr->right) > 0) {
                //do rotate right for the right child of the node to make it right right case
                rotateRight(ptr->right);
            }
            //then do the right-right case rotation, by rotating left calling the rotateleft function
            rotateLeft(ptr);
        }
        
        //move up to parent
        ptr = ptr->parent;
    }
}