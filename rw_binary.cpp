#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <tuple>

#include "rw_binary.h"


using namespace std;



void write_vb_binary(ofstream &fout, vector<bool> a) {

    long long num_elements = a.size();
    fout.write((char*)(&num_elements), sizeof(num_elements));

    for (bool x : a) {
        fout.write((char*)(&x), sizeof(x));
    }
}

vector<bool> read_vb_binary(ifstream &fin) {
    long long num_elements;
    fin.read((char*)(&num_elements), sizeof(num_elements));

    vector<bool> vb(num_elements); // Resize the vector *before* reading

    for (size_t i = 0; i < num_elements; ++i) {
        bool temp;
        fin.read((char*)(&temp), sizeof(temp)); // Read each boolean
        vb[i] = temp;
    }
    return vb;
}