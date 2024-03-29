//
// Created by Kang on 10/28/2019.
// A class that reads dictionary.txt then store the word and definition
// into a map.
// User can select option from the menu to print the whole dictionary, search for a word
// and add a new word and definition into the dictionary.
//
#include <climits>
#include "dictionary.hpp"
// read the file then store word and definition into map mp
void dictionary::readFile() {
    f.open("../dictionary.txt");
    if (!f.is_open()) {
        cerr << "Unable to open file" << endl;
        exit(1);
    } else {
        while(getline(f, s)) {
            stringstream ss(s);
            string word, def;
            getline(ss, word, '-');
            getline(ss, def, '-');
            mp.insert(pair<string, string>(word, def));
        }
    }
}
// print the word and definition stored in map mp
void dictionary::printDic() {
    for (auto it = mp.begin(); it != mp.end(); it++) {
        cout << it->first << "-" << it->second << endl;
    }
}
// show menu and pick choice
void dictionary::choice() {
    int choice;
    while(choice != 4) {
        // print menu
        cout << "1 - Print dictionary.txt\n"
             << "2 - Find word definition\n"
             << "3 - Enter new word and definition\n"
             << "4 - Exit\n";
        cout << "Enter a choice: ";
        // promote entry
        if(cin >> choice) {
            // choose to print the dictionary.txt
            switch(choice) {
                case 1:
                    cout << "\nHere's the full version of dictionary.txt: \n";
                    printDic();
                    cout <<"\n";
                    break;
                case 2:
                    findWord(); // choice to find a certain word in the dictionary.txt
                    break;
                case 3:
                    addWord(); // choice to add a word into dictionary.txt if it doesnt exist
                    break;
            }
        }  else {
            cin.clear();
            cin.ignore(INT_MAX,'\n');
            choice = 5;
        }
    }
    cout << "Bye, BB" << endl;
    f.close(); // close file
}
// find word in dictionary.txt
void dictionary::findWord() {
    string word;
    cout << "Enter the word: ";
    cin >> word;
    cout << "\n";
    if(isExist(word)) { // checking if the word exists
        auto itr = mp.find(word);
        cout << "The definition for \"" << word << "\"" <<" - " << itr->second << endl;
        cout << "\n";
        cin.clear(); // clear cin
    }
    else
        cout << "There's no \"" << word << "\" in dictionary.txt\n\n";
}
// if the word exist
bool dictionary::isExist(string &s) {
    for (auto it = mp.begin(); it != mp.end(); it++) {
        if(it->first == s)
            return true;
    }
    return false;
}
// add word and definition if it doesnt exist in the dictionary.txt
void dictionary::addWord() {
    string word;
    cout << "Enter the word: ";
    cin >> word;
    cout << "\n";
    if(isExist(word)) // checking if the word exists
        cout << "\"" << word << "\"" << " already exist\n\n";
    else {
        string def;
        // open file for reading, point to the nextLine
        ofstream of("../dictionary.txt", std::ios_base::app | std::ios_base::out);
        cout << "Enter the definition for \"" << word << "\" \n";
        cin.ignore(INT_MAX,'\n');
        getline(cin, def);
        mp.insert(pair<string, string>(word, def));
        of << word << "-" << def << "\n";
        of.close();
        cout << "\"" << word << "\" is addedd to the dictionary!\n\n";
    }
}