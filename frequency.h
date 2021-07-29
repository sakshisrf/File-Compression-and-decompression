#include<iostream>
#include<fstream>
#include<bits/stdc++.h>
using namespace std;

#ifndef FREQUENCY_COUNTER_H_
#define FREQUENCY_COUNTER_H_

class frequency_count{
    unordered_map<char,int> freq_map;

    public:
    const unordered_map<char,int> &get_frequency() const;
    void read_file(string filename);
};

#endif