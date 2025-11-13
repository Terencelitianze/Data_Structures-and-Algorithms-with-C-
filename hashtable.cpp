#include "hashtable.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;


//converts a string to lowercase for case-insensitive operations.
string toLower(const string& str) {
    //copy the input string
    string lowerStr = str;
    //apply tolower to each character
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
        [](unsigned char c){ return tolower(c); });
    //returns the string
    return lowerStr;
}

//translation class implementation
//store language in lowercase
Translation::Translation(string language, string meaning) : language(toLower(language)) {
    //initialize meanings list with the first meaning
    meanings.push_back(meaning);
}

//adds a new meaning if not already present
void Translation::addMeaning(string newMeaning) {
    if (find(meanings.begin(), meanings.end(), newMeaning) == meanings.end()) {
        //append unique meaning
        meanings.push_back(newMeaning);
    }
}

//entry class implementation
//store word lowercase, mark as not deleted
Entry::Entry(string word, string meaning, string language) : 
    word(toLower(word)), deleted(false) {
    //create initial translation
    translations.push_back(Translation(language, meaning));
}

//adds a translation to an existing entry
void Entry::addTranslation(string newMeaning, string language) {
    //normalize language to lowercase
    string langLower = toLower(language);
    //iterate through existing translations to find a matching language block
    for (auto& translation : translations) {
        //compare stored translation.language (already lowercase) with langLower
        if (toLower(translation.language) == langLower) {
            //found a matching language section, add new meaning if unique
            translation.addMeaning(newMeaning);
            return;
        }
    }
    //if no existing translation for this language, create and append a new Translation
    translations.push_back(Translation(language, newMeaning));
}

//prints all translations for this entry in <language> : <meanings...> format
void Entry::print() {
        //iterate over each translation block
    for (size_t i = 0; i < translations.size(); ++i) {
        //print language code followed by colon and space
        cout << translations[i].language << " : ";
        //iterate through each meaning in this translation
        for (size_t j = 0; j < translations[i].meanings.size(); ++j) {
            //print the j-th meaning
            cout << translations[i].meanings[j];
            //if not the last meaning, print a semicolon and space as delimiter
            if (j != translations[i].meanings.size() - 1) {
                cout << "; ";
            }
        }
        //after printing all meanings for this language, end the line
        cout << endl;
    }
}

//hashTable class implementation
//constructor: initialize HashTable with given capacity
HashTable::HashTable(int tableCapacity) : 
    size(0), capacity(tableCapacity), collisions(0) {
    //allocate an array of Entry pointers, initialize all to nullptr
    buckets = new Entry*[capacity]();
}

//destructor: clean up memory for entries and bucket array
HashTable::~HashTable() {
    //delete each Entry pointer if it points to an Entry using a for loop
    for (unsigned int i = 0; i < capacity; ++i) {
        if (buckets[i] != nullptr) {
            delete buckets[i];
        }
    }
    //delete the buckets array itself
    delete[] buckets;
}

//computes a hash code for the given word using polynomial hash function
unsigned long HashTable::hashCode(string word) {
    //set p as a small prime base
    const unsigned long p = 31;      
    unsigned long hash = 0;
    //for each character times the hash by the p value and add the next characters hash value
    for (char c : word) {
        hash = hash * p + static_cast<unsigned char>(c);
    }
    return hash;
}

//returns the current count of stored entries
unsigned int HashTable::getSize() { return size; }
//returns the number of collisions encountered during insertions
unsigned int HashTable::getCollisions() { return collisions; }

//imports word-meaning pairs from a file; first line indicates language
void HashTable::import(string path) {
    //attempt to open file for reading
    ifstream file(path);
    //if file can not be opened output an error message
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << path << endl;
        return;
    }


    string line, language;
    //first line should specify language
    getline(file, language); 

    int wordcount = 0;
    //read each subsequent line: format "word:meaning1;meaning2;..." using a while loop
    while (getline(file, line)) {

        size_t colonPos = line.find(':');
        //skip lines missing ':'
        if (colonPos == string::npos) continue;

        //extract the word
        string word = line.substr(0, colonPos);
        //extract meanings section
        string meaningsStr = line.substr(colonPos + 1);
        
        //trim whitespace from word
        word.erase(0, word.find_first_not_of(" \t\n\r\f\v"));
        word.erase(word.find_last_not_of(" \t\n\r\f\v") + 1);
        
        //skip blank words
        if (word.empty()) continue;

        //split multiple meanings separated by semicolons
        //initialize stringstream with the entire meaningsStr to parse individual meanings
        stringstream meaningsStream(meaningsStr);
        string meaning;
        //loop to extract substrings delimited by ';' from the stringstream
        while (getline(meaningsStream, meaning, ';')) {
            //trim whitespace from each meaning
            meaning.erase(0, meaning.find_first_not_of(" \t\n\r\f\v"));
            meaning.erase(meaning.find_last_not_of(" \t\n\r\f\v") + 1);
            
            //only proceed if the trimmed token is non-empty (skip blank tokens)
            if (!meaning.empty()) {
                //insert the cleaned meaning along with its associated word and language into the hash table
                insert(word, meaning, language);
            }
        }
    wordcount ++;
    }
    //output the final result 
    cout << wordcount << " " << language << " words imported successfully." << endl;
    file.close();
}

//inserts a word with its meaning and language into the hash table
void HashTable::insert(string word, string meaning, string language) {
    word = toLower(word);
    language = toLower(language);
    
    unsigned long hash = hashCode(word);
    unsigned int index = hash % capacity;
    unsigned int i = 0;

    while (i < capacity) {
        if (buckets[index] == nullptr || buckets[index]->deleted) {
            buckets[index] = new Entry(word, meaning, language);
            size++;
            return;
        }
        else if (toLower(buckets[index]->word) == word) {
            buckets[index]->addTranslation(meaning, language);
            return;
        }

        collisions++;
        index = (index + 1) % capacity;
        i++;
    }

    cerr << "Error: Hash table is full" << endl;
}

//finds and prints translations for a given word using linear probing
void HashTable::find(string word) {
    word = toLower(word);
    unsigned long hash = hashCode(word);
    unsigned int index = hash % capacity;
    //number of probes performed
    unsigned int comparisons = 1;

    //linear probing through table to maintain simplicity of lookup
    while (comparisons < capacity) {
        //if slot has a valid, matching, non-deleted entry
        if (buckets[index] != nullptr && !buckets[index]->deleted && 
            toLower(buckets[index]->word) == word) {
            //provide a output for number of comparisons
            cout << word << " found in the Dictionary after " << comparisons << " comparisons." << endl;
            //display all stored translations
            buckets[index]->print();
            return;
        }
        //move to next slot (with wrap-around)
        index = (index + 1) % capacity;
        //increment probe count
        comparisons++;
    }
    //output error if word not present
    cout << word << " not found in the Dictionary." << endl;
}

//mark an entry as logically deleted so it won't be found but probe chains remain intact for other keys.
void HashTable::delWord(string word) {
    word = toLower(word);
    //compute primary hash and map to table index
    unsigned long hash = hashCode(word);
    unsigned int index = hash % capacity;
    //track number of slots inspected
    unsigned int comparisons = 0;

    //loop until we've checked every possible slot
    while (comparisons < capacity) {
        //if there's a valid entry and it matches our word:
        if (buckets[index] != nullptr && !buckets[index]->deleted && 
            toLower(buckets[index]->word) == word) {
            //logical deletion: mark entry as deleted without breaking probe chain
            buckets[index]->deleted = true;
            //adjust size counter to reflect removal
            size--;
            //inform the user of successful deletion
            cout << word << " has been successfully deleted from the Dictionary." << endl;
            return;
        }
        //advance to next slot (wrap around if needed)
        index = (index + 1) % capacity;
        //increment probe counter
        comparisons++;
    }
    //if loop completes, word wasn't found output error message
    cout << word << " not found in the Dictionary." << endl;
}

//remove all meanings for a word in a single language if no translations remain, delete the entry.
void HashTable::delTranslation(string word, string language) {
    //normalize both 'word' and 'language' to lowercase for consistent lookup
    word = toLower(word);
    language = toLower(language);
    unsigned long hash = hashCode(word);
    unsigned int index = hash % capacity;
    unsigned int comparisons = 0;

    //probe through the table, up to 'capacity' slots
    while (comparisons < capacity) {
        //check for a valid, non-deleted entry that matches 'word'
        if (buckets[index] != nullptr && !buckets[index]->deleted && 
            toLower(buckets[index]->word) == word) {
            
            //reference to vector of Translation objects
            auto& translations = buckets[index]->translations;
            //iterate through each Translation block
            for (auto it = translations.begin(); it != translations.end(); ++it) {
                //compare normalized language codes
                if (toLower(it->language) == language) {
                    //erase the entire Translation block for this language
                    translations.erase(it);
                    //confirmation output for the user
                    cout << "Translation has been successfully deleted from the Dictionary."<<endl;
                    
                    //if no translations left, mark as deleted
                    if (translations.empty()) {
                        buckets[index]->deleted = true;
                        size--;
                    }
                    return;
                }
            }
            //if the loop ends without finding the language, report it
            cout << "Translation not found for " << word << " in " << language << endl;
            return;
        }
        //advance to the next slot (linear probing) and increment attempt count
        index = (index + 1) % capacity;
        comparisons++;
    }

    cout << word << " not found in the Dictionary." << endl;
}

void HashTable::delMeaning(string word, string meaning, string language) {
    word = toLower(word);
    language = toLower(language);
    unsigned long hash = hashCode(word);
    unsigned int index = hash % capacity;
    unsigned int comparisons = 0;

    //linear probe to locate the word entry
    while (comparisons < capacity) {
        //check entry validity and match
        if (buckets[index] != nullptr && !buckets[index]->deleted && 
            toLower(buckets[index]->word) == word) {
            
            auto& translations = buckets[index]->translations;
            //found the correct entry, now search its translations
            for (auto& translation : translations) {
                if (toLower(translation.language) == language) {
                    //found the correct language block
                    auto& meanings = translation.meanings;
                    //find the specific meaning
                    auto it = std::find(meanings.begin(), meanings.end(), meaning);
                    if (it != meanings.end()) {
                        //meaning exists then erase it
                        meanings.erase(it);
                        cout << "Meaning has been successfully deleted from the Translation." <<endl;
                            
                        //if no meanings left, delete entire translation
                        if (meanings.empty()) {
                            //normalize both 'word' and 'language' to lowercase for consistent lookup
                            word = toLower(word);
                            language = toLower(language);
                            unsigned long hash = hashCode(word);
                            unsigned int index = hash % capacity;
                            unsigned int comparisons = 0;

                            //probe through the table, up to 'capacity' slots
                            while (comparisons < capacity) {
                                //check for a valid, non-deleted entry that matches 'word'
                                if (buckets[index] != nullptr && !buckets[index]->deleted && 
                                    toLower(buckets[index]->word) == word) {
                                    
                                    //reference to vector of Translation objects
                                    auto& translations = buckets[index]->translations;
                                    //iterate through each Translation block
                                    for (auto it = translations.begin(); it != translations.end(); ++it) {
                                        //compare normalized language codes
                                        if (toLower(it->language) == language) {
                                            //erase the entire Translation block for this language
                                            translations.erase(it);
                                        
                                            
                                            //if no translations left, mark as deleted
                                            if (translations.empty()) {
                                                buckets[index]->deleted = true;
                                                size--;
                                            }
                                            return;
                                        }
                                    }
                                    //if the loop ends without finding the language, report it
                                    cout << "Translation not found for " << word << " in " << language << endl;
                                    return;
                                }
                                //advance to the next slot (linear probing) and increment attempt count
                                index = (index + 1) % capacity;
                                comparisons++;
                            }

                            cout << word << " not found in the Dictionary." << endl;
                        }
                        return;
                    }
                    cout << "Meaning not found for " << word << " in " << language << endl;
                    return;
                }
            }
            cout << "Translation not found for " << word << " in " << language << endl;
            return;
        }
        //continue probing
        index = (index + 1) % capacity;
        comparisons++;
    }

    cout << word << " not found in the Dictionary." << endl;
}

void HashTable::exportData(string language, string filePath) {
    //open file for writing
    ofstream file(filePath);
    //output a error message if file can not be opened
    if (!file.is_open()) {
        cerr << "Error: Could not create file " << filePath << endl;
        return;
    }
    //write language header
    file << language << endl; 
    unsigned int count = 0;

    //loop through each bucket
    for (unsigned int i = 0; i < capacity; ++i) {
        if (buckets[i] != nullptr && !buckets[i]->deleted) {
            //loop translations to match target language
            for (const auto& trans : buckets[i]->translations) {
                if (toLower(trans.language) == toLower(language)) {
                    //write word and semicolon-separated meanings
                    file << buckets[i]->word << ":";
                    for (size_t j = 0; j < trans.meanings.size(); ++j) {
                        //write out the j-th meaning for this word
                        file << trans.meanings[j];
                        //if this isn’t the last meaning in the list, append a semicolon as a separator
                        if (j != trans.meanings.size() - 1) {
                            file << ";";
                        }
                    }
                    //after all meanings for this word/language are written, end the line
                    file << endl;
                    //increment the count
                    count++;
                }
            }
        }
    }
    //report number of records written
    cout << count << " records exported to " << filePath << endl;
    //close the file
    file.close();
}