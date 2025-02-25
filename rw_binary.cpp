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

template <typename T>
void write_tuple_binary(ofstream &fout, tuple<int, int, T> t) {
    long long size_t0 = sizeof(get<0>(t));
    fout.write((char*)&size_t0, sizeof size_t0);
    fout.write((char*)&get<0>(t), size_t0);

    long long size_t1 = sizeof(get<1>(t));
    fout.write((char*)&size_t1, sizeof size_t1);
    fout.write((char*)&get<1>(t), size_t1);

    long long size_t2 = sizeof(get<2>(t));
    fout.write((char*)&size_t2, sizeof size_t2);
    fout.write((char*)&get<2>(t), size_t2);
}

template<typename T>
tuple<int, int, T> read_tuple_binary(ifstream &fin) {
    long long size_t0;
    fin.read((char*)&size_t0, sizeof size_t0);
    int t0;
    fin.read((char*)&t0, size_t0);

    long long size_t1;
    fin.read((char*)&size_t1, sizeof size_t1);
    int t1;
    fin.read((char*)&t1, size_t1);

    long long size_t2;
    fin.read((char*)&size_t2, sizeof size_t2);
    T t2;
    fin.read((char*)&t2, size_t2);

    return {t0, t1, t2};
}


template<typename T>
void write_dict_binary(ofstream &fout, map<tuple<int, int, T>, vector<bool>> &dict) {
    long long dict_size = dict.size();
    fout.write((char*)&dict_size, sizeof dict_size);
    for(auto &x: dict) {
        write_tuple_binary(fout, x.first);
        write_vb_binary(fout, x.second);
    }
}


template <typename T>
map<tuple<int, int, T>, vector<bool>> read_dict_binary(ifstream &fin) {
    long long dict_size;
    fin.read((char*)&dict_size, sizeof dict_size);
    map<tuple<int, int, T>, vector<bool>> dict;
    for(int i=0; i<dict_size; ++i) {
        tuple<int, int, T> key = read_tuple_binary<T>(fin);
        if (fin.fail()) break; // Check if reading the key failed

        vector<bool> val = read_vb_binary(fin);
        if (fin.fail()) break; // Check if reading the value failed

        dict[key] = val;
    }
    return dict;

}

template <typename T>
void print_dict(map<tuple<int, int, T>, vector<bool>> &dict) {
    for(auto &x: dict) {
        cout << "\"" << get<0>(x.first) << " " << get<1>(x.first) << " " << get<2>(x.first) << "\" -> \"";
        for(auto bi: x.second) {
            cout << bi;
        }
        cout << "\"" << endl;
    }
}