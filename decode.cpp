#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <list>
#include <cstring>
#include <map>
#include <queue>
#include <string>

#include "rw_binary.h"


using namespace std;
#define MAX_BUFFER_SIZE 32768
// #define DEBUG


template <typename T>
vector<tuple<int, int, T>> decode_Huffman(vector<bool> &code, map<tuple<int, int, T>, vector<bool>> &dict) {
    long long n = code.size();

    map<vector<bool>, tuple<int, int, T>> r_dict;
    for(auto &[key, value]: dict) {
        r_dict[value] = key;
    }

    vector<tuple<int, int, T>> decoded;

    vector<bool> cur;
    for(long long i=0; i<n; ++i) {
        cur.push_back(code[i]);
        if(r_dict.find(cur) != r_dict.end()) {
            decoded.push_back(r_dict[cur]);
            cur = {};
        }
    }
    return decoded;
}

string decode_LZ77(vector<tuple<int, int, char>> &code) {

    string decoded;

    list<char> buffer;
    long long buffer_size = 0;

    for(const auto &[index, size, next]: code) {
        int i=0;
        auto it=buffer.end();
        for(; i<index; --it, ++i) {;}

        for(int j=0; j<size; ++j) {
            buffer.push_back(*it);
            ++buffer_size;
            decoded += *it;
            ++it;
            if(buffer_size >= MAX_BUFFER_SIZE)
                buffer.pop_front();
        }
        buffer.push_back(next);
        ++it;
        if(buffer_size >= MAX_BUFFER_SIZE)
            buffer.pop_front();

        decoded += next;
    }
    return decoded;
}


int main(int argc, char *argv[]) {
    string input_file, output_file;
    if(argc != 3) {
        cout << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        cout << "Enter input file: ";
        getline(cin, input_file);
        cout << "Enter output file: ";
        getline(cin, output_file);
    } else {
        input_file = argv[1];
        output_file = argv[2];
    }


    ifstream fin;
    fin.open(input_file, ios::binary);
    if(!fin.is_open()) {
        cout << "Couldn't open the read file" << endl;
        return 1;
    }

    if (!fin) {
        cout << "Problem with file open the file" << endl;
        return 1;
    }

    map<tuple<int, int, char>, vector<bool>> dict = read_dict_binary<char>(fin);
    vector<bool> code = read_vb_binary(fin);


    #ifdef DEBUG
    print_dict(dict);
    for(auto x: code) {
        cout << x;
    }
    cout << endl;
    #endif

    vector<tuple<int, int, char>> decoded_h = decode_Huffman(code, dict);
    #ifdef DEBUG
    for(const auto &x: decoded_h) {
        cout << "(" << get<0>(x) << " " << get<1>(x) << " \"" << get<2>(x) << "\")"<< endl;
    }
    #endif

    string decoded_message = decode_LZ77(decoded_h).c_str();

    #ifdef DEBUG
    cout << decoded_message << endl;
    #endif

    ofstream fout;
    fout.open(output_file, ios::binary);
    if(!fout.is_open()) {
        cout << "Couldn't open the write file" << endl;
        return 1;
    }
    fout << decoded_message;
    fout.close();
    return 0;
}