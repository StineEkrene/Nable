#include "Words.h"

vector <string> readWords(string filename){
    vector <string> Words;
    ifstream ist{filename};
    if(!ist){
        error("Kunne ikke åpne fil ", filename);
    }

    string line; 
    while (getline(ist, line))
    {
        for_each(line.begin(), line.end(), [](char & c) {c = toupper(c);});
        Words.push_back(line);
    }
    ist.close(); 

    return Words;
}