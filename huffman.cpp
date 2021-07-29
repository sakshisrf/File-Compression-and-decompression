#include "huffman.h"
#define INTERNAL_NODE_CHARACTER char(128)
#define PSEUDO_EOF char(129)
#define CHARACTER_CODE_SEPERATOR char(130)
#define HEADER_ENTRY_SEPERATOR char(131)
#define HEADER_TEXT_SEPERATOR char(132)

bool huffman::myComparator::operator()(node *node1, node *node2) {
    return node1->get_frequency() > node2->get_frequency();
}

void huffman::huffer(unordered_map<char, int> frequencyMap) {
    priority_queue <node *, vector<node *>, myComparator> HufferQueue;
    string tempString;
    node *leftNode, *rightNode, *newNode;
    for (const auto &item : frequencyMap)
        HufferQueue.push(new node(item.first, item.second));
    HufferQueue.push(new node(PSEUDO_EOF, 1));
    while (HufferQueue.size() != 1) {
        leftNode = HufferQueue.top();
        HufferQueue.pop();
        rightNode = HufferQueue.top();
        HufferQueue.pop();
        newNode = new node(INTERNAL_NODE_CHARACTER, leftNode->get_frequency() + rightNode->get_frequency());
        HufferQueue.push(newNode);
        newNode->set_left(leftNode);
        newNode->set_right(rightNode);
    }
    encodeCharacters(HufferQueue.top(), tempString);
}

void huffman::encodeCharacters(node *rootNode, string codeString) {

    if (!rootNode)
        return;
    if (rootNode->get_character() != INTERNAL_NODE_CHARACTER) {
        codeMap[rootNode->get_character()] = codeString;

    }
    encodeCharacters(rootNode->get_left(), codeString + "0");
    encodeCharacters(rootNode->get_right(), codeString + "1");
}

void huffman::writeHeader(ofstream &outputStream) {
    for (const auto &item : codeMap){
        outputStream << item.first << CHARACTER_CODE_SEPERATOR << item.second << HEADER_ENTRY_SEPERATOR;
    }
    outputStream << HEADER_TEXT_SEPERATOR;
}

void huffman::compressTofile(string InputfileName ,string OutputfileName) {

    char character;
    string file;
    ifstream inputStream;
    ofstream outputStream;
    outputStream.open(OutputfileName, ios::out);
    inputStream.open(InputfileName, ios::in);
    writeHeader(outputStream);
    while (inputStream.get(character))
        file += codeMap[character];
    inputStream.close();
    file += codeMap[PSEUDO_EOF];
    unsigned long remainder = (file.size() - 1) % 8;
    for (int i = 0; i < 8 - remainder; ++i)
        file += '0';
    stringstream stringStream(file);

    while (stringStream.good()) {
        bitset<8> bits;
        stringStream >> bits;
        char c = char(bits.to_ulong());
        outputStream << c;
    }


    outputStream.flush();
    outputStream.close();
}

void huffman::readHeader(ifstream &inputStream) {
    codeMap.clear();
    char character;
    inputStream.get(character);
    char key = character;
    while (character != HEADER_TEXT_SEPERATOR) {
        if (character == CHARACTER_CODE_SEPERATOR) {
            inputStream.get(character);
            while (character != HEADER_ENTRY_SEPERATOR) {
                codeMap[key] += character;
                inputStream.get(character);
            }
        } else
            key = character;
        inputStream.get(character);
    }
}

void huffman::dehuffer(string compressedFileName, string decompressedFileName) {
    char character;
    string codeString;
    ifstream inputStream;
    inputStream.open(compressedFileName, ios::in);
    readHeader(inputStream);
    while (inputStream.get(character)) {
        bitset<8> bits(character);
        codeString += bits.to_string();
    }
    node *rootNode = buildDecodingTree(codeMap);
    decompressToFile(codeString, rootNode, decompressedFileName);

}
node* huffman::buildDecodingTree(unordered_map<char, string> encodingMap) {

    node *rootNode = new node(INTERNAL_NODE_CHARACTER);
    node *previousNode;

    for (const auto &item : encodingMap) {
        previousNode = rootNode;
        node *newNode = new node(item.first);
        string characterCode = item.second;
        for (int i = 0; i < characterCode.size(); ++i) {
            if (characterCode[i] == '0') {
                if (i == characterCode.size() - 1)
                    previousNode->set_left(newNode);
                else {
                    if (!previousNode->get_left()) {
                        previousNode->set_left(new node(INTERNAL_NODE_CHARACTER));
                        previousNode = previousNode->get_left();
                    } else previousNode = previousNode->get_left();
                }
            } else {
                if (i == characterCode.size() - 1)
                    previousNode->set_right(newNode);
                else {
                    if (!previousNode->get_right()) {
                        previousNode->set_right(new node(INTERNAL_NODE_CHARACTER));
                        previousNode = previousNode->get_right();
                    } else previousNode = previousNode->get_right();
                }
            }
        }

    }
    return rootNode;
}

void huffman::decompressToFile(string codeString, node *rootNode, string decompressedFileName) {
    ofstream outputStream;
    outputStream.open(decompressedFileName, ios::out);
    node *traversingPointer = rootNode;
    for (int i = 0; i < codeString.size() + 1; ++i) {
        if (codeString[i] == '0')
            traversingPointer = traversingPointer->get_left();
        else
            traversingPointer = traversingPointer->get_right();

        if (traversingPointer->get_character() != INTERNAL_NODE_CHARACTER) {
            if (traversingPointer->get_character() == PSEUDO_EOF)
                break;
            outputStream << traversingPointer->get_character();
            traversingPointer = rootNode;
        }
    }
    outputStream.flush();
    outputStream.close();
}

int main(){
    cout<<1;
}
