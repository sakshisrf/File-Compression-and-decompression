#include<bits/stdc++.h>
#include<iostream>
using namespace std;
#ifndef HUFFMANCODING_NODE_H
#define HUFFMANCODING_NODE_H
class node{
    char character;
    int frequency;
    node* left;
    node* right;

    public:
    node(char character,int frequency);
    node(char character);
    char get_character() const;
    int get_frequency() const;
    node* get_left() const;
    node* get_right()  const;
    void set_left(node* left);
    void set_right(node* right);
};
#endif