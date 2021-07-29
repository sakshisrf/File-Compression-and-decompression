#include<iostream>
#include<bits/stdc++.h>
#include<fstream>
#include "node.h"
using namespace std;
#ifndef HUFFMANCODING_HUFFER_H
#define HUFFMANCODING_HUFFER_H

class huffman{
    unordered_map<char,string> codeMap;
    void encodeCharacters(node* rootNode,string codeString);
    void writeHeader(ofstream &outputStream);
    void readHeader(ifstream &inputStream);
    node* buildDecodingTree(unordered_map<char,string> encodingMap);
    class myComparator{
        public:
        bool operator()(node* node1,node* node2);
    };
    public:
    void huffer(unordered_map<char,int> frequencyMap);
    void dehuffer(string fileName, string decompressedFileName);
    void compressTofile(string InputfileName ,string OutputfileName);
    void decompressToFile(string codeString,node *rootNode,string decompressedFileName);

};

#endif
