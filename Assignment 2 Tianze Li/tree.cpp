#include "tree.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cstring>
#include "myvector.h"
#include "book.h"



//the constructor Initializes a new node with the given category name
//sets bookCount to 0 and parent to nullptr
Node::Node(string name) : name(name), bookCount(0), parent(nullptr) {}

//returns the full category path of this node as a string
string Node::getCategory(Node* node) {
    //if node is nullptr or has no parent, returns empty string for root
    if (node == nullptr || node->parent == nullptr) {
        return "";
    }
    //if the parent path is empty, return the node name 
    string parentPath = node->parent->getCategory(node->parent);
    return (parentPath == "" ? "" : parentPath + "/") + node->name;
}

//destructor cleans up dynamically allocated memory deletes all Book objects and recursively deletes all child nodes
Node::~Node() {
    //delete all Book objects in this category
    for (int i = 0; i < books.size(); i++) {
        delete books[i];
    }
    
    //recursively delete all child category nodes
    for (int i = 0; i < children.size(); i++) {
        delete children[i];
    }
}


//intiallises the tree 
Tree::Tree(string rootName) {
    //setting the root of the tree to a node called rootname
    root = new Node(rootName);
}

//destructor for the tree
Tree::~Tree() {
    //deletes the tree dynamically by deleting the root
    delete root;
}

//getroot function of the tree returns the root of the tree 
Node* Tree::getRoot() {
    return root;
}

//calls the print_helper function to print the categories in the desired way
void Tree::print() {
    //calls the print_helper function with empty strings
    print_helper(string(), string(), root);
}

void Tree::print_helper(string padding, string pointer, Node* node) {
    if (!node) return;
    
    //print current node with book count
    cout << padding << pointer << node->name << "(" << node->bookCount << ")" << endl;
    
    //calculate new padding - add either "    " or "│   " depending if this is last child
    string new_padding = padding + (isLastChild(node) ? "    " : "│   ");
    
    //print all children with appropriate pointers
    for (int i = 0; i < node->children.size(); i++) {
        string new_pointer = (i == node->children.size() - 1) ? "└── " : "├── ";
        print_helper(new_padding, new_pointer, node->children[i]);
    }
}

//check if a node is the last child of its parent
bool Tree::isLastChild(Node* ptr) {
    //if node is null or has no parent then it the last child
    if (ptr == nullptr || ptr->parent == nullptr) return true;
    //check if this node is the last one in parent's children list
    return ptr->parent->children.back() == ptr;
}

//insert a new child node under the given parent node
void Tree::insert(Node* node, string child_name) {
    //if parent node is null, can't insert
    if (node == nullptr) return;
    
    //check if child with same name already exists
    for (int i = 0; i < node->children.size(); i++) {
        if (node->children[i]->name == child_name) return;
    }
    
    //create a new child node and set up parent-child relationship
    Node* newChild = new Node(child_name);
    newChild->parent = node;
    node->children.push_back(newChild);
}

//remove a child node and all its descendants
void Tree::removeChild(Node* node, string child_name) {
    //if parent node is null, can't remove
    if (node == nullptr) return;
    
    //look for child with matching name
    for (int i = 0; i < node->children.size(); i++) {
        if (node->children[i]->name == child_name) {
            //update book counts and clean up memory
            int booksToRemove = node->children[i]->bookCount;
            updateBookCount(node, -booksToRemove);
            delete node->children[i];
            node->children.erase(i);
            return;
        }
    }
}

//update book count recursively up the tree
void Tree::updateBookCount(Node* ptr, int offset) {
    //if node is null, stop recursion
    if (ptr == nullptr) return;
    
    //update current node's count and propagate to parent
    ptr->bookCount += offset;
    updateBookCount(ptr->parent, offset);
}

//find a book by title within a node and its children
Book* Tree::findBook(Node* node, string bookTitle) {
    //if node is null, book not found
    if (node == nullptr) return nullptr;
    
    //check all books in current node
    for (int i = 0; i < node->books.size(); i++) {
        if (node->books[i]->title == bookTitle) {
            return node->books[i];
        }
    }
    
    //if not found, check all child nodes recursively
    for (int i = 0; i < node->children.size(); i++) {
        Book* found = findBook(node->children[i], bookTitle);
        if (found != nullptr) return found;
    }
    
    return nullptr;
}

//remove a book by title
bool Tree::removeBook(Node* node, string bookTitle) {
    //if node is null, can't remove
    if (node == nullptr) return false;
    
    //check all books in current node
    for (int i = 0; i < node->books.size(); i++) {
        if (node->books[i]->title == bookTitle) {
            //delete book and update counts
            delete node->books[i];
            node->books.erase(i);
            updateBookCount(node, -1);
            return true;
        }
    }
    
    //if not found, check all child nodes recursively
    for (int i = 0; i < node->children.size(); i++) {
        if (removeBook(node->children[i], bookTitle)) {
            return true;
        }
    }
    
    return false;
}

//print all books under a node and its children
void Tree::printAll(Node* node) {
    //if node is null, nothing to print
    if (node == nullptr) return;
    
    //print all books in current node
    for (int i = 0; i < node->books.size(); i++) {
        node->books[i]->print();
    }
    
    //print all books in child nodes recursively
    for (int i = 0; i < node->children.size(); i++) {
        printAll(node->children[i]);
    }
}

//find nodes and books matching a keyword
void Tree::find(Node* node, string keyword, 
                MyVector<Node*>& categoriesFound,
                MyVector<Book*>& booksFound) {
    if (node == nullptr) return;

    //check if node name contains the keyword (case-sensitive)
    if (node->name.find(keyword) != string::npos) {
        categoriesFound.push_back(node);
    }

    //check all books in current node
    for (int i = 0; i < node->books.size(); i++) {
        Book* book = node->books[i];
        
        //check if keyword appears in title or author (case-sensitive)
        if (book->title.find(keyword) != string::npos) {
            booksFound.push_back(book);
        }
    }

    //recursively check all child nodes
    for (int i = 0; i < node->children.size(); i++) {
        find(node->children[i], keyword, categoriesFound, booksFound);
    }
}

//export data to file
int Tree::exportData(Node* node, ofstream& file) {
    //if node is null or file not open, can't export
    if (node == nullptr || !file.is_open()) return 0;
    
    int count = 0;
    
    //export all books in current node
    for (int i = 0; i < node->books.size(); i++) {
        Book* book = node->books[i];
        
        //always quote title and author to be safe
        file << "\"" << book->title << "\","
            << "\"" << book->author << "\","
            //exports isbn, publication year and category in desired format
            << book->isbn << "," 
            << book->publication_year << ","
            << node->getCategory(node) << "\n";
        //increment the count
        count++;
    }
    
    //export all child nodes recursively
    for (int i = 0; i < node->children.size(); i++) {
        count += exportData(node->children[i], file);
    }
    
    return count;
}

//get node by path
Node* Tree::getNode(string path) {
    //if path is empty, return root
    if (path == "") return root;
    
    //split path into individual categories
    MyVector<string> categories;
    stringstream ss(path);
    string category;
    
    while (getline(ss, category, '/')) {
        categories.push_back(category);
    }
    
    //navigate through the tree following the path
    Node* current = root;
    for (int i = 0; i < categories.size(); i++) {
        bool found = false;
        //look for matching child node
        for (int j = 0; j < current->children.size(); j++) {
            if (current->children[j]->name == categories[i]) {
                current = current->children[j];
                found = true;
                break;
            }
        }
        if (!found) return nullptr;
    }
    
    return current;
}

//create node by path (creates missing nodes)
Node* Tree::createNode(string path) {
    //if path is empty, return root
    if (path == "") return root;
    
    //split path into individual categories
    MyVector<string> categories;
    stringstream ss(path);
    string category;
    
    while (getline(ss, category, '/')) {
        categories.push_back(category);
    }
    
    //navigate through the tree, creating missing nodes
    Node* current = root;
    for (int i = 0; i < categories.size(); i++) {
        bool found = false;
        //look for existing child node
        for (int j = 0; j < current->children.size(); j++) {
            if (current->children[j]->name == categories[i]) {
                current = current->children[j];
                found = true;
                break;
            }
        }
        //if not found, create new node
        if (!found) {
            Node* newNode = new Node(categories[i]);
            newNode->parent = current;
            current->children.push_back(newNode);
            current = newNode;
        }
    }
    
    return current;
}

//check if tree is empty
bool Tree::isEmpty() {
    //tree is empty if root is null or has no children and no books
    return root == nullptr || (root->children.empty() && root->books.empty());
}