#include "frequency.h"

void frequency_count::read_file(string filename){
    char character;
    ifstream inputfile;
    inputfile.open(filename,ios::in);

    while(inputfile.get(character)){
        freq_map[character]++;
    }

    inputfile.close();
}

unordered_map<char,int> frequency_count:: get_frequency(){
    return freq_map;
}
