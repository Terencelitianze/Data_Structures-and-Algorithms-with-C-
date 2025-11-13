#include "book.h"
#include <iostream>
#include <iomanip>

// intiallise book with title, author isbn, publication_year
Book::Book(std::string title, string author, string isbn, int publication_year)
    : title(title), author(author), isbn(isbn), publication_year(publication_year) {}

// the print method
void Book::print() {
    //print out the title, author, isbn and publication year in desired format
    std::cout << "---------------------------------------------------------------\n";
    std::cout << std::left << std::setw(15) << "Title:" << title << "\n";
    std::cout << std::left << std::setw(15) << "Author(s):" << author << "\n";
    std::cout << std::left << std::setw(15) << "ISBN:" << isbn << "\n";
    std::cout << std::left << std::setw(15) << "Year:" << publication_year << "\n";
    std::cout << "---------------------------------------------------------------\n";
}