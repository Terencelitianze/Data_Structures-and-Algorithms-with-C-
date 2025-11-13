
//============================================================================
// Name         :lab8.cpp
// Author       : Tianze Li
// Version      : 1.0
// Date Created : 21/3/25
// Date Modified: 21/3/25
// Description  : General Tree implmentation in C++
//============================================================================
//starter_code_begins (please do not remove this line)
#include<iostream>
#include<sstream>
#include<stdlib.h>
#include<vector>
using namespace std;

class Node
{
	private:
		string name;				//name of the Node
		vector<Node*> children;		//Children of Node
		Node* parent; 				//link to the parent 

	public:
		Node(string name, Node* parent = nullptr) : name(name), parent(parent)
		{ }
		string getName()
		{
			return this->name;
		}
		~Node();
		friend class Tree;
};
//==========================================================
class Tree
{
	private:
		Node *root;				//root of the Tree
		Node *curr_Node;		//current Node
		
	public:	
		//Methods that are part of the starter-code	
		Tree();	
		~Tree();
		Node* getRoot();
		Node* getCurrentNode();
		void cd(string name);
		void print();			//Print entire tree
	private:					//Helper methods
		void print_helper(string padding, string pointer,Node *node);
		bool isLastChild(Node *ptr);
	public:
		//Required Methods
		void insert(Node* node,string name);
		void remove(Node* node,string child_name);
		bool isExternal(Node* node);
		bool isInternal(Node* node);
		int size(Node* node);
		int depth(Node* node);
		int height(Node *node);
		int treeHeight();
		void preorder(Node *node);
		void postorder(Node *node);
};
//==================================================================
void help(void)
{
	cout<<"print               : Print the Tee"<<endl
	    <<"insert <child-name> : Insert a new node as a child of the current node"<<endl
	    <<"remove <child-name> : Removes a specific child from the current node"<<endl
		<<"cd <child-name>     : change the current working directory to child directory (node)"<<endl
		<<"cd ..               : change the current working directory to parent directory (node)"<<endl
	    <<"treeSize            : Print the total number of nodes in the Tree"<<endl
	    <<"height              : Print the height of the current node"<<endl
	    <<"depth               : Print the depth of the current node"<<endl
	    <<"treeHeight          : Print the height(Max-depth) of the Tree"<<endl
	    <<"isExternal          : Check if the current node is an external node or not"<<endl
	    <<"isInternal          : Check if the current node is an internal node or not"<<endl
	    <<"preorder            : Traverse/Print the Tree in pre-order"<<endl
	    <<"postorder           : Traverse/Print the Tree in post-order"<<endl
	    <<"help                : Display the list of available commands"<<endl
	    <<"exit                : Exit the Program"<<endl;
}
//==================================================================
//==================================================================
int main()
{
	Tree tree;
	help();
	while(true)
	{
		string user_input;
		string command;
		string parameter;
		cout<<">";
		getline(cin,user_input);

		// parse userinput into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,parameter);

		try
		{
				 if(command=="insert" or command=="i")		tree.insert(tree.getCurrentNode(),parameter); 	
			else if(command=="remove" or command=="r")		tree.remove(tree.getCurrentNode(),parameter);
			else if(command=="cd")							tree.cd(parameter);
			else if(command=="treeSize")						cout<<"Size of the Tree is :"<<tree.size(tree.getRoot())<<endl;
			else if(command=="depth")						cout<<"The depth of the current node("<<tree.getCurrentNode()->getName()<<") is: "<<tree.depth(tree.getCurrentNode())<<endl;
			else if(command=="height")						cout<<"The height of the current node("<<tree.getCurrentNode()->getName()<<") is: "<<tree.height(tree.getCurrentNode())<<endl;
			else if(command=="treeHeight")					cout<<"The height(max-depth) of the Tree is: "<<tree.treeHeight()<<endl;
			else if(command=="print")	                    tree.print();		//print the tree
			else if(command=="preorder")					tree.preorder(tree.getRoot()),cout<<endl;
			else if(command=="postorder")					tree.postorder(tree.getRoot()),cout<<endl;
			else if(command=="help")                        help();
			else if(command=="exit")						break;
			else if(command=="isExternal")					cout<<"Current node("<<tree.getCurrentNode()->getName()<<") is "<<((tree.isExternal(tree.getCurrentNode())==true) ? "":"not ")<<"an external node of the tree."<<endl;
			else if(command=="isInternal")					cout<<"Current node("<<tree.getCurrentNode()->getName()<<") is "<<((tree.isInternal(tree.getCurrentNode())==true) ? "":"not ")<<"an internal node of the tree."<<endl;
			else 											cout<<command<<": command not found"<<endl;
		}
		catch(exception &e)
		{
			cout<<"Exception: "<<e.what()<<endl;
		}

	}
}
//========================================================================
Tree::Tree()
{
	this->root = new Node("root");
	this->curr_Node = this->root;
}
Tree::~Tree()
{
	delete this->root;
}
//========================================================================
Node* Tree::getRoot()
{
	return root;
}
//========================================================================
Node* Tree::getCurrentNode()
{
	return curr_Node;
}
//========================================================================
void Tree::cd(string name)
{
	if(name=="..")
	{
		if(curr_Node!=root)	curr_Node = curr_Node->parent;
	}
	else
	{
		for(int i=0; i<curr_Node->children.size(); i++)
			if(name == curr_Node->children[i]->name)
			{
				curr_Node = curr_Node->children[i];						//update current working directory
				return;
			}

		cout<<name<<": child not found"<<endl;
	}
}
//==========================================================================
void Tree::print()
{
	print_helper("","",root);
}
//==========================================================================
void Tree::print_helper(string padding, string pointer,Node *node)
{
    if (node != nullptr) 
    {
        if(node == curr_Node)	//print current Node in blue color
        	cout <<padding<<pointer<<"\x1B[33m"<<node->name<<"\x1B[0m"<<endl;
        else 
        	cout <<padding<<pointer<<node->name<<endl;

		if(node!=root)	padding+=(isLastChild(node)) ? "   " : "│  ";


        for(int i=0; i<node->children.size(); i++)
		{
			string marker = isLastChild(node->children[i]) ? "└──" : "├──";
			print_helper(padding,marker, node->children[i]);

		}
    }
}
//==========================================================================
bool Tree::isLastChild(Node *ptr)
{
	if(ptr!=root and ptr == ptr->parent->children[ptr->parent->children.size()-1])
		return true;
	return false;
}
//===========================================================================
//starter_code_ends  (please do not remove this line)
//==========================================================================
bool Tree::isExternal(Node* node)
{
	//checks if they node has children or not if it does not have children then it is external
	return node->children.empty();
}
//==========================================================================
bool Tree::isInternal(Node* node)
{
	//checks if they node has children or not if it does have children then it is internal
	return !node->children.empty();
}
//==========================================================================
int Tree::size(Node *node)
{
	//use recursion to count the number of nodes in tree
	//base case of if node is leaf
	if (node == nullptr) return 0;
	//set count to 1 
    int count = 1;
	//loop through the whole vector using a iterator 
    for (Node* child : node->children)
	//uses recursion to count the number of children
        count += size(child);
	//return the count value
    return count;
}
//========================================================================
void Tree::insert(Node* node, string child_name)
{
	//intialise a node ptr called child and loop through the whole vector using a iterator 
	for (Node* child : node->children)
		//checks if the node that user want to insert is unique or not
        if (child->name == child_name)
        {
			//if yes then output an error
            cout << "Error: Child with the same name already exists." << endl;
            return;
        }
	//uses the push back function of vector to insert the child into the parent node vector
    node->children.push_back(new Node(child_name, node));
}
//========================================================================
void Tree::remove(Node* node, string child_name)
{
	//iterate through the children of the current node
    for (vector<Node*>::iterator iterator = node->children.begin(); iterator != node->children.end(); ++iterator)
    {
		//if the child is found 
        if ((*iterator)->name == child_name)
        {
            //delete the child node and its subtree
            delete *iterator; 
            //remove the child node from the parent's children list
            node->children.erase(iterator);

            cout << child_name << " has been deleted successfully." << endl;
            return;
        }
    }
	//else output an error
    cout << "child not found" << endl;
}
//==========================================================================
int Tree::depth(Node* node)
{
	//intiallise depth to 0 
	int depth = 0;
	//loop while the node is not the root 
    while (node != root)
    {
		//increment depth
        depth++;
		//let the parent of the node to be the next one to be checks
        node = node->parent;
    }
	//return the value of depth
    return depth;
}
//==========================================================================
int Tree::height(Node* node)
{
	//recursivly calculates the height by setting the node is leaf as base pointer
	if (node == nullptr) return -1;
	//intiallises a max height to -1
    int maxHeight = -1;
	//loop through the whole vector using a iterator 
    for (Node* child : node->children)
	//calculate the max height recursively by comparing between the height of all its leaf nodes
        maxHeight = max(maxHeight, height(child));
	//return the value of the max height + 1
    return maxHeight + 1;
}
//==========================================================================
int Tree::treeHeight()
{
	//return the height of the root node
	return height(root);
}
//==========================================================================
void Tree::preorder(Node *node)
{
	//calls it from root to children recursively, using leaf as base condition
	if (node == nullptr) return;
	//print out the node name
    cout << node->name << " ";
	//loop through the whole vector using a iterator 
    for (Node* child : node->children)
	//calls it recursively
        preorder(child);
}
//==========================================================================
void Tree::postorder(Node *node)
{
	//calls it from children to root recursively, using leaf as base condition
	if (node == nullptr) return;
    //loop through the whole vector using a iterator 
    for (Node* child : node->children)
	//calls it recursively
        postorder(child);
	//print out the node name
    cout << node->name << " ";
}
//==========================================================================
Node::~Node()
{
	//loop through the whole vector using a iterator 
	for (Node* child : children)
		//delete every node
        delete child;
}
