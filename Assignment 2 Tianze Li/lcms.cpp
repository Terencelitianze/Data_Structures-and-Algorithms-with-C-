#include "lcms.h"
#include <fstream>
#include <sstream>
#include <iostream>

//constructor that creates a new LCMS with a given name
LCMS::LCMS(string name) {
    //create a new tree structure to organize the library content
    libTree = new Tree(name);
}

//destructor to clean up resources
LCMS::~LCMS() {
    //delete the tree structure to free up memory
    delete libTree;
}

//import data from a file into the library
int LCMS::import(string path) {
    //try to open the file for reading
    ifstream file(path);
    //if file can't be opened, return error
    if (!file.is_open()) return -1;
    
    string line;
    int count = 0;
    
    //skip the header line of the CSV file
    getline(file, line);
    
    //read each line of the file
    while (getline(file, line)) {
        //parse the CSV line into individual fields
        stringstream ss(line);
        string title, author, isbn, category;
        int year;
        
        //read title handle quoted fields
        if (ss.peek() == '"') {
            ss.ignore();
            getline(ss, title, '"');
            //skip the comma after the quote
            ss.ignore(); 
        } else {
            getline(ss, title, ',');
        }
        
        //read author (handle quoted fields)
        if (ss.peek() == '"') {
            ss.ignore();
            getline(ss, author, '"');
            //skip the comma after the quote
            ss.ignore(); 
        } else {
            //read the author field
            getline(ss, author, ',');
        }
        
        //read the isbn field
        getline(ss, isbn, ',');
        //read the year field
        ss >> year;
        //skip the comma
        ss.ignore(); 
        //read the category field
        getline(ss, category);
        
        //create or find the category node and add the book
        Node* node = libTree->createNode(category);
        //create a new book object
        Book* book = new Book(title, author, isbn, year);
        //add the book to the category
        node->books.push_back(book);
        //update the book count for the category
        libTree->updateBookCount(node, 1);
        //increment the count of imported records
        count++;
    }
    
    //print how many records were imported
    cout << count << " records have been imported." << endl;
    return 0;
}

//export library data to a file
void LCMS::exportData(string path) {
    //try to open the file for writing
    ofstream file(path);
    if (!file.is_open()) {
        //output error message if file can't be opened
        cout << "Error opening file for export." << endl;
        return;
    }
    
    //write the CSV header
    file << "Title,Author,ISBN,Publication Year,Category\n";
    //export all data and get the count
    int count = libTree->exportData(libTree->getRoot(), file);
    cout << count << " records have been successfully exported to " << path << endl;
}

//search for books and categories containing a keyword
void LCMS::find(string keyword) {
    //create vectors to store search results
    MyVector<Node*> categoriesFound;
    MyVector<Book*> booksFound;
    //search the entire tree
    libTree->find(libTree->getRoot(), keyword, categoriesFound, booksFound);
    
    //print summary of search results
    cout << categoriesFound.size() << " Categories/sub-categories found." << endl;
    cout << booksFound.size() << " Book(s) found." << endl << endl;
    
    //print matching categories if any found
    if (!categoriesFound.empty()) {
        cout << "List of Categories containing <" << keyword << ">:" << endl;
        //print each category in the list
        for (int i = 0; i < categoriesFound.size(); i++) {
            //print the category number and name
            cout << (i+1) << ": " << categoriesFound[i]->name << endl;
        }
    }
    
    //print matching books if any found
    if (!booksFound.empty()) {
        cout << "\nList of Books containing <" << keyword << ">:" << endl;
        for (int i = 0; i < booksFound.size(); i++) {
            booksFound[i]->print();
        }
    }
}

//find and display all books in a specific category
void LCMS::findAll(string category) {
    Node* node;
    //if no category specified, use root
    if (category == "") {
        node = libTree->getRoot();
    } else {
        //try to find the specified category
        node = libTree->getNode(category);
    }
    
    //if category not found, show error
    if (node == nullptr) {
        cout << "Category not found." << endl;
        return;
    }
    
    //print all books in the category
    libTree->printAll(node);
}

//display the entire library structure
void LCMS::list() {
    libTree->print();
}

//search for a specific book by title
void LCMS::findBook(string bookTitle) {
    //search the entire tree for the book
    Book* book = libTree->findBook(libTree->getRoot(), bookTitle);
    if (book != nullptr) {
        //if found, display book details
        cout << "Book found in the library:" << endl;
        book->print();
    } else {
        //if not found, show error
        cout << "Book not found in the library." << endl;
    }
}

//add a new book to the library
void LCMS::addBook() {
    string title, author, isbn, category;
    int year;
    
    //get book details from user
    cout << "Enter Title: ";
    getline(cin, title);
    cout << "Enter author(s): ";
    getline(cin, author);
    cout << "Enter ISBN: ";
    getline(cin, isbn);
    cout << "Enter Publication Year: ";
    cin >> year;
    cin.ignore();
    cout << "Enter Category: ";
    getline(cin, category);
    
    //create or find the category and add the book
    Node* node = libTree->createNode(category);
    //create a new book object
    Book* book = new Book(title, author, isbn, year);
    //add the book to the category  
    node->books.push_back(book);
    //update the book count for the category
    libTree->updateBookCount(node, 1);
    
    //confirm book was added
    cout << title << " has been successfully added into the Catalog." << endl;
}

//edit details of an existing book
void LCMS::editBook(string bookTitle) {
    //find the book to edit
    Book* book = libTree->findBook(libTree->getRoot(), bookTitle);
    //if book not found show error 
    if (book == nullptr) {
        cout << "Book not found." << endl;
        return;
    }
    
    //show current book details
    cout << "Book found in the library:" << endl;
    book->print();
    
    //let user choose what to edit
    while (true) {
        cout << "1: Title" << endl;
        cout << "2: Author" << endl;
        cout << "3: ISBN" << endl;
        cout << "4: Publication_year" << endl;
        cout << "5: exit" << endl;
        cout << "choose the field that you want to edit: ";
        
        int choice;
        cin >> choice;
        cin.ignore();
        
        //exit if user chooses to
        if (choice == 5) break;
        
        //get new value from user
        string newValue;
        cout << "Enter new value: ";
        getline(cin, newValue);
        
        //update the chosen field by using switch case to handle different fields
        switch (choice) {
            case 1: book->title = newValue; break;
            case 2: book->author = newValue; break;
            case 3: book->isbn = newValue; break;
            case 4: book->publication_year = stoi(newValue); break;
            default: cout << "Invalid choice." << endl;
        }
    }
}

//remove a book from the library
void LCMS::removeBook(string bookTitle) {
    //find the book to remove
    Book* book = libTree->findBook(libTree->getRoot(), bookTitle);
    if (book == nullptr) {
        cout << "Book not found." << endl;
        return;
    }
    
    //show book details and ask for confirmation
    cout << "Book found in the library:" << endl;
    book->print();
    
    cout << "Are you sure you want to delete the book " << bookTitle << " (yes/no): ";
    string confirm;
    getline(cin, confirm);
    
    //if confirmed, remove the book
    if (confirm == "yes") {
        //remove the book from the library
        if (libTree->removeBook(libTree->getRoot(), bookTitle)) {
            cout << "Book \"" << bookTitle << "\" has been deleted from the library" << endl;
        }
    }
}

//search for a specific category
void LCMS::findCategory(string category) {
    //try to find the category
    Node* node = libTree->getNode(category);
    if (node != nullptr) {
        //if found, show confirmation
        cout << "Category " << node->name << " was found in the Catalog" << endl;
    } else {
        //if not found show error
        cout << "No such category/sub-category found in the Catalog" << endl;
    }
}

//add a new category to the library
void LCMS::addCategory(string category) {
    //create the new category
    Node* node = libTree->createNode(category);
    cout << node->name << " has been successfully created." << endl;
}

//edit the name of an existing category
void LCMS::editCategory(string category) {
    //find the category to edit
    Node* node = libTree->getNode(category);
    //if category not found show error
    if (node == nullptr) {
        cout << "Category not found." << endl;
        return;
    }
    
    //get new name from user
    cout << "Enter new name for category: ";
    string newName;
    getline(cin, newName);
    
    //update the category name
    node->name = newName;
    cout << "Category name updated successfully." << endl;
}

//remove a category from the library
void LCMS::removeCategory(string category) {
    //find the category to remove
    Node* node = libTree->getNode(category);
    //if category not found show error
    if (node == nullptr) {
        cout << "Category not found." << endl;
        return;
    }
    //if trying to remove root category show error
    if (node->parent == nullptr) {
        cout << "Cannot remove root category." << endl;
        return;
    }

    //store parent reference before any deletions
    Node* parent = node->parent;

    //delete all books in current node
    while (node->books.size() > 0) {
        //delete the book by using the last book in the vector
        cout << "Book \"" << node->books[node->books.size() - 1]->title << "\" has been deleted from the Library." << endl;
        delete node->books[node->books.size() - 1];
        //remove the book from the vector
        node->books.erase(node->books.size() - 1);
    }

    //recursively delete all children (from last to first)
    while (node->children.size() > 0) {
        //get the last child
        Node* child = node->children[node->children.size() - 1];
        
        //delete all books in child
        while (child->books.size() > 0) {
            //delete the book by using the last book in the vector
            cout << "Book \"" << child->books[child->books.size() - 1]->title << "\" has been deleted from the Library." << endl;
            delete child->books[child->books.size() - 1];
            //remove the book from the vector
            child->books.erase(child->books.size() - 1);
        }
        
        //delete the child node
        cout << "Category \"" << child->name << "\" has been deleted from the Library." << endl;
        delete child;
        //remove the child from the vector
        node->children.erase(node->children.size() - 1);
    }

    //remove from parent's children and adjust book count
    for (int i = 0; i < parent->children.size(); i++) {
        //if the child is the one to remove
        if (parent->children[i] == node) {
            //update the book count for the parent
            libTree->updateBookCount(parent, -node->bookCount);
            //remove the child from the vector
            parent->children.erase(i);
            break;
        }
    }

    //delete the node itself
    cout << "Category \"" << node->name << "\" has been deleted from the Library." << endl;
    delete node;
}